//  Copyright (c) 2015 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_main.hpp>
#include <hpx/include/components.hpp>
#include <hpx/include/actions.hpp>
#include <hpx/util/lightweight_test.hpp>

///////////////////////////////////////////////////////////////////////////////
struct test_server : hpx::components::simple_component_base<test_server>
{
    hpx::id_type call() const { return hpx::find_here(); }

    HPX_DEFINE_COMPONENT_ACTION(test_server, call);
};

typedef hpx::components::simple_component<test_server> server_type;
HPX_REGISTER_MINIMAL_COMPONENT_FACTORY(server_type, test_server);

typedef test_server::call_action call_action;
HPX_REGISTER_ACTION(call_action);

struct test_client : hpx::components::client_base<test_client, test_server>
{
    typedef hpx::components::client_base<test_client, test_server> base_type;

    test_client(hpx::future<hpx::id_type> && id)
      : base_type(std::move(id))
    {}

    hpx::id_type  call()
    {
        return hpx::async<call_action>(this->get_gid()).get();
    }
};

///////////////////////////////////////////////////////////////////////////////
void test_create_single_instance()
{
    // make sure created objects live on locality they are supposed to be
    for (hpx::id_type const& loc: hpx::find_all_localities())
    {
        hpx::id_type id = hpx::new_<test_server>(loc).get();
        HPX_TEST(hpx::async<call_action>(id).get() == loc);
    }

    for (hpx::id_type const& loc: hpx::find_all_localities())
    {
        test_client t1 = hpx::new_<test_client>(loc);
        HPX_TEST(t1.call() == loc);
    }

    // make sure distribution policy is properly used
    hpx::id_type id = hpx::new_<test_server>(hpx::default_layout).get();
    HPX_TEST(hpx::async<call_action>(id).get() == hpx::find_here());

    test_client t2 = hpx::new_<test_client>(hpx::default_layout);
    HPX_TEST(t2.call() == hpx::find_here());

    for (hpx::id_type const& loc: hpx::find_all_localities())
    {
        hpx::id_type id = hpx::new_<test_server>(hpx::default_layout(loc)).get();
        HPX_TEST(hpx::async<call_action>(id).get() == loc);
    }

    for (hpx::id_type const& loc: hpx::find_all_localities())
    {
        test_client t3 = hpx::new_<test_client>(hpx::default_layout(loc));
        HPX_TEST(t3.call() == loc);
    }
}

///////////////////////////////////////////////////////////////////////////////
void test_create_many_instances()
{
    // make sure created objects live on locality they are supposed to be
    for (hpx::id_type const& loc: hpx::find_all_localities())
    {
        hpx::id_type id = hpx::new_<test_server[]>(loc).get();
        HPX_TEST(hpx::async<call_action>(id).get() == loc);
    }

    for (hpx::id_type const& loc: hpx::find_all_localities())
    {
        test_client t1 = hpx::new_<test_client>(loc);
        HPX_TEST(t1.call() == loc);
    }
}

int main()
{
    test_create_single_instance();
    test_create_many_instances();
    return 0;
}

