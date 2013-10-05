//  Copyright (c) 2011-2012 Bryce Adelstein-Lelbach
//  Copyright (c) 2007-2013 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "worker.hpp"

#include <hpx/hpx_init.hpp>
#include <hpx/util/thread_aware_timer.hpp>
#include <hpx/include/iostreams.hpp>

#include <stdexcept>

#include <boost/format.hpp>
#include <boost/cstdint.hpp>

using boost::program_options::variables_map;
using boost::program_options::options_description;
using boost::program_options::value;

using hpx::init;
using hpx::finalize;
using hpx::get_os_thread_count;

using hpx::applier::register_work;
using hpx::applier::register_non_suspendable_work;

using hpx::this_thread::suspend;
using hpx::threads::get_thread_count;

using hpx::util::thread_aware_timer;

using hpx::cout;
using hpx::flush;

///////////////////////////////////////////////////////////////////////////////
// Command-line variables.
boost::uint64_t tasks = 500000;
boost::uint64_t delay = 0;
boost::uint64_t feeders = 1;

bool header = true;

///////////////////////////////////////////////////////////////////////////////
void print_results(
    boost::uint64_t cores
  , double walltime
    )
{
    if (header)
        cout << "OS-threads,Tasks,Delay (iterations),"
                "Total Walltime (seconds),Walltime per Task (seconds)\n"
             << flush;

    std::string const cores_str = boost::str(boost::format("%lu,") % cores);
    std::string const tasks_str = boost::str(boost::format("%lu,") % tasks);
    std::string const delay_str = boost::str(boost::format("%lu,") % delay);

    cout << ( boost::format("%-21s %-21s %-21s %10.12s, %10.12s\n")
            % cores_str % tasks_str % delay_str
            % walltime % (walltime / tasks)) << flush;
}

///////////////////////////////////////////////////////////////////////////////
void invoke_worker_helper(hpx::threads::thread_state_ex_enum)
{
    invoke_worker(delay);
}

///////////////////////////////////////////////////////////////////////////////
void create_tasks(boost::uint64_t tasks)
{
    for (boost::uint64_t i = 0; i != tasks; ++i)
        register_work(&invoke_worker_helper);
}

void create_stackless_tasks(boost::uint64_t tasks)
{
    for (boost::uint64_t i = 0; i != tasks; ++i)
        register_non_suspendable_work(&invoke_worker_helper);
}

///////////////////////////////////////////////////////////////////////////////
int hpx_main(
    variables_map& vm
    )
{
    if (vm.count("no-header"))
        header = false;

    {
        if (0 == tasks)
            throw std::invalid_argument("count of 0 tasks specified\n");

        if (0 == feeders || feeders > get_os_thread_count())
            throw std::invalid_argument("number of feeders must be between 1 and OS-thread-count\n");

        // Start the clock.
        thread_aware_timer t;

        if (0 == vm.count("no-stack")) {
            for (boost::uint64_t i = 0; i != feeders; ++i)
                register_work(HPX_STD_BIND(&create_tasks, tasks/feeders));
        }
        else {
            for (boost::uint64_t i = 0; i != feeders; ++i)
                register_work(HPX_STD_BIND(&create_stackless_tasks, tasks/feeders));
        }

        // Reschedule hpx_main until all other hpx-threads have finished. We
        // should be resumed after most of the null HPX-threads have been
        // executed. If we haven't, we just reschedule ourselves again.
        do {
            suspend();
        } while (get_thread_count(hpx::threads::thread_priority_normal) > 1);

        print_results(get_os_thread_count(), t.elapsed());
    }

    return finalize();
}

///////////////////////////////////////////////////////////////////////////////
int main(
    int argc
  , char* argv[]
    )
{
    // Configure application-specific options.
    options_description cmdline("usage: " HPX_APPLICATION_STRING " [options]");

    cmdline.add_options()
        ( "tasks"
        , value<boost::uint64_t>(&tasks)->default_value(500000)
        , "number of tasks to invoke")

        ( "feeders"
        , value<boost::uint64_t>(&feeders)->default_value(1)
        , "number of feeders (threads creating new tasks)")

        ( "no-stack"
        , "use stackless threads")

        ( "delay"
        , value<boost::uint64_t>(&delay)->default_value(0)
        , "number of iterations in the delay loop")

        ( "no-header"
        , "do not print out the csv header row")
        ;

    // Initialize and run HPX.
    return init(cmdline, argc, argv);
}

