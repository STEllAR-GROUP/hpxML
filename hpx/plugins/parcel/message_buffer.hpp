//  Copyright (c) 2007-2013 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_RUNTIME_PARCELSET_POLICIES_COALESCING_MESSAGE_BUFFER_MAR_07_2013_1250PM)
#define HPX_RUNTIME_PARCELSET_POLICIES_COALESCING_MESSAGE_BUFFER_MAR_07_2013_1250PM

#include <hpx/hpx_fwd.hpp>
#include <hpx/runtime/parcelset/parcelport.hpp>
#include <hpx/lcos/local/spinlock.hpp>
#include <hpx/util/move.hpp>

#include <vector>

#include <boost/noncopyable.hpp>

namespace hpx { namespace plugins { namespace parcel { namespace detail
{
    class message_buffer
    {
        BOOST_COPYABLE_AND_MOVABLE(message_buffer);

        typedef lcos::local::spinlock mutex_type;

    public:
        enum message_buffer_append_state
        {
            normal = 0,
            first_message = 1,
            buffer_now_full = 2,
            singleton_buffer = 3
        };


        message_buffer()
          : max_messages_(0)
        {}

        message_buffer(std::size_t max_messages)
          : max_messages_(max_messages)
        {}

        message_buffer(message_buffer const& rhs)
          : max_messages_(rhs.max_messages_),
            messages_(rhs.messages_),
            handlers_(rhs.handlers_)
        {}

        message_buffer(BOOST_RV_REF(message_buffer) rhs)
          : max_messages_(rhs.max_messages_),
            messages_(boost::move(rhs.messages_)),
            handlers_(boost::move(rhs.handlers_))
        {}

        message_buffer& operator=(BOOST_COPY_ASSIGN_REF(message_buffer) rhs)
        {
            if (&rhs != this) {
                max_messages_ = rhs.max_messages_;
                messages_ = rhs.messages_;
                handlers_ = rhs.handlers_;
            }
            return *this;
        }

        message_buffer& operator=(BOOST_RV_REF(message_buffer) rhs)
        {
            if (&rhs != this) {
                max_messages_ = rhs.max_messages_;
                messages_ = boost::move(rhs.messages_);
                handlers_ = boost::move(rhs.handlers_);
            }
            return *this;
        }

        void operator()(parcelset::parcelport* set)
        {
            message_buffer buff (max_messages_);

            {
                mutex_type::scoped_lock l(mtx_);
                std::swap(buff, *this);
            }

            buff.flush(set);
        }

        message_buffer_append_state append(parcelset::parcel& p,
            parcelset::parcelport::write_handler_type const& f)
        {
            mutex_type::scoped_lock l(mtx_);

            BOOST_ASSERT(messages_.size() == handlers_.size());

            int result = normal;
            if (messages_.empty())
                result = first_message;

            messages_.push_back(p);
            handlers_.push_back(f);

            if (messages_.size() >= max_messages_)
                result = buffer_now_full;

            return message_buffer_append_state(result);
        }

        bool empty() const
        {
            mutex_type::scoped_lock l(mtx_);
            BOOST_ASSERT(messages_.size() == handlers_.size());
            return messages_.empty();
        }

        void clear()
        {
            mutex_type::scoped_lock l(mtx_);
            messages_.clear();
            handlers_.clear();
        }

        size_t size() const
        {
            mutex_type::scoped_lock l(mtx_);
            BOOST_ASSERT(messages_.size() == handlers_.size());
            return messages_.size();
        }

        void swap(message_buffer& o)
        {
            std::swap(max_messages_, o.max_messages_);
            std::swap(messages_, o.messages_);
            std::swap(handlers_, o.handlers_);
        }

    protected:
        void flush(parcelset::parcelport* set)
        {
            if (!messages_.empty())
                set->put_parcels(messages_, handlers_);
        }

    private:
        mutable mutex_type mtx_;
        std::vector<parcelset::parcel> messages_;
        std::vector<parcelset::parcelport::write_handler_type> handlers_;
        std::size_t max_messages_;
    };
}}}}

#endif
