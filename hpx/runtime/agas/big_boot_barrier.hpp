////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//  Copyright (c) 2007-2013 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(HPX_0C9D09E0_725D_4FA6_A879_8226DE97C6B9)
#define HPX_0C9D09E0_725D_4FA6_A879_8226DE97C6B9

#include <boost/cstdint.hpp>
#include <boost/noncopyable.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

#include <hpx/hpx_fwd.hpp>
#include <hpx/util/io_service_pool.hpp>
#include <hpx/util/connection_cache.hpp>
#include <boost/lockfree/queue.hpp>
#include <hpx/runtime/naming/address.hpp>
#include <hpx/runtime/parcelset/parcelport.hpp>

#include <hpx/config/warnings_prefix.hpp>

namespace hpx { namespace agas
{

struct HPX_EXPORT big_boot_barrier : boost::noncopyable
{
  private:
    parcelset::parcelport& pp;

    service_mode const service_type;
    naming::address const bootstrap_agas;

    boost::condition_variable cond;
    boost::mutex mtx;
    std::size_t connected;

    boost::lockfree::queue<HPX_STD_FUNCTION<void()>* > thunks;

    void spin();

    void notify();

  public:
    struct scoped_lock
    {
      private:
        big_boot_barrier& bbb;

      public:
        scoped_lock(
            big_boot_barrier& bbb_
            )
          : bbb(bbb_)
        {
            bbb.mtx.lock();
        }

        ~scoped_lock()
        {
            bbb.notify();
        }
    };

    big_boot_barrier(
        parcelset::parcelport& pp_
      , util::runtime_configuration const& ini_
        );

    ~big_boot_barrier()
    {
        HPX_STD_FUNCTION<void()>* f;
        while (thunks.pop(f))
            delete f;
    }

    void apply(
        boost::uint32_t source_prefix
      , boost::uint32_t prefix
      , naming::address const& addr
      , actions::base_action* act
        );

    void apply_late(
        boost::uint32_t source_prefix
      , boost::uint32_t prefix
      , naming::address const& addr
      , actions::base_action* act
        );

    void wait_bootstrap();
    void wait_hosted(std::string const& locality_name,
        void* primary_ns_ptr, void* symbol_ns_ptr);

    // no-op on non-bootstrap localities
    void trigger();

    void add_thunk(
        HPX_STD_FUNCTION<void()>* f
        )
    {
        thunks.push(f);
    }
};

HPX_EXPORT void create_big_boot_barrier(
    parcelset::parcelport& pp_
  , util::runtime_configuration const& ini_
    );

HPX_EXPORT void destroy_big_boot_barrier();

HPX_EXPORT big_boot_barrier& get_big_boot_barrier();

}}

#include <hpx/config/warnings_suffix.hpp>

#endif // HPX_0C9D09E0_725D_4FA6_A879_8226DE97C6B9

