// Copyright (c) 2007-2013 Hartmut Kaiser
// Copyright (c) 2012-2013 Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This file has been automatically generated using the Boost.Wave tool.
// Do not edit manually.


namespace detail
{
    
    
    
    
    
    
    template <typename Action>
    struct continuation_thread_function_void_0
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
           >
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
           ) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                func();
                cont->trigger();
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    
    
    
    template <typename Action>
    struct construct_continuation_thread_function_voidN<Action, 0>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_void_0<Action>()),
                cont, std::forward<Func>(func)
              
                    );
        }
    };
    
    template <typename Action>
    struct continuation_thread_function_0
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
           >
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
           ) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                cont->trigger(std::forward<typename Action::result_type>(
                    func()
                ));
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    template <typename Action>
    struct construct_continuation_thread_functionN<Action, 0>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_0<Action>()),
                cont, std::forward<Func>(func)
              
                    );
        }
    };
}
namespace detail
{
    
    
    
    
    
    
    template <typename Action>
    struct continuation_thread_function_void_1
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
          , typename Arg0>
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
          , Arg0 && arg0) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                func(std::forward<Arg0>( arg0 ));
                cont->trigger();
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    
    
    
    template <typename Action>
    struct construct_continuation_thread_function_voidN<Action, 1>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_void_1<Action>()),
                cont, std::forward<Func>(func)
              ,
                    util::get< 0>(std::forward<Arguments>( args)));
        }
    };
    
    template <typename Action>
    struct continuation_thread_function_1
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
          , typename Arg0>
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
          , Arg0 && arg0) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                cont->trigger(std::forward<typename Action::result_type>(
                    func(std::forward<Arg0>( arg0 ))
                ));
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    template <typename Action>
    struct construct_continuation_thread_functionN<Action, 1>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_1<Action>()),
                cont, std::forward<Func>(func)
              ,
                    util::get< 0>(std::forward<Arguments>( args)));
        }
    };
}
namespace detail
{
    
    
    
    
    
    
    template <typename Action>
    struct continuation_thread_function_void_2
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
          , typename Arg0 , typename Arg1>
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
          , Arg0 && arg0 , Arg1 && arg1) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                func(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ));
                cont->trigger();
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    
    
    
    template <typename Action>
    struct construct_continuation_thread_function_voidN<Action, 2>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_void_2<Action>()),
                cont, std::forward<Func>(func)
              ,
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)));
        }
    };
    
    template <typename Action>
    struct continuation_thread_function_2
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
          , typename Arg0 , typename Arg1>
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
          , Arg0 && arg0 , Arg1 && arg1) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                cont->trigger(std::forward<typename Action::result_type>(
                    func(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ))
                ));
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    template <typename Action>
    struct construct_continuation_thread_functionN<Action, 2>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_2<Action>()),
                cont, std::forward<Func>(func)
              ,
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)));
        }
    };
}
namespace detail
{
    
    
    
    
    
    
    template <typename Action>
    struct continuation_thread_function_void_3
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
          , typename Arg0 , typename Arg1 , typename Arg2>
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
          , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                func(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ));
                cont->trigger();
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    
    
    
    template <typename Action>
    struct construct_continuation_thread_function_voidN<Action, 3>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_void_3<Action>()),
                cont, std::forward<Func>(func)
              ,
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)));
        }
    };
    
    template <typename Action>
    struct continuation_thread_function_3
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
          , typename Arg0 , typename Arg1 , typename Arg2>
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
          , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                cont->trigger(std::forward<typename Action::result_type>(
                    func(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ))
                ));
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    template <typename Action>
    struct construct_continuation_thread_functionN<Action, 3>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_3<Action>()),
                cont, std::forward<Func>(func)
              ,
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)));
        }
    };
}
namespace detail
{
    
    
    
    
    
    
    template <typename Action>
    struct continuation_thread_function_void_4
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
          , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3>
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
          , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                func(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ) , std::forward<Arg3>( arg3 ));
                cont->trigger();
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    
    
    
    template <typename Action>
    struct construct_continuation_thread_function_voidN<Action, 4>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_void_4<Action>()),
                cont, std::forward<Func>(func)
              ,
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args)));
        }
    };
    
    template <typename Action>
    struct continuation_thread_function_4
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
          , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3>
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
          , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                cont->trigger(std::forward<typename Action::result_type>(
                    func(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ) , std::forward<Arg3>( arg3 ))
                ));
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    template <typename Action>
    struct construct_continuation_thread_functionN<Action, 4>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_4<Action>()),
                cont, std::forward<Func>(func)
              ,
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args)));
        }
    };
}
namespace detail
{
    
    
    
    
    
    
    template <typename Action>
    struct continuation_thread_function_void_5
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
          , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4>
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
          , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                func(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ) , std::forward<Arg3>( arg3 ) , std::forward<Arg4>( arg4 ));
                cont->trigger();
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    
    
    
    template <typename Action>
    struct construct_continuation_thread_function_voidN<Action, 5>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_void_5<Action>()),
                cont, std::forward<Func>(func)
              ,
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args)) , util::get< 4>(std::forward<Arguments>( args)));
        }
    };
    
    template <typename Action>
    struct continuation_thread_function_5
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
          , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4>
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
          , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                cont->trigger(std::forward<typename Action::result_type>(
                    func(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ) , std::forward<Arg3>( arg3 ) , std::forward<Arg4>( arg4 ))
                ));
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    template <typename Action>
    struct construct_continuation_thread_functionN<Action, 5>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_5<Action>()),
                cont, std::forward<Func>(func)
              ,
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args)) , util::get< 4>(std::forward<Arguments>( args)));
        }
    };
}
namespace detail
{
    
    
    
    
    
    
    template <typename Action>
    struct continuation_thread_function_void_6
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
          , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5>
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
          , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                func(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ) , std::forward<Arg3>( arg3 ) , std::forward<Arg4>( arg4 ) , std::forward<Arg5>( arg5 ));
                cont->trigger();
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    
    
    
    template <typename Action>
    struct construct_continuation_thread_function_voidN<Action, 6>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_void_6<Action>()),
                cont, std::forward<Func>(func)
              ,
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args)) , util::get< 4>(std::forward<Arguments>( args)) , util::get< 5>(std::forward<Arguments>( args)));
        }
    };
    
    template <typename Action>
    struct continuation_thread_function_6
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
          , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5>
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
          , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                cont->trigger(std::forward<typename Action::result_type>(
                    func(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ) , std::forward<Arg3>( arg3 ) , std::forward<Arg4>( arg4 ) , std::forward<Arg5>( arg5 ))
                ));
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    template <typename Action>
    struct construct_continuation_thread_functionN<Action, 6>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_6<Action>()),
                cont, std::forward<Func>(func)
              ,
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args)) , util::get< 4>(std::forward<Arguments>( args)) , util::get< 5>(std::forward<Arguments>( args)));
        }
    };
}
namespace detail
{
    
    
    
    
    
    
    template <typename Action>
    struct continuation_thread_function_void_7
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
          , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6>
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
          , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                func(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ) , std::forward<Arg3>( arg3 ) , std::forward<Arg4>( arg4 ) , std::forward<Arg5>( arg5 ) , std::forward<Arg6>( arg6 ));
                cont->trigger();
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    
    
    
    template <typename Action>
    struct construct_continuation_thread_function_voidN<Action, 7>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_void_7<Action>()),
                cont, std::forward<Func>(func)
              ,
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args)) , util::get< 4>(std::forward<Arguments>( args)) , util::get< 5>(std::forward<Arguments>( args)) , util::get< 6>(std::forward<Arguments>( args)));
        }
    };
    
    template <typename Action>
    struct continuation_thread_function_7
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
          , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6>
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
          , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                cont->trigger(std::forward<typename Action::result_type>(
                    func(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ) , std::forward<Arg3>( arg3 ) , std::forward<Arg4>( arg4 ) , std::forward<Arg5>( arg5 ) , std::forward<Arg6>( arg6 ))
                ));
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    template <typename Action>
    struct construct_continuation_thread_functionN<Action, 7>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_7<Action>()),
                cont, std::forward<Func>(func)
              ,
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args)) , util::get< 4>(std::forward<Arguments>( args)) , util::get< 5>(std::forward<Arguments>( args)) , util::get< 6>(std::forward<Arguments>( args)));
        }
    };
}
namespace detail
{
    
    
    
    
    
    
    template <typename Action>
    struct continuation_thread_function_void_8
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
          , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7>
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
          , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                func(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ) , std::forward<Arg3>( arg3 ) , std::forward<Arg4>( arg4 ) , std::forward<Arg5>( arg5 ) , std::forward<Arg6>( arg6 ) , std::forward<Arg7>( arg7 ));
                cont->trigger();
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    
    
    
    template <typename Action>
    struct construct_continuation_thread_function_voidN<Action, 8>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_void_8<Action>()),
                cont, std::forward<Func>(func)
              ,
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args)) , util::get< 4>(std::forward<Arguments>( args)) , util::get< 5>(std::forward<Arguments>( args)) , util::get< 6>(std::forward<Arguments>( args)) , util::get< 7>(std::forward<Arguments>( args)));
        }
    };
    
    template <typename Action>
    struct continuation_thread_function_8
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
          , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7>
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
          , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                cont->trigger(std::forward<typename Action::result_type>(
                    func(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ) , std::forward<Arg3>( arg3 ) , std::forward<Arg4>( arg4 ) , std::forward<Arg5>( arg5 ) , std::forward<Arg6>( arg6 ) , std::forward<Arg7>( arg7 ))
                ));
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    template <typename Action>
    struct construct_continuation_thread_functionN<Action, 8>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_8<Action>()),
                cont, std::forward<Func>(func)
              ,
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args)) , util::get< 4>(std::forward<Arguments>( args)) , util::get< 5>(std::forward<Arguments>( args)) , util::get< 6>(std::forward<Arguments>( args)) , util::get< 7>(std::forward<Arguments>( args)));
        }
    };
}
namespace detail
{
    
    
    
    
    
    
    template <typename Action>
    struct continuation_thread_function_void_9
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
          , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8>
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
          , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                func(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ) , std::forward<Arg3>( arg3 ) , std::forward<Arg4>( arg4 ) , std::forward<Arg5>( arg5 ) , std::forward<Arg6>( arg6 ) , std::forward<Arg7>( arg7 ) , std::forward<Arg8>( arg8 ));
                cont->trigger();
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    
    
    
    template <typename Action>
    struct construct_continuation_thread_function_voidN<Action, 9>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_void_9<Action>()),
                cont, std::forward<Func>(func)
              ,
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args)) , util::get< 4>(std::forward<Arguments>( args)) , util::get< 5>(std::forward<Arguments>( args)) , util::get< 6>(std::forward<Arguments>( args)) , util::get< 7>(std::forward<Arguments>( args)) , util::get< 8>(std::forward<Arguments>( args)));
        }
    };
    
    template <typename Action>
    struct continuation_thread_function_9
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
          , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8>
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
          , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                cont->trigger(std::forward<typename Action::result_type>(
                    func(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ) , std::forward<Arg3>( arg3 ) , std::forward<Arg4>( arg4 ) , std::forward<Arg5>( arg5 ) , std::forward<Arg6>( arg6 ) , std::forward<Arg7>( arg7 ) , std::forward<Arg8>( arg8 ))
                ));
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    template <typename Action>
    struct construct_continuation_thread_functionN<Action, 9>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_9<Action>()),
                cont, std::forward<Func>(func)
              ,
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args)) , util::get< 4>(std::forward<Arguments>( args)) , util::get< 5>(std::forward<Arguments>( args)) , util::get< 6>(std::forward<Arguments>( args)) , util::get< 7>(std::forward<Arguments>( args)) , util::get< 8>(std::forward<Arguments>( args)));
        }
    };
}
namespace detail
{
    
    
    
    
    
    
    template <typename Action>
    struct continuation_thread_function_void_10
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
          , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9>
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
          , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8 , Arg9 && arg9) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                func(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ) , std::forward<Arg3>( arg3 ) , std::forward<Arg4>( arg4 ) , std::forward<Arg5>( arg5 ) , std::forward<Arg6>( arg6 ) , std::forward<Arg7>( arg7 ) , std::forward<Arg8>( arg8 ) , std::forward<Arg9>( arg9 ));
                cont->trigger();
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    
    
    
    template <typename Action>
    struct construct_continuation_thread_function_voidN<Action, 10>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_void_10<Action>()),
                cont, std::forward<Func>(func)
              ,
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args)) , util::get< 4>(std::forward<Arguments>( args)) , util::get< 5>(std::forward<Arguments>( args)) , util::get< 6>(std::forward<Arguments>( args)) , util::get< 7>(std::forward<Arguments>( args)) , util::get< 8>(std::forward<Arguments>( args)) , util::get< 9>(std::forward<Arguments>( args)));
        }
    };
    
    template <typename Action>
    struct continuation_thread_function_10
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
          , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9>
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
          , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8 , Arg9 && arg9) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                cont->trigger(std::forward<typename Action::result_type>(
                    func(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ) , std::forward<Arg3>( arg3 ) , std::forward<Arg4>( arg4 ) , std::forward<Arg5>( arg5 ) , std::forward<Arg6>( arg6 ) , std::forward<Arg7>( arg7 ) , std::forward<Arg8>( arg8 ) , std::forward<Arg9>( arg9 ))
                ));
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    template <typename Action>
    struct construct_continuation_thread_functionN<Action, 10>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_10<Action>()),
                cont, std::forward<Func>(func)
              ,
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args)) , util::get< 4>(std::forward<Arguments>( args)) , util::get< 5>(std::forward<Arguments>( args)) , util::get< 6>(std::forward<Arguments>( args)) , util::get< 7>(std::forward<Arguments>( args)) , util::get< 8>(std::forward<Arguments>( args)) , util::get< 9>(std::forward<Arguments>( args)));
        }
    };
}
namespace detail
{
    
    
    
    
    
    
    template <typename Action>
    struct continuation_thread_function_void_11
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
          , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10>
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
          , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8 , Arg9 && arg9 , Arg10 && arg10) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                func(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ) , std::forward<Arg3>( arg3 ) , std::forward<Arg4>( arg4 ) , std::forward<Arg5>( arg5 ) , std::forward<Arg6>( arg6 ) , std::forward<Arg7>( arg7 ) , std::forward<Arg8>( arg8 ) , std::forward<Arg9>( arg9 ) , std::forward<Arg10>( arg10 ));
                cont->trigger();
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    
    
    
    template <typename Action>
    struct construct_continuation_thread_function_voidN<Action, 11>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_void_11<Action>()),
                cont, std::forward<Func>(func)
              ,
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args)) , util::get< 4>(std::forward<Arguments>( args)) , util::get< 5>(std::forward<Arguments>( args)) , util::get< 6>(std::forward<Arguments>( args)) , util::get< 7>(std::forward<Arguments>( args)) , util::get< 8>(std::forward<Arguments>( args)) , util::get< 9>(std::forward<Arguments>( args)) , util::get< 10>(std::forward<Arguments>( args)));
        }
    };
    
    template <typename Action>
    struct continuation_thread_function_11
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
          , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10>
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
          , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8 , Arg9 && arg9 , Arg10 && arg10) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                cont->trigger(std::forward<typename Action::result_type>(
                    func(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ) , std::forward<Arg3>( arg3 ) , std::forward<Arg4>( arg4 ) , std::forward<Arg5>( arg5 ) , std::forward<Arg6>( arg6 ) , std::forward<Arg7>( arg7 ) , std::forward<Arg8>( arg8 ) , std::forward<Arg9>( arg9 ) , std::forward<Arg10>( arg10 ))
                ));
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    template <typename Action>
    struct construct_continuation_thread_functionN<Action, 11>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_11<Action>()),
                cont, std::forward<Func>(func)
              ,
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args)) , util::get< 4>(std::forward<Arguments>( args)) , util::get< 5>(std::forward<Arguments>( args)) , util::get< 6>(std::forward<Arguments>( args)) , util::get< 7>(std::forward<Arguments>( args)) , util::get< 8>(std::forward<Arguments>( args)) , util::get< 9>(std::forward<Arguments>( args)) , util::get< 10>(std::forward<Arguments>( args)));
        }
    };
}
namespace detail
{
    
    
    
    
    
    
    template <typename Action>
    struct continuation_thread_function_void_12
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
          , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11>
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
          , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8 , Arg9 && arg9 , Arg10 && arg10 , Arg11 && arg11) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                func(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ) , std::forward<Arg3>( arg3 ) , std::forward<Arg4>( arg4 ) , std::forward<Arg5>( arg5 ) , std::forward<Arg6>( arg6 ) , std::forward<Arg7>( arg7 ) , std::forward<Arg8>( arg8 ) , std::forward<Arg9>( arg9 ) , std::forward<Arg10>( arg10 ) , std::forward<Arg11>( arg11 ));
                cont->trigger();
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    
    
    
    template <typename Action>
    struct construct_continuation_thread_function_voidN<Action, 12>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_void_12<Action>()),
                cont, std::forward<Func>(func)
              ,
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args)) , util::get< 4>(std::forward<Arguments>( args)) , util::get< 5>(std::forward<Arguments>( args)) , util::get< 6>(std::forward<Arguments>( args)) , util::get< 7>(std::forward<Arguments>( args)) , util::get< 8>(std::forward<Arguments>( args)) , util::get< 9>(std::forward<Arguments>( args)) , util::get< 10>(std::forward<Arguments>( args)) , util::get< 11>(std::forward<Arguments>( args)));
        }
    };
    
    template <typename Action>
    struct continuation_thread_function_12
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
          , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11>
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
          , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8 , Arg9 && arg9 , Arg10 && arg10 , Arg11 && arg11) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                cont->trigger(std::forward<typename Action::result_type>(
                    func(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ) , std::forward<Arg3>( arg3 ) , std::forward<Arg4>( arg4 ) , std::forward<Arg5>( arg5 ) , std::forward<Arg6>( arg6 ) , std::forward<Arg7>( arg7 ) , std::forward<Arg8>( arg8 ) , std::forward<Arg9>( arg9 ) , std::forward<Arg10>( arg10 ) , std::forward<Arg11>( arg11 ))
                ));
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    template <typename Action>
    struct construct_continuation_thread_functionN<Action, 12>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_12<Action>()),
                cont, std::forward<Func>(func)
              ,
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args)) , util::get< 4>(std::forward<Arguments>( args)) , util::get< 5>(std::forward<Arguments>( args)) , util::get< 6>(std::forward<Arguments>( args)) , util::get< 7>(std::forward<Arguments>( args)) , util::get< 8>(std::forward<Arguments>( args)) , util::get< 9>(std::forward<Arguments>( args)) , util::get< 10>(std::forward<Arguments>( args)) , util::get< 11>(std::forward<Arguments>( args)));
        }
    };
}
namespace detail
{
    
    
    
    
    
    
    template <typename Action>
    struct continuation_thread_function_void_13
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
          , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11 , typename Arg12>
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
          , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8 , Arg9 && arg9 , Arg10 && arg10 , Arg11 && arg11 , Arg12 && arg12) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                func(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ) , std::forward<Arg3>( arg3 ) , std::forward<Arg4>( arg4 ) , std::forward<Arg5>( arg5 ) , std::forward<Arg6>( arg6 ) , std::forward<Arg7>( arg7 ) , std::forward<Arg8>( arg8 ) , std::forward<Arg9>( arg9 ) , std::forward<Arg10>( arg10 ) , std::forward<Arg11>( arg11 ) , std::forward<Arg12>( arg12 ));
                cont->trigger();
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    
    
    
    template <typename Action>
    struct construct_continuation_thread_function_voidN<Action, 13>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_void_13<Action>()),
                cont, std::forward<Func>(func)
              ,
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args)) , util::get< 4>(std::forward<Arguments>( args)) , util::get< 5>(std::forward<Arguments>( args)) , util::get< 6>(std::forward<Arguments>( args)) , util::get< 7>(std::forward<Arguments>( args)) , util::get< 8>(std::forward<Arguments>( args)) , util::get< 9>(std::forward<Arguments>( args)) , util::get< 10>(std::forward<Arguments>( args)) , util::get< 11>(std::forward<Arguments>( args)) , util::get< 12>(std::forward<Arguments>( args)));
        }
    };
    
    template <typename Action>
    struct continuation_thread_function_13
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
          , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11 , typename Arg12>
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
          , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8 , Arg9 && arg9 , Arg10 && arg10 , Arg11 && arg11 , Arg12 && arg12) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                cont->trigger(std::forward<typename Action::result_type>(
                    func(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ) , std::forward<Arg3>( arg3 ) , std::forward<Arg4>( arg4 ) , std::forward<Arg5>( arg5 ) , std::forward<Arg6>( arg6 ) , std::forward<Arg7>( arg7 ) , std::forward<Arg8>( arg8 ) , std::forward<Arg9>( arg9 ) , std::forward<Arg10>( arg10 ) , std::forward<Arg11>( arg11 ) , std::forward<Arg12>( arg12 ))
                ));
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    template <typename Action>
    struct construct_continuation_thread_functionN<Action, 13>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_13<Action>()),
                cont, std::forward<Func>(func)
              ,
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args)) , util::get< 4>(std::forward<Arguments>( args)) , util::get< 5>(std::forward<Arguments>( args)) , util::get< 6>(std::forward<Arguments>( args)) , util::get< 7>(std::forward<Arguments>( args)) , util::get< 8>(std::forward<Arguments>( args)) , util::get< 9>(std::forward<Arguments>( args)) , util::get< 10>(std::forward<Arguments>( args)) , util::get< 11>(std::forward<Arguments>( args)) , util::get< 12>(std::forward<Arguments>( args)));
        }
    };
}
namespace detail
{
    
    
    
    
    
    
    template <typename Action>
    struct continuation_thread_function_void_14
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
          , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11 , typename Arg12 , typename Arg13>
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
          , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8 , Arg9 && arg9 , Arg10 && arg10 , Arg11 && arg11 , Arg12 && arg12 , Arg13 && arg13) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                func(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ) , std::forward<Arg3>( arg3 ) , std::forward<Arg4>( arg4 ) , std::forward<Arg5>( arg5 ) , std::forward<Arg6>( arg6 ) , std::forward<Arg7>( arg7 ) , std::forward<Arg8>( arg8 ) , std::forward<Arg9>( arg9 ) , std::forward<Arg10>( arg10 ) , std::forward<Arg11>( arg11 ) , std::forward<Arg12>( arg12 ) , std::forward<Arg13>( arg13 ));
                cont->trigger();
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    
    
    
    template <typename Action>
    struct construct_continuation_thread_function_voidN<Action, 14>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_void_14<Action>()),
                cont, std::forward<Func>(func)
              ,
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args)) , util::get< 4>(std::forward<Arguments>( args)) , util::get< 5>(std::forward<Arguments>( args)) , util::get< 6>(std::forward<Arguments>( args)) , util::get< 7>(std::forward<Arguments>( args)) , util::get< 8>(std::forward<Arguments>( args)) , util::get< 9>(std::forward<Arguments>( args)) , util::get< 10>(std::forward<Arguments>( args)) , util::get< 11>(std::forward<Arguments>( args)) , util::get< 12>(std::forward<Arguments>( args)) , util::get< 13>(std::forward<Arguments>( args)));
        }
    };
    
    template <typename Action>
    struct continuation_thread_function_14
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
          , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11 , typename Arg12 , typename Arg13>
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
          , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8 , Arg9 && arg9 , Arg10 && arg10 , Arg11 && arg11 , Arg12 && arg12 , Arg13 && arg13) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                cont->trigger(std::forward<typename Action::result_type>(
                    func(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ) , std::forward<Arg3>( arg3 ) , std::forward<Arg4>( arg4 ) , std::forward<Arg5>( arg5 ) , std::forward<Arg6>( arg6 ) , std::forward<Arg7>( arg7 ) , std::forward<Arg8>( arg8 ) , std::forward<Arg9>( arg9 ) , std::forward<Arg10>( arg10 ) , std::forward<Arg11>( arg11 ) , std::forward<Arg12>( arg12 ) , std::forward<Arg13>( arg13 ))
                ));
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    template <typename Action>
    struct construct_continuation_thread_functionN<Action, 14>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_14<Action>()),
                cont, std::forward<Func>(func)
              ,
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args)) , util::get< 4>(std::forward<Arguments>( args)) , util::get< 5>(std::forward<Arguments>( args)) , util::get< 6>(std::forward<Arguments>( args)) , util::get< 7>(std::forward<Arguments>( args)) , util::get< 8>(std::forward<Arguments>( args)) , util::get< 9>(std::forward<Arguments>( args)) , util::get< 10>(std::forward<Arguments>( args)) , util::get< 11>(std::forward<Arguments>( args)) , util::get< 12>(std::forward<Arguments>( args)) , util::get< 13>(std::forward<Arguments>( args)));
        }
    };
}
namespace detail
{
    
    
    
    
    
    
    template <typename Action>
    struct continuation_thread_function_void_15
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
          , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11 , typename Arg12 , typename Arg13 , typename Arg14>
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
          , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8 , Arg9 && arg9 , Arg10 && arg10 , Arg11 && arg11 , Arg12 && arg12 , Arg13 && arg13 , Arg14 && arg14) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                func(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ) , std::forward<Arg3>( arg3 ) , std::forward<Arg4>( arg4 ) , std::forward<Arg5>( arg5 ) , std::forward<Arg6>( arg6 ) , std::forward<Arg7>( arg7 ) , std::forward<Arg8>( arg8 ) , std::forward<Arg9>( arg9 ) , std::forward<Arg10>( arg10 ) , std::forward<Arg11>( arg11 ) , std::forward<Arg12>( arg12 ) , std::forward<Arg13>( arg13 ) , std::forward<Arg14>( arg14 ));
                cont->trigger();
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    
    
    
    template <typename Action>
    struct construct_continuation_thread_function_voidN<Action, 15>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_void_15<Action>()),
                cont, std::forward<Func>(func)
              ,
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args)) , util::get< 4>(std::forward<Arguments>( args)) , util::get< 5>(std::forward<Arguments>( args)) , util::get< 6>(std::forward<Arguments>( args)) , util::get< 7>(std::forward<Arguments>( args)) , util::get< 8>(std::forward<Arguments>( args)) , util::get< 9>(std::forward<Arguments>( args)) , util::get< 10>(std::forward<Arguments>( args)) , util::get< 11>(std::forward<Arguments>( args)) , util::get< 12>(std::forward<Arguments>( args)) , util::get< 13>(std::forward<Arguments>( args)) , util::get< 14>(std::forward<Arguments>( args)));
        }
    };
    
    template <typename Action>
    struct continuation_thread_function_15
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
          , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11 , typename Arg12 , typename Arg13 , typename Arg14>
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
          , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8 , Arg9 && arg9 , Arg10 && arg10 , Arg11 && arg11 , Arg12 && arg12 , Arg13 && arg13 , Arg14 && arg14) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                cont->trigger(std::forward<typename Action::result_type>(
                    func(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ) , std::forward<Arg3>( arg3 ) , std::forward<Arg4>( arg4 ) , std::forward<Arg5>( arg5 ) , std::forward<Arg6>( arg6 ) , std::forward<Arg7>( arg7 ) , std::forward<Arg8>( arg8 ) , std::forward<Arg9>( arg9 ) , std::forward<Arg10>( arg10 ) , std::forward<Arg11>( arg11 ) , std::forward<Arg12>( arg12 ) , std::forward<Arg13>( arg13 ) , std::forward<Arg14>( arg14 ))
                ));
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    template <typename Action>
    struct construct_continuation_thread_functionN<Action, 15>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_15<Action>()),
                cont, std::forward<Func>(func)
              ,
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args)) , util::get< 4>(std::forward<Arguments>( args)) , util::get< 5>(std::forward<Arguments>( args)) , util::get< 6>(std::forward<Arguments>( args)) , util::get< 7>(std::forward<Arguments>( args)) , util::get< 8>(std::forward<Arguments>( args)) , util::get< 9>(std::forward<Arguments>( args)) , util::get< 10>(std::forward<Arguments>( args)) , util::get< 11>(std::forward<Arguments>( args)) , util::get< 12>(std::forward<Arguments>( args)) , util::get< 13>(std::forward<Arguments>( args)) , util::get< 14>(std::forward<Arguments>( args)));
        }
    };
}
namespace detail
{
    
    
    
    
    
    
    template <typename Action>
    struct continuation_thread_function_void_16
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
          , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11 , typename Arg12 , typename Arg13 , typename Arg14 , typename Arg15>
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
          , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8 , Arg9 && arg9 , Arg10 && arg10 , Arg11 && arg11 , Arg12 && arg12 , Arg13 && arg13 , Arg14 && arg14 , Arg15 && arg15) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                func(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ) , std::forward<Arg3>( arg3 ) , std::forward<Arg4>( arg4 ) , std::forward<Arg5>( arg5 ) , std::forward<Arg6>( arg6 ) , std::forward<Arg7>( arg7 ) , std::forward<Arg8>( arg8 ) , std::forward<Arg9>( arg9 ) , std::forward<Arg10>( arg10 ) , std::forward<Arg11>( arg11 ) , std::forward<Arg12>( arg12 ) , std::forward<Arg13>( arg13 ) , std::forward<Arg14>( arg14 ) , std::forward<Arg15>( arg15 ));
                cont->trigger();
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    
    
    
    template <typename Action>
    struct construct_continuation_thread_function_voidN<Action, 16>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_void_16<Action>()),
                cont, std::forward<Func>(func)
              ,
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args)) , util::get< 4>(std::forward<Arguments>( args)) , util::get< 5>(std::forward<Arguments>( args)) , util::get< 6>(std::forward<Arguments>( args)) , util::get< 7>(std::forward<Arguments>( args)) , util::get< 8>(std::forward<Arguments>( args)) , util::get< 9>(std::forward<Arguments>( args)) , util::get< 10>(std::forward<Arguments>( args)) , util::get< 11>(std::forward<Arguments>( args)) , util::get< 12>(std::forward<Arguments>( args)) , util::get< 13>(std::forward<Arguments>( args)) , util::get< 14>(std::forward<Arguments>( args)) , util::get< 15>(std::forward<Arguments>( args)));
        }
    };
    
    template <typename Action>
    struct continuation_thread_function_16
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
          , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11 , typename Arg12 , typename Arg13 , typename Arg14 , typename Arg15>
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
          , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8 , Arg9 && arg9 , Arg10 && arg10 , Arg11 && arg11 , Arg12 && arg12 , Arg13 && arg13 , Arg14 && arg14 , Arg15 && arg15) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                cont->trigger(std::forward<typename Action::result_type>(
                    func(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ) , std::forward<Arg3>( arg3 ) , std::forward<Arg4>( arg4 ) , std::forward<Arg5>( arg5 ) , std::forward<Arg6>( arg6 ) , std::forward<Arg7>( arg7 ) , std::forward<Arg8>( arg8 ) , std::forward<Arg9>( arg9 ) , std::forward<Arg10>( arg10 ) , std::forward<Arg11>( arg11 ) , std::forward<Arg12>( arg12 ) , std::forward<Arg13>( arg13 ) , std::forward<Arg14>( arg14 ) , std::forward<Arg15>( arg15 ))
                ));
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    template <typename Action>
    struct construct_continuation_thread_functionN<Action, 16>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_16<Action>()),
                cont, std::forward<Func>(func)
              ,
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args)) , util::get< 4>(std::forward<Arguments>( args)) , util::get< 5>(std::forward<Arguments>( args)) , util::get< 6>(std::forward<Arguments>( args)) , util::get< 7>(std::forward<Arguments>( args)) , util::get< 8>(std::forward<Arguments>( args)) , util::get< 9>(std::forward<Arguments>( args)) , util::get< 10>(std::forward<Arguments>( args)) , util::get< 11>(std::forward<Arguments>( args)) , util::get< 12>(std::forward<Arguments>( args)) , util::get< 13>(std::forward<Arguments>( args)) , util::get< 14>(std::forward<Arguments>( args)) , util::get< 15>(std::forward<Arguments>( args)));
        }
    };
}
namespace detail
{
    
    
    
    
    
    
    template <typename Action>
    struct continuation_thread_function_void_17
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
          , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11 , typename Arg12 , typename Arg13 , typename Arg14 , typename Arg15 , typename Arg16>
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
          , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8 , Arg9 && arg9 , Arg10 && arg10 , Arg11 && arg11 , Arg12 && arg12 , Arg13 && arg13 , Arg14 && arg14 , Arg15 && arg15 , Arg16 && arg16) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                func(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ) , std::forward<Arg3>( arg3 ) , std::forward<Arg4>( arg4 ) , std::forward<Arg5>( arg5 ) , std::forward<Arg6>( arg6 ) , std::forward<Arg7>( arg7 ) , std::forward<Arg8>( arg8 ) , std::forward<Arg9>( arg9 ) , std::forward<Arg10>( arg10 ) , std::forward<Arg11>( arg11 ) , std::forward<Arg12>( arg12 ) , std::forward<Arg13>( arg13 ) , std::forward<Arg14>( arg14 ) , std::forward<Arg15>( arg15 ) , std::forward<Arg16>( arg16 ));
                cont->trigger();
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    
    
    
    template <typename Action>
    struct construct_continuation_thread_function_voidN<Action, 17>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_void_17<Action>()),
                cont, std::forward<Func>(func)
              ,
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args)) , util::get< 4>(std::forward<Arguments>( args)) , util::get< 5>(std::forward<Arguments>( args)) , util::get< 6>(std::forward<Arguments>( args)) , util::get< 7>(std::forward<Arguments>( args)) , util::get< 8>(std::forward<Arguments>( args)) , util::get< 9>(std::forward<Arguments>( args)) , util::get< 10>(std::forward<Arguments>( args)) , util::get< 11>(std::forward<Arguments>( args)) , util::get< 12>(std::forward<Arguments>( args)) , util::get< 13>(std::forward<Arguments>( args)) , util::get< 14>(std::forward<Arguments>( args)) , util::get< 15>(std::forward<Arguments>( args)) , util::get< 16>(std::forward<Arguments>( args)));
        }
    };
    
    template <typename Action>
    struct continuation_thread_function_17
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
          , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11 , typename Arg12 , typename Arg13 , typename Arg14 , typename Arg15 , typename Arg16>
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
          , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8 , Arg9 && arg9 , Arg10 && arg10 , Arg11 && arg11 , Arg12 && arg12 , Arg13 && arg13 , Arg14 && arg14 , Arg15 && arg15 , Arg16 && arg16) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                cont->trigger(std::forward<typename Action::result_type>(
                    func(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ) , std::forward<Arg3>( arg3 ) , std::forward<Arg4>( arg4 ) , std::forward<Arg5>( arg5 ) , std::forward<Arg6>( arg6 ) , std::forward<Arg7>( arg7 ) , std::forward<Arg8>( arg8 ) , std::forward<Arg9>( arg9 ) , std::forward<Arg10>( arg10 ) , std::forward<Arg11>( arg11 ) , std::forward<Arg12>( arg12 ) , std::forward<Arg13>( arg13 ) , std::forward<Arg14>( arg14 ) , std::forward<Arg15>( arg15 ) , std::forward<Arg16>( arg16 ))
                ));
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    template <typename Action>
    struct construct_continuation_thread_functionN<Action, 17>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_17<Action>()),
                cont, std::forward<Func>(func)
              ,
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args)) , util::get< 4>(std::forward<Arguments>( args)) , util::get< 5>(std::forward<Arguments>( args)) , util::get< 6>(std::forward<Arguments>( args)) , util::get< 7>(std::forward<Arguments>( args)) , util::get< 8>(std::forward<Arguments>( args)) , util::get< 9>(std::forward<Arguments>( args)) , util::get< 10>(std::forward<Arguments>( args)) , util::get< 11>(std::forward<Arguments>( args)) , util::get< 12>(std::forward<Arguments>( args)) , util::get< 13>(std::forward<Arguments>( args)) , util::get< 14>(std::forward<Arguments>( args)) , util::get< 15>(std::forward<Arguments>( args)) , util::get< 16>(std::forward<Arguments>( args)));
        }
    };
}
namespace detail
{
    
    
    
    
    
    
    template <typename Action>
    struct continuation_thread_function_void_18
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
          , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11 , typename Arg12 , typename Arg13 , typename Arg14 , typename Arg15 , typename Arg16 , typename Arg17>
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
          , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8 , Arg9 && arg9 , Arg10 && arg10 , Arg11 && arg11 , Arg12 && arg12 , Arg13 && arg13 , Arg14 && arg14 , Arg15 && arg15 , Arg16 && arg16 , Arg17 && arg17) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                func(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ) , std::forward<Arg3>( arg3 ) , std::forward<Arg4>( arg4 ) , std::forward<Arg5>( arg5 ) , std::forward<Arg6>( arg6 ) , std::forward<Arg7>( arg7 ) , std::forward<Arg8>( arg8 ) , std::forward<Arg9>( arg9 ) , std::forward<Arg10>( arg10 ) , std::forward<Arg11>( arg11 ) , std::forward<Arg12>( arg12 ) , std::forward<Arg13>( arg13 ) , std::forward<Arg14>( arg14 ) , std::forward<Arg15>( arg15 ) , std::forward<Arg16>( arg16 ) , std::forward<Arg17>( arg17 ));
                cont->trigger();
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    
    
    
    template <typename Action>
    struct construct_continuation_thread_function_voidN<Action, 18>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_void_18<Action>()),
                cont, std::forward<Func>(func)
              ,
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args)) , util::get< 4>(std::forward<Arguments>( args)) , util::get< 5>(std::forward<Arguments>( args)) , util::get< 6>(std::forward<Arguments>( args)) , util::get< 7>(std::forward<Arguments>( args)) , util::get< 8>(std::forward<Arguments>( args)) , util::get< 9>(std::forward<Arguments>( args)) , util::get< 10>(std::forward<Arguments>( args)) , util::get< 11>(std::forward<Arguments>( args)) , util::get< 12>(std::forward<Arguments>( args)) , util::get< 13>(std::forward<Arguments>( args)) , util::get< 14>(std::forward<Arguments>( args)) , util::get< 15>(std::forward<Arguments>( args)) , util::get< 16>(std::forward<Arguments>( args)) , util::get< 17>(std::forward<Arguments>( args)));
        }
    };
    
    template <typename Action>
    struct continuation_thread_function_18
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
          , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11 , typename Arg12 , typename Arg13 , typename Arg14 , typename Arg15 , typename Arg16 , typename Arg17>
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
          , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8 , Arg9 && arg9 , Arg10 && arg10 , Arg11 && arg11 , Arg12 && arg12 , Arg13 && arg13 , Arg14 && arg14 , Arg15 && arg15 , Arg16 && arg16 , Arg17 && arg17) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                cont->trigger(std::forward<typename Action::result_type>(
                    func(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ) , std::forward<Arg3>( arg3 ) , std::forward<Arg4>( arg4 ) , std::forward<Arg5>( arg5 ) , std::forward<Arg6>( arg6 ) , std::forward<Arg7>( arg7 ) , std::forward<Arg8>( arg8 ) , std::forward<Arg9>( arg9 ) , std::forward<Arg10>( arg10 ) , std::forward<Arg11>( arg11 ) , std::forward<Arg12>( arg12 ) , std::forward<Arg13>( arg13 ) , std::forward<Arg14>( arg14 ) , std::forward<Arg15>( arg15 ) , std::forward<Arg16>( arg16 ) , std::forward<Arg17>( arg17 ))
                ));
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    template <typename Action>
    struct construct_continuation_thread_functionN<Action, 18>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_18<Action>()),
                cont, std::forward<Func>(func)
              ,
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args)) , util::get< 4>(std::forward<Arguments>( args)) , util::get< 5>(std::forward<Arguments>( args)) , util::get< 6>(std::forward<Arguments>( args)) , util::get< 7>(std::forward<Arguments>( args)) , util::get< 8>(std::forward<Arguments>( args)) , util::get< 9>(std::forward<Arguments>( args)) , util::get< 10>(std::forward<Arguments>( args)) , util::get< 11>(std::forward<Arguments>( args)) , util::get< 12>(std::forward<Arguments>( args)) , util::get< 13>(std::forward<Arguments>( args)) , util::get< 14>(std::forward<Arguments>( args)) , util::get< 15>(std::forward<Arguments>( args)) , util::get< 16>(std::forward<Arguments>( args)) , util::get< 17>(std::forward<Arguments>( args)));
        }
    };
}
namespace detail
{
    
    
    
    
    
    
    template <typename Action>
    struct continuation_thread_function_void_19
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
          , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11 , typename Arg12 , typename Arg13 , typename Arg14 , typename Arg15 , typename Arg16 , typename Arg17 , typename Arg18>
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
          , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8 , Arg9 && arg9 , Arg10 && arg10 , Arg11 && arg11 , Arg12 && arg12 , Arg13 && arg13 , Arg14 && arg14 , Arg15 && arg15 , Arg16 && arg16 , Arg17 && arg17 , Arg18 && arg18) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                func(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ) , std::forward<Arg3>( arg3 ) , std::forward<Arg4>( arg4 ) , std::forward<Arg5>( arg5 ) , std::forward<Arg6>( arg6 ) , std::forward<Arg7>( arg7 ) , std::forward<Arg8>( arg8 ) , std::forward<Arg9>( arg9 ) , std::forward<Arg10>( arg10 ) , std::forward<Arg11>( arg11 ) , std::forward<Arg12>( arg12 ) , std::forward<Arg13>( arg13 ) , std::forward<Arg14>( arg14 ) , std::forward<Arg15>( arg15 ) , std::forward<Arg16>( arg16 ) , std::forward<Arg17>( arg17 ) , std::forward<Arg18>( arg18 ));
                cont->trigger();
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    
    
    
    template <typename Action>
    struct construct_continuation_thread_function_voidN<Action, 19>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_void_19<Action>()),
                cont, std::forward<Func>(func)
              ,
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args)) , util::get< 4>(std::forward<Arguments>( args)) , util::get< 5>(std::forward<Arguments>( args)) , util::get< 6>(std::forward<Arguments>( args)) , util::get< 7>(std::forward<Arguments>( args)) , util::get< 8>(std::forward<Arguments>( args)) , util::get< 9>(std::forward<Arguments>( args)) , util::get< 10>(std::forward<Arguments>( args)) , util::get< 11>(std::forward<Arguments>( args)) , util::get< 12>(std::forward<Arguments>( args)) , util::get< 13>(std::forward<Arguments>( args)) , util::get< 14>(std::forward<Arguments>( args)) , util::get< 15>(std::forward<Arguments>( args)) , util::get< 16>(std::forward<Arguments>( args)) , util::get< 17>(std::forward<Arguments>( args)) , util::get< 18>(std::forward<Arguments>( args)));
        }
    };
    
    template <typename Action>
    struct continuation_thread_function_19
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
          , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11 , typename Arg12 , typename Arg13 , typename Arg14 , typename Arg15 , typename Arg16 , typename Arg17 , typename Arg18>
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
          , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8 , Arg9 && arg9 , Arg10 && arg10 , Arg11 && arg11 , Arg12 && arg12 , Arg13 && arg13 , Arg14 && arg14 , Arg15 && arg15 , Arg16 && arg16 , Arg17 && arg17 , Arg18 && arg18) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                cont->trigger(std::forward<typename Action::result_type>(
                    func(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ) , std::forward<Arg3>( arg3 ) , std::forward<Arg4>( arg4 ) , std::forward<Arg5>( arg5 ) , std::forward<Arg6>( arg6 ) , std::forward<Arg7>( arg7 ) , std::forward<Arg8>( arg8 ) , std::forward<Arg9>( arg9 ) , std::forward<Arg10>( arg10 ) , std::forward<Arg11>( arg11 ) , std::forward<Arg12>( arg12 ) , std::forward<Arg13>( arg13 ) , std::forward<Arg14>( arg14 ) , std::forward<Arg15>( arg15 ) , std::forward<Arg16>( arg16 ) , std::forward<Arg17>( arg17 ) , std::forward<Arg18>( arg18 ))
                ));
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    template <typename Action>
    struct construct_continuation_thread_functionN<Action, 19>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_19<Action>()),
                cont, std::forward<Func>(func)
              ,
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args)) , util::get< 4>(std::forward<Arguments>( args)) , util::get< 5>(std::forward<Arguments>( args)) , util::get< 6>(std::forward<Arguments>( args)) , util::get< 7>(std::forward<Arguments>( args)) , util::get< 8>(std::forward<Arguments>( args)) , util::get< 9>(std::forward<Arguments>( args)) , util::get< 10>(std::forward<Arguments>( args)) , util::get< 11>(std::forward<Arguments>( args)) , util::get< 12>(std::forward<Arguments>( args)) , util::get< 13>(std::forward<Arguments>( args)) , util::get< 14>(std::forward<Arguments>( args)) , util::get< 15>(std::forward<Arguments>( args)) , util::get< 16>(std::forward<Arguments>( args)) , util::get< 17>(std::forward<Arguments>( args)) , util::get< 18>(std::forward<Arguments>( args)));
        }
    };
}
namespace detail
{
    
    
    
    
    
    
    template <typename Action>
    struct continuation_thread_function_void_20
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
          , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11 , typename Arg12 , typename Arg13 , typename Arg14 , typename Arg15 , typename Arg16 , typename Arg17 , typename Arg18 , typename Arg19>
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
          , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8 , Arg9 && arg9 , Arg10 && arg10 , Arg11 && arg11 , Arg12 && arg12 , Arg13 && arg13 , Arg14 && arg14 , Arg15 && arg15 , Arg16 && arg16 , Arg17 && arg17 , Arg18 && arg18 , Arg19 && arg19) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                func(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ) , std::forward<Arg3>( arg3 ) , std::forward<Arg4>( arg4 ) , std::forward<Arg5>( arg5 ) , std::forward<Arg6>( arg6 ) , std::forward<Arg7>( arg7 ) , std::forward<Arg8>( arg8 ) , std::forward<Arg9>( arg9 ) , std::forward<Arg10>( arg10 ) , std::forward<Arg11>( arg11 ) , std::forward<Arg12>( arg12 ) , std::forward<Arg13>( arg13 ) , std::forward<Arg14>( arg14 ) , std::forward<Arg15>( arg15 ) , std::forward<Arg16>( arg16 ) , std::forward<Arg17>( arg17 ) , std::forward<Arg18>( arg18 ) , std::forward<Arg19>( arg19 ));
                cont->trigger();
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    
    
    
    template <typename Action>
    struct construct_continuation_thread_function_voidN<Action, 20>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_void_20<Action>()),
                cont, std::forward<Func>(func)
              ,
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args)) , util::get< 4>(std::forward<Arguments>( args)) , util::get< 5>(std::forward<Arguments>( args)) , util::get< 6>(std::forward<Arguments>( args)) , util::get< 7>(std::forward<Arguments>( args)) , util::get< 8>(std::forward<Arguments>( args)) , util::get< 9>(std::forward<Arguments>( args)) , util::get< 10>(std::forward<Arguments>( args)) , util::get< 11>(std::forward<Arguments>( args)) , util::get< 12>(std::forward<Arguments>( args)) , util::get< 13>(std::forward<Arguments>( args)) , util::get< 14>(std::forward<Arguments>( args)) , util::get< 15>(std::forward<Arguments>( args)) , util::get< 16>(std::forward<Arguments>( args)) , util::get< 17>(std::forward<Arguments>( args)) , util::get< 18>(std::forward<Arguments>( args)) , util::get< 19>(std::forward<Arguments>( args)));
        }
    };
    
    template <typename Action>
    struct continuation_thread_function_20
    {
        typedef threads::thread_state_enum result_type;
        template <typename Func
          , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 , typename Arg10 , typename Arg11 , typename Arg12 , typename Arg13 , typename Arg14 , typename Arg15 , typename Arg16 , typename Arg17 , typename Arg18 , typename Arg19>
        BOOST_FORCEINLINE result_type operator()(
            continuation_type cont, Func const& func
          , Arg0 && arg0 , Arg1 && arg1 , Arg2 && arg2 , Arg3 && arg3 , Arg4 && arg4 , Arg5 && arg5 , Arg6 && arg6 , Arg7 && arg7 , Arg8 && arg8 , Arg9 && arg9 , Arg10 && arg10 , Arg11 && arg11 , Arg12 && arg12 , Arg13 && arg13 , Arg14 && arg14 , Arg15 && arg15 , Arg16 && arg16 , Arg17 && arg17 , Arg18 && arg18 , Arg19 && arg19) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                cont->trigger(std::forward<typename Action::result_type>(
                    func(std::forward<Arg0>( arg0 ) , std::forward<Arg1>( arg1 ) , std::forward<Arg2>( arg2 ) , std::forward<Arg3>( arg3 ) , std::forward<Arg4>( arg4 ) , std::forward<Arg5>( arg5 ) , std::forward<Arg6>( arg6 ) , std::forward<Arg7>( arg7 ) , std::forward<Arg8>( arg8 ) , std::forward<Arg9>( arg9 ) , std::forward<Arg10>( arg10 ) , std::forward<Arg11>( arg11 ) , std::forward<Arg12>( arg12 ) , std::forward<Arg13>( arg13 ) , std::forward<Arg14>( arg14 ) , std::forward<Arg15>( arg15 ) , std::forward<Arg16>( arg16 ) , std::forward<Arg17>( arg17 ) , std::forward<Arg18>( arg18 ) , std::forward<Arg19>( arg19 ))
                ));
            }
            catch (...) {
                
                cont->trigger_error(boost::current_exception());
            }
            return threads::terminated;
        }
    };
    template <typename Action>
    struct construct_continuation_thread_functionN<Action, 20>
    {
        template <typename Func, typename Arguments>
        static HPX_STD_FUNCTION<threads::thread_function_type>
        call(continuation_type cont, Func && func,
            Arguments && args)
        {
            return util::bind(util::one_shot(
                continuation_thread_function_20<Action>()),
                cont, std::forward<Func>(func)
              ,
                    util::get< 0>(std::forward<Arguments>( args)) , util::get< 1>(std::forward<Arguments>( args)) , util::get< 2>(std::forward<Arguments>( args)) , util::get< 3>(std::forward<Arguments>( args)) , util::get< 4>(std::forward<Arguments>( args)) , util::get< 5>(std::forward<Arguments>( args)) , util::get< 6>(std::forward<Arguments>( args)) , util::get< 7>(std::forward<Arguments>( args)) , util::get< 8>(std::forward<Arguments>( args)) , util::get< 9>(std::forward<Arguments>( args)) , util::get< 10>(std::forward<Arguments>( args)) , util::get< 11>(std::forward<Arguments>( args)) , util::get< 12>(std::forward<Arguments>( args)) , util::get< 13>(std::forward<Arguments>( args)) , util::get< 14>(std::forward<Arguments>( args)) , util::get< 15>(std::forward<Arguments>( args)) , util::get< 16>(std::forward<Arguments>( args)) , util::get< 17>(std::forward<Arguments>( args)) , util::get< 18>(std::forward<Arguments>( args)) , util::get< 19>(std::forward<Arguments>( args)));
        }
    };
}
