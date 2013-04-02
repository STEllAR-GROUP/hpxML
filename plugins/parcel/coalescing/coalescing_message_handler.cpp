//  Copyright (c) 2007-2013 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_fwd.hpp>
#include <hpx/runtime/parcelset/parcelport.hpp>

#include <hpx/plugins/message_handler_factory.hpp>
#include <hpx/plugins/parcel/coalescing_message_handler.hpp>

#include <boost/lexical_cast.hpp>

namespace hpx { namespace traits
{
    // Inject additional configuration data into the factory registry for this
    // type. This information ends up in the system wide configuration database
    // under the plugin specific section:
    //
    //      [hpx.plugins.coalescing_message_handler]
    //      ...
    //      num_messages = 50
    //      interval = 100
    //
    template <>
    struct plugin_config_data<hpx::plugins::parcel::coalescing_message_handler>
    {
        static char const* call()
        {
            return "num_messages = 50\n"
                   "interval = 100";
        }
    };
}}

///////////////////////////////////////////////////////////////////////////////
HPX_REGISTER_PLUGIN_MODULE();
HPX_REGISTER_MESSAGE_HANDLER_FACTORY(
    hpx::plugins::parcel::coalescing_message_handler,
    coalescing_message_handler);

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace plugins { namespace parcel
{
    namespace detail
    {
        std::size_t get_num_messages(std::size_t num_messages)
        {
            if (std::size_t(-1) != num_messages)
                return num_messages;

            return boost::lexical_cast<std::size_t>(hpx::get_config_entry(
                "hpx.plugins.coalescing_message_handler.num_messages", 50));
        }

        std::size_t get_interval(std::size_t interval)
        {
            if (std::size_t(-1) != interval)
                return interval;

            return boost::lexical_cast<std::size_t>(hpx::get_config_entry(
                "hpx.plugins.coalescing_message_handler.interval", 100));
        }
    }

    coalescing_message_handler::coalescing_message_handler(
            char const* action_name, parcelset::parcelport* pp, std::size_t num,
            std::size_t interval)
      : buffer_(detail::get_num_messages(num)), pp_(pp),
        interval_(detail::get_interval(interval)),
        timer_(boost::bind(&coalescing_message_handler::timer_flush, this_()),
            boost::bind(&coalescing_message_handler::flush, this_(), true),
            interval_, std::string(action_name) + "_timer", true),
        stopped_(false)
    {}

    void coalescing_message_handler::put_parcel(parcelset::parcel& p,
        write_handler_type const& f)
    {
        mutex_type::scoped_lock l(mtx_);
        if (stopped_) {
            l.unlock();

            // this instance should not buffer parcels anymore
            pp_->put_parcel(p, f);
            return;
        }

        detail::message_buffer::message_buffer_append_state s =
            buffer_.append(p, f);

        switch(s) {
        case detail::message_buffer::first_message:
            timer_.start(false);        // start deadline timer to flush buffer
            break;

        case detail::message_buffer::normal:
            timer_.restart(false);      // restart timer
            break;

        case detail::message_buffer::buffer_now_full:
            flush(l, false);
            break;

        default:
            HPX_THROW_EXCEPTION(bad_parameter,
                "coalescing_message_handler::put_parcel",
                "unexpected return value from message_buffer::append");
            return;
        }
    }

    bool coalescing_message_handler::timer_flush()
    {
        // adjust timer if needed
        mutex_type::scoped_lock l(mtx_);
        if (!buffer_.empty())
            flush(l, false);

        // do not restart timer for now, will be restarted on next parcel
        return false;
    }

    void coalescing_message_handler::flush(bool stop_buffering)
    {
        mutex_type::scoped_lock l(mtx_);
        flush(l, stop_buffering);
    }

    void coalescing_message_handler::flush(mutex_type::scoped_lock& l,
        bool stop_buffering)
    {
        if (!stopped_ && stop_buffering) {
            stopped_ = true;
            timer_.stop();              // interrupt timer
        }

        if (buffer_.empty())
            return;

        detail::message_buffer buff (buffer_.capacity());
        std::swap(buff, buffer_);

        l.unlock();

        BOOST_ASSERT(NULL != pp_);
        buff(pp_);                   // 'invoke' the buffer
    }
}}}
