// Copyright (c) 2016 John Biddiscombe
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at

#ifndef HPX_PARCELSET_POLICIES_VERBS_ENDPOINT_HPP
#define HPX_PARCELSET_POLICIES_VERBS_ENDPOINT_HPP

// Includes
#include <plugins/parcelport/verbs/rdma/rdma_error.hpp>
#include <plugins/parcelport/verbs/rdma/protection_domain.hpp>
#include <plugins/parcelport/verbs/rdma/memory_region.hpp>
#include <plugins/parcelport/verbs/rdma/event_channel.hpp>
#include <plugins/parcelport/verbs/rdma/rdma_shared_receive_queue.hpp>
#include <plugins/parcelport/verbs/rdma/verbs_sender_receiver.hpp>
//
#include <hpx/config/parcelport_verbs_defines.hpp>
//
#include <plugins/parcelport/verbs/rdmahelper/include/RdmaCompletionQueue.h>
#include <inttypes.h>
#include <stdexcept>
#include <string>
#include <memory>
#include <iostream>
#include <iomanip>
#include <atomic>

#define HPX_PARCELPORT_VERBS_MAX_WORK_REQUESTS     2048

using namespace bgcios;

namespace hpx {
namespace parcelset {
namespace policies {
namespace verbs
{

    // Connection for RDMA operations with a remote partner.
    class verbs_endpoint : public verbs_sender_receiver
    {
    public:
        // ---------------------------------------------------------------------------
        enum connection_state {
            connecting,
            accepting,
            rejecting,
            connected,
            disconnecting,
            being_disconnected
        };

        std::atomic<connection_state> state_;

       // ---------------------------------------------------------------------------
        // This constructor is used to create a local server endpoint.
        // The server endpoint can accept incoming connections, or make outgoing ones.
        // Every node will create one server endpoint, then for each connection
        // made a new client endpoint will be constructed.
        // The endpoint will represent the local node.
        verbs_endpoint(struct sockaddr_in local_address) : verbs_sender_receiver(nullptr)
         {
            LOG_DEVEL_MSG("verbs_endpoint Listening Server Constructor");
            //
            init();
            create_id();
            bind(local_address);
         }

        // ---------------------------------------------------------------------------
        // This constructor is used when we have received a connection request and
        // create a client endpoint to manage the remote client/server.
        // The endpoint will represent the remote node.
        // NB. we only use one CompletionQ, send/recv share the same one.
        // This could be changed if need arises
        verbs_endpoint(
            struct rdma_cm_id *cmId,
            rdma_protection_domain_ptr domain,
            bgcios::RdmaCompletionQueuePtr CompletionQ,
            rdma_memory_pool_ptr pool,
            rdma_shared_receive_queue_ptr SRQ,
            bool signalSendQueue = false) :
                verbs_sender_receiver(nullptr)
        {
            LOG_DEVEL_MSG("verbs_endpoint receive connection constructor");
            //
            init();

            // Use the input rdma connection management id.
            cmId_           = cmId;
            remote_address_ = *(sockaddr_in*)(&cmId->route.addr.dst_addr);
            srq_            = SRQ;
            completionQ_    = CompletionQ;
            memory_pool_    = pool;

            // Create a queue pair. Both send and receive share a completion queue
            createQp(domain, CompletionQ, CompletionQ,
                HPX_PARCELPORT_VERBS_MAX_WORK_REQUESTS, signalSendQueue);
        }

        // ---------------------------------------------------------------------------
        // This constructor is used when we make/start a new connection to a remote
        // node (as opposed to when they connect to us).
        // The endpoint will represent the remote node.
        verbs_endpoint(
            struct sockaddr_in localAddress,
            struct sockaddr_in remoteAddress) :
                verbs_sender_receiver(nullptr)
        {
            LOG_DEVEL_MSG("verbs_endpoint create connection constructor "
                << ipaddress(localAddress.sin_addr.s_addr) << " "
                << ipaddress(remoteAddress.sin_addr.s_addr));
            //
            init();
            create_id();
            //
            resolve_address(&localAddress, &remoteAddress, std::chrono::milliseconds(10000));
        }

        // ---------------------------------------------------------------------------
        ~verbs_endpoint(void)
        {
            // Destroy the rdma cm id and queue pair.
            if (cmId_ != nullptr) {
                if (cmId_->qp != nullptr) {
                    rdma_destroy_qp(cmId_); // No return code
                    LOG_DEBUG_MSG("destroyed queue pair");
                }

                if (rdma_destroy_id(cmId_) == 0) {
                    LOG_DEBUG_MSG("destroyed rdma cm id " << cmId_);
                    cmId_ = nullptr;
                }
                else {
                    int err = errno;
                    LOG_ERROR_MSG(
                        "error destroying rdma cm id " << cmId_ << ": "
                        << rdma_error::error_string(err));
                }
            }

            LOG_DEBUG_MSG("releasing memory pool reference");
            memory_pool_.reset();

            // event channel is cleaned up by unique ptr destructor
            LOG_DEBUG_MSG("destroyed connection");
        }

        // ---------------------------------------------------------------------------
        //
        void handle_event() {

        }


        // ---------------------------------------------------------------------------
        // Initiate a connection to another node's server endpoint
        int makePeer(rdma_protection_domain_ptr domain,
            RdmaCompletionQueuePtr completionQ)
        {
            this->_domain = domain;
            this->completionQ_ = completionQ;

            // Create a queue pair.
            try {
                createQp(domain, completionQ, completionQ, 1, false);
            }
            catch (rdma_error& e) {
                LOG_ERROR_MSG(
                    "makePeer error creating queue pair: "
                    << rdma_error::error_string(e.error_code()));
                return e.error_code();
            }

            // Resolve a route to the server.
            int err = resolve_route();
            if (err != 0) {
                LOG_ERROR_MSG("error resolving route to "
                    << sockaddress(&remote_address_)
                    << "from " << sockaddress(&local_address_)
                    << ": " << rdma_error::error_string(err));
                return err;
            }

            // Connect to server.
            err = connect();
            if (err != 0) {
                LOG_ERROR_MSG("error in makePeer connecting to "
                    << sockaddress(&remote_address_)
                    << "from " << sockaddress(&local_address_)
                    << ": " << rdma_error::error_string(err));

                LOG_ERROR_MSG("destroy qp");
                rdma_destroy_qp(cmId_);

                LOG_ERROR_MSG("reset domain");
                this->_domain.reset();

                LOG_ERROR_MSG("reset CQ ");
                this->completionQ_.reset();

                return err;
            }

            return 0;
        }

        // ---------------------------------------------------------------------------
        RdmaCompletionQueuePtr& getCompletionQ(void) {
            return completionQ_;
        }

        // ---------------------------------------------------------------------------
        void refill_preposts(unsigned int preposts) {
            //            LOG_DEBUG_MSG("Entering refill size of waiting receives is "
            //                << decnumber(get_receive_count()));
            while (get_receive_count() < preposts) {
                // if the pool has spare small blocks (just use 0 size) then
                // refill the queues, but don't wait, just abort if none are available
                if (this->memory_pool_->can_allocate_unsafe(
                    this->memory_pool_->small_.chunk_size_))
                {
                    LOG_DEBUG_MSG("Pre-Posting a receive to client size "
                        << hexnumber(this->memory_pool_->small_.chunk_size_));
                    rdma_memory_region *region =
                        this->get_free_region(
                            this->memory_pool_->small_.chunk_size_);
                    this->post_recv_region_as_id_counted(region,
                        region->get_size());
                }
                else {
                    break; // don't block, if there are no free memory blocks
                }
            }
        }

        // ---------------------------------------------------------------------------
        inline void set_memory_pool(rdma_memory_pool_ptr pool) {
            this->memory_pool_ = pool;
        }

        // ---------------------------------------------------------------------------
        inline rdma_memory_region *get_free_region(size_t size)
        {
            rdma_memory_region* region = this->memory_pool_->allocate_region(size);
            if (!region) {
                LOG_ERROR_MSG("Error creating free memory region");
            }
            region->set_message_length(size);

            return region;
        }

        // ---------------------------------------------------------------------------
        // Called by server side prior to listening for connections
        int bind(struct sockaddr_in local_address)
        {
           local_address_ = local_address;
           // Bind address to the listening connection.
           LOG_DEVEL_MSG("binding " << sockaddress(&local_address_)
               << "to port " << decnumber(local_address_.sin_port));
           //
           int err = rdma_bind_addr(cmId_, (struct sockaddr *)&local_address_);
           if (err != 0) {
              err = abs(err);
              LOG_ERROR_MSG("error binding to address "
                  << sockaddress(&local_address_) << ": "
                  << rdma_error::error_string(err));
              return err;
           }
           LOG_DEBUG_MSG("bound rdma cm id to address " << sockaddress(&local_address_));
           return 0;
        }

        // ---------------------------------------------------------------------------
        // called by server side to enable clients to connect
        int listen(int backlog)
        {
           // Start listening for connections.
           int err = rdma_listen(cmId_, backlog);
           if (err != 0) {
              err = abs(err);
              LOG_ERROR_MSG("error listening for connections: " << rdma_error::error_string(err));
              return err;
           }
           LOG_DEBUG_MSG("listening for connections with backlog " << backlog);
           return 0;
        }

        // ---------------------------------------------------------------------------
        template<typename Func>
        int poll_for_events(Func &&f) {
            return event_channel_->poll_event_channel(std::forward<Func>(f));
        }

        // ---------------------------------------------------------------------------
        int get_event(event_channel::event_ack_type ack,
            rdma_cm_event_type event, struct rdma_cm_event *&cm_event)
        {
            return event_channel_->get_event(ack, event, cm_event);
        }

        // ---------------------------------------------------------------------------
        int resolve_address(
            struct sockaddr_in *localAddr,
            struct sockaddr_in *remoteAddr,
            std::chrono::milliseconds timeout)
        {
            int err = -1;
            using namespace std::chrono;
            auto start = system_clock::now();
//            while (err!=0 &&
//                duration_cast<milliseconds>(system_clock::now()-start) < timeout)
            {
                // Resolve the addresses.
                LOG_DEVEL_MSG("resolving remote address "
                    << sockaddress(localAddr) << ": "
                    << sockaddress(remoteAddr));
                localAddr->sin_port = 0 ;
                int rc = rdma_resolve_addr(cmId_,
                    (struct sockaddr *) localAddr,
                    (struct sockaddr *) remoteAddr, 1000); // Configurable timeout?

                if (rc != 0) {
                    rdma_error e(errno, "rdma_resolve_addr() failed");
                    LOG_ERROR_MSG("error resolving remote address "
                        << sockaddress(localAddr) << ": "
                        << sockaddress(remoteAddr) << ": "
                        << rdma_error::error_string(e.error_code()));
                    throw e;
                }

                // Save the addresses.
                memcpy(&remote_address_, remoteAddr, sizeof(struct sockaddr_in));
                if (localAddr != nullptr) {
                    memcpy(&local_address_, localAddr, sizeof(struct sockaddr_in));
                }

                LOG_DEVEL_MSG("Called  rdma_resolve_addr    from "
                    << sockaddress(&local_address_)
                    << "to " << sockaddress(&remote_address_)
                    << "( " << sockaddress(remoteAddr) << ")");

                // Wait for RDMA_CM_EVENT_ADDR_RESOLVED event.
                struct rdma_cm_event *event;
                err = event_channel_->get_event(event_channel::do_ack_event,
                    RDMA_CM_EVENT_ADDR_RESOLVED, event);
                if (err != 0) {
                    std::cout << "local address "
                        << sockaddress(&local_address_)
                    << " remote address "
                    << sockaddress(&remote_address_)
                    << " " << errno << " " << rdma_error::error_string(errno)
                    << std::endl;
                }
            }

            LOG_DEBUG_MSG("resolved to address " << sockaddress(&remote_address_));
            return err;
        }

        // ---------------------------------------------------------------------------
        int accept()
        {
            //
            // Debugging code to get ip address of soure/dest of event
            // NB: The src and dest fields refer to the message and not the connect request
            // so we are actually receiving a request from dest (it is the src of the msg)
            //
            struct sockaddr *ip_src = &cmId_->route.addr.src_addr;
            struct sockaddr_in *addr_src =
                reinterpret_cast<struct sockaddr_in *>(ip_src);
            //
            struct sockaddr *ip_dst = &cmId_->route.addr.dst_addr;
            struct sockaddr_in *addr_dst =
                reinterpret_cast<struct sockaddr_in *>(ip_dst);
            local_address_ = *addr_src;
            remote_address_ = *addr_dst;

            LOG_DEVEL_MSG("Calling rdma_accept          from "
                << ipaddress(remote_address_.sin_addr.s_addr)
                << "to " << ipaddress(local_address_.sin_addr.s_addr)
                << "( " << ipaddress(local_address_.sin_addr.s_addr) << ")");

            // Accept the connection request.
            struct rdma_conn_param param;
            memset(&param, 0, sizeof(param));
            param.responder_resources = 1;
            param.initiator_depth = 1;
            param.rnr_retry_count = 7; // special code for infinite retries

            int rc = rdma_accept(cmId_, &param);
            if (rc != 0) {
                int err = errno;
                LOG_ERROR_MSG(
                    "error accepting connection: " << rdma_error::error_string(err));
                return err;
            }

            LOG_DEBUG_MSG("accepted connection from client " << sockaddress(&remote_address_));
            return 0;
        }

        // ---------------------------------------------------------------------------
        int reject(rdma_cm_id *id)
        {
            //
            // Debugging code to get ip address of soure/dest of event
            // NB: The src and dest fields refer to the message and not the connect request
            // so we are actually receiving a request from dest (it is the src of the msg)
            //
            struct sockaddr *ip_src = &cmId_->route.addr.src_addr;
            struct sockaddr_in *addr_src =
                reinterpret_cast<struct sockaddr_in *>(ip_src);
            //
            struct sockaddr *ip_dst = &cmId_->route.addr.dst_addr;
            struct sockaddr_in *addr_dst =
                reinterpret_cast<struct sockaddr_in *>(ip_dst);
            local_address_ = *addr_src;
            remote_address_ = *addr_dst;

            LOG_DEVEL_MSG("Calling rdma_reject          from "
                << ipaddress(remote_address_.sin_addr.s_addr)
                << "to " << ipaddress(local_address_.sin_addr.s_addr)
                << "( " << ipaddress(local_address_.sin_addr.s_addr) << ")");

            // Reject a connection request.
            int err = rdma_reject(id, 0, 0);
            if (err != 0) {
                LOG_ERROR_MSG("error rejecting connection on cmid "
                    << hexpointer(id) << rdma_error::error_string(errno));
                return -1;
            }

            LOG_DEVEL_MSG("Rejected connection from new client");
            return 0;
        }

        // ---------------------------------------------------------------------------
        int resolve_route(void)
        {
            LOG_DEBUG_MSG("Calling rdma_resolve_route   from "
                << ipaddress(local_address_.sin_addr.s_addr)
                << "to " << ipaddress(remote_address_.sin_addr.s_addr)
                << "( " << ipaddress(local_address_.sin_addr.s_addr) << ")");
            // Resolve a route.
            int rc = rdma_resolve_route(cmId_, 1000); // Configurable timeout?
            if (rc != 0) {
                int err = errno;
                LOG_ERROR_MSG(
                    "error resolving route: " << rdma_error::error_string(err));
                return err;
            }

            // Wait for RDMA_CM_EVENT_ROUTE_RESOLVED event.
            struct rdma_cm_event *event;
            int err = event_channel_->get_event(event_channel::do_ack_event,
                RDMA_CM_EVENT_ROUTE_RESOLVED, event);

            LOG_DEBUG_MSG("resolved route to " << sockaddress(&remote_address_));

            return err;
        }

        // ---------------------------------------------------------------------------
        int connect(void)
        {
            LOG_DEVEL_MSG("Calling rdma_connect         from "
                << ipaddress(local_address_.sin_addr.s_addr)
                << "to " << ipaddress(remote_address_.sin_addr.s_addr)
                << "( " << ipaddress(local_address_.sin_addr.s_addr) << ")");
            // Connect to the server.
            struct rdma_conn_param param;
            memset(&param, 0, sizeof(param));
            param.responder_resources = 1;
            param.initiator_depth = 2;
            param.retry_count = 7;
            param.rnr_retry_count = 7;
            int rc = rdma_connect(cmId_, &param);
            if (rc != 0) {
                int err = errno;
                LOG_ERROR_MSG("error in rdma_connect to "
                    << ipaddress(remote_address_.sin_addr.s_addr)
                    << "from " << ipaddress(local_address_.sin_addr.s_addr)
                    << ": " << rdma_error::error_string(err));
                return err;
            }

            // Wait for RDMA_CM_EVENT_ESTABLISHED event.
            struct rdma_cm_event *event;
            int err = event_channel_->get_event(event_channel::no_ack_event,
                RDMA_CM_EVENT_ESTABLISHED, event);

            if (err != 0 && event == NULL)
            {
                LOG_DEVEL_MSG("1: Connection error, unknown event ");
                return err;
            }
            else if (err != 0 && event->event != RDMA_CM_EVENT_ESTABLISHED)
            {
                LOG_DEVEL_MSG("2: did not get RDMA_CM_EVENT_ESTABLISHED");
                if (event->event == RDMA_CM_EVENT_REJECTED) {
                    LOG_DEVEL_MSG("2: Connection rejected "
                        << "from " << ipaddress(remote_address_.sin_addr.s_addr)
                        << "( " << ipaddress(local_address_.sin_addr.s_addr) << ")");
                } else {
                    throw rdma_error(errno, "Error in connecting");
                }
                int status = event->status;
                event_channel::ack_event(event);
                //
                return status;
            }
            else if (err != 0)
            {
                LOG_DEVEL_MSG("3: Connection error, RDMA_CM_EVENT_ESTABLISHED not set ");
                return err;
            }

            LOG_DEBUG_MSG("connected to " << sockaddress(&remote_address_));
            return event_channel::ack_event(event);
            ;
        }

        // ---------------------------------------------------------------------------
        int disconnect(bool initiate)
        {
            LOG_DEBUG_MSG("disconnect");
            // Disconnect the connection.
            int err = rdma_disconnect(cmId_);
            if (err != 0) {
                err = abs(err);
                LOG_ERROR_MSG(
                    "error disconnect: " << rdma_error::error_string(err));
                return err;
            }

            // Wait for the DISCONNECTED event if initiating the disconnect sequence.
            if (initiate) {
                LOG_INFO_MSG("initiated disconnect");
                struct rdma_cm_event *event;
                err = event_channel_->get_event(event_channel::do_ack_event,
                    RDMA_CM_EVENT_DISCONNECTED, event);
            }

            LOG_INFO_MSG("disconnect completed for rdma cm id " << cmId_);
            return err;
        }

        // ---------------------------------------------------------------------------
        int create_srq(rdma_protection_domain_ptr domain)
        {
            try {
                srq_ = std::make_shared < rdma_shared_receive_queue
                    > (cmId_, domain);
            }
            catch (...) {
                return 0;
            }
            return 1;
        }

        // ---------------------------------------------------------------------------
        uint32_t getQpNum(void) const {
            return cmId_->qp->qp_num;
        }

        // ---------------------------------------------------------------------------
        struct ibv_context *getContext(void) const {
            return cmId_->verbs;
        }

        // ---------------------------------------------------------------------------
        inline in_addr_t get_local_address(void) const {
            return local_address_.sin_addr.s_addr;
        }

        // ---------------------------------------------------------------------------
        inline in_port_t get_local_port(void) {
            if (local_address_.sin_port == 0) {
                local_address_.sin_port = rdma_get_src_port(cmId_);
            }
            return local_address_.sin_port;
        }

        // ---------------------------------------------------------------------------
        inline in_addr_t get_remote_address(void) const {
            return remote_address_.sin_addr.s_addr;
        }

        // ---------------------------------------------------------------------------
        inline in_port_t get_remote_port(void) const {
            return remote_address_.sin_port;
        }

        // ---------------------------------------------------------------------------
        inline rdma_shared_receive_queue_ptr SRQ() {
            return srq_;
        }

        // ---------------------------------------------------------------------------
        virtual inline struct ibv_srq *getsrq_() {
            if (srq_ == NULL)
                return NULL;
            return srq_->getsrq_();
        }

        // ---------------------------------------------------------------------------
        inline bool getInitiatedConnection() {
            return _initiated_connection;
        }

        // ---------------------------------------------------------------------------
        inline void setInitiatedConnection(bool i) {
            _initiated_connection = i;
        }

        inline struct sockaddr_in *get_remote_address() {
            return &remote_address_;
        }

    protected:

        // ---------------------------------------------------------------------------
        void init(void)
        {
            // Initialize private data.
            memset(&local_address_, 0, sizeof(local_address_));
            memset(&remote_address_, 0, sizeof(remote_address_));
            event_channel_ = std::unique_ptr<event_channel> (new event_channel);
            clear_counters();
            _initiated_connection = false;
            return;
        }

        // ---------------------------------------------------------------------------
        void create_id(void)
        {
            // Create the event channel.
            event_channel_->create_channel();

            // Create the rdma cm id.
            int err = rdma_create_id(event_channel_->get_event_channel(),
                &cmId_, this, RDMA_PS_TCP);
            if (err != 0) {
                rdma_error e(err, "rdma_create_id() failed");
                LOG_ERROR_MSG(
                    "error creating rdma cm id: " << rdma_error::error_string(err));
                throw e;
            }
            LOG_DEVEL_MSG("created rdma cm id " << cmId_);
        }

        // ---------------------------------------------------------------------------
        void createQp(rdma_protection_domain_ptr domain,
            bgcios::RdmaCompletionQueuePtr sendCompletionQ,
            bgcios::RdmaCompletionQueuePtr recvCompletionQ,
            uint32_t maxWorkRequests, bool signalSendQueue)
        {
            // Create a queue pair.
            struct ibv_qp_init_attr qpAttributes;
            memset(&qpAttributes, 0, sizeof qpAttributes);
            qpAttributes.cap.max_send_wr = 4096; // maxWorkRequests;
            qpAttributes.cap.max_recv_wr = 4096; // maxWorkRequests;
            qpAttributes.cap.max_send_sge = 6; // 6;
            qpAttributes.cap.max_recv_sge = 6; // 6;
            qpAttributes.qp_context = this; // Save the pointer this object.
            qpAttributes.sq_sig_all = signalSendQueue;
            qpAttributes.qp_type = IBV_QPT_RC;
            qpAttributes.send_cq = sendCompletionQ->getQueue();
            qpAttributes.recv_cq = recvCompletionQ->getQueue();
            LOG_DEBUG_MSG("Setting SRQ to " << getsrq_());
            qpAttributes.srq = getsrq_();

            int rc = rdma_create_qp(cmId_, domain->getDomain(),
                &qpAttributes);

            LOG_DEBUG_MSG("After Create QP, SRQ is " << getsrq_());

            //   cmId_->qp = ibv_create_qp(domain->getDomain(), &qpAttributes);
            //   int rc = (cmId_->qp==nullptr);

            if (rc != 0) {
                rdma_error e(errno, "rdma_create_qp() failed");
                LOG_ERROR_MSG(
                    "createQp : error creating queue pair: " << hexpointer(this)
                    "local address " << sockaddress(&local_address_)
                << " remote address " << sockaddress(&remote_address_)
                << rdma_error::error_string(e.error_code()));
                throw e;
            }

            LOG_DEBUG_MSG("created queue pair " << decnumber(cmId_->qp->qp_num)
                << " max inline data is " << hexnumber(qpAttributes.cap.max_inline_data));

            return;
        }

        rdma_memory_pool_ptr memory_pool_;

        rdma_shared_receive_queue_ptr srq_;

        // Event channel for notification of RDMA connection management events.
        std::unique_ptr<event_channel> event_channel_;

        // Address of this (local) side of the connection.
        struct sockaddr_in local_address_;

        // Address of other (remote) side of the connection.
        struct sockaddr_in remote_address_;

        // if the client connected to the server, then set this flag so that
        // at shutdown, we use the correct flag for disconnect(mode)
        bool _initiated_connection;

        // Memory region for inbound messages.
        rdma_protection_domain_ptr _domain;

        // Completion queue.
        bgcios::RdmaCompletionQueuePtr completionQ_;

    };

    // Smart pointer for verbs_endpoint object.
    typedef std::shared_ptr<verbs_endpoint> verbs_endpoint_ptr;

}}}}

#endif