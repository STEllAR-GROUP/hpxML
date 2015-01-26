//  Copyright (c) 2007-2013 Hartmut Kaiser
//  Copyright (c) 2011-2014 Thomas Heller
//  Copyright (c) 2007 Richard D Guidry Jr
//  Copyright (c) 2011 Bryce Lelbach
//  Copyright (c) 2011 Katelyn Kufahl
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef HPX_PARCELSET_ENCODE_PARCELS_HPP
#define HPX_PARCELSET_ENCODE_PARCELS_HPP

#include <hpx/runtime/parcelset/parcel_buffer.hpp>
#include <hpx/runtime/parcelset/encode_parcel.hpp>
#include <hpx/util/high_resolution_timer.hpp>

#if defined(HPX_HAVE_SECURITY)
#include <hpx/components/security/certificate.hpp>
#include <hpx/components/security/parcel_suffix.hpp>
#include <hpx/components/security/signed_type.hpp>
#include <hpx/components/security/hash.hpp>
#endif

#include <boost/integer/endian.hpp>

#if defined(HPX_HAVE_SECURITY)
namespace hpx
{
    HPX_API_EXPORT bool is_starting();

    /// \brief Sign the given parcel-suffix
    ///
    /// \param suffix         The parcel suffoix to be signed
    /// \param signed_suffix  The signed parcel suffix will be placed here
    ///
    HPX_API_EXPORT void sign_parcel_suffix(
        components::security::parcel_suffix const& suffix,
        components::security::signed_parcel_suffix& signed_suffix,
        error_code& ec = throws);
}
#endif

namespace hpx { namespace parcelset
{
#if defined(HPX_HAVE_SECURITY)
    template <typename Archive, typename Connection>
    void serialize_certificate(Archive& archive, Connection & connection,
        std::set<boost::uint32_t>& localities, parcel const& p)
    {
        // We send the certificate corresponding to the originating locality
        // of the parcel if this is the first message over this connection
        // or if the originating locality is not the current one.
        boost::uint32_t locality_id =
            naming::get_locality_id_from_gid(p.get_parcel_id());
        error_code ec(lightweight);
        boost::uint32_t this_locality_id = get_locality_id(ec);
        if (ec) {
            // this should only happen during bootstrap
            HPX_ASSERT(hpx::is_starting());
            this_locality_id = locality_id;
        }

        bool has_certificate = false;
        if ((connection.first_message_ || locality_id != this_locality_id) &&
            localities.find(locality_id) == localities.end())
        {
            // the first message must originate from this locality
            HPX_ASSERT(!connection.first_message_ || locality_id == this_locality_id);

            components::security::signed_certificate const& certificate =
                hpx::get_locality_certificate(locality_id, ec);

            if (!ec) {
                has_certificate = true;
                if (locality_id == this_locality_id)
                    connection.first_message_ = false;
                archive << has_certificate << certificate;

                // keep track of all certificates already prepended for this message
                localities.insert(locality_id);
            }
            else {
                // if the certificate is not available we have to still be on
                // the 'first' message (it's too early for a certificate)
                HPX_ASSERT(connection.first_message_);
                archive << has_certificate;
            }
        }
        else {
            archive << has_certificate;
        }
    }

    template <typename ParcelBuffer>
    void create_message_suffix(ParcelBuffer & buffer,
        naming::gid_type const& parcel_id)
    {
        // mark start of security work
        util::high_resolution_timer timer_sec;

        // calculate hash of overall message
        components::security::hash hash(
            reinterpret_cast<unsigned char const*>(&buffer.data_.front()),
            buffer.data_.size());

        using components::security::parcel_suffix;
        using components::security::signed_parcel_suffix;

        signed_parcel_suffix suffix;
        sign_parcel_suffix(
            parcel_suffix(get_locality_id(), parcel_id, hash),
            suffix);

        // append the signed parcel suffix to the message
        buffer.data_.reserve(buffer.data_.size() + signed_parcel_suffix::size());

        std::copy(suffix.begin(), suffix.end(), std::back_inserter(buffer.data_));

        // store the time required for security
        buffer.data_point_.security_time_ = timer_sec.elapsed_nanoseconds();
    }
#endif

    template <typename Connection>
    std::size_t
    encode_parcels(std::vector<parcel> const & pv, Connection & connection,
        int archive_flags_, std::size_t max_outbound_size, bool enable_security)
    {
        typedef parcel_buffer<typename Connection::buffer_type> parcel_buffer_type;

        // collect argument sizes from parcels
        std::size_t arg_size = 0;
        boost::uint32_t dest_locality_id = pv[0].get_destination_locality_id();

        parcel_buffer_type & buffer = connection.get_buffer(pv[0]);
        HPX_ASSERT(buffer.data_.empty());
        std::size_t parcels_sent = 0;

        // guard against serialization errors
        try {
            try {
                // preallocate data
                for (/**/; parcels_sent != pv.size(); ++parcels_sent)
                {
                    if (arg_size >= max_outbound_size)
                        break;
                    arg_size += traits::get_type_size(pv[parcels_sent]);
                }

                buffer.data_.reserve(arg_size);

                // mark start of serialization
                util::high_resolution_timer timer;

                {
                    // Serialize the data
                    HPX_STD_UNIQUE_PTR<util::binary_filter> filter(
                        pv[0].get_serialization_filter());

                    int archive_flags = archive_flags_;
                    if (filter.get() != 0) {
                        filter->set_max_length(buffer.data_.capacity());
                        archive_flags |= util::enable_compression;
                    }

                    util::portable_binary_oarchive archive(
                        buffer.data_
                      , &buffer.chunks_
                      , dest_locality_id
                      , filter.get()
                      , archive_flags);

#if defined(HPX_HAVE_SECURITY)
                    std::set<boost::uint32_t> localities;
#endif
                    archive << parcels_sent; //-V128

                    for (std::size_t i = 0; i != parcels_sent; ++i)
                    {
#if defined(HPX_HAVE_SECURITY)
                        if (enable_security)
                            serialize_certificate(archive, connection, localities, pv[i]);
#endif
                        archive << pv[i];
                    }

                    arg_size = archive.bytes_written();
                }

#if defined(HPX_HAVE_SECURITY)
                // calculate and sign the hash, but only after everything has
                // been initialized
                if (enable_security && !connection.first_message_)
                    create_message_suffix(buffer, pv[0].get_parcel_id());
#endif
                // store the time required for serialization
                buffer.data_point_.serialization_time_ = timer.elapsed_nanoseconds();
            }
            catch (hpx::exception const& e) {
                LPT_(fatal)
                    << "encode_parcels: "
                       "caught hpx::exception: "
                    << e.what();
                hpx::report_error(boost::current_exception());
                return 0;
            }
            catch (boost::system::system_error const& e) {
                LPT_(fatal)
                    << "encode_parcels: "
                       "caught boost::system::error: "
                    << e.what();
                hpx::report_error(boost::current_exception());
                return 0;
            }
            catch (boost::exception const&) {
                LPT_(fatal)
                    << "encode_parcels: "
                       "caught boost::exception";
                hpx::report_error(boost::current_exception());
                return 0;
            }
            catch (std::exception const& e) {
                // We have to repackage all exceptions thrown by the
                // serialization library as otherwise we will loose the
                // e.what() description of the problem, due to slicing.
                boost::throw_exception(boost::enable_error_info(
                    hpx::exception(serialization_error, e.what())));
                return 0;
            }
        }
        catch (...) {
            LPT_(fatal)
                    << "encode_parcels: "
                   "caught unknown exception";
            hpx::report_error(boost::current_exception());
            return 0;
        }

        buffer.data_point_.num_parcels_ = parcels_sent;
        encode_finalize(buffer, arg_size);

        return parcels_sent;
    }
}}

#endif
