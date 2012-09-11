// Copyright (C) 2012 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_main.hpp>
#include <hpx/include/actions.hpp>
#include <hpx/util/lightweight_test.hpp>

///////////////////////////////////////////////////////////////////////////////
void test_default_stacksize()
{
    HPX_TEST(hpx::threads::get_self_ptr()); 
    // verify that sufficient stack has been allocated
    HPX_TEST_EQ(hpx::threads::get_ctx_ptr()->get_stacksize(), 
        hpx::get_runtime().get_config().get_default_stack_size());

    // allocate HPX_DEFAULT_STACK_SIZE - 0x800 memory on the stack 
    char array[HPX_DEFAULT_STACK_SIZE-0x800];

    // do something to that array
    std::memset(array, '\0', sizeof(array));
}
HPX_PLAIN_ACTION(test_default_stacksize, test_default_stacksize_action)

///////////////////////////////////////////////////////////////////////////////
void test_small_stacksize()
{
    HPX_TEST(hpx::threads::get_self_ptr()); 
    // verify that sufficient stack has been allocated
    HPX_TEST_EQ(hpx::threads::get_ctx_ptr()->get_stacksize(),
        hpx::get_runtime().get_config().get_stack_size(
            hpx::threads::thread_stacksize_small));

    // allocate HPX_SMALL_STACK_SIZE - 0x800 memory on the stack 
    char array[HPX_SMALL_STACK_SIZE-0x800];

    // do something to that array
    std::memset(array, '\0', sizeof(array));
}
HPX_PLAIN_ACTION(test_small_stacksize, test_small_stacksize_action)
HPX_ACTION_USES_SMALL_STACK(test_small_stacksize_action)

///////////////////////////////////////////////////////////////////////////////
void test_medium_stacksize()
{
    HPX_TEST(hpx::threads::get_self_ptr()); 
    // verify that sufficient stack has been allocated
    HPX_TEST_EQ(hpx::threads::get_ctx_ptr()->get_stacksize(), 
        hpx::get_runtime().get_config().get_stack_size(
            hpx::threads::thread_stacksize_medium));

    // allocate HPX_MEDIUM_STACK_SIZE - 0x800 memory on the stack 
    char array[HPX_MEDIUM_STACK_SIZE-0x800];

    // do something to that array
    std::memset(array, '\0', sizeof(array));
}
HPX_PLAIN_ACTION(test_medium_stacksize, test_medium_stacksize_action)
HPX_ACTION_USES_MEDIUM_STACK(test_medium_stacksize_action)

///////////////////////////////////////////////////////////////////////////////
void test_large_stacksize()
{
    HPX_TEST(hpx::threads::get_self_ptr()); 
    // verify that sufficient stack has been allocated
    HPX_TEST(hpx::threads::get_ctx_ptr()->get_stacksize() >= 
        hpx::get_runtime().get_config().get_stack_size(
            hpx::threads::thread_stacksize_large));

    // allocate HPX_LARGE_STACK_SIZE - 0x800 memory on the stack 
    char array[HPX_LARGE_STACK_SIZE-0x800];

    // do something to that array
    std::memset(array, '\0', sizeof(array));
}
HPX_PLAIN_ACTION(test_large_stacksize, test_large_stacksize_action)
HPX_ACTION_USES_LARGE_STACK(test_large_stacksize_action)

///////////////////////////////////////////////////////////////////////////////
int main()
{
    /*
    {
        test_default_stacksize_action test_action;
        test_action(hpx::find_here());
    }
    */

    {
        test_small_stacksize_action test_action;
        test_action(hpx::find_here());
    }

    {
        test_medium_stacksize_action test_action;
        test_action(hpx::find_here());
    }

    {
        test_large_stacksize_action test_action;
        test_action(hpx::find_here());
    }

    return hpx::util::report_errors();
}

