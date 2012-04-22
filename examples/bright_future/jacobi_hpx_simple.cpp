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
#include <hpx/util/high_resolution_timer.hpp>
#include <hpx/include/async.hpp>
#include <hpx/include/iostreams.hpp>
#include <algorithm>

#include <fstream>

#include <hpx/components/dataflow/dataflow.hpp>
#include <hpx/components/dataflow/dataflow_trigger.hpp>
#include <hpx/components/dataflow/async_dataflow_wait.hpp>
#include <hpx/components/dataflow/dataflow_object.hpp>

#undef min

using bright_future::grid;
using bright_future::range_type;
using bright_future::jacobi_kernel_simple;

typedef bright_future::grid<double> grid_type;

using hpx::util::high_resolution_timer;

using hpx::cout;
using hpx::flush;
using hpx::lcos::dataflow_trigger;
using hpx::lcos::dataflow_base;
using hpx::find_here;
using hpx::find_all_localities;
using hpx::find_here;
using hpx::lcos::wait;
using hpx::naming::id_type;
using hpx::naming::get_locality_from_id;

using hpx::components::new_;

using hpx::components::dataflow_object;

struct update_fun
{
    typedef void result_type;

    range_type x_range;
    range_type y_range;
    std::size_t old;
    std::size_t n;
    std::size_t cache_block;

    update_fun() {}

    update_fun(update_fun const & other)
      : x_range(other.x_range)
      , y_range(other.y_range)
      , old(other.old)
      , n(other.n)
      , cache_block(other.cache_block)
    {}

    update_fun(BOOST_RV_REF(update_fun) other)
      : x_range(boost::move(other.x_range))
      , y_range(boost::move(other.y_range))
      , old(boost::move(other.old))
      , n(boost::move(other.n))
      , cache_block(boost::move(other.cache_block))
    {}

    update_fun(range_type const & x, range_type const & y, std::size_t o, std::size_t n_, std::size_t c)
        : x_range(x)
        , y_range(y)
        , old(o)
        , n(n_)
        , cache_block(c)
    {}

    update_fun& operator=(BOOST_COPY_ASSIGN_REF(update_fun) other)
    {
        x_range = other.x_range;
        y_range = other.y_range;
        old = other.old;
        n = other.n;
        cache_block = other.cache_block;
        return *this;
    }

    update_fun& operator=(BOOST_RV_REF(update_fun) other)
    {
        x_range = boost::move(other.x_range);
        y_range = boost::move(other.y_range);
        old = boost::move(other.old);
        n = boost::move(other.n);
        cache_block = boost::move(other.cache_block);
        return *this;
    }

    void operator()(std::vector<grid_type> & u) const
    {
        jacobi_kernel_simple(
            u
          , x_range
          , y_range
          , old, n
          , cache_block
        );
    }

    template <typename Archive>
    void serialize(Archive & ar, const unsigned int )
    {
        ar & x_range;
        ar & y_range;
        ar & old;
        ar & n;
        ar & cache_block;
    }

    private:
        BOOST_COPYABLE_AND_MOVABLE(update_fun)
};

struct output_fun
{
    std::string file_name;
    range_type x_range;
    range_type y_range;
    std::size_t cur;

    output_fun() {}

    output_fun(std::string const & output, range_type x, range_type y, std::size_t cur_)
        : file_name(output)
        , x_range(x)
        , y_range(y)
        , cur(cur_)
    {}

    typedef void result_type;

    void operator()(std::vector<grid_type> & u) const
    {
        std::ofstream file(file_name.c_str(), std::ios_base::app | std::ios_base::out);
        for(std::size_t x = x_range.first; x < x_range.second; ++x)
        {
            for(std::size_t y = y_range.first; y < y_range.second; ++y)
            {
                file << x << " " << y << " " << u[cur](x, y) << "\n";
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
    }
};

void gs(
    std::size_t n_x
  , std::size_t n_y
  , double //hx_
  , double //hy_
  , double //k_
  , double //relaxation_
  , unsigned max_iterations
  , unsigned //iteration_block
  , unsigned block_size
  , std::size_t cache_block
  , std::string const & output
)
{
    typedef dataflow_object<std::vector<grid_type> > object_type;

    object_type u(new_<std::vector<grid_type> >(find_here(), 2, grid_type(n_x, n_y, block_size, 1)).get());

    n_x = n_x -1;
    n_y = n_y -1;

    high_resolution_timer t;
    std::size_t old = 0;
    std::size_t n = 1;
    std::size_t n_x_block = (n_x - 2)/block_size + 1;
    std::size_t n_y_block = (n_y - 2)/block_size + 1;
    typedef dataflow_base<void> promise;
    typedef grid<promise> promise_grid_type;
    std::vector<promise_grid_type> deps(2, promise_grid_type(n_x_block, n_y_block));

    t.restart();
    for(std::size_t iter = 0; iter < max_iterations; ++iter)//iter += iteration_block)
    {
        for(std::size_t y = 1, yy = 0; y < n_y - 1; y += block_size, ++yy)
        {
            std::size_t y_end = (std::min)(y + block_size, n_y-1);
            for(std::size_t x = 1, xx = 0; x < n_x - 1; x += block_size, ++xx)
            {
                std::size_t x_end = (std::min)(x + block_size, n_x-1);
                if(iter > 0)
                {
                    std::vector<promise > trigger;
                    trigger.reserve(5);
                    trigger.push_back(deps[old](xx,yy));
                    if(xx + 1 < n_x_block)
                        trigger.push_back(deps[old](xx+1, yy));
                    if(xx > 0)
                        trigger.push_back(deps[old](xx-1, yy));
                    if(yy + 1 < n_y_block)
                        trigger.push_back(deps[old](xx, yy+1));
                    if(yy > 0)
                        trigger.push_back(deps[old](xx, yy-1));

                    deps[n](xx, yy)
                        = u.apply(
                            boost::move(update_fun(
                                range_type(x, x_end)
                              , range_type(y, y_end)
                              , old
                              , n
                              , cache_block
                            ))
                          , dataflow_trigger(u.gid_, boost::move(trigger))
                        );
                }
                else
                {
                    deps[n](xx, yy)
                        = u.apply(
                            boost::move(update_fun(
                                boost::move(range_type(x, x_end))
                              , boost::move(range_type(y, y_end))
                              , old
                              , n
                              , cache_block
                            ))
                        );
                }
            }
        }
        std::swap(old, n);
    }
    for(std::size_t y = 1, yy = 0; y < n_y - 1; y += block_size, ++yy)
    {
        for(std::size_t x = 1, xx = 0; x < n_x - 1; x += block_size, ++xx)
        {
            deps[old](xx, yy).get_future().get();
        }
    }

    double time_elapsed = t.elapsed();
    cout << n_x << "x" << n_y << " "
         //<< ((((n_x-2)*(n_y-2) * max_iterations)/1e6)/time_elapsed) << " MLUPS/s\n" << flush;
         << ((double((n_x-1)*(n_y-1) * max_iterations)/1e6)/time_elapsed) << " MLUPS/s\n" << flush;

    if(!output.empty())
    {
        // make sure to have an empty file
        {
            std::ofstream(output.c_str());
        }
        u.apply(
            output_fun(output, range_type(0, n_x), range_type(0, n_y), old)
        ).get_future().get();
    }
}
