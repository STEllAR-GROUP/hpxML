// Copyright (c) 2007-2013 Hartmut Kaiser
// Copyright (c) 2012-2013 Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This file has been automatically generated using the Boost.Wave tool.
// Do not edit manually.


        
namespace hpx { namespace util
{
    namespace detail
    {
        template <typename F, typename BoundArgs, typename UnboundArgs>
        struct bind_invoke_impl<
            F, BoundArgs, UnboundArgs
          , typename boost::enable_if_c<
                util::tuple_size<BoundArgs>::value == 1
            >::type
        >
        {
            typedef
                typename util::detail::result_of_or<
                    F(typename detail::bind_eval_impl< F, typename util::tuple_element< 0, BoundArgs>::type , UnboundArgs >::type)
                  , cannot_be_called
                >::type
                type;
            static BOOST_FORCEINLINE
            type call(
                F& f, BoundArgs& bound_args
              , BOOST_FWD_REF(UnboundArgs) unbound_args
            )
            {
                return util::invoke(f, detail::bind_eval<F>( util::get< 0>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ));
            }
        };
    }
    template <typename F, typename T0>
    typename boost::disable_if_c<
        traits::is_action<typename util::remove_reference<F>::type>::value
      , detail::bound<
            typename util::decay<F>::type
          , util::tuple<typename util::decay<T0>::type>
        >
    >::type
    bind(BOOST_FWD_REF(F) f, BOOST_FWD_REF(T0) t0)
    {
        typedef
            detail::bound<
                typename util::decay<F>::type
              , util::tuple<typename util::decay<T0>::type>
            >
            result_type;
        return
            result_type(
                boost::forward<F>(f)
              , util::forward_as_tuple(boost::forward<T0>( t0 ))
            );
    }
}}
namespace hpx { namespace util
{
    namespace detail
    {
        template <typename F, typename BoundArgs, typename UnboundArgs>
        struct bind_invoke_impl<
            F, BoundArgs, UnboundArgs
          , typename boost::enable_if_c<
                util::tuple_size<BoundArgs>::value == 2
            >::type
        >
        {
            typedef
                typename util::detail::result_of_or<
                    F(typename detail::bind_eval_impl< F, typename util::tuple_element< 0, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 1, BoundArgs>::type , UnboundArgs >::type)
                  , cannot_be_called
                >::type
                type;
            static BOOST_FORCEINLINE
            type call(
                F& f, BoundArgs& bound_args
              , BOOST_FWD_REF(UnboundArgs) unbound_args
            )
            {
                return util::invoke(f, detail::bind_eval<F>( util::get< 0>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 1>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ));
            }
        };
    }
    template <typename F, typename T0 , typename T1>
    typename boost::disable_if_c<
        traits::is_action<typename util::remove_reference<F>::type>::value
      , detail::bound<
            typename util::decay<F>::type
          , util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type>
        >
    >::type
    bind(BOOST_FWD_REF(F) f, BOOST_FWD_REF(T0) t0 , BOOST_FWD_REF(T1) t1)
    {
        typedef
            detail::bound<
                typename util::decay<F>::type
              , util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type>
            >
            result_type;
        return
            result_type(
                boost::forward<F>(f)
              , util::forward_as_tuple(boost::forward<T0>( t0 ) , boost::forward<T1>( t1 ))
            );
    }
}}
namespace hpx { namespace util
{
    namespace detail
    {
        template <typename F, typename BoundArgs, typename UnboundArgs>
        struct bind_invoke_impl<
            F, BoundArgs, UnboundArgs
          , typename boost::enable_if_c<
                util::tuple_size<BoundArgs>::value == 3
            >::type
        >
        {
            typedef
                typename util::detail::result_of_or<
                    F(typename detail::bind_eval_impl< F, typename util::tuple_element< 0, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 1, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 2, BoundArgs>::type , UnboundArgs >::type)
                  , cannot_be_called
                >::type
                type;
            static BOOST_FORCEINLINE
            type call(
                F& f, BoundArgs& bound_args
              , BOOST_FWD_REF(UnboundArgs) unbound_args
            )
            {
                return util::invoke(f, detail::bind_eval<F>( util::get< 0>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 1>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 2>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ));
            }
        };
    }
    template <typename F, typename T0 , typename T1 , typename T2>
    typename boost::disable_if_c<
        traits::is_action<typename util::remove_reference<F>::type>::value
      , detail::bound<
            typename util::decay<F>::type
          , util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type>
        >
    >::type
    bind(BOOST_FWD_REF(F) f, BOOST_FWD_REF(T0) t0 , BOOST_FWD_REF(T1) t1 , BOOST_FWD_REF(T2) t2)
    {
        typedef
            detail::bound<
                typename util::decay<F>::type
              , util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type>
            >
            result_type;
        return
            result_type(
                boost::forward<F>(f)
              , util::forward_as_tuple(boost::forward<T0>( t0 ) , boost::forward<T1>( t1 ) , boost::forward<T2>( t2 ))
            );
    }
}}
namespace hpx { namespace util
{
    namespace detail
    {
        template <typename F, typename BoundArgs, typename UnboundArgs>
        struct bind_invoke_impl<
            F, BoundArgs, UnboundArgs
          , typename boost::enable_if_c<
                util::tuple_size<BoundArgs>::value == 4
            >::type
        >
        {
            typedef
                typename util::detail::result_of_or<
                    F(typename detail::bind_eval_impl< F, typename util::tuple_element< 0, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 1, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 2, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 3, BoundArgs>::type , UnboundArgs >::type)
                  , cannot_be_called
                >::type
                type;
            static BOOST_FORCEINLINE
            type call(
                F& f, BoundArgs& bound_args
              , BOOST_FWD_REF(UnboundArgs) unbound_args
            )
            {
                return util::invoke(f, detail::bind_eval<F>( util::get< 0>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 1>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 2>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 3>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ));
            }
        };
    }
    template <typename F, typename T0 , typename T1 , typename T2 , typename T3>
    typename boost::disable_if_c<
        traits::is_action<typename util::remove_reference<F>::type>::value
      , detail::bound<
            typename util::decay<F>::type
          , util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type>
        >
    >::type
    bind(BOOST_FWD_REF(F) f, BOOST_FWD_REF(T0) t0 , BOOST_FWD_REF(T1) t1 , BOOST_FWD_REF(T2) t2 , BOOST_FWD_REF(T3) t3)
    {
        typedef
            detail::bound<
                typename util::decay<F>::type
              , util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type>
            >
            result_type;
        return
            result_type(
                boost::forward<F>(f)
              , util::forward_as_tuple(boost::forward<T0>( t0 ) , boost::forward<T1>( t1 ) , boost::forward<T2>( t2 ) , boost::forward<T3>( t3 ))
            );
    }
}}
namespace hpx { namespace util
{
    namespace detail
    {
        template <typename F, typename BoundArgs, typename UnboundArgs>
        struct bind_invoke_impl<
            F, BoundArgs, UnboundArgs
          , typename boost::enable_if_c<
                util::tuple_size<BoundArgs>::value == 5
            >::type
        >
        {
            typedef
                typename util::detail::result_of_or<
                    F(typename detail::bind_eval_impl< F, typename util::tuple_element< 0, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 1, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 2, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 3, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 4, BoundArgs>::type , UnboundArgs >::type)
                  , cannot_be_called
                >::type
                type;
            static BOOST_FORCEINLINE
            type call(
                F& f, BoundArgs& bound_args
              , BOOST_FWD_REF(UnboundArgs) unbound_args
            )
            {
                return util::invoke(f, detail::bind_eval<F>( util::get< 0>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 1>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 2>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 3>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 4>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ));
            }
        };
    }
    template <typename F, typename T0 , typename T1 , typename T2 , typename T3 , typename T4>
    typename boost::disable_if_c<
        traits::is_action<typename util::remove_reference<F>::type>::value
      , detail::bound<
            typename util::decay<F>::type
          , util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type>
        >
    >::type
    bind(BOOST_FWD_REF(F) f, BOOST_FWD_REF(T0) t0 , BOOST_FWD_REF(T1) t1 , BOOST_FWD_REF(T2) t2 , BOOST_FWD_REF(T3) t3 , BOOST_FWD_REF(T4) t4)
    {
        typedef
            detail::bound<
                typename util::decay<F>::type
              , util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type>
            >
            result_type;
        return
            result_type(
                boost::forward<F>(f)
              , util::forward_as_tuple(boost::forward<T0>( t0 ) , boost::forward<T1>( t1 ) , boost::forward<T2>( t2 ) , boost::forward<T3>( t3 ) , boost::forward<T4>( t4 ))
            );
    }
}}
namespace hpx { namespace util
{
    namespace detail
    {
        template <typename F, typename BoundArgs, typename UnboundArgs>
        struct bind_invoke_impl<
            F, BoundArgs, UnboundArgs
          , typename boost::enable_if_c<
                util::tuple_size<BoundArgs>::value == 6
            >::type
        >
        {
            typedef
                typename util::detail::result_of_or<
                    F(typename detail::bind_eval_impl< F, typename util::tuple_element< 0, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 1, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 2, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 3, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 4, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 5, BoundArgs>::type , UnboundArgs >::type)
                  , cannot_be_called
                >::type
                type;
            static BOOST_FORCEINLINE
            type call(
                F& f, BoundArgs& bound_args
              , BOOST_FWD_REF(UnboundArgs) unbound_args
            )
            {
                return util::invoke(f, detail::bind_eval<F>( util::get< 0>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 1>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 2>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 3>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 4>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 5>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ));
            }
        };
    }
    template <typename F, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5>
    typename boost::disable_if_c<
        traits::is_action<typename util::remove_reference<F>::type>::value
      , detail::bound<
            typename util::decay<F>::type
          , util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type>
        >
    >::type
    bind(BOOST_FWD_REF(F) f, BOOST_FWD_REF(T0) t0 , BOOST_FWD_REF(T1) t1 , BOOST_FWD_REF(T2) t2 , BOOST_FWD_REF(T3) t3 , BOOST_FWD_REF(T4) t4 , BOOST_FWD_REF(T5) t5)
    {
        typedef
            detail::bound<
                typename util::decay<F>::type
              , util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type>
            >
            result_type;
        return
            result_type(
                boost::forward<F>(f)
              , util::forward_as_tuple(boost::forward<T0>( t0 ) , boost::forward<T1>( t1 ) , boost::forward<T2>( t2 ) , boost::forward<T3>( t3 ) , boost::forward<T4>( t4 ) , boost::forward<T5>( t5 ))
            );
    }
}}
namespace hpx { namespace util
{
    namespace detail
    {
        template <typename F, typename BoundArgs, typename UnboundArgs>
        struct bind_invoke_impl<
            F, BoundArgs, UnboundArgs
          , typename boost::enable_if_c<
                util::tuple_size<BoundArgs>::value == 7
            >::type
        >
        {
            typedef
                typename util::detail::result_of_or<
                    F(typename detail::bind_eval_impl< F, typename util::tuple_element< 0, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 1, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 2, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 3, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 4, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 5, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 6, BoundArgs>::type , UnboundArgs >::type)
                  , cannot_be_called
                >::type
                type;
            static BOOST_FORCEINLINE
            type call(
                F& f, BoundArgs& bound_args
              , BOOST_FWD_REF(UnboundArgs) unbound_args
            )
            {
                return util::invoke(f, detail::bind_eval<F>( util::get< 0>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 1>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 2>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 3>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 4>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 5>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 6>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ));
            }
        };
    }
    template <typename F, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6>
    typename boost::disable_if_c<
        traits::is_action<typename util::remove_reference<F>::type>::value
      , detail::bound<
            typename util::decay<F>::type
          , util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type>
        >
    >::type
    bind(BOOST_FWD_REF(F) f, BOOST_FWD_REF(T0) t0 , BOOST_FWD_REF(T1) t1 , BOOST_FWD_REF(T2) t2 , BOOST_FWD_REF(T3) t3 , BOOST_FWD_REF(T4) t4 , BOOST_FWD_REF(T5) t5 , BOOST_FWD_REF(T6) t6)
    {
        typedef
            detail::bound<
                typename util::decay<F>::type
              , util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type>
            >
            result_type;
        return
            result_type(
                boost::forward<F>(f)
              , util::forward_as_tuple(boost::forward<T0>( t0 ) , boost::forward<T1>( t1 ) , boost::forward<T2>( t2 ) , boost::forward<T3>( t3 ) , boost::forward<T4>( t4 ) , boost::forward<T5>( t5 ) , boost::forward<T6>( t6 ))
            );
    }
}}
namespace hpx { namespace util
{
    namespace detail
    {
        template <typename F, typename BoundArgs, typename UnboundArgs>
        struct bind_invoke_impl<
            F, BoundArgs, UnboundArgs
          , typename boost::enable_if_c<
                util::tuple_size<BoundArgs>::value == 8
            >::type
        >
        {
            typedef
                typename util::detail::result_of_or<
                    F(typename detail::bind_eval_impl< F, typename util::tuple_element< 0, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 1, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 2, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 3, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 4, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 5, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 6, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 7, BoundArgs>::type , UnboundArgs >::type)
                  , cannot_be_called
                >::type
                type;
            static BOOST_FORCEINLINE
            type call(
                F& f, BoundArgs& bound_args
              , BOOST_FWD_REF(UnboundArgs) unbound_args
            )
            {
                return util::invoke(f, detail::bind_eval<F>( util::get< 0>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 1>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 2>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 3>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 4>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 5>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 6>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 7>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ));
            }
        };
    }
    template <typename F, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7>
    typename boost::disable_if_c<
        traits::is_action<typename util::remove_reference<F>::type>::value
      , detail::bound<
            typename util::decay<F>::type
          , util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type>
        >
    >::type
    bind(BOOST_FWD_REF(F) f, BOOST_FWD_REF(T0) t0 , BOOST_FWD_REF(T1) t1 , BOOST_FWD_REF(T2) t2 , BOOST_FWD_REF(T3) t3 , BOOST_FWD_REF(T4) t4 , BOOST_FWD_REF(T5) t5 , BOOST_FWD_REF(T6) t6 , BOOST_FWD_REF(T7) t7)
    {
        typedef
            detail::bound<
                typename util::decay<F>::type
              , util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type>
            >
            result_type;
        return
            result_type(
                boost::forward<F>(f)
              , util::forward_as_tuple(boost::forward<T0>( t0 ) , boost::forward<T1>( t1 ) , boost::forward<T2>( t2 ) , boost::forward<T3>( t3 ) , boost::forward<T4>( t4 ) , boost::forward<T5>( t5 ) , boost::forward<T6>( t6 ) , boost::forward<T7>( t7 ))
            );
    }
}}
namespace hpx { namespace util
{
    namespace detail
    {
        template <typename F, typename BoundArgs, typename UnboundArgs>
        struct bind_invoke_impl<
            F, BoundArgs, UnboundArgs
          , typename boost::enable_if_c<
                util::tuple_size<BoundArgs>::value == 9
            >::type
        >
        {
            typedef
                typename util::detail::result_of_or<
                    F(typename detail::bind_eval_impl< F, typename util::tuple_element< 0, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 1, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 2, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 3, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 4, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 5, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 6, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 7, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 8, BoundArgs>::type , UnboundArgs >::type)
                  , cannot_be_called
                >::type
                type;
            static BOOST_FORCEINLINE
            type call(
                F& f, BoundArgs& bound_args
              , BOOST_FWD_REF(UnboundArgs) unbound_args
            )
            {
                return util::invoke(f, detail::bind_eval<F>( util::get< 0>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 1>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 2>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 3>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 4>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 5>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 6>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 7>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 8>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ));
            }
        };
    }
    template <typename F, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8>
    typename boost::disable_if_c<
        traits::is_action<typename util::remove_reference<F>::type>::value
      , detail::bound<
            typename util::decay<F>::type
          , util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type>
        >
    >::type
    bind(BOOST_FWD_REF(F) f, BOOST_FWD_REF(T0) t0 , BOOST_FWD_REF(T1) t1 , BOOST_FWD_REF(T2) t2 , BOOST_FWD_REF(T3) t3 , BOOST_FWD_REF(T4) t4 , BOOST_FWD_REF(T5) t5 , BOOST_FWD_REF(T6) t6 , BOOST_FWD_REF(T7) t7 , BOOST_FWD_REF(T8) t8)
    {
        typedef
            detail::bound<
                typename util::decay<F>::type
              , util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type>
            >
            result_type;
        return
            result_type(
                boost::forward<F>(f)
              , util::forward_as_tuple(boost::forward<T0>( t0 ) , boost::forward<T1>( t1 ) , boost::forward<T2>( t2 ) , boost::forward<T3>( t3 ) , boost::forward<T4>( t4 ) , boost::forward<T5>( t5 ) , boost::forward<T6>( t6 ) , boost::forward<T7>( t7 ) , boost::forward<T8>( t8 ))
            );
    }
}}
namespace hpx { namespace util
{
    namespace detail
    {
        template <typename F, typename BoundArgs, typename UnboundArgs>
        struct bind_invoke_impl<
            F, BoundArgs, UnboundArgs
          , typename boost::enable_if_c<
                util::tuple_size<BoundArgs>::value == 10
            >::type
        >
        {
            typedef
                typename util::detail::result_of_or<
                    F(typename detail::bind_eval_impl< F, typename util::tuple_element< 0, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 1, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 2, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 3, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 4, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 5, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 6, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 7, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 8, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 9, BoundArgs>::type , UnboundArgs >::type)
                  , cannot_be_called
                >::type
                type;
            static BOOST_FORCEINLINE
            type call(
                F& f, BoundArgs& bound_args
              , BOOST_FWD_REF(UnboundArgs) unbound_args
            )
            {
                return util::invoke(f, detail::bind_eval<F>( util::get< 0>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 1>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 2>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 3>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 4>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 5>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 6>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 7>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 8>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 9>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ));
            }
        };
    }
    template <typename F, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9>
    typename boost::disable_if_c<
        traits::is_action<typename util::remove_reference<F>::type>::value
      , detail::bound<
            typename util::decay<F>::type
          , util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type>
        >
    >::type
    bind(BOOST_FWD_REF(F) f, BOOST_FWD_REF(T0) t0 , BOOST_FWD_REF(T1) t1 , BOOST_FWD_REF(T2) t2 , BOOST_FWD_REF(T3) t3 , BOOST_FWD_REF(T4) t4 , BOOST_FWD_REF(T5) t5 , BOOST_FWD_REF(T6) t6 , BOOST_FWD_REF(T7) t7 , BOOST_FWD_REF(T8) t8 , BOOST_FWD_REF(T9) t9)
    {
        typedef
            detail::bound<
                typename util::decay<F>::type
              , util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type>
            >
            result_type;
        return
            result_type(
                boost::forward<F>(f)
              , util::forward_as_tuple(boost::forward<T0>( t0 ) , boost::forward<T1>( t1 ) , boost::forward<T2>( t2 ) , boost::forward<T3>( t3 ) , boost::forward<T4>( t4 ) , boost::forward<T5>( t5 ) , boost::forward<T6>( t6 ) , boost::forward<T7>( t7 ) , boost::forward<T8>( t8 ) , boost::forward<T9>( t9 ))
            );
    }
}}
namespace hpx { namespace util
{
    namespace detail
    {
        template <typename F, typename BoundArgs, typename UnboundArgs>
        struct bind_invoke_impl<
            F, BoundArgs, UnboundArgs
          , typename boost::enable_if_c<
                util::tuple_size<BoundArgs>::value == 11
            >::type
        >
        {
            typedef
                typename util::detail::result_of_or<
                    F(typename detail::bind_eval_impl< F, typename util::tuple_element< 0, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 1, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 2, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 3, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 4, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 5, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 6, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 7, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 8, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 9, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 10, BoundArgs>::type , UnboundArgs >::type)
                  , cannot_be_called
                >::type
                type;
            static BOOST_FORCEINLINE
            type call(
                F& f, BoundArgs& bound_args
              , BOOST_FWD_REF(UnboundArgs) unbound_args
            )
            {
                return util::invoke(f, detail::bind_eval<F>( util::get< 0>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 1>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 2>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 3>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 4>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 5>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 6>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 7>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 8>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 9>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 10>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ));
            }
        };
    }
    template <typename F, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10>
    typename boost::disable_if_c<
        traits::is_action<typename util::remove_reference<F>::type>::value
      , detail::bound<
            typename util::decay<F>::type
          , util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type>
        >
    >::type
    bind(BOOST_FWD_REF(F) f, BOOST_FWD_REF(T0) t0 , BOOST_FWD_REF(T1) t1 , BOOST_FWD_REF(T2) t2 , BOOST_FWD_REF(T3) t3 , BOOST_FWD_REF(T4) t4 , BOOST_FWD_REF(T5) t5 , BOOST_FWD_REF(T6) t6 , BOOST_FWD_REF(T7) t7 , BOOST_FWD_REF(T8) t8 , BOOST_FWD_REF(T9) t9 , BOOST_FWD_REF(T10) t10)
    {
        typedef
            detail::bound<
                typename util::decay<F>::type
              , util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type>
            >
            result_type;
        return
            result_type(
                boost::forward<F>(f)
              , util::forward_as_tuple(boost::forward<T0>( t0 ) , boost::forward<T1>( t1 ) , boost::forward<T2>( t2 ) , boost::forward<T3>( t3 ) , boost::forward<T4>( t4 ) , boost::forward<T5>( t5 ) , boost::forward<T6>( t6 ) , boost::forward<T7>( t7 ) , boost::forward<T8>( t8 ) , boost::forward<T9>( t9 ) , boost::forward<T10>( t10 ))
            );
    }
}}
namespace hpx { namespace util
{
    namespace detail
    {
        template <typename F, typename BoundArgs, typename UnboundArgs>
        struct bind_invoke_impl<
            F, BoundArgs, UnboundArgs
          , typename boost::enable_if_c<
                util::tuple_size<BoundArgs>::value == 12
            >::type
        >
        {
            typedef
                typename util::detail::result_of_or<
                    F(typename detail::bind_eval_impl< F, typename util::tuple_element< 0, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 1, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 2, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 3, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 4, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 5, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 6, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 7, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 8, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 9, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 10, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 11, BoundArgs>::type , UnboundArgs >::type)
                  , cannot_be_called
                >::type
                type;
            static BOOST_FORCEINLINE
            type call(
                F& f, BoundArgs& bound_args
              , BOOST_FWD_REF(UnboundArgs) unbound_args
            )
            {
                return util::invoke(f, detail::bind_eval<F>( util::get< 0>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 1>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 2>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 3>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 4>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 5>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 6>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 7>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 8>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 9>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 10>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 11>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ));
            }
        };
    }
    template <typename F, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11>
    typename boost::disable_if_c<
        traits::is_action<typename util::remove_reference<F>::type>::value
      , detail::bound<
            typename util::decay<F>::type
          , util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type>
        >
    >::type
    bind(BOOST_FWD_REF(F) f, BOOST_FWD_REF(T0) t0 , BOOST_FWD_REF(T1) t1 , BOOST_FWD_REF(T2) t2 , BOOST_FWD_REF(T3) t3 , BOOST_FWD_REF(T4) t4 , BOOST_FWD_REF(T5) t5 , BOOST_FWD_REF(T6) t6 , BOOST_FWD_REF(T7) t7 , BOOST_FWD_REF(T8) t8 , BOOST_FWD_REF(T9) t9 , BOOST_FWD_REF(T10) t10 , BOOST_FWD_REF(T11) t11)
    {
        typedef
            detail::bound<
                typename util::decay<F>::type
              , util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type>
            >
            result_type;
        return
            result_type(
                boost::forward<F>(f)
              , util::forward_as_tuple(boost::forward<T0>( t0 ) , boost::forward<T1>( t1 ) , boost::forward<T2>( t2 ) , boost::forward<T3>( t3 ) , boost::forward<T4>( t4 ) , boost::forward<T5>( t5 ) , boost::forward<T6>( t6 ) , boost::forward<T7>( t7 ) , boost::forward<T8>( t8 ) , boost::forward<T9>( t9 ) , boost::forward<T10>( t10 ) , boost::forward<T11>( t11 ))
            );
    }
}}
namespace hpx { namespace util
{
    namespace detail
    {
        template <typename F, typename BoundArgs, typename UnboundArgs>
        struct bind_invoke_impl<
            F, BoundArgs, UnboundArgs
          , typename boost::enable_if_c<
                util::tuple_size<BoundArgs>::value == 13
            >::type
        >
        {
            typedef
                typename util::detail::result_of_or<
                    F(typename detail::bind_eval_impl< F, typename util::tuple_element< 0, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 1, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 2, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 3, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 4, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 5, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 6, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 7, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 8, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 9, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 10, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 11, BoundArgs>::type , UnboundArgs >::type , typename detail::bind_eval_impl< F, typename util::tuple_element< 12, BoundArgs>::type , UnboundArgs >::type)
                  , cannot_be_called
                >::type
                type;
            static BOOST_FORCEINLINE
            type call(
                F& f, BoundArgs& bound_args
              , BOOST_FWD_REF(UnboundArgs) unbound_args
            )
            {
                return util::invoke(f, detail::bind_eval<F>( util::get< 0>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 1>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 2>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 3>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 4>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 5>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 6>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 7>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 8>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 9>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 10>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 11>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ) , detail::bind_eval<F>( util::get< 12>(bound_args) , boost::forward<UnboundArgs>(unbound_args) ));
            }
        };
    }
    template <typename F, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12>
    typename boost::disable_if_c<
        traits::is_action<typename util::remove_reference<F>::type>::value
      , detail::bound<
            typename util::decay<F>::type
          , util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type>
        >
    >::type
    bind(BOOST_FWD_REF(F) f, BOOST_FWD_REF(T0) t0 , BOOST_FWD_REF(T1) t1 , BOOST_FWD_REF(T2) t2 , BOOST_FWD_REF(T3) t3 , BOOST_FWD_REF(T4) t4 , BOOST_FWD_REF(T5) t5 , BOOST_FWD_REF(T6) t6 , BOOST_FWD_REF(T7) t7 , BOOST_FWD_REF(T8) t8 , BOOST_FWD_REF(T9) t9 , BOOST_FWD_REF(T10) t10 , BOOST_FWD_REF(T11) t11 , BOOST_FWD_REF(T12) t12)
    {
        typedef
            detail::bound<
                typename util::decay<F>::type
              , util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type>
            >
            result_type;
        return
            result_type(
                boost::forward<F>(f)
              , util::forward_as_tuple(boost::forward<T0>( t0 ) , boost::forward<T1>( t1 ) , boost::forward<T2>( t2 ) , boost::forward<T3>( t3 ) , boost::forward<T4>( t4 ) , boost::forward<T5>( t5 ) , boost::forward<T6>( t6 ) , boost::forward<T7>( t7 ) , boost::forward<T8>( t8 ) , boost::forward<T9>( t9 ) , boost::forward<T10>( t10 ) , boost::forward<T11>( t11 ) , boost::forward<T12>( t12 ))
            );
    }
}}
