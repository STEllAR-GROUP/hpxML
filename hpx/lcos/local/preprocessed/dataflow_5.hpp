// Copyright (c) 2007-2013 Hartmut Kaiser
// Copyright (c) 2012-2013 Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This file has been automatically generated using the Boost.Wave tool.
// Do not edit manually.


namespace hpx { namespace lcos { namespace local {
    namespace detail {
        template <typename Func, typename F0>
        struct dataflow_frame_1
          : boost::enable_shared_from_this<
                dataflow_frame_1<
                    Func, F0
                >
            >
        {
            typedef
                typename hpx::util::detail::remove_reference<Func>::type
                func_type;
            func_type func_;
            typedef typename boost::remove_const< typename hpx::util::detail::remove_reference< F0 >::type >::type f0_type;
            typedef 
                hpx::util::tuple1< 
                    f0_type
                > 
                futures_type; 
            futures_type futures_;
            
            typedef
                typename boost::result_of<
                    func_type(
                        f0_type
                    )
                >::type
                result_type;
            typedef hpx::future<result_type> future_result_type;
            typedef hpx::lcos::local::promise<result_type> promise_result_type;
            template <typename FFunc, typename FF0>
            dataflow_frame_1(
                BOOST_SCOPED_ENUM(launch) policy
              , BOOST_FWD_REF(FFunc) func
              , BOOST_FWD_REF(FF0) f0
            )
              : func_(boost::forward<FFunc>(func))
              , futures_(
                    boost::forward<FF0>(f0)
                )
              , policy_(policy)
            {}
            template <typename Iter>
            BOOST_FORCEINLINE
            void await(
                BOOST_FWD_REF(Iter) iter, boost::mpl::true_, boost::mpl::true_
            )
            {
                if(!result_.valid())
                {
                    result_type (*f)(Func, futures_type &) = &boost::fusion::invoke;
                    result_
                        = hpx::async(policy_, hpx::util::bind(f, func_, futures_));
                }
                else
                {
                    boost::fusion::invoke(func_, futures_);
                    result_promise_.set_value();
                }
            }
            template <typename Iter>
            BOOST_FORCEINLINE
            void await(
                BOOST_FWD_REF(Iter) iter, boost::mpl::true_, boost::mpl::false_
            )
            {
                if(!result_.valid())
                {
                    result_type (*f)(Func, futures_type &) = &boost::fusion::invoke;
                    result_
                        = hpx::async(policy_, hpx::util::bind(f, func_, futures_));
                }
                else
                {
                    result_promise_.set_value(
                        boost::fusion::invoke(func_, futures_)
                    );
                }
            }
            template <typename Iter>
            void await_range(Iter next, Iter end)
            {
                if(next == end) return;
                if(!next->ready())
                {
                    if(!result_.valid())
                    {
                        result_ = result_promise_.get_future();
                    }
                    void (dataflow_frame_1::*f)
                        (Iter, Iter)
                        = &dataflow_frame_1::await_range;
                    next->then(
                        policy_
                      , boost::bind(
                            f
                          , this->shared_from_this()
                          , next
                          , end
                        )
                    );
                    return;
                }
                await_range(++next, end);
            }
            template <typename Iter, typename IsVoid>
            BOOST_FORCEINLINE
            typename boost::enable_if<
                typename traits::is_future_range<
                    typename boost::fusion::result_of::deref<Iter>::type
                >::type
            >::type
            await(Iter const & iter, boost::mpl::false_, IsVoid)
            {
                typedef
                    typename boost::fusion::result_of::next<Iter>::type
                    next_type;
                typedef
                    typename boost::fusion::result_of::end<futures_type>::type
                    end_type;
                await_range(
                    boost::begin(boost::fusion::deref(iter))
                  , boost::end(boost::fusion::deref(iter))
                );
                await(
                    boost::fusion::next(iter)
                  , typename boost::is_same<next_type, end_type>::type()
                  , IsVoid()
                );
            }
            
            template <typename Iter, typename IsVoid>
            BOOST_FORCEINLINE
            typename boost::disable_if<
                typename traits::is_future_range<
                    typename boost::fusion::result_of::deref<Iter>::type
                >::type
            >::type
            await(Iter const & iter, boost::mpl::false_, IsVoid)
            {
                typedef
                    typename boost::fusion::result_of::next<Iter>::type
                    next_type;
                typedef
                    typename boost::fusion::result_of::end<futures_type>::type
                    end_type;
                if(!boost::fusion::deref(iter).ready())
                {
                    if(!result_.valid())
                    {
                        result_ = result_promise_.get_future();
                    }
                    void (dataflow_frame_1::*f)
                        (Iter const &, boost::mpl::false_, IsVoid)
                        = &dataflow_frame_1::await;
                    boost::fusion::deref(iter).then(
                        policy_
                      , boost::bind(
                            f
                          , this->shared_from_this()
                          , iter
                          , boost::mpl::false_()
                          , IsVoid()
                        )
                    );
                    return;
                }
                await(
                    boost::fusion::next(iter)
                  , typename boost::is_same<next_type, end_type>::type()
                  , IsVoid()
                );
            }
            BOOST_FORCEINLINE void await()
            {
                await(
                    boost::fusion::begin(futures_)
                  , boost::mpl::false_()
                  , typename boost::is_same<void, result_type>::type()
                );
            }
            
            BOOST_SCOPED_ENUM(launch) policy_;
            future_result_type result_;
            promise_result_type result_promise_;
        };
    }
    template <typename Func, typename F0>
    BOOST_FORCEINLINE
    typename detail::dataflow_frame_1<
        Func
      , F0
    >::future_result_type
    dataflow(BOOST_SCOPED_ENUM(launch) policy, BOOST_FWD_REF(Func) func, BOOST_FWD_REF(F0) f0)
    {
        typedef
            detail::dataflow_frame_1<
                Func
              , F0
            >
            frame_type;
        boost::shared_ptr<frame_type> frame =
            boost::make_shared<frame_type>(
                policy
              , boost::forward<Func>(func)
              , boost::forward<F0>( f0 )
            );
        frame->await();
        return frame->result_;
    }
    template <typename Func, typename F0>
    BOOST_FORCEINLINE
    typename detail::dataflow_frame_1<
        Func
      , F0
    >::future_result_type
    dataflow(BOOST_FWD_REF(Func) func, BOOST_FWD_REF(F0) f0)
    {
        return dataflow(launch::all, func, boost::forward<F0>( f0 ));
    }
}}}
namespace hpx { namespace lcos { namespace local {
    namespace detail {
        template <typename Func, typename F0 , typename F1>
        struct dataflow_frame_2
          : boost::enable_shared_from_this<
                dataflow_frame_2<
                    Func, F0 , F1
                >
            >
        {
            typedef
                typename hpx::util::detail::remove_reference<Func>::type
                func_type;
            func_type func_;
            typedef typename boost::remove_const< typename hpx::util::detail::remove_reference< F0 >::type >::type f0_type; typedef typename boost::remove_const< typename hpx::util::detail::remove_reference< F1 >::type >::type f1_type;
            typedef 
                hpx::util::tuple2< 
                    f0_type , f1_type
                > 
                futures_type; 
            futures_type futures_;
            
            typedef
                typename boost::result_of<
                    func_type(
                        f0_type , f1_type
                    )
                >::type
                result_type;
            typedef hpx::future<result_type> future_result_type;
            typedef hpx::lcos::local::promise<result_type> promise_result_type;
            template <typename FFunc, typename FF0 , typename FF1>
            dataflow_frame_2(
                BOOST_SCOPED_ENUM(launch) policy
              , BOOST_FWD_REF(FFunc) func
              , BOOST_FWD_REF(FF0) f0 , BOOST_FWD_REF(FF1) f1
            )
              : func_(boost::forward<FFunc>(func))
              , futures_(
                    boost::forward<FF0>(f0) , boost::forward<FF1>(f1)
                )
              , policy_(policy)
            {}
            template <typename Iter>
            BOOST_FORCEINLINE
            void await(
                BOOST_FWD_REF(Iter) iter, boost::mpl::true_, boost::mpl::true_
            )
            {
                if(!result_.valid())
                {
                    result_type (*f)(Func, futures_type &) = &boost::fusion::invoke;
                    result_
                        = hpx::async(policy_, hpx::util::bind(f, func_, futures_));
                }
                else
                {
                    boost::fusion::invoke(func_, futures_);
                    result_promise_.set_value();
                }
            }
            template <typename Iter>
            BOOST_FORCEINLINE
            void await(
                BOOST_FWD_REF(Iter) iter, boost::mpl::true_, boost::mpl::false_
            )
            {
                if(!result_.valid())
                {
                    result_type (*f)(Func, futures_type &) = &boost::fusion::invoke;
                    result_
                        = hpx::async(policy_, hpx::util::bind(f, func_, futures_));
                }
                else
                {
                    result_promise_.set_value(
                        boost::fusion::invoke(func_, futures_)
                    );
                }
            }
            template <typename Iter>
            void await_range(Iter next, Iter end)
            {
                if(next == end) return;
                if(!next->ready())
                {
                    if(!result_.valid())
                    {
                        result_ = result_promise_.get_future();
                    }
                    void (dataflow_frame_2::*f)
                        (Iter, Iter)
                        = &dataflow_frame_2::await_range;
                    next->then(
                        policy_
                      , boost::bind(
                            f
                          , this->shared_from_this()
                          , next
                          , end
                        )
                    );
                    return;
                }
                await_range(++next, end);
            }
            template <typename Iter, typename IsVoid>
            BOOST_FORCEINLINE
            typename boost::enable_if<
                typename traits::is_future_range<
                    typename boost::fusion::result_of::deref<Iter>::type
                >::type
            >::type
            await(Iter const & iter, boost::mpl::false_, IsVoid)
            {
                typedef
                    typename boost::fusion::result_of::next<Iter>::type
                    next_type;
                typedef
                    typename boost::fusion::result_of::end<futures_type>::type
                    end_type;
                await_range(
                    boost::begin(boost::fusion::deref(iter))
                  , boost::end(boost::fusion::deref(iter))
                );
                await(
                    boost::fusion::next(iter)
                  , typename boost::is_same<next_type, end_type>::type()
                  , IsVoid()
                );
            }
            
            template <typename Iter, typename IsVoid>
            BOOST_FORCEINLINE
            typename boost::disable_if<
                typename traits::is_future_range<
                    typename boost::fusion::result_of::deref<Iter>::type
                >::type
            >::type
            await(Iter const & iter, boost::mpl::false_, IsVoid)
            {
                typedef
                    typename boost::fusion::result_of::next<Iter>::type
                    next_type;
                typedef
                    typename boost::fusion::result_of::end<futures_type>::type
                    end_type;
                if(!boost::fusion::deref(iter).ready())
                {
                    if(!result_.valid())
                    {
                        result_ = result_promise_.get_future();
                    }
                    void (dataflow_frame_2::*f)
                        (Iter const &, boost::mpl::false_, IsVoid)
                        = &dataflow_frame_2::await;
                    boost::fusion::deref(iter).then(
                        policy_
                      , boost::bind(
                            f
                          , this->shared_from_this()
                          , iter
                          , boost::mpl::false_()
                          , IsVoid()
                        )
                    );
                    return;
                }
                await(
                    boost::fusion::next(iter)
                  , typename boost::is_same<next_type, end_type>::type()
                  , IsVoid()
                );
            }
            BOOST_FORCEINLINE void await()
            {
                await(
                    boost::fusion::begin(futures_)
                  , boost::mpl::false_()
                  , typename boost::is_same<void, result_type>::type()
                );
            }
            
            BOOST_SCOPED_ENUM(launch) policy_;
            future_result_type result_;
            promise_result_type result_promise_;
        };
    }
    template <typename Func, typename F0 , typename F1>
    BOOST_FORCEINLINE
    typename detail::dataflow_frame_2<
        Func
      , F0 , F1
    >::future_result_type
    dataflow(BOOST_SCOPED_ENUM(launch) policy, BOOST_FWD_REF(Func) func, BOOST_FWD_REF(F0) f0 , BOOST_FWD_REF(F1) f1)
    {
        typedef
            detail::dataflow_frame_2<
                Func
              , F0 , F1
            >
            frame_type;
        boost::shared_ptr<frame_type> frame =
            boost::make_shared<frame_type>(
                policy
              , boost::forward<Func>(func)
              , boost::forward<F0>( f0 ) , boost::forward<F1>( f1 )
            );
        frame->await();
        return frame->result_;
    }
    template <typename Func, typename F0 , typename F1>
    BOOST_FORCEINLINE
    typename detail::dataflow_frame_2<
        Func
      , F0 , F1
    >::future_result_type
    dataflow(BOOST_FWD_REF(Func) func, BOOST_FWD_REF(F0) f0 , BOOST_FWD_REF(F1) f1)
    {
        return dataflow(launch::all, func, boost::forward<F0>( f0 ) , boost::forward<F1>( f1 ));
    }
}}}
namespace hpx { namespace lcos { namespace local {
    namespace detail {
        template <typename Func, typename F0 , typename F1 , typename F2>
        struct dataflow_frame_3
          : boost::enable_shared_from_this<
                dataflow_frame_3<
                    Func, F0 , F1 , F2
                >
            >
        {
            typedef
                typename hpx::util::detail::remove_reference<Func>::type
                func_type;
            func_type func_;
            typedef typename boost::remove_const< typename hpx::util::detail::remove_reference< F0 >::type >::type f0_type; typedef typename boost::remove_const< typename hpx::util::detail::remove_reference< F1 >::type >::type f1_type; typedef typename boost::remove_const< typename hpx::util::detail::remove_reference< F2 >::type >::type f2_type;
            typedef 
                hpx::util::tuple3< 
                    f0_type , f1_type , f2_type
                > 
                futures_type; 
            futures_type futures_;
            
            typedef
                typename boost::result_of<
                    func_type(
                        f0_type , f1_type , f2_type
                    )
                >::type
                result_type;
            typedef hpx::future<result_type> future_result_type;
            typedef hpx::lcos::local::promise<result_type> promise_result_type;
            template <typename FFunc, typename FF0 , typename FF1 , typename FF2>
            dataflow_frame_3(
                BOOST_SCOPED_ENUM(launch) policy
              , BOOST_FWD_REF(FFunc) func
              , BOOST_FWD_REF(FF0) f0 , BOOST_FWD_REF(FF1) f1 , BOOST_FWD_REF(FF2) f2
            )
              : func_(boost::forward<FFunc>(func))
              , futures_(
                    boost::forward<FF0>(f0) , boost::forward<FF1>(f1) , boost::forward<FF2>(f2)
                )
              , policy_(policy)
            {}
            template <typename Iter>
            BOOST_FORCEINLINE
            void await(
                BOOST_FWD_REF(Iter) iter, boost::mpl::true_, boost::mpl::true_
            )
            {
                if(!result_.valid())
                {
                    result_type (*f)(Func, futures_type &) = &boost::fusion::invoke;
                    result_
                        = hpx::async(policy_, hpx::util::bind(f, func_, futures_));
                }
                else
                {
                    boost::fusion::invoke(func_, futures_);
                    result_promise_.set_value();
                }
            }
            template <typename Iter>
            BOOST_FORCEINLINE
            void await(
                BOOST_FWD_REF(Iter) iter, boost::mpl::true_, boost::mpl::false_
            )
            {
                if(!result_.valid())
                {
                    result_type (*f)(Func, futures_type &) = &boost::fusion::invoke;
                    result_
                        = hpx::async(policy_, hpx::util::bind(f, func_, futures_));
                }
                else
                {
                    result_promise_.set_value(
                        boost::fusion::invoke(func_, futures_)
                    );
                }
            }
            template <typename Iter>
            void await_range(Iter next, Iter end)
            {
                if(next == end) return;
                if(!next->ready())
                {
                    if(!result_.valid())
                    {
                        result_ = result_promise_.get_future();
                    }
                    void (dataflow_frame_3::*f)
                        (Iter, Iter)
                        = &dataflow_frame_3::await_range;
                    next->then(
                        policy_
                      , boost::bind(
                            f
                          , this->shared_from_this()
                          , next
                          , end
                        )
                    );
                    return;
                }
                await_range(++next, end);
            }
            template <typename Iter, typename IsVoid>
            BOOST_FORCEINLINE
            typename boost::enable_if<
                typename traits::is_future_range<
                    typename boost::fusion::result_of::deref<Iter>::type
                >::type
            >::type
            await(Iter const & iter, boost::mpl::false_, IsVoid)
            {
                typedef
                    typename boost::fusion::result_of::next<Iter>::type
                    next_type;
                typedef
                    typename boost::fusion::result_of::end<futures_type>::type
                    end_type;
                await_range(
                    boost::begin(boost::fusion::deref(iter))
                  , boost::end(boost::fusion::deref(iter))
                );
                await(
                    boost::fusion::next(iter)
                  , typename boost::is_same<next_type, end_type>::type()
                  , IsVoid()
                );
            }
            
            template <typename Iter, typename IsVoid>
            BOOST_FORCEINLINE
            typename boost::disable_if<
                typename traits::is_future_range<
                    typename boost::fusion::result_of::deref<Iter>::type
                >::type
            >::type
            await(Iter const & iter, boost::mpl::false_, IsVoid)
            {
                typedef
                    typename boost::fusion::result_of::next<Iter>::type
                    next_type;
                typedef
                    typename boost::fusion::result_of::end<futures_type>::type
                    end_type;
                if(!boost::fusion::deref(iter).ready())
                {
                    if(!result_.valid())
                    {
                        result_ = result_promise_.get_future();
                    }
                    void (dataflow_frame_3::*f)
                        (Iter const &, boost::mpl::false_, IsVoid)
                        = &dataflow_frame_3::await;
                    boost::fusion::deref(iter).then(
                        policy_
                      , boost::bind(
                            f
                          , this->shared_from_this()
                          , iter
                          , boost::mpl::false_()
                          , IsVoid()
                        )
                    );
                    return;
                }
                await(
                    boost::fusion::next(iter)
                  , typename boost::is_same<next_type, end_type>::type()
                  , IsVoid()
                );
            }
            BOOST_FORCEINLINE void await()
            {
                await(
                    boost::fusion::begin(futures_)
                  , boost::mpl::false_()
                  , typename boost::is_same<void, result_type>::type()
                );
            }
            
            BOOST_SCOPED_ENUM(launch) policy_;
            future_result_type result_;
            promise_result_type result_promise_;
        };
    }
    template <typename Func, typename F0 , typename F1 , typename F2>
    BOOST_FORCEINLINE
    typename detail::dataflow_frame_3<
        Func
      , F0 , F1 , F2
    >::future_result_type
    dataflow(BOOST_SCOPED_ENUM(launch) policy, BOOST_FWD_REF(Func) func, BOOST_FWD_REF(F0) f0 , BOOST_FWD_REF(F1) f1 , BOOST_FWD_REF(F2) f2)
    {
        typedef
            detail::dataflow_frame_3<
                Func
              , F0 , F1 , F2
            >
            frame_type;
        boost::shared_ptr<frame_type> frame =
            boost::make_shared<frame_type>(
                policy
              , boost::forward<Func>(func)
              , boost::forward<F0>( f0 ) , boost::forward<F1>( f1 ) , boost::forward<F2>( f2 )
            );
        frame->await();
        return frame->result_;
    }
    template <typename Func, typename F0 , typename F1 , typename F2>
    BOOST_FORCEINLINE
    typename detail::dataflow_frame_3<
        Func
      , F0 , F1 , F2
    >::future_result_type
    dataflow(BOOST_FWD_REF(Func) func, BOOST_FWD_REF(F0) f0 , BOOST_FWD_REF(F1) f1 , BOOST_FWD_REF(F2) f2)
    {
        return dataflow(launch::all, func, boost::forward<F0>( f0 ) , boost::forward<F1>( f1 ) , boost::forward<F2>( f2 ));
    }
}}}
namespace hpx { namespace lcos { namespace local {
    namespace detail {
        template <typename Func, typename F0 , typename F1 , typename F2 , typename F3>
        struct dataflow_frame_4
          : boost::enable_shared_from_this<
                dataflow_frame_4<
                    Func, F0 , F1 , F2 , F3
                >
            >
        {
            typedef
                typename hpx::util::detail::remove_reference<Func>::type
                func_type;
            func_type func_;
            typedef typename boost::remove_const< typename hpx::util::detail::remove_reference< F0 >::type >::type f0_type; typedef typename boost::remove_const< typename hpx::util::detail::remove_reference< F1 >::type >::type f1_type; typedef typename boost::remove_const< typename hpx::util::detail::remove_reference< F2 >::type >::type f2_type; typedef typename boost::remove_const< typename hpx::util::detail::remove_reference< F3 >::type >::type f3_type;
            typedef 
                hpx::util::tuple4< 
                    f0_type , f1_type , f2_type , f3_type
                > 
                futures_type; 
            futures_type futures_;
            
            typedef
                typename boost::result_of<
                    func_type(
                        f0_type , f1_type , f2_type , f3_type
                    )
                >::type
                result_type;
            typedef hpx::future<result_type> future_result_type;
            typedef hpx::lcos::local::promise<result_type> promise_result_type;
            template <typename FFunc, typename FF0 , typename FF1 , typename FF2 , typename FF3>
            dataflow_frame_4(
                BOOST_SCOPED_ENUM(launch) policy
              , BOOST_FWD_REF(FFunc) func
              , BOOST_FWD_REF(FF0) f0 , BOOST_FWD_REF(FF1) f1 , BOOST_FWD_REF(FF2) f2 , BOOST_FWD_REF(FF3) f3
            )
              : func_(boost::forward<FFunc>(func))
              , futures_(
                    boost::forward<FF0>(f0) , boost::forward<FF1>(f1) , boost::forward<FF2>(f2) , boost::forward<FF3>(f3)
                )
              , policy_(policy)
            {}
            template <typename Iter>
            BOOST_FORCEINLINE
            void await(
                BOOST_FWD_REF(Iter) iter, boost::mpl::true_, boost::mpl::true_
            )
            {
                if(!result_.valid())
                {
                    result_type (*f)(Func, futures_type &) = &boost::fusion::invoke;
                    result_
                        = hpx::async(policy_, hpx::util::bind(f, func_, futures_));
                }
                else
                {
                    boost::fusion::invoke(func_, futures_);
                    result_promise_.set_value();
                }
            }
            template <typename Iter>
            BOOST_FORCEINLINE
            void await(
                BOOST_FWD_REF(Iter) iter, boost::mpl::true_, boost::mpl::false_
            )
            {
                if(!result_.valid())
                {
                    result_type (*f)(Func, futures_type &) = &boost::fusion::invoke;
                    result_
                        = hpx::async(policy_, hpx::util::bind(f, func_, futures_));
                }
                else
                {
                    result_promise_.set_value(
                        boost::fusion::invoke(func_, futures_)
                    );
                }
            }
            template <typename Iter>
            void await_range(Iter next, Iter end)
            {
                if(next == end) return;
                if(!next->ready())
                {
                    if(!result_.valid())
                    {
                        result_ = result_promise_.get_future();
                    }
                    void (dataflow_frame_4::*f)
                        (Iter, Iter)
                        = &dataflow_frame_4::await_range;
                    next->then(
                        policy_
                      , boost::bind(
                            f
                          , this->shared_from_this()
                          , next
                          , end
                        )
                    );
                    return;
                }
                await_range(++next, end);
            }
            template <typename Iter, typename IsVoid>
            BOOST_FORCEINLINE
            typename boost::enable_if<
                typename traits::is_future_range<
                    typename boost::fusion::result_of::deref<Iter>::type
                >::type
            >::type
            await(Iter const & iter, boost::mpl::false_, IsVoid)
            {
                typedef
                    typename boost::fusion::result_of::next<Iter>::type
                    next_type;
                typedef
                    typename boost::fusion::result_of::end<futures_type>::type
                    end_type;
                await_range(
                    boost::begin(boost::fusion::deref(iter))
                  , boost::end(boost::fusion::deref(iter))
                );
                await(
                    boost::fusion::next(iter)
                  , typename boost::is_same<next_type, end_type>::type()
                  , IsVoid()
                );
            }
            
            template <typename Iter, typename IsVoid>
            BOOST_FORCEINLINE
            typename boost::disable_if<
                typename traits::is_future_range<
                    typename boost::fusion::result_of::deref<Iter>::type
                >::type
            >::type
            await(Iter const & iter, boost::mpl::false_, IsVoid)
            {
                typedef
                    typename boost::fusion::result_of::next<Iter>::type
                    next_type;
                typedef
                    typename boost::fusion::result_of::end<futures_type>::type
                    end_type;
                if(!boost::fusion::deref(iter).ready())
                {
                    if(!result_.valid())
                    {
                        result_ = result_promise_.get_future();
                    }
                    void (dataflow_frame_4::*f)
                        (Iter const &, boost::mpl::false_, IsVoid)
                        = &dataflow_frame_4::await;
                    boost::fusion::deref(iter).then(
                        policy_
                      , boost::bind(
                            f
                          , this->shared_from_this()
                          , iter
                          , boost::mpl::false_()
                          , IsVoid()
                        )
                    );
                    return;
                }
                await(
                    boost::fusion::next(iter)
                  , typename boost::is_same<next_type, end_type>::type()
                  , IsVoid()
                );
            }
            BOOST_FORCEINLINE void await()
            {
                await(
                    boost::fusion::begin(futures_)
                  , boost::mpl::false_()
                  , typename boost::is_same<void, result_type>::type()
                );
            }
            
            BOOST_SCOPED_ENUM(launch) policy_;
            future_result_type result_;
            promise_result_type result_promise_;
        };
    }
    template <typename Func, typename F0 , typename F1 , typename F2 , typename F3>
    BOOST_FORCEINLINE
    typename detail::dataflow_frame_4<
        Func
      , F0 , F1 , F2 , F3
    >::future_result_type
    dataflow(BOOST_SCOPED_ENUM(launch) policy, BOOST_FWD_REF(Func) func, BOOST_FWD_REF(F0) f0 , BOOST_FWD_REF(F1) f1 , BOOST_FWD_REF(F2) f2 , BOOST_FWD_REF(F3) f3)
    {
        typedef
            detail::dataflow_frame_4<
                Func
              , F0 , F1 , F2 , F3
            >
            frame_type;
        boost::shared_ptr<frame_type> frame =
            boost::make_shared<frame_type>(
                policy
              , boost::forward<Func>(func)
              , boost::forward<F0>( f0 ) , boost::forward<F1>( f1 ) , boost::forward<F2>( f2 ) , boost::forward<F3>( f3 )
            );
        frame->await();
        return frame->result_;
    }
    template <typename Func, typename F0 , typename F1 , typename F2 , typename F3>
    BOOST_FORCEINLINE
    typename detail::dataflow_frame_4<
        Func
      , F0 , F1 , F2 , F3
    >::future_result_type
    dataflow(BOOST_FWD_REF(Func) func, BOOST_FWD_REF(F0) f0 , BOOST_FWD_REF(F1) f1 , BOOST_FWD_REF(F2) f2 , BOOST_FWD_REF(F3) f3)
    {
        return dataflow(launch::all, func, boost::forward<F0>( f0 ) , boost::forward<F1>( f1 ) , boost::forward<F2>( f2 ) , boost::forward<F3>( f3 ));
    }
}}}
namespace hpx { namespace lcos { namespace local {
    namespace detail {
        template <typename Func, typename F0 , typename F1 , typename F2 , typename F3 , typename F4>
        struct dataflow_frame_5
          : boost::enable_shared_from_this<
                dataflow_frame_5<
                    Func, F0 , F1 , F2 , F3 , F4
                >
            >
        {
            typedef
                typename hpx::util::detail::remove_reference<Func>::type
                func_type;
            func_type func_;
            typedef typename boost::remove_const< typename hpx::util::detail::remove_reference< F0 >::type >::type f0_type; typedef typename boost::remove_const< typename hpx::util::detail::remove_reference< F1 >::type >::type f1_type; typedef typename boost::remove_const< typename hpx::util::detail::remove_reference< F2 >::type >::type f2_type; typedef typename boost::remove_const< typename hpx::util::detail::remove_reference< F3 >::type >::type f3_type; typedef typename boost::remove_const< typename hpx::util::detail::remove_reference< F4 >::type >::type f4_type;
            typedef 
                hpx::util::tuple5< 
                    f0_type , f1_type , f2_type , f3_type , f4_type
                > 
                futures_type; 
            futures_type futures_;
            
            typedef
                typename boost::result_of<
                    func_type(
                        f0_type , f1_type , f2_type , f3_type , f4_type
                    )
                >::type
                result_type;
            typedef hpx::future<result_type> future_result_type;
            typedef hpx::lcos::local::promise<result_type> promise_result_type;
            template <typename FFunc, typename FF0 , typename FF1 , typename FF2 , typename FF3 , typename FF4>
            dataflow_frame_5(
                BOOST_SCOPED_ENUM(launch) policy
              , BOOST_FWD_REF(FFunc) func
              , BOOST_FWD_REF(FF0) f0 , BOOST_FWD_REF(FF1) f1 , BOOST_FWD_REF(FF2) f2 , BOOST_FWD_REF(FF3) f3 , BOOST_FWD_REF(FF4) f4
            )
              : func_(boost::forward<FFunc>(func))
              , futures_(
                    boost::forward<FF0>(f0) , boost::forward<FF1>(f1) , boost::forward<FF2>(f2) , boost::forward<FF3>(f3) , boost::forward<FF4>(f4)
                )
              , policy_(policy)
            {}
            template <typename Iter>
            BOOST_FORCEINLINE
            void await(
                BOOST_FWD_REF(Iter) iter, boost::mpl::true_, boost::mpl::true_
            )
            {
                if(!result_.valid())
                {
                    result_type (*f)(Func, futures_type &) = &boost::fusion::invoke;
                    result_
                        = hpx::async(policy_, hpx::util::bind(f, func_, futures_));
                }
                else
                {
                    boost::fusion::invoke(func_, futures_);
                    result_promise_.set_value();
                }
            }
            template <typename Iter>
            BOOST_FORCEINLINE
            void await(
                BOOST_FWD_REF(Iter) iter, boost::mpl::true_, boost::mpl::false_
            )
            {
                if(!result_.valid())
                {
                    result_type (*f)(Func, futures_type &) = &boost::fusion::invoke;
                    result_
                        = hpx::async(policy_, hpx::util::bind(f, func_, futures_));
                }
                else
                {
                    result_promise_.set_value(
                        boost::fusion::invoke(func_, futures_)
                    );
                }
            }
            template <typename Iter>
            void await_range(Iter next, Iter end)
            {
                if(next == end) return;
                if(!next->ready())
                {
                    if(!result_.valid())
                    {
                        result_ = result_promise_.get_future();
                    }
                    void (dataflow_frame_5::*f)
                        (Iter, Iter)
                        = &dataflow_frame_5::await_range;
                    next->then(
                        policy_
                      , boost::bind(
                            f
                          , this->shared_from_this()
                          , next
                          , end
                        )
                    );
                    return;
                }
                await_range(++next, end);
            }
            template <typename Iter, typename IsVoid>
            BOOST_FORCEINLINE
            typename boost::enable_if<
                typename traits::is_future_range<
                    typename boost::fusion::result_of::deref<Iter>::type
                >::type
            >::type
            await(Iter const & iter, boost::mpl::false_, IsVoid)
            {
                typedef
                    typename boost::fusion::result_of::next<Iter>::type
                    next_type;
                typedef
                    typename boost::fusion::result_of::end<futures_type>::type
                    end_type;
                await_range(
                    boost::begin(boost::fusion::deref(iter))
                  , boost::end(boost::fusion::deref(iter))
                );
                await(
                    boost::fusion::next(iter)
                  , typename boost::is_same<next_type, end_type>::type()
                  , IsVoid()
                );
            }
            
            template <typename Iter, typename IsVoid>
            BOOST_FORCEINLINE
            typename boost::disable_if<
                typename traits::is_future_range<
                    typename boost::fusion::result_of::deref<Iter>::type
                >::type
            >::type
            await(Iter const & iter, boost::mpl::false_, IsVoid)
            {
                typedef
                    typename boost::fusion::result_of::next<Iter>::type
                    next_type;
                typedef
                    typename boost::fusion::result_of::end<futures_type>::type
                    end_type;
                if(!boost::fusion::deref(iter).ready())
                {
                    if(!result_.valid())
                    {
                        result_ = result_promise_.get_future();
                    }
                    void (dataflow_frame_5::*f)
                        (Iter const &, boost::mpl::false_, IsVoid)
                        = &dataflow_frame_5::await;
                    boost::fusion::deref(iter).then(
                        policy_
                      , boost::bind(
                            f
                          , this->shared_from_this()
                          , iter
                          , boost::mpl::false_()
                          , IsVoid()
                        )
                    );
                    return;
                }
                await(
                    boost::fusion::next(iter)
                  , typename boost::is_same<next_type, end_type>::type()
                  , IsVoid()
                );
            }
            BOOST_FORCEINLINE void await()
            {
                await(
                    boost::fusion::begin(futures_)
                  , boost::mpl::false_()
                  , typename boost::is_same<void, result_type>::type()
                );
            }
            
            BOOST_SCOPED_ENUM(launch) policy_;
            future_result_type result_;
            promise_result_type result_promise_;
        };
    }
    template <typename Func, typename F0 , typename F1 , typename F2 , typename F3 , typename F4>
    BOOST_FORCEINLINE
    typename detail::dataflow_frame_5<
        Func
      , F0 , F1 , F2 , F3 , F4
    >::future_result_type
    dataflow(BOOST_SCOPED_ENUM(launch) policy, BOOST_FWD_REF(Func) func, BOOST_FWD_REF(F0) f0 , BOOST_FWD_REF(F1) f1 , BOOST_FWD_REF(F2) f2 , BOOST_FWD_REF(F3) f3 , BOOST_FWD_REF(F4) f4)
    {
        typedef
            detail::dataflow_frame_5<
                Func
              , F0 , F1 , F2 , F3 , F4
            >
            frame_type;
        boost::shared_ptr<frame_type> frame =
            boost::make_shared<frame_type>(
                policy
              , boost::forward<Func>(func)
              , boost::forward<F0>( f0 ) , boost::forward<F1>( f1 ) , boost::forward<F2>( f2 ) , boost::forward<F3>( f3 ) , boost::forward<F4>( f4 )
            );
        frame->await();
        return frame->result_;
    }
    template <typename Func, typename F0 , typename F1 , typename F2 , typename F3 , typename F4>
    BOOST_FORCEINLINE
    typename detail::dataflow_frame_5<
        Func
      , F0 , F1 , F2 , F3 , F4
    >::future_result_type
    dataflow(BOOST_FWD_REF(Func) func, BOOST_FWD_REF(F0) f0 , BOOST_FWD_REF(F1) f1 , BOOST_FWD_REF(F2) f2 , BOOST_FWD_REF(F3) f3 , BOOST_FWD_REF(F4) f4)
    {
        return dataflow(launch::all, func, boost::forward<F0>( f0 ) , boost::forward<F1>( f1 ) , boost::forward<F2>( f2 ) , boost::forward<F3>( f3 ) , boost::forward<F4>( f4 ));
    }
}}}
