//  Copyright (c) 2007-2014 Hartmut Kaiser
//  Copyright (c) 2013-2014 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef HPX_PARCELSET_POLICIES_IBVERBS_CONNECTION_HANDLER_HPP
#define HPX_PARCELSET_POLICIES_IBVERBS_CONNECTION_HANDLER_HPP

#include <hpx/config/warnings_prefix.hpp>

#include <hpx/runtime/naming/locality.hpp>
#include <hpx/runtime/parcelset/parcelport_impl.hpp>
#include <hpx/runtime/parcelset/policies/ibverbs/acceptor.hpp>
#include <hpx/runtime/parcelset/policies/ibverbs/memory_pool.hpp>


namespace hpx { namespace parcelset {
    namespace policies { namespace ibverbs
    {
        class receiver;
        class sender;
        class HPX_EXPORT connection_handler;
    }}

    template <>
    struct connection_handler_traits<policies::ibverbs::connection_handler>
    {
        typedef policies::ibverbs::sender connection_type;
        typedef boost::mpl::false_  send_early_parcel;
        typedef boost::mpl::true_ do_background_work;
        typedef boost::mpl::false_ do_enable_parcel_handling;

        static const char * name()
        {
            return "ibverbs";
        }

        static const char * pool_name()
        {
            return "parcel_pool_ibverbs";
        }

        static const char * pool_name_postfix()
        {
            return "-ibverbs";
        }
    };

    namespace policies { namespace ibverbs
    {
        class HPX_EXPORT connection_handler
          : public parcelport_impl<connection_handler>
        {
            typedef parcelport_impl<connection_handler> base_type;

        public:
            static std::vector<std::string> runtime_configuration();
            static std::size_t memory_chunk_size(util::runtime_configuration const& ini);
            static std::size_t max_memory_chunks(util::runtime_configuration const& ini);

            connection_handler(util::runtime_configuration const& ini,
                HPX_STD_FUNCTION<void(std::size_t, char const*)> const& on_start_thread,
                HPX_STD_FUNCTION<void()> const& on_stop_thread);

            ~connection_handler();

            /// Start the handling of connections.
            bool do_run();

            /// Stop the handling of connections.
            void do_stop();

            void background_work();

            /// Retrieve the type of the locality represented by this parcelport
            connection_type get_type() const
            {
                return connection_ibverbs;
            }

            /// Return the name of this locality
            std::string get_locality_name() const;

            boost::shared_ptr<sender> create_connection(
                naming::locality const& l, error_code& ec);

            void add_sender(boost::shared_ptr<sender> const& sender_connection);

            ibv_pd *get_pd(ibv_context *context, boost::system::error_code & ec);

            ibv_mr register_buffer(ibv_pd * pd, char * buffer, std::size_t size);
            ibv_mr get_mr(ibv_pd * pd, char * buffer, std::size_t);

        private:
            // helper functions for receiving parcels
            void handle_messages();
            bool do_sends();
            bool do_receives();
            void handle_accepts();

            memory_pool memory_pool_;

            typedef std::map<ibv_context *, ibv_pd *> pd_map_type;
            hpx::lcos::local::spinlock pd_map_mtx_;
            pd_map_type pd_map_;

            typedef
                std::map<void *, ibverbs_mr>
                mr_cache_type;
            typedef
                std::map<ibv_pd *, mr_cache_type>
                mr_map_type;

            hpx::lcos::local::spinlock mr_map_mtx_;
            mr_map_type mr_map_;

            ibv_device **device_list_;
            std::vector<ibv_context *> context_list_;

            /// Acceptor used to listen for incoming connections.
            acceptor acceptor_;

            hpx::lcos::local::spinlock receivers_mtx_;
            typedef std::list<boost::shared_ptr<receiver> > receivers_type;
            receivers_type receivers_;

            hpx::lcos::local::spinlock senders_mtx_;
            typedef std::list<boost::shared_ptr<sender> > senders_type;
            senders_type senders_;

            double time_send;
            double time_recv;
            double time_acct;

            boost::atomic<bool> stopped_;
            boost::atomic<bool> handling_messages_;
            boost::atomic<bool> handling_accepts_;

            bool use_io_pool_;
        };
    }}
}}

#include <hpx/config/warnings_suffix.hpp>

#endif
