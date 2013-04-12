//  Copyright (c)      2013 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_PARCELSET_IBVERBS_SERVER_HPP)
#define HPX_PARCELSET_IBVERBS_SERVER_HPP

#include <hpx/runtime/parcelset/ibverbs/messages.hpp>
#include <tcmalloc.h>

namespace hpx { namespace parcelset { namespace ibverbs { namespace detail {
    struct server
    {
        server()
          : buffer_(0)
          , buffer_size_(0)
          , buffer_mr_(0)
          , server_msg_(0)
          , server_msg_mr_(0)
          , client_msg_(0)
          , client_msg_mr_(0)
          , size_(0)
          , id_(0)
        {
            int ret = 0;
            ret = posix_memalign(reinterpret_cast<void **>(&server_msg_), EXEC_PAGESIZE, sizeof(message));
            BOOST_ASSERT(ret == 0);
            
            ret = posix_memalign(reinterpret_cast<void **>(&client_msg_), EXEC_PAGESIZE, sizeof(message));
            BOOST_ASSERT(ret == 0);
        }

        ~server()
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
            BOOST_ASSERT(buffer_ == 0);
            int ret = 0;
            buffer_size_ = buffer_size;
            ret = posix_memalign(reinterpret_cast<void **>(&buffer_), EXEC_PAGESIZE, buffer_size_);
            BOOST_ASSERT(ret == 0);
            boost::uint64_t header[2] = {0};
            std::memcpy(buffer_, header, sizeof(header));
            return buffer_;
        }

        void close()
        {
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

            size_ = 0;
        }

        void post_receive()
        {
            struct ibv_recv_wr wr, *bad_wr = NULL;
            struct ibv_sge sge;

            std::memset(&wr, 0, sizeof(ibv_recv_wr));

            BOOST_ASSERT(id_);
            wr.wr_id = (uintptr_t)id_;
            wr.sg_list = &sge;
            wr.num_sge = 1;

            sge.addr = (uintptr_t)client_msg_;
            sge.length = sizeof(message);
            sge.lkey = client_msg_mr_->lkey;

            int ret = 0;
            BOOST_ASSERT(id_);
            ret = ibv_post_recv(id_->qp, &wr, &bad_wr);
            if(ret)
            {
                // FIXME: error
            }
        }

        void send_message()
        {
            struct ibv_send_wr wr, *bad_wr = NULL;
            struct ibv_sge sge;
                
            std::memset(&wr, 0, sizeof(ibv_recv_wr));
            
            BOOST_ASSERT(id_);
            wr.wr_id = (uintptr_t)id_;
            wr.opcode = IBV_WR_SEND;
            wr.sg_list = &sge;
            wr.num_sge = 1;
            wr.send_flags = IBV_SEND_SIGNALED;

            sge.addr = (uintptr_t)server_msg_;
            sge.length = sizeof(message);
            sge.lkey = server_msg_mr_->lkey;

            int ret = 0;
            BOOST_ASSERT(id_);
            ret = ibv_post_send(id_->qp, &wr, &bad_wr);
            if(ret)
            {
                // FIXME: error
            }
        }

        void send_ready()
        {
            server_msg_->id = MSG_DONE;
            send_message();
        }
        
        void on_preconnect(rdma_cm_id * id, ibv_pd * pd)
        {
            close();
            BOOST_ASSERT(buffer_);
            buffer_mr_ = ibv_reg_mr(
                pd
              , buffer_
              , buffer_size_
              , IBV_ACCESS_LOCAL_WRITE | IBV_ACCESS_REMOTE_WRITE
            );
            if(!buffer_mr_)
            {
                // FIXME: error
            }
            server_msg_mr_ = ibv_reg_mr(
                pd
              , server_msg_
              , sizeof(hpx::parcelset::ibverbs::message)
              , IBV_ACCESS_LOCAL_WRITE | IBV_ACCESS_REMOTE_WRITE
            );
            if(!server_msg_mr_)
            {
                // FIXME: error
            }
            client_msg_mr_ = ibv_reg_mr(
                pd
              , client_msg_
              , sizeof(hpx::parcelset::ibverbs::message)
              , IBV_ACCESS_LOCAL_WRITE | IBV_ACCESS_REMOTE_WRITE
            );
            if(!client_msg_mr_)
            {
                // FIXME: error
            }

            id_ = id;

            //post_receive();
        }

        void on_connection(rdma_cm_id *id)
        {
            id_ = id;
            server_msg_->id = MSG_MR;
            server_msg_->addr = (uintptr_t)buffer_mr_->addr;
            server_msg_->rkey = buffer_mr_->rkey;

            send_message();
        }
        
        message_type on_completion(ibv_wc * wc)
        {
            /*
            std::cout << "server opcode: ";
            switch (wc->opcode)
            {
                case IBV_WC_SEND:
                    std::cout << "IBV_WC_SEND\n";
                    break;
                case IBV_WC_RDMA_WRITE:
                    std::cout << "IBV_WC_RDMA_WRITE\n";
                    break;
                case IBV_WC_RDMA_READ:
                    std::cout << "IBV_WC_RDMA_READ\n";
                    break;
                case IBV_WC_COMP_SWAP:
                    std::cout << "IBV_WC_COMP_SWAP\n";
                    break;
                case IBV_WC_FETCH_ADD:
                    std::cout << "IBV_WC_FETCH_ADD\n";
                    break;
                case IBV_WC_BIND_MW:
                    std::cout << "IBV_WC_BIND_MW\n";
                    break;
                case IBV_WC_RECV:
                    std::cout << "IBV_WC_RECV\n";
                    break;
                case IBV_WC_RECV_RDMA_WITH_IMM:
                    std::cout << "IBV_WC_RDMA_WRITE\n";
                    break;
            }
            */

            if(wc->opcode == IBV_WC_RECV)
            {
                //std::cout << client_msg_->id << "\n";
                switch(client_msg_->id)
                {
                    case MSG_DATA:
                        return MSG_DATA;
                    default:
                        return MSG_INVALID;
                }
            }

            if(wc->opcode == IBV_WC_SEND)
            {
                //std::cout << server_msg_->id << "\n";
                switch(server_msg_->id)
                {
                    case MSG_DONE:
                        return MSG_DONE;
                    case MSG_DATA:
                        return MSG_DATA;
                    case MSG_MR:
                        return MSG_MR;
                    default:
                        return MSG_INVALID;
                }
            }

            /*
            if(wc->opcode == IBV_WC_RECV_RDMA_WITH_IMM)
            {
                return MSG_DATA;
            }
            */
            //post_receive();
            return MSG_RETRY;
        }
        
        void on_disconnect(rdma_cm_id * id)
        {
        }

        char *buffer_;
        std::size_t buffer_size_;
        ibv_mr *buffer_mr_;

        message *server_msg_;
        ibv_mr *server_msg_mr_;

        message *client_msg_;
        ibv_mr *client_msg_mr_;

        std::size_t size_;

        rdma_cm_id *id_;
    };
}}}}

#endif
