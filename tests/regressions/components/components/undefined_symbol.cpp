//  Copyright (c) 2011 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx.hpp>
#include <hpx/runtime/components/component_factory.hpp>
#include <hpx/util/portable_binary_iarchive.hpp>
#include <hpx/util/portable_binary_oarchive.hpp>

#include <boost/serialization/version.hpp>
#include <boost/serialization/export.hpp>

#include <tests/regressions/components/components/server/undefined_symbol.hpp>

HPX_REGISTER_COMPONENT_MODULE();

using hpx::test::server::undefined_symbol;

HPX_REGISTER_MINIMAL_COMPONENT_FACTORY(
    hpx::components::managed_component<undefined_symbol>,
    test_undefined_symbol_component);

HPX_REGISTER_ACTION_EX(
    undefined_symbol::break_action,
    test_undefined_symbol_break_action);

