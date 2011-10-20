//  Copyright (c)      2011 Bryce Lelbach
//  Copyright (c) 2007-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <boost/bind.hpp>

#include <hpx/hpx.hpp>
#include <hpx/hpx_init.hpp>
#include <hpx/runtime/actions/plain_action.hpp>
#include <hpx/runtime/components/plain_component_factory.hpp>
#include <hpx/lcos/future_wait.hpp>
#include <hpx/lcos/eager_future.hpp>
#include <hpx/lcos/object_semaphore.hpp>

typedef hpx::lcos::object_semaphore<int> object_semaphore_type;

///////////////////////////////////////////////////////////////////////////////
void worker(hpx::naming::id_type const& gid)
{
    object_semaphore_type os(gid);

    try
    {
        int value = os.get_sync(); // retrieve one value, might throw
        std::cout << value << std::endl;
    }

    catch (hpx::exception const& e)
    {
        std::cout << e.what() << std::endl;
    }
}

typedef hpx::actions::plain_action1<hpx::naming::id_type const&, worker>
    worker_action;

HPX_REGISTER_PLAIN_ACTION(worker_action);

typedef hpx::lcos::eager_future<worker_action> worker_future;

///////////////////////////////////////////////////////////////////////////////
void breaker(hpx::naming::id_type const& gid)
{
    object_semaphore_type os(gid);
    os.abort_pending_sync();
}

///////////////////////////////////////////////////////////////////////////////
int hpx_main(boost::program_options::variables_map &vm)
{
    {
        // create a new object semaphore
        object_semaphore_type os
            (object_semaphore_type::create_sync(hpx::find_here()));

        // create some threads waiting to pull elements from the queue
        for (std::size_t i = 0; i < 5; ++i)
            hpx::applier::register_work(boost::bind(&worker, os.get_gid()));

        // add some values to the queue
        for (std::size_t i = 0; i < 5; ++i)
            os.signal_sync(i);

        std::vector<hpx::lcos::promise<void> > barrier;

        // create some threads waiting to pull elements from the queue
        for (std::size_t i = 0; i < 5; ++i)
            barrier.push_back(worker_future(hpx::find_here(), os.get_gid()));

        // abort all pending workers
        hpx::applier::register_work(boost::bind(&breaker, os.get_gid()));

        hpx::lcos::wait(barrier);
    }

    hpx::finalize();
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    // Configure application-specific options
    boost::program_options::options_description
       desc_commandline("Usage: " HPX_APPLICATION_STRING " [options]");

    // Initialize and run HPX
    return hpx::init(desc_commandline, argc, argv);
}

