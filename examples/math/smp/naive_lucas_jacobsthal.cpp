////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

// Naive SMP version implemented with eager_futures.

#include <iostream>

#include <boost/cstdint.hpp>
#include <boost/format.hpp>

#include <hpx/hpx.hpp>
#include <hpx/hpx_init.hpp>
#include <hpx/runtime/actions/plain_action.hpp>
#include <hpx/runtime/components/plain_component_factory.hpp>
#include <hpx/util/high_resolution_timer.hpp>
#include <hpx/lcos/eager_future.hpp>

using boost::program_options::variables_map;
using boost::program_options::options_description;
using boost::program_options::value;

using hpx::naming::id_type;

using hpx::applier::get_applier;

using hpx::actions::plain_result_action2;

using hpx::lcos::eager_future;

using hpx::util::high_resolution_timer;

using hpx::init;
using hpx::finalize;

///////////////////////////////////////////////////////////////////////////////
boost::uint64_t lucas_jacobsthal(
    id_type const& prefix 
  , boost::uint64_t m
);

typedef plain_result_action2<
    // result type
    boost::uint64_t
    // arguments
  , id_type const&  
  , boost::uint64_t
    // function
  , lucas_jacobsthal
> lucas_jacobsthal_action;

HPX_REGISTER_PLAIN_ACTION(lucas_jacobsthal_action);

typedef eager_future<lucas_jacobsthal_action> lucas_jacobsthal_future;

///////////////////////////////////////////////////////////////////////////////
boost::uint64_t lucas_jacobsthal(
    id_type const& prefix
  , boost::uint64_t n
) {
    if (0 == n)
        return 2;

    else if (1 == n)
        return 1;

    else
    {
        lucas_jacobsthal_future n1(prefix, prefix, n - 1);
        lucas_jacobsthal_future n2(prefix, prefix, n - 2);
        return n1.get() + 2 * n2.get(); 
    }
}

///////////////////////////////////////////////////////////////////////////////
int hpx_main(variables_map& vm)
{
    {
        boost::uint64_t n = vm["n-value"].as<boost::uint64_t>();

        const id_type prefix = get_applier().get_runtime_support_gid();

        high_resolution_timer t;

        lucas_jacobsthal_future f(prefix, prefix, n);

        boost::uint64_t r = f.get();

        double elapsed = t.elapsed();

        std::cout
            << ( boost::format("lucas_jacobsthal(%1%) == %2%\n"
                               "elapsed time == %3%\n")
               % n % r % elapsed);
    }

    finalize();

    return 0;
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    // Configure application-specific options
    options_description
       desc_commandline("Usage: " HPX_APPLICATION_STRING " [options]");

    desc_commandline.add_options()
        ( "n-value"
        , value<boost::uint64_t>()->default_value(10)
        , "n value for the Lucas-Jacobsthal function") 
        ;

    // Initialize and run HPX
    return init(desc_commandline, argc, argv);
}

