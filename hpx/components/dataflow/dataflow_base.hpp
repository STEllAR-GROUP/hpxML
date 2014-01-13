//  Copyright (c) 2011-2012 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef HPX_LCOS_FUTURE_DATAFLOW_BASE_HPP
#define HPX_LCOS_FUTURE_DATAFLOW_BASE_HPP

#include <hpx/components/dataflow/dataflow_base_fwd.hpp>
#include <hpx/components/dataflow/dataflow_base_void.hpp>
#include <hpx/components/dataflow/dataflow_base_impl.hpp>
#include <hpx/components/dataflow/dataflow_fwd.hpp>
#include <hpx/components/dataflow/stubs/dataflow.hpp>
#include <boost/intrusive_ptr.hpp>

namespace hpx { namespace lcos
{
    template <typename Result, typename RemoteResult>
    struct dataflow_base
    {
        typedef RemoteResult remote_result_type;
        typedef Result       result_type;

        dataflow_base()
        {}

        explicit dataflow_base(lcos::unique_future<naming::id_type> promise)
            : impl(new detail::dataflow_base_impl(std::move(promise)))
        {}

        void connect(naming::id_type const & id) const
        {
            impl->connect(id);
        }

        unique_future<Result> get_future() const
        {
            promise<Result, remote_result_type> p;
            impl->connect(p.get_gid());
            return p.get_future();
        }

        bool valid()
        {
            return impl && impl->get_gid();
        }

    private:
        friend class boost::serialization::access;

        boost::intrusive_ptr<detail::dataflow_base_impl> impl;

        template <typename Archive>
        void serialize(Archive & ar, unsigned)
        {
            ar & impl;
        }
    };
}}

#endif
