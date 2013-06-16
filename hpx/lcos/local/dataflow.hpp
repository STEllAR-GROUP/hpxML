//  Copyright (c)      2013 Thomas Heller
//  Copyright (c) 2007-2013 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !BOOST_PP_IS_ITERATING

#ifndef HPX_LCOS_LOCAL_DATAFLOW_HPP
#define HPX_LCOS_LOCAL_DATAFLOW_HPP

#include <hpx/hpx_fwd.hpp>
#include <hpx/apply.hpp>
#include <hpx/lcos/future.hpp>
#include <hpx/util/tuple.hpp>
#include <hpx/util/bind.hpp>
#include <hpx/util/detail/remove_reference.hpp>
#include <hpx/traits/is_future.hpp>
#include <hpx/traits/is_future_range.hpp>

#include <boost/fusion/include/deref.hpp>
#include <boost/fusion/include/begin.hpp>
#include <boost/fusion/include/end.hpp>
#include <boost/fusion/include/next.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/or.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_same.hpp>

#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/enum.hpp>
#include <boost/preprocessor/enum_params.hpp>
#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/cat.hpp>

namespace hpx { namespace lcos { namespace local { namespace detail
{
    template <typename T>
    struct is_future_or_future_range
      : boost::mpl::or_<traits::is_future<T>, traits::is_future_range<T> >
    {};

    template <
        typename Future
      , typename IsFutureRange = typename traits::is_future_range<Future>::type
    >
    struct extract_completed_callback_type;

    template <typename Future>
    struct extract_completed_callback_type<Future, boost::mpl::true_>
    {
        typedef
            typename boost::remove_const<
                typename hpx::util::detail::remove_reference<
                    Future
                >::type
            >::type::value_type::future_data_type
            future_data_type;

        typedef
            typename future_data_type::completed_callback_type
            type;
    };

    template <typename Future>
    struct extract_completed_callback_type<Future, boost::mpl::false_>
    {
        typedef
            typename boost::remove_const<
                typename hpx::util::detail::remove_reference<
                    Future
                >::type
            >::type::future_data_type
            future_data_type;

        typedef
            typename future_data_type::completed_callback_type
            type;
    };

    template <typename F1, typename F2>
    struct compose_cb_impl
    {
        typename util::detail::remove_reference<F1>::type f1_;
        typename util::detail::remove_reference<F2>::type f2_;

        template <typename A1, typename A2>
        compose_cb_impl(BOOST_FWD_REF(A1) f1, BOOST_FWD_REF(A2) f2)
          : f1_(boost::forward<A1>(f1))
          , f2_(boost::forward<A2>(f2))
        {}

        typedef void result_type;

        template <typename Future>
        void operator()(Future & f)
        {
            f1_(f);
            f2_(f);
        }
    };

    template <typename F1, typename F2>
    compose_cb_impl<F1, F2>
    compose_cb(BOOST_FWD_REF(F1) f1, BOOST_FWD_REF(F2) f2)
    {
        return
            boost::move(
                compose_cb_impl<F1, F2>(
                    boost::forward<F1>(f1)
                  , boost::forward<F2>(f2)
                )
            );
    }
}}}}

#if !defined(HPX_USE_PREPROCESSOR_LIMIT_EXPANSION)
#  include <hpx/lcos/local/preprocessed/dataflow.hpp>
#else

#if defined(__WAVE__) && defined(HPX_CREATE_PREPROCESSED_FILES)
#  pragma wave option(preserve: 1, line: 0, output: "preprocessed/dataflow_" HPX_LIMIT_STR ".hpp")
#endif

#define HPX_LCOS_LOCAL_DATAFLOW_FRAME_RESULT_OF(z, n, d)                        \
    typename boost::remove_const<                                               \
        typename hpx::util::detail::remove_reference<                           \
            BOOST_PP_CAT(F, n)                                                  \
        >::type                                                                 \
    >::type                                                                     \
/**/

#define HPX_LCOS_LOCAL_DATAFLOW_FRAME_CTOR_LIST(z, n, d)                        \
    boost::forward<BOOST_PP_CAT(A, n)>(BOOST_PP_CAT(f, n))                      \
/**/

#define HPX_LCOS_LOCAL_DATAFLOW_FRAME_MEMBER(z, n, d)                           \
    BOOST_PP_CAT(BOOST_PP_CAT(f, n), _type)                                     \
/**/
#define HPX_LCOS_LOCAL_DATAFLOW_FRAME_MEMBER_TYPES(z, n, d)                     \
    typedef                                                                     \
        typename boost::remove_const<                                           \
            typename hpx::util::detail::remove_reference<                       \
                BOOST_PP_CAT(F, n)                                              \
            >::type                                                             \
        >::type                                                                 \
        BOOST_PP_CAT(BOOST_PP_CAT(f, n), _type);                                \
/**/

#define HPX_LCOS_LOCAL_DATAFLOW_FRAME_RESET_FUTURES(z, n, d)                    \
    boost::fusion::at_c< n >(futures_)                                          \
        = BOOST_PP_CAT(BOOST_PP_CAT(f, n), _type)();                            \

#define BOOST_PP_ITERATION_PARAMS_1                                             \
    (3, (1, HPX_ACTION_ARGUMENT_LIMIT, <hpx/lcos/local/dataflow.hpp>))          \
    /**/

#include BOOST_PP_ITERATE()

#undef HPX_LCOS_LOCAL_DATAFLOW_FRAME_CTOR_LIST
#undef HPX_LCOS_LOCAL_DATAFLOW_FRAME_MEMBER
#undef HPX_LCOS_LOCAL_DATAFLOW_FRAME_MEMBER_TYPES
#undef HPX_LCOS_LOCAL_DATAFLOW_FRAME_RESULT_OF
#undef HPX_LCOS_LOCAL_DATAFLOW_FRAME_RESET_FUTURES

#if defined(__WAVE__) && defined (HPX_CREATE_PREPROCESSED_FILES)
#  pragma wave option(output: null)
#endif

#endif // !defined(HPX_USE_PREPROCESSOR_LIMIT_EXPANSION)

#endif

#else

#define N BOOST_PP_ITERATION()

namespace hpx { namespace lcos { namespace local {
    namespace detail {
        template <typename Func, BOOST_PP_ENUM_PARAMS(N, typename F)>
        struct BOOST_PP_CAT(dataflow_frame_, N)
          : hpx::lcos::detail::future_data<
                typename boost::result_of<
                    typename hpx::util::detail::remove_reference<Func>::type(
                        BOOST_PP_ENUM(
                            N
                          , HPX_LCOS_LOCAL_DATAFLOW_FRAME_RESULT_OF
                          , _
                        )
                    )
                >::type
            >
        {

            typedef
                typename hpx::util::detail::remove_reference<Func>::type
                func_type;
            
            BOOST_PP_REPEAT(N, HPX_LCOS_LOCAL_DATAFLOW_FRAME_MEMBER_TYPES, _)
            typedef
                BOOST_PP_CAT(hpx::util::tuple, N)<
                    BOOST_PP_ENUM(N, HPX_LCOS_LOCAL_DATAFLOW_FRAME_MEMBER, _)
                >
                futures_type;

            typedef
                typename boost::fusion::result_of::end<futures_type>::type
                end_type;

            typedef
                typename boost::result_of<
                    func_type(
                        BOOST_PP_ENUM(
                            N
                          , HPX_LCOS_LOCAL_DATAFLOW_FRAME_RESULT_OF
                          , _
                        )
                    )
                >::type
                result_type;

            typedef
                boost::intrusive_ptr<BOOST_PP_CAT(dataflow_frame_, N)>
                future_base_type;

            typedef hpx::lcos::future<result_type> type;

            typedef
                typename boost::mpl::if_<
                    boost::is_void<result_type>
                  , void(BOOST_PP_CAT(dataflow_frame_, N)::*)(boost::mpl::true_)
                  , void(BOOST_PP_CAT(dataflow_frame_, N)::*)(boost::mpl::false_)
                >::type
                execute_function_type;

            futures_type futures_;

            BOOST_SCOPED_ENUM(launch) policy_;
            func_type func_;

            template <typename FFunc, BOOST_PP_ENUM_PARAMS(N, typename A)>
            BOOST_PP_CAT(dataflow_frame_, N)(
                BOOST_SCOPED_ENUM(launch) policy
              , BOOST_FWD_REF(FFunc) func
              , HPX_ENUM_FWD_ARGS(N, A, f)
            )
              : futures_(
                    BOOST_PP_ENUM(N, HPX_LCOS_LOCAL_DATAFLOW_FRAME_CTOR_LIST, _)
                )
              , policy_(policy)
              , func_(boost::forward<FFunc>(func))
            {}

            BOOST_FORCEINLINE
            void execute(boost::mpl::false_)
            {
                result_type res(
                    boost::move(boost::fusion::invoke(func_, futures_))
                );

                BOOST_PP_REPEAT(N, HPX_LCOS_LOCAL_DATAFLOW_FRAME_RESET_FUTURES, _)

                this->set_data(boost::move(res));
            }

            BOOST_FORCEINLINE
            void execute(boost::mpl::true_)
            {
                boost::fusion::invoke(func_, futures_);

                BOOST_PP_REPEAT(N, HPX_LCOS_LOCAL_DATAFLOW_FRAME_RESET_FUTURES, _)

                this->set_data(util::unused_type());
            }

            template <typename Iter>
            BOOST_FORCEINLINE
            void await(
                BOOST_FWD_REF(Iter) iter, boost::mpl::true_)
            {
                typedef
                    boost::mpl::bool_<boost::is_void<result_type>::value>
                    is_void;
                if(policy_ == hpx::launch::sync)
                {
                    execute(is_void());
                    return;
                }
                execute_function_type f = &BOOST_PP_CAT(dataflow_frame_, N)::execute;
                hpx::apply(hpx::util::bind(f, future_base_type(this), is_void()));
            }

            template <typename Iter>
            void await_range(Iter next, Iter end)
            {
                if(next == end) return;

                typedef
                    typename std::iterator_traits<
                        Iter
                    >::value_type
                    future_type;

                if(!next->ready())
                {
                    void (BOOST_PP_CAT(dataflow_frame_, N)::*f)
                        (Iter, Iter)
                        = &BOOST_PP_CAT(dataflow_frame_, N)::await_range;

                    typedef
                        typename extract_completed_callback_type<
                            future_type
                        >::type
                        completed_callback_type;

                    completed_callback_type cb 
                        = boost::move(
                            hpx::lcos::detail::get_future_data(*next)
                            ->set_on_completed(
                                completed_callback_type()
                            )
                        );

                    if(cb)
                    {
                        hpx::lcos::detail::get_future_data(*next)
                        ->set_on_completed(
                            boost::move(
                                compose_cb(
                                    boost::move(cb)
                                  , boost::bind(
                                        f
                                      , future_base_type(this)
                                      , boost::move(next)
                                      , boost::move(end)
                                    )
                                )
                            )
                        );
                    }
                    else
                    {
                        hpx::lcos::detail::get_future_data(*next)
                        ->set_on_completed(
                            boost::move(
                                boost::bind(
                                    f
                                  , future_base_type(this)
                                  , boost::move(next)
                                  , boost::move(end)
                                )
                            )
                        );
                    }
                    return;
                }

                await_range(boost::move(++next), boost::move(end));
            }

            template <typename Iter>
            BOOST_FORCEINLINE
            void await_next(Iter iter, boost::mpl::true_)
            {
                typedef
                    typename boost::fusion::result_of::next<Iter>::type
                    next_type;

                await_range(
                    boost::move(boost::begin(boost::fusion::deref(iter)))
                  , boost::move(boost::end(boost::fusion::deref(iter)))
                );

                await(
                    boost::move(boost::fusion::next(iter))
                  , boost::mpl::bool_<
                        boost::is_same<next_type, end_type>::value
                    >()
                );
            }

            template <typename Iter>
            BOOST_FORCEINLINE
            void await_next(Iter iter, boost::mpl::false_)
            {
                typedef
                    typename boost::fusion::result_of::next<Iter>::type
                    next_type;

                typedef
                    typename util::detail::remove_reference<
                        typename boost::fusion::result_of::deref<Iter>::type
                    >::type
                    future_type;
                future_type &  f_ =
                    boost::fusion::deref(iter);

                if(!f_.ready())
                {
                    void (BOOST_PP_CAT(dataflow_frame_, N)::*f)
                        (Iter, boost::mpl::false_)
                        = &BOOST_PP_CAT(dataflow_frame_, N)::await_next;

                    typedef
                        typename extract_completed_callback_type<
                            future_type
                        >::type
                        completed_callback_type;

                    completed_callback_type cb 
                        = boost::move(
                            hpx::lcos::detail::get_future_data(f_)
                            ->set_on_completed(
                                completed_callback_type()
                            )
                        );
                    
                    if(cb)
                    {
                        hpx::lcos::detail::get_future_data(f_)
                        ->set_on_completed(
                            boost::move(
                                compose_cb(
                                    boost::move(cb)
                                  , hpx::util::bind(
                                        f
                                      , future_base_type(this)
                                      , boost::move(iter)
                                      , boost::mpl::false_()
                                    )
                                )
                            )
                        );
                    }
                    else
                    {
                        hpx::lcos::detail::get_future_data(f_)
                        ->set_on_completed(
                            boost::move(
                                hpx::util::bind(
                                    f
                                  , future_base_type(this)
                                  , boost::move(iter)
                                  , boost::mpl::false_()
                                )
                            )
                        );
                    }

                    return;
                }

                await(
                    boost::move(boost::fusion::next(iter))
                  , boost::mpl::bool_<
                        boost::is_same<next_type, end_type>::value
                    >()
                );
            }

            template <typename Iter>
            BOOST_FORCEINLINE
            void await(Iter iter, boost::mpl::false_)
            {
                typedef
                    typename boost::fusion::result_of::deref<Iter>::type
                    future_type;

                typedef typename traits::is_future_range<
                    future_type
                >::type is_range;

                await_next(boost::move(iter), is_range());
            }

            BOOST_FORCEINLINE void await()
            {
                typedef
                    typename boost::fusion::result_of::begin<futures_type>::type
                    begin_type;

                await(
                    boost::move(boost::fusion::begin(futures_))
                  , boost::mpl::bool_<
                        boost::is_same<begin_type, end_type>::value
                    >()
                );
            }

            BOOST_FORCEINLINE
            type get_future()
            {
                await();

                return
                    lcos::detail::make_future_from_data(
                        boost::intrusive_ptr<
                            lcos::detail::future_data_base<result_type>
                        >(this)
                    );
            }
        };
    }

    template <typename Func, BOOST_PP_ENUM_PARAMS(N, typename F)>
    BOOST_FORCEINLINE
    typename boost::lazy_disable_if<
        detail::is_future_or_future_range<
            typename boost::remove_const<
                typename hpx::util::detail::remove_reference<Func>::type
            >::type
        >
      , BOOST_PP_CAT(detail::dataflow_frame_, N)<
            Func
          , BOOST_PP_ENUM_PARAMS(N, F)
        >
    >::type
    dataflow(
        BOOST_SCOPED_ENUM(launch) policy
      , BOOST_FWD_REF(Func) func
      , HPX_ENUM_FWD_ARGS(N, F, f)
    )
    {
        typedef
            BOOST_PP_CAT(detail::dataflow_frame_, N)<
                Func
              , BOOST_PP_ENUM_PARAMS(N, F)
            >
            frame_type;

        boost::intrusive_ptr<frame_type> frame =
            new frame_type(
                policy
              , boost::forward<Func>(func)
              , HPX_ENUM_FORWARD_ARGS(N, F, f)
            );

        return frame->get_future();
    }

    template <typename Func, BOOST_PP_ENUM_PARAMS(N, typename F)>
    BOOST_FORCEINLINE
    typename boost::lazy_disable_if<
        boost::is_same<
            BOOST_SCOPED_ENUM(launch)
          , typename boost::remove_const<
                typename hpx::util::detail::remove_reference<
                    Func
                >::type
            >::type
        >
      , BOOST_PP_CAT(detail::dataflow_frame_, N)<
            Func
          , BOOST_PP_ENUM_PARAMS(N, F)
        >
    >::type
    dataflow(BOOST_FWD_REF(Func) func, HPX_ENUM_FWD_ARGS(N, F, f))
    {
        typedef
            BOOST_PP_CAT(detail::dataflow_frame_, N)<
                Func
              , BOOST_PP_ENUM_PARAMS(N, F)
            >
            frame_type;

        boost::intrusive_ptr<frame_type> frame =
            new frame_type(
                launch::all
              , boost::forward<Func>(func)
              , HPX_ENUM_FORWARD_ARGS(N, F, f)
            );

        return frame->get_future();
    }

}}}

#endif
