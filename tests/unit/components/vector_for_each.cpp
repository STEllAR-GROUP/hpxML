//  Copyright (c) 2014 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_main.hpp>
#include <hpx/components/vector/vector.hpp>
#include <hpx/util/lightweight_test.hpp>

#include <hpx/include/parallel_for_each.hpp>
#include <hpx/include/parallel_count.hpp>

#include <hpx/parallel/segmented_algorithms/for_each.hpp>
#include <hpx/parallel/segmented_algorithms/count.hpp>

///////////////////////////////////////////////////////////////////////////////
// Define the vector types to be used.
HPX_REGISTER_VECTOR(double);
HPX_REGISTER_VECTOR(int);

struct pfo
{
    template <typename T>
    void operator()(T& val) const
    {
        ++val;
    }
};

template <typename T>
struct cmp
{
    cmp(T const& val = T()) : value_(val) {}

    template <typename T_>
    bool operator()(T_ const& val) const
    {
        return val == value_;
    }

    T value_;

    template <typename Archive>
    void serialize(Archive& ar, unsigned version)
    {
        ar & value_;
    }
};

///////////////////////////////////////////////////////////////////////////////
template <typename ExPolicy, typename T>
void verify_values(ExPolicy && policy, hpx::vector<T> const& v, T const& val)
{
    typedef typename hpx::vector<T>::const_iterator const_iterator;

    std::size_t size = 0;

    const_iterator end = v.end();
    for (const_iterator it = v.begin(); it != end; ++it, ++size)
    {
        HPX_TEST_EQ(*it, val);
    }

    HPX_TEST_EQ(size, v.size());
}

template <typename ExPolicy, typename T>
void verify_values_count(ExPolicy && policy, hpx::vector<T> const& v, T const& val)
{
    HPX_TEST_EQ(
        std::size_t(hpx::parallel::count(
            policy, v.begin(), v.end(), val)),
        v.size());
    HPX_TEST_EQ(
        std::size_t(hpx::parallel::count_if(
            policy, v.begin(), v.end(), cmp<T>(val))),
        v.size());
}

template <typename ExPolicy, typename T>
void test_for_each(ExPolicy && policy, hpx::vector<T>& v, T val)
{
    verify_values(policy, v, val);
    verify_values_count(policy, v, val);

    hpx::parallel::for_each(policy, v.begin(), v.end(), pfo());

    verify_values(policy, v, ++val);
    verify_values_count(policy, v, val);
}

template <typename ExPolicy, typename T>
void verify_values_count_async(ExPolicy && policy, hpx::vector<T> const& v,
    T const& val)
{
    HPX_TEST_EQ(
        std::size_t(hpx::parallel::count(
            policy, v.begin(), v.end(), val).get()),
        v.size());
    HPX_TEST_EQ(
        std::size_t(hpx::parallel::count_if(
            policy, v.begin(), v.end(), cmp<T>(val)).get()),
        v.size());
}

template <typename ExPolicy, typename T>
void test_for_each_async(ExPolicy && policy, hpx::vector<T>& v, T val)
{
    verify_values(policy, v, val);
    verify_values_count_async(policy, v, val);

    hpx::parallel::for_each(policy, v.begin(), v.end(), pfo()).get();

    verify_values(policy, v, ++val);
    verify_values_count_async(policy, v, val);
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
void for_each_tests()
{
    std::size_t const length = 12;

    {
        hpx::vector<T> v;
        hpx::parallel::for_each(hpx::parallel::seq, v.begin(), v.end(), pfo());
        hpx::parallel::for_each(hpx::parallel::par, v.begin(), v.end(), pfo());
        hpx::parallel::for_each(hpx::parallel::seq(hpx::parallel::task),
            v.begin(), v.end(), pfo()).get();
        hpx::parallel::for_each(hpx::parallel::par(hpx::parallel::task),
            v.begin(), v.end(), pfo()).get();
    }

    {
        hpx::vector<T> v(length, T(0));
        test_for_each(hpx::parallel::seq, v, T(0));
        test_for_each(hpx::parallel::par, v, T(1));
        test_for_each_async(hpx::parallel::seq(hpx::parallel::task), v, T(2));
        test_for_each_async(hpx::parallel::par(hpx::parallel::task), v, T(3));
    }
}

///////////////////////////////////////////////////////////////////////////////
int main()
{
    for_each_tests<int>();
    for_each_tests<double>();

    return 0;
}

