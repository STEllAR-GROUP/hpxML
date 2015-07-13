//  Copyright (c) 2007-2014 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_fwd.hpp>
#include <hpx/exception.hpp>
#include <hpx/apply.hpp>
#include <hpx/runtime/actions/continuation.hpp>
#include <hpx/lcos/base_lco.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace hpx
{
    void trigger_lco_event(naming::id_type const& id, bool move_credits)
    {
        lcos::base_lco::set_event_action set;
        if (move_credits)
        {
            naming::id_type target(id.get_gid(), id_type::managed_move_credit);
            id.make_unmanaged();

            apply(set, target);
        }
        else
        {
            apply(set, id);
        }
    }

    void trigger_lco_event(naming::id_type const& id,
        naming::id_type const& cont, bool move_credits)
    {
        lcos::base_lco::set_event_action set;
        if (move_credits)
        {
            naming::id_type target(id.get_gid(), id_type::managed_move_credit);
            id.make_unmanaged();

            apply_c(set, cont, target);
        }
        else
        {
            apply_c(set, cont, id);
        }
    }

    void set_lco_error(naming::id_type const& id,
        boost::exception_ptr const& e, bool move_credits)
    {
        lcos::base_lco::set_exception_action set;
        if (move_credits)
        {
            naming::id_type target(id.get_gid(), id_type::managed_move_credit);
            id.make_unmanaged();

            apply(set, target, e);
        }
        else
        {
            apply(set, id, e);
        }
    }

    void set_lco_error(naming::id_type const& id, //-V659
        boost::exception_ptr && e, bool move_credits)
    {
        lcos::base_lco::set_exception_action set;
        if (move_credits)
        {
            naming::id_type target(id.get_gid(), id_type::managed_move_credit);
            id.make_unmanaged();

            apply(set, target, std::move(e));
        }
        else
        {
            apply(set, id, std::move(e));
        }
    }

    void set_lco_error(naming::id_type const& id, boost::exception_ptr const& e,
        naming::id_type const& cont, bool move_credits)
    {
        lcos::base_lco::set_exception_action set;
        if (move_credits)
        {
            naming::id_type target(id.get_gid(), id_type::managed_move_credit);
            id.make_unmanaged();

            apply_c(set, cont, target, e);
        }
        else
        {
            apply_c(set, cont, id, e);
        }
    }

    void set_lco_error(naming::id_type const& id, //-V659
        boost::exception_ptr && e, naming::id_type const& cont,
        bool move_credits)
    {
        lcos::base_lco::set_exception_action set;
        if (move_credits)
        {
            naming::id_type target(id.get_gid(), id_type::managed_move_credit);
            id.make_unmanaged();

            apply_c(set, cont, target, std::move(e));
        }
        else
        {
            apply_c(set, cont, id, std::move(e));
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace actions
{
    ///////////////////////////////////////////////////////////////////////////
    void continuation::trigger() const
    {
        if (!gid_) {
            HPX_THROW_EXCEPTION(invalid_status,
                "continuation::trigger",
                "attempt to trigger invalid LCO (the id is invalid)");
            return;
        }

        LLCO_(info) << "continuation::trigger(" << gid_ << ")";
        trigger_lco_event(gid_);
    }

    ///////////////////////////////////////////////////////////////////////////
    void continuation::trigger_error(boost::exception_ptr const& e) const
    {
        if (!gid_) {
            HPX_THROW_EXCEPTION(invalid_status,
                "continuation::trigger_error",
                "attempt to trigger invalid LCO (the id is invalid)");
            return;
        }

        LLCO_(info) << "continuation::trigger_error(" << gid_ << ")";
        set_lco_error(gid_, e);
    }

    void continuation::trigger_error(boost::exception_ptr && e) const //-V659
    {
        if (!gid_) {
            HPX_THROW_EXCEPTION(invalid_status,
                "continuation::trigger_error",
                "attempt to trigger invalid LCO (the id is invalid)");
            return;
        }

        LLCO_(info) << "continuation::trigger_error(" << gid_ << ")";
        set_lco_error(gid_, std::move(e));
    }
}}

HPX_REGISTER_TYPED_CONTINUATION(void, hpx_void_typed_continuation);

