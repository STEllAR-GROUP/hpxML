
//  Copyright (c) 2007-2013 Hartmut Kaiser
//  Copyright (c) 2014-2015 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef HPX_PARCELSET_POLICIES_MPI_RECEIVER_HPP
#define HPX_PARCELSET_POLICIES_MPI_RECEIVER_HPP

#include <hpx/plugins/parcelport/mpi/header.hpp>
#include <hpx/plugins/parcelport/mpi/receiver_connection.hpp>

#include <hpx/util/memory_chunk_pool.hpp>

#include <list>
#include <iterator>

namespace hpx { namespace parcelset { namespace policies { namespace mpi
{
    class parcelport;

    struct receiver
    {
        typedef hpx::lcos::local::spinlock mutex_type;
        typedef std::list<std::pair<int, header> > header_list;
        typedef std::set<std::pair<int, int> > handles_header_type;
        typedef util::memory_chunk_pool<mutex_type> memory_pool_type;
        typedef
            receiver_connection
            connection_type;
#if defined(HPX_INTEL_VERSION) && ((__GNUC__ == 4 && __GNUC_MINOR__ == 4) || HPX_INTEL_VERSION < 1400)
        typedef boost::shared_ptr<connection_type> connection_ptr;
#else
        typedef std::unique_ptr<connection_type> connection_ptr;
#endif
        typedef std::list<connection_ptr> connection_list;

        receiver(parcelport & pp, memory_pool_type & chunk_pool
              , std::size_t max_connections)
          : pp_(pp)
          , chunk_pool_(chunk_pool)
          , max_connections_(max_connections)
          , num_connections_(0)
        {}

        void run()
        {
            new_header();
        }

        bool background_work(std::size_t num_thread)
        {
            // We accept as many connections as we can ...
            while(true)
            {
                connection_ptr rcv = accept();
                if(rcv)
                {
                    if(!rcv->receive())
                    {
                        boost::unique_lock<mutex_type> l(connections_mtx_);
                        connections_.push_back(std::move(rcv));
                    }
                }
                else
                {
                    break;
                }
            }

            connection_list connections;
            {
                boost::unique_lock<mutex_type> l(connections_mtx_);
                std::swap(connections, connections_);
            }

            if(!connections.empty())
            {
                if(hpx::is_starting())
                {
                    receive_messages(std::move(connections));
                }
                else
                {
//                     error_code ec(lightweight);
                    hpx::applier::register_thread_nullary(
                        util::bind(
                            util::one_shot(&receiver::receive_messages),
                            this, std::move(connections)),
                        "mpi::receiver::receive_messages",
                        threads::pending, true, threads::thread_priority_boost,
                        num_thread, threads::thread_stacksize_default);
                }
                return true;
            }
            return false;
        }

        void receive_messages(
            connection_list connections
        )
        {
            std::size_t k = 0;
            connection_list::iterator it = connections.begin();

            // Handle all receives
            while(it != connections.end())
            {
                connection_type & rcv = **it;
                if(rcv.receive())
                {
                    it = connections.erase(it);
                }
                else
                {
                    if(k < 32 || k & 1) //-V112
                    {
                        if(threads::get_self_ptr())
                            hpx::this_thread::suspend(hpx::threads::pending,
                                "mpi::receiver::wait_done");
                    }
                    ++k;
                    ++it;
                }
            }

            if(!connections.empty())
            {
                boost::unique_lock<mutex_type> l(connections_mtx_);
                if(connections_.empty())
                {
                    std::swap(connections, connections_);
                }
                else
                {
                    connections_.insert(
                        connections_.end()
#if defined(HPX_INTEL_VERSION) && ((__GNUC__ == 4 && __GNUC_MINOR__ == 4) || HPX_INTEL_VERSION < 1400)
                      , connections.begin()
                      , connections.end()
#else
                      , std::make_move_iterator(connections.begin())
                      , std::make_move_iterator(connections.end())
#endif
                    );
                }
            }
        }

        connection_ptr accept()
        {
            mutex_type::scoped_try_lock l(headers_mtx_);
            if(l)
                return accept_locked(l);
            return std::unique_ptr<connection_type>();
        }

        connection_ptr accept_locked(mutex_type::scoped_try_lock & header_lock)
        {
            util::mpi_environment::scoped_try_lock l;

            connection_ptr res;
            if(l.locked)
            {
                MPI_Status status;
                if(request_done_locked(hdr_request_, &status))
                {
                    header h = new_header();
                    l.unlock();
                    header_lock.unlock();
                    res.reset(
                        new connection_type(
                            status.MPI_SOURCE
                          , h
                          , pp_
                          , chunk_pool_
                        )
                    );
                    return res;
                }
            }
            return res;
        }

        header new_header()
        {
            header h = rcv_header_;
            rcv_header_.reset();
            MPI_Irecv(
                rcv_header_.data()
              , rcv_header_.data_size_
              , MPI_BYTE
              , MPI_ANY_SOURCE
              , 0
              , util::mpi_environment::communicator()
              , &hdr_request_
            );
            return h;
        }

        parcelport & pp_;

        memory_pool_type & chunk_pool_;

        mutex_type headers_mtx_;
        MPI_Request hdr_request_;
        header rcv_header_;

        mutex_type handles_header_mtx_;
        handles_header_type handles_header_;

        mutex_type connections_mtx_;
        std::size_t const max_connections_;
        boost::atomic<std::size_t> num_connections_;
        connection_list connections_;

        bool request_done_locked(MPI_Request & r, MPI_Status *status)
        {
            int completed = 0;
            int ret = 0;
            ret = MPI_Test(&r, &completed, status);
            HPX_ASSERT(ret == MPI_SUCCESS);
            if(completed)// && status->MPI_ERROR != MPI_ERR_PENDING)
            {
                return true;
            }
            return false;
        }
    };

}}}}

#endif
