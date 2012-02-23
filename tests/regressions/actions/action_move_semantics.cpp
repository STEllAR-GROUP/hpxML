////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Adelstein-Lelbach
//  Copyright (c) 2011-2012 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <hpx/hpx_init.hpp>
#include <hpx/include/plain_actions.hpp>
#include <hpx/lcos/eager_future.hpp>
#include <hpx/util/lightweight_test.hpp>

#include <tests/regressions/actions/action_move_semantics.hpp>

using boost::program_options::variables_map;
using boost::program_options::options_description;
using boost::program_options::value;

using hpx::naming::id_type;

using hpx::actions::plain_action1;
using hpx::actions::plain_result_action1;
using hpx::actions::plain_direct_action1;
using hpx::actions::plain_direct_result_action1;

using hpx::lcos::eager_future;

using hpx::init;
using hpx::finalize;
using hpx::find_here;

using hpx::test::movable_object;
using hpx::test::non_movable_object;

///////////////////////////////////////////////////////////////////////////////
void pass_movable_object_void(movable_object const& obj) {}
int pass_movable_object(movable_object const& obj) { return 0; }

// 'normal' actions (execution is scheduled on a new thread
typedef plain_action1<
    movable_object const&, pass_movable_object_void
> pass_movable_object_void_action;
typedef plain_result_action1<
    int, movable_object const&, pass_movable_object
> pass_movable_object_action;

HPX_REGISTER_PLAIN_ACTION(pass_movable_object_void_action);
HPX_REGISTER_PLAIN_ACTION(pass_movable_object_action);

// direct actions (execution happens in the calling thread)
typedef plain_direct_action1<
    movable_object const&, pass_movable_object_void
> pass_movable_object_void_direct_action;
typedef plain_direct_result_action1<
    int, movable_object const&, pass_movable_object
> pass_movable_object_direct_action;

HPX_REGISTER_PLAIN_ACTION(pass_movable_object_void_direct_action);
HPX_REGISTER_PLAIN_ACTION(pass_movable_object_direct_action);

///////////////////////////////////////////////////////////////////////////////
void pass_non_movable_object_void(non_movable_object const& obj) {}
int pass_non_movable_object(non_movable_object const& obj) { return 0; }

// 'normal' actions (execution is scheduled on a new thread
typedef plain_action1<
    non_movable_object const&, pass_non_movable_object_void
> pass_non_movable_object_void_action;
typedef plain_result_action1<
    int, non_movable_object const&, pass_non_movable_object
> pass_non_movable_object_action;

HPX_REGISTER_PLAIN_ACTION(pass_non_movable_object_void_action);
HPX_REGISTER_PLAIN_ACTION(pass_non_movable_object_action);

// direct actions (execution happens in the calling thread)
typedef plain_direct_action1<
    non_movable_object const&, pass_non_movable_object_void
> pass_non_movable_object_void_direct_action;
typedef plain_direct_result_action1<
    int, non_movable_object const&, pass_non_movable_object
> pass_non_movable_object_direct_action;

HPX_REGISTER_PLAIN_ACTION(pass_non_movable_object_void_direct_action);
HPX_REGISTER_PLAIN_ACTION(pass_non_movable_object_direct_action);

///////////////////////////////////////////////////////////////////////////////
template <typename Action, typename Object>
std::size_t pass_object()
{
    Object obj;
    eager_future<Action> f(find_here(), obj);
    f.get();

    return obj.copy_count;
}

int hpx_main(variables_map& vm)
{
    // test for movable object ('normal' actions)
    HPX_TEST((pass_object<pass_movable_object_void_action, movable_object>() == 1));
    HPX_TEST((pass_object<pass_movable_object_action, movable_object>() == 1));

    // test for movable object (direct actions)
    HPX_TEST((pass_object<pass_movable_object_void_direct_action, movable_object>() == 0));
    HPX_TEST((pass_object<pass_movable_object_direct_action, movable_object>(), 0));

    // FIXME: Can we get down to one copy for non-movable objects as well?

    // test for a non-movable object ('normal' actions)
    HPX_TEST((pass_object<pass_non_movable_object_void_action, non_movable_object>() == 2));
    HPX_TEST((pass_object<pass_non_movable_object_action, non_movable_object>() == 2));

    // test for a non-movable object (direct actions)
    HPX_TEST((pass_object<pass_non_movable_object_void_direct_action, non_movable_object>() == 0));
    HPX_TEST((pass_object<pass_non_movable_object_direct_action, non_movable_object>() == 0));

    finalize();

    return hpx::util::report_errors();
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    // Configure application-specific options.
    options_description desc_commandline(
        "Usage: " HPX_APPLICATION_STRING " [options]");

    // Initialize and run HPX.
    return init(desc_commandline, argc, argv);
}

