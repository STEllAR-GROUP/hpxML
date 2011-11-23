////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(HPX_28443929_CB68_43ED_B134_F60602A344DD)
#define HPX_28443929_CB68_43ED_B134_F60602A344DD

#include <hpx/hpx_fwd.hpp>
#include <hpx/lcos/eager_future.hpp>
#include <hpx/runtime/agas/server/symbol_namespace.hpp>

namespace hpx { namespace agas { namespace stubs
{

struct symbol_namespace
{
    typedef server::symbol_namespace server_type;

    typedef server_type::iterate_names_function_type
        iterate_names_function_type;

    template <
        typename Result
    >
    static lcos::promise<Result, response> service_async(
        naming::id_type const& gid
      , request const& req
      , threads::thread_priority priority = threads::thread_priority_default
        )
    {
        typedef server_type::service_action action_type;
        return lcos::eager_future<action_type, Result>(gid, priority, req);
    }

    static response service(
        naming::id_type const& gid
      , request const& req
      , threads::thread_priority priority = threads::thread_priority_default
      , error_code& ec = throws
        )
    {
        return service_async<response>(gid, req, priority).get(ec);
    }
};

}}}

#endif // HPX_28443929_CB68_43ED_B134_F60602A344DD

