//  Copyright (c) 2016 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_init.hpp>
#include <hpx/hpx.hpp>
#include <hpx/include/parallel_generate.hpp>
#include <hpx/include/parallel_minmax.hpp>
#include <hpx/include/partitioned_vector.hpp>
#include <hpx/include/iostreams.hpp>
#include <hpx/util/high_resolution_clock.hpp>

#include <boost/program_options.hpp>
#include <boost/random.hpp>

#include <iostream>

///////////////////////////////////////////////////////////////////////////////
// Define the vector types to be used.
HPX_REGISTER_PARTITIONED_VECTOR(int);

///////////////////////////////////////////////////////////////////////////////
struct random_fill
{
    random_fill()
      : gen(std::rand()),
        dist(0, RAND_MAX)
    {}

    int operator()()
    {
        return dist(gen);
    }

    boost::random::mt19937 gen;
    boost::random::uniform_int_distribution<> dist;

    template <typename Archive>
    void serialize(Archive& ar, unsigned)
    {}
};

///////////////////////////////////////////////////////////////////////////////
double run_minmax_element_benchmark()
{
    return 0.0;
}

///////////////////////////////////////////////////////////////////////////////
int hpx_main(boost::program_options::variables_map& vm)
{
    if (hpx::get_locality_id() == 0)
    {
        // pull values from cmd
        std::size_t size = vm["vector_size"].as<std::size_t>();
        bool csvoutput = vm.count("csv_output") != 0;
        int test_count = vm["test_count"].as<int>();

        // create as many partitions as we have localities
        std::vector<hpx::id_type> localities = hpx::find_all_localities();
        hpx::partitioned_vector<int> v(size, hpx::container_layout(localities));

        // initialize data
        hpx::parallel::generate(
            hpx::parallel::par, v.begin(), v.end(), random_fill());

        // invoke minmax
        auto iters = hpx::parallel::minmax_element(
            hpx::parallel::par, v.begin(), v.end());

        return hpx::finalize();
    }

    return 0;
}

int main(int argc, char* argv[])
{
    std::srand((unsigned int)std::time(0));

    // initialize program
    std::vector<std::string> cfg;
    cfg.push_back("hpx.os_threads=" +
        boost::lexical_cast<std::string>(hpx::threads::hardware_concurrency()));
    cfg.push_back("hpx.run_hpx_main=1");

    boost::program_options::options_description cmdline(
        "usage: " HPX_APPLICATION_STRING " [options]");

    cmdline.add_options()
        ( "vector_size",
            boost::program_options::value<std::size_t>()->default_value(1000),
            "size of vector (default: 1000)")
        ("test_count",
            boost::program_options::value<int>()->default_value(100),
            "number of tests to be averaged (default: 100)")
        ("csv_output",
            "print results in csv format")
        ("seed,s", boost::program_options::value<unsigned int>(),
            "the random number generator seed to use for this run")
        ;

    return hpx::init(cmdline, argc, argv, cfg);
}

