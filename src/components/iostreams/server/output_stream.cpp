////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <hpx/config.hpp>

#include <boost/ref.hpp>
#include <boost/bind.hpp>

#include <hpx/runtime.hpp>
#include <hpx/runtime/threads/thread_data.hpp>
#include <hpx/runtime/threads/thread_helpers.hpp>
#include <hpx/components/iostreams/server/output_stream.hpp>

#include <hpx/util/io_service_pool.hpp>

#include <iostream>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>

namespace hpx { namespace iostreams {
    void buffer::save(hpx::util::portable_binary_oarchive & ar, unsigned) const
    {
        bool valid = (data_ && !data_->empty());
        ar & valid;
        if(valid)
        {
            ar & data_;
        }
    }

    void buffer::load(hpx::util::portable_binary_iarchive& ar, unsigned)
    {
        bool valid = false;
        ar & valid;
        if(valid)
        {
            ar & data_;
        }
    }
}}

namespace hpx { namespace iostreams { namespace server
{

///////////////////////////////////////////////////////////////////////////////
void output_stream::call_write_async(
    buffer const& in
) { // {{{
    if(in.data_)
    {
        mutex_type::scoped_lock l(mtx);

    // Perform the IO operation.
        write_f(*(in.data_));
    }
} // }}}

void output_stream::write_async(
    buffer const& in
) { // {{{
    if(!in.data_) return;
    // Perform the IO in another OS thread.
    hpx::get_thread_pool("io_pool")->get_io_service().post(
        boost::bind(&output_stream::call_write_async, this, in));
} // }}}

///////////////////////////////////////////////////////////////////////////////
void output_stream::call_write_sync(
    buffer const& in
  , threads::thread_id_type caller
) {
    if(in.data_)
    {
        mutex_type::scoped_lock l(mtx);

        // Perform the IO operation.
        write_f(*(in.data_));
    }

    // Wake up caller.
    threads::set_thread_state(caller, threads::pending);
}

void output_stream::write_sync(
    buffer const& in
) { // {{{
    if(!in.data_) return;

    // Perform the IO in another OS thread.
    hpx::get_thread_pool("io_pool")->get_io_service().post(
        boost::bind(&output_stream::call_write_sync, this, in, threads::get_self_id()));

    // Sleep until the worker thread wakes us up.
    this_thread::suspend(threads::suspended, "output_stream::write_sync");
} // }}}

}}}

