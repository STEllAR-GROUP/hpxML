////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(HPX_5D993B14_5B65_4231_A84E_90AD1807EB8F)
#define HPX_5D993B14_5B65_4231_A84E_90AD1807EB8F

#include <hpx/hpx_fwd.hpp>
#include <hpx/lcos/eager_future.hpp>
#include <hpx/runtime/agas/server/primary_namespace.hpp>

namespace hpx { namespace agas { namespace stubs
{

struct primary_namespace 
{
    typedef server::primary_namespace server_type; 

    static lcos::promise<response> service_async(
        naming::id_type const& gid
      , request const& req
        )
    {
        typedef server_type::service_action action_type;
        return lcos::eager_future<action_type, response>(gid, req);
    }

    static response service(
        naming::id_type const& gid
      , request const& req 
      , error_code& ec = throws
        )
    {
        return service_async(gid, req).get(ec);
    } 
};            

}}}

#endif // HPX_5D993B14_5B65_4231_A84E_90AD1807EB8F

