//  Copyright (c) 2007-2012 Hartmut Kaiser
//  Copyright (c) 2008-2009 Chirag Dekate, Anshul Tandon
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_RUNTIME_THREAD_AFFINITY_NOV_11_2008_0711PM)
#define HPX_RUNTIME_THREAD_AFFINITY_NOV_11_2008_0711PM

#include <hpx/hpx_fwd.hpp>
#include <hpx/util/static.hpp>

#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>

#include <vector>

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace threads
{
    inline std::size_t least_significant_bit(boost::uint64_t mask)
    {
        if (mask) {
            int c = 0;    // will count v's trailing zero bits

            // Set mask's trailing 0s to 1s and zero rest
            mask = (mask ^ (mask - 1)) >> 1;
            for (/**/; mask; ++c)
                mask >>= 1;

            return std::size_t(1) << c;
        }
        return std::size_t(1);
    }

    inline std::size_t least_significant_bit_set(boost::uint64_t mask)
    {
        if (mask) {
            std::size_t c = 0;    // will count v's trailing zero bits

            // Set mask's trailing 0s to 1s and zero rest
            mask = (mask ^ (mask - 1)) >> 1;
            for (/**/; mask; ++c)
                mask >>= 1;

            return c;
        }
        return std::size_t(-1);
    }

    inline std::size_t hardware_concurrency()
    {
        static std::size_t num_of_cores = boost::thread::hardware_concurrency();
        return num_of_cores;
    }

#if defined(BOOST_WINDOWS)

#include <Psapi.h>

    ///////////////////////////////////////////////////////////////////////////
    struct numa_node_data
    {
        struct tag {};

        numa_node_data()
        {
            data_.reserve(hardware_concurrency());
            numa_sensitve_data_.reserve(hardware_concurrency());
            for (UCHAR i = 0; i < hardware_concurrency(); ++i)
            {
                data_.push_back(init_numa_node(i, false));
                numa_sensitve_data_.push_back(init_numa_node(i, true));
            }
        }

        std::size_t get_numa_node(std::size_t thread_num, bool numa_sensitive)
        {
            BOOST_ASSERT(0 <= thread_num && thread_num < data_.size());
            return numa_sensitive ?
                numa_sensitve_data_[thread_num] : data_[thread_num];
        }

    private:
        std::size_t init_numa_node(UCHAR thread_num, bool numa_sensitive)
        {
            if (UCHAR(-1) == thread_num)
                 return std::size_t(-1);

            UCHAR node_number = 0;
            if (GetNumaProcessorNode(thread_num, &node_number))
                return node_number;

            std::size_t num_of_cores = hardware_concurrency();
            if (0 == num_of_cores)
                num_of_cores = 1;     // assume one core

            std::size_t num_of_numa_cores = num_of_cores;
            ULONG numa_nodes = 0;
            if (GetNumaHighestNodeNumber(&numa_nodes) && 0 != numa_nodes)
                num_of_numa_cores = num_of_cores / (numa_nodes + 1);

            return thread_num / num_of_numa_cores;
        }

        std::vector<std::size_t> data_;
        std::vector<std::size_t> numa_sensitve_data_;
    };

    inline std::size_t get_numa_node(std::size_t thread_num, bool numa_sensitive)
    {
        util::static_<numa_node_data, numa_node_data::tag> data;
        return data.get().get_numa_node(thread_num, numa_sensitive);
    }

    ///////////////////////////////////////////////////////////////////////////
    struct numa_affinity_mask_data
    {
        struct tag {};

        numa_affinity_mask_data()
        {
            data_.reserve(hardware_concurrency());
            numa_sensitve_data_.reserve(hardware_concurrency());
            for (std::size_t i = 0; i < hardware_concurrency(); ++i)
            {
                data_.push_back(init_numa_node_affinity_mask(i, false));
                numa_sensitve_data_.push_back(init_numa_node_affinity_mask(i, true));
            }
        }

        boost::uint64_t get_numa_node_affinity_mask(std::size_t thread_num,
            bool numa_sensitive)
        {
            BOOST_ASSERT(0 <= thread_num && thread_num < data_.size());
            return numa_sensitive ?
                numa_sensitve_data_[thread_num] : data_[thread_num];
        }

    private:
        boost::uint64_t init_numa_node_affinity_mask(std::size_t num_thread,
            bool numa_sensitive)
        {
            std::size_t num_of_cores = hardware_concurrency();
            if (0 == num_of_cores)
                num_of_cores = 1;     // assume one core
            UCHAR affinity = static_cast<UCHAR>(num_thread % num_of_cores);

            ULONG numa_nodes = 1;
            if (GetNumaHighestNodeNumber(&numa_nodes))
                ++numa_nodes;

            boost::uint64_t node_affinity_mask = 0;
            if (numa_sensitive) {
                UCHAR numa_node = affinity % numa_nodes;
                if (!GetNumaNodeProcessorMask(numa_node, &node_affinity_mask))
                    return false;

                return node_affinity_mask;
            }

            UCHAR numa_node = static_cast<UCHAR>(get_numa_node(num_thread, numa_sensitive));
            if (!GetNumaNodeProcessorMask(numa_node, &node_affinity_mask))
                return false;

            return node_affinity_mask;
        }

        std::vector<boost::uint64_t> data_;
        std::vector<boost::uint64_t> numa_sensitve_data_;
    };

    inline boost::uint64_t
    get_numa_node_affinity_mask(std::size_t num_thread, bool numa_sensitive)
    {
        util::static_<numa_affinity_mask_data, numa_affinity_mask_data::tag> data;
        return data.get().get_numa_node_affinity_mask(num_thread, numa_sensitive);
    }

    ///////////////////////////////////////////////////////////////////////////
    struct thread_affinity_mask_data
    {
        struct tag {};

        thread_affinity_mask_data()
        {
            data_.reserve(hardware_concurrency());
            numa_sensitve_data_.reserve(hardware_concurrency());
            for (std::size_t i = 0; i < hardware_concurrency(); ++i)
            {
                data_.push_back(init_thread_affinity_mask(i, false));
                numa_sensitve_data_.push_back(init_thread_affinity_mask(i, true));
            }
        }

        boost::uint64_t get_thread_affinity_mask(std::size_t thread_num,
            bool numa_sensitive)
        {
            BOOST_ASSERT(0 <= thread_num && thread_num < data_.size());
            return numa_sensitive ?
                numa_sensitve_data_[thread_num] : data_[thread_num];
        }

    private:
        boost::uint64_t init_thread_affinity_mask(std::size_t num_thread,
            bool numa_sensitive)
        {
            std::size_t num_of_cores = hardware_concurrency();
            if (0 == num_of_cores)
                num_of_cores = 1;     // assume one core
            std::size_t affinity = num_thread % num_of_cores;

            ULONG numa_nodes = 1;
            if (GetNumaHighestNodeNumber(&numa_nodes))
                ++numa_nodes;

            std::size_t num_of_cores_per_numa_node = num_of_cores / numa_nodes;
            boost::uint64_t node_affinity_mask = 0;
            boost::uint64_t mask = 0x01LL;
            if (numa_sensitive) {
                UCHAR numa_node = static_cast<UCHAR>(affinity % numa_nodes);
                if (!GetNumaNodeProcessorMask(numa_node, &node_affinity_mask))
                    return false;

                mask = least_significant_bit(node_affinity_mask) <<
                    (affinity / numa_nodes);
            }
            else {
                UCHAR numa_node = static_cast<UCHAR>(get_numa_node(num_thread, numa_sensitive));
                if (!GetNumaNodeProcessorMask(numa_node, &node_affinity_mask))
                    return false;

                mask = least_significant_bit(node_affinity_mask) <<
                    (affinity % num_of_cores_per_numa_node);
            }

            while (!(mask & node_affinity_mask)) {
                mask <<= 1LL;
                if (0 == mask)
                    mask = 0x01LL;
            }

            return mask;
        }

        std::vector<boost::uint64_t> data_;
        std::vector<boost::uint64_t> numa_sensitve_data_;
    };

    inline boost::uint64_t
    get_thread_affinity_mask(std::size_t num_thread, bool numa_sensitive)
    {
        util::static_<thread_affinity_mask_data, thread_affinity_mask_data::tag> data;
        return data.get().get_thread_affinity_mask(num_thread, numa_sensitive);
    }

    ///////////////////////////////////////////////////////////////////////////
    inline bool
    set_affinity(boost::thread& thrd, std::size_t num_thread, bool numa_sensitive)
    {
        boost::uint64_t mask = get_thread_affinity_mask(num_thread, numa_sensitive);
        return SetThreadAffinityMask(thrd.native_handle(), DWORD_PTR(mask)) != 0;
    }

    inline bool set_affinity(std::size_t affinity, bool numa_sensitive)
    {
        return true;
    }

    ///////////////////////////////////////////////////////////////////////////
    inline boost::uint64_t
    get_thread_affinity_mask_from_lva(naming::address::address_type lva)
    {
        PSAPI_WORKING_SET_EX_INFORMATION info;
        info.VirtualAddress = reinterpret_cast<void*>(lva);

        if (!QueryWorkingSetEx(GetCurrentProcess(), &info, sizeof(info)))
            return std::size_t(-1);

        boost::uint64_t node_affinity_mask = 0;
        if (!GetNumaNodeProcessorMask(info.VirtualAttributes.Node, &node_affinity_mask))
            return std::size_t(-1);

        return node_affinity_mask;
    }

#elif defined(__APPLE__)

    // the thread affinity code is taken from the example:
    // http://www.opensource.apple.com/darwinsource/projects/other/xnu-1228.3.13/tools/tests/affinity/pool.c

    #include <AvailabilityMacros.h>
    #include <mach/mach.h>
    #include <mach/mach_error.h>
#ifdef AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER
    #include <mach/thread_policy.h>
#endif

    inline bool set_affinity(boost::thread& thrd, std::size_t affinity,
        bool numa_sensitive)
    {
        return true;
    }
    inline bool set_affinity(std::size_t num_thread, bool numa_sensitive)
    {
#ifdef AVAILABLE_MAC_OS_X_VERSION_10_5_AND_LATER
        thread_extended_policy_data_t epolicy;
        epolicy.timeshare = FALSE;

        kern_return_t ret = thread_policy_set(mach_thread_self(),
            THREAD_EXTENDED_POLICY, (thread_policy_t) &epolicy,
            THREAD_EXTENDED_POLICY_COUNT);

        if (ret != KERN_SUCCESS)
            return false;

        thread_affinity_policy_data_t policy;
        policy.affinity_tag = num_thread + 1;   // 1...N

        ret = thread_policy_set(mach_thread_self(),
            THREAD_AFFINITY_POLICY, (thread_policy_t) &policy,
            THREAD_AFFINITY_POLICY_COUNT);

        return ret == KERN_SUCCESS;
#else
        return true;
#endif
    }

    inline std::size_t
    get_thread_affinity_mask(std::size_t thread_num, bool numa_sensitive)
    {
        return std::size_t(-1);
    }

    inline std::size_t
    get_numa_node_affinity_mask(std::size_t thread_num, bool numa_sensitive)
    {
        return std::size_t(-1);
    }

    inline int get_numa_node(std::size_t thread_num, bool numa_sensitive)
    {
        return -1;
    }

    ///////////////////////////////////////////////////////////////////////////
    inline std::size_t
    get_thread_affinity_mask_from_lva(naming::address::address_type lva)
    {
        return std::size_t(-1);
    }

#else

#if defined(HPX_HAVE_PTHREAD_AFFINITY_NP)
    #include <pthread.h>
#endif
#if HPX_HAVE_NUMA
    #include <numa.h>
#endif
    #include <sched.h>    // declares the scheduling interface
    #include <sys/syscall.h>
    #include <sys/types.h>
    #include <iostream>

    inline bool set_affinity(boost::thread& thrd, std::size_t num_thread,
        bool numa_sensitive)
    {
        return true;
    }
    inline bool set_affinity(std::size_t num_thread, bool numa_sensitive)
    {
        std::size_t num_of_cores = hardware_concurrency();
        if (0 == num_of_cores)
            num_of_cores = 1;     // assume one core

        cpu_set_t cpu;
        CPU_ZERO(&cpu);

        // limit this thread to one of the cores
        std::size_t num_blocks = 1;
        std::size_t num_cores = num_of_cores;

        num_blocks = boost::lexical_cast<std::size_t>(
            get_config_entry("system_topology.num_blocks", num_blocks));
        num_cores = boost::lexical_cast<std::size_t>(
            get_config_entry("system_topology.num_cores", num_cores));

        // Check sanity
        assert(num_blocks * num_cores == num_of_cores);

        // Choose thread mapping function and determine affinity
        std::string thread_map = "linear";
        thread_map = get_config_entry("system_topology.thread_map", thread_map);

        std::size_t affinity(0);
        if (thread_map == "linear")
        {
          affinity = (num_thread) % num_of_cores;
        }
        else if (thread_map == "block_striped")
        {
          affinity = (num_thread/num_blocks)
                      + (num_cores * (num_thread % num_blocks));
        }
        else
        {
          assert(0);
        }

#if HPX_HAVE_NUMA
        int numa_cpus       = numa_num_configured_cpus();
        int numa_nodes      = numa_num_configured_nodes();
        int cpus_per_node   = numa_cpus/numa_nodes;
        struct bitmask * mask = numa_bitmask_alloc(numa_cpus);
        int node            = affinity / cpus_per_node;
        int node_id         = affinity % cpus_per_node;

        numa_bitmask_clearall(mask);
        numa_node_to_cpus(node, mask);
        unsigned real_affinity = 0;
        int index = 0;
        for(real_affinity = 0; real_affinity < mask->size; ++real_affinity)
        {
            if(numa_bitmask_isbitset(mask, real_affinity))
            {
                if(index == node_id) break;
                ++index;
            }
        }
        numa_bitmask_free(mask);

        CPU_SET(real_affinity, &cpu);
#else
        CPU_SET(affinity, &cpu);
#endif

#if defined(HPX_HAVE_PTHREAD_AFFINITY_NP)
        if (0 == pthread_setaffinity_np(pthread_self(), sizeof(cpu), &cpu))
#else
        if (0 == sched_setaffinity(syscall(SYS_gettid), sizeof(cpu), &cpu))
#endif
        {
            sleep(0);   // allow the OS to pick up the change
            return true;
        }
        return false;
    }

    inline std::size_t
    get_thread_affinity_mask(std::size_t thread_num, bool numa_sensitive)
    {
        return std::size_t(-1);
    }

    inline std::size_t
    get_numa_node_affinity_mask(std::size_t thread_num, bool numa_sensitive)
    {
        return std::size_t(-1);
    }

    inline int get_numa_node(std::size_t thread_num, bool numa_sensitive)
    {
        return -1;
    }

    ///////////////////////////////////////////////////////////////////////////
    inline std::size_t
    get_thread_affinity_mask_from_lva(naming::address::address_type lva)
    {
        return std::size_t(-1);
    }

#endif

}}

#endif

