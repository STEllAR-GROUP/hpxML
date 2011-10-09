////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <hpx/runtime/naming/resolver_client.hpp>
#include <hpx/runtime/actions/continuation_impl.hpp>
#include <hpx/runtime/agas/server/symbol_namespace.hpp>

namespace hpx { namespace agas
{

naming::gid_type bootstrap_symbol_namespace_gid()
{
    return naming::gid_type
        (HPX_AGAS_SYMBOL_NS_MSB, HPX_AGAS_SYMBOL_NS_LSB);
}

naming::id_type bootstrap_symbol_namespace_id()
{
    return naming::id_type
        (bootstrap_symbol_namespace_gid(), naming::id_type::unmanaged);
}

namespace server
{

response symbol_namespace::service(
    request const& req
  , error_code& ec
    )
{
    // IMPLEMENT
    return response();
}

response symbol_namespace::bind(
    std::string const& key
  , naming::gid_type const& gid
  , error_code& ec
    )
{ // {{{ bind implementation
    database_mutex_type::scoped_lock l(mutex_);

    gid_table_type::iterator it = gids_.find(key)
                           , end = gids_.end();

    if (it != end)
    {
        naming::gid_type old = it->second;
        it->second = gid;

        LAGAS_(info) << (boost::format(
            "symbol_namespace::bind, key(%1%), gid(%2%), old_gid(%3%)")
            % key % gid % old);

        if (&ec != &throws)
            ec = make_success_code();

        return response(symbol_ns_bind, old);
    }

    if (HPX_UNLIKELY(!util::insert_checked(gids_.insert(
            std::make_pair(key, gid)))))
    {
        HPX_THROWS_IF(ec, lock_error
          , "symbol_namespace::bind"
          , "GID table insertion failed due to a locking error or "
            "memory corruption");
        return response();
    }

    LAGAS_(info) << (boost::format(
        "symbol_namespace::bind, key(%1%), gid(%2%), old_gid(%3%)")
        % key % gid % gid);

    if (&ec != &throws)
        ec = make_success_code();

    return response(symbol_ns_bind, gid); 
} // }}}

response symbol_namespace::resolve(
    std::string const& key
  , error_code& ec
    )
{ // {{{ resolve implementation
    database_mutex_type::scoped_lock l(mutex_);

    gid_table_type::iterator it = gids_.find(key)
                           , end = gids_.end();

    if (it == end)
    {
        LAGAS_(info) << (boost::format(
            "symbol_namespace::resolve, key(%1%), response(no_success)")
            % key);

        if (&ec != &throws)
            ec = make_success_code();

        return response(symbol_ns_resolve
                           , naming::invalid_gid
                           , no_success);
    }

    LAGAS_(info) << (boost::format(
        "symbol_namespace::resolve, key(%1%), gid(%2%)")
        % key % it->second);

    if (&ec != &throws)
        ec = make_success_code();

    naming::gid_type gid;

    // Is this entry reference counted?
    if (naming::get_credit_from_gid(it->second) != 0)
    {
        gid = split_credits_for_gid(it->second);

        // Credit exhaustion - we need to get more.
        if (0 == naming::get_credit_from_gid(gid)) 
        {
            BOOST_ASSERT(1 == naming::get_credit_from_gid(it->second));
            naming::get_agas_client().incref(gid, 2 * HPX_INITIAL_GLOBALCREDIT); 

            naming::add_credit_to_gid(gid, HPX_INITIAL_GLOBALCREDIT);
            naming::add_credit_to_gid(it->second, HPX_INITIAL_GLOBALCREDIT);
        }
    }

    else
        gid = it->second;

    return response(symbol_ns_resolve, gid);
} // }}}  

response symbol_namespace::unbind(
    std::string const& key
  , error_code& ec
    )
{ // {{{ unbind implementation
    database_mutex_type::scoped_lock l(mutex_);
    
    gid_table_type::iterator it = gids_.find(key)
                           , end = gids_.end();

    if (it == end)
    {
        LAGAS_(info) << (boost::format(
            "symbol_namespace::unbind, key(%1%), response(no_success)")
            % key);

        if (&ec != &throws)
            ec = make_success_code();

        return response(symbol_ns_unbind, naming::invalid_gid, no_success);
    }

    const naming::gid_type gid = it->second;

    gids_.erase(it);

    LAGAS_(info) << (boost::format(
        "symbol_namespace::unbind, key(%1%)")
        % key);

    if (&ec != &throws)
        ec = make_success_code();

    return response(symbol_ns_unbind, gid);
} // }}} 

response symbol_namespace::iterate(
    iterate_symbols_function_type const& f
  , error_code& ec
    )
{ // {{{ iterate implementation
    database_mutex_type::scoped_lock l(mutex_);
    
    for (gid_table_type::iterator it = gids_.begin()
                                , end = gids_.end();
         it != end; ++it)
    {
        f(it->first, it->second);
    }

    LAGAS_(info) << "symbol_namespace::iterate";

    if (&ec != &throws)
        ec = make_success_code();

    return response(symbol_ns_iterate);
} // }}} 

}}}

