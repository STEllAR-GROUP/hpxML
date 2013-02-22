//  Copyright (c) 2012 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_fwd.hpp>

#include "grid.hpp"
#include <cmath>

#include <hpx/hpx.hpp>
#include <hpx/runtime/actions/plain_action.hpp>
#include <hpx/runtime/components/plain_component_factory.hpp>
#include <hpx/runtime/components/component_factory.hpp>
#include <hpx/components/remote_object/new.hpp>
#include <hpx/components/remote_object/distributed_new.hpp>
#include <hpx/components/dataflow/dataflow_object.hpp>
#include <hpx/util/high_resolution_timer.hpp>
#include <hpx/include/async.hpp>
#include <hpx/include/iostreams.hpp>
#include <algorithm>

#include <hpx/components/dataflow/dataflow.hpp>
#include <hpx/components/dataflow/dataflow_trigger.hpp>
#include <hpx/components/dataflow/async_dataflow_wait.hpp>

#undef min

using bright_future::grid;
using bright_future::update;
using bright_future::update_residuum;

typedef bright_future::grid<double> grid_type;
typedef std::pair<std::size_t, std::size_t> range_type;

using hpx::util::high_resolution_timer;

using hpx::cout;
using hpx::flush;
using hpx::lcos::dataflow_trigger;
using hpx::find_here;
using hpx::find_all_localities;
using hpx::find_here;
using hpx::lcos::wait;
using hpx::naming::id_type;
using hpx::naming::get_locality_from_id;

using hpx::components::distributed_new;
using hpx::components::object;

struct data
{
    data(
        std::size_t n_x_local_
      , std::size_t n_y_local_
      , std::size_t n_x_
      , std::size_t n_y_
      , std::size_t block_size_
      , double hx_
      , double hy_
      , double div_inv_
      , double inv_hx_sq_
      , double inv_hy_sq_
    )
        : n_x(n_x_)
        , n_y(n_y_)
        , n_x_local(n_x_local_)
        , n_y_local(n_y_local_)
        , block_size(block_size_)
        , hx(hx_)
        , hy(hy_)
        , div_inv(div_inv_)
        , inv_hx_sq(inv_hx_sq_)
        , inv_hy_sq(inv_hy_sq_)
        , u(2, grid_type(n_x_local_, n_y_local_))
        , rhs(n_x_local_, n_y_local_)
    {}
    std::size_t n_x;
    std::size_t n_y;
    std::size_t n_x_local;
    std::size_t n_y_local;
    std::size_t block_size;
    double hx;
    double hy;
    double div_inv;
    double inv_hx_sq;
    double inv_hy_sq;
    std::vector<grid_type> u;
    grid_type rhs;

};

using hpx::components::dataflow_object;

struct init_fun
{
    range_type x_range;
    range_type y_range;
    std::size_t x_start;
    std::size_t y_start;

    init_fun() {}

    init_fun(range_type x, range_type y, std::size_t xx, std::size_t yy)
        : x_range(x)
        , y_range(y)
        , x_start(xx)
        , y_start(yy)
    {}

    typedef void result_type;

    void operator()(data & d) const
    {
        for(std::size_t y = y_range.first; y < y_range.second; ++y)
        {
            for(std::size_t x = x_range.first; x < x_range.second; ++x)
            {
                std::size_t xx = x_start + x - 1;
                std::size_t yy = y_start + y - 1;
                d.u[0](x, y) = yy == (d.n_y - 1) ? sin((double(xx) * d.hx) * 6.283) * sinh(6.283) : 0.0;
                d.u[1](x, y) = yy == (d.n_y - 1) ? sin((double(xx) * d.hx) * 6.283) * sinh(6.283) : 0.0;
                d.rhs(x, y) = 39.478 * sin((double(xx) * d.hx) * 6.283) * sinh((double(yy) * d.hy) * 6.283);
            }
        }
    }

    template <typename Archive>
    void serialize(Archive & ar, const unsigned int )
    {
        ar & x_range;
        ar & y_range;
        ar & x_start;
        ar & y_start;
    }
};

struct get_col_fun
{
    range_type range;
    std::size_t col;
    std::size_t cur;

    typedef std::vector<double> result_type;

    get_col_fun() {}
    get_col_fun(range_type const & r, std::size_t ro, std::size_t cur_)
        : range(r), col(ro), cur(cur_) {}

    template <typename Archive>
    void serialize(Archive & ar, unsigned)
    {
        ar & range;
        ar & col;
        ar & cur;
    }

    result_type operator()(data & d) const
    {
        std::vector<double> result;
        result.reserve(range.second-range.first);
        for(std::size_t y = range.first; y < range.second; ++y)
        {
            result.push_back(d.u[cur](col, y));
        }
        return result;
    }
};

struct get_row_fun
{
    range_type range;
    std::size_t row;
    std::size_t cur;

    typedef std::vector<double> result_type;

    get_row_fun() {}
    get_row_fun(range_type const & r, std::size_t ro_, std::size_t cur_)
        : range(r), row(ro_), cur(cur_) {}

    template <typename Archive>
    void serialize(Archive & ar, unsigned)
    {
        ar & range;
        ar & row;
        ar & cur;
    }

    result_type operator()(data & d) const
    {
        std::vector<double> result;

        result.reserve((range.second-range.first));

        for(std::size_t x = range.first; x < range.second; ++x)
        {
            result.push_back(d.u[cur](x, row));
        }

        return result;
    }
};

struct update_top_boundary_fun
{
    range_type range;
    dataflow_object<data> neighbor;
    std::size_t cur;

    typedef void result_type;

    update_top_boundary_fun() {}
    update_top_boundary_fun(range_type const & r, dataflow_object<data> n, std::size_t cur_)
        : range(r)
        , neighbor(n)
        , cur(cur_)
    {}

    template <typename Archive>
    void serialize(Archive & ar, unsigned)
    {
        ar & range;
        ar & neighbor;
        ar & cur;
    }

    result_type operator()(data & d) const
    {

        std::vector<double> b = neighbor.apply(
            get_row_fun(range, d.u[cur].y()-2, cur)).get_future().get();
        for(std::size_t x = range.first, i = 0; x < range.second; ++x, ++i)
        {
            d.u[cur](x, 0) = b.at(i);
        }
    }
};

struct update_bottom_boundary_fun
{
    range_type range;
    dataflow_object<data> neighbor;
    std::size_t cur;

    typedef void result_type;

    update_bottom_boundary_fun() {}
    update_bottom_boundary_fun(range_type const & r, dataflow_object<data> n, std::size_t cur_)
        : range(r)
        , neighbor(n)
        , cur(cur_)
    {}

    template <typename Archive>
    void serialize(Archive & ar, unsigned)
    {
        ar & range;
        ar & neighbor;
        ar & cur;
    }

    result_type operator()(data & d) const
    {
        std::vector<double> b = neighbor.apply(
            get_row_fun(range, 1, cur)).get_future().get();
        for(std::size_t x = range.first, i = 0; x < range.second; ++x, ++i)
        {
            d.u[cur](x, d.u[cur].y()-1) = b.at(i);
        }
    }
};

struct update_right_boundary_fun
{
    range_type range;
    dataflow_object<data> neighbor;
    std::size_t cur;

    typedef void result_type;

    update_right_boundary_fun() {}
    update_right_boundary_fun(range_type const & r, dataflow_object<data> n, std::size_t cur_)
        : range(r)
        , neighbor(n)
        , cur(cur_)
    {}

    template <typename Archive>
    void serialize(Archive & ar, unsigned)
    {
        ar & range;
        ar & neighbor;
        ar & cur;
    }

    result_type operator()(data & d) const
    {
        std::vector<double> b = neighbor.apply(
            get_col_fun(range, 1, cur)).get_future().get();
        for(std::size_t y = range.first, i = 0; y < range.second; ++y, ++i)
        {
            d.u[cur](d.u[cur].x()-1, y) = b.at(i);
        }
    }
};

struct update_left_boundary_fun
{
    range_type range;
    dataflow_object<data> neighbor;
    std::size_t cur;

    typedef void result_type;

    update_left_boundary_fun() {}
    update_left_boundary_fun(range_type const & r, dataflow_object<data> n, std::size_t cur_)
        : range(r)
        , neighbor(n)
        , cur(cur_)
    {}

    template <typename Archive>
    void serialize(Archive & ar, unsigned)
    {
        ar & range;
        ar & neighbor;
        ar & cur;
    }

    result_type operator()(data & d) const
    {
        std::vector<double> b = neighbor.apply(
            get_col_fun(range, d.u[cur].x()-2, cur)).get_future().get();
        for(std::size_t y = range.first, i = 0; y < range.second; ++y, ++i)
        {
            d.u[cur](0, y) = b.at(i);
        }
    }
};

struct update_fun
{
    typedef void result_type;

    range_type x_range;
    range_type y_range;
    std::size_t old;
    std::size_t new_;

    update_fun() {}

    update_fun(range_type x, range_type y, std::size_t old_, std::size_t n)
        : x_range(x)
        , y_range(y)
        , old(old_)
        , new_(n)
    {}

    void operator()(data & d) const
    {
        for(std::size_t y_block = y_range.first; y_block < y_range.second; y_block += 128)
        {
            std::size_t y_end = (std::min)(y_block + 128, y_range.second);
            for(std::size_t x_block = x_range.first; x_block < x_range.second; x_block += 128)
            {
                std::size_t x_end = (std::min)(x_block + 128, x_range.second);
                for(std::size_t y = y_block; y < y_end; ++y)
                {
                    for(std::size_t x = x_block; x < x_end; ++x)
                    {
                        d.u[new_](x,y)
                            = d.div_inv * (
                                d.rhs(x,y)
                              + d.inv_hx_sq * (
                                    d.u[old](x-1,y)
                                  + d.u[old](x+1,y)
                                )
                              + d.inv_hy_sq * (
                                    d.u[old](x,y-1)
                                  + d.u[old](x,y+1)
                                )
                            );
                    }
                }
            }
        }
    }

    template <typename Archive>
    void serialize(Archive & ar, const unsigned int)
    {
        ar & x_range;
        ar & y_range;
    }
};

struct output_fun
{
    std::string file_name;
    range_type x_range;
    range_type y_range;
    std::size_t x_start;
    std::size_t y_start;
    std::size_t cur;

    output_fun() {}

    output_fun(std::string const & output, range_type x, range_type y, std::size_t xx, std::size_t yy, std::size_t cur_)
        : file_name(output)
        , x_range(x)
        , y_range(y)
        , x_start(xx)
        , y_start(yy)
        , cur(cur_)
    {}

    typedef void result_type;

    void operator()(data & d) const
    {
        std::ofstream file(file_name.c_str(), std::ios_base::app | std::ios_base::out);
        for(std::size_t x = x_range.first; x < x_range.second; ++x)
        {
            for(std::size_t y = y_range.first; y < y_range.second; ++y)
            {
                double xx = static_cast<double>(x_start + x) - 1.;
                double yy = static_cast<double>(y_start + y) - 1.;
                file << xx * d.hx << " " << yy * d.hy << " " << d.u[cur](x, y) << "\n";
            }
            file << "\n";
        }
    }

    template <typename Archive>
    void serialize(Archive & ar, const unsigned int )
    {
        ar & file_name;
        ar & x_range;
        ar & y_range;
        ar & x_start;
        ar & y_start;
    }
};

void gs(
    /*
    bright_future::grid<double> & u
  , bright_future::grid<double> const & rhs
  */
    std::size_t n_x
  , std::size_t n_y
  , double hx_
  , double hy_
  , double k_
  , double relaxation_
  , unsigned max_iterations
  , unsigned //iteration_block
  , unsigned block_size
  , std::size_t //cache_block
  , std::string const & output
)
{
    /*
    grid_type rhs(n_x, n_y);
    grid_type u0(n_x, n_y);
    grid_type u1(n_x, n_y);
    */

    double relaxation;
    double k;
    double hx;
    double hy;
    double div;// = (2.0/(hx*hx) + 2.0/(hy*hy) + (k*k));
    double hx_sq;// = hx * hx;
    double hy_sq;// = hy * hy;
    // set our initial values, setting the top boundary to be a dirichlet
    // boundary condition
    unsigned iter;

    //bool debug = false;

    high_resolution_timer t;
    {
        hx = hx_;
        hy = hy_;
        k = k_;
        relaxation = relaxation_;
        div = (2.0/(hx*hx) + 2.0/(hy*hy) + (k*k));
        double div_inv = 1.0/div;
        hx_sq = hx * hx;
        hy_sq = hy * hy;
        double inv_hx_sq = 1.0 / hx_sq;
        double inv_hy_sq = 1.0 / hy_sq;

        /*
        std::size_t n_x_block = n_x / block_size + 1;
        std::size_t n_y_block = n_y / block_size + 1;
        */

        hpx::components::component_type type
            = hpx::components::get_component_type<hpx::components::server::remote_object>();

        std::vector<id_type> prefixes = find_all_localities(type);

        double num_blocks_sqrt = std::floor(std::sqrt(static_cast<double>(prefixes.size())));

        std::size_t num_blocks = 0;
        if(std::abs(num_blocks_sqrt - std::sqrt(static_cast<double>(prefixes.size()))) > 1e-9)
        {
            num_blocks_sqrt = num_blocks_sqrt + 1;
        }
        num_blocks = std::size_t(num_blocks_sqrt * num_blocks_sqrt);

        typedef dataflow_object<data> object_type;

        typedef hpx::lcos::dataflow_base<void> promise;

        std::size_t n_x_block = std::size_t(num_blocks_sqrt);
        std::size_t n_y_block = std::size_t(num_blocks_sqrt);

        std::size_t n_x_local = n_x / n_x_block + 1;
        std::size_t n_y_local = n_y / n_y_block + 1;

        std::size_t n_x_local_block = n_x_local/block_size+1;
        std::size_t n_y_local_block = n_y_local/block_size+1;

        std::vector<hpx::lcos::future<object<data> > >
            objects =
                distributed_new<data>(
                    num_blocks
                  , n_x_local + 2
                  , n_y_local + 2
                  , n_x
                  , n_y
                  , block_size
                  , hx
                  , hy
                  , div_inv
                  , inv_hx_sq
                  , inv_hy_sq
                );

        typedef grid<object_type> object_grid_type;

        object_grid_type object_grid(n_x_block, n_y_block);
        {
            std::size_t x = 0;
            std::size_t y = 0;

            BOOST_FOREACH(hpx::lcos::future<object<data> > const & o, objects)
            {
                object_grid(x, y) = o.get();

                if(++x > n_x_block - 1)
                {
                    x = 0;
                    ++y;
                }
            }
        }

        typedef grid<promise> promise_grid_type;
        typedef grid<promise_grid_type> block_promise_grid_type;

        block_promise_grid_type
            deps(
                block_promise_grid_type(
                    n_x_block
                  , n_y_block
                  , block_size
                  , promise_grid_type(
                        n_x_local_block
                      , n_y_local_block
                    )
                )
            );

        for(std::size_t y_block = 0; y_block < n_y_block; ++y_block)
        {
            for(std::size_t x_block = 0; x_block < n_x_block; ++x_block)
            {
                for(std::size_t y = 0, yy = 0; y < n_y_local + 2; y += block_size, ++yy)
                {
                    for(std::size_t x = 0, xx = 0; x < n_x_local + 2; x += block_size, ++xx)
                    {
                        range_type
                            x_range(
                                x
                              , (std::min)(n_x_local + 2, x + block_size)
                            );

                        range_type
                            y_range(
                                y
                              , (std::min)(n_y_local + 2, y + block_size)
                            );

                        deps(x_block, y_block)(xx,yy)
                            = object_grid(x_block, y_block).apply(
                                init_fun(
                                    x_range
                                  , y_range
                                  , x_block * n_x_local
                                  , y_block * n_y_local
                                )
                            );
                        deps(x_block, y_block)(xx,yy).get_future().get();
                    }
                }
            }
        }

        std::cout << "initialization complete\n";

        t.restart();
        std::size_t old = 0;
        std::size_t new_ = 1;
        for(iter = 0; iter < max_iterations; ++iter)//iter += iteration_block)
        {
            for(std::size_t y_block = 0; y_block < n_y_block; ++y_block)
            {
                for(std::size_t x_block = 0; x_block < n_x_block; ++x_block)
                {
                    promise_grid_type & cur_deps = deps(x_block, y_block);
                    for(std::size_t y = 1, yy = 0; y < n_y_local + 1; y += block_size, ++yy)
                    {
                        for(std::size_t x = 1, xx = 0; x < n_x_local + 1; x += block_size, ++xx)
                        {
                            range_type
                                x_range(
                                    xx == 0 && x_block == 0 ? 2 : x
                                  , xx + 1 == n_x_local_block
                                        ? x_block + 1 == n_x_block
                                            ? n_x - (x_block * n_x_local)
                                            : (std::min)(n_x_local + 1, x + block_size)
                                        : (std::min)(n_x_local + 1, x + block_size)
                                );

                            range_type
                                y_range(
                                    yy == 0 && y_block == 0 ? 2 : y
                                  , yy + 1 == n_y_local_block
                                        ? y_block + 1 == n_y_block
                                            ? n_y - (y_block * n_y_local)
                                            : (std::min)(n_y_local + 1, y + block_size)
                                        : (std::min)(n_y_local + 1, y + block_size)
                                );

                            std::vector<promise > trigger;
                            trigger.reserve(9);

                            trigger.push_back(cur_deps(xx,yy));

                            if(xx > 0)
                                trigger.push_back(cur_deps(xx-1, yy));
                            if(yy > 0)
                                trigger.push_back(cur_deps(xx, yy-1));
                            if(xx + 1 < n_x_local_block)
                                trigger.push_back(cur_deps(xx+1, yy));
                            if(yy + 1 < n_y_local_block)
                                trigger.push_back(cur_deps(xx, yy+1));

                            if(xx == 0 && x_block > 0)
                            {
                                trigger.push_back(
                                    object_grid(x_block, y_block).apply(
                                        update_left_boundary_fun(
                                            y_range
                                          , object_grid(x_block - 1, y_block)
                                          , old
                                        )
                                    )
                                );
                            }

                            if(xx + 1 == n_x_local_block && x_block + 1 < n_x_block)
                            {
                                trigger.push_back(
                                    object_grid(x_block, y_block).apply(
                                        update_right_boundary_fun(
                                            y_range
                                          , object_grid(x_block + 1, y_block)
                                          , old
                                        )
                                    )
                                );
                            }

                            if(yy == 0 && y_block > 0)
                            {
                                trigger.push_back(
                                    object_grid(x_block, y_block).apply(
                                        update_top_boundary_fun(
                                            x_range
                                          , object_grid(x_block, y_block - 1)
                                          , old
                                        )
                                    )
                                );
                            }

                            if(yy + 1 == n_y_local_block && y_block + 1 < n_y_block)
                            {
                                trigger.push_back(
                                    object_grid(x_block, y_block).apply(
                                        update_bottom_boundary_fun(
                                            x_range
                                          , object_grid(x_block, y_block + 1)
                                          , old
                                        )
                                    )
                                );
                            }

                            cur_deps(xx, yy)
                                = object_grid(x_block, y_block).apply(
                                    update_fun(
                                        x_range
                                      , y_range
                                      , old
                                      , new_
                                    )
                                  , dataflow_trigger(object_grid(x_block, y_block).gid_, trigger)
                                );
                        }
                    }
                }
            }
            std::swap(old, new_);
        }
        std::cout << "dataflow construction complete\n";
        BOOST_FOREACH(promise_grid_type & block, deps)
        {
            BOOST_FOREACH(promise & p, block)
            {
                p.get_future().get();
            }
            //wait(block.data_handle(), [&](size_t){if(debug) cout << "." << flush; });
        }

        double time_elapsed = t.elapsed();
        cout << n_x-1 << "x" << n_y-1 << " "
             << ((double((n_x-2)*(n_y-2) * max_iterations)/1e6)/time_elapsed) << " MLUP/S\n" << flush;

        if(!output.empty())
        {
            // make sure to have an empty file
            {
                std::ofstream(output.c_str());
            }
            for(std::size_t x_block = 0; x_block < n_x_block; ++x_block)
            {
                for(std::size_t y_block = 0; y_block < n_y_block; ++y_block)
                {
                    range_type
                        x_range(
                            1
                          , x_block + 1 == n_x_block
                          ? n_x - x_block * n_x_local + 1
                          : n_x_local+1
                        );

                    range_type
                        y_range(
                            1
                          , y_block + 1 == n_y_block
                          ? n_y - y_block * n_y_local + 1
                          : n_y_local+1
                        );

                    object_grid(x_block, y_block).apply(
                        output_fun(
                            output
                          , x_range
                          , y_range
                          , x_block * n_x_local
                          , y_block * n_y_local
                          , new_
                        )
                    ).get_future().get();
                }
            }
        }
    }
}
