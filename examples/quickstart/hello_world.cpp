///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2007-2012 Hartmut Kaiser
//  Copyright (c) 2011 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
///////////////////////////////////////////////////////////////////////////////

#include <hpx/hpx_init.hpp>
#include <hpx/include/lcos.hpp>
#include <hpx/include/actions.hpp>
#include <hpx/include/components.hpp>
#include <hpx/include/iostreams.hpp>

#include <vector>
#include <list>
#include <set>

#include <boost/ref.hpp>
#include <boost/foreach.hpp>
#include <boost/format.hpp>

///////////////////////////////////////////////////////////////////////////////
// The purpose of this example is to execute a PX-thread printing "Hello world"
// once on each OS-thread on each of the connected localities.
//
// The function hello_world_foreman_action is executed once on each locality.
// It schedules a PX-thread (encapsulating hello_world_worker) once for each
// OS-thread on that locality. The code make sure that the PX-thread gets
// really executed by the requested OS-thread. While the PX-thread is scheduled
// to run on a particular OS-thread, we may have to retry as the PX-thread may
// end up being 'stolen' by another OS-thread.

///////////////////////////////////////////////////////////////////////////////
//[hello_world_worker
std::size_t hello_world_worker(std::size_t desired)
{
    // Returns the OS-thread number of the worker that is running this
    // PX-thread.
    std::size_t current = hpx::get_worker_thread_num();
    if (current == desired)
    {
        // The PX-thread has been run on the desired OS-thread.
        char const* msg = "hello world from OS-thread %1% on locality %2%\n";

        hpx::cout << (boost::format(msg) % desired % hpx::get_locality_id())
                  << hpx::flush;

        return desired;
    }

    // This PX-thread has been run by the wrong OS-thread, make the foreman
    // try again by rescheduling it.
    return std::size_t(-1);
}

// Define the boilerplate code necessary for the function 'hello_world_worker'
// to be invoked as an HPX action (by a HPX future). This macro defines the
// type 'hello_world_worker_action'.
HPX_PLAIN_ACTION(hello_world_worker, hello_world_worker_action);
//]

///////////////////////////////////////////////////////////////////////////////
//[hello_world_foreman
void hello_world_foreman()
{
    // Get the number of worker OS-threads in use by this locality.
    std::size_t const os_threads = hpx::get_os_thread_count();

    // Find the global name of the current locality.
    hpx::naming::id_type const here = hpx::find_here();

    // Populate a set with the OS-thread numbers of all OS-threads on this
    // locality. When the hello world message has been printed on a particular
    // OS-thread, we will remove it from the set.
    std::set<std::size_t> attendance;
    for (std::size_t os_thread = 0; os_thread < os_threads; ++os_thread)
        attendance.insert(os_thread);

    // As long as there are still elements in the set, we must keep scheduling
    // PX-threads. Because HPX features work-stealing task schedulers, we have
    // no way of enforcing which worker OS-thread will actually execute
    // each PX-thread.
    while (!attendance.empty())
    {
        // Each iteration, we create a task for each element in the set of
        // OS-threads that have not said "Hello world". Each of these tasks
        // is encapsulated in a future.
        std::vector<hpx::lcos::future<std::size_t> > futures;
        futures.reserve(attendance.size());

        BOOST_FOREACH(std::size_t worker, attendance)
        {
            // Asynchronously start a new task. The task is encapsulated in a
            // future, which we can query to determine if the task has
            // completed.
            typedef hello_world_worker_action action_type;
            futures.push_back(hpx::async<action_type>(here, worker));
        }

        // Wait for all of the futures to finish. The callback version of the
        // hpx::lcos::wait function takes two arguments: a vector of futures,
        // and a binary callback.  The callback takes two arguments; the first
        // is the index of the future in the vector, and the second is the
        // return value of the future. hpx::lcos::wait doesn't return until
        // all the futures in the vector have returned.
        hpx::lcos::wait(futures,
            [&](std::size_t, std::size_t t) {
                if (std::size_t(-1) != t)
                    attendance.erase(t);
            });
    }
}
//]

//[hello_world_action_wrapper
// Define the boilerplate code necessary for the function 'hello_world_foreman'
// to be invoked as an HPX action.
HPX_PLAIN_ACTION(hello_world_foreman, hello_world_foreman_action);
//]

///////////////////////////////////////////////////////////////////////////////
//[hello_world_hpx_main
//`Here is hpx_main:
int hpx_main(boost::program_options::variables_map& vm)
{
    {
        // Get a list of all available localities.
        std::vector<hpx::naming::id_type> localities =
            hpx::find_all_localities();

        // Reserve storage space for futures, one for each locality.
        std::vector<hpx::lcos::future<void> > futures;
        futures.reserve(localities.size());

        BOOST_FOREACH(hpx::naming::id_type const& node, localities)
        {
            // Asynchronously start a new task. The task is encapsulated in a
            // future, which we can query to determine if the task has
            // completed.
            typedef hello_world_foreman_action action_type;
            futures.push_back(hpx::async<action_type>(node));
        }

        // The non-callback version of hpx::lcos::wait takes a single parameter,
        // a future of vectors to wait on. hpx::lcos::wait only returns when
        // all of the futures have finished.
        hpx::lcos::wait(futures);
    }

    // Initiate shutdown of the runtime system.
    return hpx::finalize();
}
//]

///////////////////////////////////////////////////////////////////////////////
//[hello_world_main
int main(int argc, char* argv[])
{
    // Configure application-specific options.
    boost::program_options::options_description
       desc_commandline("usage: " HPX_APPLICATION_STRING " [options]");

    // Initialize and run HPX.
    return hpx::init(desc_commandline, argc, argv);
}
//` In HPX `main` is used to initialize the runtime system and pass the command
//` line arguments to the program. If you wish to add command line options to
//` your program you would add them here using the instance of the Boost
//` class `options_description`, and invoking the public member function
//` `.add_options()` (see __boost_doc__ or the __fibonacci_example__
//` for more details). `hpx::init()` calls `hpx_main` after setting up
//` HPX, which is where the logic of our program is encoded.
//]

