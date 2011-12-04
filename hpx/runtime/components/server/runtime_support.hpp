//  Copyright (c) 2007-2011 Hartmut Kaiser
//  Copyright (c)      2011 Bryce Lelbach
//  Copyright (c)      2011 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_RUNTIME_SUPPORT_JUN_02_2008_1145AM)
#define HPX_RUNTIME_SUPPORT_JUN_02_2008_1145AM

#include <map>
#include <list>

#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/plugin.hpp>

#include <hpx/hpx_fwd.hpp>
#include <hpx/runtime/agas/gva.hpp>
#include <hpx/runtime/components/component_type.hpp>
#include <hpx/runtime/components/component_factory_base.hpp>
#include <hpx/runtime/components/constructor_argument.hpp>
#include <hpx/runtime/actions/component_action.hpp>
#include <hpx/runtime/actions/manage_object_action.hpp>
#include <hpx/util/spinlock.hpp>

#include <hpx/config/warnings_prefix.hpp>

namespace hpx { namespace components { namespace server
{
#define HPX_RUNTIME_SUPPORT_CREATE_ONE_M0(Z, N, D)                            \
        BOOST_PP_CAT(a, N)(boost::cref(BOOST_PP_CAT(_a, N)))                  \
    /**/
#define HPX_RUNTIME_SUPPORT_CREATE_ONE_M1(Z, N, D)                            \
        boost::reference_wrapper<BOOST_PP_CAT(A, N) const> BOOST_PP_CAT(a, N);\
    /**/
#define HPX_RUNTIME_SUPPORT_CREATE_ONE_M2(Z, N, D)                            \
        BOOST_PP_CAT(a, N).get()                                              \
    /**/
#define HPX_RUNTIME_SUPPORT_CREATE_ONE_COMPONENT(Z, N, D)                     \
        template <typename Component, BOOST_PP_ENUM_PARAMS(N, typename A)>    \
        struct BOOST_PP_CAT(create_one_component_functor, N)                  \
        {                                                                     \
            typedef void result_type;                                         \
            BOOST_PP_CAT(create_one_component_functor, N)(                    \
                      BOOST_PP_ENUM_BINARY_PARAMS(N, A, const & _a))          \
              : BOOST_PP_ENUM(N, HPX_RUNTIME_SUPPORT_CREATE_ONE_M0, _)        \
            {}                                                                \
            result_type operator()(void* p) const                             \
            {                                                                 \
                new (p) Component(BOOST_PP_ENUM(N, HPX_RUNTIME_SUPPORT_CREATE_ONE_M2, _));\
            }                                                                 \
            BOOST_PP_REPEAT(N, HPX_RUNTIME_SUPPORT_CREATE_ONE_M1, _)          \
        };                                                                    \
        template <typename Component, BOOST_PP_ENUM_PARAMS(N, typename A)>    \
        naming::gid_type create_one_functor(                                  \
            component_factory_base* factory,                                  \
            BOOST_PP_ENUM_BINARY_PARAMS(N, A, const& a))                      \
        {                                                                     \
            return factory->create_one_functor(                               \
                BOOST_PP_CAT(create_one_component_functor, N)<                \
                    Component, BOOST_PP_ENUM_PARAMS(N, A)>(                   \
                        BOOST_PP_ENUM_PARAMS(N, a))                           \
            );                                                                \
        }                                                                     \
    /**/
    BOOST_PP_REPEAT_FROM_TO(
        1
      , HPX_ACTION_ARGUMENT_LIMIT
      , HPX_RUNTIME_SUPPORT_CREATE_ONE_COMPONENT
      , _
    )
#undef HPX_RUNTIME_SUPPORT_CREATE_ONE_COMPONENT
#undef HPX_RUNTIME_SUPPORT_CREATE_ONE_M0
#undef HPX_RUNTIME_SUPPORT_CREATE_ONE_M1
#undef HPX_RUNTIME_SUPPORT_CREATE_ONE_M2

    ///////////////////////////////////////////////////////////////////////////
    class runtime_support
    {
    private:
        typedef boost::mutex mutex_type;
        struct component_factory
        {
            component_factory() : isenabled(false) {}

            component_factory(
                  boost::shared_ptr<component_factory_base> const& f,
                  boost::plugin::dll const& d, bool enabled)
              : first(f), second(d), isenabled(enabled)
            {};

            boost::shared_ptr<component_factory_base> first;
            boost::plugin::dll second;
            bool isenabled;
        };
        typedef component_factory component_factory_type;
        typedef std::map<component_type, component_factory_type> component_map_type;

    public:
        typedef runtime_support type_holder;

        // parcel action code: the action to be performed on the destination
        // object
        enum actions
        {
            runtime_support_factory_properties = 0, ///< return whether more than
                                                    ///< one instance of a component
                                                    ///< can be created at once
            runtime_support_create_component = 1,   ///< create new components
            runtime_support_create_one_component = 2,   ///< create new component with one constructor argument
            runtime_support_free_component = 3,     ///< delete existing components
            runtime_support_shutdown = 4,           ///< shut down this runtime instance
            runtime_support_shutdown_all = 5,       ///< shut down the runtime instances of all localities
            runtime_support_terminate = 6,          ///< terminate the runtime instances of all localities
            runtime_support_terminate_all = 7,      ///< terminate the runtime instances of all localities

            runtime_support_get_config = 8,         ///< get configuration information
            runtime_support_create_memory_block = 9,  ///< create new memory block
            runtime_support_load_components = 10,
            runtime_support_call_startup_functions = 11,
            runtime_support_call_shutdown_functions = 12,
            runtime_support_update_agas_cache = 13,
        };

        static component_type get_component_type()
        {
            return components::get_component_type<runtime_support>();
        }
        static void set_component_type(component_type t)
        {
            components::set_component_type<runtime_support>(t);
        }

        // constructor
        runtime_support(util::section& ini, naming::gid_type const& prefix,
                naming::resolver_client& agas_client, applier::applier& applier);

        ~runtime_support()
        {
            tidy();
        }

        /// \brief finalize() will be called just before the instance gets
        ///        destructed
        ///
        /// \param self [in] The PX \a thread used to execute this function.
        /// \param appl [in] The applier to be used for finalization of the
        ///             component instance.
        void finalize() {}

        void tidy();

        ///////////////////////////////////////////////////////////////////////
        // exposed functionality of this component

        /// \brief Action to figure out, whether we can create more than one
        ///        instance at once
        int factory_properties(components::component_type type);

        /// \brief Action to create new components
        naming::gid_type create_component(components::component_type type,
            std::size_t count);

        /// \brief Action to create new component while passing one constructor
        ///        parameter
        naming::gid_type create_one_component(components::component_type type,
            constructor_argument const& arg0);

#define HPX_RUNTIME_SUPPORT_CREATE_ONE_COMPONENT_(Z, N, D)                      \
        template <typename Component, BOOST_PP_ENUM_PARAMS(N, typename A)>      \
        naming::gid_type create_one_component_(components::component_type type, \
            BOOST_PP_ENUM_BINARY_PARAMS(N, A, const & a))                       \
        {                                                                       \
            component_map_type::const_iterator it = components_.find(type);     \
            if (it == components_.end()) {                                      \
                hpx::util::osstream strm;                                       \
                strm << "attempt to create component instance of "              \
                     << "invalid/unknown type: "                                \
                     << components::get_component_type_name(type)               \
                     << " (component not found in map)";                        \
                HPX_THROW_EXCEPTION(hpx::bad_component_type,                    \
                    "runtime_support::create_component",                        \
                    hpx::util::osstream_get_string(strm));                      \
                return naming::invalid_gid;                                     \
            }                                                                   \
            if (!(*it).second.first) {                                          \
                hpx::util::osstream strm;                                       \
                strm << "attempt to create component instance of "              \
                     << "invalid/unknown type: "                                \
                     << components::get_component_type_name(type)               \
                     << " (map entry is NULL)";                                 \
                HPX_THROW_EXCEPTION(hpx::bad_component_type,                    \
                    "runtime_support::create_component",                        \
                    hpx::util::osstream_get_string(strm));                      \
                return naming::invalid_gid;                                     \
            }                                                                   \
                                                                                \
            naming::gid_type id = server::create_one_functor<Component>(        \
                (*it).second.first.get(), BOOST_PP_ENUM_PARAMS(N, a));          \
            LRT_(info) << "successfully created component " << id               \
                       << " of type: "                                          \
                       << components::get_component_type_name(type);            \
                                                                                \
            return id;                                                          \
        }                                                                       \
    /**/
        BOOST_PP_REPEAT_FROM_TO(
            1
          , HPX_ACTION_ARGUMENT_LIMIT
          , HPX_RUNTIME_SUPPORT_CREATE_ONE_COMPONENT_
          , _
        )
#undef HPX_RUNTIME_SUPPORT_CREATE_ONE_COMPONENT_

        /// \brief Action to create new memory block
        naming::gid_type create_memory_block(std::size_t count,
            hpx::actions::manage_object_action_base const& act);

        /// \brief Action to delete existing components
        ///
        /// \param count [in] This GID is a count of the number of components
        ///                   to destroy. It does not represent a global address.
        void free_component(components::component_type type,
            naming::gid_type const& gid, naming::gid_type const& count);

        /// \brief Gracefully shutdown this runtime system instance
        void shutdown(double timeout,
            naming::id_type const& respond_to = naming::invalid_id);

        /// \brief Gracefully shutdown runtime system instances on all localities
        void shutdown_all(double timeout);

        /// \brief Shutdown this runtime system instance
        void terminate(naming::id_type const& respond_to = naming::invalid_id);

        /// \brief Shutdown runtime system instances on all localities
        void terminate_all();

        /// \brief Retrieve configuration information
        util::section get_config();

        void update_agas_cache(naming::gid_type const&, agas::gva const&);

        void load_components();

        void call_startup_functions();
        void call_shutdown_functions(bool pre_shutdown);

        ///////////////////////////////////////////////////////////////////////
        // Each of the exposed functions needs to be encapsulated into a action
        // type, allowing to generate all require boilerplate code for threads,
        // serialization, etc.
        typedef hpx::actions::result_action1<
            runtime_support, int,
            runtime_support_factory_properties, components::component_type,
            &runtime_support::factory_properties
        > factory_properties_action;

        typedef hpx::actions::result_action2<
            runtime_support, naming::gid_type, runtime_support_create_component,
            components::component_type, std::size_t,
            &runtime_support::create_component
        > create_component_action;

        typedef hpx::actions::result_action2<
            runtime_support, naming::gid_type,
            runtime_support_create_one_component,
            components::component_type, constructor_argument const&,
            &runtime_support::create_one_component
        > create_one_component_action;

        typedef hpx::actions::result_action2<
            runtime_support, naming::gid_type, runtime_support_create_memory_block,
            std::size_t, hpx::actions::manage_object_action_base const&,
            &runtime_support::create_memory_block
        > create_memory_block_action;

        typedef hpx::actions::direct_action0<
            runtime_support, runtime_support_load_components,
            &runtime_support::load_components
        > load_components_action;

        typedef hpx::actions::action0<
            runtime_support, runtime_support_call_startup_functions,
            &runtime_support::call_startup_functions
        > call_startup_functions_action;

        typedef hpx::actions::action1<
            runtime_support, runtime_support_call_shutdown_functions, bool,
            &runtime_support::call_shutdown_functions
        > call_shutdown_functions_action;

        typedef hpx::actions::action3<
            runtime_support, runtime_support_free_component,
            components::component_type, naming::gid_type const&, naming::gid_type const&,
            &runtime_support::free_component
        > free_component_action;

        typedef hpx::actions::action2<
            runtime_support, runtime_support_shutdown, double, naming::id_type const&,
            &runtime_support::shutdown
        > shutdown_action;

        typedef hpx::actions::action1<
            runtime_support, runtime_support_shutdown_all, double,
            &runtime_support::shutdown_all
        > shutdown_all_action;

        typedef hpx::actions::action1<
            runtime_support, runtime_support_terminate, naming::id_type const&,
            &runtime_support::terminate
        > terminate_action;

        typedef hpx::actions::action0<
            runtime_support, runtime_support_terminate_all,
            &runtime_support::terminate_all
        > terminate_all_action;

        // even if this is not a short/minimal action, we still execute it
        // directly to avoid a deadlock condition inside the thread manager
        // waiting for this thread to finish, which waits for the thread
        // manager to exit
        typedef hpx::actions::direct_result_action0<
            runtime_support, util::section, runtime_support_get_config,
            &runtime_support::get_config
        > get_config_action;

        typedef hpx::actions::action2<
            runtime_support, runtime_support_update_agas_cache,
            naming::gid_type const&, agas::gva const&,
            &runtime_support::update_agas_cache
        > update_agas_cache_action;

        /// \brief Start the runtime_support component
        void run();

        /// \brief Wait for the runtime_support component to notify the calling
        ///        thread.
        ///
        /// This function will be called from the main thread, causing it to
        /// block while the HPX functionality is executed. The main thread will
        /// block until the shutdown_action is executed, which in turn notifies
        /// all waiting threads.
        void wait();

        /// \brief Notify all waiting (blocking) threads allowing the system to
        ///        be properly stopped.
        ///
        /// \note      This function can be called from any thread.
        void stop(double timeout, naming::id_type const& respond_to);

        /// called locally only
        void stopped();

        bool was_stopped() const { return stopped_; }

        void add_startup_function(HPX_STD_FUNCTION<void()> const& f)
        {
            util::spinlock::scoped_lock l(globals_mtx_);
            startup_functions_.push_back(f);
        }

        void add_pre_shutdown_function(HPX_STD_FUNCTION<void()> const& f)
        {
            util::spinlock::scoped_lock l(globals_mtx_);
            pre_shutdown_functions_.push_back(f);
        }

        void add_shutdown_function(HPX_STD_FUNCTION<void()> const& f)
        {
            util::spinlock::scoped_lock l(globals_mtx_);
            shutdown_functions_.push_back(f);
        }

    protected:
        // Load all components from the ini files found in the configuration
        void load_components(util::section& ini, naming::gid_type const& prefix,
            naming::resolver_client& agas_client);
        bool load_component(util::section& ini, std::string const& instance,
            std::string const& component, boost::filesystem::path lib,
            naming::gid_type const& prefix, naming::resolver_client& agas_client,
            bool isdefault, bool isenabled);

        bool load_startup_shutdown_functions(boost::plugin::dll& d);

    private:
        mutex_type mtx_;
        boost::condition wait_condition_;
        boost::condition stop_condition_;
        bool stopped_;
        bool terminated_;

        component_map_type components_;
        util::section& ini_;

        util::spinlock globals_mtx_;
        std::list<HPX_STD_FUNCTION<void()> > startup_functions_;
        std::list<HPX_STD_FUNCTION<void()> > pre_shutdown_functions_;
        std::list<HPX_STD_FUNCTION<void()> > shutdown_functions_;
    };

#define HPX_RUNTIME_SUPPORT_CREATE_ONE_COMPONENT_ACTION(Z, N, D)              \
    template <typename Component, BOOST_PP_ENUM_PARAMS(N, typename A)>        \
    struct BOOST_PP_CAT(create_one_component_action, N)                       \
    {                                                                         \
        typedef                                                               \
            BOOST_PP_CAT( ::hpx::actions::result_action, BOOST_PP_INC(N))<    \
                runtime_support                                               \
              , naming::gid_type                                              \
              , runtime_support::runtime_support_create_one_component         \
              , components::component_type                                    \
              , BOOST_PP_ENUM_BINARY_PARAMS(N, A, const & BOOST_PP_INTERCEPT) \
              , &runtime_support::create_one_component_<                      \
                    Component                                                 \
                  , BOOST_PP_ENUM_PARAMS(N, A)                                \
                >                                                             \
            >                                                                 \
            type;                                                             \
    };                                                                        \
    /**/
    BOOST_PP_REPEAT_FROM_TO(
        1
      , BOOST_PP_DEC(HPX_ACTION_ARGUMENT_LIMIT)
      , HPX_RUNTIME_SUPPORT_CREATE_ONE_COMPONENT_ACTION
      , _
    )
#undef HPX_RUNTIME_SUPPORT_CREATE_ONE_COMPONENT_ACTION

}}}

///////////////////////////////////////////////////////////////////////////////
// Declaration of serialization support for the runtime_support actions
HPX_REGISTER_ACTION_DECLARATION_EX(
    hpx::components::server::runtime_support::factory_properties_action,
    factory_properties_action);
HPX_REGISTER_ACTION_DECLARATION_EX(
    hpx::components::server::runtime_support::create_component_action,
    create_component_action);
HPX_REGISTER_ACTION_DECLARATION_EX(
    hpx::components::server::runtime_support::create_one_component_action,
    create_one_component_action);
HPX_REGISTER_ACTION_DECLARATION_EX(
    hpx::components::server::runtime_support::create_memory_block_action,
    create_memory_block_action);
HPX_REGISTER_ACTION_DECLARATION_EX(
    hpx::components::server::runtime_support::load_components_action,
    load_components_action);
HPX_REGISTER_ACTION_DECLARATION_EX(
    hpx::components::server::runtime_support::call_startup_functions_action,
    call_startup_functions_action);
HPX_REGISTER_ACTION_DECLARATION_EX(
    hpx::components::server::runtime_support::call_shutdown_functions_action,
    call_shutdown_functions_action);
HPX_REGISTER_ACTION_DECLARATION_EX(
    hpx::components::server::runtime_support::free_component_action,
    free_component_action);
HPX_REGISTER_ACTION_DECLARATION_EX(
    hpx::components::server::runtime_support::shutdown_action,
    shutdown_action);
HPX_REGISTER_ACTION_DECLARATION_EX(
    hpx::components::server::runtime_support::shutdown_all_action,
    shutdown_all_action);
HPX_REGISTER_ACTION_DECLARATION_EX(
    hpx::components::server::runtime_support::terminate_action,
    terminate_action);
HPX_REGISTER_ACTION_DECLARATION_EX(
    hpx::components::server::runtime_support::terminate_all_action,
    terminate_all_action);
HPX_REGISTER_ACTION_DECLARATION_EX(
    hpx::components::server::runtime_support::get_config_action,
    get_config_action);
HPX_REGISTER_ACTION_DECLARATION_EX(
    hpx::components::server::runtime_support::update_agas_cache_action,
    update_agas_cache_action);

#include <hpx/config/warnings_suffix.hpp>

#endif
