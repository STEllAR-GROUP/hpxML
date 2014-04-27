//  Copyright (c) 2014 Hartmut Kaiser
//  Copyright (c) 2014 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_init.hpp>
#include <hpx/hpx.hpp>

///////////////////////////////////////////////////////////////////////////////
struct cell
{
    cell(std::size_t size)
      : data_(size)
    {}

    void init(double initial_value)
    {
        double base_value = double(initial_value * size());
        for (std::size_t i = 0; i != size(); ++i)
            data_[i] = base_value + double(i);
    }

    double& operator[](std::size_t idx) { return data_[idx]; }
    double operator[](std::size_t idx) const { return data_[idx]; }

    std::size_t size() const { return data_.size(); }

private:
    std::vector<double> data_;
};

std::ostream& operator<<(std::ostream& os, cell const& c)
{
    os << "{";
    for (std::size_t i = 0; i != c.size(); ++i)
    {
        if (i != 0)
            os << ", ";
        os << c[i];
    }
    os << "}";
    return os;
}

///////////////////////////////////////////////////////////////////////////////
typedef std::vector<cell> space;        // data for one time step
typedef std::vector<space> spacetime;   // all of stored time steps

///////////////////////////////////////////////////////////////////////////////
inline std::size_t idx(std::size_t i, std::size_t size)
{
    return (boost::int64_t(i) < 0) ? (i + size) % size : i % size;
}

///////////////////////////////////////////////////////////////////////////////
int hpx_main(boost::program_options::variables_map& vm)
{
    boost::uint64_t nt = vm["nt"].as<boost::uint64_t>();   // Number of steps.
    boost::uint64_t nx = vm["nx"].as<boost::uint64_t>();   // Number of grid points.
    boost::uint64_t np = vm["np"].as<boost::uint64_t>();   // Number of partitions.

    // U[t][i] is the state of position i at time t.
    spacetime U(2);
    for (space& s: U)
        s.resize(np, cell(nx));

    // Initial conditions:
    //   f(0, i) = i
    for (std::size_t i = 0; i != np; ++i)
        U[0][i].init(double(i));

    // Our operator:
    //   f(t+1, i) = (f(t, i-1) + f(t, i) + f(t, i+1)) / 3
    auto Op = [](double a, double b, double c) { return (a + b + c) / 3.; };

    auto PartOp = [&Op](cell const& left, cell const& middle, cell const& right) -> cell
        {
            std::size_t size = middle.size();
            cell next(size);

            next[0] = Op(left[size-1], middle[0], middle[1]);

            for (std::size_t i = 1; i != size-2; ++i)
                next[i] = Op(middle[i-1], middle[i], middle[i+1]);

            next[size-1] = Op(middle[size-2], middle[size-1], right[0]);

            return next;
        };

    for (std::size_t t = 0; t != nt; ++t)
    {
        space& current = U[t % 2];
        space& next = U[(t + 1) % 2];

        for (std::size_t i = 0; i != nx; ++i)
            next[i] = PartOp(current[idx(i-1, nx)], current[i], current[idx(i+1, nx)]);
    }

    // Print the solution at time-step 'nt'.
    space const& solution = U[nt % 2];
    for (std::size_t i = 0; i != nx; ++i)
        std::cout << "U[" << i << "] = " << solution[i] << std::endl;

    return hpx::finalize();
}

int main(int argc, char* argv[])
{
    using namespace boost::program_options;

    options_description desc_commandline;
    desc_commandline.add_options()
        ("nx", value<boost::uint64_t>()->default_value(10),
         "Local x dimension (of each partition)")
        ("nt", value<boost::uint64_t>()->default_value(45),
         "Number of time steps")
        ("np", value<boost::uint64_t>()->default_value(10),
         "Number of partitions")
    ;

    // Initialize and run HPX
    return hpx::init(desc_commandline, argc, argv);
}
