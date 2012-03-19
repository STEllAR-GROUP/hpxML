//[hello_world_hpp_getting_started
#if !defined(HELLO_WORLD_HPP)
#define HELLO_WORLD_HPP 

#include <hpx/include/actions.hpp>
#include <hpx/include/lcos.hpp>
#include <hpx/include/components.hpp>
#include <hpx/include/serialization.hpp>

namespace examples { namespace server
{

struct HPX_COMPONENT_EXPORT hello_world
  : hpx::components::managed_component_base<hello_world>
{
    void invoke();

    typedef hpx::actions::action0<
        hello_world, 0, &hello_world::invoke
    > invoke_action;
};

}

namespace stubs
{

struct hello_world : hpx::components::stub_base<server::hello_world>
{
    static void invoke(hpx::naming::id_type const& gid)
    {
        hpx::lcos::async<server::hello_world::invoke_action>(gid).get();
    }
};

}

struct hello_world
  : hpx::components::client_base<hello_world, stubs::hello_world>
{
    typedef hpx::components::client_base<hello_world, stubs::hello_world>
        base_type;

    void invoke()
    {
        this->base_type::invoke(this->gid_);
    }
};

}

HPX_REGISTER_ACTION_DECLARATION_EX(
    examples::server::hello_world::invoke_action, hello_world_invoke_action);

#endif // HELLO_WORLD_HPP 
//]

