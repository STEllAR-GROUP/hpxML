//  Copyright (c) 2014 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_main.hpp>
#include <hpx/components/vector/vector.hpp>
#include <hpx/util/lightweight_test.hpp>

#include <hpx/include/parallel_for_each.hpp>
#include <hpx/parallel/segmented_algorithms/for_each.hpp>

///////////////////////////////////////////////////////////////////////////////
// Define the vector types to be used.
HPX_REGISTER_VECTOR(double);
HPX_REGISTER_VECTOR(int);

///////////////////////////////////////////////////////////////////////////////
template <typename T>
void fill_vector(hpx::vector<T>& v, T const& val)
{
    typename hpx::vector<T>::iterator it = v.begin(), end = v.end();
    for (/**/; it != end; ++it)
        *it = val;
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
void compare_vectors(hpx::vector<T> const& v1, hpx::vector<T> const& v2,
    bool must_be_equal = true)
{
    typedef typename hpx::vector<T>::const_iterator const_iterator;

    HPX_TEST_EQ(v1.size(), v2.size());
    HPX_TEST(v1.get_policy() == v2.get_policy());

    const_iterator it1 = v1.begin(), it2 = v2.begin();
    const_iterator end1 = v1.end(), end2 = v2.end();
    for (/**/; it1 != end1 && it2 != end2; ++it1, ++it2)
    {
        if (must_be_equal)
        {
            HPX_TEST_EQ(*it1, *it2);
        }
        else
        {
            HPX_TEST_NEQ(*it1, *it2);
        }
    }
}

template <typename T>
void move_tests(hpx::vector<T> const& v1)
{
    hpx::vector<T> v2(v1);
    compare_vectors(v1, v2);

    hpx::vector<T> v3(std::move(v2));
    compare_vectors(v1, v3);

    fill_vector(v3, T(43));
    compare_vectors(v1, v3, false);

    hpx::vector<T> v4;
    v4 = v1;
    compare_vectors(v1, v4);

    hpx::vector<T> v5;
    v5 = std::move(v4);
    compare_vectors(v1, v5);

    fill_vector(v5, T(43));
    compare_vectors(v1, v5, false);
}

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename DistPolicy>
void move_tests_with_policy(std::size_t size, std::size_t localities,
    DistPolicy const& policy)
{
    hpx::vector<T> v1(size, policy);

    hpx::vector<T> v2(v1);
    HPX_TEST(v2.get_policy() == policy.get_policy_type());
    compare_vectors(v1, v2);

    hpx::vector<T> v3(std::move(v2));
    HPX_TEST(v3.get_policy() == policy.get_policy_type());
    compare_vectors(v1, v3);

    fill_vector(v3, T(43));
    compare_vectors(v1, v3, false);

    hpx::vector<T> v4;
    v4 = v1;
    HPX_TEST(v4.get_policy() == policy.get_policy_type());
    compare_vectors(v1, v4);

    hpx::vector<T> v5;
    v5 = std::move(v4);
    HPX_TEST(v5.get_policy() == policy.get_policy_type());
    compare_vectors(v1, v5);

    fill_vector(v5, T(43));
    compare_vectors(v1, v5, false);
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
void move_tests()
{
    std::size_t const length = 12;
    std::vector<hpx::id_type> localities = hpx::find_all_localities();

    {
        hpx::vector<T> v;
        move_tests(v);
    }

    {
        hpx::vector<T> v(length);
        move_tests(v);
    }

    {
        hpx::vector<T> v(length, T(42));
        move_tests(v);
    }

    move_tests_with_policy<T>(length, 1, hpx::block);
    move_tests_with_policy<T>(length, 3, hpx::block(3));
    move_tests_with_policy<T>(length, 3, hpx::block(3, localities));
    move_tests_with_policy<T>(length, localities.size(),
        hpx::block(localities));

    move_tests_with_policy<T>(length, 1, hpx::cyclic);
    move_tests_with_policy<T>(length, 3, hpx::cyclic(3));
    move_tests_with_policy<T>(length, 3, hpx::cyclic(3, localities));
    move_tests_with_policy<T>(length, localities.size(),
        hpx::cyclic(localities));

    move_tests_with_policy<T>(length, 1, hpx::block_cyclic);
    move_tests_with_policy<T>(length, 3, hpx::block_cyclic(3));
    move_tests_with_policy<T>(length, 3,
        hpx::block_cyclic(3, localities));
    move_tests_with_policy<T>(length, localities.size(),
        hpx::block_cyclic(localities));
    move_tests_with_policy<T>(length, 4, hpx::block_cyclic(4, 3)); //-V112
    move_tests_with_policy<T>(length, 4, //-V112
        hpx::block_cyclic(4, localities, 3)); //-V112
    move_tests_with_policy<T>(length, localities.size(),
        hpx::block_cyclic(localities, 3));
}

///////////////////////////////////////////////////////////////////////////////
int main()
{
    move_tests<double>();
    move_tests<int>();

    return 0;
}

