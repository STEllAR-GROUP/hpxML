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
