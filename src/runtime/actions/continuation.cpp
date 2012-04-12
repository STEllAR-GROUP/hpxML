//  Copyright (c) 2007-2012 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_fwd.hpp>
#include <hpx/runtime/applier/apply.hpp>
#include <hpx/runtime/actions/continuation.hpp>
#include <hpx/lcos/base_lco.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace actions
{
    ///////////////////////////////////////////////////////////////////////////
    void continuation::trigger()
    {
        LLCO_(info) << "continuation::trigger(" << gid_ << ")";
        hpx::applier::apply<lcos::base_lco::set_event_action>(gid_);
    }

    ///////////////////////////////////////////////////////////////////////////
    void continuation::trigger_error(boost::exception_ptr const& e)
    {
        LLCO_(info) << "continuation::trigger_error(" << gid_ << ")";
        hpx::applier::apply<lcos::base_lco::set_exception_action>(gid_, e);
    }

    void continuation::trigger_error(BOOST_RV_REF(boost::exception_ptr) e)
    {
        LLCO_(info) << "continuation::trigger_error(" << gid_ << ")";
        hpx::applier::apply<lcos::base_lco::set_exception_action>(
            gid_, boost::move(e));
    }
}}

