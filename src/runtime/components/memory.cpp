//  Copyright (c) 2007-2012 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_fwd.hpp>
#include <hpx/runtime/components/server/memory.hpp>
#include <hpx/lcos/base_lco_with_value.hpp>
#include <hpx/runtime/applier/apply.hpp>
#include <hpx/runtime/actions/continuation.hpp>
#include <hpx/util/assert.hpp>

#include <hpx/util/portable_binary_iarchive.hpp>
#include <hpx/util/portable_binary_oarchive.hpp>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/export.hpp>

///////////////////////////////////////////////////////////////////////////////
HPX_DEFINE_GET_COMPONENT_TYPE_STATIC(hpx::components::server::memory,
    hpx::components::component_memory)

///////////////////////////////////////////////////////////////////////////////
// Serialization support for the runtime_support actions
HPX_REGISTER_PLAIN_ACTION(hpx::components::server::allocate_action, allocate_action);

HPX_REGISTER_ACTION(hpx::components::server::memory::store8_action, store8_action)
HPX_REGISTER_ACTION(hpx::components::server::memory::store16_action, store16_action)
HPX_REGISTER_ACTION(hpx::components::server::memory::store32_action, store32_action)
HPX_REGISTER_ACTION(hpx::components::server::memory::store64_action, store64_action)
HPX_REGISTER_ACTION(hpx::components::server::memory::store128_action, store128_action)

HPX_REGISTER_ACTION(hpx::components::server::memory::load8_action, load8_action)
HPX_REGISTER_ACTION(hpx::components::server::memory::load16_action, load16_action)
HPX_REGISTER_ACTION(hpx::components::server::memory::load32_action, load32_action)
HPX_REGISTER_ACTION(hpx::components::server::memory::load64_action, load64_action)
HPX_REGISTER_ACTION(hpx::components::server::memory::load128_action, load128_action)

HPX_REGISTER_BASE_LCO_WITH_VALUE(
    hpx::components::server::memory::uint128_t
  , hpx_components_memory_uint128_t
)

namespace hpx { namespace components { namespace server
{
    naming::gid_type allocate(std::size_t size)
    {
        naming::gid_type gid(hpx::applier::get_applier().get_raw_locality());
        gid.set_lsb(new boost::uint8_t[size]);
        naming::detail::set_credit_for_gid(gid, HPX_GLOBALCREDIT_INITIAL);
        return gid;
    }

    template <typename Archive>
    void memory::uint128_t::serialize(Archive& ar, const unsigned int version)
    {
        ar & msb & lsb;
    }

    template void memory::uint128_t::serialize<util::portable_binary_oarchive>(
        util::portable_binary_oarchive& ar, const unsigned int version);
    template void memory::uint128_t::serialize<util::portable_binary_iarchive>(
        util::portable_binary_iarchive& ar, const unsigned int version);
}}}
