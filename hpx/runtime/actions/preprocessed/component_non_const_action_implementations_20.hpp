// Copyright (c) 2007-2013 Hartmut Kaiser
// Copyright (c) 2012-2013 Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This file has been automatically generated using the Boost.Wave tool.
// Do not edit manually.


namespace hpx { namespace actions
{
    
    
    template <
        typename Component, typename Result, typename T0,
        Result (Component::*F)(T0), typename Derived>
    class base_result_action1<
            Result (Component::*)(T0), F, Derived>
      : public action<
            Component, Result,
            hpx::util::tuple<typename util::decay<T0>::type>,
            Derived>
    {
    public:
        typedef Result result_type;
        typedef typename detail::remote_action_result<Result>::type
            remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type> arguments_type;
        typedef action<Component, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component>::call(lva)) << ")";
                    (get_lva<Component>::call(lva)->*F)(
                        boost::forward<Arg0>( arg0 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        typedef boost::mpl::false_ direct_execution;
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                util::bind(util::one_shot(typename Derived::thread_function()),
                    lva, util::get< 0>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function(
                    cont, F, get_lva<Component>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static Result
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_result_action" << 1
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component>::call(lva)) << ")";
            return (get_lva<Component>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)));
        }
    };
    
    
    template <
        typename Component, typename Result, typename T0,
        Result (Component::*F)(T0), typename Derived>
    struct result_action1<
            Result (Component::*)(T0), F, Derived>
      : base_result_action1<
            Result (Component::*)(T0), F,
            typename detail::action_type<
                result_action1<
                    Result (Component::*)(T0), F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            result_action1, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename Result, typename T0,
        Result (Component::*F)(T0), typename Derived>
    struct make_action<Result (Component::*)(T0),
            F, Derived, boost::mpl::false_>
      : result_action1<
            Result (Component::*)(T0), F, Derived>
    {
        typedef result_action1<
            Result (Component::*)(T0), F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename Result,
        typename T0,
        Result (Component::*F)(T0),
        typename Derived>
    struct direct_result_action1<
            Result (Component::*)(T0), F, Derived>
      : base_result_action1<
            Result (Component::*)(T0), F,
            typename detail::action_type<
                direct_result_action1<
                    Result (Component::*)(T0), F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_result_action1, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename Result, typename T0,
        Result (Component::*F)(T0), typename Derived>
    struct make_action<Result (Component::*)(T0),
            F, Derived, boost::mpl::true_>
      : direct_result_action1<
            Result (Component::*)(T0), F, Derived>
    {
        typedef direct_result_action1<
            Result (Component::*)(T0), F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename T0,
        void (Component::*F)(T0), typename Derived>
    class base_action1<
            void (Component::*)(T0), F, Derived>
      : public action<
            Component, util::unused_type,
            hpx::util::tuple<typename util::decay<T0>::type>,
            Derived>
    {
    public:
        typedef util::unused_type result_type;
        typedef util::unused_type remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type> arguments_type;
        typedef action<Component, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component>::call(lva)) << ")";
                    (get_lva<Component>::call(lva)->*F)(
                        boost::forward<Arg0>( arg0 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            
            
            return Derived::decorate_action(
                util::bind(util::one_shot(typename Derived::thread_function()), lva,
                    util::get< 0>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function_void(
                    cont, F, get_lva<Component>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static util::unused_type
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_action" << 1
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component>::call(lva)) << ")";
            (get_lva<Component>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)));
            return util::unused;
        }
    };
    
    template <
        typename Component, typename T0,
        void (Component::*F)(T0),
        typename Derived>
    struct action1<
            void (Component::*)(T0), F, Derived>
      : base_action1<
            void (Component::*)(T0), F,
            typename detail::action_type<
                action1<
                    void (Component::*)(T0), F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            action1, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename T0,
        void (Component::*F)(T0), typename Derived>
    struct make_action<void (Component::*)(T0),
            F, Derived, boost::mpl::false_>
      : action1<
            void (Component::*)(T0), F, Derived>
    {
        typedef action1<
            void (Component::*)(T0), F, Derived
        > type;
    };
    
    template <
        typename Component, typename T0,
        void (Component::*F)(T0),
        typename Derived>
    struct direct_action1<
            void (Component::*)(T0), F, Derived>
      : base_action1<
            void (Component::*)(T0), F,
            typename detail::action_type<
                direct_action1<
                    void (Component::*)(T0), F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_action1, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename T0,
        void (Component::*F)(T0), typename Derived>
    struct make_action<void (Component::*)(T0),
            F, Derived, boost::mpl::true_>
      : direct_action1<
            void (Component::*)(T0), F, Derived>
    {
        typedef direct_action1<
            void (Component::*)(T0), F, Derived
        > type;
    };
    
    
    template <
        typename Component,
        typename T0,
        void (Component::*F)(T0),
        typename Derived>
    struct result_action1<
            void (Component::*)(T0), F, Derived>
      : action1<
            void (Component::*)(T0), F, Derived>
    {};
}}
namespace hpx { namespace actions
{
    
    
    template <
        typename Component, typename Result, typename T0 , typename T1,
        Result (Component::*F)(T0 , T1), typename Derived>
    class base_result_action2<
            Result (Component::*)(T0 , T1), F, Derived>
      : public action<
            Component, Result,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type>,
            Derived>
    {
    public:
        typedef Result result_type;
        typedef typename detail::remote_action_result<Result>::type
            remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type> arguments_type;
        typedef action<Component, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component>::call(lva)) << ")";
                    (get_lva<Component>::call(lva)->*F)(
                        boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        typedef boost::mpl::false_ direct_execution;
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                util::bind(util::one_shot(typename Derived::thread_function()),
                    lva, util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function(
                    cont, F, get_lva<Component>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static Result
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_result_action" << 2
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component>::call(lva)) << ")";
            return (get_lva<Component>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)));
        }
    };
    
    
    template <
        typename Component, typename Result, typename T0 , typename T1,
        Result (Component::*F)(T0 , T1), typename Derived>
    struct result_action2<
            Result (Component::*)(T0 , T1), F, Derived>
      : base_result_action2<
            Result (Component::*)(T0 , T1), F,
            typename detail::action_type<
                result_action2<
                    Result (Component::*)(T0 , T1), F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            result_action2, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1,
        Result (Component::*F)(T0 , T1), typename Derived>
    struct make_action<Result (Component::*)(T0 , T1),
            F, Derived, boost::mpl::false_>
      : result_action2<
            Result (Component::*)(T0 , T1), F, Derived>
    {
        typedef result_action2<
            Result (Component::*)(T0 , T1), F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1,
        Result (Component::*F)(T0 , T1),
        typename Derived>
    struct direct_result_action2<
            Result (Component::*)(T0 , T1), F, Derived>
      : base_result_action2<
            Result (Component::*)(T0 , T1), F,
            typename detail::action_type<
                direct_result_action2<
                    Result (Component::*)(T0 , T1), F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_result_action2, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1,
        Result (Component::*F)(T0 , T1), typename Derived>
    struct make_action<Result (Component::*)(T0 , T1),
            F, Derived, boost::mpl::true_>
      : direct_result_action2<
            Result (Component::*)(T0 , T1), F, Derived>
    {
        typedef direct_result_action2<
            Result (Component::*)(T0 , T1), F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename T0 , typename T1,
        void (Component::*F)(T0 , T1), typename Derived>
    class base_action2<
            void (Component::*)(T0 , T1), F, Derived>
      : public action<
            Component, util::unused_type,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type>,
            Derived>
    {
    public:
        typedef util::unused_type result_type;
        typedef util::unused_type remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type> arguments_type;
        typedef action<Component, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component>::call(lva)) << ")";
                    (get_lva<Component>::call(lva)->*F)(
                        boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            
            
            return Derived::decorate_action(
                util::bind(util::one_shot(typename Derived::thread_function()), lva,
                    util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function_void(
                    cont, F, get_lva<Component>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static util::unused_type
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_action" << 2
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component>::call(lva)) << ")";
            (get_lva<Component>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)));
            return util::unused;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1,
        void (Component::*F)(T0 , T1),
        typename Derived>
    struct action2<
            void (Component::*)(T0 , T1), F, Derived>
      : base_action2<
            void (Component::*)(T0 , T1), F,
            typename detail::action_type<
                action2<
                    void (Component::*)(T0 , T1), F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            action2, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename T0 , typename T1,
        void (Component::*F)(T0 , T1), typename Derived>
    struct make_action<void (Component::*)(T0 , T1),
            F, Derived, boost::mpl::false_>
      : action2<
            void (Component::*)(T0 , T1), F, Derived>
    {
        typedef action2<
            void (Component::*)(T0 , T1), F, Derived
        > type;
    };
    
    template <
        typename Component, typename T0 , typename T1,
        void (Component::*F)(T0 , T1),
        typename Derived>
    struct direct_action2<
            void (Component::*)(T0 , T1), F, Derived>
      : base_action2<
            void (Component::*)(T0 , T1), F,
            typename detail::action_type<
                direct_action2<
                    void (Component::*)(T0 , T1), F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_action2, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1,
        void (Component::*F)(T0 , T1), typename Derived>
    struct make_action<void (Component::*)(T0 , T1),
            F, Derived, boost::mpl::true_>
      : direct_action2<
            void (Component::*)(T0 , T1), F, Derived>
    {
        typedef direct_action2<
            void (Component::*)(T0 , T1), F, Derived
        > type;
    };
    
    
    template <
        typename Component,
        typename T0 , typename T1,
        void (Component::*F)(T0 , T1),
        typename Derived>
    struct result_action2<
            void (Component::*)(T0 , T1), F, Derived>
      : action2<
            void (Component::*)(T0 , T1), F, Derived>
    {};
}}
namespace hpx { namespace actions
{
    
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2,
        Result (Component::*F)(T0 , T1 , T2), typename Derived>
    class base_result_action3<
            Result (Component::*)(T0 , T1 , T2), F, Derived>
      : public action<
            Component, Result,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type>,
            Derived>
    {
    public:
        typedef Result result_type;
        typedef typename detail::remote_action_result<Result>::type
            remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type> arguments_type;
        typedef action<Component, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component>::call(lva)) << ")";
                    (get_lva<Component>::call(lva)->*F)(
                        boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        typedef boost::mpl::false_ direct_execution;
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                util::bind(util::one_shot(typename Derived::thread_function()),
                    lva, util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function(
                    cont, F, get_lva<Component>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static Result
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_result_action" << 3
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component>::call(lva)) << ")";
            return (get_lva<Component>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)));
        }
    };
    
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2,
        Result (Component::*F)(T0 , T1 , T2), typename Derived>
    struct result_action3<
            Result (Component::*)(T0 , T1 , T2), F, Derived>
      : base_result_action3<
            Result (Component::*)(T0 , T1 , T2), F,
            typename detail::action_type<
                result_action3<
                    Result (Component::*)(T0 , T1 , T2), F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            result_action3, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2,
        Result (Component::*F)(T0 , T1 , T2), typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2),
            F, Derived, boost::mpl::false_>
      : result_action3<
            Result (Component::*)(T0 , T1 , T2), F, Derived>
    {
        typedef result_action3<
            Result (Component::*)(T0 , T1 , T2), F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2,
        Result (Component::*F)(T0 , T1 , T2),
        typename Derived>
    struct direct_result_action3<
            Result (Component::*)(T0 , T1 , T2), F, Derived>
      : base_result_action3<
            Result (Component::*)(T0 , T1 , T2), F,
            typename detail::action_type<
                direct_result_action3<
                    Result (Component::*)(T0 , T1 , T2), F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_result_action3, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2,
        Result (Component::*F)(T0 , T1 , T2), typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2),
            F, Derived, boost::mpl::true_>
      : direct_result_action3<
            Result (Component::*)(T0 , T1 , T2), F, Derived>
    {
        typedef direct_result_action3<
            Result (Component::*)(T0 , T1 , T2), F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename T0 , typename T1 , typename T2,
        void (Component::*F)(T0 , T1 , T2), typename Derived>
    class base_action3<
            void (Component::*)(T0 , T1 , T2), F, Derived>
      : public action<
            Component, util::unused_type,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type>,
            Derived>
    {
    public:
        typedef util::unused_type result_type;
        typedef util::unused_type remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type> arguments_type;
        typedef action<Component, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component>::call(lva)) << ")";
                    (get_lva<Component>::call(lva)->*F)(
                        boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            
            
            return Derived::decorate_action(
                util::bind(util::one_shot(typename Derived::thread_function()), lva,
                    util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function_void(
                    cont, F, get_lva<Component>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static util::unused_type
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_action" << 3
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component>::call(lva)) << ")";
            (get_lva<Component>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)));
            return util::unused;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2,
        void (Component::*F)(T0 , T1 , T2),
        typename Derived>
    struct action3<
            void (Component::*)(T0 , T1 , T2), F, Derived>
      : base_action3<
            void (Component::*)(T0 , T1 , T2), F,
            typename detail::action_type<
                action3<
                    void (Component::*)(T0 , T1 , T2), F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            action3, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2,
        void (Component::*F)(T0 , T1 , T2), typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2),
            F, Derived, boost::mpl::false_>
      : action3<
            void (Component::*)(T0 , T1 , T2), F, Derived>
    {
        typedef action3<
            void (Component::*)(T0 , T1 , T2), F, Derived
        > type;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2,
        void (Component::*F)(T0 , T1 , T2),
        typename Derived>
    struct direct_action3<
            void (Component::*)(T0 , T1 , T2), F, Derived>
      : base_action3<
            void (Component::*)(T0 , T1 , T2), F,
            typename detail::action_type<
                direct_action3<
                    void (Component::*)(T0 , T1 , T2), F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_action3, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2,
        void (Component::*F)(T0 , T1 , T2), typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2),
            F, Derived, boost::mpl::true_>
      : direct_action3<
            void (Component::*)(T0 , T1 , T2), F, Derived>
    {
        typedef direct_action3<
            void (Component::*)(T0 , T1 , T2), F, Derived
        > type;
    };
    
    
    template <
        typename Component,
        typename T0 , typename T1 , typename T2,
        void (Component::*F)(T0 , T1 , T2),
        typename Derived>
    struct result_action3<
            void (Component::*)(T0 , T1 , T2), F, Derived>
      : action3<
            void (Component::*)(T0 , T1 , T2), F, Derived>
    {};
}}
namespace hpx { namespace actions
{
    
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3,
        Result (Component::*F)(T0 , T1 , T2 , T3), typename Derived>
    class base_result_action4<
            Result (Component::*)(T0 , T1 , T2 , T3), F, Derived>
      : public action<
            Component, Result,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type>,
            Derived>
    {
    public:
        typedef Result result_type;
        typedef typename detail::remote_action_result<Result>::type
            remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type> arguments_type;
        typedef action<Component, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component>::call(lva)) << ")";
                    (get_lva<Component>::call(lva)->*F)(
                        boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        typedef boost::mpl::false_ direct_execution;
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                util::bind(util::one_shot(typename Derived::thread_function()),
                    lva, util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function(
                    cont, F, get_lva<Component>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static Result
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_result_action" << 4
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component>::call(lva)) << ")";
            return (get_lva<Component>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)));
        }
    };
    
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3,
        Result (Component::*F)(T0 , T1 , T2 , T3), typename Derived>
    struct result_action4<
            Result (Component::*)(T0 , T1 , T2 , T3), F, Derived>
      : base_result_action4<
            Result (Component::*)(T0 , T1 , T2 , T3), F,
            typename detail::action_type<
                result_action4<
                    Result (Component::*)(T0 , T1 , T2 , T3), F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            result_action4, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3,
        Result (Component::*F)(T0 , T1 , T2 , T3), typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3),
            F, Derived, boost::mpl::false_>
      : result_action4<
            Result (Component::*)(T0 , T1 , T2 , T3), F, Derived>
    {
        typedef result_action4<
            Result (Component::*)(T0 , T1 , T2 , T3), F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2 , typename T3,
        Result (Component::*F)(T0 , T1 , T2 , T3),
        typename Derived>
    struct direct_result_action4<
            Result (Component::*)(T0 , T1 , T2 , T3), F, Derived>
      : base_result_action4<
            Result (Component::*)(T0 , T1 , T2 , T3), F,
            typename detail::action_type<
                direct_result_action4<
                    Result (Component::*)(T0 , T1 , T2 , T3), F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_result_action4, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3,
        Result (Component::*F)(T0 , T1 , T2 , T3), typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3),
            F, Derived, boost::mpl::true_>
      : direct_result_action4<
            Result (Component::*)(T0 , T1 , T2 , T3), F, Derived>
    {
        typedef direct_result_action4<
            Result (Component::*)(T0 , T1 , T2 , T3), F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3,
        void (Component::*F)(T0 , T1 , T2 , T3), typename Derived>
    class base_action4<
            void (Component::*)(T0 , T1 , T2 , T3), F, Derived>
      : public action<
            Component, util::unused_type,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type>,
            Derived>
    {
    public:
        typedef util::unused_type result_type;
        typedef util::unused_type remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type> arguments_type;
        typedef action<Component, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component>::call(lva)) << ")";
                    (get_lva<Component>::call(lva)->*F)(
                        boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            
            
            return Derived::decorate_action(
                util::bind(util::one_shot(typename Derived::thread_function()), lva,
                    util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function_void(
                    cont, F, get_lva<Component>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static util::unused_type
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_action" << 4
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component>::call(lva)) << ")";
            (get_lva<Component>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)));
            return util::unused;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3,
        void (Component::*F)(T0 , T1 , T2 , T3),
        typename Derived>
    struct action4<
            void (Component::*)(T0 , T1 , T2 , T3), F, Derived>
      : base_action4<
            void (Component::*)(T0 , T1 , T2 , T3), F,
            typename detail::action_type<
                action4<
                    void (Component::*)(T0 , T1 , T2 , T3), F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            action4, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3,
        void (Component::*F)(T0 , T1 , T2 , T3), typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3),
            F, Derived, boost::mpl::false_>
      : action4<
            void (Component::*)(T0 , T1 , T2 , T3), F, Derived>
    {
        typedef action4<
            void (Component::*)(T0 , T1 , T2 , T3), F, Derived
        > type;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3,
        void (Component::*F)(T0 , T1 , T2 , T3),
        typename Derived>
    struct direct_action4<
            void (Component::*)(T0 , T1 , T2 , T3), F, Derived>
      : base_action4<
            void (Component::*)(T0 , T1 , T2 , T3), F,
            typename detail::action_type<
                direct_action4<
                    void (Component::*)(T0 , T1 , T2 , T3), F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_action4, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3,
        void (Component::*F)(T0 , T1 , T2 , T3), typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3),
            F, Derived, boost::mpl::true_>
      : direct_action4<
            void (Component::*)(T0 , T1 , T2 , T3), F, Derived>
    {
        typedef direct_action4<
            void (Component::*)(T0 , T1 , T2 , T3), F, Derived
        > type;
    };
    
    
    template <
        typename Component,
        typename T0 , typename T1 , typename T2 , typename T3,
        void (Component::*F)(T0 , T1 , T2 , T3),
        typename Derived>
    struct result_action4<
            void (Component::*)(T0 , T1 , T2 , T3), F, Derived>
      : action4<
            void (Component::*)(T0 , T1 , T2 , T3), F, Derived>
    {};
}}
namespace hpx { namespace actions
{
    
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4), typename Derived>
    class base_result_action5<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4), F, Derived>
      : public action<
            Component, Result,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type>,
            Derived>
    {
    public:
        typedef Result result_type;
        typedef typename detail::remote_action_result<Result>::type
            remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type> arguments_type;
        typedef action<Component, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component>::call(lva)) << ")";
                    (get_lva<Component>::call(lva)->*F)(
                        boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        typedef boost::mpl::false_ direct_execution;
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                util::bind(util::one_shot(typename Derived::thread_function()),
                    lva, util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function(
                    cont, F, get_lva<Component>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static Result
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_result_action" << 5
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component>::call(lva)) << ")";
            return (get_lva<Component>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)));
        }
    };
    
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4), typename Derived>
    struct result_action5<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4), F, Derived>
      : base_result_action5<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4), F,
            typename detail::action_type<
                result_action5<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4), F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            result_action5, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4), typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4),
            F, Derived, boost::mpl::false_>
      : result_action5<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4), F, Derived>
    {
        typedef result_action5<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4), F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4),
        typename Derived>
    struct direct_result_action5<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4), F, Derived>
      : base_result_action5<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4), F,
            typename detail::action_type<
                direct_result_action5<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4), F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_result_action5, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4), typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4),
            F, Derived, boost::mpl::true_>
      : direct_result_action5<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4), F, Derived>
    {
        typedef direct_result_action5<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4), F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4), typename Derived>
    class base_action5<
            void (Component::*)(T0 , T1 , T2 , T3 , T4), F, Derived>
      : public action<
            Component, util::unused_type,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type>,
            Derived>
    {
    public:
        typedef util::unused_type result_type;
        typedef util::unused_type remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type> arguments_type;
        typedef action<Component, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component>::call(lva)) << ")";
                    (get_lva<Component>::call(lva)->*F)(
                        boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            
            
            return Derived::decorate_action(
                util::bind(util::one_shot(typename Derived::thread_function()), lva,
                    util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function_void(
                    cont, F, get_lva<Component>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static util::unused_type
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_action" << 5
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component>::call(lva)) << ")";
            (get_lva<Component>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)));
            return util::unused;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4),
        typename Derived>
    struct action5<
            void (Component::*)(T0 , T1 , T2 , T3 , T4), F, Derived>
      : base_action5<
            void (Component::*)(T0 , T1 , T2 , T3 , T4), F,
            typename detail::action_type<
                action5<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4), F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            action5, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4), typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4),
            F, Derived, boost::mpl::false_>
      : action5<
            void (Component::*)(T0 , T1 , T2 , T3 , T4), F, Derived>
    {
        typedef action5<
            void (Component::*)(T0 , T1 , T2 , T3 , T4), F, Derived
        > type;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4),
        typename Derived>
    struct direct_action5<
            void (Component::*)(T0 , T1 , T2 , T3 , T4), F, Derived>
      : base_action5<
            void (Component::*)(T0 , T1 , T2 , T3 , T4), F,
            typename detail::action_type<
                direct_action5<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4), F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_action5, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4), typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4),
            F, Derived, boost::mpl::true_>
      : direct_action5<
            void (Component::*)(T0 , T1 , T2 , T3 , T4), F, Derived>
    {
        typedef direct_action5<
            void (Component::*)(T0 , T1 , T2 , T3 , T4), F, Derived
        > type;
    };
    
    
    template <
        typename Component,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4),
        typename Derived>
    struct result_action5<
            void (Component::*)(T0 , T1 , T2 , T3 , T4), F, Derived>
      : action5<
            void (Component::*)(T0 , T1 , T2 , T3 , T4), F, Derived>
    {};
}}
namespace hpx { namespace actions
{
    
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5), typename Derived>
    class base_result_action6<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5), F, Derived>
      : public action<
            Component, Result,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type>,
            Derived>
    {
    public:
        typedef Result result_type;
        typedef typename detail::remote_action_result<Result>::type
            remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type> arguments_type;
        typedef action<Component, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component>::call(lva)) << ")";
                    (get_lva<Component>::call(lva)->*F)(
                        boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        typedef boost::mpl::false_ direct_execution;
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                util::bind(util::one_shot(typename Derived::thread_function()),
                    lva, util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function(
                    cont, F, get_lva<Component>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static Result
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_result_action" << 6
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component>::call(lva)) << ")";
            return (get_lva<Component>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)));
        }
    };
    
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5), typename Derived>
    struct result_action6<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5), F, Derived>
      : base_result_action6<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5), F,
            typename detail::action_type<
                result_action6<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5), F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            result_action6, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5), typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5),
            F, Derived, boost::mpl::false_>
      : result_action6<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5), F, Derived>
    {
        typedef result_action6<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5), F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5),
        typename Derived>
    struct direct_result_action6<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5), F, Derived>
      : base_result_action6<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5), F,
            typename detail::action_type<
                direct_result_action6<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5), F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_result_action6, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5), typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5),
            F, Derived, boost::mpl::true_>
      : direct_result_action6<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5), F, Derived>
    {
        typedef direct_result_action6<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5), F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5), typename Derived>
    class base_action6<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5), F, Derived>
      : public action<
            Component, util::unused_type,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type>,
            Derived>
    {
    public:
        typedef util::unused_type result_type;
        typedef util::unused_type remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type> arguments_type;
        typedef action<Component, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component>::call(lva)) << ")";
                    (get_lva<Component>::call(lva)->*F)(
                        boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            
            
            return Derived::decorate_action(
                util::bind(util::one_shot(typename Derived::thread_function()), lva,
                    util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function_void(
                    cont, F, get_lva<Component>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static util::unused_type
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_action" << 6
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component>::call(lva)) << ")";
            (get_lva<Component>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)));
            return util::unused;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5),
        typename Derived>
    struct action6<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5), F, Derived>
      : base_action6<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5), F,
            typename detail::action_type<
                action6<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5), F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            action6, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5), typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5),
            F, Derived, boost::mpl::false_>
      : action6<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5), F, Derived>
    {
        typedef action6<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5), F, Derived
        > type;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5),
        typename Derived>
    struct direct_action6<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5), F, Derived>
      : base_action6<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5), F,
            typename detail::action_type<
                direct_action6<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5), F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_action6, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5), typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5),
            F, Derived, boost::mpl::true_>
      : direct_action6<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5), F, Derived>
    {
        typedef direct_action6<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5), F, Derived
        > type;
    };
    
    
    template <
        typename Component,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5),
        typename Derived>
    struct result_action6<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5), F, Derived>
      : action6<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5), F, Derived>
    {};
}}
namespace hpx { namespace actions
{
    
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6), typename Derived>
    class base_result_action7<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6), F, Derived>
      : public action<
            Component, Result,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type>,
            Derived>
    {
    public:
        typedef Result result_type;
        typedef typename detail::remote_action_result<Result>::type
            remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type> arguments_type;
        typedef action<Component, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component>::call(lva)) << ")";
                    (get_lva<Component>::call(lva)->*F)(
                        boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        typedef boost::mpl::false_ direct_execution;
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                util::bind(util::one_shot(typename Derived::thread_function()),
                    lva, util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function(
                    cont, F, get_lva<Component>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static Result
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_result_action" << 7
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component>::call(lva)) << ")";
            return (get_lva<Component>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)));
        }
    };
    
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6), typename Derived>
    struct result_action7<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6), F, Derived>
      : base_result_action7<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6), F,
            typename detail::action_type<
                result_action7<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6), F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            result_action7, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6), typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6),
            F, Derived, boost::mpl::false_>
      : result_action7<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6), F, Derived>
    {
        typedef result_action7<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6), F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6),
        typename Derived>
    struct direct_result_action7<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6), F, Derived>
      : base_result_action7<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6), F,
            typename detail::action_type<
                direct_result_action7<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6), F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_result_action7, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6), typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6),
            F, Derived, boost::mpl::true_>
      : direct_result_action7<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6), F, Derived>
    {
        typedef direct_result_action7<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6), F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6), typename Derived>
    class base_action7<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6), F, Derived>
      : public action<
            Component, util::unused_type,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type>,
            Derived>
    {
    public:
        typedef util::unused_type result_type;
        typedef util::unused_type remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type> arguments_type;
        typedef action<Component, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component>::call(lva)) << ")";
                    (get_lva<Component>::call(lva)->*F)(
                        boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            
            
            return Derived::decorate_action(
                util::bind(util::one_shot(typename Derived::thread_function()), lva,
                    util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function_void(
                    cont, F, get_lva<Component>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static util::unused_type
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_action" << 7
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component>::call(lva)) << ")";
            (get_lva<Component>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)));
            return util::unused;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6),
        typename Derived>
    struct action7<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6), F, Derived>
      : base_action7<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6), F,
            typename detail::action_type<
                action7<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6), F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            action7, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6), typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6),
            F, Derived, boost::mpl::false_>
      : action7<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6), F, Derived>
    {
        typedef action7<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6), F, Derived
        > type;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6),
        typename Derived>
    struct direct_action7<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6), F, Derived>
      : base_action7<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6), F,
            typename detail::action_type<
                direct_action7<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6), F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_action7, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6), typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6),
            F, Derived, boost::mpl::true_>
      : direct_action7<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6), F, Derived>
    {
        typedef direct_action7<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6), F, Derived
        > type;
    };
    
    
    template <
        typename Component,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6),
        typename Derived>
    struct result_action7<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6), F, Derived>
      : action7<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6), F, Derived>
    {};
}}
namespace hpx { namespace actions
{
    
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7), typename Derived>
    class base_result_action8<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7), F, Derived>
      : public action<
            Component, Result,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type>,
            Derived>
    {
    public:
        typedef Result result_type;
        typedef typename detail::remote_action_result<Result>::type
            remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type> arguments_type;
        typedef action<Component, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component>::call(lva)) << ")";
                    (get_lva<Component>::call(lva)->*F)(
                        boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        typedef boost::mpl::false_ direct_execution;
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                util::bind(util::one_shot(typename Derived::thread_function()),
                    lva, util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function(
                    cont, F, get_lva<Component>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static Result
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_result_action" << 8
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component>::call(lva)) << ")";
            return (get_lva<Component>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)));
        }
    };
    
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7), typename Derived>
    struct result_action8<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7), F, Derived>
      : base_result_action8<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7), F,
            typename detail::action_type<
                result_action8<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7), F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            result_action8, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7), typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7),
            F, Derived, boost::mpl::false_>
      : result_action8<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7), F, Derived>
    {
        typedef result_action8<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7), F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7),
        typename Derived>
    struct direct_result_action8<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7), F, Derived>
      : base_result_action8<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7), F,
            typename detail::action_type<
                direct_result_action8<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7), F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_result_action8, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7), typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7),
            F, Derived, boost::mpl::true_>
      : direct_result_action8<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7), F, Derived>
    {
        typedef direct_result_action8<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7), F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7), typename Derived>
    class base_action8<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7), F, Derived>
      : public action<
            Component, util::unused_type,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type>,
            Derived>
    {
    public:
        typedef util::unused_type result_type;
        typedef util::unused_type remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type> arguments_type;
        typedef action<Component, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component>::call(lva)) << ")";
                    (get_lva<Component>::call(lva)->*F)(
                        boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            
            
            return Derived::decorate_action(
                util::bind(util::one_shot(typename Derived::thread_function()), lva,
                    util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function_void(
                    cont, F, get_lva<Component>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static util::unused_type
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_action" << 8
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component>::call(lva)) << ")";
            (get_lva<Component>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)));
            return util::unused;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7),
        typename Derived>
    struct action8<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7), F, Derived>
      : base_action8<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7), F,
            typename detail::action_type<
                action8<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7), F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            action8, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7), typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7),
            F, Derived, boost::mpl::false_>
      : action8<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7), F, Derived>
    {
        typedef action8<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7), F, Derived
        > type;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7),
        typename Derived>
    struct direct_action8<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7), F, Derived>
      : base_action8<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7), F,
            typename detail::action_type<
                direct_action8<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7), F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_action8, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7), typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7),
            F, Derived, boost::mpl::true_>
      : direct_action8<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7), F, Derived>
    {
        typedef direct_action8<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7), F, Derived
        > type;
    };
    
    
    template <
        typename Component,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7),
        typename Derived>
    struct result_action8<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7), F, Derived>
      : action8<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7), F, Derived>
    {};
}}
namespace hpx { namespace actions
{
    
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8), typename Derived>
    class base_result_action9<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8), F, Derived>
      : public action<
            Component, Result,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type>,
            Derived>
    {
    public:
        typedef Result result_type;
        typedef typename detail::remote_action_result<Result>::type
            remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type> arguments_type;
        typedef action<Component, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component>::call(lva)) << ")";
                    (get_lva<Component>::call(lva)->*F)(
                        boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        typedef boost::mpl::false_ direct_execution;
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                util::bind(util::one_shot(typename Derived::thread_function()),
                    lva, util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function(
                    cont, F, get_lva<Component>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static Result
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_result_action" << 9
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component>::call(lva)) << ")";
            return (get_lva<Component>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)));
        }
    };
    
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8), typename Derived>
    struct result_action9<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8), F, Derived>
      : base_result_action9<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8), F,
            typename detail::action_type<
                result_action9<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8), F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            result_action9, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8), typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8),
            F, Derived, boost::mpl::false_>
      : result_action9<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8), F, Derived>
    {
        typedef result_action9<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8), F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8),
        typename Derived>
    struct direct_result_action9<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8), F, Derived>
      : base_result_action9<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8), F,
            typename detail::action_type<
                direct_result_action9<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8), F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_result_action9, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8), typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8),
            F, Derived, boost::mpl::true_>
      : direct_result_action9<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8), F, Derived>
    {
        typedef direct_result_action9<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8), F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8), typename Derived>
    class base_action9<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8), F, Derived>
      : public action<
            Component, util::unused_type,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type>,
            Derived>
    {
    public:
        typedef util::unused_type result_type;
        typedef util::unused_type remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type> arguments_type;
        typedef action<Component, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component>::call(lva)) << ")";
                    (get_lva<Component>::call(lva)->*F)(
                        boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            
            
            return Derived::decorate_action(
                util::bind(util::one_shot(typename Derived::thread_function()), lva,
                    util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function_void(
                    cont, F, get_lva<Component>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static util::unused_type
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_action" << 9
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component>::call(lva)) << ")";
            (get_lva<Component>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)));
            return util::unused;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8),
        typename Derived>
    struct action9<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8), F, Derived>
      : base_action9<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8), F,
            typename detail::action_type<
                action9<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8), F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            action9, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8), typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8),
            F, Derived, boost::mpl::false_>
      : action9<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8), F, Derived>
    {
        typedef action9<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8), F, Derived
        > type;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8),
        typename Derived>
    struct direct_action9<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8), F, Derived>
      : base_action9<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8), F,
            typename detail::action_type<
                direct_action9<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8), F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_action9, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8), typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8),
            F, Derived, boost::mpl::true_>
      : direct_action9<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8), F, Derived>
    {
        typedef direct_action9<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8), F, Derived
        > type;
    };
    
    
    template <
        typename Component,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8),
        typename Derived>
    struct result_action9<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8), F, Derived>
      : action9<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8), F, Derived>
    {};
}}
namespace hpx { namespace actions
{
    
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9), typename Derived>
    class base_result_action10<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9), F, Derived>
      : public action<
            Component, Result,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type>,
            Derived>
    {
    public:
        typedef Result result_type;
        typedef typename detail::remote_action_result<Result>::type
            remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type> arguments_type;
        typedef action<Component, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component>::call(lva)) << ")";
                    (get_lva<Component>::call(lva)->*F)(
                        boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ) , boost::forward<Arg9>( arg9 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        typedef boost::mpl::false_ direct_execution;
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                util::bind(util::one_shot(typename Derived::thread_function()),
                    lva, util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function(
                    cont, F, get_lva<Component>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static Result
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_result_action" << 10
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component>::call(lva)) << ")";
            return (get_lva<Component>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)));
        }
    };
    
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9), typename Derived>
    struct result_action10<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9), F, Derived>
      : base_result_action10<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9), F,
            typename detail::action_type<
                result_action10<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9), F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            result_action10, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9), typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9),
            F, Derived, boost::mpl::false_>
      : result_action10<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9), F, Derived>
    {
        typedef result_action10<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9), F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9),
        typename Derived>
    struct direct_result_action10<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9), F, Derived>
      : base_result_action10<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9), F,
            typename detail::action_type<
                direct_result_action10<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9), F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_result_action10, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9), typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9),
            F, Derived, boost::mpl::true_>
      : direct_result_action10<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9), F, Derived>
    {
        typedef direct_result_action10<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9), F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9), typename Derived>
    class base_action10<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9), F, Derived>
      : public action<
            Component, util::unused_type,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type>,
            Derived>
    {
    public:
        typedef util::unused_type result_type;
        typedef util::unused_type remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type> arguments_type;
        typedef action<Component, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component>::call(lva)) << ")";
                    (get_lva<Component>::call(lva)->*F)(
                        boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ) , boost::forward<Arg9>( arg9 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            
            
            return Derived::decorate_action(
                util::bind(util::one_shot(typename Derived::thread_function()), lva,
                    util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function_void(
                    cont, F, get_lva<Component>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static util::unused_type
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_action" << 10
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component>::call(lva)) << ")";
            (get_lva<Component>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)));
            return util::unused;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9),
        typename Derived>
    struct action10<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9), F, Derived>
      : base_action10<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9), F,
            typename detail::action_type<
                action10<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9), F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            action10, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9), typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9),
            F, Derived, boost::mpl::false_>
      : action10<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9), F, Derived>
    {
        typedef action10<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9), F, Derived
        > type;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9),
        typename Derived>
    struct direct_action10<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9), F, Derived>
      : base_action10<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9), F,
            typename detail::action_type<
                direct_action10<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9), F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_action10, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9), typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9),
            F, Derived, boost::mpl::true_>
      : direct_action10<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9), F, Derived>
    {
        typedef direct_action10<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9), F, Derived
        > type;
    };
    
    
    template <
        typename Component,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9),
        typename Derived>
    struct result_action10<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9), F, Derived>
      : action10<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9), F, Derived>
    {};
}}
namespace hpx { namespace actions
{
    
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10), typename Derived>
    class base_result_action11<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10), F, Derived>
      : public action<
            Component, Result,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type>,
            Derived>
    {
    public:
        typedef Result result_type;
        typedef typename detail::remote_action_result<Result>::type
            remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type> arguments_type;
        typedef action<Component, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9 , BOOST_FWD_REF(Arg10) arg10) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component>::call(lva)) << ")";
                    (get_lva<Component>::call(lva)->*F)(
                        boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ) , boost::forward<Arg9>( arg9 ) , boost::forward<Arg10>( arg10 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        typedef boost::mpl::false_ direct_execution;
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                util::bind(util::one_shot(typename Derived::thread_function()),
                    lva, util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)) , util::get< 10>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function(
                    cont, F, get_lva<Component>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static Result
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_result_action" << 11
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component>::call(lva)) << ")";
            return (get_lva<Component>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)) , util::get< 10>(boost::forward<Arguments>( args)));
        }
    };
    
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10), typename Derived>
    struct result_action11<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10), F, Derived>
      : base_result_action11<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10), F,
            typename detail::action_type<
                result_action11<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10), F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            result_action11, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10), typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10),
            F, Derived, boost::mpl::false_>
      : result_action11<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10), F, Derived>
    {
        typedef result_action11<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10), F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10),
        typename Derived>
    struct direct_result_action11<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10), F, Derived>
      : base_result_action11<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10), F,
            typename detail::action_type<
                direct_result_action11<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10), F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_result_action11, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10), typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10),
            F, Derived, boost::mpl::true_>
      : direct_result_action11<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10), F, Derived>
    {
        typedef direct_result_action11<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10), F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10), typename Derived>
    class base_action11<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10), F, Derived>
      : public action<
            Component, util::unused_type,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type>,
            Derived>
    {
    public:
        typedef util::unused_type result_type;
        typedef util::unused_type remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type> arguments_type;
        typedef action<Component, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9 , BOOST_FWD_REF(Arg10) arg10) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component>::call(lva)) << ")";
                    (get_lva<Component>::call(lva)->*F)(
                        boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ) , boost::forward<Arg9>( arg9 ) , boost::forward<Arg10>( arg10 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            
            
            return Derived::decorate_action(
                util::bind(util::one_shot(typename Derived::thread_function()), lva,
                    util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)) , util::get< 10>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function_void(
                    cont, F, get_lva<Component>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static util::unused_type
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_action" << 11
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component>::call(lva)) << ")";
            (get_lva<Component>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)) , util::get< 10>(boost::forward<Arguments>( args)));
            return util::unused;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10),
        typename Derived>
    struct action11<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10), F, Derived>
      : base_action11<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10), F,
            typename detail::action_type<
                action11<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10), F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            action11, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10), typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10),
            F, Derived, boost::mpl::false_>
      : action11<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10), F, Derived>
    {
        typedef action11<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10), F, Derived
        > type;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10),
        typename Derived>
    struct direct_action11<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10), F, Derived>
      : base_action11<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10), F,
            typename detail::action_type<
                direct_action11<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10), F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_action11, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10), typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10),
            F, Derived, boost::mpl::true_>
      : direct_action11<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10), F, Derived>
    {
        typedef direct_action11<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10), F, Derived
        > type;
    };
    
    
    template <
        typename Component,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10),
        typename Derived>
    struct result_action11<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10), F, Derived>
      : action11<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10), F, Derived>
    {};
}}
namespace hpx { namespace actions
{
    
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11), typename Derived>
    class base_result_action12<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11), F, Derived>
      : public action<
            Component, Result,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type>,
            Derived>
    {
    public:
        typedef Result result_type;
        typedef typename detail::remote_action_result<Result>::type
            remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type> arguments_type;
        typedef action<Component, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9 , BOOST_FWD_REF(Arg10) arg10 , BOOST_FWD_REF(Arg11) arg11) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component>::call(lva)) << ")";
                    (get_lva<Component>::call(lva)->*F)(
                        boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ) , boost::forward<Arg9>( arg9 ) , boost::forward<Arg10>( arg10 ) , boost::forward<Arg11>( arg11 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        typedef boost::mpl::false_ direct_execution;
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                util::bind(util::one_shot(typename Derived::thread_function()),
                    lva, util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)) , util::get< 10>(boost::forward<Arguments>( args)) , util::get< 11>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function(
                    cont, F, get_lva<Component>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static Result
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_result_action" << 12
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component>::call(lva)) << ")";
            return (get_lva<Component>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)) , util::get< 10>(boost::forward<Arguments>( args)) , util::get< 11>(boost::forward<Arguments>( args)));
        }
    };
    
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11), typename Derived>
    struct result_action12<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11), F, Derived>
      : base_result_action12<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11), F,
            typename detail::action_type<
                result_action12<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11), F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            result_action12, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11), typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11),
            F, Derived, boost::mpl::false_>
      : result_action12<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11), F, Derived>
    {
        typedef result_action12<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11), F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11),
        typename Derived>
    struct direct_result_action12<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11), F, Derived>
      : base_result_action12<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11), F,
            typename detail::action_type<
                direct_result_action12<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11), F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_result_action12, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11), typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11),
            F, Derived, boost::mpl::true_>
      : direct_result_action12<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11), F, Derived>
    {
        typedef direct_result_action12<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11), F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11), typename Derived>
    class base_action12<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11), F, Derived>
      : public action<
            Component, util::unused_type,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type>,
            Derived>
    {
    public:
        typedef util::unused_type result_type;
        typedef util::unused_type remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type> arguments_type;
        typedef action<Component, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9 , BOOST_FWD_REF(Arg10) arg10 , BOOST_FWD_REF(Arg11) arg11) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component>::call(lva)) << ")";
                    (get_lva<Component>::call(lva)->*F)(
                        boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ) , boost::forward<Arg9>( arg9 ) , boost::forward<Arg10>( arg10 ) , boost::forward<Arg11>( arg11 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            
            
            return Derived::decorate_action(
                util::bind(util::one_shot(typename Derived::thread_function()), lva,
                    util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)) , util::get< 10>(boost::forward<Arguments>( args)) , util::get< 11>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function_void(
                    cont, F, get_lva<Component>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static util::unused_type
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_action" << 12
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component>::call(lva)) << ")";
            (get_lva<Component>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)) , util::get< 10>(boost::forward<Arguments>( args)) , util::get< 11>(boost::forward<Arguments>( args)));
            return util::unused;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11),
        typename Derived>
    struct action12<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11), F, Derived>
      : base_action12<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11), F,
            typename detail::action_type<
                action12<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11), F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            action12, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11), typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11),
            F, Derived, boost::mpl::false_>
      : action12<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11), F, Derived>
    {
        typedef action12<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11), F, Derived
        > type;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11),
        typename Derived>
    struct direct_action12<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11), F, Derived>
      : base_action12<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11), F,
            typename detail::action_type<
                direct_action12<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11), F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_action12, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11), typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11),
            F, Derived, boost::mpl::true_>
      : direct_action12<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11), F, Derived>
    {
        typedef direct_action12<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11), F, Derived
        > type;
    };
    
    
    template <
        typename Component,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11),
        typename Derived>
    struct result_action12<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11), F, Derived>
      : action12<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11), F, Derived>
    {};
}}
namespace hpx { namespace actions
{
    
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12), typename Derived>
    class base_result_action13<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12), F, Derived>
      : public action<
            Component, Result,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type>,
            Derived>
    {
    public:
        typedef Result result_type;
        typedef typename detail::remote_action_result<Result>::type
            remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type> arguments_type;
        typedef action<Component, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11 , typename Arg12>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9 , BOOST_FWD_REF(Arg10) arg10 , BOOST_FWD_REF(Arg11) arg11 , BOOST_FWD_REF(Arg12) arg12) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component>::call(lva)) << ")";
                    (get_lva<Component>::call(lva)->*F)(
                        boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ) , boost::forward<Arg9>( arg9 ) , boost::forward<Arg10>( arg10 ) , boost::forward<Arg11>( arg11 ) , boost::forward<Arg12>( arg12 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        typedef boost::mpl::false_ direct_execution;
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                util::bind(util::one_shot(typename Derived::thread_function()),
                    lva, util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)) , util::get< 10>(boost::forward<Arguments>( args)) , util::get< 11>(boost::forward<Arguments>( args)) , util::get< 12>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function(
                    cont, F, get_lva<Component>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static Result
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_result_action" << 13
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component>::call(lva)) << ")";
            return (get_lva<Component>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)) , util::get< 10>(boost::forward<Arguments>( args)) , util::get< 11>(boost::forward<Arguments>( args)) , util::get< 12>(boost::forward<Arguments>( args)));
        }
    };
    
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12), typename Derived>
    struct result_action13<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12), F, Derived>
      : base_result_action13<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12), F,
            typename detail::action_type<
                result_action13<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12), F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            result_action13, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12), typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12),
            F, Derived, boost::mpl::false_>
      : result_action13<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12), F, Derived>
    {
        typedef result_action13<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12), F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12),
        typename Derived>
    struct direct_result_action13<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12), F, Derived>
      : base_result_action13<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12), F,
            typename detail::action_type<
                direct_result_action13<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12), F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_result_action13, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12), typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12),
            F, Derived, boost::mpl::true_>
      : direct_result_action13<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12), F, Derived>
    {
        typedef direct_result_action13<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12), F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12), typename Derived>
    class base_action13<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12), F, Derived>
      : public action<
            Component, util::unused_type,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type>,
            Derived>
    {
    public:
        typedef util::unused_type result_type;
        typedef util::unused_type remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type> arguments_type;
        typedef action<Component, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11 , typename Arg12>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9 , BOOST_FWD_REF(Arg10) arg10 , BOOST_FWD_REF(Arg11) arg11 , BOOST_FWD_REF(Arg12) arg12) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component>::call(lva)) << ")";
                    (get_lva<Component>::call(lva)->*F)(
                        boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ) , boost::forward<Arg9>( arg9 ) , boost::forward<Arg10>( arg10 ) , boost::forward<Arg11>( arg11 ) , boost::forward<Arg12>( arg12 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            
            
            return Derived::decorate_action(
                util::bind(util::one_shot(typename Derived::thread_function()), lva,
                    util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)) , util::get< 10>(boost::forward<Arguments>( args)) , util::get< 11>(boost::forward<Arguments>( args)) , util::get< 12>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function_void(
                    cont, F, get_lva<Component>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static util::unused_type
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_action" << 13
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component>::call(lva)) << ")";
            (get_lva<Component>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)) , util::get< 10>(boost::forward<Arguments>( args)) , util::get< 11>(boost::forward<Arguments>( args)) , util::get< 12>(boost::forward<Arguments>( args)));
            return util::unused;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12),
        typename Derived>
    struct action13<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12), F, Derived>
      : base_action13<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12), F,
            typename detail::action_type<
                action13<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12), F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            action13, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12), typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12),
            F, Derived, boost::mpl::false_>
      : action13<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12), F, Derived>
    {
        typedef action13<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12), F, Derived
        > type;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12),
        typename Derived>
    struct direct_action13<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12), F, Derived>
      : base_action13<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12), F,
            typename detail::action_type<
                direct_action13<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12), F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_action13, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12), typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12),
            F, Derived, boost::mpl::true_>
      : direct_action13<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12), F, Derived>
    {
        typedef direct_action13<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12), F, Derived
        > type;
    };
    
    
    template <
        typename Component,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12),
        typename Derived>
    struct result_action13<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12), F, Derived>
      : action13<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12), F, Derived>
    {};
}}
namespace hpx { namespace actions
{
    
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13), typename Derived>
    class base_result_action14<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13), F, Derived>
      : public action<
            Component, Result,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type>,
            Derived>
    {
    public:
        typedef Result result_type;
        typedef typename detail::remote_action_result<Result>::type
            remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type> arguments_type;
        typedef action<Component, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11 , typename Arg12 , typename Arg13>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9 , BOOST_FWD_REF(Arg10) arg10 , BOOST_FWD_REF(Arg11) arg11 , BOOST_FWD_REF(Arg12) arg12 , BOOST_FWD_REF(Arg13) arg13) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component>::call(lva)) << ")";
                    (get_lva<Component>::call(lva)->*F)(
                        boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ) , boost::forward<Arg9>( arg9 ) , boost::forward<Arg10>( arg10 ) , boost::forward<Arg11>( arg11 ) , boost::forward<Arg12>( arg12 ) , boost::forward<Arg13>( arg13 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        typedef boost::mpl::false_ direct_execution;
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                util::bind(util::one_shot(typename Derived::thread_function()),
                    lva, util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)) , util::get< 10>(boost::forward<Arguments>( args)) , util::get< 11>(boost::forward<Arguments>( args)) , util::get< 12>(boost::forward<Arguments>( args)) , util::get< 13>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function(
                    cont, F, get_lva<Component>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static Result
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_result_action" << 14
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component>::call(lva)) << ")";
            return (get_lva<Component>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)) , util::get< 10>(boost::forward<Arguments>( args)) , util::get< 11>(boost::forward<Arguments>( args)) , util::get< 12>(boost::forward<Arguments>( args)) , util::get< 13>(boost::forward<Arguments>( args)));
        }
    };
    
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13), typename Derived>
    struct result_action14<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13), F, Derived>
      : base_result_action14<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13), F,
            typename detail::action_type<
                result_action14<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13), F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            result_action14, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13), typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13),
            F, Derived, boost::mpl::false_>
      : result_action14<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13), F, Derived>
    {
        typedef result_action14<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13), F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13),
        typename Derived>
    struct direct_result_action14<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13), F, Derived>
      : base_result_action14<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13), F,
            typename detail::action_type<
                direct_result_action14<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13), F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_result_action14, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13), typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13),
            F, Derived, boost::mpl::true_>
      : direct_result_action14<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13), F, Derived>
    {
        typedef direct_result_action14<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13), F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13), typename Derived>
    class base_action14<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13), F, Derived>
      : public action<
            Component, util::unused_type,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type>,
            Derived>
    {
    public:
        typedef util::unused_type result_type;
        typedef util::unused_type remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type> arguments_type;
        typedef action<Component, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11 , typename Arg12 , typename Arg13>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9 , BOOST_FWD_REF(Arg10) arg10 , BOOST_FWD_REF(Arg11) arg11 , BOOST_FWD_REF(Arg12) arg12 , BOOST_FWD_REF(Arg13) arg13) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component>::call(lva)) << ")";
                    (get_lva<Component>::call(lva)->*F)(
                        boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ) , boost::forward<Arg9>( arg9 ) , boost::forward<Arg10>( arg10 ) , boost::forward<Arg11>( arg11 ) , boost::forward<Arg12>( arg12 ) , boost::forward<Arg13>( arg13 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            
            
            return Derived::decorate_action(
                util::bind(util::one_shot(typename Derived::thread_function()), lva,
                    util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)) , util::get< 10>(boost::forward<Arguments>( args)) , util::get< 11>(boost::forward<Arguments>( args)) , util::get< 12>(boost::forward<Arguments>( args)) , util::get< 13>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function_void(
                    cont, F, get_lva<Component>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static util::unused_type
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_action" << 14
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component>::call(lva)) << ")";
            (get_lva<Component>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)) , util::get< 10>(boost::forward<Arguments>( args)) , util::get< 11>(boost::forward<Arguments>( args)) , util::get< 12>(boost::forward<Arguments>( args)) , util::get< 13>(boost::forward<Arguments>( args)));
            return util::unused;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13),
        typename Derived>
    struct action14<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13), F, Derived>
      : base_action14<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13), F,
            typename detail::action_type<
                action14<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13), F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            action14, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13), typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13),
            F, Derived, boost::mpl::false_>
      : action14<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13), F, Derived>
    {
        typedef action14<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13), F, Derived
        > type;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13),
        typename Derived>
    struct direct_action14<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13), F, Derived>
      : base_action14<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13), F,
            typename detail::action_type<
                direct_action14<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13), F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_action14, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13), typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13),
            F, Derived, boost::mpl::true_>
      : direct_action14<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13), F, Derived>
    {
        typedef direct_action14<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13), F, Derived
        > type;
    };
    
    
    template <
        typename Component,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13),
        typename Derived>
    struct result_action14<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13), F, Derived>
      : action14<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13), F, Derived>
    {};
}}
namespace hpx { namespace actions
{
    
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14), typename Derived>
    class base_result_action15<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14), F, Derived>
      : public action<
            Component, Result,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type>,
            Derived>
    {
    public:
        typedef Result result_type;
        typedef typename detail::remote_action_result<Result>::type
            remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type> arguments_type;
        typedef action<Component, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11 , typename Arg12 , typename Arg13 , typename Arg14>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9 , BOOST_FWD_REF(Arg10) arg10 , BOOST_FWD_REF(Arg11) arg11 , BOOST_FWD_REF(Arg12) arg12 , BOOST_FWD_REF(Arg13) arg13 , BOOST_FWD_REF(Arg14) arg14) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component>::call(lva)) << ")";
                    (get_lva<Component>::call(lva)->*F)(
                        boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ) , boost::forward<Arg9>( arg9 ) , boost::forward<Arg10>( arg10 ) , boost::forward<Arg11>( arg11 ) , boost::forward<Arg12>( arg12 ) , boost::forward<Arg13>( arg13 ) , boost::forward<Arg14>( arg14 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        typedef boost::mpl::false_ direct_execution;
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                util::bind(util::one_shot(typename Derived::thread_function()),
                    lva, util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)) , util::get< 10>(boost::forward<Arguments>( args)) , util::get< 11>(boost::forward<Arguments>( args)) , util::get< 12>(boost::forward<Arguments>( args)) , util::get< 13>(boost::forward<Arguments>( args)) , util::get< 14>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function(
                    cont, F, get_lva<Component>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static Result
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_result_action" << 15
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component>::call(lva)) << ")";
            return (get_lva<Component>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)) , util::get< 10>(boost::forward<Arguments>( args)) , util::get< 11>(boost::forward<Arguments>( args)) , util::get< 12>(boost::forward<Arguments>( args)) , util::get< 13>(boost::forward<Arguments>( args)) , util::get< 14>(boost::forward<Arguments>( args)));
        }
    };
    
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14), typename Derived>
    struct result_action15<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14), F, Derived>
      : base_result_action15<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14), F,
            typename detail::action_type<
                result_action15<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14), F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            result_action15, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14), typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14),
            F, Derived, boost::mpl::false_>
      : result_action15<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14), F, Derived>
    {
        typedef result_action15<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14), F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14),
        typename Derived>
    struct direct_result_action15<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14), F, Derived>
      : base_result_action15<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14), F,
            typename detail::action_type<
                direct_result_action15<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14), F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_result_action15, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14), typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14),
            F, Derived, boost::mpl::true_>
      : direct_result_action15<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14), F, Derived>
    {
        typedef direct_result_action15<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14), F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14), typename Derived>
    class base_action15<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14), F, Derived>
      : public action<
            Component, util::unused_type,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type>,
            Derived>
    {
    public:
        typedef util::unused_type result_type;
        typedef util::unused_type remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type> arguments_type;
        typedef action<Component, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11 , typename Arg12 , typename Arg13 , typename Arg14>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9 , BOOST_FWD_REF(Arg10) arg10 , BOOST_FWD_REF(Arg11) arg11 , BOOST_FWD_REF(Arg12) arg12 , BOOST_FWD_REF(Arg13) arg13 , BOOST_FWD_REF(Arg14) arg14) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component>::call(lva)) << ")";
                    (get_lva<Component>::call(lva)->*F)(
                        boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ) , boost::forward<Arg9>( arg9 ) , boost::forward<Arg10>( arg10 ) , boost::forward<Arg11>( arg11 ) , boost::forward<Arg12>( arg12 ) , boost::forward<Arg13>( arg13 ) , boost::forward<Arg14>( arg14 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            
            
            return Derived::decorate_action(
                util::bind(util::one_shot(typename Derived::thread_function()), lva,
                    util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)) , util::get< 10>(boost::forward<Arguments>( args)) , util::get< 11>(boost::forward<Arguments>( args)) , util::get< 12>(boost::forward<Arguments>( args)) , util::get< 13>(boost::forward<Arguments>( args)) , util::get< 14>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function_void(
                    cont, F, get_lva<Component>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static util::unused_type
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_action" << 15
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component>::call(lva)) << ")";
            (get_lva<Component>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)) , util::get< 10>(boost::forward<Arguments>( args)) , util::get< 11>(boost::forward<Arguments>( args)) , util::get< 12>(boost::forward<Arguments>( args)) , util::get< 13>(boost::forward<Arguments>( args)) , util::get< 14>(boost::forward<Arguments>( args)));
            return util::unused;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14),
        typename Derived>
    struct action15<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14), F, Derived>
      : base_action15<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14), F,
            typename detail::action_type<
                action15<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14), F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            action15, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14), typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14),
            F, Derived, boost::mpl::false_>
      : action15<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14), F, Derived>
    {
        typedef action15<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14), F, Derived
        > type;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14),
        typename Derived>
    struct direct_action15<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14), F, Derived>
      : base_action15<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14), F,
            typename detail::action_type<
                direct_action15<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14), F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_action15, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14), typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14),
            F, Derived, boost::mpl::true_>
      : direct_action15<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14), F, Derived>
    {
        typedef direct_action15<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14), F, Derived
        > type;
    };
    
    
    template <
        typename Component,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14),
        typename Derived>
    struct result_action15<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14), F, Derived>
      : action15<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14), F, Derived>
    {};
}}
namespace hpx { namespace actions
{
    
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15), typename Derived>
    class base_result_action16<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15), F, Derived>
      : public action<
            Component, Result,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type>,
            Derived>
    {
    public:
        typedef Result result_type;
        typedef typename detail::remote_action_result<Result>::type
            remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type> arguments_type;
        typedef action<Component, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11 , typename Arg12 , typename Arg13 , typename Arg14 , typename Arg15>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9 , BOOST_FWD_REF(Arg10) arg10 , BOOST_FWD_REF(Arg11) arg11 , BOOST_FWD_REF(Arg12) arg12 , BOOST_FWD_REF(Arg13) arg13 , BOOST_FWD_REF(Arg14) arg14 , BOOST_FWD_REF(Arg15) arg15) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component>::call(lva)) << ")";
                    (get_lva<Component>::call(lva)->*F)(
                        boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ) , boost::forward<Arg9>( arg9 ) , boost::forward<Arg10>( arg10 ) , boost::forward<Arg11>( arg11 ) , boost::forward<Arg12>( arg12 ) , boost::forward<Arg13>( arg13 ) , boost::forward<Arg14>( arg14 ) , boost::forward<Arg15>( arg15 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        typedef boost::mpl::false_ direct_execution;
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                util::bind(util::one_shot(typename Derived::thread_function()),
                    lva, util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)) , util::get< 10>(boost::forward<Arguments>( args)) , util::get< 11>(boost::forward<Arguments>( args)) , util::get< 12>(boost::forward<Arguments>( args)) , util::get< 13>(boost::forward<Arguments>( args)) , util::get< 14>(boost::forward<Arguments>( args)) , util::get< 15>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function(
                    cont, F, get_lva<Component>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static Result
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_result_action" << 16
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component>::call(lva)) << ")";
            return (get_lva<Component>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)) , util::get< 10>(boost::forward<Arguments>( args)) , util::get< 11>(boost::forward<Arguments>( args)) , util::get< 12>(boost::forward<Arguments>( args)) , util::get< 13>(boost::forward<Arguments>( args)) , util::get< 14>(boost::forward<Arguments>( args)) , util::get< 15>(boost::forward<Arguments>( args)));
        }
    };
    
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15), typename Derived>
    struct result_action16<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15), F, Derived>
      : base_result_action16<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15), F,
            typename detail::action_type<
                result_action16<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15), F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            result_action16, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15), typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15),
            F, Derived, boost::mpl::false_>
      : result_action16<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15), F, Derived>
    {
        typedef result_action16<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15), F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15),
        typename Derived>
    struct direct_result_action16<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15), F, Derived>
      : base_result_action16<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15), F,
            typename detail::action_type<
                direct_result_action16<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15), F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_result_action16, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15), typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15),
            F, Derived, boost::mpl::true_>
      : direct_result_action16<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15), F, Derived>
    {
        typedef direct_result_action16<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15), F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15), typename Derived>
    class base_action16<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15), F, Derived>
      : public action<
            Component, util::unused_type,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type>,
            Derived>
    {
    public:
        typedef util::unused_type result_type;
        typedef util::unused_type remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type> arguments_type;
        typedef action<Component, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11 , typename Arg12 , typename Arg13 , typename Arg14 , typename Arg15>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9 , BOOST_FWD_REF(Arg10) arg10 , BOOST_FWD_REF(Arg11) arg11 , BOOST_FWD_REF(Arg12) arg12 , BOOST_FWD_REF(Arg13) arg13 , BOOST_FWD_REF(Arg14) arg14 , BOOST_FWD_REF(Arg15) arg15) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component>::call(lva)) << ")";
                    (get_lva<Component>::call(lva)->*F)(
                        boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ) , boost::forward<Arg9>( arg9 ) , boost::forward<Arg10>( arg10 ) , boost::forward<Arg11>( arg11 ) , boost::forward<Arg12>( arg12 ) , boost::forward<Arg13>( arg13 ) , boost::forward<Arg14>( arg14 ) , boost::forward<Arg15>( arg15 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            
            
            return Derived::decorate_action(
                util::bind(util::one_shot(typename Derived::thread_function()), lva,
                    util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)) , util::get< 10>(boost::forward<Arguments>( args)) , util::get< 11>(boost::forward<Arguments>( args)) , util::get< 12>(boost::forward<Arguments>( args)) , util::get< 13>(boost::forward<Arguments>( args)) , util::get< 14>(boost::forward<Arguments>( args)) , util::get< 15>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function_void(
                    cont, F, get_lva<Component>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static util::unused_type
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_action" << 16
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component>::call(lva)) << ")";
            (get_lva<Component>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)) , util::get< 10>(boost::forward<Arguments>( args)) , util::get< 11>(boost::forward<Arguments>( args)) , util::get< 12>(boost::forward<Arguments>( args)) , util::get< 13>(boost::forward<Arguments>( args)) , util::get< 14>(boost::forward<Arguments>( args)) , util::get< 15>(boost::forward<Arguments>( args)));
            return util::unused;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15),
        typename Derived>
    struct action16<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15), F, Derived>
      : base_action16<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15), F,
            typename detail::action_type<
                action16<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15), F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            action16, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15), typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15),
            F, Derived, boost::mpl::false_>
      : action16<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15), F, Derived>
    {
        typedef action16<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15), F, Derived
        > type;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15),
        typename Derived>
    struct direct_action16<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15), F, Derived>
      : base_action16<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15), F,
            typename detail::action_type<
                direct_action16<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15), F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_action16, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15), typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15),
            F, Derived, boost::mpl::true_>
      : direct_action16<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15), F, Derived>
    {
        typedef direct_action16<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15), F, Derived
        > type;
    };
    
    
    template <
        typename Component,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15),
        typename Derived>
    struct result_action16<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15), F, Derived>
      : action16<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15), F, Derived>
    {};
}}
namespace hpx { namespace actions
{
    
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16), typename Derived>
    class base_result_action17<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16), F, Derived>
      : public action<
            Component, Result,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type , typename util::decay<T16>::type>,
            Derived>
    {
    public:
        typedef Result result_type;
        typedef typename detail::remote_action_result<Result>::type
            remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type , typename util::decay<T16>::type> arguments_type;
        typedef action<Component, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11 , typename Arg12 , typename Arg13 , typename Arg14 , typename Arg15 , typename Arg16>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9 , BOOST_FWD_REF(Arg10) arg10 , BOOST_FWD_REF(Arg11) arg11 , BOOST_FWD_REF(Arg12) arg12 , BOOST_FWD_REF(Arg13) arg13 , BOOST_FWD_REF(Arg14) arg14 , BOOST_FWD_REF(Arg15) arg15 , BOOST_FWD_REF(Arg16) arg16) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component>::call(lva)) << ")";
                    (get_lva<Component>::call(lva)->*F)(
                        boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ) , boost::forward<Arg9>( arg9 ) , boost::forward<Arg10>( arg10 ) , boost::forward<Arg11>( arg11 ) , boost::forward<Arg12>( arg12 ) , boost::forward<Arg13>( arg13 ) , boost::forward<Arg14>( arg14 ) , boost::forward<Arg15>( arg15 ) , boost::forward<Arg16>( arg16 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        typedef boost::mpl::false_ direct_execution;
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                util::bind(util::one_shot(typename Derived::thread_function()),
                    lva, util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)) , util::get< 10>(boost::forward<Arguments>( args)) , util::get< 11>(boost::forward<Arguments>( args)) , util::get< 12>(boost::forward<Arguments>( args)) , util::get< 13>(boost::forward<Arguments>( args)) , util::get< 14>(boost::forward<Arguments>( args)) , util::get< 15>(boost::forward<Arguments>( args)) , util::get< 16>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function(
                    cont, F, get_lva<Component>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static Result
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_result_action" << 17
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component>::call(lva)) << ")";
            return (get_lva<Component>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)) , util::get< 10>(boost::forward<Arguments>( args)) , util::get< 11>(boost::forward<Arguments>( args)) , util::get< 12>(boost::forward<Arguments>( args)) , util::get< 13>(boost::forward<Arguments>( args)) , util::get< 14>(boost::forward<Arguments>( args)) , util::get< 15>(boost::forward<Arguments>( args)) , util::get< 16>(boost::forward<Arguments>( args)));
        }
    };
    
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16), typename Derived>
    struct result_action17<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16), F, Derived>
      : base_result_action17<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16), F,
            typename detail::action_type<
                result_action17<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16), F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            result_action17, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16), typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16),
            F, Derived, boost::mpl::false_>
      : result_action17<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16), F, Derived>
    {
        typedef result_action17<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16), F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16),
        typename Derived>
    struct direct_result_action17<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16), F, Derived>
      : base_result_action17<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16), F,
            typename detail::action_type<
                direct_result_action17<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16), F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_result_action17, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16), typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16),
            F, Derived, boost::mpl::true_>
      : direct_result_action17<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16), F, Derived>
    {
        typedef direct_result_action17<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16), F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16), typename Derived>
    class base_action17<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16), F, Derived>
      : public action<
            Component, util::unused_type,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type , typename util::decay<T16>::type>,
            Derived>
    {
    public:
        typedef util::unused_type result_type;
        typedef util::unused_type remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type , typename util::decay<T16>::type> arguments_type;
        typedef action<Component, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11 , typename Arg12 , typename Arg13 , typename Arg14 , typename Arg15 , typename Arg16>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9 , BOOST_FWD_REF(Arg10) arg10 , BOOST_FWD_REF(Arg11) arg11 , BOOST_FWD_REF(Arg12) arg12 , BOOST_FWD_REF(Arg13) arg13 , BOOST_FWD_REF(Arg14) arg14 , BOOST_FWD_REF(Arg15) arg15 , BOOST_FWD_REF(Arg16) arg16) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component>::call(lva)) << ")";
                    (get_lva<Component>::call(lva)->*F)(
                        boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ) , boost::forward<Arg9>( arg9 ) , boost::forward<Arg10>( arg10 ) , boost::forward<Arg11>( arg11 ) , boost::forward<Arg12>( arg12 ) , boost::forward<Arg13>( arg13 ) , boost::forward<Arg14>( arg14 ) , boost::forward<Arg15>( arg15 ) , boost::forward<Arg16>( arg16 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            
            
            return Derived::decorate_action(
                util::bind(util::one_shot(typename Derived::thread_function()), lva,
                    util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)) , util::get< 10>(boost::forward<Arguments>( args)) , util::get< 11>(boost::forward<Arguments>( args)) , util::get< 12>(boost::forward<Arguments>( args)) , util::get< 13>(boost::forward<Arguments>( args)) , util::get< 14>(boost::forward<Arguments>( args)) , util::get< 15>(boost::forward<Arguments>( args)) , util::get< 16>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function_void(
                    cont, F, get_lva<Component>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static util::unused_type
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_action" << 17
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component>::call(lva)) << ")";
            (get_lva<Component>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)) , util::get< 10>(boost::forward<Arguments>( args)) , util::get< 11>(boost::forward<Arguments>( args)) , util::get< 12>(boost::forward<Arguments>( args)) , util::get< 13>(boost::forward<Arguments>( args)) , util::get< 14>(boost::forward<Arguments>( args)) , util::get< 15>(boost::forward<Arguments>( args)) , util::get< 16>(boost::forward<Arguments>( args)));
            return util::unused;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16),
        typename Derived>
    struct action17<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16), F, Derived>
      : base_action17<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16), F,
            typename detail::action_type<
                action17<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16), F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            action17, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16), typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16),
            F, Derived, boost::mpl::false_>
      : action17<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16), F, Derived>
    {
        typedef action17<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16), F, Derived
        > type;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16),
        typename Derived>
    struct direct_action17<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16), F, Derived>
      : base_action17<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16), F,
            typename detail::action_type<
                direct_action17<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16), F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_action17, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16), typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16),
            F, Derived, boost::mpl::true_>
      : direct_action17<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16), F, Derived>
    {
        typedef direct_action17<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16), F, Derived
        > type;
    };
    
    
    template <
        typename Component,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16),
        typename Derived>
    struct result_action17<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16), F, Derived>
      : action17<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16), F, Derived>
    {};
}}
namespace hpx { namespace actions
{
    
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17), typename Derived>
    class base_result_action18<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17), F, Derived>
      : public action<
            Component, Result,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type , typename util::decay<T16>::type , typename util::decay<T17>::type>,
            Derived>
    {
    public:
        typedef Result result_type;
        typedef typename detail::remote_action_result<Result>::type
            remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type , typename util::decay<T16>::type , typename util::decay<T17>::type> arguments_type;
        typedef action<Component, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11 , typename Arg12 , typename Arg13 , typename Arg14 , typename Arg15 , typename Arg16 , typename Arg17>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9 , BOOST_FWD_REF(Arg10) arg10 , BOOST_FWD_REF(Arg11) arg11 , BOOST_FWD_REF(Arg12) arg12 , BOOST_FWD_REF(Arg13) arg13 , BOOST_FWD_REF(Arg14) arg14 , BOOST_FWD_REF(Arg15) arg15 , BOOST_FWD_REF(Arg16) arg16 , BOOST_FWD_REF(Arg17) arg17) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component>::call(lva)) << ")";
                    (get_lva<Component>::call(lva)->*F)(
                        boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ) , boost::forward<Arg9>( arg9 ) , boost::forward<Arg10>( arg10 ) , boost::forward<Arg11>( arg11 ) , boost::forward<Arg12>( arg12 ) , boost::forward<Arg13>( arg13 ) , boost::forward<Arg14>( arg14 ) , boost::forward<Arg15>( arg15 ) , boost::forward<Arg16>( arg16 ) , boost::forward<Arg17>( arg17 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        typedef boost::mpl::false_ direct_execution;
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                util::bind(util::one_shot(typename Derived::thread_function()),
                    lva, util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)) , util::get< 10>(boost::forward<Arguments>( args)) , util::get< 11>(boost::forward<Arguments>( args)) , util::get< 12>(boost::forward<Arguments>( args)) , util::get< 13>(boost::forward<Arguments>( args)) , util::get< 14>(boost::forward<Arguments>( args)) , util::get< 15>(boost::forward<Arguments>( args)) , util::get< 16>(boost::forward<Arguments>( args)) , util::get< 17>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function(
                    cont, F, get_lva<Component>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static Result
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_result_action" << 18
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component>::call(lva)) << ")";
            return (get_lva<Component>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)) , util::get< 10>(boost::forward<Arguments>( args)) , util::get< 11>(boost::forward<Arguments>( args)) , util::get< 12>(boost::forward<Arguments>( args)) , util::get< 13>(boost::forward<Arguments>( args)) , util::get< 14>(boost::forward<Arguments>( args)) , util::get< 15>(boost::forward<Arguments>( args)) , util::get< 16>(boost::forward<Arguments>( args)) , util::get< 17>(boost::forward<Arguments>( args)));
        }
    };
    
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17), typename Derived>
    struct result_action18<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17), F, Derived>
      : base_result_action18<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17), F,
            typename detail::action_type<
                result_action18<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17), F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            result_action18, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17), typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17),
            F, Derived, boost::mpl::false_>
      : result_action18<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17), F, Derived>
    {
        typedef result_action18<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17), F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17),
        typename Derived>
    struct direct_result_action18<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17), F, Derived>
      : base_result_action18<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17), F,
            typename detail::action_type<
                direct_result_action18<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17), F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_result_action18, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17), typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17),
            F, Derived, boost::mpl::true_>
      : direct_result_action18<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17), F, Derived>
    {
        typedef direct_result_action18<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17), F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17), typename Derived>
    class base_action18<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17), F, Derived>
      : public action<
            Component, util::unused_type,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type , typename util::decay<T16>::type , typename util::decay<T17>::type>,
            Derived>
    {
    public:
        typedef util::unused_type result_type;
        typedef util::unused_type remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type , typename util::decay<T16>::type , typename util::decay<T17>::type> arguments_type;
        typedef action<Component, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11 , typename Arg12 , typename Arg13 , typename Arg14 , typename Arg15 , typename Arg16 , typename Arg17>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9 , BOOST_FWD_REF(Arg10) arg10 , BOOST_FWD_REF(Arg11) arg11 , BOOST_FWD_REF(Arg12) arg12 , BOOST_FWD_REF(Arg13) arg13 , BOOST_FWD_REF(Arg14) arg14 , BOOST_FWD_REF(Arg15) arg15 , BOOST_FWD_REF(Arg16) arg16 , BOOST_FWD_REF(Arg17) arg17) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component>::call(lva)) << ")";
                    (get_lva<Component>::call(lva)->*F)(
                        boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ) , boost::forward<Arg9>( arg9 ) , boost::forward<Arg10>( arg10 ) , boost::forward<Arg11>( arg11 ) , boost::forward<Arg12>( arg12 ) , boost::forward<Arg13>( arg13 ) , boost::forward<Arg14>( arg14 ) , boost::forward<Arg15>( arg15 ) , boost::forward<Arg16>( arg16 ) , boost::forward<Arg17>( arg17 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            
            
            return Derived::decorate_action(
                util::bind(util::one_shot(typename Derived::thread_function()), lva,
                    util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)) , util::get< 10>(boost::forward<Arguments>( args)) , util::get< 11>(boost::forward<Arguments>( args)) , util::get< 12>(boost::forward<Arguments>( args)) , util::get< 13>(boost::forward<Arguments>( args)) , util::get< 14>(boost::forward<Arguments>( args)) , util::get< 15>(boost::forward<Arguments>( args)) , util::get< 16>(boost::forward<Arguments>( args)) , util::get< 17>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function_void(
                    cont, F, get_lva<Component>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static util::unused_type
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_action" << 18
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component>::call(lva)) << ")";
            (get_lva<Component>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)) , util::get< 10>(boost::forward<Arguments>( args)) , util::get< 11>(boost::forward<Arguments>( args)) , util::get< 12>(boost::forward<Arguments>( args)) , util::get< 13>(boost::forward<Arguments>( args)) , util::get< 14>(boost::forward<Arguments>( args)) , util::get< 15>(boost::forward<Arguments>( args)) , util::get< 16>(boost::forward<Arguments>( args)) , util::get< 17>(boost::forward<Arguments>( args)));
            return util::unused;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17),
        typename Derived>
    struct action18<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17), F, Derived>
      : base_action18<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17), F,
            typename detail::action_type<
                action18<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17), F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            action18, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17), typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17),
            F, Derived, boost::mpl::false_>
      : action18<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17), F, Derived>
    {
        typedef action18<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17), F, Derived
        > type;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17),
        typename Derived>
    struct direct_action18<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17), F, Derived>
      : base_action18<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17), F,
            typename detail::action_type<
                direct_action18<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17), F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_action18, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17), typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17),
            F, Derived, boost::mpl::true_>
      : direct_action18<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17), F, Derived>
    {
        typedef direct_action18<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17), F, Derived
        > type;
    };
    
    
    template <
        typename Component,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17),
        typename Derived>
    struct result_action18<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17), F, Derived>
      : action18<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17), F, Derived>
    {};
}}
namespace hpx { namespace actions
{
    
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18), typename Derived>
    class base_result_action19<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18), F, Derived>
      : public action<
            Component, Result,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type , typename util::decay<T16>::type , typename util::decay<T17>::type , typename util::decay<T18>::type>,
            Derived>
    {
    public:
        typedef Result result_type;
        typedef typename detail::remote_action_result<Result>::type
            remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type , typename util::decay<T16>::type , typename util::decay<T17>::type , typename util::decay<T18>::type> arguments_type;
        typedef action<Component, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11 , typename Arg12 , typename Arg13 , typename Arg14 , typename Arg15 , typename Arg16 , typename Arg17 , typename Arg18>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9 , BOOST_FWD_REF(Arg10) arg10 , BOOST_FWD_REF(Arg11) arg11 , BOOST_FWD_REF(Arg12) arg12 , BOOST_FWD_REF(Arg13) arg13 , BOOST_FWD_REF(Arg14) arg14 , BOOST_FWD_REF(Arg15) arg15 , BOOST_FWD_REF(Arg16) arg16 , BOOST_FWD_REF(Arg17) arg17 , BOOST_FWD_REF(Arg18) arg18) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component>::call(lva)) << ")";
                    (get_lva<Component>::call(lva)->*F)(
                        boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ) , boost::forward<Arg9>( arg9 ) , boost::forward<Arg10>( arg10 ) , boost::forward<Arg11>( arg11 ) , boost::forward<Arg12>( arg12 ) , boost::forward<Arg13>( arg13 ) , boost::forward<Arg14>( arg14 ) , boost::forward<Arg15>( arg15 ) , boost::forward<Arg16>( arg16 ) , boost::forward<Arg17>( arg17 ) , boost::forward<Arg18>( arg18 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        typedef boost::mpl::false_ direct_execution;
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                util::bind(util::one_shot(typename Derived::thread_function()),
                    lva, util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)) , util::get< 10>(boost::forward<Arguments>( args)) , util::get< 11>(boost::forward<Arguments>( args)) , util::get< 12>(boost::forward<Arguments>( args)) , util::get< 13>(boost::forward<Arguments>( args)) , util::get< 14>(boost::forward<Arguments>( args)) , util::get< 15>(boost::forward<Arguments>( args)) , util::get< 16>(boost::forward<Arguments>( args)) , util::get< 17>(boost::forward<Arguments>( args)) , util::get< 18>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function(
                    cont, F, get_lva<Component>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static Result
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_result_action" << 19
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component>::call(lva)) << ")";
            return (get_lva<Component>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)) , util::get< 10>(boost::forward<Arguments>( args)) , util::get< 11>(boost::forward<Arguments>( args)) , util::get< 12>(boost::forward<Arguments>( args)) , util::get< 13>(boost::forward<Arguments>( args)) , util::get< 14>(boost::forward<Arguments>( args)) , util::get< 15>(boost::forward<Arguments>( args)) , util::get< 16>(boost::forward<Arguments>( args)) , util::get< 17>(boost::forward<Arguments>( args)) , util::get< 18>(boost::forward<Arguments>( args)));
        }
    };
    
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18), typename Derived>
    struct result_action19<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18), F, Derived>
      : base_result_action19<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18), F,
            typename detail::action_type<
                result_action19<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18), F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            result_action19, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18), typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18),
            F, Derived, boost::mpl::false_>
      : result_action19<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18), F, Derived>
    {
        typedef result_action19<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18), F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18),
        typename Derived>
    struct direct_result_action19<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18), F, Derived>
      : base_result_action19<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18), F,
            typename detail::action_type<
                direct_result_action19<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18), F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_result_action19, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18), typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18),
            F, Derived, boost::mpl::true_>
      : direct_result_action19<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18), F, Derived>
    {
        typedef direct_result_action19<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18), F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18), typename Derived>
    class base_action19<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18), F, Derived>
      : public action<
            Component, util::unused_type,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type , typename util::decay<T16>::type , typename util::decay<T17>::type , typename util::decay<T18>::type>,
            Derived>
    {
    public:
        typedef util::unused_type result_type;
        typedef util::unused_type remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type , typename util::decay<T16>::type , typename util::decay<T17>::type , typename util::decay<T18>::type> arguments_type;
        typedef action<Component, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11 , typename Arg12 , typename Arg13 , typename Arg14 , typename Arg15 , typename Arg16 , typename Arg17 , typename Arg18>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9 , BOOST_FWD_REF(Arg10) arg10 , BOOST_FWD_REF(Arg11) arg11 , BOOST_FWD_REF(Arg12) arg12 , BOOST_FWD_REF(Arg13) arg13 , BOOST_FWD_REF(Arg14) arg14 , BOOST_FWD_REF(Arg15) arg15 , BOOST_FWD_REF(Arg16) arg16 , BOOST_FWD_REF(Arg17) arg17 , BOOST_FWD_REF(Arg18) arg18) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component>::call(lva)) << ")";
                    (get_lva<Component>::call(lva)->*F)(
                        boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ) , boost::forward<Arg9>( arg9 ) , boost::forward<Arg10>( arg10 ) , boost::forward<Arg11>( arg11 ) , boost::forward<Arg12>( arg12 ) , boost::forward<Arg13>( arg13 ) , boost::forward<Arg14>( arg14 ) , boost::forward<Arg15>( arg15 ) , boost::forward<Arg16>( arg16 ) , boost::forward<Arg17>( arg17 ) , boost::forward<Arg18>( arg18 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            
            
            return Derived::decorate_action(
                util::bind(util::one_shot(typename Derived::thread_function()), lva,
                    util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)) , util::get< 10>(boost::forward<Arguments>( args)) , util::get< 11>(boost::forward<Arguments>( args)) , util::get< 12>(boost::forward<Arguments>( args)) , util::get< 13>(boost::forward<Arguments>( args)) , util::get< 14>(boost::forward<Arguments>( args)) , util::get< 15>(boost::forward<Arguments>( args)) , util::get< 16>(boost::forward<Arguments>( args)) , util::get< 17>(boost::forward<Arguments>( args)) , util::get< 18>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function_void(
                    cont, F, get_lva<Component>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static util::unused_type
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_action" << 19
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component>::call(lva)) << ")";
            (get_lva<Component>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)) , util::get< 10>(boost::forward<Arguments>( args)) , util::get< 11>(boost::forward<Arguments>( args)) , util::get< 12>(boost::forward<Arguments>( args)) , util::get< 13>(boost::forward<Arguments>( args)) , util::get< 14>(boost::forward<Arguments>( args)) , util::get< 15>(boost::forward<Arguments>( args)) , util::get< 16>(boost::forward<Arguments>( args)) , util::get< 17>(boost::forward<Arguments>( args)) , util::get< 18>(boost::forward<Arguments>( args)));
            return util::unused;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18),
        typename Derived>
    struct action19<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18), F, Derived>
      : base_action19<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18), F,
            typename detail::action_type<
                action19<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18), F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            action19, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18), typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18),
            F, Derived, boost::mpl::false_>
      : action19<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18), F, Derived>
    {
        typedef action19<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18), F, Derived
        > type;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18),
        typename Derived>
    struct direct_action19<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18), F, Derived>
      : base_action19<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18), F,
            typename detail::action_type<
                direct_action19<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18), F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_action19, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18), typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18),
            F, Derived, boost::mpl::true_>
      : direct_action19<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18), F, Derived>
    {
        typedef direct_action19<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18), F, Derived
        > type;
    };
    
    
    template <
        typename Component,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18),
        typename Derived>
    struct result_action19<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18), F, Derived>
      : action19<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18), F, Derived>
    {};
}}
namespace hpx { namespace actions
{
    
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19), typename Derived>
    class base_result_action20<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19), F, Derived>
      : public action<
            Component, Result,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type , typename util::decay<T16>::type , typename util::decay<T17>::type , typename util::decay<T18>::type , typename util::decay<T19>::type>,
            Derived>
    {
    public:
        typedef Result result_type;
        typedef typename detail::remote_action_result<Result>::type
            remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type , typename util::decay<T16>::type , typename util::decay<T17>::type , typename util::decay<T18>::type , typename util::decay<T19>::type> arguments_type;
        typedef action<Component, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11 , typename Arg12 , typename Arg13 , typename Arg14 , typename Arg15 , typename Arg16 , typename Arg17 , typename Arg18 , typename Arg19>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9 , BOOST_FWD_REF(Arg10) arg10 , BOOST_FWD_REF(Arg11) arg11 , BOOST_FWD_REF(Arg12) arg12 , BOOST_FWD_REF(Arg13) arg13 , BOOST_FWD_REF(Arg14) arg14 , BOOST_FWD_REF(Arg15) arg15 , BOOST_FWD_REF(Arg16) arg16 , BOOST_FWD_REF(Arg17) arg17 , BOOST_FWD_REF(Arg18) arg18 , BOOST_FWD_REF(Arg19) arg19) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component>::call(lva)) << ")";
                    (get_lva<Component>::call(lva)->*F)(
                        boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ) , boost::forward<Arg9>( arg9 ) , boost::forward<Arg10>( arg10 ) , boost::forward<Arg11>( arg11 ) , boost::forward<Arg12>( arg12 ) , boost::forward<Arg13>( arg13 ) , boost::forward<Arg14>( arg14 ) , boost::forward<Arg15>( arg15 ) , boost::forward<Arg16>( arg16 ) , boost::forward<Arg17>( arg17 ) , boost::forward<Arg18>( arg18 ) , boost::forward<Arg19>( arg19 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        typedef boost::mpl::false_ direct_execution;
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                util::bind(util::one_shot(typename Derived::thread_function()),
                    lva, util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)) , util::get< 10>(boost::forward<Arguments>( args)) , util::get< 11>(boost::forward<Arguments>( args)) , util::get< 12>(boost::forward<Arguments>( args)) , util::get< 13>(boost::forward<Arguments>( args)) , util::get< 14>(boost::forward<Arguments>( args)) , util::get< 15>(boost::forward<Arguments>( args)) , util::get< 16>(boost::forward<Arguments>( args)) , util::get< 17>(boost::forward<Arguments>( args)) , util::get< 18>(boost::forward<Arguments>( args)) , util::get< 19>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function(
                    cont, F, get_lva<Component>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static Result
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_result_action" << 20
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component>::call(lva)) << ")";
            return (get_lva<Component>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)) , util::get< 10>(boost::forward<Arguments>( args)) , util::get< 11>(boost::forward<Arguments>( args)) , util::get< 12>(boost::forward<Arguments>( args)) , util::get< 13>(boost::forward<Arguments>( args)) , util::get< 14>(boost::forward<Arguments>( args)) , util::get< 15>(boost::forward<Arguments>( args)) , util::get< 16>(boost::forward<Arguments>( args)) , util::get< 17>(boost::forward<Arguments>( args)) , util::get< 18>(boost::forward<Arguments>( args)) , util::get< 19>(boost::forward<Arguments>( args)));
        }
    };
    
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19), typename Derived>
    struct result_action20<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19), F, Derived>
      : base_result_action20<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19), F,
            typename detail::action_type<
                result_action20<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19), F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            result_action20, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19), typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19),
            F, Derived, boost::mpl::false_>
      : result_action20<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19), F, Derived>
    {
        typedef result_action20<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19), F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename Result,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19),
        typename Derived>
    struct direct_result_action20<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19), F, Derived>
      : base_result_action20<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19), F,
            typename detail::action_type<
                direct_result_action20<
                    Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19), F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_result_action20, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename Result, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19,
        Result (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19), typename Derived>
    struct make_action<Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19),
            F, Derived, boost::mpl::true_>
      : direct_result_action20<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19), F, Derived>
    {
        typedef direct_result_action20<
            Result (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19), F, Derived
        > type;
    };
    
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19), typename Derived>
    class base_action20<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19), F, Derived>
      : public action<
            Component, util::unused_type,
            hpx::util::tuple<typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type , typename util::decay<T16>::type , typename util::decay<T17>::type , typename util::decay<T18>::type , typename util::decay<T19>::type>,
            Derived>
    {
    public:
        typedef util::unused_type result_type;
        typedef util::unused_type remote_result_type;
        typedef hpx::util::tuple<
            typename util::decay<T0>::type , typename util::decay<T1>::type , typename util::decay<T2>::type , typename util::decay<T3>::type , typename util::decay<T4>::type , typename util::decay<T5>::type , typename util::decay<T6>::type , typename util::decay<T7>::type , typename util::decay<T8>::type , typename util::decay<T9>::type , typename util::decay<T10>::type , typename util::decay<T11>::type , typename util::decay<T12>::type , typename util::decay<T13>::type , typename util::decay<T14>::type , typename util::decay<T15>::type , typename util::decay<T16>::type , typename util::decay<T17>::type , typename util::decay<T18>::type , typename util::decay<T19>::type> arguments_type;
        typedef action<Component, remote_result_type, arguments_type, Derived>
            base_type;
    protected:
        
        
        
        struct thread_function
        {
            typedef threads::thread_state_enum result_type;
            template <typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11 , typename Arg12 , typename Arg13 , typename Arg14 , typename Arg15 , typename Arg16 , typename Arg17 , typename Arg18 , typename Arg19>
            BOOST_FORCEINLINE result_type operator()(
                naming::address::address_type lva,
                BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9 , BOOST_FWD_REF(Arg10) arg10 , BOOST_FWD_REF(Arg11) arg11 , BOOST_FWD_REF(Arg12) arg12 , BOOST_FWD_REF(Arg13) arg13 , BOOST_FWD_REF(Arg14) arg14 , BOOST_FWD_REF(Arg15) arg15 , BOOST_FWD_REF(Arg16) arg16 , BOOST_FWD_REF(Arg17) arg17 , BOOST_FWD_REF(Arg18) arg18 , BOOST_FWD_REF(Arg19) arg19) const
            {
                try {
                    LTM_(debug) << "Executing component action("
                                << detail::get_action_name<Derived>()
                                << ") lva(" << reinterpret_cast<void const*>
                                    (get_lva<Component>::call(lva)) << ")";
                    (get_lva<Component>::call(lva)->*F)(
                        boost::forward<Arg0>( arg0 ) , boost::forward<Arg1>( arg1 ) , boost::forward<Arg2>( arg2 ) , boost::forward<Arg3>( arg3 ) , boost::forward<Arg4>( arg4 ) , boost::forward<Arg5>( arg5 ) , boost::forward<Arg6>( arg6 ) , boost::forward<Arg7>( arg7 ) , boost::forward<Arg8>( arg8 ) , boost::forward<Arg9>( arg9 ) , boost::forward<Arg10>( arg10 ) , boost::forward<Arg11>( arg11 ) , boost::forward<Arg12>( arg12 ) , boost::forward<Arg13>( arg13 ) , boost::forward<Arg14>( arg14 ) , boost::forward<Arg15>( arg15 ) , boost::forward<Arg16>( arg16 ) , boost::forward<Arg17>( arg17 ) , boost::forward<Arg18>( arg18 ) , boost::forward<Arg19>( arg19 ));
                }
                catch (hpx::thread_interrupted const&) {
                     
                }
                catch (hpx::exception const& e) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << "): " << e.what();
                    
                    hpx::report_error(boost::current_exception());
                }
                catch (...) {
                    LTM_(error)
                        << "Unhandled exception while executing component action("
                        << detail::get_action_name<Derived>()
                        << ") lva(" << reinterpret_cast<void const*>
                            (get_lva<Component>::call(lva)) << ")";
                    
                    hpx::report_error(boost::current_exception());
                }
                
                
                
                util::force_error_on_lock();
                return threads::terminated;
            }
        };
    public:
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            
            
            return Derived::decorate_action(
                util::bind(util::one_shot(typename Derived::thread_function()), lva,
                    util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)) , util::get< 10>(boost::forward<Arguments>( args)) , util::get< 11>(boost::forward<Arguments>( args)) , util::get< 12>(boost::forward<Arguments>( args)) , util::get< 13>(boost::forward<Arguments>( args)) , util::get< 14>(boost::forward<Arguments>( args)) , util::get< 15>(boost::forward<Arguments>( args)) , util::get< 16>(boost::forward<Arguments>( args)) , util::get< 17>(boost::forward<Arguments>( args)) , util::get< 18>(boost::forward<Arguments>( args)) , util::get< 19>(boost::forward<Arguments>( args))), lva);
        }
        
        
        
        
        template <typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        construct_thread_function(continuation_type& cont,
            naming::address::address_type lva, BOOST_FWD_REF(Arguments) args)
        {
            return Derived::decorate_action(
                base_type::construct_continuation_thread_object_function_void(
                    cont, F, get_lva<Component>::call(lva),
                    boost::forward<Arguments>(args)), lva);
        }
        
        template <typename Arguments>
        BOOST_FORCEINLINE static util::unused_type
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            LTM_(debug)
                << "base_action" << 20
                << "::execute_function name("
                << detail::get_action_name<Derived>()
                << ") lva(" << reinterpret_cast<void const*>(
                    get_lva<Component>::call(lva)) << ")";
            (get_lva<Component>::call(lva)->*F)(
                util::get< 0>(boost::forward<Arguments>( args)) , util::get< 1>(boost::forward<Arguments>( args)) , util::get< 2>(boost::forward<Arguments>( args)) , util::get< 3>(boost::forward<Arguments>( args)) , util::get< 4>(boost::forward<Arguments>( args)) , util::get< 5>(boost::forward<Arguments>( args)) , util::get< 6>(boost::forward<Arguments>( args)) , util::get< 7>(boost::forward<Arguments>( args)) , util::get< 8>(boost::forward<Arguments>( args)) , util::get< 9>(boost::forward<Arguments>( args)) , util::get< 10>(boost::forward<Arguments>( args)) , util::get< 11>(boost::forward<Arguments>( args)) , util::get< 12>(boost::forward<Arguments>( args)) , util::get< 13>(boost::forward<Arguments>( args)) , util::get< 14>(boost::forward<Arguments>( args)) , util::get< 15>(boost::forward<Arguments>( args)) , util::get< 16>(boost::forward<Arguments>( args)) , util::get< 17>(boost::forward<Arguments>( args)) , util::get< 18>(boost::forward<Arguments>( args)) , util::get< 19>(boost::forward<Arguments>( args)));
            return util::unused;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19),
        typename Derived>
    struct action20<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19), F, Derived>
      : base_action20<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19), F,
            typename detail::action_type<
                action20<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19), F, Derived>,
                Derived
            >::type>
    {
        typedef typename detail::action_type<
            action20, Derived
        >::type derived_type;
        typedef boost::mpl::false_ direct_execution;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19), typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19),
            F, Derived, boost::mpl::false_>
      : action20<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19), F, Derived>
    {
        typedef action20<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19), F, Derived
        > type;
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19),
        typename Derived>
    struct direct_action20<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19), F, Derived>
      : base_action20<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19), F,
            typename detail::action_type<
                direct_action20<
                    void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19), F, Derived>,
                    Derived
            >::type>
    {
        typedef typename detail::action_type<
            direct_action20, Derived
        >::type derived_type;
        typedef boost::mpl::true_ direct_execution;
        
        
        static base_action::action_type get_action_type()
        {
            return base_action::direct_action;
        }
    };
    
    template <
        typename Component, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19), typename Derived>
    struct make_action<void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19),
            F, Derived, boost::mpl::true_>
      : direct_action20<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19), F, Derived>
    {
        typedef direct_action20<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19), F, Derived
        > type;
    };
    
    
    template <
        typename Component,
        typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19,
        void (Component::*F)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19),
        typename Derived>
    struct result_action20<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19), F, Derived>
      : action20<
            void (Component::*)(T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19), F, Derived>
    {};
}}
