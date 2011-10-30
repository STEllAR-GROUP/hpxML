//  Copyright (c) 2007-2011 Hartmut Kaiser
//  Copyright (c) 2011      Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_RUNTIME_ACTIONS_COMPONENT_ACTION_MAR_26_2008_1054AM)
#define HPX_RUNTIME_ACTIONS_COMPONENT_ACTION_MAR_26_2008_1054AM

#include <cstdlib>
#include <stdexcept>

#include <hpx/hpx_fwd.hpp>
#include <hpx/config.hpp>
#include <hpx/config/bind.hpp>
#include <hpx/exception.hpp>
#include <hpx/runtime/naming/address.hpp>
#include <hpx/runtime/actions/continuation.hpp>
#include <hpx/runtime/actions/action_support.hpp>
#include <hpx/runtime/components/console_error_sink.hpp>
#include <hpx/util/unused.hpp>

#include <boost/version.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/ref.hpp>
#include <boost/preprocessor/stringize.hpp>

#include <hpx/config/warnings_prefix.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace actions
{
    ///////////////////////////////////////////////////////////////////////////
    //  Specialized generic component action types allowing to hold a different
    //  number of arguments
    ///////////////////////////////////////////////////////////////////////////

    // zero argument version
    template <
        typename Component, typename Result, int Action,
        Result (Component::*F)(), typename Derived,
        threads::thread_priority Priority = threads::thread_priority_default>
    class base_result_action0
      : public action<Component, Action, Result, boost::fusion::vector<>,
                      Derived, Priority>
    {
    public:
        typedef Result result_type;
        typedef boost::fusion::vector<> arguments_type;
        typedef action<Component, Action, result_type, arguments_type,
                       Derived, Priority>
            base_type;

        explicit base_result_action0(threads::thread_priority priority = Priority)
          : base_type(priority)
        {}

    protected:
        /// The \a continuation_thread_function will be registered as the thread
        /// function of a thread. It encapsulates the execution of the
        /// original function (given by \a func), while ignoring the return
        /// value.
        template <typename Address>   // dummy template parameter
        static threads::thread_state_enum
        thread_function(Address lva)
        {
            try {
                LTM_(debug) << "Executing component action("
                            << detail::get_action_name<Derived>()
                            << ") lva(" << reinterpret_cast<void const*>
                                (get_lva<Component>::call(lva)) << ")";
                (get_lva<Component>::call(lva)->*F)();      // just call the function
            }
            catch (hpx::exception const& e) {
                LTM_(error)
                    << "Unhandled exception while executing component action("
                    << detail::get_action_name<Derived>()
                    << ") lva(" << reinterpret_cast<void const*>
                        (get_lva<Component>::call(lva)) << "): " << e.what();

                // report this error to the console in any case
                hpx::report_error(boost::current_exception());
            }
            return threads::terminated;
        }

    public:
        typedef boost::mpl::false_ direct_execution;

        /// \brief This static \a construct_thread_function allows to construct
        /// a proper thread function for a \a thread without having to
        /// instantiate the \a base_result_action0 type. This is used by the \a
        /// applier in case no continuation has been supplied.
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva)
        {
            threads::thread_state_enum (*f)(naming::address::address_type) =
                &Derived::template thread_function<naming::address::address_type>;

            return HPX_STD_BIND(f, lva);
        }

        /// \brief This static \a construct_thread_function allows to construct
        /// a proper thread function for a \a thread without having to
        /// instantiate the \a base_result_action0 type. This is used by the \a
        /// applier in case a continuation has been supplied
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva)
        {
            return base_type::construct_continuation_thread_function(
                HPX_STD_BIND(F, get_lva<Component>::call(lva)), cont);
        }

        /// serialization support
        static void register_base()
        {
            using namespace boost::serialization;
            void_cast_register<base_result_action0, base_type>();
            base_type::register_base();
        }

    private:
        /// This \a get_thread_function will be invoked to retrieve the thread
        /// function for an action which has to be invoked without continuations.
        HPX_STD_FUNCTION<threads::thread_function_type>
        get_thread_function(naming::address::address_type lva) const
        {
            return construct_thread_function(lva);
        }

        /// This \a get_thread_function will be invoked to retrieve the thread
        /// function for an action which has to be invoked with continuations.
        HPX_STD_FUNCTION<threads::thread_function_type>
        get_thread_function(continuation_type& cont,
            naming::address::address_type lva) const
        {
            return construct_thread_function(cont, lva);
        }

        HPX_STD_FUNCTION<threads::thread_function_type>
        get_thread_function(naming::address::address_type lva,
            arguments_type const&) const
        {
            return construct_thread_function(lva);
        }

        HPX_STD_FUNCTION<threads::thread_function_type>
        get_thread_function(continuation_type& cont,
            naming::address::address_type lva, arguments_type const&) const
        {
            return construct_thread_function(cont, lva);
        }

    private:
        // serialization support
        friend class boost::serialization::access;

        template<class Archive>
        void serialize(Archive& ar, const unsigned int /*version*/)
        {
            ar & boost::serialization::base_object<base_type>(*this);
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    template <
        typename Component, typename Result, int Action,
        Result (Component::*F)(),
        threads::thread_priority Priority = threads::thread_priority_default,
        typename Derived = detail::this_type>
    class result_action0
      : public base_result_action0<Component, Result, Action, F,
            typename detail::action_type<
                result_action0<Component, Result, Action, F, Priority>,
                Derived
            >::type, Priority>
    {
    private:
        typedef typename detail::action_type<
            result_action0<Component, Result, Action, F, Priority>, Derived
        >::type derived_type;

        typedef base_result_action0<
            Component, Result, Action, F, derived_type, Priority>
        base_type;

    public:
        explicit result_action0(threads::thread_priority priority = Priority)
          : base_type(priority)
        {}

        Result execute_function(naming::address::address_type lva) const
        {
            LTM_(debug) << "result_action0::execute_function: name("
                        << detail::get_action_name<derived_type>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
            return (get_lva<Component>::call(lva)->*F)();
        }

        static Result execute_function_nonvirt(naming::address::address_type lva)
        {
            LTM_(debug) << "result_action0::execute_function_nonvirt: name("
                        << detail::get_action_name<derived_type>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
            return (get_lva<Component>::call(lva)->*F)();
        }

        /// serialization support
        static void register_base()
        {
            using namespace boost::serialization;
            void_cast_register<result_action0, base_type>();
            base_type::register_base();
        }

    private:
        // serialization support
        friend class boost::serialization::access;

        template<class Archive>
        void serialize(Archive& ar, const unsigned int /*version*/)
        {
            ar & boost::serialization::base_object<base_type>(*this);
        }

    private:
        threads::thread_init_data&
        get_thread_init_data(naming::address::address_type lva,
            threads::thread_init_data& data)
        {
            data.lva = lva;
            data.func = this->construct_thread_function(lva);
            data.description = detail::get_action_name<derived_type>();
            data.parent_id =
                reinterpret_cast<threads::thread_id_type>(this->parent_id_);
            data.parent_prefix = this->parent_locality_;
            data.priority = this->priority_;
            return data;
        }

        threads::thread_init_data&
        get_thread_init_data(continuation_type& cont,
            naming::address::address_type lva,
            threads::thread_init_data& data)
        {
            data.lva = lva;
            data.func = this->construct_thread_function(cont, lva);
            data.description = detail::get_action_name<derived_type>();
            data.parent_id =
                reinterpret_cast<threads::thread_id_type>(this->parent_id_);
            data.parent_prefix = this->parent_locality_;
            data.priority = this->priority_;
            return data;
        }

        threads::thread_init_data&
        get_thread_init_data(naming::address::address_type lva,
            threads::thread_init_data& data,
            typename base_type::arguments_type const&)
        {
            return this->get_thread_init_data(lva, data);
        }

        threads::thread_init_data&
        get_thread_init_data(continuation_type& cont,
            naming::address::address_type lva,
            threads::thread_init_data& data,
            typename base_type::arguments_type const&)
        {
            return this->get_thread_init_data(cont, lva, data);
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    template <
        typename Component, typename Result, int Action,
        Result (Component::*F)(), typename Derived = detail::this_type>
    class direct_result_action0
      : public base_result_action0<Component, Result, Action, F,
            typename detail::action_type<
                direct_result_action0<Component, Result, Action, F>, Derived
            >::type>
    {
    private:
        typedef typename detail::action_type<
            direct_result_action0<Component, Result, Action, F>, Derived
        >::type derived_type;

        typedef base_result_action0<
            Component, Result, Action, F, derived_type>
        base_type;

    public:
        direct_result_action0()
        {}

        explicit direct_result_action0(threads::thread_priority)
        {}

    public:
        typedef boost::mpl::true_ direct_execution;

        Result execute_function(naming::address::address_type lva) const
        {
            LTM_(debug) << "direct_result_action0::execute_function: name("
                        << detail::get_action_name<derived_type>()
                        << ") lva(" << lva << ")";
            return (get_lva<Component>::call(lva)->*F)();
        }

        static Result execute_function_nonvirt(naming::address::address_type lva)
        {
            LTM_(debug) << "direct_result_action0::execute_function_nonvirt: name("
                        << detail::get_action_name<derived_type>()
                        << ") lva(" << lva << ")";
            return (get_lva<Component>::call(lva)->*F)();
        }

        /// serialization support
        static void register_base()
        {
            using namespace boost::serialization;
            void_cast_register<direct_result_action0, base_type>();
            base_type::register_base();
        }

    private:
        // serialization support
        friend class boost::serialization::access;

        template<class Archive>
        void serialize(Archive& ar, const unsigned int /*version*/)
        {
            ar & boost::serialization::base_object<base_type>(*this);
        }

    private:
        /// The function \a get_action_type returns whether this action needs
        /// to be executed in a new thread or directly.
        base_action::action_type get_action_type() const
        {
            return base_action::direct_action;
        }

        threads::thread_init_data&
        get_thread_init_data(naming::address::address_type lva,
            threads::thread_init_data& data)
        {
            data.lva = lva;
            data.func = this->construct_thread_function(lva);
            data.description = detail::get_action_name<derived_type>();
            data.parent_id =
                reinterpret_cast<threads::thread_id_type>(this->parent_id_);
            data.parent_prefix = this->parent_locality_;
            data.priority = this->priority_;
            return data;
        }

        threads::thread_init_data&
        get_thread_init_data(continuation_type& cont,
            naming::address::address_type lva,
            threads::thread_init_data& data)
        {
            data.lva = lva;
            data.func = this->construct_thread_function(cont, lva);
            data.description = detail::get_action_name<derived_type>();
            data.parent_id =
                reinterpret_cast<threads::thread_id_type>(this->parent_id_);
            data.parent_prefix = this->parent_locality_;
            data.priority = this->priority_;
            return data;
        }

        threads::thread_init_data&
        get_thread_init_data(naming::address::address_type lva,
            threads::thread_init_data& data,
            typename base_type::arguments_type const&)
        {
            return this->get_thread_init_data(lva, data);
        }

        threads::thread_init_data&
        get_thread_init_data(continuation_type& cont,
            naming::address::address_type lva,
            threads::thread_init_data& data,
            typename base_type::arguments_type const&)
        {
            return this->get_thread_init_data(cont, lva, data);
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    //  zero parameter version, no result value
    template <typename Component, int Action, void (Component::*F)(), typename Derived,
      threads::thread_priority Priority = threads::thread_priority_default>
    class base_action0
      : public action<Component, Action, util::unused_type,
                      boost::fusion::vector<>, Derived, Priority>
    {
    public:
        typedef util::unused_type result_type;
        typedef boost::fusion::vector<> arguments_type;
        typedef action<Component, Action, result_type, arguments_type,
                       Derived, Priority>
            base_type;

        explicit base_action0(threads::thread_priority priority = Priority)
          : base_type(priority)
        {}

    protected:
        /// The \a continuation_thread_function will be registered as the thread
        /// function of a thread. It encapsulates the execution of the
        /// original function (given by \a func), while ignoring the return
        /// value.
        template <typename Address>   // dummy template parameter
        static threads::thread_state_enum
        thread_function(Address lva)
        {
            try {
                LTM_(debug) << "Executing component action("
                            << detail::get_action_name<Derived>()
                            << ") lva(" << reinterpret_cast<void const*>
                                (get_lva<Component>::call(lva)) << ")";
                (get_lva<Component>::call(lva)->*F)();      // just call the function
            }
            catch (hpx::exception const& e) {
                LTM_(error)
                    << "Unhandled exception while executing component action("
                    << detail::get_action_name<Derived>()
                    << ") lva(" << reinterpret_cast<void const*>
                        (get_lva<Component>::call(lva)) << "): " << e.what();

                // report this error to the console in any case
                hpx::report_error(boost::current_exception());
            }
            return threads::terminated;
        }

    public:
        typedef boost::mpl::false_ direct_execution;

        /// \brief This static \a construct_thread_function allows to construct
        /// a proper thread function for a \a thread without having to
        /// instantiate the base_action0 type. This is used by the \a applier in
        /// case no continuation has been supplied.
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva)
        {
            threads::thread_state_enum (*f)(naming::address::address_type) =
                &Derived::template thread_function<naming::address::address_type>;

            return HPX_STD_BIND(f, lva);
        }

        /// \brief This static \a construct_thread_function allows to construct
        /// a proper thread function for a \a thread without having to
        /// instantiate the base_action0 type. This is used by the \a applier in
        /// case a continuation has been supplied
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva)
        {
            return base_type::construct_continuation_thread_function_void(
                HPX_STD_BIND(F, get_lva<Component>::call(lva)), cont);
        }

        /// serialization support
        static void register_base()
        {
            using namespace boost::serialization;
            void_cast_register<base_action0, base_type>();
            base_type::register_base();
        }

    private:
        HPX_STD_FUNCTION<threads::thread_function_type>
        get_thread_function(naming::address::address_type lva) const
        {
            return construct_thread_function(lva);
        }

        HPX_STD_FUNCTION<threads::thread_function_type>
        get_thread_function(continuation_type& cont,
            naming::address::address_type lva) const
        {
            return construct_thread_function(cont, lva);
        }

        HPX_STD_FUNCTION<threads::thread_function_type>
        get_thread_function(naming::address::address_type lva,
            arguments_type const&) const
        {
            return construct_thread_function(lva);
        }

        HPX_STD_FUNCTION<threads::thread_function_type>
        get_thread_function(continuation_type& cont,
            naming::address::address_type lva, arguments_type const&) const
        {
            return construct_thread_function(cont, lva);
        }

    private:
        // serialization support
        friend class boost::serialization::access;

        template<class Archive>
        void serialize(Archive& ar, const unsigned int /*version*/)
        {
            ar & boost::serialization::base_object<base_type>(*this);
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    template <typename Component, int Action, void (Component::*F)(),
        threads::thread_priority Priority = threads::thread_priority_default,
        typename Derived = detail::this_type>
    class action0
      : public base_action0<Component, Action, F,
            typename detail::action_type<
                action0<Component, Action, F, Priority>, Derived
            >::type, Priority>
    {
    private:
        typedef typename detail::action_type<
            action0<Component, Action, F, Priority>, Derived
        >::type derived_type;

        typedef base_action0<Component, Action, F, derived_type, Priority>
            base_type;

    public:
        explicit action0(threads::thread_priority priority = Priority)
          : base_type(priority)
        {}

        util::unused_type
        execute_function(naming::address::address_type lva) const
        {
            LTM_(debug) << "action0::execute_function: name("
                        << detail::get_action_name<derived_type>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
            (get_lva<Component>::call(lva)->*F)();
            return util::unused;
        }

        static util::unused_type
        execute_function_nonvirt(naming::address::address_type lva)
        {
            LTM_(debug) << "action0::execute_function_nonvirt: name("
                        << detail::get_action_name<derived_type>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
            (get_lva<Component>::call(lva)->*F)();
            return util::unused;
        }

        /// serialization support
        static void register_base()
        {
            using namespace boost::serialization;
            void_cast_register<action0, base_type>();
            base_type::register_base();
        }

    private:
        // serialization support
        friend class boost::serialization::access;

        template<class Archive>
        void serialize(Archive& ar, const unsigned int /*version*/)
        {
            ar & boost::serialization::base_object<base_type>(*this);
        }

    private:
        threads::thread_init_data&
        get_thread_init_data(naming::address::address_type lva,
            threads::thread_init_data& data)
        {
            data.lva = lva;
            data.func = this->construct_thread_function(lva);
            data.description = detail::get_action_name<derived_type>();
            data.parent_id =
                reinterpret_cast<threads::thread_id_type>(this->parent_id_);
            data.parent_prefix = this->parent_locality_;
            data.priority = this->priority_;
            return data;
        }

        threads::thread_init_data&
        get_thread_init_data(continuation_type& cont,
            naming::address::address_type lva,
            threads::thread_init_data& data)
        {
            data.lva = lva;
            data.func = this->construct_thread_function(cont, lva);
            data.description = detail::get_action_name<derived_type>();
            data.parent_id =
                reinterpret_cast<threads::thread_id_type>(this->parent_id_);
            data.parent_prefix = this->parent_locality_;
            data.priority = this->priority_;
            return data;
        }

        threads::thread_init_data&
        get_thread_init_data(naming::address::address_type lva,
            threads::thread_init_data& data,
            typename base_type::arguments_type const&)
        {
            return this->get_thread_init_data(lva, data);
        }

        threads::thread_init_data&
        get_thread_init_data(continuation_type& cont,
            naming::address::address_type lva,
            threads::thread_init_data& data,
            typename base_type::arguments_type const&)
        {
            return this->get_thread_init_data(cont, lva, data);
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    template <typename Component, int Action, void (Component::*F)(),
        typename Derived = detail::this_type>
    class direct_action0
      : public base_action0<Component, Action, F,
            typename detail::action_type<
                direct_action0<Component, Action, F>, Derived
            >::type>
    {
    private:
        typedef typename detail::action_type<
            direct_action0<Component, Action, F>, Derived
        >::type derived_type;

        typedef base_action0<Component, Action, F, derived_type> base_type;

    public:
        direct_action0()
        {}

        explicit direct_action0(threads::thread_priority)
        {}

    public:
        typedef boost::mpl::true_ direct_execution;

        util::unused_type
        execute_function(naming::address::address_type lva) const
        {
            LTM_(debug) << "direct_action0::execute_function: name("
                        << detail::get_action_name<derived_type>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
            (get_lva<Component>::call(lva)->*F)();
            return util::unused;
        }

        static util::unused_type
        execute_function_nonvirt(naming::address::address_type lva)
        {
            LTM_(debug) << "direct_action0::execute_function_nonvirt: name("
                        << detail::get_action_name<derived_type>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
            (get_lva<Component>::call(lva)->*F)();
            return util::unused;
        }

        /// serialization support
        static void register_base()
        {
            using namespace boost::serialization;
            void_cast_register<direct_action0, base_type>();
            base_type::register_base();
        }

    private:
        // serialization support
        friend class boost::serialization::access;

        template<class Archive>
        void serialize(Archive& ar, const unsigned int /*version*/)
        {
            ar & boost::serialization::base_object<base_type>(*this);
        }

    private:
        /// The function \a get_action_type returns whether this action needs
        /// to be executed in a new thread or directly.
        base_action::action_type get_action_type() const
        {
            return base_action::direct_action;
        }

        threads::thread_init_data&
        get_thread_init_data(naming::address::address_type lva,
            threads::thread_init_data& data)
        {
            data.lva = lva;
            data.func = this->construct_thread_function(lva);
            data.description = detail::get_action_name<derived_type>();
            data.parent_id =
                reinterpret_cast<threads::thread_id_type>(this->parent_id_);
            data.parent_prefix = this->parent_locality_;
            data.priority = this->priority_;
            return data;
        }

        threads::thread_init_data&
        get_thread_init_data(continuation_type& cont,
            naming::address::address_type lva,
            threads::thread_init_data& data)
        {
            data.lva = lva;
            data.func = this->construct_thread_function(cont, lva);
            data.description = detail::get_action_name<derived_type>();
            data.parent_id =
                reinterpret_cast<threads::thread_id_type>(this->parent_id_);
            data.parent_prefix = this->parent_locality_;
            data.priority = this->priority_;
            return data;
        }

        threads::thread_init_data&
        get_thread_init_data(naming::address::address_type lva,
            threads::thread_init_data& data,
            typename base_type::arguments_type const&)
        {
            return this->get_thread_init_data(lva, data);
        }

        threads::thread_init_data&
        get_thread_init_data(continuation_type& cont,
            naming::address::address_type lva,
            threads::thread_init_data& data,
            typename base_type::arguments_type const&)
        {
            return this->get_thread_init_data(cont, lva, data);
        }
    };

    template <
        typename Component, int Action,
        void (Component::*F)(),
        threads::thread_priority Priority,
        typename Derived>
    class result_action0<Component, void, Action, F, Priority, Derived>
        : public action0<Component, Action, F, Priority, Derived>
    {
        typedef action0<Component, Action, F, Priority, Derived> base_type;

    public:
        explicit result_action0(threads::thread_priority priority = Priority)
          : base_type(priority)
        {}

        /// serialization support
        static void register_base()
        {
            using namespace boost::serialization;
            void_cast_register<result_action0, base_type>();
            base_type::register_base();
        }

    private:
        // serialization support
        friend class boost::serialization::access;

        template<class Archive>
        void serialize(Archive& ar, const unsigned int /*version*/)
        {
            ar & boost::serialization::base_object<base_type>(*this);
        }
    };
}}

///////////////////////////////////////////////////////////////////////////////
// Register the action templates with serialization.
HPX_SERIALIZATION_REGISTER_TEMPLATE(
    (
        template <
            typename Component
          , typename Result
          , int Action
          , Result (Component::*F)()
          , hpx::threads::thread_priority Priority
          , typename Derived
        >
    )
  , (
        hpx::actions::result_action0<Component, Result, Action, F, Priority, Derived>
    )
)

HPX_SERIALIZATION_REGISTER_TEMPLATE(
    (
        template <
            typename Component
          , typename Result
          , int Action
          , Result (Component::*F)()
          , typename Derived
        >
    )
  , (
        hpx::actions::direct_result_action0<Component, Result, Action, F, Derived>
    )
)

HPX_SERIALIZATION_REGISTER_TEMPLATE(
    (
        template <
            typename Component
          , int Action
          , void (Component::*F)()
          , hpx::threads::thread_priority Priority
          , typename Derived
        >
    )
  , (
        hpx::actions::action0<Component, Action, F, Priority, Derived>
    )
)

HPX_SERIALIZATION_REGISTER_TEMPLATE(
    (
        template <
            typename Component
          , int Action
          , void (Component::*F)()
          , typename Derived
        >
    )
  , (
        hpx::actions::direct_action0<Component, Action, F, Derived>
    )
)

/////////////////////////////////////////////////////////////////////////////////
// bring in the rest of the implementations
#include <hpx/runtime/actions/component_action_implementations.hpp>

#include <hpx/config/warnings_suffix.hpp>

#endif

