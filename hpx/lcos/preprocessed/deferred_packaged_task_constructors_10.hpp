// Copyright (c) 2007-2012 Hartmut Kaiser
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This file has been automatically generated using the Boost.Wave tool.
// Do not edit manually.


    template <typename Arg0 , typename Arg1>
    void apply(naming::id_type const& gid,
        HPX_FWD_ARGS(2, 0, ( Arg, arg)) , HPX_FWD_ARGS(2, 1, ( Arg, arg)))
    {
        util::block_profiler_wrapper<deferred_packaged_task_tag> bp(apply_logger_);
        hpx::apply_c<Action>(
            this->get_gid(), gid, HPX_FORWARD_ARGS(2, 0, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 1, ( Arg, arg)));
    }
private:
    template <typename Arg0 , typename Arg1>
    static void invoke2(
        hpx::lcos::deferred_packaged_task<Action,Result> *th,
        naming::id_type const& gid,
        HPX_FWD_ARGS(2, 0, ( Arg, arg)) , HPX_FWD_ARGS(2, 1, ( Arg, arg)))
    {
        if (!((*th->impl_)->is_ready()))
            th->apply(gid, HPX_FORWARD_ARGS(2, 0, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 1, ( Arg, arg)));
    }
public:
    template <typename Arg0 , typename Arg1>
    deferred_packaged_task(naming::gid_type const& gid,
            HPX_FWD_ARGS(2, 0, ( Arg, arg)) , HPX_FWD_ARGS(2, 1, ( Arg, arg)))
      : apply_logger_("deferred_packaged_task::apply"),
        closure_(boost::bind(
          &deferred_packaged_task::template invoke2<Arg0 , Arg1>,
            this_(), naming::id_type(gid, naming::id_type::unmanaged),
            HPX_FORWARD_ARGS(2, 0, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 1, ( Arg, arg))))
    {
        LLCO_(info) << "deferred_packaged_task::deferred_packaged_task("
                    << hpx::actions::detail::get_action_name<Action>()
                    << ", "
                    << gid
                    << ") args(" << (2 + 1) << ")";
    }
    template <typename Arg0 , typename Arg1>
    deferred_packaged_task(naming::id_type const& gid,
            HPX_FWD_ARGS(2, 0, ( Arg, arg)) , HPX_FWD_ARGS(2, 1, ( Arg, arg)))
      : apply_logger_("deferred_packaged_task::apply"),
        closure_(boost::bind(
          &deferred_packaged_task::template invoke2<Arg0 , Arg1>,
            this_(), gid,
            HPX_FORWARD_ARGS(2, 0, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 1, ( Arg, arg))))
    {
        LLCO_(info) << "deferred_packaged_task::deferred_packaged_task("
                    << hpx::actions::detail::get_action_name<Action>()
                    << ", "
                    << gid
                    << ") args(" << (2 + 1) << ")";
    }
    template <typename Arg0 , typename Arg1 , typename Arg2>
    void apply(naming::id_type const& gid,
        HPX_FWD_ARGS(2, 0, ( Arg, arg)) , HPX_FWD_ARGS(2, 1, ( Arg, arg)) , HPX_FWD_ARGS(2, 2, ( Arg, arg)))
    {
        util::block_profiler_wrapper<deferred_packaged_task_tag> bp(apply_logger_);
        hpx::apply_c<Action>(
            this->get_gid(), gid, HPX_FORWARD_ARGS(2, 0, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 1, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 2, ( Arg, arg)));
    }
private:
    template <typename Arg0 , typename Arg1 , typename Arg2>
    static void invoke3(
        hpx::lcos::deferred_packaged_task<Action,Result> *th,
        naming::id_type const& gid,
        HPX_FWD_ARGS(2, 0, ( Arg, arg)) , HPX_FWD_ARGS(2, 1, ( Arg, arg)) , HPX_FWD_ARGS(2, 2, ( Arg, arg)))
    {
        if (!((*th->impl_)->is_ready()))
            th->apply(gid, HPX_FORWARD_ARGS(2, 0, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 1, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 2, ( Arg, arg)));
    }
public:
    template <typename Arg0 , typename Arg1 , typename Arg2>
    deferred_packaged_task(naming::gid_type const& gid,
            HPX_FWD_ARGS(2, 0, ( Arg, arg)) , HPX_FWD_ARGS(2, 1, ( Arg, arg)) , HPX_FWD_ARGS(2, 2, ( Arg, arg)))
      : apply_logger_("deferred_packaged_task::apply"),
        closure_(boost::bind(
          &deferred_packaged_task::template invoke3<Arg0 , Arg1 , Arg2>,
            this_(), naming::id_type(gid, naming::id_type::unmanaged),
            HPX_FORWARD_ARGS(2, 0, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 1, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 2, ( Arg, arg))))
    {
        LLCO_(info) << "deferred_packaged_task::deferred_packaged_task("
                    << hpx::actions::detail::get_action_name<Action>()
                    << ", "
                    << gid
                    << ") args(" << (3 + 1) << ")";
    }
    template <typename Arg0 , typename Arg1 , typename Arg2>
    deferred_packaged_task(naming::id_type const& gid,
            HPX_FWD_ARGS(2, 0, ( Arg, arg)) , HPX_FWD_ARGS(2, 1, ( Arg, arg)) , HPX_FWD_ARGS(2, 2, ( Arg, arg)))
      : apply_logger_("deferred_packaged_task::apply"),
        closure_(boost::bind(
          &deferred_packaged_task::template invoke3<Arg0 , Arg1 , Arg2>,
            this_(), gid,
            HPX_FORWARD_ARGS(2, 0, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 1, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 2, ( Arg, arg))))
    {
        LLCO_(info) << "deferred_packaged_task::deferred_packaged_task("
                    << hpx::actions::detail::get_action_name<Action>()
                    << ", "
                    << gid
                    << ") args(" << (3 + 1) << ")";
    }
    template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3>
    void apply(naming::id_type const& gid,
        HPX_FWD_ARGS(2, 0, ( Arg, arg)) , HPX_FWD_ARGS(2, 1, ( Arg, arg)) , HPX_FWD_ARGS(2, 2, ( Arg, arg)) , HPX_FWD_ARGS(2, 3, ( Arg, arg)))
    {
        util::block_profiler_wrapper<deferred_packaged_task_tag> bp(apply_logger_);
        hpx::apply_c<Action>(
            this->get_gid(), gid, HPX_FORWARD_ARGS(2, 0, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 1, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 2, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 3, ( Arg, arg)));
    }
private:
    template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3>
    static void invoke4(
        hpx::lcos::deferred_packaged_task<Action,Result> *th,
        naming::id_type const& gid,
        HPX_FWD_ARGS(2, 0, ( Arg, arg)) , HPX_FWD_ARGS(2, 1, ( Arg, arg)) , HPX_FWD_ARGS(2, 2, ( Arg, arg)) , HPX_FWD_ARGS(2, 3, ( Arg, arg)))
    {
        if (!((*th->impl_)->is_ready()))
            th->apply(gid, HPX_FORWARD_ARGS(2, 0, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 1, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 2, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 3, ( Arg, arg)));
    }
public:
    template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3>
    deferred_packaged_task(naming::gid_type const& gid,
            HPX_FWD_ARGS(2, 0, ( Arg, arg)) , HPX_FWD_ARGS(2, 1, ( Arg, arg)) , HPX_FWD_ARGS(2, 2, ( Arg, arg)) , HPX_FWD_ARGS(2, 3, ( Arg, arg)))
      : apply_logger_("deferred_packaged_task::apply"),
        closure_(boost::bind(
          &deferred_packaged_task::template invoke4<Arg0 , Arg1 , Arg2 , Arg3>,
            this_(), naming::id_type(gid, naming::id_type::unmanaged),
            HPX_FORWARD_ARGS(2, 0, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 1, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 2, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 3, ( Arg, arg))))
    {
        LLCO_(info) << "deferred_packaged_task::deferred_packaged_task("
                    << hpx::actions::detail::get_action_name<Action>()
                    << ", "
                    << gid
                    << ") args(" << (4 + 1) << ")";
    }
    template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3>
    deferred_packaged_task(naming::id_type const& gid,
            HPX_FWD_ARGS(2, 0, ( Arg, arg)) , HPX_FWD_ARGS(2, 1, ( Arg, arg)) , HPX_FWD_ARGS(2, 2, ( Arg, arg)) , HPX_FWD_ARGS(2, 3, ( Arg, arg)))
      : apply_logger_("deferred_packaged_task::apply"),
        closure_(boost::bind(
          &deferred_packaged_task::template invoke4<Arg0 , Arg1 , Arg2 , Arg3>,
            this_(), gid,
            HPX_FORWARD_ARGS(2, 0, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 1, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 2, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 3, ( Arg, arg))))
    {
        LLCO_(info) << "deferred_packaged_task::deferred_packaged_task("
                    << hpx::actions::detail::get_action_name<Action>()
                    << ", "
                    << gid
                    << ") args(" << (4 + 1) << ")";
    }
    template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4>
    void apply(naming::id_type const& gid,
        HPX_FWD_ARGS(2, 0, ( Arg, arg)) , HPX_FWD_ARGS(2, 1, ( Arg, arg)) , HPX_FWD_ARGS(2, 2, ( Arg, arg)) , HPX_FWD_ARGS(2, 3, ( Arg, arg)) , HPX_FWD_ARGS(2, 4, ( Arg, arg)))
    {
        util::block_profiler_wrapper<deferred_packaged_task_tag> bp(apply_logger_);
        hpx::apply_c<Action>(
            this->get_gid(), gid, HPX_FORWARD_ARGS(2, 0, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 1, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 2, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 3, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 4, ( Arg, arg)));
    }
private:
    template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4>
    static void invoke5(
        hpx::lcos::deferred_packaged_task<Action,Result> *th,
        naming::id_type const& gid,
        HPX_FWD_ARGS(2, 0, ( Arg, arg)) , HPX_FWD_ARGS(2, 1, ( Arg, arg)) , HPX_FWD_ARGS(2, 2, ( Arg, arg)) , HPX_FWD_ARGS(2, 3, ( Arg, arg)) , HPX_FWD_ARGS(2, 4, ( Arg, arg)))
    {
        if (!((*th->impl_)->is_ready()))
            th->apply(gid, HPX_FORWARD_ARGS(2, 0, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 1, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 2, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 3, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 4, ( Arg, arg)));
    }
public:
    template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4>
    deferred_packaged_task(naming::gid_type const& gid,
            HPX_FWD_ARGS(2, 0, ( Arg, arg)) , HPX_FWD_ARGS(2, 1, ( Arg, arg)) , HPX_FWD_ARGS(2, 2, ( Arg, arg)) , HPX_FWD_ARGS(2, 3, ( Arg, arg)) , HPX_FWD_ARGS(2, 4, ( Arg, arg)))
      : apply_logger_("deferred_packaged_task::apply"),
        closure_(boost::bind(
          &deferred_packaged_task::template invoke5<Arg0 , Arg1 , Arg2 , Arg3 , Arg4>,
            this_(), naming::id_type(gid, naming::id_type::unmanaged),
            HPX_FORWARD_ARGS(2, 0, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 1, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 2, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 3, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 4, ( Arg, arg))))
    {
        LLCO_(info) << "deferred_packaged_task::deferred_packaged_task("
                    << hpx::actions::detail::get_action_name<Action>()
                    << ", "
                    << gid
                    << ") args(" << (5 + 1) << ")";
    }
    template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4>
    deferred_packaged_task(naming::id_type const& gid,
            HPX_FWD_ARGS(2, 0, ( Arg, arg)) , HPX_FWD_ARGS(2, 1, ( Arg, arg)) , HPX_FWD_ARGS(2, 2, ( Arg, arg)) , HPX_FWD_ARGS(2, 3, ( Arg, arg)) , HPX_FWD_ARGS(2, 4, ( Arg, arg)))
      : apply_logger_("deferred_packaged_task::apply"),
        closure_(boost::bind(
          &deferred_packaged_task::template invoke5<Arg0 , Arg1 , Arg2 , Arg3 , Arg4>,
            this_(), gid,
            HPX_FORWARD_ARGS(2, 0, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 1, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 2, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 3, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 4, ( Arg, arg))))
    {
        LLCO_(info) << "deferred_packaged_task::deferred_packaged_task("
                    << hpx::actions::detail::get_action_name<Action>()
                    << ", "
                    << gid
                    << ") args(" << (5 + 1) << ")";
    }
    template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5>
    void apply(naming::id_type const& gid,
        HPX_FWD_ARGS(2, 0, ( Arg, arg)) , HPX_FWD_ARGS(2, 1, ( Arg, arg)) , HPX_FWD_ARGS(2, 2, ( Arg, arg)) , HPX_FWD_ARGS(2, 3, ( Arg, arg)) , HPX_FWD_ARGS(2, 4, ( Arg, arg)) , HPX_FWD_ARGS(2, 5, ( Arg, arg)))
    {
        util::block_profiler_wrapper<deferred_packaged_task_tag> bp(apply_logger_);
        hpx::apply_c<Action>(
            this->get_gid(), gid, HPX_FORWARD_ARGS(2, 0, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 1, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 2, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 3, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 4, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 5, ( Arg, arg)));
    }
private:
    template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5>
    static void invoke6(
        hpx::lcos::deferred_packaged_task<Action,Result> *th,
        naming::id_type const& gid,
        HPX_FWD_ARGS(2, 0, ( Arg, arg)) , HPX_FWD_ARGS(2, 1, ( Arg, arg)) , HPX_FWD_ARGS(2, 2, ( Arg, arg)) , HPX_FWD_ARGS(2, 3, ( Arg, arg)) , HPX_FWD_ARGS(2, 4, ( Arg, arg)) , HPX_FWD_ARGS(2, 5, ( Arg, arg)))
    {
        if (!((*th->impl_)->is_ready()))
            th->apply(gid, HPX_FORWARD_ARGS(2, 0, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 1, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 2, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 3, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 4, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 5, ( Arg, arg)));
    }
public:
    template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5>
    deferred_packaged_task(naming::gid_type const& gid,
            HPX_FWD_ARGS(2, 0, ( Arg, arg)) , HPX_FWD_ARGS(2, 1, ( Arg, arg)) , HPX_FWD_ARGS(2, 2, ( Arg, arg)) , HPX_FWD_ARGS(2, 3, ( Arg, arg)) , HPX_FWD_ARGS(2, 4, ( Arg, arg)) , HPX_FWD_ARGS(2, 5, ( Arg, arg)))
      : apply_logger_("deferred_packaged_task::apply"),
        closure_(boost::bind(
          &deferred_packaged_task::template invoke6<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5>,
            this_(), naming::id_type(gid, naming::id_type::unmanaged),
            HPX_FORWARD_ARGS(2, 0, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 1, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 2, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 3, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 4, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 5, ( Arg, arg))))
    {
        LLCO_(info) << "deferred_packaged_task::deferred_packaged_task("
                    << hpx::actions::detail::get_action_name<Action>()
                    << ", "
                    << gid
                    << ") args(" << (6 + 1) << ")";
    }
    template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5>
    deferred_packaged_task(naming::id_type const& gid,
            HPX_FWD_ARGS(2, 0, ( Arg, arg)) , HPX_FWD_ARGS(2, 1, ( Arg, arg)) , HPX_FWD_ARGS(2, 2, ( Arg, arg)) , HPX_FWD_ARGS(2, 3, ( Arg, arg)) , HPX_FWD_ARGS(2, 4, ( Arg, arg)) , HPX_FWD_ARGS(2, 5, ( Arg, arg)))
      : apply_logger_("deferred_packaged_task::apply"),
        closure_(boost::bind(
          &deferred_packaged_task::template invoke6<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5>,
            this_(), gid,
            HPX_FORWARD_ARGS(2, 0, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 1, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 2, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 3, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 4, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 5, ( Arg, arg))))
    {
        LLCO_(info) << "deferred_packaged_task::deferred_packaged_task("
                    << hpx::actions::detail::get_action_name<Action>()
                    << ", "
                    << gid
                    << ") args(" << (6 + 1) << ")";
    }
    template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6>
    void apply(naming::id_type const& gid,
        HPX_FWD_ARGS(2, 0, ( Arg, arg)) , HPX_FWD_ARGS(2, 1, ( Arg, arg)) , HPX_FWD_ARGS(2, 2, ( Arg, arg)) , HPX_FWD_ARGS(2, 3, ( Arg, arg)) , HPX_FWD_ARGS(2, 4, ( Arg, arg)) , HPX_FWD_ARGS(2, 5, ( Arg, arg)) , HPX_FWD_ARGS(2, 6, ( Arg, arg)))
    {
        util::block_profiler_wrapper<deferred_packaged_task_tag> bp(apply_logger_);
        hpx::apply_c<Action>(
            this->get_gid(), gid, HPX_FORWARD_ARGS(2, 0, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 1, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 2, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 3, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 4, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 5, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 6, ( Arg, arg)));
    }
private:
    template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6>
    static void invoke7(
        hpx::lcos::deferred_packaged_task<Action,Result> *th,
        naming::id_type const& gid,
        HPX_FWD_ARGS(2, 0, ( Arg, arg)) , HPX_FWD_ARGS(2, 1, ( Arg, arg)) , HPX_FWD_ARGS(2, 2, ( Arg, arg)) , HPX_FWD_ARGS(2, 3, ( Arg, arg)) , HPX_FWD_ARGS(2, 4, ( Arg, arg)) , HPX_FWD_ARGS(2, 5, ( Arg, arg)) , HPX_FWD_ARGS(2, 6, ( Arg, arg)))
    {
        if (!((*th->impl_)->is_ready()))
            th->apply(gid, HPX_FORWARD_ARGS(2, 0, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 1, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 2, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 3, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 4, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 5, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 6, ( Arg, arg)));
    }
public:
    template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6>
    deferred_packaged_task(naming::gid_type const& gid,
            HPX_FWD_ARGS(2, 0, ( Arg, arg)) , HPX_FWD_ARGS(2, 1, ( Arg, arg)) , HPX_FWD_ARGS(2, 2, ( Arg, arg)) , HPX_FWD_ARGS(2, 3, ( Arg, arg)) , HPX_FWD_ARGS(2, 4, ( Arg, arg)) , HPX_FWD_ARGS(2, 5, ( Arg, arg)) , HPX_FWD_ARGS(2, 6, ( Arg, arg)))
      : apply_logger_("deferred_packaged_task::apply"),
        closure_(boost::bind(
          &deferred_packaged_task::template invoke7<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6>,
            this_(), naming::id_type(gid, naming::id_type::unmanaged),
            HPX_FORWARD_ARGS(2, 0, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 1, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 2, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 3, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 4, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 5, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 6, ( Arg, arg))))
    {
        LLCO_(info) << "deferred_packaged_task::deferred_packaged_task("
                    << hpx::actions::detail::get_action_name<Action>()
                    << ", "
                    << gid
                    << ") args(" << (7 + 1) << ")";
    }
    template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6>
    deferred_packaged_task(naming::id_type const& gid,
            HPX_FWD_ARGS(2, 0, ( Arg, arg)) , HPX_FWD_ARGS(2, 1, ( Arg, arg)) , HPX_FWD_ARGS(2, 2, ( Arg, arg)) , HPX_FWD_ARGS(2, 3, ( Arg, arg)) , HPX_FWD_ARGS(2, 4, ( Arg, arg)) , HPX_FWD_ARGS(2, 5, ( Arg, arg)) , HPX_FWD_ARGS(2, 6, ( Arg, arg)))
      : apply_logger_("deferred_packaged_task::apply"),
        closure_(boost::bind(
          &deferred_packaged_task::template invoke7<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6>,
            this_(), gid,
            HPX_FORWARD_ARGS(2, 0, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 1, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 2, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 3, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 4, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 5, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 6, ( Arg, arg))))
    {
        LLCO_(info) << "deferred_packaged_task::deferred_packaged_task("
                    << hpx::actions::detail::get_action_name<Action>()
                    << ", "
                    << gid
                    << ") args(" << (7 + 1) << ")";
    }
    template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7>
    void apply(naming::id_type const& gid,
        HPX_FWD_ARGS(2, 0, ( Arg, arg)) , HPX_FWD_ARGS(2, 1, ( Arg, arg)) , HPX_FWD_ARGS(2, 2, ( Arg, arg)) , HPX_FWD_ARGS(2, 3, ( Arg, arg)) , HPX_FWD_ARGS(2, 4, ( Arg, arg)) , HPX_FWD_ARGS(2, 5, ( Arg, arg)) , HPX_FWD_ARGS(2, 6, ( Arg, arg)) , HPX_FWD_ARGS(2, 7, ( Arg, arg)))
    {
        util::block_profiler_wrapper<deferred_packaged_task_tag> bp(apply_logger_);
        hpx::apply_c<Action>(
            this->get_gid(), gid, HPX_FORWARD_ARGS(2, 0, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 1, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 2, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 3, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 4, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 5, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 6, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 7, ( Arg, arg)));
    }
private:
    template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7>
    static void invoke8(
        hpx::lcos::deferred_packaged_task<Action,Result> *th,
        naming::id_type const& gid,
        HPX_FWD_ARGS(2, 0, ( Arg, arg)) , HPX_FWD_ARGS(2, 1, ( Arg, arg)) , HPX_FWD_ARGS(2, 2, ( Arg, arg)) , HPX_FWD_ARGS(2, 3, ( Arg, arg)) , HPX_FWD_ARGS(2, 4, ( Arg, arg)) , HPX_FWD_ARGS(2, 5, ( Arg, arg)) , HPX_FWD_ARGS(2, 6, ( Arg, arg)) , HPX_FWD_ARGS(2, 7, ( Arg, arg)))
    {
        if (!((*th->impl_)->is_ready()))
            th->apply(gid, HPX_FORWARD_ARGS(2, 0, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 1, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 2, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 3, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 4, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 5, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 6, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 7, ( Arg, arg)));
    }
public:
    template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7>
    deferred_packaged_task(naming::gid_type const& gid,
            HPX_FWD_ARGS(2, 0, ( Arg, arg)) , HPX_FWD_ARGS(2, 1, ( Arg, arg)) , HPX_FWD_ARGS(2, 2, ( Arg, arg)) , HPX_FWD_ARGS(2, 3, ( Arg, arg)) , HPX_FWD_ARGS(2, 4, ( Arg, arg)) , HPX_FWD_ARGS(2, 5, ( Arg, arg)) , HPX_FWD_ARGS(2, 6, ( Arg, arg)) , HPX_FWD_ARGS(2, 7, ( Arg, arg)))
      : apply_logger_("deferred_packaged_task::apply"),
        closure_(boost::bind(
          &deferred_packaged_task::template invoke8<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6 , Arg7>,
            this_(), naming::id_type(gid, naming::id_type::unmanaged),
            HPX_FORWARD_ARGS(2, 0, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 1, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 2, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 3, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 4, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 5, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 6, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 7, ( Arg, arg))))
    {
        LLCO_(info) << "deferred_packaged_task::deferred_packaged_task("
                    << hpx::actions::detail::get_action_name<Action>()
                    << ", "
                    << gid
                    << ") args(" << (8 + 1) << ")";
    }
    template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7>
    deferred_packaged_task(naming::id_type const& gid,
            HPX_FWD_ARGS(2, 0, ( Arg, arg)) , HPX_FWD_ARGS(2, 1, ( Arg, arg)) , HPX_FWD_ARGS(2, 2, ( Arg, arg)) , HPX_FWD_ARGS(2, 3, ( Arg, arg)) , HPX_FWD_ARGS(2, 4, ( Arg, arg)) , HPX_FWD_ARGS(2, 5, ( Arg, arg)) , HPX_FWD_ARGS(2, 6, ( Arg, arg)) , HPX_FWD_ARGS(2, 7, ( Arg, arg)))
      : apply_logger_("deferred_packaged_task::apply"),
        closure_(boost::bind(
          &deferred_packaged_task::template invoke8<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6 , Arg7>,
            this_(), gid,
            HPX_FORWARD_ARGS(2, 0, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 1, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 2, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 3, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 4, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 5, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 6, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 7, ( Arg, arg))))
    {
        LLCO_(info) << "deferred_packaged_task::deferred_packaged_task("
                    << hpx::actions::detail::get_action_name<Action>()
                    << ", "
                    << gid
                    << ") args(" << (8 + 1) << ")";
    }
    template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8>
    void apply(naming::id_type const& gid,
        HPX_FWD_ARGS(2, 0, ( Arg, arg)) , HPX_FWD_ARGS(2, 1, ( Arg, arg)) , HPX_FWD_ARGS(2, 2, ( Arg, arg)) , HPX_FWD_ARGS(2, 3, ( Arg, arg)) , HPX_FWD_ARGS(2, 4, ( Arg, arg)) , HPX_FWD_ARGS(2, 5, ( Arg, arg)) , HPX_FWD_ARGS(2, 6, ( Arg, arg)) , HPX_FWD_ARGS(2, 7, ( Arg, arg)) , HPX_FWD_ARGS(2, 8, ( Arg, arg)))
    {
        util::block_profiler_wrapper<deferred_packaged_task_tag> bp(apply_logger_);
        hpx::apply_c<Action>(
            this->get_gid(), gid, HPX_FORWARD_ARGS(2, 0, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 1, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 2, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 3, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 4, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 5, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 6, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 7, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 8, ( Arg, arg)));
    }
private:
    template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8>
    static void invoke9(
        hpx::lcos::deferred_packaged_task<Action,Result> *th,
        naming::id_type const& gid,
        HPX_FWD_ARGS(2, 0, ( Arg, arg)) , HPX_FWD_ARGS(2, 1, ( Arg, arg)) , HPX_FWD_ARGS(2, 2, ( Arg, arg)) , HPX_FWD_ARGS(2, 3, ( Arg, arg)) , HPX_FWD_ARGS(2, 4, ( Arg, arg)) , HPX_FWD_ARGS(2, 5, ( Arg, arg)) , HPX_FWD_ARGS(2, 6, ( Arg, arg)) , HPX_FWD_ARGS(2, 7, ( Arg, arg)) , HPX_FWD_ARGS(2, 8, ( Arg, arg)))
    {
        if (!((*th->impl_)->is_ready()))
            th->apply(gid, HPX_FORWARD_ARGS(2, 0, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 1, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 2, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 3, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 4, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 5, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 6, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 7, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 8, ( Arg, arg)));
    }
public:
    template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8>
    deferred_packaged_task(naming::gid_type const& gid,
            HPX_FWD_ARGS(2, 0, ( Arg, arg)) , HPX_FWD_ARGS(2, 1, ( Arg, arg)) , HPX_FWD_ARGS(2, 2, ( Arg, arg)) , HPX_FWD_ARGS(2, 3, ( Arg, arg)) , HPX_FWD_ARGS(2, 4, ( Arg, arg)) , HPX_FWD_ARGS(2, 5, ( Arg, arg)) , HPX_FWD_ARGS(2, 6, ( Arg, arg)) , HPX_FWD_ARGS(2, 7, ( Arg, arg)) , HPX_FWD_ARGS(2, 8, ( Arg, arg)))
      : apply_logger_("deferred_packaged_task::apply"),
        closure_(boost::bind(
          &deferred_packaged_task::template invoke9<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6 , Arg7 , Arg8>,
            this_(), naming::id_type(gid, naming::id_type::unmanaged),
            HPX_FORWARD_ARGS(2, 0, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 1, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 2, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 3, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 4, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 5, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 6, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 7, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 8, ( Arg, arg))))
    {
        LLCO_(info) << "deferred_packaged_task::deferred_packaged_task("
                    << hpx::actions::detail::get_action_name<Action>()
                    << ", "
                    << gid
                    << ") args(" << (9 + 1) << ")";
    }
    template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8>
    deferred_packaged_task(naming::id_type const& gid,
            HPX_FWD_ARGS(2, 0, ( Arg, arg)) , HPX_FWD_ARGS(2, 1, ( Arg, arg)) , HPX_FWD_ARGS(2, 2, ( Arg, arg)) , HPX_FWD_ARGS(2, 3, ( Arg, arg)) , HPX_FWD_ARGS(2, 4, ( Arg, arg)) , HPX_FWD_ARGS(2, 5, ( Arg, arg)) , HPX_FWD_ARGS(2, 6, ( Arg, arg)) , HPX_FWD_ARGS(2, 7, ( Arg, arg)) , HPX_FWD_ARGS(2, 8, ( Arg, arg)))
      : apply_logger_("deferred_packaged_task::apply"),
        closure_(boost::bind(
          &deferred_packaged_task::template invoke9<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6 , Arg7 , Arg8>,
            this_(), gid,
            HPX_FORWARD_ARGS(2, 0, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 1, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 2, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 3, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 4, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 5, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 6, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 7, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 8, ( Arg, arg))))
    {
        LLCO_(info) << "deferred_packaged_task::deferred_packaged_task("
                    << hpx::actions::detail::get_action_name<Action>()
                    << ", "
                    << gid
                    << ") args(" << (9 + 1) << ")";
    }
    template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9>
    void apply(naming::id_type const& gid,
        HPX_FWD_ARGS(2, 0, ( Arg, arg)) , HPX_FWD_ARGS(2, 1, ( Arg, arg)) , HPX_FWD_ARGS(2, 2, ( Arg, arg)) , HPX_FWD_ARGS(2, 3, ( Arg, arg)) , HPX_FWD_ARGS(2, 4, ( Arg, arg)) , HPX_FWD_ARGS(2, 5, ( Arg, arg)) , HPX_FWD_ARGS(2, 6, ( Arg, arg)) , HPX_FWD_ARGS(2, 7, ( Arg, arg)) , HPX_FWD_ARGS(2, 8, ( Arg, arg)) , HPX_FWD_ARGS(2, 9, ( Arg, arg)))
    {
        util::block_profiler_wrapper<deferred_packaged_task_tag> bp(apply_logger_);
        hpx::apply_c<Action>(
            this->get_gid(), gid, HPX_FORWARD_ARGS(2, 0, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 1, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 2, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 3, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 4, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 5, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 6, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 7, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 8, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 9, ( Arg, arg)));
    }
private:
    template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9>
    static void invoke10(
        hpx::lcos::deferred_packaged_task<Action,Result> *th,
        naming::id_type const& gid,
        HPX_FWD_ARGS(2, 0, ( Arg, arg)) , HPX_FWD_ARGS(2, 1, ( Arg, arg)) , HPX_FWD_ARGS(2, 2, ( Arg, arg)) , HPX_FWD_ARGS(2, 3, ( Arg, arg)) , HPX_FWD_ARGS(2, 4, ( Arg, arg)) , HPX_FWD_ARGS(2, 5, ( Arg, arg)) , HPX_FWD_ARGS(2, 6, ( Arg, arg)) , HPX_FWD_ARGS(2, 7, ( Arg, arg)) , HPX_FWD_ARGS(2, 8, ( Arg, arg)) , HPX_FWD_ARGS(2, 9, ( Arg, arg)))
    {
        if (!((*th->impl_)->is_ready()))
            th->apply(gid, HPX_FORWARD_ARGS(2, 0, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 1, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 2, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 3, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 4, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 5, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 6, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 7, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 8, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 9, ( Arg, arg)));
    }
public:
    template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9>
    deferred_packaged_task(naming::gid_type const& gid,
            HPX_FWD_ARGS(2, 0, ( Arg, arg)) , HPX_FWD_ARGS(2, 1, ( Arg, arg)) , HPX_FWD_ARGS(2, 2, ( Arg, arg)) , HPX_FWD_ARGS(2, 3, ( Arg, arg)) , HPX_FWD_ARGS(2, 4, ( Arg, arg)) , HPX_FWD_ARGS(2, 5, ( Arg, arg)) , HPX_FWD_ARGS(2, 6, ( Arg, arg)) , HPX_FWD_ARGS(2, 7, ( Arg, arg)) , HPX_FWD_ARGS(2, 8, ( Arg, arg)) , HPX_FWD_ARGS(2, 9, ( Arg, arg)))
      : apply_logger_("deferred_packaged_task::apply"),
        closure_(boost::bind(
          &deferred_packaged_task::template invoke10<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6 , Arg7 , Arg8 , Arg9>,
            this_(), naming::id_type(gid, naming::id_type::unmanaged),
            HPX_FORWARD_ARGS(2, 0, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 1, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 2, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 3, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 4, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 5, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 6, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 7, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 8, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 9, ( Arg, arg))))
    {
        LLCO_(info) << "deferred_packaged_task::deferred_packaged_task("
                    << hpx::actions::detail::get_action_name<Action>()
                    << ", "
                    << gid
                    << ") args(" << (10 + 1) << ")";
    }
    template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9>
    deferred_packaged_task(naming::id_type const& gid,
            HPX_FWD_ARGS(2, 0, ( Arg, arg)) , HPX_FWD_ARGS(2, 1, ( Arg, arg)) , HPX_FWD_ARGS(2, 2, ( Arg, arg)) , HPX_FWD_ARGS(2, 3, ( Arg, arg)) , HPX_FWD_ARGS(2, 4, ( Arg, arg)) , HPX_FWD_ARGS(2, 5, ( Arg, arg)) , HPX_FWD_ARGS(2, 6, ( Arg, arg)) , HPX_FWD_ARGS(2, 7, ( Arg, arg)) , HPX_FWD_ARGS(2, 8, ( Arg, arg)) , HPX_FWD_ARGS(2, 9, ( Arg, arg)))
      : apply_logger_("deferred_packaged_task::apply"),
        closure_(boost::bind(
          &deferred_packaged_task::template invoke10<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6 , Arg7 , Arg8 , Arg9>,
            this_(), gid,
            HPX_FORWARD_ARGS(2, 0, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 1, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 2, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 3, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 4, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 5, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 6, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 7, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 8, ( Arg, arg)) , HPX_FORWARD_ARGS(2, 9, ( Arg, arg))))
    {
        LLCO_(info) << "deferred_packaged_task::deferred_packaged_task("
                    << hpx::actions::detail::get_action_name<Action>()
                    << ", "
                    << gid
                    << ") args(" << (10 + 1) << ")";
    }
