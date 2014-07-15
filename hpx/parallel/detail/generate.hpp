//  Copyright (c) 2014 Grant Mercer
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

/// \file parallel/detail/generate.hpp

#if !defined(HPX_PARALLEL_DETAIL_GENERATE_JULY_15_2014_0224PM)
#define HPX_PARALLEL_DETAIL_GENERATE_JULY_15_2014_0224PM

#include <hpx/hpx_fwd.hpp>
#include <hpx/parallel/execution_policy.hpp>
#include <hpx/parallel/detail/algorithm_result.hpp>

#include <algorithm>
#include <iterator>

#include <boost/static_assert.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_base_of.hpp>

namespace hpx { namespace parallel { HPX_INLINE_NAMESPACE(v1)
{
    ///////////////////////////////////////////////////////////////////////////
    // generate
    namespace detail
    {
        /// \cond NOINTERNAL
        struct generate : public detail::algorithm<generate>
        {
            generate()
                : detail::algorithm<generate>("generate")
            {}

            template <typename ExPolicy, typename InIter, typename F>
            static typename detail::algorithm_result<ExPolicy>::type
            sequential(ExPolicy const&, InIter first, InIter last, F && f)
            {
                std::generate(first, last, std::forward<F>(f));
                return detail::algorithm_result<ExPolicy>::get();
            }

            template <typename ExPolicy, typename FwdIter, typename F>
            static typename detail::algorithm_result<ExPolicy>::type
            parallel(ExPolicy const& policy, FwdIter first, FwdIter last, F && f)
            {
                typedef typename detail::algorithm_result<ExPolicy>::type
                    result_type;
                typedef typename std::iterator_traits<FwdIter>::value_type type;

                return hpx::util::void_guard<result_type>(),
                    for_each_n<FwdIter>().call(
                        policy, first, std::distance(first, last),
                        [f](type& v){
                            v = f();
                        },
                        boost::mpl::false_());
            }
        };
        /// \endcond
    }

    template <typename ExPolicy, typename InIter, typename F>
    inline typename boost::enable_if<
        is_execution_policy<ExPolicy>,
        typename detail::algorithm_result<ExPolicy, void>::type
    >::type
    generate(ExPolicy && policy, InIter first, InIter last, F && f)
    {
        typedef typename std::iterator_traits<InIter>::iterator_category
            iterator_category;

        BOOST_STATIC_ASSERT_MSG(
            (boost::is_base_of<
                std::forward_iterator_tag, iterator_category>::value),
            "Required at least forward iterator.");
            
        typedef typename is_sequential_execution_policy<ExPolicy>::type is_seq;

        return detail::generate().call(
            std::forward<ExPolicy>(policy),
            first, last, std::forward<F>(f), is_seq());
    }

    ///////////////////////////////////////////////////////////////////////////
    // generate_n
    namespace detail
    {
        /// \cond NOINTERNAL
        template <typename OutIter>
        struct generate_n: public detail::algorithm<generate_n<OutIter>, OutIter>
        {
            generate_n()
                : detail::algorithm<generate_n<OutIter>, OutIter>("generate_n")
            {}

            template <typename ExPolicy, typename F>
            static typename detail::algorithm_result<ExPolicy, OutIter>::type
            sequential(ExPolicy const&, OutIter first, std::size_t count, F && f)
            {
                return detail::algorithm_result<ExPolicy, OutIter>::get(
                    std::generate_n(first, count, f));
            }

            template <typename ExPolicy, typename F>
            static typename detail::algorithm_result<ExPolicy, OutIter>::type
            parallel(ExPolicy const& policy, OutIter first, std::size_t count,
                F && f)
            {
                typedef typename std::iterator_traits<OutIter>::iterator_category
                    category;
                typedef typename std::iterator_traits<OutIter>::value_type type;

                return
                    for_each_n<OutIter>().call(
                        policy, first, count,
                        [f](type& v) {
                            v = f();
                        },
                        boost::mpl::false_());
            }
        };
        /// \endcond
    }

    template <typename ExPolicy, typename OutIter, typename Size, typename F>
    inline typename boost::enable_if<
        is_execution_policy<ExPolicy>,
        typename detail::algorithm_result<ExPolicy, OutIter>::type
    >::type
    generate_n(ExPolicy && policy, OutIter first, Size count, F && f)
    {
        typedef typename std::iterator_traits<OutIter>::iterator_category
            iterator_category;

        BOOST_STATIC_ASSERT_MSG(
            (boost::is_base_of<
                std::output_iterator_tag, iterator_category
            >::value),
            "Requires at least output iterator.");

        if(detail::is_negative<Size>::call(count))
        {
            return detail::algorithm_result<ExPolicy, OutIter>::get(
                std::move(first));
        }

        typedef typename boost::mpl::or_<
            is_sequential_execution_policy<ExPolicy>,
            boost::is_same<std::output_iterator_tag, iterator_category>
        >::type is_seq;

        return detail::generate_n<OutIter>().call(
            std::forward<ExPolicy>(policy),
            first, std::size_t(count), std::forward<F>(f),
            is_seq());
    }

}}}

#endif