// Copyright (c) 2007-2013 Hartmut Kaiser
// Copyright (c) 2012-2013 Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This file has been automatically generated using the Boost.Wave tool.
// Do not edit manually.



    template <typename IdType, typename Arg0>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                arguments_type::size_value == 1>,
            boost::is_same<IdType, naming::id_type>,
            boost::is_same<local_result_type, void> >
    >::type
    operator()(BOOST_SCOPED_ENUM(launch) policy, IdType const& id,
        BOOST_FWD_REF(Arg0) arg0, error_code& ec = throws) const
    {
        hpx::async<action>(policy, id,
            boost::forward<Arg0>( arg0 )).get(ec);
    }
    template <typename IdType, typename Arg0>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                arguments_type::size_value == 1>,
            boost::is_same<IdType, naming::id_type>,
            boost::is_same<local_result_type, void> >
    >::type
    operator()(IdType const& id, BOOST_FWD_REF(Arg0) arg0,
        error_code& ec = throws) const
    {
        hpx::async<action>(launch::sync, id,
            boost::forward<Arg0>( arg0 )).get(ec);
    }

    template <typename LocalResult>
    struct sync_invoke_1
    {
        template <typename Arg0>
        BOOST_FORCEINLINE static LocalResult call(
            boost::mpl::false_, BOOST_SCOPED_ENUM(launch) policy,
            naming::id_type const& id, BOOST_FWD_REF(Arg0) arg0,
            error_code& ec)
        {
            return hpx::async<action>(policy, id,
                boost::forward<Arg0>( arg0 )).move(ec);
        }
        template <typename Arg0>
        BOOST_FORCEINLINE static LocalResult call(
            boost::mpl::true_, BOOST_SCOPED_ENUM(launch) policy,
            naming::id_type const& id, BOOST_FWD_REF(Arg0) arg0,
            error_code& ec)
        {
            return hpx::async<action>(policy, id,
                boost::forward<Arg0>( arg0 ));
        }
    };
    template <typename IdType, typename Arg0>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                arguments_type::size_value == 1>,
            boost::is_same<IdType, naming::id_type>,
            boost::mpl::not_<boost::is_same<local_result_type, void> > >,
        local_result_type
    >::type
    operator()(BOOST_SCOPED_ENUM(launch) policy, IdType const& id,
        BOOST_FWD_REF(Arg0) arg0, error_code& ec = throws) const
    {
        return sync_invoke_1<local_result_type>::call(
            is_future_pred(), policy, id, boost::forward<Arg0>( arg0 ), ec);
    }
    template <typename IdType, typename Arg0>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                arguments_type::size_value == 1>,
            boost::is_same<IdType, naming::id_type>,
            boost::mpl::not_<boost::is_same<local_result_type, void> > >,
        local_result_type
    >::type
    operator()(IdType const& id, BOOST_FWD_REF(Arg0) arg0,
        error_code& ec = throws) const
    {
        return sync_invoke_1<local_result_type>::call(
            is_future_pred(), launch::sync, id, boost::forward<Arg0>( arg0 ), ec);
    }

    template <typename IdType, typename Arg0 , typename Arg1>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                arguments_type::size_value == 2>,
            boost::is_same<IdType, naming::id_type>,
            boost::is_same<local_result_type, void> >
    >::type
    operator()(BOOST_SCOPED_ENUM(launch) policy, IdType const& id,
        BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1, error_code& ec = throws) const
    {
        hpx::async<action>(policy, id,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 )).get(ec);
    }
    template <typename IdType, typename Arg0 , typename Arg1>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                arguments_type::size_value == 2>,
            boost::is_same<IdType, naming::id_type>,
            boost::is_same<local_result_type, void> >
    >::type
    operator()(IdType const& id, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1,
        error_code& ec = throws) const
    {
        hpx::async<action>(launch::sync, id,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 )).get(ec);
    }

    template <typename LocalResult>
    struct sync_invoke_2
    {
        template <typename Arg0 , typename Arg1>
        BOOST_FORCEINLINE static LocalResult call(
            boost::mpl::false_, BOOST_SCOPED_ENUM(launch) policy,
            naming::id_type const& id, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1,
            error_code& ec)
        {
            return hpx::async<action>(policy, id,
                boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 )).move(ec);
        }
        template <typename Arg0 , typename Arg1>
        BOOST_FORCEINLINE static LocalResult call(
            boost::mpl::true_, BOOST_SCOPED_ENUM(launch) policy,
            naming::id_type const& id, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1,
            error_code& ec)
        {
            return hpx::async<action>(policy, id,
                boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ));
        }
    };
    template <typename IdType, typename Arg0 , typename Arg1>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                arguments_type::size_value == 2>,
            boost::is_same<IdType, naming::id_type>,
            boost::mpl::not_<boost::is_same<local_result_type, void> > >,
        local_result_type
    >::type
    operator()(BOOST_SCOPED_ENUM(launch) policy, IdType const& id,
        BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1, error_code& ec = throws) const
    {
        return sync_invoke_2<local_result_type>::call(
            is_future_pred(), policy, id, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ), ec);
    }
    template <typename IdType, typename Arg0 , typename Arg1>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                arguments_type::size_value == 2>,
            boost::is_same<IdType, naming::id_type>,
            boost::mpl::not_<boost::is_same<local_result_type, void> > >,
        local_result_type
    >::type
    operator()(IdType const& id, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1,
        error_code& ec = throws) const
    {
        return sync_invoke_2<local_result_type>::call(
            is_future_pred(), launch::sync, id, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ), ec);
    }

    template <typename IdType, typename Arg0 , typename Arg1 , typename Arg2>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                arguments_type::size_value == 3>,
            boost::is_same<IdType, naming::id_type>,
            boost::is_same<local_result_type, void> >
    >::type
    operator()(BOOST_SCOPED_ENUM(launch) policy, IdType const& id,
        BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2, error_code& ec = throws) const
    {
        hpx::async<action>(policy, id,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 )).get(ec);
    }
    template <typename IdType, typename Arg0 , typename Arg1 , typename Arg2>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                arguments_type::size_value == 3>,
            boost::is_same<IdType, naming::id_type>,
            boost::is_same<local_result_type, void> >
    >::type
    operator()(IdType const& id, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2,
        error_code& ec = throws) const
    {
        hpx::async<action>(launch::sync, id,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 )).get(ec);
    }

    template <typename LocalResult>
    struct sync_invoke_3
    {
        template <typename Arg0 , typename Arg1 , typename Arg2>
        BOOST_FORCEINLINE static LocalResult call(
            boost::mpl::false_, BOOST_SCOPED_ENUM(launch) policy,
            naming::id_type const& id, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2,
            error_code& ec)
        {
            return hpx::async<action>(policy, id,
                boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 )).move(ec);
        }
        template <typename Arg0 , typename Arg1 , typename Arg2>
        BOOST_FORCEINLINE static LocalResult call(
            boost::mpl::true_, BOOST_SCOPED_ENUM(launch) policy,
            naming::id_type const& id, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2,
            error_code& ec)
        {
            return hpx::async<action>(policy, id,
                boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ));
        }
    };
    template <typename IdType, typename Arg0 , typename Arg1 , typename Arg2>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                arguments_type::size_value == 3>,
            boost::is_same<IdType, naming::id_type>,
            boost::mpl::not_<boost::is_same<local_result_type, void> > >,
        local_result_type
    >::type
    operator()(BOOST_SCOPED_ENUM(launch) policy, IdType const& id,
        BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2, error_code& ec = throws) const
    {
        return sync_invoke_3<local_result_type>::call(
            is_future_pred(), policy, id, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ), ec);
    }
    template <typename IdType, typename Arg0 , typename Arg1 , typename Arg2>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                arguments_type::size_value == 3>,
            boost::is_same<IdType, naming::id_type>,
            boost::mpl::not_<boost::is_same<local_result_type, void> > >,
        local_result_type
    >::type
    operator()(IdType const& id, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2,
        error_code& ec = throws) const
    {
        return sync_invoke_3<local_result_type>::call(
            is_future_pred(), launch::sync, id, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ), ec);
    }

    template <typename IdType, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                arguments_type::size_value == 4>,
            boost::is_same<IdType, naming::id_type>,
            boost::is_same<local_result_type, void> >
    >::type
    operator()(BOOST_SCOPED_ENUM(launch) policy, IdType const& id,
        BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3, error_code& ec = throws) const
    {
        hpx::async<action>(policy, id,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 )).get(ec);
    }
    template <typename IdType, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                arguments_type::size_value == 4>,
            boost::is_same<IdType, naming::id_type>,
            boost::is_same<local_result_type, void> >
    >::type
    operator()(IdType const& id, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3,
        error_code& ec = throws) const
    {
        hpx::async<action>(launch::sync, id,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 )).get(ec);
    }

    template <typename LocalResult>
    struct sync_invoke_4
    {
        template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3>
        BOOST_FORCEINLINE static LocalResult call(
            boost::mpl::false_, BOOST_SCOPED_ENUM(launch) policy,
            naming::id_type const& id, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3,
            error_code& ec)
        {
            return hpx::async<action>(policy, id,
                boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 )).move(ec);
        }
        template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3>
        BOOST_FORCEINLINE static LocalResult call(
            boost::mpl::true_, BOOST_SCOPED_ENUM(launch) policy,
            naming::id_type const& id, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3,
            error_code& ec)
        {
            return hpx::async<action>(policy, id,
                boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ));
        }
    };
    template <typename IdType, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                arguments_type::size_value == 4>,
            boost::is_same<IdType, naming::id_type>,
            boost::mpl::not_<boost::is_same<local_result_type, void> > >,
        local_result_type
    >::type
    operator()(BOOST_SCOPED_ENUM(launch) policy, IdType const& id,
        BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3, error_code& ec = throws) const
    {
        return sync_invoke_4<local_result_type>::call(
            is_future_pred(), policy, id, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ), ec);
    }
    template <typename IdType, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                arguments_type::size_value == 4>,
            boost::is_same<IdType, naming::id_type>,
            boost::mpl::not_<boost::is_same<local_result_type, void> > >,
        local_result_type
    >::type
    operator()(IdType const& id, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3,
        error_code& ec = throws) const
    {
        return sync_invoke_4<local_result_type>::call(
            is_future_pred(), launch::sync, id, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ), ec);
    }

    template <typename IdType, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                arguments_type::size_value == 5>,
            boost::is_same<IdType, naming::id_type>,
            boost::is_same<local_result_type, void> >
    >::type
    operator()(BOOST_SCOPED_ENUM(launch) policy, IdType const& id,
        BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4, error_code& ec = throws) const
    {
        hpx::async<action>(policy, id,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 )).get(ec);
    }
    template <typename IdType, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                arguments_type::size_value == 5>,
            boost::is_same<IdType, naming::id_type>,
            boost::is_same<local_result_type, void> >
    >::type
    operator()(IdType const& id, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4,
        error_code& ec = throws) const
    {
        hpx::async<action>(launch::sync, id,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 )).get(ec);
    }

    template <typename LocalResult>
    struct sync_invoke_5
    {
        template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4>
        BOOST_FORCEINLINE static LocalResult call(
            boost::mpl::false_, BOOST_SCOPED_ENUM(launch) policy,
            naming::id_type const& id, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4,
            error_code& ec)
        {
            return hpx::async<action>(policy, id,
                boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 )).move(ec);
        }
        template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4>
        BOOST_FORCEINLINE static LocalResult call(
            boost::mpl::true_, BOOST_SCOPED_ENUM(launch) policy,
            naming::id_type const& id, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4,
            error_code& ec)
        {
            return hpx::async<action>(policy, id,
                boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ));
        }
    };
    template <typename IdType, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                arguments_type::size_value == 5>,
            boost::is_same<IdType, naming::id_type>,
            boost::mpl::not_<boost::is_same<local_result_type, void> > >,
        local_result_type
    >::type
    operator()(BOOST_SCOPED_ENUM(launch) policy, IdType const& id,
        BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4, error_code& ec = throws) const
    {
        return sync_invoke_5<local_result_type>::call(
            is_future_pred(), policy, id, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ), ec);
    }
    template <typename IdType, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                arguments_type::size_value == 5>,
            boost::is_same<IdType, naming::id_type>,
            boost::mpl::not_<boost::is_same<local_result_type, void> > >,
        local_result_type
    >::type
    operator()(IdType const& id, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4,
        error_code& ec = throws) const
    {
        return sync_invoke_5<local_result_type>::call(
            is_future_pred(), launch::sync, id, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ), ec);
    }

    template <typename IdType, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                arguments_type::size_value == 6>,
            boost::is_same<IdType, naming::id_type>,
            boost::is_same<local_result_type, void> >
    >::type
    operator()(BOOST_SCOPED_ENUM(launch) policy, IdType const& id,
        BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5, error_code& ec = throws) const
    {
        hpx::async<action>(policy, id,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 )).get(ec);
    }
    template <typename IdType, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                arguments_type::size_value == 6>,
            boost::is_same<IdType, naming::id_type>,
            boost::is_same<local_result_type, void> >
    >::type
    operator()(IdType const& id, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5,
        error_code& ec = throws) const
    {
        hpx::async<action>(launch::sync, id,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 )).get(ec);
    }

    template <typename LocalResult>
    struct sync_invoke_6
    {
        template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5>
        BOOST_FORCEINLINE static LocalResult call(
            boost::mpl::false_, BOOST_SCOPED_ENUM(launch) policy,
            naming::id_type const& id, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5,
            error_code& ec)
        {
            return hpx::async<action>(policy, id,
                boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 )).move(ec);
        }
        template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5>
        BOOST_FORCEINLINE static LocalResult call(
            boost::mpl::true_, BOOST_SCOPED_ENUM(launch) policy,
            naming::id_type const& id, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5,
            error_code& ec)
        {
            return hpx::async<action>(policy, id,
                boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ));
        }
    };
    template <typename IdType, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                arguments_type::size_value == 6>,
            boost::is_same<IdType, naming::id_type>,
            boost::mpl::not_<boost::is_same<local_result_type, void> > >,
        local_result_type
    >::type
    operator()(BOOST_SCOPED_ENUM(launch) policy, IdType const& id,
        BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5, error_code& ec = throws) const
    {
        return sync_invoke_6<local_result_type>::call(
            is_future_pred(), policy, id, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ), ec);
    }
    template <typename IdType, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                arguments_type::size_value == 6>,
            boost::is_same<IdType, naming::id_type>,
            boost::mpl::not_<boost::is_same<local_result_type, void> > >,
        local_result_type
    >::type
    operator()(IdType const& id, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5,
        error_code& ec = throws) const
    {
        return sync_invoke_6<local_result_type>::call(
            is_future_pred(), launch::sync, id, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ), ec);
    }

    template <typename IdType, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                arguments_type::size_value == 7>,
            boost::is_same<IdType, naming::id_type>,
            boost::is_same<local_result_type, void> >
    >::type
    operator()(BOOST_SCOPED_ENUM(launch) policy, IdType const& id,
        BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6, error_code& ec = throws) const
    {
        hpx::async<action>(policy, id,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 )).get(ec);
    }
    template <typename IdType, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                arguments_type::size_value == 7>,
            boost::is_same<IdType, naming::id_type>,
            boost::is_same<local_result_type, void> >
    >::type
    operator()(IdType const& id, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6,
        error_code& ec = throws) const
    {
        hpx::async<action>(launch::sync, id,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 )).get(ec);
    }

    template <typename LocalResult>
    struct sync_invoke_7
    {
        template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6>
        BOOST_FORCEINLINE static LocalResult call(
            boost::mpl::false_, BOOST_SCOPED_ENUM(launch) policy,
            naming::id_type const& id, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6,
            error_code& ec)
        {
            return hpx::async<action>(policy, id,
                boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 )).move(ec);
        }
        template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6>
        BOOST_FORCEINLINE static LocalResult call(
            boost::mpl::true_, BOOST_SCOPED_ENUM(launch) policy,
            naming::id_type const& id, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6,
            error_code& ec)
        {
            return hpx::async<action>(policy, id,
                boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ));
        }
    };
    template <typename IdType, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                arguments_type::size_value == 7>,
            boost::is_same<IdType, naming::id_type>,
            boost::mpl::not_<boost::is_same<local_result_type, void> > >,
        local_result_type
    >::type
    operator()(BOOST_SCOPED_ENUM(launch) policy, IdType const& id,
        BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6, error_code& ec = throws) const
    {
        return sync_invoke_7<local_result_type>::call(
            is_future_pred(), policy, id, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ), ec);
    }
    template <typename IdType, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                arguments_type::size_value == 7>,
            boost::is_same<IdType, naming::id_type>,
            boost::mpl::not_<boost::is_same<local_result_type, void> > >,
        local_result_type
    >::type
    operator()(IdType const& id, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6,
        error_code& ec = throws) const
    {
        return sync_invoke_7<local_result_type>::call(
            is_future_pred(), launch::sync, id, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ), ec);
    }

    template <typename IdType, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                arguments_type::size_value == 8>,
            boost::is_same<IdType, naming::id_type>,
            boost::is_same<local_result_type, void> >
    >::type
    operator()(BOOST_SCOPED_ENUM(launch) policy, IdType const& id,
        BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7, error_code& ec = throws) const
    {
        hpx::async<action>(policy, id,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 )).get(ec);
    }
    template <typename IdType, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                arguments_type::size_value == 8>,
            boost::is_same<IdType, naming::id_type>,
            boost::is_same<local_result_type, void> >
    >::type
    operator()(IdType const& id, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7,
        error_code& ec = throws) const
    {
        hpx::async<action>(launch::sync, id,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 )).get(ec);
    }

    template <typename LocalResult>
    struct sync_invoke_8
    {
        template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7>
        BOOST_FORCEINLINE static LocalResult call(
            boost::mpl::false_, BOOST_SCOPED_ENUM(launch) policy,
            naming::id_type const& id, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7,
            error_code& ec)
        {
            return hpx::async<action>(policy, id,
                boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 )).move(ec);
        }
        template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7>
        BOOST_FORCEINLINE static LocalResult call(
            boost::mpl::true_, BOOST_SCOPED_ENUM(launch) policy,
            naming::id_type const& id, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7,
            error_code& ec)
        {
            return hpx::async<action>(policy, id,
                boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ));
        }
    };
    template <typename IdType, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                arguments_type::size_value == 8>,
            boost::is_same<IdType, naming::id_type>,
            boost::mpl::not_<boost::is_same<local_result_type, void> > >,
        local_result_type
    >::type
    operator()(BOOST_SCOPED_ENUM(launch) policy, IdType const& id,
        BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7, error_code& ec = throws) const
    {
        return sync_invoke_8<local_result_type>::call(
            is_future_pred(), policy, id, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ), ec);
    }
    template <typename IdType, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                arguments_type::size_value == 8>,
            boost::is_same<IdType, naming::id_type>,
            boost::mpl::not_<boost::is_same<local_result_type, void> > >,
        local_result_type
    >::type
    operator()(IdType const& id, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7,
        error_code& ec = throws) const
    {
        return sync_invoke_8<local_result_type>::call(
            is_future_pred(), launch::sync, id, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ), ec);
    }

    template <typename IdType, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                arguments_type::size_value == 9>,
            boost::is_same<IdType, naming::id_type>,
            boost::is_same<local_result_type, void> >
    >::type
    operator()(BOOST_SCOPED_ENUM(launch) policy, IdType const& id,
        BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8, error_code& ec = throws) const
    {
        hpx::async<action>(policy, id,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 )).get(ec);
    }
    template <typename IdType, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                arguments_type::size_value == 9>,
            boost::is_same<IdType, naming::id_type>,
            boost::is_same<local_result_type, void> >
    >::type
    operator()(IdType const& id, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8,
        error_code& ec = throws) const
    {
        hpx::async<action>(launch::sync, id,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 )).get(ec);
    }

    template <typename LocalResult>
    struct sync_invoke_9
    {
        template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8>
        BOOST_FORCEINLINE static LocalResult call(
            boost::mpl::false_, BOOST_SCOPED_ENUM(launch) policy,
            naming::id_type const& id, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8,
            error_code& ec)
        {
            return hpx::async<action>(policy, id,
                boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 )).move(ec);
        }
        template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8>
        BOOST_FORCEINLINE static LocalResult call(
            boost::mpl::true_, BOOST_SCOPED_ENUM(launch) policy,
            naming::id_type const& id, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8,
            error_code& ec)
        {
            return hpx::async<action>(policy, id,
                boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ));
        }
    };
    template <typename IdType, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                arguments_type::size_value == 9>,
            boost::is_same<IdType, naming::id_type>,
            boost::mpl::not_<boost::is_same<local_result_type, void> > >,
        local_result_type
    >::type
    operator()(BOOST_SCOPED_ENUM(launch) policy, IdType const& id,
        BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8, error_code& ec = throws) const
    {
        return sync_invoke_9<local_result_type>::call(
            is_future_pred(), policy, id, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ), ec);
    }
    template <typename IdType, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                arguments_type::size_value == 9>,
            boost::is_same<IdType, naming::id_type>,
            boost::mpl::not_<boost::is_same<local_result_type, void> > >,
        local_result_type
    >::type
    operator()(IdType const& id, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8,
        error_code& ec = throws) const
    {
        return sync_invoke_9<local_result_type>::call(
            is_future_pred(), launch::sync, id, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ), ec);
    }

    template <typename IdType, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                arguments_type::size_value == 10>,
            boost::is_same<IdType, naming::id_type>,
            boost::is_same<local_result_type, void> >
    >::type
    operator()(BOOST_SCOPED_ENUM(launch) policy, IdType const& id,
        BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9, error_code& ec = throws) const
    {
        hpx::async<action>(policy, id,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ) , boost::forward<Arg9>( arg9 )).get(ec);
    }
    template <typename IdType, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                arguments_type::size_value == 10>,
            boost::is_same<IdType, naming::id_type>,
            boost::is_same<local_result_type, void> >
    >::type
    operator()(IdType const& id, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9,
        error_code& ec = throws) const
    {
        hpx::async<action>(launch::sync, id,
            boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ) , boost::forward<Arg9>( arg9 )).get(ec);
    }

    template <typename LocalResult>
    struct sync_invoke_10
    {
        template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9>
        BOOST_FORCEINLINE static LocalResult call(
            boost::mpl::false_, BOOST_SCOPED_ENUM(launch) policy,
            naming::id_type const& id, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9,
            error_code& ec)
        {
            return hpx::async<action>(policy, id,
                boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ) , boost::forward<Arg9>( arg9 )).move(ec);
        }
        template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9>
        BOOST_FORCEINLINE static LocalResult call(
            boost::mpl::true_, BOOST_SCOPED_ENUM(launch) policy,
            naming::id_type const& id, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9,
            error_code& ec)
        {
            return hpx::async<action>(policy, id,
                boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ) , boost::forward<Arg9>( arg9 ));
        }
    };
    template <typename IdType, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                arguments_type::size_value == 10>,
            boost::is_same<IdType, naming::id_type>,
            boost::mpl::not_<boost::is_same<local_result_type, void> > >,
        local_result_type
    >::type
    operator()(BOOST_SCOPED_ENUM(launch) policy, IdType const& id,
        BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9, error_code& ec = throws) const
    {
        return sync_invoke_10<local_result_type>::call(
            is_future_pred(), policy, id, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ) , boost::forward<Arg9>( arg9 ), ec);
    }
    template <typename IdType, typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                arguments_type::size_value == 10>,
            boost::is_same<IdType, naming::id_type>,
            boost::mpl::not_<boost::is_same<local_result_type, void> > >,
        local_result_type
    >::type
    operator()(IdType const& id, BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9,
        error_code& ec = throws) const
    {
        return sync_invoke_10<local_result_type>::call(
            is_future_pred(), launch::sync, id, boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ) , boost::forward<Arg9>( arg9 ), ec);
    }
