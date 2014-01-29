//  Copyright (c) 2013-2014 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_PARCELSET_POLICIES_IBVERBS_CLIENT_HPP)
#define HPX_PARCELSET_POLICIES_IBVERBS_CLIENT_HPP

#include <hpx/runtime/parcelset/policies/ibverbs/messages.hpp>
#include <hpx/runtime/parcelset/policies/ibverbs/ibverbs_errors.hpp>
#include <hpx/util/spinlock.hpp>

namespace hpx { namespace parcelset { namespace policies { namespace ibverbs { namespace detail {
    struct client
    {
        client()
          : buffer_(0)
          , buffer_size_(0)
          , buffer_mr_(0)
          , server_msg_(0)
          , server_msg_mr_(0)
          , client_msg_(0)
          , client_msg_mr_(0)
          , peer_addr_(0)
          , peer_rkey_(0)
          , size_(0)
          , id_(0)
        {
            int ret = 0;
            ret = posix_memalign(reinterpret_cast<void **>(&server_msg_), EXEC_PAGESIZE, sizeof(message));
            HPX_ASSERT(ret == 0);
            ret = posix_memalign(reinterpret_cast<void **>(&client_msg_), EXEC_PAGESIZE, sizeof(message));
            HPX_ASSERT(ret == 0);
        }

        ~client()
        {
            close();
            if(buffer_)
            {
                free(buffer_);
                buffer_ = 0;
            }
            if(server_msg_)
            {
                free(server_msg_);
                server_msg_ = 0;
            }
            if(client_msg_)
            {
                free(client_msg_);
                client_msg_ = 0;
            }
        }

        char * set_buffer_size(std::size_t buffer_size, boost::system::error_code &ec)
        {
            HPX_ASSERT(buffer_ == 0);
            int ret = 0;
            buffer_size_ = buffer_size;
            ret = posix_memalign(reinterpret_cast<void **>(&buffer_), EXEC_PAGESIZE, buffer_size_);
            HPX_ASSERT(ret == 0);

            return buffer_;
        }


        void close()
        {
            util::spinlock::scoped_lock lk(mtx_);
            if(buffer_mr_)
            {
                ibv_dereg_mr(buffer_mr_);
                buffer_mr_ = 0;
            }
            if(server_msg_mr_)
            {
                ibv_dereg_mr(server_msg_mr_);
                server_msg_mr_ = 0;
            }
            if(client_msg_mr_)
            {
                ibv_dereg_mr(client_msg_mr_);
                client_msg_mr_ = 0;
            }

            if(id_)
            {
                rdma_disconnect(id_);
                id_ = 0;
            }

            peer_addr_ = 0;
            peer_rkey_ = 0;

            size_ = 0;
        }

        void post_receive(boost::system::error_code &ec)
        {
            util::spinlock::scoped_lock lk(mtx_);
            if(!id_)
            {
                HPX_IBVERBS_THROWS_IF(ec, boost::asio::error::not_connected);
                return;
            }

            struct ibv_recv_wr wr, *bad_wr = NULL;
            struct ibv_sge sge;

            std::memset(&wr, 0, sizeof(ibv_recv_wr));

            wr.wr_id = (uintptr_t)id_;
            wr.sg_list = &sge;
            wr.num_sge = 1;

            sge.addr = (uintptr_t)server_msg_;
            sge.length = sizeof(message);
            sge.lkey = server_msg_mr_->lkey;

            int ret = ibv_post_recv(id_->qp, &wr, &bad_wr);
            if(ret)
            {
                int verrno = errno;
                boost::system::error_code err(verrno, boost::system::system_category());
                HPX_IBVERBS_THROWS_IF(
                    ec
                  , err
                );
            }
        }

        void on_preconnect(rdma_cm_id * id, ibv_pd * pd, boost::system::error_code &ec)
        {
            close();
            {
                util::spinlock::scoped_lock lk(mtx_);
                HPX_ASSERT(buffer_);
                buffer_mr_ = ibv_reg_mr(pd, buffer_, buffer_size_, IBV_ACCESS_LOCAL_WRITE);
                if(!buffer_mr_)
                {
                    int verrno = errno;
                    boost::system::error_code err(verrno, boost::system::system_category());
                    HPX_IBVERBS_THROWS_IF(
                        ec
                      , err
                    );
                    return;
                }
                server_msg_mr_ = ibv_reg_mr(pd, server_msg_, sizeof(message), IBV_ACCESS_LOCAL_WRITE | IBV_ACCESS_REMOTE_WRITE);
                if(!server_msg_mr_)
                {
                    int verrno = errno;
                    boost::system::error_code err(verrno, boost::system::system_category());
                    HPX_IBVERBS_THROWS_IF(
                        ec
                      , err
                    );
                    return;
                }

                client_msg_mr_ = ibv_reg_mr(pd, client_msg_, sizeof(message), IBV_ACCESS_LOCAL_WRITE | IBV_ACCESS_REMOTE_WRITE);
                if(!client_msg_mr_)
                {
                    int verrno = errno;
                    boost::system::error_code err(verrno, boost::system::system_category());
                    HPX_IBVERBS_THROWS_IF(
                        ec
                      , err
                    );
                    return;
                }

                id_ = id;
            }
            post_receive(ec);
        }

        void on_connection(rdma_cm_id * id)
        {
            util::spinlock::scoped_lock lk(mtx_);
            id_ = id;
        }

        void write_remote(std::size_t chunk_size, boost::system::error_code &ec)
        {
            util::spinlock::scoped_lock lk(mtx_);
            if(!id_)
            {
                HPX_IBVERBS_THROWS_IF(ec, boost::asio::error::not_connected);
                return;
            }

            ibv_send_wr wr[2], *bad_wr = NULL;
            ibv_sge sge[2];

            std::memset(wr, 0, sizeof(wr));

            wr[0].wr_id = (uintptr_t)id_;
            wr[0].opcode = IBV_WR_RDMA_WRITE;
            wr[0].send_flags = IBV_SEND_SIGNALED;
            wr[0].wr.rdma.remote_addr = peer_addr_;
            wr[0].wr.rdma.rkey = peer_rkey_;

            wr[0].sg_list = &sge[0];
            wr[0].num_sge = 1;

            wr[0].next = &wr[1];

            sge[0].addr = (uintptr_t)buffer_;
            sge[0].length = chunk_size;
            sge[0].lkey = buffer_mr_->lkey;

            wr[1].wr_id = (uintptr_t)id_;
            wr[1].opcode = IBV_WR_SEND;
            wr[1].sg_list = &sge[1];
            wr[1].num_sge = 1;
            wr[1].send_flags = IBV_SEND_SIGNALED;

            client_msg_->id = MSG_DATA;
            sge[1].addr = (uintptr_t)client_msg_;
            sge[1].length = sizeof(message);
            sge[1].lkey = client_msg_mr_->lkey;

            int ret = ibv_post_send(id_->qp, &wr[0], &bad_wr);
            if(ret)
            {
                int verrno = errno;
                boost::system::error_code err(verrno, boost::system::system_category());
                HPX_IBVERBS_THROWS_IF(
                    ec
                  , err
                );
            }
        }

        void send_message(message_type m, boost::system::error_code &ec)
        {
            util::spinlock::scoped_lock lk(mtx_);
            if(!id_)
            {
                HPX_IBVERBS_THROWS_IF(ec, boost::asio::error::not_connected);
                return;
            }

            struct ibv_send_wr wr, *bad_wr = NULL;
            struct ibv_sge sge;

            std::memset(&wr, 0, sizeof(ibv_recv_wr));

            HPX_ASSERT(id_);
            wr.wr_id = (uintptr_t)id_;
            wr.opcode = IBV_WR_SEND;
            wr.sg_list = &sge;
            wr.num_sge = 1;
            wr.send_flags = IBV_SEND_SIGNALED;

            client_msg_->id = m;
            sge.addr = (uintptr_t)client_msg_;
            sge.length = sizeof(message);
            sge.lkey = client_msg_mr_->lkey;

            int ret = 0;
            HPX_ASSERT(id_);
            ret = ibv_post_send(id_->qp, &wr, &bad_wr);
            if(ret)
            {
                int verrno = errno;
                boost::system::error_code err(verrno, boost::system::system_category());
                HPX_IBVERBS_THROWS_IF(
                    ec
                  , err
                );
            }
        }

        void send_shutdown(boost::system::error_code &ec)
        {
            send_message(MSG_SHUTDOWN, ec);
        }

        message_type on_completion(ibv_wc * wc, boost::system::error_code &ec)
        {
            util::spinlock::scoped_lock lk(mtx_);
            if(!id_)
            {
                HPX_IBVERBS_THROWS_IF(ec, boost::asio::error::not_connected);
                return MSG_SHUTDOWN;
            }

            if(wc->opcode == IBV_WC_RECV)
            {
                switch(server_msg_->id)
                {
                    case MSG_MR:
                        peer_addr_ = server_msg_->addr;
                        peer_rkey_ = server_msg_->rkey;
                        return MSG_MR;
                    case MSG_DATA:
                        return MSG_DATA;
                    case MSG_DONE:
                        return MSG_DONE;
                    case MSG_SHUTDOWN:
                        return MSG_SHUTDOWN;
                }
                return MSG_INVALID;
            }

            if(wc->opcode == IBV_WC_SEND && client_msg_->id == MSG_SHUTDOWN)
            {
                return MSG_SHUTDOWN;
            }

            return MSG_RETRY;
        }

        void on_disconnect(rdma_cm_id * id)
        {
        }

        util::spinlock mtx_;

        char *buffer_;
        std::size_t buffer_size_;
        ibv_mr *buffer_mr_;

        message *server_msg_;
        ibv_mr *server_msg_mr_;

        message *client_msg_;
        ibv_mr *client_msg_mr_;

        uint64_t peer_addr_;
        uint32_t peer_rkey_;

        std::size_t size_;

        rdma_cm_id *id_;
    };
}}}}}

#endif
