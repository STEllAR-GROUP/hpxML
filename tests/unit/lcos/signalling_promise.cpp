//  Copyright (c) 2007-2012 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_init.hpp>
#include <hpx/include/plain_actions.hpp>
#include <hpx/include/lcos.hpp>
#include <hpx/util/lightweight_test.hpp>

#include <boost/bind.hpp>
#include <boost/ref.hpp>

using boost::program_options::variables_map;
using boost::program_options::options_description;
using boost::program_options::value;

///////////////////////////////////////////////////////////////////////////////
int test()
{
    return 42;
}
HPX_PLAIN_ACTION(test, test_action);

///////////////////////////////////////////////////////////////////////////////
int test_error()
{
    HPX_THROW_EXCEPTION(hpx::not_implemented, "test_error",
        "throwing test exception");
    return 42;
}
HPX_PLAIN_ACTION(test_error, test_error_action);

///////////////////////////////////////////////////////////////////////////////
void future_callback(
    bool& data_cb_called
  , bool& error_cb_called
  , hpx::lcos::future<int> f
    )
{
    if (f.has_value()) {
        data_cb_called = true;
        HPX_TEST_EQ(f.get(), 42);
    }
    else {
        error_cb_called = true;
        HPX_TEST(f.has_exception());

        std::string error_msg("throwing test exception: HPX(not_implemented)");
        std::string what_msg;

        try {
            f.get();          // should rethrow
            HPX_TEST(false);
        }
        catch (std::exception const& e) {
            what_msg = e.what();
            HPX_TEST(true);
        }

        HPX_TEST_EQ(what_msg, error_msg);
    }
}

///////////////////////////////////////////////////////////////////////////////
int hpx_main(variables_map& vm)
{
    using hpx::lcos::future;
    using hpx::lcos::async_callback;

    {
        bool data_cb_called = false;
        bool error_cb_called = false;

        future<int> p = async_callback<test_action>(
            boost::bind(future_callback, boost::ref(data_cb_called)
              , boost::ref(error_cb_called), _1),
            hpx::find_here()
        );

        HPX_TEST_EQ(p.get(), 42);
        HPX_TEST(data_cb_called);
        HPX_TEST(!error_cb_called);
    }

    {
        bool data_cb_called = false;
        bool error_cb_called = false;

        future<int> p = async_callback<test_error_action>(
            boost::bind(future_callback, boost::ref(data_cb_called)
              , boost::ref(error_cb_called), _1),
            hpx::find_here()
        );

        std::string error_msg = "throwing test exception: HPX(not_implemented)";
        std::string what_msg;
        bool exception_caught = false;

        try {
            p.get();      // throws
        }
        catch (std::exception const& e) {
            exception_caught = true;
            what_msg = e.what();
        }

        HPX_TEST_EQ(what_msg, error_msg);
        HPX_TEST(exception_caught);
        HPX_TEST(!data_cb_called);
        HPX_TEST(error_cb_called);
    }

    hpx::finalize();
    return hpx::util::report_errors();
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    // Configure application-specific options
    options_description desc_commandline(
        "Usage: " HPX_APPLICATION_STRING " [options]");

    // Initialize and run HPX
    return hpx::init(desc_commandline, argc, argv);
}

