//  Copyright (c) 2007-2015 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_init.hpp>
#include <hpx/hpx.hpp>
#include <hpx/include/parallel_executors.hpp>
#include <hpx/util/lightweight_test.hpp>

#include <algorithm>
#include <cstdlib>
#include <string>
#include <vector>

#include <boost/chrono.hpp>

using namespace boost::chrono;

///////////////////////////////////////////////////////////////////////////////
hpx::thread::id test() { return hpx::this_thread::get_id(); }

template <typename Executor>
void test_timed_sync(Executor& exec)
{
    typedef hpx::parallel::timed_executor_traits<Executor> traits;

    HPX_TEST(
        traits::execute_after(exec, milliseconds(1), &test) !=
            hpx::this_thread::get_id());

    HPX_TEST(
        traits::execute_at(exec, steady_clock::now()+milliseconds(1), &test) !=
            hpx::this_thread::get_id());
}

template <typename Executor>
void test_timed_async(Executor& exec)
{
    typedef hpx::parallel::timed_executor_traits<Executor> traits;

    HPX_TEST(
        traits::async_execute_after(
            exec, milliseconds(1), &test
        ).get() != hpx::this_thread::get_id());

    HPX_TEST(
        traits::async_execute_at(
            exec, steady_clock::now()+milliseconds(1), &test
        ).get() != hpx::this_thread::get_id());
}

template <typename Executor>
void test_timed_apply(Executor& exec)
{
    typedef hpx::parallel::timed_executor_traits<Executor> traits;

    traits::apply_execute_after(exec, milliseconds(1), &test);
    traits::apply_execute_at(exec, steady_clock::now()+milliseconds(1), &test);
}

///////////////////////////////////////////////////////////////////////////////
template <typename Executor>
void test_timed_thread_pool_executor(Executor& exec)
{
    test_timed_sync(exec);
    test_timed_async(exec);
    test_timed_apply(exec);
}

int hpx_main(int argc, char* argv[])
{
    std::size_t num_threads = hpx::get_os_thread_count();

#if defined(HPX_HAVE_STATIC_SCHEDULER)
    {
        hpx::parallel::static_queue_executor exec(num_threads);
        test_timed_thread_pool_executor(exec);
    }
#endif

    {
        hpx::parallel::local_priority_queue_executor exec(num_threads);
        test_timed_thread_pool_executor(exec);
    }

#if defined(HPX_HAVE_STATIC_PRIORITY_SCHEDULER)
    {
        hpx::parallel::static_priority_queue_executor exec(num_threads);
        test_timed_thread_pool_executor(exec);
    }
#endif

    return hpx::finalize();
}

int main(int argc, char* argv[])
{
    // By default this test should run on all available cores
    std::vector<std::string> cfg;
    cfg.push_back("hpx.os_threads=" +
        std::to_string(hpx::threads::hardware_concurrency()));

    // Initialize and run HPX
    HPX_TEST_EQ_MSG(hpx::init(argc, argv, cfg), 0,
        "HPX main exited with non-zero status");

    return hpx::util::report_errors();
}
