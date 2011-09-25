////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <hpx/config.hpp>
#include <hpx/hpx.hpp>
#include <hpx/lcos/eager_future.hpp>
#include <hpx/runtime/actions/plain_action.hpp>
#include <hpx/runtime/components/plain_component_factory.hpp>
#include <hpx/runtime/components/server/manage_component.hpp>
#include <hpx/util/static.hpp>
#include <hpx/components/iostreams/lazy_ostream.hpp>
#include <hpx/components/iostreams/standard_streams.hpp>

///////////////////////////////////////////////////////////////////////////////
typedef hpx::actions::plain_action0<hpx::iostreams::create_cout>
    create_cout_action;
typedef hpx::actions::plain_action0<hpx::iostreams::create_cerr>
    create_cerr_action;

HPX_REGISTER_PLAIN_ACTION(create_cout_action);
HPX_REGISTER_PLAIN_ACTION(create_cerr_action);

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace iostreams
{
    ///////////////////////////////////////////////////////////////////////////
    // Tag types to be used for the RAII wrappers below
    struct raii_cout_tag {};
    struct raii_cerr_tag {};

    namespace detail
    {
        std::ostream& get_outstream(raii_cout_tag)
        {
            return std::cout;
        }

        std::ostream& get_outstream(raii_cerr_tag)
        {
            return std::cerr;
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    // This is a RAII wrapper managing the output stream objects (or their
    // references) for a particular locality
    template <typename Tag>
    struct stream_raii
    {
        typedef components::managed_component<server::output_stream> ostream_type;

        stream_raii(char const* cout_name)
        {
            naming::resolver_client& agas_client = get_runtime().get_agas_client();
            if (agas_client.is_console())
            {
                naming::id_type cout_id(
                    components::server::create_one<ostream_type>(
                        boost::ref(detail::get_outstream(Tag()))),
                    naming::id_type::managed);
                client.reset(new lazy_ostream(cout_id));
                agas_client.registerid (cout_name, client->get_raw_gid()); 
            }

            else
            {
                naming::gid_type gid;
                if (!agas_client.queryid(cout_name, gid))
                {
                    naming::gid_type console;
                    error_code ec;
                    agas_client.get_console_prefix_cached(console, ec);
                    if (HPX_UNLIKELY(ec || !console))
                    {
                        HPX_THROW_EXCEPTION(no_registered_console,
                            "stream_raii::stream_raii", "couldn't contact console");
                    }

                    lcos::eager_future<create_cout_action>(console).get();

                    bool r = agas_client.queryid(cout_name, gid, ec);
                    if (HPX_UNLIKELY(ec || !r || !gid))
                    {
                        HPX_THROW_EXCEPTION(service_unavailable,
                            "stream_raii::stream_raii",
                            "couldn't create cout stream on the console locality");
                    } 
                }

                client.reset(new lazy_ostream(
                    naming::id_type(gid, naming::id_type::managed))); 
            }
        }

        boost::shared_ptr<lazy_ostream> client;
    };

    // return the singleton stream objects
    lazy_ostream& cout()
    {
        util::static_<stream_raii<raii_cout_tag>, raii_cout_tag> cout_(
            "/locality(console)/output_stream(cout)");
        return *cout_.get().client;  
    }

    lazy_ostream& cerr()
    {
        util::static_<stream_raii<raii_cerr_tag>, raii_cerr_tag> cerr_(
            "/locality(console)/output_stream(cerr)");
        return *cerr_.get().client;  
    }

    // force the creation of the singleton stream objects
    void create_cout()
    { 
        cout(); 
    }

    void create_cerr()
    { 
        cerr(); 
    }
}}

///////////////////////////////////////////////////////////////////////////////
namespace hpx
{
    cout_wrapper cout = {};
    cerr_wrapper cerr = {};
}

