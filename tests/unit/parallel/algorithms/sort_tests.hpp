//  Copyright (c) 2015 Daniel Bourgeois
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_PARALLEL_TEST_IS_SORTED_MAY28_15_1320)
#define HPX_PARALLEL_TEST_IS_SORTED_MAY28_15_1320

//
#include <random>
#include <limits>
//
#include <hpx/hpx_init.hpp>
#include <hpx/hpx.hpp>
#include <hpx/include/parallel_sort.hpp>
#include <hpx/util/lightweight_test.hpp>

#include <boost/range/functions.hpp>

#include "test_utils.hpp"

// Fill a vector with random numbers in the range [lower, upper]
template <typename T>
void rnd_fill(std::vector<T> &V, const T lower, const T upper, const T seed)
{
    // use the default random engine and an uniform distribution
    std::default_random_engine eng(seed);
    std::uniform_real_distribution<double> distr(lower, upper);

    for (auto &elem : V) {
        elem = static_cast<T>(distr(eng));
    }
}

template <class IA, typename Compare>
int verify(const std::vector <IA> &A, Compare comp, bool print) {
    if (A.size()<2) {
        // skip checks as we must be sorted
    }
    else {
        IA temp = *(A.begin());
        for (typename std::vector<IA>::const_iterator it=A.begin(); it!=A.end(); ++it) {
            if (comp((*it),temp)) {
                if (print) std::cout << "Verify fail " << A.size() << std::endl;
                return 0;
            }
            temp = (*it);
        }
    }
    if (print) std::cout << "Verify OK " << A.size() << std::endl;
    return 1;
}


#define msg(a,b,c,d,e) \
        std::cout \
        << std::setw(60) << a << std::setw(3) <<  b \
        << std::setw(20) << c << std::setw(6) << #d \
        << std::setw(8)  << #e << "\t";

////////////////////////////////////////////////////////////////////////////////
// call sort with no comparison operator
template <typename ExPolicy, typename T>
void test_sort1(ExPolicy && policy, T)
{
    BOOST_STATIC_ASSERT(hpx::parallel::is_execution_policy<ExPolicy>::value);
    msg(typeid(ExPolicy).name(), typeid(T).name(), "default", sync, random);

    // Fill vector with random values
    std::vector<T> c(5000000);
    rnd_fill<T>(c, std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), std::random_device{}());

    // sort, blocking when seq, par, par_vec
    hpx::parallel::sort(std::forward<ExPolicy>(policy),
            c.begin(), c.end());

    bool is_sorted = (verify(c, std::less<T>(), true) != 0);
    HPX_TEST(is_sorted);
}

////////////////////////////////////////////////////////////////////////////////
// call sort with a comparison operator
template <typename ExPolicy, typename T, typename Compare = std::less<T>>
        void test_sort1_comp(ExPolicy && policy, T, Compare comp = Compare())
{
    BOOST_STATIC_ASSERT(hpx::parallel::is_execution_policy<ExPolicy>::value);
    msg(typeid(ExPolicy).name(), typeid(T).name(), typeid(Compare).name(), sync, random);

    // Fill vector with random values
    std::vector<T> c(5000000);
    rnd_fill<T>(c, std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), std::random_device{}());

    // sort, blocking when seq, par, par_vec
    hpx::parallel::sort(std::forward<ExPolicy>(policy),
            c.begin(), c.end(), comp);

    bool is_sorted = (verify(c, comp, true)!=0);
    HPX_TEST(is_sorted);
}

////////////////////////////////////////////////////////////////////////////////
template <typename ExPolicy, typename T, typename Compare = std::less<T>>
        void test_sort1_async(ExPolicy && policy, T, Compare comp = Compare())
{
    BOOST_STATIC_ASSERT(hpx::parallel::is_execution_policy<ExPolicy>::value);
    msg(typeid(ExPolicy).name(), typeid(T).name(), typeid(Compare).name(), async, random);

    // Fill vector with random values
    std::vector<T> c(5000000);
    rnd_fill<T>(c, std::numeric_limits<T>::min(), std::numeric_limits<T>::max(), std::random_device{}());

    // sort, non blocking
    hpx::future<void> f = hpx::parallel::sort(std::forward<ExPolicy>(policy),
            c.begin(), c.end(), comp);

    f.get();
    bool is_sorted = (verify(c, comp, true)!=0);
    HPX_TEST(is_sorted);
}

////////////////////////////////////////////////////////////////////////////////
// already sorted
template <typename ExPolicy, typename T>
void test_sort2(ExPolicy && policy, T)
{
    BOOST_STATIC_ASSERT(hpx::parallel::is_execution_policy<ExPolicy>::value);
    msg(typeid(ExPolicy).name(), typeid(T).name(), "default", sync, sorted);

    // Fill vector with increasing values
    std::vector<T> c(5000000);
    std::iota(boost::begin(c), boost::end(c), 0);

    // sort, blocking when seq, par, par_vec
    hpx::parallel::sort(std::forward<ExPolicy>(policy),
            c.begin(), c.end());

    bool is_sorted = (verify(c, std::less<T>(), true) != 0);
    HPX_TEST(is_sorted);
}

////////////////////////////////////////////////////////////////////////////////
template <typename ExPolicy, typename T, typename Compare = std::less<T> >
void test_sort2_comp(ExPolicy && policy, T, Compare comp = Compare())
{
    BOOST_STATIC_ASSERT(hpx::parallel::is_execution_policy<ExPolicy>::value);
    msg(typeid(ExPolicy).name(), typeid(T).name(), typeid(Compare).name(), sync, sorted);

    // Fill vector with increasing values
    std::vector<T> c(5000000);
    std::iota(boost::begin(c), boost::end(c), 0);

    // sort, blocking when seq, par, par_vec
    hpx::parallel::sort(std::forward<ExPolicy>(policy),
            c.begin(), c.end(), comp);

    bool is_sorted = (verify(c, comp, true)!=0);
    HPX_TEST(is_sorted);
}

////////////////////////////////////////////////////////////////////////////////
template <typename ExPolicy, typename T, typename Compare = std::less<T> >
void test_sort2_async(ExPolicy && policy, T, Compare comp = Compare())
{
    BOOST_STATIC_ASSERT(hpx::parallel::is_execution_policy<ExPolicy>::value);
    msg(typeid(ExPolicy).name(), typeid(T).name(), typeid(Compare).name(), async, sorted);

    // Fill vector with random values
    std::vector<T> c(5000000);
    std::iota(boost::begin(c), boost::end(c), 0);

    // sort, non blocking
    hpx::future<void> f = hpx::parallel::sort(std::forward<ExPolicy>(policy),
            c.begin(), c.end(), comp);

    f.get();
    bool is_sorted = (verify(c, comp, true)!=0);
    HPX_TEST(is_sorted);
}
/*
////////////////////////////////////////////////////////////////////////////////
template <typename ExPolicy, typename IteratorTag>
void test_sorted3(ExPolicy policy, IteratorTag)
{
    BOOST_STATIC_ASSERT(hpx::parallel::is_execution_policy<ExPolicy>::value);

    typedef std::vector<T>::iterator base_iterator;
    typedef test::test_iterator<base_iterator, IteratorTag> iterator;

    std::vector<T> c_beg(10007);
    std::vector<T> c_end(10007);
    //Fill with sorted values from 0 to 10006
    std::iota(boost::begin(c_beg), boost::end(c_beg), 0);
    std::iota(boost::begin(c_end), boost::end(c_end), 0);
    //add unsorted element to c_beg, c_end at the beginning, end respectively
    c_beg[0] = 20000;
    c_end[c_end.size()-1] = 0;

    bool is_ordered1 = hpx::parallel::is_sorted(policy,
        iterator(boost::begin(c_beg)), iterator(boost::end(c_beg)));
    bool is_ordered2 = hpx::parallel::is_sorted(policy,
        iterator(boost::begin(c_end)), iterator(boost::end(c_end)));

    HPX_TEST(!is_ordered1);
    HPX_TEST(!is_ordered2);
}

template <typename ExPolicy, typename IteratorTag>
void test_sorted3_async(ExPolicy p, IteratorTag)
{
    BOOST_STATIC_ASSERT(hpx::parallel::is_execution_policy<ExPolicy>::value);

    typedef std::vector<T>::iterator base_iterator;
    typedef test::test_iterator<base_iterator, IteratorTag> iterator;

    std::vector<T> c_beg(10007);
    std::vector<T> c_end(10007);
    //Fill with sorted values from 0 to 10006
    std::iota(boost::begin(c_beg), boost::end(c_beg), 0);
    std::iota(boost::begin(c_end), boost::end(c_end), 0);
    //add unsorted element to c_beg, c_end at the beginning, end respectively
    c_beg[0] = 20000;
    c_end[c_end.size()-1] = 0;

    hpx::future<bool> f1 = hpx::parallel::is_sorted(p,
        iterator(boost::begin(c_beg)), iterator(boost::end(c_beg)));
    hpx::future<bool> f2 = hpx::parallel::is_sorted(p,
        iterator(boost::begin(c_end)), iterator(boost::end(c_end)));
    f1.wait();
    HPX_TEST(!f1.get());
    f2.wait();
    HPX_TEST(!f2.get());
}

////////////////////////////////////////////////////////////////////////////////
template <typename ExPolicy, typename IteratorTag>
void test_sorted_exception(ExPolicy policy, IteratorTag)
{
    BOOST_STATIC_ASSERT(hpx::parallel::is_execution_policy<ExPolicy>::value);

    typedef std::vector<T>::iterator base_iterator;
    typedef test::decorated_iterator<base_iterator, IteratorTag>
        decorated_iterator;
    std::vector<T> c(10007);
    std::iota(boost::begin(c), boost::end(c), 0);

    bool caught_exception = false;
    try{
        hpx::parallel::is_sorted(policy,
            decorated_iterator(
                boost::begin(c),
                [](){ throw std::runtime_error("test"); }),
            decorated_iterator(
                boost::end(c),
                [](){ throw std::runtime_error("test"); }));
    }
    catch(hpx::exception_list const& e) {
        caught_exception = true;
        test::test_num_exceptions<ExPolicy, IteratorTag>::call(policy, e);
    }
    catch(...) {
        HPX_TEST(false);
    }

    HPX_TEST(caught_exception);
}

template <typename ExPolicy, typename IteratorTag>
void test_sorted_exception_async(ExPolicy p, IteratorTag)
{
    typedef std::vector<T>::iterator base_iterator;
    typedef test::decorated_iterator<base_iterator, IteratorTag>
        decorated_iterator;

    std::vector<T> c(10007);
    std::iota(boost::begin(c), boost::end(c), std::rand() + 1);

    bool caught_exception = false;
    try {
        hpx::future<bool> f =
            hpx::parallel::is_sorted(p,
                decorated_iterator(
                    boost::begin(c),
                    [](){ throw std::runtime_error("test"); }),
                decorated_iterator(
                    boost::end(c),
                    [](){ throw std::runtime_error("test"); }));
        f.get();

        HPX_TEST(false);
    }
    catch(hpx::exception_list const& e) {
        caught_exception = true;
        test::test_num_exceptions<
            ExPolicy, IteratorTag
            >::call(p, e);
    }
    catch(...) {
        HPX_TEST(false);
    }

    HPX_TEST(caught_exception);
}

////////////////////////////////////////////////////////////////////////////////
template <typename ExPolicy, typename IteratorTag>
void test_sorted_bad_alloc(ExPolicy policy, IteratorTag)
{
    BOOST_STATIC_ASSERT(hpx::parallel::is_execution_policy<ExPolicy>::value);

    typedef std::vector<T>::iterator base_iterator;
    typedef test::decorated_iterator<base_iterator, IteratorTag>
        decorated_iterator;

    std::vector<T> c(100007);
    std::iota(boost::begin(c), boost::end(c), 0);

    bool caught_bad_alloc = false;
    try {
        hpx::parallel::is_sorted(policy,
            decorated_iterator(
                boost::begin(c),
                [](){ throw std::bad_alloc(); }),
            decorated_iterator(
                boost::end(c),
                [](){ throw std::bad_alloc(); }));
        HPX_TEST(false);
    }
    catch(std::bad_alloc const&) {
        caught_bad_alloc = true;
    }
    catch(...) {
        HPX_TEST(false);
    }

    HPX_TEST(caught_bad_alloc);
}

template <typename ExPolicy, typename IteratorTag>
void test_sorted_bad_alloc_async(ExPolicy p, IteratorTag)
{
    typedef std::vector<T>::iterator base_iterator;
    typedef test::decorated_iterator<base_iterator, IteratorTag>
        decorated_iterator;

    std::vector<T> c(10007);
    std::iota(boost::begin(c), boost::end(c), 0);

    bool caught_bad_alloc = false;
    try {
        hpx::future<bool> f =
            hpx::parallel::is_sorted(p,
                decorated_iterator(
                    boost::begin(c),
                    [](){ throw std::bad_alloc(); }),
                decorated_iterator(
                    boost::end(c),
                    [](){ throw std::bad_alloc(); }));

        f.get();
        HPX_TEST(false);
    }
    catch(std::bad_alloc const&) {
        caught_bad_alloc = true;
    }
    catch(...) {
        HPX_TEST(false);
    }

    HPX_TEST(caught_bad_alloc);
}
 */
#endif
