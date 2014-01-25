//  Copyright (c) 2007-2013 Hartmut Kaiser
//  Copyright (c) 2013 Agustin Berge
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !BOOST_PP_IS_ITERATING

#if !defined(HPX_LCOS_WHEN_N_APR_19_2012_0203PM)
#define HPX_LCOS_WHEN_N_APR_19_2012_0203PM

#include <hpx/hpx_fwd.hpp>
#include <hpx/lcos/future.hpp>
#include <hpx/lcos/local/packaged_task.hpp>
#include <hpx/lcos/local/packaged_continuation.hpp>
#include <hpx/runtime/threads/thread.hpp>
#include <hpx/util/assert.hpp>
#include <hpx/util/always_void.hpp>
#include <hpx/util/bind.hpp>
#include <hpx/util/decay.hpp>
#include <hpx/util/move.hpp>
#include <hpx/util/tuple.hpp>
#include <hpx/util/detail/pp_strip_parens.hpp>

#include <boost/atomic.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/is_sequence.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/enum.hpp>
#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repeat.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/utility/enable_if.hpp>

#include <algorithm>
#include <iterator>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace lcos
{
    namespace detail
    {
        template <typename Future>
        struct when_acquire_future
        {
            typedef Future result_type;

            template <typename R>
            BOOST_FORCEINLINE hpx::unique_future<R>
            operator()(hpx::unique_future<R>& future) const
            {
                return std::move(future);
            }

            template <typename R>
            BOOST_FORCEINLINE hpx::shared_future<R>
            operator()(hpx::shared_future<R>& future) const
            {
                return future;
            }

#if defined(HPX_ENABLE_DEPRECATED_FUTURE)
            template <typename Result>
            BOOST_FORCEINLINE hpx::future<Result>
            operator()(hpx::future<Result>& future) const
            {
                return future;
            }
#endif
        };

        ///////////////////////////////////////////////////////////////////////
        template <typename Sequence>
        struct when_n;

        template <typename Sequence, typename Callback>
        struct set_when_on_completed_callback_impl
        {
            explicit set_when_on_completed_callback_impl(
                    when_n<Sequence>& when, Callback const& callback)
              : when_(when),
                callback_(callback)
            {}

            template <typename Future>
            void operator()(Future& future) const
            {
                std::size_t counter = when_.count_.load(boost::memory_order_acquire);
                if (counter < when_.needed_count_ && !future.is_ready()) {
                    // handle future only if not enough futures are ready yet
                    // also, do not touch any futures which are already ready

                    typedef
                        typename lcos::detail::shared_state_ptr_for<Future>::type
                        shared_state_ptr;

                    using lcos::detail::future_access;
                    shared_state_ptr const& shared_state =
                        future_access::get_shared_state(future);

                    shared_state->set_on_completed(Callback(callback_));
                }
                else {
                    ++when_.count_;
                }
            }

            template <typename Sequence_>
            void apply(Sequence_& sequence, typename boost::enable_if<
                boost::fusion::traits::is_sequence<Sequence_> >::type* = 0) const
            {
                boost::fusion::for_each(sequence, *this);
            }

            template <typename Sequence_>
            void apply(Sequence_& sequence, typename boost::disable_if<
                boost::fusion::traits::is_sequence<Sequence_> >::type* = 0) const
            {
                std::for_each(sequence.begin(), sequence.end(), *this);
            }

            when_n<Sequence>& when_;
            Callback const& callback_;
        };

        template <typename Sequence, typename Callback>
        void set_on_completed_callback(when_n<Sequence>& when,
            Callback const& callback)
        {
            set_when_on_completed_callback_impl<Sequence, Callback>
                set_on_completed_callback_helper(when, callback);
            set_on_completed_callback_helper.apply(when.lazy_values_);
        }

        template <typename Sequence>
        struct when_n : boost::enable_shared_from_this<when_n<Sequence> >
        {
        private:
            void on_future_ready(threads::thread_id_type const& id)
            {
                if (count_.fetch_add(1) + 1 == needed_count_)
                {
                    // reactivate waiting thread only if it's not us
                    if (id != threads::get_self_id())
                        threads::set_thread_state(id, threads::pending);
                }
            }

        private:
            // workaround gcc regression wrongly instantiating constructors
            when_n();
            when_n(when_n const&);

        public:
            typedef Sequence argument_type;
            typedef Sequence result_type;

            when_n(argument_type && lazy_values, std::size_t n)
              : lazy_values_(std::move(lazy_values))
              , count_(0)
              , needed_count_(n)
            {}

            result_type operator()()
            {
                // set callback functions to executed when future is ready
                set_on_completed_callback(*this,
                    util::bind(
                        &when_n::on_future_ready, this->shared_from_this(),
                        threads::get_self_id()));

                // if all of the requested futures are already set, our
                // callback above has already been called often enough, otherwise
                // we suspend ourselves
                if (count_.load(boost::memory_order_acquire) < needed_count_)
                {
                    // wait for any of the futures to return to become ready
                    this_thread::suspend(threads::suspended);
                }

                // at least N futures should be ready
                HPX_ASSERT(count_.load(boost::memory_order_acquire) >= needed_count_);

                return std::move(lazy_values_);
            }

            result_type lazy_values_;
            boost::atomic<std::size_t> count_;
            std::size_t needed_count_;
        };
    }

    /// The function \a when_n is a operator allowing to join on the result
    /// of all given futures. It AND-composes all future objects given and
    /// returns a new future object representing the same list of futures
    /// after n of them finished executing.
    ///
    /// \note There are three variations of when_n. The first takes a pair
    ///       of InputIterators. The second takes an std::vector of future<R>.
    ///       The third takes any arbitrary number of future<R>, where R need
    ///       not be the same type.
    ///
    /// \return   Returns a future holding the same list of futures as has
    ///           been passed to when_n.
    ///           - future<vector<future<R>>>: If the input cardinality is
    ///             unknown at compile time and the futures are all of the
    ///             same type.
    ///           - future<tuple<future<R0>, future<R1>, future<R2>...>>: If
    ///             inputs are fixed in number and are of heterogeneous types.
    ///             The inputs can be any arbitrary number of future objects.

    template <typename Future>
    lcos::unique_future<std::vector<Future> >
    when_n(std::size_t n,
        std::vector<Future>& lazy_values,
        error_code& ec = throws)
    {
        BOOST_STATIC_ASSERT_MSG(
            traits::is_future<Future>::value, "invalid use of when_n");

        typedef std::vector<Future> result_type;

        if (n == 0)
        {
            return lcos::make_ready_future(std::move(lazy_values));
        }

        if (n > lazy_values.size())
        {
            HPX_THROWS_IF(ec, hpx::bad_parameter,
                "hpx::lcos::when_n",
                "number of results to wait for is out of bounds");
            return lcos::make_ready_future(result_type());
        }

        result_type lazy_values_;
        lazy_values_.reserve(lazy_values.size());
        std::transform(lazy_values.begin(), lazy_values.end(),
            std::back_inserter(lazy_values_),
            detail::when_acquire_future<Future>());

        boost::shared_ptr<detail::when_n<result_type> > f =
            boost::make_shared<detail::when_n<result_type> >(
                std::move(lazy_values_), n);

        lcos::local::futures_factory<result_type()> p(
            util::bind(&detail::when_n<result_type>::operator(), f));

        p.apply();
        return p.get_future();
    }

    template <typename Future>
    lcos::unique_future<std::vector<Future> > //-V659
    when_n(std::size_t n,
        std::vector<Future> && lazy_values,
        error_code& ec = throws)
    {
        return when_n(n, lazy_values, ec);
    }

    template <typename Iterator>
    lcos::unique_future<std::vector<
        typename lcos::detail::future_iterator_traits<Iterator>::type
    > >
    when_n(std::size_t n, Iterator begin, Iterator end,
        error_code& ec = throws)
    {
        typedef
            typename lcos::detail::future_iterator_traits<Iterator>::type
            future_type;
        typedef std::vector<future_type> result_type;

        result_type lazy_values_;
        std::transform(begin, end, std::back_inserter(lazy_values_),
            detail::when_acquire_future<future_type>());
        return when_n(n, lazy_values_, ec);
    }

    inline lcos::unique_future<HPX_STD_TUPLE<> >
    when_n(std::size_t n, error_code& ec = throws)
    {
        typedef HPX_STD_TUPLE<> result_type;

        result_type lazy_values;

        if (n == 0)
        {
            return lcos::make_ready_future(std::move(lazy_values));
        }

        //if (n > 0)
        //{
            HPX_THROWS_IF(ec, hpx::bad_parameter,
                "hpx::lcos::when_n",
                "number of results to wait for is out of bounds");
            return lcos::make_ready_future(result_type());
        //}
    }
}}

#if !defined(HPX_USE_PREPROCESSOR_LIMIT_EXPANSION)
#  include <hpx/lcos/preprocessed/when_n.hpp>
#else

#if defined(__WAVE__) && defined(HPX_CREATE_PREPROCESSED_FILES)
#  pragma wave option(preserve: 1, line: 0, output: "preprocessed/when_n_" HPX_LIMIT_STR ".hpp")
#endif

#define BOOST_PP_ITERATION_PARAMS_1                                           \
    (3, (1, HPX_WAIT_ARGUMENT_LIMIT, <hpx/lcos/when_n.hpp>))                  \
/**/
#include BOOST_PP_ITERATE()

#if defined(__WAVE__) && defined (HPX_CREATE_PREPROCESSED_FILES)
#  pragma wave option(output: null)
#endif

#endif // !defined(HPX_USE_PREPROCESSOR_LIMIT_EXPANSION)

namespace hpx
{
    using lcos::when_n;
}

#endif

///////////////////////////////////////////////////////////////////////////////
#else // BOOST_PP_IS_ITERATING

#define N BOOST_PP_ITERATION()

#define HPX_WHEN_N_DECAY_FUTURE(Z, N, D)                                      \
    typename util::decay<BOOST_PP_CAT(T, N)>::type                            \
    /**/
#define HPX_WHEN_N_ACQUIRE_FUTURE(Z, N, D)                                    \
    detail::when_acquire_future<BOOST_PP_CAT(T, N)>()(BOOST_PP_CAT(f, N))     \
    /**/

namespace hpx { namespace lcos
{
    ///////////////////////////////////////////////////////////////////////////
    template <BOOST_PP_ENUM_PARAMS(N, typename T)>
    lcos::unique_future<HPX_STD_TUPLE<BOOST_PP_ENUM(N, HPX_WHEN_N_DECAY_FUTURE, _)> >
    when_n(std::size_t n, HPX_ENUM_FWD_ARGS(N, T, f),
        error_code& ec = throws)
    {
        typedef HPX_STD_TUPLE<
            BOOST_PP_ENUM(N, HPX_WHEN_N_DECAY_FUTURE, _)>
            result_type;

        result_type lazy_values(BOOST_PP_ENUM(N, HPX_WHEN_N_ACQUIRE_FUTURE, _));

        if (n == 0)
        {
            return lcos::make_ready_future(std::move(lazy_values));
        }

        if (n > N)
        {
            HPX_THROWS_IF(ec, hpx::bad_parameter,
                "hpx::lcos::when_n",
                "number of results to wait for is out of bounds");
            return lcos::make_ready_future(result_type());
        }

        boost::shared_ptr<detail::when_n<result_type> > f =
            boost::make_shared<detail::when_n<result_type> >(
                std::move(lazy_values), n);

        lcos::local::futures_factory<result_type()> p(
            util::bind(&detail::when_n<result_type>::operator(), f));

        p.apply();
        return p.get_future();
    }
}}

#undef HPX_WHEN_N_DECAY_FUTURE
#undef HPX_WHEN_N_ACQUIRE_FUTURE
#undef N

#endif

