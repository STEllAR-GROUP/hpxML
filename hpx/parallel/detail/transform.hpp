//  Copyright (c) 2007-2014 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

/// \file transform.hpp

#if !defined(HPX_PARALLEL_DETAIL_TRANSFORM_MAY_29_2014_0932PM)
#define HPX_PARALLEL_DETAIL_TRANSFORM_MAY_29_2014_0932PM

#include <hpx/hpx_fwd.hpp>
#include <hpx/exception_list.hpp>
#include <hpx/parallel/execution_policy.hpp>
#include <hpx/parallel/detail/algorithm_result.hpp>
#include <hpx/parallel/detail/zip_iterator.hpp>
#include <hpx/parallel/detail/synchronize.hpp>
#include <hpx/util/move.hpp>

#include <algorithm>
#include <iterator>

#include <boost/static_assert.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_base_of.hpp>

namespace hpx { namespace parallel { HPX_INLINE_NAMESPACE(v1)
{
    ///////////////////////////////////////////////////////////////////////////
    // transform
    namespace detail
    {
        /// \cond NOINTERNAL
        template <typename ExPolicy, typename InIter, typename OutIter,
            typename F>
        typename detail::algorithm_result<ExPolicy, OutIter>::type
        transform(ExPolicy const&, InIter first, InIter last, OutIter dest,
            F && f, boost::mpl::true_)
        {
            try {
                detail::synchronize(first, last);
                return detail::algorithm_result<ExPolicy, OutIter>::get(
                    std::transform(first, last, dest, std::forward<F>(f)));
            }
            catch (...) {
                detail::handle_exception<ExPolicy>::call();
            }
        }

        template <typename ExPolicy, typename FwdIter, typename OutIter,
            typename F>
        typename detail::algorithm_result<ExPolicy, OutIter>::type
        transform(ExPolicy const& policy, FwdIter first, FwdIter last,
            OutIter dest, F && f, boost::mpl::false_ fls)
        {
            typedef boost::tuple<FwdIter, OutIter> iterator_tuple;
            typedef detail::zip_iterator<iterator_tuple> zip_iterator;
            typedef typename zip_iterator::reference reference;
            typedef
                typename detail::algorithm_result<ExPolicy, OutIter>::type
            result_type;

            return get_iter<1, result_type>(
                for_each_n(policy,
                    detail::make_zip_iterator(boost::make_tuple(first, dest)),
                    std::distance(first, last),
                    [f](reference it) {
                        *boost::get<1>(it) = f(*boost::get<0>(it));
                    },
                    fls));
        }

        template <typename InIter, typename OutIter, typename F>
        OutIter transform(execution_policy const& policy,
            InIter first, InIter last, OutIter dest, F && f, boost::mpl::false_)
        {
            HPX_PARALLEL_DISPATCH(policy, detail::transform, first, last, dest,
                std::forward<F>(f));
        }

        template <typename InIter, typename OutIter, typename F>
        OutIter transform(execution_policy const& policy,
            InIter first, InIter last, OutIter dest, F && f, boost::mpl::true_ t)
        {
            return detail::transform(sequential_execution_policy(),
                first, last, dest, std::forward<F>(f), t);
        }
        /// \endcond
    }

    /// Applies the given function \a f to the range [first, last) and stores
    /// the result in another range, beginning at dest.
    ///
    /// \note   Complexity: Exactly \a last - \a first applications of \a f
    ///
    /// \tparam ExPolicy    The type of the execution policy to use (deduced).
    ///                     It describes the manner in which the execution
    ///                     of the algorithm may be parallelized and the manner
    ///                     in which it executes the invocations of \a f.
    /// \tparam InIter      The type of the source iterators used (deduced).
    ///                     This iterator type must meet the requirements of an
    ///                     input iterator.
    /// \tparam OutIter     The type of the iterator representing the
    ///                     destination range (deduced).
    ///                     This iterator type must meet the requirements of an
    ///                     output iterator.
    /// \tparam F           The type of the function/function object to use
    ///                     (deduced). Unlike its sequential form, the parallel
    ///                     overload of \a transform requires \a F to meet the
    ///                     requirements of \a CopyConstructible.
    ///
    /// \param policy       The execution policy to use for the scheduling of
    ///                     the iterations.
    /// \param first        Refers to the beginning of the sequence of elements
    ///                     the algorithm will be applied to.
    /// \param last         Refers to the end of the sequence of elements the
    ///                     algorithm will be applied to.
    /// \param dest         Refers to the beginning of the destination range.
    /// \param f            Specifies the function (or function object) which
    ///                     will be invoked for each of the elements in the
    ///                     sequence specified by [first, last).This is an
    ///                     unary predicate. The signature of this predicate
    ///                     should be equivalent to:
    ///                     \code
    ///                     Ret fun(const Type &a);
    ///                     \endcode \n
    ///                     The signature does not need to have const&.
    ///                     The type \a Type must be such that an object of
    ///                     type \a InIter can be dereferenced and then
    ///                     implicitly converted to \a Type. The type \a Ret
    ///                     must be such that an object of type \a OutIter can
    ///                     be dereferenced and assigned a value of type
    ///                     \a Ret.
    ///
    /// The invocations of \a f in the parallel \a transform algorithm invoked
    /// with an execution policy object of type \a sequential_execution_policy
    /// execute in sequential order in the calling thread.
    ///
    /// The invocations of \a f in the parallel \a transform algorithm invoked
    /// with an execution policy object of type \a parallel_execution_policy or
    /// \a task_execution_policy are permitted to execute in an unordered
    /// fashion in unspecified threads, and indeterminately sequenced
    /// within each thread.
    ///
    /// \returns  The \a transform algorithm returns a \a hpx::future<OutIter>
    ///           if the execution policy is of type \a task_execution_policy
    ///           and returns \a OutIter otherwise.
    ///           The \a transform algorithm returns the output iterator to the
    ///           element in the destination range, one past the last element
    ///           copied.
    ///
    template <typename ExPolicy, typename InIter, typename OutIter, typename F>
    inline typename boost::enable_if<
        is_execution_policy<ExPolicy>,
        typename detail::algorithm_result<ExPolicy, OutIter>::type
    >::type
    transform(ExPolicy&& policy, InIter first, InIter last, OutIter dest, F && f)
    {
        typedef typename std::iterator_traits<InIter>::iterator_category
            iterator_category;

        BOOST_STATIC_ASSERT_MSG(
            (boost::is_base_of<std::input_iterator_tag, iterator_category>::value),
            "Required at least input iterator.");

        typedef typename boost::mpl::or_<
            is_sequential_execution_policy<ExPolicy>,
            boost::is_same<std::input_iterator_tag, iterator_category>
        >::type is_seq;

        return detail::transform(std::forward<ExPolicy>(policy),
            first, last, dest, std::forward<F>(f), is_seq());
    }

    ///////////////////////////////////////////////////////////////////////////
    // transform binary predicate
    namespace detail
    {
        /// \cond NOINTERNAL
        template <typename ExPolicy, typename InIter1, typename InIter2,
            typename OutIter, typename F>
        typename detail::algorithm_result<ExPolicy, OutIter>::type
        transform_binary(ExPolicy const&, InIter1 first1, InIter1 last1,
            InIter2 first2, OutIter dest, F && f, boost::mpl::true_)
        {
            try {
                detail::synchronize_binary(first1, last1, first2);
                return detail::algorithm_result<ExPolicy, OutIter>::get(
                    std::transform(first1, last1, first2, dest,
                        std::forward<F>(f)));
            }
            catch (...) {
                detail::handle_exception<ExPolicy>::call();
            }
        }

        template <typename ExPolicy, typename FwdIter1, typename FwdIter2,
            typename OutIter, typename F>
        typename detail::algorithm_result<ExPolicy, OutIter>::type
        transform_binary(ExPolicy const& policy, FwdIter1 first1, FwdIter1 last1,
            FwdIter2 first2, OutIter dest, F && f, boost::mpl::false_ fls)
        {
            typedef boost::tuple<FwdIter1, FwdIter2, OutIter> iterator_tuple;
            typedef detail::zip_iterator<iterator_tuple> zip_iterator;
            typedef typename zip_iterator::reference reference;
            typedef
                typename detail::algorithm_result<ExPolicy, OutIter>::type
            result_type;

            return get_iter<2, result_type>(
                for_each_n(policy,
                    detail::make_zip_iterator(boost::make_tuple(first1, first2, dest)),
                    std::distance(first1, last1),
                    [f](reference it) {
                        *boost::get<2>(it) =
                            f(*boost::get<0>(it), *boost::get<1>(it));
                    },
                    fls));
        }

        template <typename InIter1, typename InIter2, typename OutIter,
            typename F>
        OutIter transform_binary(execution_policy const& policy,
            InIter1 first1, InIter1 last1, InIter2 first2, OutIter dest,
            F && f, boost::mpl::false_)
        {
            HPX_PARALLEL_DISPATCH(policy, detail::transform_binary, first1,
                last1, first2, dest, std::forward<F>(f));
        }

        template<typename InIter1, typename InIter2, typename OutIter,
            typename F>
        OutIter transform_binary(execution_policy const& policy,
            InIter1 first1, InIter1 last1, InIter2 first2, OutIter dest,
            F && f, boost::mpl::true_ t)
        {
            return detail::transform_binary(sequential_execution_policy(),
                first1, last1, first2, dest, std::forward<F>(f),
                t);
        }
        /// \endcond
    }

    /// Applies the given function \a f to pairs of elements from two ranges:
    /// one defined by [first1, last1) and the other beginning at first2, and
    /// stores the result in another range, beginning at dest.
    ///
    /// \note   Complexity: Exactly \a last - \a first applications of \a f
    ///
    /// \tparam ExPolicy    The type of the execution policy to use (deduced).
    ///                     It describes the manner in which the execution
    ///                     of the algorithm may be parallelized and the manner
    ///                     in which it executes the invocations of \a f.
    /// \tparam InIter1     The type of the source iterators for the first
    ///                     range used (deduced).
    ///                     This iterator type must meet the requirements of an
    ///                     input iterator.
    /// \tparam InIter2     The type of the source iterators for the second
    ///                     range used (deduced).
    ///                     This iterator type must meet the requirements of an
    ///                     input iterator.
    /// \tparam OutIter     The type of the iterator representing the
    ///                     destination range (deduced).
    ///                     This iterator type must meet the requirements of an
    ///                     output iterator.
    /// \tparam F           The type of the function/function object to use
    ///                     (deduced). Unlike its sequential form, the parallel
    ///                     overload of \a transform requires \a F to meet the
    ///                     requirements of \a CopyConstructible.
    ///
    /// \param policy       The execution policy to use for the scheduling of
    ///                     the iterations.
    /// \param first1       Refers to the beginning of the first sequence of
    ///                     elements the algorithm will be applied to.
    /// \param last1        Refers to the end of the first sequence of elements
    ///                     the algorithm will be applied to.
    /// \param first2       Refers to the beginning of the second sequence of
    ///                     elements the algorithm will be applied to.
    /// \param dest         Refers to the beginning of the destination range.
    /// \param f            Specifies the function (or function object) which
    ///                     will be invoked for each of the elements in the
    ///                     sequence specified by [first, last).This is a
    ///                     binary predicate. The signature of this predicate
    ///                     should be equivalent to:
    ///                     \code
    ///                     Ret fun(const Type1 &a, const Type2 &b);
    ///                     \endcode \n
    ///                     The signature does not need to have const&.
    ///                     The types \a Type1 and \a Type2 must be such that
    ///                     objects of types InIter1 and InIter2 can be
    ///                     dereferenced and then implicitly converted to
    ///                     \a Type1 and \a Type2 respectively. The type \a Ret
    ///                     must be such that an object of type \a OutIter can
    ///                     be dereferenced and assigned a value of type
    ///                     \a Ret.
    ///
    /// The invocations of \a f in the parallel \a transform algorithm invoked
    /// with an execution policy object of type \a sequential_execution_policy
    /// execute in sequential order in the calling thread.
    ///
    /// The invocations of \a f in the parallel \a transform algorithm invoked
    /// with an execution policy object of type \a parallel_execution_policy or
    /// \a task_execution_policy are permitted to execute in an unordered
    /// fashion in unspecified threads, and indeterminately sequenced
    /// within each thread.
    ///
    /// \returns  The \a transform algorithm returns a \a hpx::future<OutIter>
    ///           if the execution policy is of type \a task_execution_policy
    ///           and returns \a OutIter otherwise.
    ///           The \a transform algorithm returns the output iterator to the
    ///           element in the destination range, one past the last element
    ///           copied.
    ///
    template <typename ExPolicy, typename InIter1, typename InIter2,
        typename OutIter, typename F>
    inline typename boost::enable_if<
        is_execution_policy<ExPolicy>,
        typename detail::algorithm_result<ExPolicy, OutIter>::type
    >::type
    transform(ExPolicy && policy, InIter1 first1, InIter1 last1, InIter2 first2,
        OutIter dest, F && f)
    {
        typedef typename std::iterator_traits<InIter1>::iterator_category category1;
        typedef typename std::iterator_traits<InIter2>::iterator_category category2;

        BOOST_STATIC_ASSERT_MSG(
            (boost::is_base_of<std::input_iterator_tag, category1>::value),
            "Required at least input iterator.");
        BOOST_STATIC_ASSERT_MSG(
            (boost::is_base_of<std::input_iterator_tag, category2>::value),
            "Required at least input iterator.");

        typedef typename boost::mpl::or_<
            is_sequential_execution_policy<ExPolicy>,
            boost::is_same<std::input_iterator_tag, category1>,
            boost::is_same<std::input_iterator_tag, category2>
        >::type is_seq;

        return detail::transform_binary(
            std::forward<ExPolicy>(policy),
            first1, last1, first2, dest, std::forward<F>(f), is_seq());
    }
}}}

#endif
