////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <hpx/config.hpp>
#include <hpx/hpx_fwd.hpp>
#include <hpx/state.hpp>
#include <hpx/runtime.hpp>
#include <hpx/runtime/components/console_logging.hpp>

#include <boost/fusion/include/at_c.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace components
{

void console_logging_locked(naming::id_type const& prefix,
    messages_type const& msgs)
{
    try {
        applier::apply<server::console_logging_action<> >(prefix, msgs);
    }
    catch (hpx::exception const& e) {
        using boost::fusion::at_c;

        // if this is not the console locality (or any other error occurs)
        // we might be too late for any logging, write to local file
        BOOST_FOREACH(message_type const& msg, msgs)
        {
            std::string fail_msg = e.what();

            if (fail_msg.empty())
                fail_msg = "Failed logging to console";
            else
                fail_msg = "Failed logging to console due to: "
                         + fail_msg; 

            switch (at_c<0>(msg)) {
            default:
            case destination_hpx:
                LHPX_CONSOLE_(at_c<1>(msg)) << fail_msg << "\n"
                                            << at_c<2>(msg);
                break;

            case destination_timing:
                LTIM_CONSOLE_(at_c<1>(msg)) << fail_msg << "\n"
                                            << at_c<2>(msg);
                break;

            case destination_agas:
                LAGAS_CONSOLE_(at_c<1>(msg)) << fail_msg << "\n"
                                             << at_c<2>(msg);
                break;

            case destination_app:
                LAPP_CONSOLE_(at_c<1>(msg)) << fail_msg << "\n"
                                            << at_c<2>(msg);
                break;
            }
        }
    }
}

void pending_logs::add(message_type const& msg)
{
    {
        queue_mutex_type::scoped_lock l(queue_mtx_); 
        queue_.push_back(msg);
    }

    ++queue_size_;

    if (threads::threadmanager_is(running) && threads::get_self_ptr()
       && activated_.load() && (max_pending < queue_size_.load())) 
        send();
}

void pending_logs::cleanup()
{
    if (threads::threadmanager_is(running) && threads::get_self_ptr()
       && activated_.load() && (0 < queue_size_.load())) 
        send();
}

void pending_logs::send()
{
    // Resolve the console prefix if it's still invalid.
    if (HPX_UNLIKELY(naming::invalid_id == prefix_))
    {
        prefix_mutex_type::scoped_try_lock l(prefix_mtx_); 

        if (l.owns_lock() && (naming::invalid_id == prefix_))
        {
            naming::gid_type raw_prefix;
            get_runtime().get_agas_client().get_console_prefix(raw_prefix);
            BOOST_ASSERT(naming::invalid_gid != raw_prefix);
            prefix_ = naming::id_type(raw_prefix, naming::id_type::unmanaged);
        }

        // Someone else started getting the console prefix.
        else
            return;
    }
    messages_type msgs;
    
    {
        queue_mutex_type::scoped_lock l(queue_mtx_);
        queue_.swap(msgs);
    }

    queue_size_.store(0);

    if (!msgs.empty())
        console_logging_locked(prefix_, msgs);
}

void console_logging(logging_destination dest, std::size_t level,
    std::string const& s)
{
    util::static_<pending_logs, pending_logs_tag> logs;
    message_type msg(dest, level, s);
    logs.get().add(msg);
}

void cleanup_logging()
{
    util::static_<pending_logs, pending_logs_tag> logs;
    logs.get().cleanup();
}

void activate_logging()
{
    util::static_<pending_logs, pending_logs_tag> logs;
    logs.get().activate();
}

}}

