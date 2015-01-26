//  Copyright (c) 2007-2013 Hartmut Kaiser
//  Copyright (c) 2014-2015 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef HPX_PARCELSET_DECODE_PARCEL_HPP
#define HPX_PARCELSET_DECODE_PARCEL_HPP

#include <hpx/config.hpp>
#include <hpx/util/portable_binary_archive.hpp>

#if defined(HPX_HAVE_SECURITY)
#include <hpx/components/security/hash.hpp>
#include <hpx/components/security/parcel_suffix.hpp>
#include <hpx/components/security/certificate.hpp>
#include <hpx/components/security/signed_type.hpp>
#include <hpx/runtime.hpp>
#endif

#include <boost/shared_ptr.hpp>

#include <vector>

namespace hpx
{
#if defined(HPX_HAVE_SECURITY)
    /// \brief Verify the certificate in the given byte sequence
    ///
    /// \param data      The full received message buffer, assuming that it
    ///                  has a parcel_suffix appended.
    /// \param hash      The has object for the received data.
    /// \param parcel_id The parcel id of the first parcel in side the message
    ///
    template <typename Buffer>
    bool verify_parcel_suffix(Buffer const& data,
        naming::gid_type& parcel_id, error_code& ec = throws)
    {
        runtime* rt = get_runtime_ptr();
        if (0 == rt)
        {
            HPX_THROWS_IF(ec, invalid_status,
                "hpx::verify_parcel_suffix",
                "the runtime system is not operational at this point");
            return false;
        }

        return rt->verify_parcel_suffix(data, parcel_id, ec);
    }

    bool is_starting();
    bool is_running();
#endif

    namespace parcelset
    {
        template <typename Buffer>
        std::vector<util::serialization_chunk> decode_chunks(Buffer & buffer)
        {
            typedef typename Buffer::transmission_chunk_type transmission_chunk_type;

            std::vector<util::serialization_chunk> chunks;

            std::size_t num_zero_copy_chunks =
                static_cast<std::size_t>(
                    static_cast<boost::uint32_t>(buffer.num_chunks_.first));

            if (num_zero_copy_chunks != 0)
            {
                // decode chunk information
                std::size_t num_non_zero_copy_chunks =
                    static_cast<std::size_t>(
                        static_cast<boost::uint32_t>(buffer.num_chunks_.second));

                chunks.resize(num_zero_copy_chunks + num_non_zero_copy_chunks);

                // place the zero-copy chunks at their spots first
                for (std::size_t i = 0; i != num_zero_copy_chunks; ++i)
                {
                    transmission_chunk_type& c = buffer.transmission_chunks_[i];
                    boost::uint64_t first = c.first, second = c.second;

                    HPX_ASSERT(buffer.chunks_[i].size() == second);

                    chunks[first] = util::create_pointer_chunk(
                            buffer.chunks_[i].data(), second);
                }

                std::size_t index = 0;
                for (std::size_t i = num_zero_copy_chunks;
                     i != num_zero_copy_chunks + num_non_zero_copy_chunks;
                     ++i)
                {
                    transmission_chunk_type& c = buffer.transmission_chunks_[i];
                    boost::uint64_t first = c.first, second = c.second;

                    // find next free entry
                    while (chunks[index].size_ != 0)
                        ++index;

                    // place the index based chunk at the right spot
                    chunks[index] = util::create_index_chunk(first, second);
                    ++index;
                }
#if defined(HPX_DEBUG)
                // make sure that all spots have been populated
                for (std::size_t i = 0;
                     i != num_zero_copy_chunks + num_non_zero_copy_chunks;
                     ++i)
                {
                    HPX_ASSERT(chunks[i].size_ != 0);
                }
#endif
            }

            return chunks;
        }

        ///////////////////////////////////////////////////////////////////////////
#if defined(HPX_HAVE_SECURITY)
        // read the certificate, if available, and add it to the local certificate
        // store
        template <typename Archive>
        bool deserialize_certificate(Archive& archive, bool first_message)
        {
            bool has_certificate = false;
            archive >> has_certificate;

            if (has_certificate) {
                components::security::signed_certificate certificate;
                archive >> certificate;
                add_locality_certificate(certificate);
                if (first_message)
                    first_message = false;
            }
            return first_message;
        }

        // calculate and verify the hash
        template <typename Buffer>
        void verify_message_suffix(
            Buffer const& parcel_data,
            performance_counters::parcels::data_point& receive_data,
            naming::gid_type& parcel_id)
        {
            // mark start of security work
            util::high_resolution_timer timer_sec;

            if (!verify_parcel_suffix(parcel_data, parcel_id)) {
                // all hell breaks loose!
                HPX_THROW_EXCEPTION(security_error,
                    "decode_message",
                    "verify_message_suffix failed");
                return;
            }

            // store the time required for security
            receive_data.security_time_ = timer_sec.elapsed_nanoseconds();
        }
#endif

        template <typename Parcelport, typename Buffer>
        void decode_message(
            Parcelport & pp
          , Buffer buffer
          , std::size_t parcel_count
          , bool first_message
        )
        {
            std::vector<util::serialization_chunk> chunks(decode_chunks(buffer));

            unsigned archive_flags = boost::archive::no_header;
            if (!pp.allow_array_optimizations()) {
                archive_flags |= util::disable_array_optimization;
                archive_flags |= util::disable_data_chunking;
            }
            else if (!pp.allow_zero_copy_optimizations()) {
                archive_flags |= util::disable_data_chunking;
            }
            boost::uint64_t inbound_data_size = buffer.data_size_;

            // protect from un-handled exceptions bubbling up
            try {
                try {
                    // mark start of serialization
                    util::high_resolution_timer timer;
                    boost::int64_t overall_add_parcel_time = 0;
                    performance_counters::parcels::data_point& data =
                        buffer.data_point_;

                    {
                        // De-serialize the parcel data
                        util::portable_binary_iarchive archive(buffer.data_,
                            &chunks, inbound_data_size, archive_flags);

                        if(parcel_count == 0)
                            archive >> parcel_count; //-V128a
                        for(std::size_t i = 0; i != parcel_count; ++i)
                        {
#if defined(HPX_HAVE_SECURITY)
                            naming::gid_type parcel_id;
                            if (pp.enable_security())
                            {
                                // handle certificate and verify parcel suffix once
                                first_message = deserialize_certificate(archive,
                                    first_message);
                                if (!first_message && i == 0)
                                {
                                    verify_message_suffix(buffer->data_,
                                        buffer->data_point_, parcel_id);
                                }
                            }

                            // de-serialize parcel and add it to incoming parcel queue
                            parcel p;
                            archive >> p;

                            // verify parcel id, but only once while handling the
                            // first parcel
                            if (pp.enable_security() && !first_message && i == 0 &&
                                parcel_id != p.get_parcel_id())
                            {
                                // again, all hell breaks loose
                                HPX_THROW_EXCEPTION(security_error,
                                    "decode_message", "parcel id mismatch");
                                return;
                            }
#else
                            // de-serialize parcel and add it to incoming parcel queue
                            parcel p;
                            archive >> p;
#endif
                            // make sure this parcel ended up on the right locality
#ifdef HPX_DEBUG
                            if(hpx::get_locality() && hpx::get_runtime_ptr())
                                HPX_ASSERT(p.get_destination_locality() == hpx::get_locality());
#endif

                            // be sure not to measure add_parcel as serialization time
                            boost::int64_t add_parcel_time = timer.elapsed_nanoseconds();
                            pp.add_received_parcel(p);
                            overall_add_parcel_time += timer.elapsed_nanoseconds() -
                                add_parcel_time;
                        }

                        // complete received data with parcel count
                        data.num_parcels_ = parcel_count;
                        data.raw_bytes_ = archive.bytes_read();
                    }

                    // store the time required for serialization
                    data.serialization_time_ = timer.elapsed_nanoseconds() -
                        overall_add_parcel_time;

                    pp.add_received_data(data);
                }
                catch (hpx::exception const& e) {
                    LPT_(error)
                        << "decode_message: caught hpx::exception: "
                        << e.what();
                    hpx::report_error(boost::current_exception());
                }
                catch (boost::system::system_error const& e) {
                    LPT_(error)
                        << "decode_message: caught boost::system::error: "
                        << e.what();
                    hpx::report_error(boost::current_exception());
                }
                catch (boost::exception const&) {
                    LPT_(error)
                        << "decode_message: caught boost::exception.";
                    hpx::report_error(boost::current_exception());
                }
                catch (std::exception const& e) {
                    // We have to repackage all exceptions thrown by the
                    // serialization library as otherwise we will loose the
                    // e.what() description of the problem, due to slicing.
                    boost::throw_exception(boost::enable_error_info(
                        hpx::exception(serialization_error, e.what())));
                }
            }
            catch (...) {
                LPT_(error)
                    << "decode_message: caught unknown exception.";
                hpx::report_error(boost::current_exception());
            }
        }

        template <typename Parcelport, typename Buffer>
        void decode_parcel(Parcelport & parcelport, Buffer buffer)
        {
            if(hpx::is_running() && parcelport.async_serialization())
            {
                hpx::applier::register_thread_nullary(
                    util::bind(
                        util::one_shot(&decode_message<Parcelport, Buffer>),
                        boost::ref(parcelport), std::move(buffer), 1, false),
                    "decode_parcels",
                    threads::pending, true, threads::thread_priority_boost);
            }
            else
            {
                decode_message(parcelport, std::move(buffer), 1, false);
            }
        }
    }
}

#endif
