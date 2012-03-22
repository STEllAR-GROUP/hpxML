//  Copyright (c) 2011 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef HPX_LCOS_DATAFLOW_BASE_VOID_HPP
#define HPX_LCOS_DATAFLOW_BASE_VOID_HPP

#include <hpx/components/dataflow/dataflow_base_fwd.hpp>
#include <hpx/components/dataflow/dataflow_base_impl.hpp>
#include <hpx/components/dataflow/stubs/dataflow.hpp>

namespace hpx { namespace lcos
{
    template <>
    struct dataflow_base<void>
    {
        typedef traits::promise_remote_result<void>::type remote_result_type;
        typedef void result_type;
        typedef
            components::client_base<
                dataflow_base<void>
              , stubs::dataflow
            >
            base_type;

        typedef stubs::dataflow stub_type;

        /*
        dataflow_base(dataflow_base &&) = delete;
        dataflow_base& operator=(dataflow_base &&) = delete;
        */
        
        dataflow_base(dataflow_base const &o)
            : impl(o.impl)
        {}

        dataflow_base& operator=(dataflow_base const& o)
        {
            impl = o.impl;
            return *this;
        }


        dataflow_base()
        {}

        virtual ~dataflow_base()
        {}

        dataflow_base(future<naming::id_type> const & promise)
            //: impl(new detail::dataflow_base_impl(promise))
            : impl(promise)
        {}

        future<void> get_future() const
        {
            promise<void> p;
            connect(p.get_gid());
            return p.get_future();
        }

//         void get() const
//         {
//             get_future().get();
//         }

        void invalidate()
        {
            impl.invalidate();
        }

        naming::id_type get_gid() const
        {
            return impl.get_gid();
        }

        void connect(naming::id_type const & target) const
        {
            BOOST_ASSERT(impl.get_gid());
            stub_type::connect(impl.get_gid(), target);
        }

        detail::dataflow_base_impl impl;

    private:
        friend class boost::serialization::access;

        template <typename Archive>
        void serialize(Archive & ar, unsigned)
        {
            ar & impl;
        }
    };
}}

#endif
