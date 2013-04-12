//  Copyright (c)      2013 Thomas Heller
//  Copyright (c) 2007-2012 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_PARCELSET_IBVERBS_PARCELPORT_CONNECTION_HPP)
#define HPX_PARCELSET_IBVERBS_PARCELPORT_CONNECTION_HPP

#include <sstream>
#include <vector>

#include <hpx/runtime/parcelset/ibverbs/context.hpp>
#include <hpx/runtime/parcelset/ibverbs/messages.hpp>
#include <hpx/runtime/applier/applier.hpp>
#include <hpx/util/connection_cache.hpp>
#include <hpx/performance_counters/parcels/data_point.hpp>
#include <hpx/performance_counters/parcels/gatherer.hpp>
#include <hpx/util/high_resolution_timer.hpp>

#include <boost/asio/buffer.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/read.hpp>
#include <boost/asio/write.hpp>
#include <boost/atomic.hpp>
#include <boost/bind.hpp>
#include <boost/bind/protect.hpp>
#include <boost/cstdint.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/integer/endian.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/tuple/tuple.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace parcelset { namespace ibverbs
{
    /// Represents a single parcelport_connection from a client.
    class parcelport_connection
      : public boost::enable_shared_from_this<parcelport_connection>,
        private boost::noncopyable
    {
    public:
        /// Construct a sending parcelport_connection with the given io_service.
        parcelport_connection(
                boost::asio::io_service& io_service,
                naming::locality const& there,
                performance_counters::parcels::gatherer& parcels_sent);

        ~parcelport_connection()
        {
            // gracefully and portably shutdown the socket
            boost::system::error_code ec;
            context_.shutdown(ec); // shut down data connection
            context_.close(ec);    // close the socket to give it back to the OS
        }

        void post_receive(rdma_cm_id * id);
    
        void on_preconn(rdma_cm_id * id);

        void set_parcel (parcel const& p)
        {
            set_parcel(std::vector<parcel>(1, p));
        }

        void set_parcel (std::vector<parcel> const& p);

        /// Get the window associated with the parcelport_connection.
        parcelset::ibverbs::client_context& context() { return context_; }

        /// Asynchronously write a data structure to the socket.
        template <typename Handler, typename ParcelPostprocess>
        void async_write(Handler handler, ParcelPostprocess parcel_postprocess)
        {
            /// Increment sends and begin timer.
            send_data_.time_ = timer_.elapsed_nanoseconds();
            /// Increment sends and begin timer.
            send_data_.time_ = timer_.elapsed_nanoseconds();

            // Write the serialized data to the socket. We use "gather-write"
            // to send both the header and the data in a single write operation.
            /*
            std::vector<boost::asio::const_buffer> buffers;
            buffers.push_back(boost::asio::buffer(&out_priority_, sizeof(out_priority_)));
            buffers.push_back(boost::asio::buffer(&out_size_, sizeof(out_size_)));
            buffers.push_back(boost::asio::buffer(&out_data_size_, sizeof(out_data_size_)));
            buffers.push_back(boost::asio::buffer(out_buffer_));
            */

            void (parcelport_connection::*f)(boost::system::error_code const&, std::size_t,
                    boost::tuple<Handler, ParcelPostprocess>)
                = &parcelport_connection::handle_write<Handler, ParcelPostprocess>;

            if(out_buffer_.size() > sync_threshold_)
            {
                context_.async_write(out_buffer_,//buffers,
                    boost::bind(f, shared_from_this(),
                        boost::asio::placeholders::error, ::_2,
                        boost::make_tuple(handler, parcel_postprocess)));
            }
            else
            {
                boost::system::error_code ec;
                std::size_t size = context_.write(out_buffer_, ec);
                handle_write(ec, size, boost::make_tuple(handler, parcel_postprocess));
            }
        }

        naming::locality const& destination() const
        {
            return there_;
        }

    protected:
        /// handle completed write operation
        template <typename Handler, typename ParcelPostprocess>
        void handle_write(boost::system::error_code const& e, std::size_t bytes,
            boost::tuple<Handler, ParcelPostprocess> handler)
        {
            // just call initial handler
            boost::get<0>(handler)(e, bytes);

            // complete data point and push back onto gatherer
            send_data_.time_ = timer_.elapsed_nanoseconds() - send_data_.time_;
            parcels_sent_.add_data(send_data_);

            // now we can give this connection back to the cache
            //reclaim_data_buffer(out_buffer_);

            send_data_.bytes_ = 0;
            send_data_.time_ = 0;
            send_data_.serialization_time_ = 0;
            send_data_.num_parcels_ = 0;

            // Call post-processing handler, which will send remaining pending
            // parcels. Pass along the connection so it can be reused if more
            // parcels have to be sent.
            boost::get<1>(handler)(e, there_, shared_from_this());
        }

    protected:
#if 0
        data_buffer get_data_buffer(std::size_t size, std::string const& name)
        {
            data_buffer buffer;
            if (cache_.get(size, buffer))
                return buffer;

            return data_buffer(name.c_str(), size);
        }

        void reclaim_data_buffer(data_buffer& buffer)
        {
            cache_.add(buffer.size(), buffer);
            buffer.resize(0);
            buffer.reset();
        }
#endif

    private:
        /// Window for the parcelport_connection.
        parcelset::ibverbs::client_context context_;

        /// buffer for outgoing data
        std::size_t sync_threshold_;
        boost::integer::ulittle8_t out_priority_;
        boost::integer::ulittle64_t out_size_;
        boost::integer::ulittle64_t out_data_size_;
        std::vector<char> out_buffer_;

        /// the other (receiving) end of this connection
        naming::locality there_;
        /// Counters and their data containers.
        util::high_resolution_timer timer_;
        performance_counters::parcels::data_point send_data_;
        performance_counters::parcels::gatherer& parcels_sent_;

        // archive flags
        int archive_flags_;
    };

    typedef boost::shared_ptr<parcelport_connection> parcelport_connection_ptr;
}}}

#endif
