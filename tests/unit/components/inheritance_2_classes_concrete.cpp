////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2012 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
///////////////////////////////////////////////////////////////////////////////

#include <hpx/hpx_main.hpp>
#include <hpx/include/components.hpp>
#include <hpx/include/actions.hpp>
#include <hpx/include/iostreams.hpp>
#include <hpx/util/lightweight_test.hpp>

bool a_ctor = false;
bool a_dtor = false;
bool b_ctor = false;
bool b_dtor = false;

///////////////////////////////////////////////////////////////////////////////
// Concrete
struct A : hpx::components::managed_component_base<A>
{
    A() { a_ctor = true; }
    virtual ~A() { a_dtor = true; }

    virtual std::string test0() const { return "A"; }
    std::string test0_nonvirt() const { return test0(); }
    HPX_DEFINE_COMPONENT_ACTION(A, test0_nonvirt, test0_action);
};

typedef hpx::components::managed_component<A> serverA_type;
HPX_REGISTER_MINIMAL_COMPONENT_FACTORY(serverA_type, A);

typedef A::test0_action test0_action;
HPX_REGISTER_ACTION_DECLARATION(test0_action);
HPX_REGISTER_ACTION(test0_action);

///////////////////////////////////////////////////////////////////////////////
// Concrete
struct B : A, hpx::components::managed_component_base<B>
{
    typedef hpx::components::managed_component_base<B>::wrapping_type
        wrapping_type;
    typedef hpx::components::managed_component_base<B>::wrapped_type
        wrapped_type;
    using hpx::components::managed_component_base<B>::decorate_action;
    using hpx::components::managed_component_base<B>::schedule_thread;
    using hpx::components::managed_component_base<B>::set_back_ptr;
    using hpx::components::managed_component_base<B>::finalize;
    using hpx::components::managed_component_base<B>::is_target_valid;

    typedef B type_holder;
    typedef A base_type_holder;

    B() { b_ctor = true; }
    ~B() { b_dtor = true; }

    std::string test0() const { return "B"; }

    std::string test1() const { return "B"; }
    HPX_DEFINE_COMPONENT_ACTION(B, test1, test1_action);
};

typedef hpx::components::managed_component<B> serverB_type;
HPX_REGISTER_DERIVED_COMPONENT_FACTORY(serverB_type, B, "A");

typedef B::test1_action test1_action;
HPX_REGISTER_ACTION_DECLARATION(test1_action);
HPX_REGISTER_ACTION(test1_action);

///////////////////////////////////////////////////////////////////////////////
struct clientA : hpx::components::client_base<clientA, A>
{
    typedef hpx::components::client_base<clientA, A> base_type;

    clientA(hpx::shared_future<hpx::id_type> const& gid)
      : base_type(gid)
    {}

    std::string test0()
    {
        test0_action act;
        return act(base_type::get_gid());
    }
};

///////////////////////////////////////////////////////////////////////////////
struct clientB : hpx::components::client_base<clientB, B>
{
    typedef hpx::components::client_base<clientB, B> base_type;

    clientB(hpx::shared_future<hpx::id_type> const& gid)
      : base_type(gid)
    {}

    std::string test0()
    {
        test0_action act;
        return act(base_type::get_gid());
    }

    std::string test1()
    {
        test1_action act;
        return act(base_type::get_gid());
    }
};

///////////////////////////////////////////////////////////////////////////////
void reset_globals()
{
    a_ctor = false;
    a_dtor = false;
    b_ctor = false;
    b_dtor = false;
}

int main()
{
    ///////////////////////////////////////////////////////////////////////////

    { // Client to A, instance of A
        clientA obj(hpx::components::new_<A>(hpx::find_here()));
    
        HPX_TEST_EQ(obj.test0(), "A");
    }
    
    HPX_TEST(a_ctor); HPX_TEST(a_dtor);
    HPX_TEST(!b_ctor); HPX_TEST(!b_dtor);

    reset_globals();

    ///////////////////////////////////////////////////////////////////////////

    { // Client to A, instance of B
        clientA obj(hpx::components::new_<B>(hpx::find_here()));
    
        HPX_TEST_EQ(obj.test0(), "B");
    }
    
    HPX_TEST(a_ctor); HPX_TEST(a_dtor);
    HPX_TEST(b_ctor); HPX_TEST(b_dtor);

    reset_globals();

    ///////////////////////////////////////////////////////////////////////////

    { // Client to B, instance of B
        clientB obj(hpx::components::new_<B>(hpx::find_here()));
    
        HPX_TEST_EQ(obj.test0(), "B");
        HPX_TEST_EQ(obj.test1(), "B");
    }
    
    HPX_TEST(a_ctor); HPX_TEST(a_dtor);
    HPX_TEST(b_ctor); HPX_TEST(b_dtor);

    reset_globals();

    return 0;
}

