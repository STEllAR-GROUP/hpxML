//  Copyright (c) 2014 Grant Mercer
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

/// \file parallel/algorithms/move.hpp

#if !defined(HPX_PARALLEL_DETAIL_MOVE_JUNE_16_2014_1106AM)
#define HPX_PARALLEL_DETAIL_MOVE_JUNE_16_2014_1106AM

#include <hpx/hpx_fwd.hpp>
#include <hpx/util/move.hpp>

#include <hpx/parallel/config/inline_namespace.hpp>
#include <hpx/parallel/execution_policy.hpp>
#include <hpx/parallel/algorithms/detail/dispatch.hpp>
#include <hpx/parallel/algorithms/for_each.hpp>
#include <hpx/parallel/util/detail/algorithm_result.hpp>
#include <hpx/parallel/util/zip_iterator.hpp>
#include <hpx/parallel/algorithms/algo.hpp>
#include <hpx/parallel/segmented_algorithms/algo.hpp>

#include <algorithm>
#include <iterator>

#include <boost/static_assert.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_base_of.hpp>

namespace hpx { namespace parallel { HPX_INLINE_NAMESPACE(v1)
{
    ///////////////////////////////////////////////////////////////////////////
    // move
    namespace detail
    {
        /// \cond NOINTERNAL

        template <typename OutIter>
        struct move : public detail::algorithm<move<OutIter>, OutIter>
        {
            move()
              : move::algorithm("move")
            {}

            template <typename ExPolicy, typename InIter, typename OutIter_>
            static OutIter_
            sequential(ExPolicy, InIter first, InIter last, OutIter_ dest)
            {
                return std::move(first, last, dest);
            }

            template <typename ExPolicy, typename FwdIter, typename OutIter_>
            static typename util::detail::algorithm_result<
                ExPolicy, OutIter_
            >::type
            parallel(ExPolicy policy, FwdIter first, FwdIter last,
                OutIter_ dest)
            {
                typedef hpx::util::zip_iterator<FwdIter, OutIter_> zip_iterator;
                typedef typename zip_iterator::reference reference;
                typedef typename util::detail::algorithm_result<
                        ExPolicy, OutIter_
                    >::type result_type;

                return get_iter<1, result_type>(
                    for_each_n<zip_iterator>().call(
                        policy, boost::mpl::false_(),
                        hpx::util::make_zip_iterator(first, dest),
                        std::distance(first, last),
                        [](reference t) {
                            using hpx::util::get;
                            get<1>(t) = std::move(get<0>(t)); //-V573
                        }));
            }
        };
    }

    /// Moves the elements in the range [first, last), to another range
    /// beginning at \a dest. After this operation the elements in the
    /// moved-from range will still contain valid values of the appropriate
    /// type, but not necessarily the same values as before the move.
    ///
    /// \note   Complexity: Performs exactly \a last - \a first move assignments.
    ///
    /// \tparam ExPolicy    The type of the execution policy to use (deduced).
    ///                     It describes the manner in which the execution
    ///                     of the algorithm may be parallelized and the manner
    ///                     in which it executes the move assignments.
    /// \tparam InIter      The type of the source iterators used (deduced).
    ///                     This iterator type must meet the requirements of an
    ///                     input iterator.
    /// \tparam OutIter     The type of the iterator representing the
    ///                     destination range (deduced).
    ///                     This iterator type must meet the requirements of an
    ///                     output iterator.
    ///
    /// \param policy       The execution policy to use for the scheduling of
    ///                     the iterations.
    /// \param first        Refers to the beginning of the sequence of elements
    ///                     the algorithm will be applied to.
    /// \param last         Refers to the end of the sequence of elements the
    ///                     algorithm will be applied to.
    /// \param dest         Refers to the beginning of the destination range.
    ///
    /// The move assignments in the parallel \a move algorithm invoked
    /// with an execution policy object of type
    /// \a sequential_execution_policy execute in sequential order in
    /// the calling thread.
    ///
    /// The move assignments in the parallel \a move algorithm invoked
    /// with an execution policy object of type
    /// \a parallel_execution_policy or \a parallel_task_execution_policy are
    /// permitted to execute in an unordered fashion in unspecified
    /// threads, and indeterminately sequenced within each thread.
    ///
    /// \returns  The \a move algorithm returns a \a hpx::future<OutIter> if
    ///           the execution policy is of type
    ///           \a sequential_task_execution_policy or
    ///           \a parallel_task_execution_policy and
    ///           returns \a OutIter otherwise.
    ///           The \a move algorithm returns the output iterator to the
    ///           element in the destination range, one past the last element
    ///           copied.
    template <typename ExPolicy, typename InIter, typename OutIter>
    inline typename boost::enable_if<
        is_execution_policy<ExPolicy>,
        typename util::detail::algorithm_result<ExPolicy, OutIter>::type
    >::type
    move(ExPolicy && policy, InIter first, InIter last, OutIter dest)
    {
        typedef hpx::traits::segmented_iterator_traits<OutIter>
            output_iterator_traits;
        return algo<detail::move<OutIter>,
            detail::move<typename output_iterator_traits::local_iterator>>(
            policy, first, last, dest);
    }
}}}

#endif
