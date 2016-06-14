//  Copyright (c)      2013 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_PARCELSET_POLICIES_IBVERBS_HELPER_HPP)
#define HPX_PARCELSET_POLICIES_IBVERBS_HELPER_HPP

#include <hpx/config.hpp>

#if defined(HPX_HAVE_PARCELPORT_IBVERBS)

#include <hpx/util/cache/entries/lru_entry.hpp>
#include <hpx/util/cache/local_cache.hpp>

#include <cstring>
#include <memory>

#include <netdb.h>
#include <rdma/rdma_cma.h>

#include <errno.h>
#include <fcntl.h>
#include <poll.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

namespace hpx { namespace parcelset { namespace policies { namespace ibverbs {
    template <typename Connection>
    inline bool get_next_event(
        rdma_event_channel *event_channel, rdma_cm_event & event_copy, Connection * c
      , boost::system::error_code &ec
    )
    {
        if(!event_channel)
        {
            HPX_IBVERBS_THROWS_IF(ec, boost::asio::error::not_connected);
            return false;
        }

        rdma_cm_event * event = nullptr;

        if(rdma_get_cm_event(event_channel, &event) == 0)
        {
            std::memcpy(&event_copy, event, sizeof(rdma_cm_event));

            rdma_ack_cm_event(event);

            if(event_copy.event == RDMA_CM_EVENT_DISCONNECTED)
            {
                c->on_disconnect(event_copy.id);
                return get_next_event(event_channel, event_copy, c, ec);
            }

            return true;
        }
        else
        {
            int verrno = errno;
            if(verrno == EBADF) return false;
            if(verrno == EAGAIN) return false;
            if(verrno == EWOULDBLOCK) return false;

            boost::system::error_code err(verrno, boost::system::system_category());
            HPX_IBVERBS_THROWS_IF(
                ec
              , err
            );

            return false;
        }
        HPX_ASSERT(false);
        return false;
    }

    inline void set_nonblocking(int fd, boost::system::error_code &ec)
    {
        int flags = fcntl(fd, F_GETFL);
        int rc = fcntl(fd, F_SETFL, flags | O_NONBLOCK | FASYNC);
        if(rc < 0)
        {
            int verrno = errno;
            boost::system::error_code err(verrno, boost::system::system_category());
            HPX_IBVERBS_THROWS_IF(
                ec
              , err
            );
        }
    }

    struct ibverbs_mr
    {
        static void deleter(ibv_mr * mr)
        {
            ibv_dereg_mr(mr);
        };

        ibverbs_mr() {}

        ibverbs_mr(ibv_pd *pd, void * buffer, std::size_t size, int access)
        {
            ibv_mr * mr = ibv_reg_mr(pd, buffer, size, access);
            if(!mr)
            {
                int verrno = errno;
                boost::system::error_code err(verrno, boost::system::system_category());
                HPX_IBVERBS_THROWS(err);
            }
            mr_ = std::shared_ptr<ibv_mr>(mr, deleter);
        }

        void reset()
        {
            mr_.reset();
        }

        std::shared_ptr<ibv_mr> mr_;
    };

}}}}

#endif

#endif
