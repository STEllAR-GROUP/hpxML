//  Copyright (c) 2007-2012 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_init.hpp>
#include <hpx/include/plain_actions.hpp>
#include <hpx/lcos/eager_future.hpp>
#include <hpx/util/lightweight_test.hpp>

#include <boost/foreach.hpp>
#include <boost/assign/std/vector.hpp>

#include <tests/regressions/actions/components/action_move_semantics.hpp>
#include <tests/regressions/actions/components/movable_objects.hpp>

using hpx::test::movable_object;
using hpx::test::non_movable_object;

///////////////////////////////////////////////////////////////////////////////
template <typename Action, typename Object>
std::size_t pass_object(hpx::naming::id_type id)
{
    using hpx::test::action_move_semantics;

    action_move_semantics test(action_move_semantics::create_sync(id));
    Object obj;
    obj.reset_count();

    return hpx::lcos::eager_future<Action>(test.get_gid(), obj).get();
}

int hpx_main(boost::program_options::variables_map& vm)
{
    using hpx::test::server::action_move_semantics;

    std::vector<hpx::naming::id_type> localities = hpx::find_all_localities();
    BOOST_FOREACH(hpx::naming::id_type id, localities)
    {
        bool is_local = (id == hpx::find_here()) ? true : false;

        // test for movable object ('normal' actions)
        HPX_TEST_EQ((
            pass_object<
                action_move_semantics::test_movable_action, movable_object
            >(id)
        ), is_local ? 1 : 2);

        // test for movable object (direct actions)
        HPX_TEST_EQ((
            pass_object<
                action_move_semantics::test_movable_direct_action, movable_object
            >(id)
        ), is_local ? 0 : 2);

        // FIXME: Can we get down to one copy for non-movable objects as well?

        // test for a non-movable object ('normal' actions)
        HPX_TEST_EQ((
            pass_object<
                action_move_semantics::test_non_movable_action, non_movable_object
            >(id)
        ), is_local ? 2 : 3);

        // test for a non-movable object (direct actions)
        HPX_TEST_EQ((
            pass_object<
                action_move_semantics::test_non_movable_direct_action, non_movable_object
            >(id)
        ), is_local ? 0 : 3);
    }

    hpx::finalize();
    return hpx::util::report_errors();
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    // Configure application-specific options.
    boost::program_options::options_description desc_commandline(
        "Usage: " HPX_APPLICATION_STRING " [options]");

    // we need to explicitly enable the test components used by this test
    using namespace boost::assign;
    std::vector<std::string> cfg;
    cfg += "hpx.components.test_action_move_semantics.enabled = 1";

    // Initialize and run HPX.
    return hpx::init(desc_commandline, argc, argv, cfg);
}

