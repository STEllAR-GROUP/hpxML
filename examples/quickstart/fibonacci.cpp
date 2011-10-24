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
using hpx::actions::plain_result_action1;
using hpx::lcos::eager_future;
using hpx::util::high_resolution_timer;
using hpx::init;
using hpx::finalize;
using hpx::find_here;

///////////////////////////////////////////////////////////////////////////////
// forward declaration of the Fibonacci function
boost::uint64_t fibonacci(boost::uint64_t m);

// Any global function needs to be wrapped into a plain_action if it should be
// invoked as a HPX-thread.
typedef plain_result_action1<
    boost::uint64_t,          // result type
    boost::uint64_t,          // argument
    fibonacci                 // function
> fibonacci_action;

// this is to generate the required boilerplate we need for the remote
// invocation to work
HPX_REGISTER_PLAIN_ACTION(fibonacci_action);

///////////////////////////////////////////////////////////////////////////////
// An eager_future is a HPX construct exposing the semantics of a Future
// object. It starts executing the bound action immediately (eagerly).
typedef eager_future<fibonacci_action> fibonacci_future;

///////////////////////////////////////////////////////////////////////////////
boost::uint64_t fibonacci(boost::uint64_t n)
{
    if (n < 2)
        return n;

    // We restrict ourselves to execute the Fibonacci function locally.
    id_type const prefix = find_here();

    // Invoking the Fibonacci algorithm twice is inefficient.
    // However, we intentionally demonstrate it this way to create some
    // heavy workload.
    fibonacci_future n1(prefix, n - 1);
    fibonacci_future n2(prefix, n - 2);

    return n1.get() + n2.get();   // wait for the Futures to return their values
}

///////////////////////////////////////////////////////////////////////////////
int hpx_main(variables_map& vm)
{
    // extract command line argument, i.e. fib(N)
    boost::uint64_t n = vm["n-value"].as<boost::uint64_t>();

    {
        // Keep track of the time required to execute.
        high_resolution_timer t;

        // Create a Future for the whole calculation and wait for it.
        fibonacci_future f(find_here(), n);    // execute locally
        boost::uint64_t r = f.get();

        char const* fmt = "fibonacci(%1%) == %2%\nelapsed time: %3% [s]\n";
        std::cout << (boost::format(fmt) % n % r % t.elapsed());

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
        ( "n-value" , value<boost::uint64_t>()->default_value(10),
            "n value for the Fibonacci function")
        ;

    // Initialize and run HPX
    return init(desc_commandline, argc, argv);
}

