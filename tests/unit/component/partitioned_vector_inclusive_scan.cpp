//  Copyright (c) 2016 Minh-Khanh Do
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_main.hpp>
#include <hpx/include/partitioned_vector.hpp>
#include <hpx/include/parallel_for_each.hpp>
#include <hpx/include/parallel_scan.hpp>
#include <hpx/include/parallel_copy.hpp>
#include <hpx/util/zip_iterator.hpp>

#include <hpx/util/lightweight_test.hpp>

#include <boost/range/functions.hpp>

#include <vector>

///////////////////////////////////////////////////////////////////////////////
// Define the vector types to be used.
HPX_REGISTER_PARTITIONED_VECTOR(double);
HPX_REGISTER_PARTITIONED_VECTOR(int);

///////////////////////////////////////////////////////////////////////////////

struct iota :
    public hpx::parallel::v1::detail::algorithm<iota>
{
    iota()
        : iota::algorithm("iota")
    {}

    template <typename ExPolicy, typename InIter, typename T>
    static hpx::util::unused_type
    sequential(ExPolicy && policy, InIter first, InIter last, T && init)
    {
        std::iota(first, last, init);
        return hpx::util::unused;
    }

    template <typename ExPolicy, typename InIter, typename T>
    static hpx::util::unused_type
    parallel(ExPolicy && policy, InIter first, InIter last, T && init)
    {
        return hpx::util::void_guard<result_type>(),
            sequential(policy, first, last, init);
    }
};

template <typename T>
void iota_vector(hpx::partitioned_vector<T>& v, T val)
{
    auto first = v.begin();
    auto last = v.end();

    typedef hpx::traits::segmented_iterator_traits<decltype(first)> traits;
    typedef typename traits::segment_iterator segment_iterator;
    typedef typename traits::local_iterator local_iterator_type;

    segment_iterator sit = traits::segment(first);
    segment_iterator send = traits::segment(last);

    T temp_val = val;

    for (; sit != send; ++sit)
    {
        local_iterator_type beg = traits::begin(sit);
        local_iterator_type end = traits::end(sit);

        hpx::parallel::v1::detail::dispatch(traits::get_id(sit),
                iota(), hpx::parallel::seq, std::true_type(), beg, end, temp_val
        );

        temp_val += std::distance(beg, end);
    }
}

template <typename Value>
struct verify :
    public hpx::parallel::v1::detail::algorithm<verify<Value>, Value>
{
    verify()
        : verify::algorithm("verify")
    {}

    template <typename ExPolicy, typename SegIter, typename InIter>
    static Value
    sequential(ExPolicy && policy, SegIter first, SegIter last, InIter in)
    {
        return std::equal(first, last, in.begin());
    }

    template <typename ExPolicy, typename SegIter, typename InIter>
    static Value
    parallel(ExPolicy && policy, InIter first, InIter last, InIter in)
    {
        return sequential(policy, first, last, in);
    }
};


template<typename T>
void verify_values(hpx::partitioned_vector<T> v1, std::vector<T> v2)
{
    auto first = v1.begin();
    auto last = v1.end();

    typedef hpx::traits::segmented_iterator_traits<decltype(first)> traits;
    typedef typename traits::segment_iterator segment_iterator;
    typedef typename traits::local_iterator local_iterator_type;

    segment_iterator sit = traits::segment(first);
    segment_iterator send = traits::segment(last);

    auto beg2 = v2.begin();

    std::vector<bool> results;

    for (; sit != send; ++sit)
    {
        local_iterator_type beg = traits::begin(sit);
        local_iterator_type end = traits::end(sit);

        std::vector<T> test(std::distance(beg, end));
        std::copy_n(beg2, test.size(), test.begin());

        results.push_back(
            hpx::parallel::v1::detail::dispatch(traits::get_id(sit),
                verify<bool>(), hpx::parallel::seq, std::true_type(), beg, end, test
        ));

        beg2 += std::distance(beg, end);
    }
    bool final_result = std::all_of(results.begin(), results.end(),
        [](bool v) { return v; });

    HPX_TEST(final_result);
}

template<typename T>
struct opt
{
    T operator()(T v1, T v2) const{
        return v1 + v2;
    }
};

///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ExPolicy>
void inclusive_scan_algo_tests_with_policy(
    hpx::partitioned_vector<T>& in,
    std::vector<T> ver, ExPolicy const& policy)
{
    std::vector<T> out(in.size());
    T val(0);

    hpx::parallel::inclusive_scan(policy,
        in.begin(), in.end(), out.begin(), val, opt<T>());

    HPX_TEST(std::equal(out.begin(), out.end(), ver.begin()));
}

template <typename T, typename ExPolicy>
void inclusive_scan_algo_tests_segmented_out_with_policy(
    hpx::partitioned_vector<T>& in, hpx::partitioned_vector<T> out,
    std::vector<T> ver, ExPolicy const& policy)
{
    T val(0);
    hpx::parallel::inclusive_scan(policy,
        in.begin(), in.end(), out.begin(), val, opt<T>());

    verify_values(out, ver);
}

template <typename T, typename DistPolicy, typename ExPolicy>
void inclusive_scan_algo_tests_inplace_with_policy(
    std::size_t size, DistPolicy const& dist_policy,
    std::vector<T> ver, ExPolicy const& policy)
{
    hpx::partitioned_vector<T> in(size, dist_policy);
    iota_vector(in, T(1));

    T val(0);
    hpx::parallel::inclusive_scan(policy,
        in.begin(), in.end(), in.begin(), val, opt<T>());

    verify_values(in, ver);
}

///////////////////////////////////////////////////////////////////////////////

template <typename T, typename ExPolicy>
void inclusive_scan_algo_tests_with_policy_async(
    hpx::partitioned_vector<T>& in,
    std::vector<T> ver, ExPolicy const& policy)
{
    std::vector<T> out(in.size());
    T val(0);

    auto res =
        hpx::parallel::inclusive_scan(policy,
        in.begin(), in.end(), out.begin(), val, opt<T>());
    res.get();

    HPX_TEST(std::equal(out.begin(), out.end(), ver.begin()));
}

template <typename T, typename ExPolicy>
void inclusive_scan_algo_tests_segmented_out_with_policy_async(
    hpx::partitioned_vector<T>& in, hpx::partitioned_vector<T> out,
    std::vector<T> ver, ExPolicy const& policy)
{
    T val(0);
    auto res =
        hpx::parallel::inclusive_scan(policy,
        in.begin(), in.end(), out.begin(), val, opt<T>());
    res.get();

    verify_values(out, ver);
}

template <typename T, typename DistPolicy, typename ExPolicy>
void inclusive_scan_algo_tests_inplace_with_policy_async(
    std::size_t size, DistPolicy const& dist_policy,
    std::vector<T> ver, ExPolicy const& policy)
{
    hpx::partitioned_vector<T> in(size, dist_policy);
    iota_vector(in, T(1));

    T val(0);
    auto res =
        hpx::parallel::inclusive_scan(policy,
        in.begin(), in.end(), in.begin(), val, opt<T>());
    res.get();

    verify_values(in, ver);
}


///////////////////////////////////////////////////////////////////////////////

template <typename T, typename DistPolicy>
void inclusive_scan_tests_with_policy(std::size_t size,
    DistPolicy const& policy)
{
    using namespace hpx::parallel;
    using hpx::parallel::task;

    // setup partitioned vector to test
    hpx::partitioned_vector<T> in(size, policy);
    iota_vector(in, T(1));

    std::vector<T> ver(in.size());
    std::iota(ver.begin(), ver.end(), T(1));
    T val(0);

    hpx::parallel::v1::detail::sequential_inclusive_scan(
        ver.begin(), ver.end(), ver.begin(), val, opt<T>());

    //sync
    inclusive_scan_algo_tests_with_policy<T>(in, ver, seq);
    inclusive_scan_algo_tests_with_policy<T>(in, ver, par);

    //async
    inclusive_scan_algo_tests_with_policy_async<T>(in, ver, seq(task));
    inclusive_scan_algo_tests_with_policy_async<T>(in, ver, par(task));
}

template <typename T, typename DistPolicy>
void inclusive_scan_tests_segmented_out_with_policy(std::size_t size,
    DistPolicy const& in_policy, DistPolicy const& out_policy)
{
    using namespace hpx::parallel;
    using hpx::parallel::task;

    // setup partitioned vector to test
    hpx::partitioned_vector<T> in(size, in_policy);
    iota_vector(in, T(1));

    hpx::partitioned_vector<T> out(size, out_policy);

    std::vector<T> ver(in.size());
    std::iota(ver.begin(), ver.end(), T(1));
    T val(0);

    hpx::parallel::v1::detail::sequential_inclusive_scan(
        ver.begin(), ver.end(), ver.begin(), val, opt<T>());

    //sync
    inclusive_scan_algo_tests_segmented_out_with_policy<T>(in, out, ver, seq);
    inclusive_scan_algo_tests_segmented_out_with_policy<T>(in, out, ver, par);

    //async
    inclusive_scan_algo_tests_segmented_out_with_policy_async<T>(
        in, out, ver, seq(task));
    inclusive_scan_algo_tests_segmented_out_with_policy_async<T>(
        in, out, ver, par(task));
}

template <typename T, typename DistPolicy>
void inclusive_scan_tests_inplace_with_policy(std::size_t size,
    DistPolicy const& policy)
{
    using namespace hpx::parallel;
    using hpx::parallel::task;

    // setup verification vector
    std::vector<T> ver(size);
    std::iota(ver.begin(), ver.end(), T(1));
    T val(0);

    hpx::parallel::v1::detail::sequential_inclusive_scan(
        ver.begin(), ver.end(), ver.begin(), val, opt<T>());

    //sync
    inclusive_scan_algo_tests_inplace_with_policy<T>(size, policy, ver, seq);
    inclusive_scan_algo_tests_inplace_with_policy<T>(size, policy, ver, par);

    //async
    inclusive_scan_algo_tests_inplace_with_policy_async<T>(
        size, policy, ver, seq(task));
    inclusive_scan_algo_tests_inplace_with_policy_async<T>(
        size, policy, ver, par(task));
}

///////////////////////////////////////////////////////////////////////////////

template <typename T>
void inclusive_scan_tests()
{
    std::size_t const length = 100000;

    std::vector<hpx::id_type> localities = hpx::find_all_localities();

    inclusive_scan_tests_with_policy<T>(length, hpx::container_layout);
    inclusive_scan_tests_with_policy<T>(length, hpx::container_layout(3));
    inclusive_scan_tests_with_policy<T>(length, hpx::container_layout(3, localities));
    inclusive_scan_tests_with_policy<T>(length, hpx::container_layout(localities));

    inclusive_scan_tests_segmented_out_with_policy<T>(length,
        hpx::container_layout(localities), hpx::container_layout(localities));

    inclusive_scan_tests_inplace_with_policy<T>(length,
        hpx::container_layout(localities));
}

///////////////////////////////////////////////////////////////////////////////

int main()
{
    std::vector<hpx::id_type> localities = hpx::find_remote_localities();
    inclusive_scan_tests<int>();
    inclusive_scan_tests<double>();

    return hpx::util::report_errors();
}

