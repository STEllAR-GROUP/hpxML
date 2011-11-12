
//  Copyright (c) 2011 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef EXAMPLES_BRIGHT_FUTURE_DATAFLOW_BASE_HPP
#define EXAMPLES_BRIGHT_FUTURE_DATAFLOW_BASE_HPP

#include <examples/bright_future/dataflow/dataflow_base_fwd.hpp>
#include <examples/bright_future/dataflow/dataflow_base_void.hpp>
#include <examples/bright_future/dataflow/dataflow_fwd.hpp>
#include <examples/bright_future/dataflow/stubs/dataflow.hpp>

namespace hpx { namespace lcos {
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
            : gid_promise(promise)
        {}

        Result get()
        {
            promise<Result, remote_result_type> p;
            connect(p.get_gid());
            return p.get();
        }

        void invalidate()
        {
            gid_promise.reset();
        }

        void connect(naming::id_type const & target) const
        {
            stub_type::connect(this->get_gid(), target);
        }

        promise<void> connect_async(naming::id_type const & target) const
        {
            return stub_type::connect_async(this->get_gid(), target);
        }

        naming::id_type get_gid() const
        {
            return gid_promise.get();
        }

    protected:
        promise<naming::id_type, naming::gid_type> gid_promise;

    private:
        friend class boost::serialization::access;

        template <typename Archive>
        void load(Archive & ar, unsigned)
        {
            naming::id_type id;
            ar & id;
            gid_promise.set_local_data(0, id);
        }

        template <typename Archive>
        void save(Archive & ar, unsigned) const
        {
            BOOST_ASSERT(this->get_gid());
            naming::id_type id = this->get_gid();
            ar & id;
        }

        BOOST_SERIALIZATION_SPLIT_MEMBER();
    };
}}
#endif
