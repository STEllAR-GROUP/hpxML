//  Copyright (c) 2007-2013 Hartmut Kaiser
//  Copyright (c)      2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_fwd.hpp>
#include <hpx/runtime/parcelset/parcel.hpp>
#include <hpx/util/portable_binary_iarchive.hpp>
#include <hpx/util/portable_binary_oarchive.hpp>
#include <hpx/util/serialize_intrusive_ptr.hpp>

#include <boost/serialization/string.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/array.hpp>
#include <boost/serialization/shared_ptr.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace parcelset
{
    ///////////////////////////////////////////////////////////////////////////
    // generate unique parcel id
    naming::gid_type parcel::generate_unique_id(boost::uint32_t locality_id_default)
    {
        static boost::atomic<boost::uint64_t> id(0);

        error_code ec(lightweight);        // ignore all errors
        boost::uint32_t locality_id = hpx::get_locality_id(ec);
        if (locality_id == naming::invalid_locality_id)
            locality_id = locality_id_default;

        naming::gid_type result = naming::get_gid_from_locality_id(locality_id);
        result.set_lsb(++id);
        return result;
    }

    namespace detail
    {
        ///////////////////////////////////////////////////////////////////////////
        template <typename Archive>
        void parcel_data::save(Archive& ar, bool has_source_id, bool has_continuation) const
        {
            // If we have a source id, serialize it.
            if (has_source_id)
                ar << source_id_;

            ar << action_;

            // If we have a continuation, serialize it.
            if (has_continuation) {
                actions::continuation const* c = continuation_.get();
                ar << c;
            }
        }

        ///////////////////////////////////////////////////////////////////////////
        template <typename Archive>
        void single_destination_parcel_data::save_optimized(Archive& ar,
            const unsigned int version, boost::mpl::true_) const
        {
            data_.has_source_id_ = source_id_ ? true : false;

            ar << boost::serialization::make_array(&data_, 1);
            ar << addr_;

            this->parcel_data::save(ar, data_.has_source_id_ ? true : false,
                data_.has_continuation_ ? true : false);
        }

        template <typename Archive>
        void single_destination_parcel_data::save_optimized(Archive& ar,
            const unsigned int version, boost::mpl::false_) const
        {
            data_.has_source_id_ = source_id_ ? true : false;

            ar << data_.parcel_id_;
            ar << data_.start_time_ << data_.creation_time_;
            ar << data_.dest_size_;
            ar << data_.has_source_id_ << data_.has_continuation_;
            ar << data_.dest_;

            ar << addr_;

            this->parcel_data::save(ar, data_.has_source_id_ ? true : false,
                data_.has_continuation_ ? true : false);
        }

        template <typename Archive>
        void single_destination_parcel_data::save(Archive& ar,
            const unsigned int version) const
        {
            if(ar.flags() & util::disable_array_optimization)
            {
                save_optimized(ar, version, boost::mpl::false_());
            }
            else
            {
                save_optimized(ar, version, boost::mpl::true_());
            }
        }

        ///////////////////////////////////////////////////////////////////////
        template <typename Archive>
        void parcel_data::load(Archive& ar, bool has_source_id, bool has_continuation)
        {
            // Check for a source id.
            if (has_source_id)
                ar >> source_id_;

            ar >> action_;

            // handle continuation.
            if (has_continuation) {
                actions::continuation* c = 0;
                ar >> c;
                continuation_.reset(c);
            }
        }

        template <typename Archive>
        void single_destination_parcel_data::load_optimized(Archive & ar,
            const unsigned int version, boost::mpl::true_)
        {
            ar >> boost::serialization::make_array(&data_, 1);
            ar >> addr_;

            this->parcel_data::load(ar, data_.has_source_id_ ? true : false,
                data_.has_continuation_ ? true : false);
        }

        template <typename Archive>
        void single_destination_parcel_data::load_optimized(Archive & ar,
            const unsigned int version, boost::mpl::false_)
        {
            ar >> data_.parcel_id_;
            ar >> data_.start_time_ >> data_.creation_time_;
            ar >> data_.dest_size_;
            ar >> data_.has_source_id_ >> data_.has_continuation_;
            ar >> data_.dest_;

            ar >> addr_;

            this->parcel_data::load(ar, data_.has_source_id_ ? true : false,
                data_.has_continuation_ ? true : false);
        }

        template <typename Archive>
        void single_destination_parcel_data::load(Archive & ar,
            const unsigned int version)
        {
            if (version > HPX_PARCEL_VERSION)
            {
                HPX_THROW_EXCEPTION(version_too_new,
                    "parcel::load",
                    "trying to load parcel with unknown version");
            }

            if(ar.flags() & util::disable_array_optimization)
            {
                load_optimized(ar, version, boost::mpl::false_());
            }
            else
            {
                load_optimized(ar, version, boost::mpl::true_());
            }
        }

        ///////////////////////////////////////////////////////////////////////////
        template <typename Archive>
        void multi_destination_parcel_data::save_optimized(Archive& ar,
            const unsigned int version, boost::mpl::true_) const
        {
            data_.has_source_id_ = source_id_ ? true : false;

            ar << boost::serialization::make_array(&data_, 1);
            ar << dests_ << addrs_;

            this->parcel_data::save(ar, data_.has_source_id_ ? true : false,
                data_.has_continuation_ ? true : false);
        }

        template <typename Archive>
        void multi_destination_parcel_data::save_optimized(Archive& ar,
            const unsigned int version, boost::mpl::false_) const
        {
            data_.has_source_id_ = source_id_ ? true : false;

            ar << data_.parcel_id_;
            ar << data_.start_time_ << data_.creation_time_;
            ar << data_.dest_size_;
            ar << data_.has_source_id_ << data_.has_continuation_;
            ar << dests_ << addrs_;

            this->parcel_data::save(ar, data_.has_source_id_ ? true : false,
                data_.has_continuation_ ? true : false);
        }

        template <typename Archive>
        void multi_destination_parcel_data::save(Archive& ar,
            const unsigned int version) const
        {
            if(ar.flags() & util::disable_array_optimization)
            {
                save_optimized(ar, version, boost::mpl::false_());
            }
            else
            {
                save_optimized(ar, version, boost::mpl::true_());
            }
        }

        ///////////////////////////////////////////////////////////////////////
        template <typename Archive>
        void multi_destination_parcel_data::load_optimized(Archive & ar,
            const unsigned int version, boost::mpl::true_)
        {
            ar >> boost::serialization::make_array(&data_, 1);
            ar >> dests_ >> addrs_;

            this->parcel_data::load(ar, data_.has_source_id_ ? true : false,
                data_.has_continuation_ ? true : false);
        }

        template <typename Archive>
        void multi_destination_parcel_data::load_optimized(Archive & ar,
            const unsigned int version, boost::mpl::false_)
        {
            ar >> data_.parcel_id_;
            ar >> data_.start_time_ >> data_.creation_time_;
            ar >> data_.dest_size_;
            ar >> data_.has_source_id_ >> data_.has_continuation_;
            ar >> dests_ >> addrs_;

            this->parcel_data::load(ar, data_.has_source_id_ ? true : false,
                data_.has_continuation_ ? true : false);
        }

        template <typename Archive>
        void multi_destination_parcel_data::load(Archive & ar,
            const unsigned int version)
        {
            if (version > HPX_PARCEL_VERSION)
            {
                HPX_THROW_EXCEPTION(version_too_new,
                    "parcel::load",
                    "trying to load parcel with unknown version");
            }

            if(ar.flags() & util::disable_array_optimization)
            {
                load_optimized(ar, version, boost::mpl::false_());
            }
            else
            {
                load_optimized(ar, version, boost::mpl::true_());
            }
        }

        ///////////////////////////////////////////////////////////////////////
        // explicit instantiation for the correct archive types
        template HPX_EXPORT void
        single_destination_parcel_data::save(util::portable_binary_oarchive&,
            const unsigned int) const;

        template HPX_EXPORT void
        single_destination_parcel_data::load(util::portable_binary_iarchive&,
            const unsigned int);

        template HPX_EXPORT void
        multi_destination_parcel_data::save(util::portable_binary_oarchive&,
            const unsigned int) const;

        template HPX_EXPORT void
        multi_destination_parcel_data::load(util::portable_binary_iarchive&,
            const unsigned int);

        ///////////////////////////////////////////////////////////////////////////
        std::ostream& operator<< (std::ostream& os, single_destination_parcel_data const& p)
        {
            os << "(" << p.data_.dest_ << ":" << p.addr_ << ":";
            os << p.action_->get_action_name() << ")";
            return os;
        }

        std::ostream& operator<< (std::ostream& os, multi_destination_parcel_data const& p)
        {
            os << "(";
            if (!p.dests_.empty())
                os << p.dests_[0] << ":" << p.addrs_[0] << ":";

            os << p.action_->get_action_name() << ")";
            return os;
        }
    }

    template <typename Archive>
    void parcel::save(Archive& ar, const unsigned int version) const
    {
        BOOST_ASSERT(data_.get() != 0);

        bool is_multi_destination = data_->is_multi_destination();
        ar << is_multi_destination;

        if (is_multi_destination)
            ar << *static_cast<detail::multi_destination_parcel_data const*>(data_.get());
        else
            ar << *static_cast<detail::single_destination_parcel_data const*>(data_.get());
    }

    template <typename Archive>
    void parcel::load(Archive& ar, const unsigned int version)
    {
        bool is_multi_destination;
        ar >> is_multi_destination;

        if (is_multi_destination) {
            boost::intrusive_ptr<detail::parcel_data> data(
                new detail::multi_destination_parcel_data);
            ar >> *static_cast<detail::multi_destination_parcel_data*>(data.get());
            std::swap(data_, data);
        }
        else {
            boost::intrusive_ptr<detail::parcel_data> data(
                new detail::single_destination_parcel_data);
            ar >> *static_cast<detail::single_destination_parcel_data*>(data.get());
            std::swap(data_, data);
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    // explicit instantiation for the correct archive types
    template HPX_EXPORT void
    parcel::save(util::portable_binary_oarchive&, const unsigned int) const;

    template HPX_EXPORT void
    parcel::load(util::portable_binary_iarchive&, const unsigned int);

    ///////////////////////////////////////////////////////////////////////////
    std::ostream& operator<< (std::ostream& os, parcel const& p)
    {
        BOOST_ASSERT(p.data_.get() != 0);
        if (p.data_->is_multi_destination()) {
            os << *static_cast<detail::multi_destination_parcel_data const*>(p.data_.get());
        }
        else {
            os << *static_cast<detail::single_destination_parcel_data const*>(p.data_.get());
        }
        return os;
    }
}}

