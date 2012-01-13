//  Copyright (c) 2011 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef EXAMPLES_BRIGHT_FUTURE_DATAFLOW_BASE_HPP
#define EXAMPLES_BRIGHT_FUTURE_DATAFLOW_BASE_HPP

#include <hpx/components/dataflow/dataflow_base_fwd.hpp>
#include <hpx/components/dataflow/dataflow_base_void.hpp>
#include <hpx/components/dataflow/dataflow_base_impl.hpp>
#include <hpx/components/dataflow/dataflow_fwd.hpp>
#include <hpx/components/dataflow/stubs/dataflow.hpp>

namespace hpx { namespace lcos 
{
    template <typename Result, typename RemoteResult>
    struct dataflow_base
    {
        typedef RemoteResult remote_result_type;
        typedef Result       result_type;
        typedef
            components::client_base<
                dataflow_base<Result, RemoteResult>
              , stubs::dataflow
            >
            base_type;

        typedef stubs::dataflow stub_type;

        dataflow_base()
        {}

        virtual ~dataflow_base()
        {
        }

        dataflow_base(promise<naming::id_type, naming::gid_type> const & promise)
            : impl(new detail::dataflow_base_impl(promise))
        {}

#define HPX_LCOS_DATAFLOW_M0(Z, N, D)                                           \
        template <BOOST_PP_ENUM_PARAMS(N, typename A)>                          \
        dataflow_base(                                                          \
            promise<naming::id_type, naming::gid_type> const & promise          \
          , BOOST_PP_ENUM_BINARY_PARAMS(N, A, const & a)                        \
        )                                                                       \
            : impl(                                                             \
                new detail::dataflow_base_impl(                                 \
                    promise                                                     \
                  , BOOST_PP_ENUM_PARAMS(N, a)                                  \
                )                                                               \
            )                                                                   \
        {                                                                       \
        }                                                                       \
    /**/
        BOOST_PP_REPEAT_FROM_TO(
            1
          , BOOST_PP_SUB(HPX_ACTION_ARGUMENT_LIMIT, 3)
          , HPX_LCOS_DATAFLOW_M0
          , _
        )

#undef HPX_LCOS_DATAFLOW_M0
        
        promise<Result, remote_result_type> get_promise() const
        {
            promise<Result, remote_result_type> p;
            connect(p.get_gid());
            return p;
        }

        Result get() const
        {
            promise<Result, remote_result_type> p;
            connect(p.get_gid());
            return p.get();
        }

        void invalidate()
        {
            impl->invalidate();
        }

        naming::id_type get_gid() const
        {
            return impl->get_gid();
        }

        void connect(naming::id_type const & target) const
        {
            stub_type::connect(impl->get_gid(), target);
        }

        boost::shared_ptr<detail::dataflow_base_impl> impl;

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
