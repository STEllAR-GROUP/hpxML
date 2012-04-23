//  Copyright (c) 2007-2012 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !BOOST_PP_IS_ITERATING

#if !defined(HPX_LCOS_WAIT_ANY_APR_17_2012_1143AM)
#define HPX_LCOS_WAIT_ANY_APR_17_2012_1143AM

#include <hpx/hpx_fwd.hpp>
#include <hpx/runtime/threads/thread.hpp>
#include <hpx/lcos/future.hpp>
#include <hpx/lcos/local/spinlock.hpp>
#include <hpx/lcos/local/packaged_task.hpp>
#include <hpx/util/bind.hpp>
#include <hpx/util/tuple.hpp>
#include <hpx/util/unlock_lock.hpp>
#include <hpx/util/detail/pp_strip_parens.hpp>

#include <vector>

#include <boost/assert.hpp>
#include <boost/move/move.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/enum.hpp>
#include <boost/preprocessor/iterate.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace hpx
{
    namespace detail
    {
        template <typename T, typename RT>
        struct wait_any
        {
        private:
            BOOST_MOVABLE_BUT_NOT_COPYABLE(wait_any)

            static const std::size_t index_error = std::size_t(-1);

            void on_future_ready(std::size_t idx, threads::thread_id_type id)
            {
                mutex_type::scoped_lock l(mtx_);
                if (index_ == index_error) {
                    index_ = idx;
                    threads::set_thread_state(id, threads::pending);
                }
            }

        public:
            typedef lcos::local::spinlock mutex_type;
            typedef HPX_STD_TUPLE<int, lcos::future<T, RT> > result_type;
            typedef std::vector<lcos::future<T, RT> > argument_type;

            wait_any(argument_type const& lazy_values)
              : lazy_values_(lazy_values), index_(index_error)
            {}

            wait_any(BOOST_RV_REF(argument_type) lazy_values)
              : lazy_values_(boost::move(lazy_values)), index_(index_error)
            {}

            wait_any(BOOST_RV_REF(wait_any) rhs)
              : lazy_values_(boost::move(rhs.lazy_values_)),
                index_(rhs.index_),
                mtx_(boost::move(rhs.mtx_))
            {
                rhs.index_ = index_error;
            }

            wait_any& operator= (BOOST_RV_REF(wait_any) rhs)
            {
                if (this != &rhs) {
                    mutex_type::scoped_lock l1(mtx_);
                    mutex_type::scoped_lock l2(rhs.mtx_);
                    lazy_values_ = boost::move(rhs.lazy_values_);
                    index_ = rhs.index_;
                    rhs.index_ = index_error;
                    mtx_ = boost::move(rhs.mtx_);
                }
                return *this;
            }

            result_type operator()()
            {
                mutex_type::scoped_lock l(mtx_);
                index_ = index_error;

                {
                    util::unlock_the_lock<mutex_type::scoped_lock> ul(l);

                    // set callback functions to executed when future is ready
                    threads::thread_id_type id = threads::get_self().get_thread_id();
                    for (std::size_t i = 0; i < lazy_values_.size(); ++i)
                    {
                        lazy_values_[i].when(
                            util::bind(&wait_any::on_future_ready, this, i, id)
                        );
                    }
                }

                // if one of the futures is already set, our callback above has
                // already been called, otherwise we suspend ourselves
                if (index_ == index_error)
                {
                    // wait for any of the futures to return to become ready
                    util::unlock_the_lock<mutex_type::scoped_lock> ul(l);
                    this_thread::suspend(threads::suspended);
                }

                BOOST_ASSERT(index_ != index_error);       // that should not happen

                // reset all pending callback functions
                l.unlock();
                for (std::size_t i = 0; i < lazy_values_.size(); ++i)
                    lazy_values_[i].when();

                return result_type(static_cast<int>(index_), lazy_values_[index_]);
            }

            std::vector<lcos::future<T, RT> > lazy_values_;
            std::size_t index_;
            mutable mutex_type mtx_;
        };
    }

    /// The function \a wait_any is a non-deterministic choice operator. It
    /// OR-composes all future objects stored in the given vector and returns
    /// a new future object representing the first future from that list which
    /// finishes execution.
    ///
    /// \return   The returned future holds a pair of values, the first value
    ///           is the index of the future which returned first and the second
    ///           value represents the actual future which returned first.
    template <typename T, typename RT>
    lcos::future<HPX_STD_TUPLE<int, lcos::future<T, RT> > >
    wait_any (BOOST_RV_REF(HPX_UTIL_STRIP((
        std::vector<lcos::future<T, RT> >))) lazy_values)
    {
        typedef HPX_STD_TUPLE<int, lcos::future<T, RT> > return_type;
        lcos::local::packaged_task<return_type()> p(
            detail::wait_any<T, RT>(boost::move(lazy_values)));
        p.apply();
        return p.get_future();
    }

    template <typename T, typename RT>
    lcos::future<HPX_STD_TUPLE<int, lcos::future<T, RT> > >
    wait_any (std::vector<lcos::future<T, RT> > const& lazy_values)
    {
        typedef HPX_STD_TUPLE<int, lcos::future<T, RT> > return_type;
        lcos::local::packaged_task<return_type()> p =
            lcos::local::packaged_task<return_type()>(
                detail::wait_any<T, RT>(lazy_values));
        p.apply();
        return p.get_future();
    }
}

#define BOOST_PP_ITERATION_PARAMS_1                                           \
    (3, (1, HPX_FUNCTION_LIMIT, <hpx/lcos/wait_any.hpp>))                     \
/**/
#include BOOST_PP_ITERATE()

#endif

///////////////////////////////////////////////////////////////////////////////
#else // BOOST_PP_IS_ITERATING

#define N BOOST_PP_ITERATION()

#define HPX_WAIT_ANY_PUSH_BACK_ARGS(z, n, _)                                  \
        lazy_values.push_back(BOOST_PP_CAT(f, n));                            \
    /**/
#define HPX_WAIT_ANY_FUTURE_ARGS(z, n, _)                                     \
        lcos::future<T, RT> BOOST_PP_CAT(f, n)                                \
    /**/

namespace hpx
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename T, typename RT>
    lcos::future<HPX_STD_TUPLE<int, lcos::future<T, RT> > >
    wait_any (BOOST_PP_ENUM(N, HPX_WAIT_ANY_FUTURE_ARGS, _))
    {
        std::vector<lcos::future<T, RT> > lazy_values;
        lazy_values.reserve(N);
        BOOST_PP_REPEAT(N, HPX_WAIT_ANY_PUSH_BACK_ARGS, _)

        typedef HPX_STD_TUPLE<int, lcos::future<T, RT> > return_type;
        lcos::local::packaged_task<return_type()> p(
            detail::wait_any<T, RT>(boost::move(lazy_values)));
        p.apply();
        return p.get_future();
    }
}

#undef HPX_WAIT_ANY_FUTURE_ARGS
#undef HPX_WAIT_ANY_PUSH_BACK_ARGS
#undef N

#endif

