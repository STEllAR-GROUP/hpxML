//  Copyright (c) 2007-2010 Hartmut Kaiser
//  Copyright (c)      2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx.hpp>
#include <hpx/hpx_init.hpp>
#include <hpx/runtime/actions/plain_action.hpp>
#include <hpx/runtime/components/plain_component_factory.hpp>
#include <hpx/util/high_resolution_timer.hpp>
#include <hpx/lcos/future_wait.hpp>
#include <hpx/lcos/async.hpp>

#include <algorithm>
#include <boost/atomic.hpp>

using boost::program_options::variables_map;
using boost::program_options::options_description;
using boost::program_options::value;

using hpx::naming::id_type;

using hpx::components::memory_block;
using hpx::components::access_memory_block;

using hpx::actions::manage_object_action;
using hpx::actions::plain_action4;

using hpx::applier::applier;
using hpx::applier::get_applier;

using hpx::lcos::async;

using hpx::util::high_resolution_timer;

using hpx::init;
using hpx::finalize;

///////////////////////////////////////////////////////////////////////////////
template <typename T>
inline std::size_t partition(T* data, std::size_t begin, std::size_t end)
{
    T* first = data + begin;
    T* last = first + (end - begin);

    T* middle = std::partition(
        first, last, std::bind2nd(std::less<T>(), *first));

    return middle - data;
}

///////////////////////////////////////////////////////////////////////////////
template <typename T>
struct quicksort_serial
{
    static std::size_t sort_count;

    static void call(T* data, std::size_t begin, std::size_t end)
    {
        if (begin != end)
        {
            std::size_t middle_idx = partition(data, begin, end);

            ++sort_count;

            // always spawn the larger part in a new thread
            if (2 * middle_idx < end - begin)
            {
                call(data, (std::max)(begin + 1, middle_idx), end);
                call(data, begin, middle_idx);
            }

            else
            {
                call(data, begin, middle_idx);
                call(data, (std::max)(begin + 1, middle_idx), end);
            }
        }
    }
};

template <typename T>
std::size_t quicksort_serial<T>::sort_count(0);

///////////////////////////////////////////////////////////////////////////////
template <typename T>
struct quicksort_parallel
{
    static std::size_t sort_count;

    static void call(id_type prefix, id_type d, std::size_t begin,
                     std::size_t end);

    typedef plain_action4<
        id_type, id_type, std::size_t, std::size_t, &quicksort_parallel::call
    > action_type;
};

template <typename T>
std::size_t quicksort_parallel<T>::sort_count(0);

template <typename T>
void quicksort_parallel<T>::call(id_type prefix, id_type d, std::size_t begin,
                                 std::size_t end)
{
    if (begin != end)
    {
        memory_block mb(d);
        access_memory_block<T> data(mb.get());

        std::size_t middle_idx = partition(data.get_ptr(), begin, end);

        ++sort_count;

        // always spawn the larger part in a new thread
        if (2 * middle_idx < end - begin)
        {
            future<id_type> n = async<action_type>(prefix, prefix, d,
                (std::max)(begin + 1, middle_idx), end);

            call(prefix, d, begin, middle_idx);
            ::hpx::lcos::wait(n);
        }

        else
        {
            future<id_type> n = async<action_type>(prefix, prefix, d,
                begin, middle_idx);

            call(prefix, d, (std::max)(begin + 1, middle_idx), end);
            ::hpx::lcos::wait(n);
        }
    }
}

typedef quicksort_parallel<int>::action_type quicksort_int_action;
HPX_REGISTER_PLAIN_ACTION(quicksort_int_action);

///////////////////////////////////////////////////////////////////////////////
int hpx_main(variables_map& vm)
{
    std::size_t elements = 0;

    if (vm.count("elements"))
        elements = vm["elements"].as<std::size_t>();

    // get list of all known localities
    std::vector<id_type> prefixes = hpx::find_remote_localities();
    id_type prefix;

    // execute the qsort() function on any of the remote localities
    if (!prefixes.empty())
        prefix = prefixes[0];

    // execute the qsort() function locally
    else
      prefix = hpx::find_here();

    {
        // create a (remote) memory block
        memory_block mb;
        mb.create<int, uint8_t>(prefix, elements);
        access_memory_block<int> data(mb.get());

        // randomly fill the vector
        std::generate(data.get_ptr(), data.get_ptr() + elements, std::rand);

        std::cout << "serial quicksort" << std::endl;

        high_resolution_timer t;
        quicksort_serial<int>::call(data.get_ptr(), 0, elements);
        double elapsed = t.elapsed();

        std::cout << "  elapsed=" << elapsed << "\n"
                  << "  count=" << quicksort_serial<int>::sort_count << "\n";

//        int* it = data.get_ptr();
//        int* end = data.get_ptr() + elements;

//        for (; it < end; ++it)
//            std::cout << *it << "\n";

        std::generate(data.get_ptr(), data.get_ptr() + elements, std::rand);

        std::cout << "parallel quicksort" << std::endl;

        t.restart();
        future<int> n = async<quicksort_parallel<int>::action_type>(
            prefix, prefix, mb.get_gid(), 0, elements);
        ::hpx::lcos::wait(n);
        elapsed = t.elapsed();

        std::cout << "  elapsed=" << elapsed << "\n"
                  << "  count=" << quicksort_parallel<int>::sort_count << "\n";

//        it = data.get_ptr();
//        end = data.get_ptr() + elements;

//        for (; it < end; ++it)
//            std::cout << *it << "\n";

        mb.free();
    }

    // initiate shutdown of the runtime systems on all localities
    finalize(1.0);

    return 0;
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    // Configure application-specific options
    options_description
       desc_commandline("Usage: " HPX_APPLICATION_STRING " [options]");

    desc_commandline.add_options()
        ("elements", value<std::size_t>()->default_value(1024),
            "the number of elements to generate and sort")
        ;

    // Initialize and run HPX
    return init(desc_commandline, argc, argv);
}

