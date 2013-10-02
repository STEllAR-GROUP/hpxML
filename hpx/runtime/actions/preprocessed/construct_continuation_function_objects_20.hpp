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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_void_0<Action>(),
                cont, boost::forward<Func>(func)
              
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
                
                
                
                
                cont->trigger(boost::move(
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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_0<Action>(),
                cont, boost::forward<Func>(func)
              
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
          , BOOST_FWD_REF(Arg0) arg0) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                
                
                
                
                func(boost::move(arg0));
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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_void_1<Action>(),
                cont, boost::forward<Func>(func)
              ,
                    boost::forward< typename util::remove_reference<Arguments>::type:: member_type0>( args. a0));
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
          , BOOST_FWD_REF(Arg0) arg0) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                
                
                
                
                cont->trigger(boost::move(
                    func(boost::move(arg0))
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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_1<Action>(),
                cont, boost::forward<Func>(func)
              ,
                    boost::forward< typename util::remove_reference<Arguments>::type:: member_type0>( args. a0));
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
          , BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                
                
                
                
                func(boost::move(arg0) , boost::move(arg1));
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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_void_2<Action>(),
                cont, boost::forward<Func>(func)
              ,
                    boost::forward< typename util::remove_reference<Arguments>::type:: member_type0>( args. a0) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type1>( args. a1));
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
          , BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                
                
                
                
                cont->trigger(boost::move(
                    func(boost::move(arg0) , boost::move(arg1))
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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_2<Action>(),
                cont, boost::forward<Func>(func)
              ,
                    boost::forward< typename util::remove_reference<Arguments>::type:: member_type0>( args. a0) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type1>( args. a1));
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
          , BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                
                
                
                
                func(boost::move(arg0) , boost::move(arg1) , boost::move(arg2));
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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_void_3<Action>(),
                cont, boost::forward<Func>(func)
              ,
                    boost::forward< typename util::remove_reference<Arguments>::type:: member_type0>( args. a0) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type1>( args. a1) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type2>( args. a2));
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
          , BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                
                
                
                
                cont->trigger(boost::move(
                    func(boost::move(arg0) , boost::move(arg1) , boost::move(arg2))
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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_3<Action>(),
                cont, boost::forward<Func>(func)
              ,
                    boost::forward< typename util::remove_reference<Arguments>::type:: member_type0>( args. a0) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type1>( args. a1) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type2>( args. a2));
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
          , BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                
                
                
                
                func(boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3));
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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_void_4<Action>(),
                cont, boost::forward<Func>(func)
              ,
                    boost::forward< typename util::remove_reference<Arguments>::type:: member_type0>( args. a0) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type1>( args. a1) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type2>( args. a2) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type3>( args. a3));
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
          , BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                
                
                
                
                cont->trigger(boost::move(
                    func(boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3))
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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_4<Action>(),
                cont, boost::forward<Func>(func)
              ,
                    boost::forward< typename util::remove_reference<Arguments>::type:: member_type0>( args. a0) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type1>( args. a1) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type2>( args. a2) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type3>( args. a3));
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
          , BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                
                
                
                
                func(boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4));
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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_void_5<Action>(),
                cont, boost::forward<Func>(func)
              ,
                    boost::forward< typename util::remove_reference<Arguments>::type:: member_type0>( args. a0) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type1>( args. a1) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type2>( args. a2) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type3>( args. a3) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type4>( args. a4));
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
          , BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                
                
                
                
                cont->trigger(boost::move(
                    func(boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4))
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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_5<Action>(),
                cont, boost::forward<Func>(func)
              ,
                    boost::forward< typename util::remove_reference<Arguments>::type:: member_type0>( args. a0) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type1>( args. a1) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type2>( args. a2) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type3>( args. a3) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type4>( args. a4));
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
          , BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                
                
                
                
                func(boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4) , boost::move(arg5));
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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_void_6<Action>(),
                cont, boost::forward<Func>(func)
              ,
                    boost::forward< typename util::remove_reference<Arguments>::type:: member_type0>( args. a0) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type1>( args. a1) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type2>( args. a2) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type3>( args. a3) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type4>( args. a4) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type5>( args. a5));
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
          , BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                
                
                
                
                cont->trigger(boost::move(
                    func(boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4) , boost::move(arg5))
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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_6<Action>(),
                cont, boost::forward<Func>(func)
              ,
                    boost::forward< typename util::remove_reference<Arguments>::type:: member_type0>( args. a0) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type1>( args. a1) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type2>( args. a2) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type3>( args. a3) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type4>( args. a4) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type5>( args. a5));
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
          , BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                
                
                
                
                func(boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4) , boost::move(arg5) , boost::move(arg6));
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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_void_7<Action>(),
                cont, boost::forward<Func>(func)
              ,
                    boost::forward< typename util::remove_reference<Arguments>::type:: member_type0>( args. a0) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type1>( args. a1) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type2>( args. a2) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type3>( args. a3) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type4>( args. a4) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type5>( args. a5) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type6>( args. a6));
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
          , BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                
                
                
                
                cont->trigger(boost::move(
                    func(boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4) , boost::move(arg5) , boost::move(arg6))
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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_7<Action>(),
                cont, boost::forward<Func>(func)
              ,
                    boost::forward< typename util::remove_reference<Arguments>::type:: member_type0>( args. a0) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type1>( args. a1) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type2>( args. a2) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type3>( args. a3) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type4>( args. a4) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type5>( args. a5) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type6>( args. a6));
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
          , BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                
                
                
                
                func(boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4) , boost::move(arg5) , boost::move(arg6) , boost::move(arg7));
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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_void_8<Action>(),
                cont, boost::forward<Func>(func)
              ,
                    boost::forward< typename util::remove_reference<Arguments>::type:: member_type0>( args. a0) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type1>( args. a1) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type2>( args. a2) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type3>( args. a3) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type4>( args. a4) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type5>( args. a5) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type6>( args. a6) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type7>( args. a7));
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
          , BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                
                
                
                
                cont->trigger(boost::move(
                    func(boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4) , boost::move(arg5) , boost::move(arg6) , boost::move(arg7))
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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_8<Action>(),
                cont, boost::forward<Func>(func)
              ,
                    boost::forward< typename util::remove_reference<Arguments>::type:: member_type0>( args. a0) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type1>( args. a1) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type2>( args. a2) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type3>( args. a3) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type4>( args. a4) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type5>( args. a5) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type6>( args. a6) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type7>( args. a7));
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
          , BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                
                
                
                
                func(boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4) , boost::move(arg5) , boost::move(arg6) , boost::move(arg7) , boost::move(arg8));
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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_void_9<Action>(),
                cont, boost::forward<Func>(func)
              ,
                    boost::forward< typename util::remove_reference<Arguments>::type:: member_type0>( args. a0) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type1>( args. a1) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type2>( args. a2) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type3>( args. a3) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type4>( args. a4) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type5>( args. a5) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type6>( args. a6) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type7>( args. a7) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type8>( args. a8));
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
          , BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                
                
                
                
                cont->trigger(boost::move(
                    func(boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4) , boost::move(arg5) , boost::move(arg6) , boost::move(arg7) , boost::move(arg8))
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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_9<Action>(),
                cont, boost::forward<Func>(func)
              ,
                    boost::forward< typename util::remove_reference<Arguments>::type:: member_type0>( args. a0) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type1>( args. a1) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type2>( args. a2) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type3>( args. a3) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type4>( args. a4) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type5>( args. a5) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type6>( args. a6) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type7>( args. a7) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type8>( args. a8));
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
          , BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                
                
                
                
                func(boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4) , boost::move(arg5) , boost::move(arg6) , boost::move(arg7) , boost::move(arg8) , boost::move(arg9));
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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_void_10<Action>(),
                cont, boost::forward<Func>(func)
              ,
                    boost::forward< typename util::remove_reference<Arguments>::type:: member_type0>( args. a0) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type1>( args. a1) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type2>( args. a2) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type3>( args. a3) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type4>( args. a4) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type5>( args. a5) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type6>( args. a6) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type7>( args. a7) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type8>( args. a8) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type9>( args. a9));
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
          , BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                
                
                
                
                cont->trigger(boost::move(
                    func(boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4) , boost::move(arg5) , boost::move(arg6) , boost::move(arg7) , boost::move(arg8) , boost::move(arg9))
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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_10<Action>(),
                cont, boost::forward<Func>(func)
              ,
                    boost::forward< typename util::remove_reference<Arguments>::type:: member_type0>( args. a0) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type1>( args. a1) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type2>( args. a2) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type3>( args. a3) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type4>( args. a4) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type5>( args. a5) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type6>( args. a6) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type7>( args. a7) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type8>( args. a8) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type9>( args. a9));
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
          , BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9 , BOOST_FWD_REF(Arg10) arg10) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                
                
                
                
                func(boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4) , boost::move(arg5) , boost::move(arg6) , boost::move(arg7) , boost::move(arg8) , boost::move(arg9) , boost::move(arg10));
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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_void_11<Action>(),
                cont, boost::forward<Func>(func)
              ,
                    boost::forward< typename util::remove_reference<Arguments>::type:: member_type0>( args. a0) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type1>( args. a1) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type2>( args. a2) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type3>( args. a3) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type4>( args. a4) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type5>( args. a5) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type6>( args. a6) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type7>( args. a7) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type8>( args. a8) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type9>( args. a9) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type10>( args. a10));
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
          , BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9 , BOOST_FWD_REF(Arg10) arg10) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                
                
                
                
                cont->trigger(boost::move(
                    func(boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4) , boost::move(arg5) , boost::move(arg6) , boost::move(arg7) , boost::move(arg8) , boost::move(arg9) , boost::move(arg10))
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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_11<Action>(),
                cont, boost::forward<Func>(func)
              ,
                    boost::forward< typename util::remove_reference<Arguments>::type:: member_type0>( args. a0) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type1>( args. a1) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type2>( args. a2) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type3>( args. a3) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type4>( args. a4) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type5>( args. a5) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type6>( args. a6) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type7>( args. a7) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type8>( args. a8) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type9>( args. a9) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type10>( args. a10));
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
          , BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9 , BOOST_FWD_REF(Arg10) arg10 , BOOST_FWD_REF(Arg11) arg11) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                
                
                
                
                func(boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4) , boost::move(arg5) , boost::move(arg6) , boost::move(arg7) , boost::move(arg8) , boost::move(arg9) , boost::move(arg10) , boost::move(arg11));
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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_void_12<Action>(),
                cont, boost::forward<Func>(func)
              ,
                    boost::forward< typename util::remove_reference<Arguments>::type:: member_type0>( args. a0) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type1>( args. a1) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type2>( args. a2) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type3>( args. a3) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type4>( args. a4) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type5>( args. a5) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type6>( args. a6) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type7>( args. a7) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type8>( args. a8) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type9>( args. a9) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type10>( args. a10) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type11>( args. a11));
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
          , BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9 , BOOST_FWD_REF(Arg10) arg10 , BOOST_FWD_REF(Arg11) arg11) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                
                
                
                
                cont->trigger(boost::move(
                    func(boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4) , boost::move(arg5) , boost::move(arg6) , boost::move(arg7) , boost::move(arg8) , boost::move(arg9) , boost::move(arg10) , boost::move(arg11))
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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_12<Action>(),
                cont, boost::forward<Func>(func)
              ,
                    boost::forward< typename util::remove_reference<Arguments>::type:: member_type0>( args. a0) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type1>( args. a1) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type2>( args. a2) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type3>( args. a3) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type4>( args. a4) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type5>( args. a5) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type6>( args. a6) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type7>( args. a7) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type8>( args. a8) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type9>( args. a9) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type10>( args. a10) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type11>( args. a11));
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
          , BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9 , BOOST_FWD_REF(Arg10) arg10 , BOOST_FWD_REF(Arg11) arg11 , BOOST_FWD_REF(Arg12) arg12) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                
                
                
                
                func(boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4) , boost::move(arg5) , boost::move(arg6) , boost::move(arg7) , boost::move(arg8) , boost::move(arg9) , boost::move(arg10) , boost::move(arg11) , boost::move(arg12));
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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_void_13<Action>(),
                cont, boost::forward<Func>(func)
              ,
                    boost::forward< typename util::remove_reference<Arguments>::type:: member_type0>( args. a0) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type1>( args. a1) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type2>( args. a2) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type3>( args. a3) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type4>( args. a4) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type5>( args. a5) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type6>( args. a6) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type7>( args. a7) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type8>( args. a8) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type9>( args. a9) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type10>( args. a10) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type11>( args. a11) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type12>( args. a12));
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
          , BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9 , BOOST_FWD_REF(Arg10) arg10 , BOOST_FWD_REF(Arg11) arg11 , BOOST_FWD_REF(Arg12) arg12) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                
                
                
                
                cont->trigger(boost::move(
                    func(boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4) , boost::move(arg5) , boost::move(arg6) , boost::move(arg7) , boost::move(arg8) , boost::move(arg9) , boost::move(arg10) , boost::move(arg11) , boost::move(arg12))
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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_13<Action>(),
                cont, boost::forward<Func>(func)
              ,
                    boost::forward< typename util::remove_reference<Arguments>::type:: member_type0>( args. a0) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type1>( args. a1) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type2>( args. a2) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type3>( args. a3) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type4>( args. a4) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type5>( args. a5) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type6>( args. a6) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type7>( args. a7) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type8>( args. a8) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type9>( args. a9) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type10>( args. a10) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type11>( args. a11) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type12>( args. a12));
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
          , BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9 , BOOST_FWD_REF(Arg10) arg10 , BOOST_FWD_REF(Arg11) arg11 , BOOST_FWD_REF(Arg12) arg12 , BOOST_FWD_REF(Arg13) arg13) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                
                
                
                
                func(boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4) , boost::move(arg5) , boost::move(arg6) , boost::move(arg7) , boost::move(arg8) , boost::move(arg9) , boost::move(arg10) , boost::move(arg11) , boost::move(arg12) , boost::move(arg13));
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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_void_14<Action>(),
                cont, boost::forward<Func>(func)
              ,
                    boost::forward< typename util::remove_reference<Arguments>::type:: member_type0>( args. a0) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type1>( args. a1) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type2>( args. a2) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type3>( args. a3) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type4>( args. a4) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type5>( args. a5) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type6>( args. a6) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type7>( args. a7) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type8>( args. a8) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type9>( args. a9) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type10>( args. a10) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type11>( args. a11) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type12>( args. a12) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type13>( args. a13));
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
          , BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9 , BOOST_FWD_REF(Arg10) arg10 , BOOST_FWD_REF(Arg11) arg11 , BOOST_FWD_REF(Arg12) arg12 , BOOST_FWD_REF(Arg13) arg13) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                
                
                
                
                cont->trigger(boost::move(
                    func(boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4) , boost::move(arg5) , boost::move(arg6) , boost::move(arg7) , boost::move(arg8) , boost::move(arg9) , boost::move(arg10) , boost::move(arg11) , boost::move(arg12) , boost::move(arg13))
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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_14<Action>(),
                cont, boost::forward<Func>(func)
              ,
                    boost::forward< typename util::remove_reference<Arguments>::type:: member_type0>( args. a0) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type1>( args. a1) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type2>( args. a2) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type3>( args. a3) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type4>( args. a4) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type5>( args. a5) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type6>( args. a6) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type7>( args. a7) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type8>( args. a8) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type9>( args. a9) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type10>( args. a10) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type11>( args. a11) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type12>( args. a12) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type13>( args. a13));
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
          , BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9 , BOOST_FWD_REF(Arg10) arg10 , BOOST_FWD_REF(Arg11) arg11 , BOOST_FWD_REF(Arg12) arg12 , BOOST_FWD_REF(Arg13) arg13 , BOOST_FWD_REF(Arg14) arg14) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                
                
                
                
                func(boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4) , boost::move(arg5) , boost::move(arg6) , boost::move(arg7) , boost::move(arg8) , boost::move(arg9) , boost::move(arg10) , boost::move(arg11) , boost::move(arg12) , boost::move(arg13) , boost::move(arg14));
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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_void_15<Action>(),
                cont, boost::forward<Func>(func)
              ,
                    boost::forward< typename util::remove_reference<Arguments>::type:: member_type0>( args. a0) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type1>( args. a1) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type2>( args. a2) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type3>( args. a3) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type4>( args. a4) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type5>( args. a5) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type6>( args. a6) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type7>( args. a7) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type8>( args. a8) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type9>( args. a9) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type10>( args. a10) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type11>( args. a11) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type12>( args. a12) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type13>( args. a13) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type14>( args. a14));
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
          , BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9 , BOOST_FWD_REF(Arg10) arg10 , BOOST_FWD_REF(Arg11) arg11 , BOOST_FWD_REF(Arg12) arg12 , BOOST_FWD_REF(Arg13) arg13 , BOOST_FWD_REF(Arg14) arg14) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                
                
                
                
                cont->trigger(boost::move(
                    func(boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4) , boost::move(arg5) , boost::move(arg6) , boost::move(arg7) , boost::move(arg8) , boost::move(arg9) , boost::move(arg10) , boost::move(arg11) , boost::move(arg12) , boost::move(arg13) , boost::move(arg14))
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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_15<Action>(),
                cont, boost::forward<Func>(func)
              ,
                    boost::forward< typename util::remove_reference<Arguments>::type:: member_type0>( args. a0) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type1>( args. a1) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type2>( args. a2) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type3>( args. a3) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type4>( args. a4) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type5>( args. a5) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type6>( args. a6) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type7>( args. a7) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type8>( args. a8) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type9>( args. a9) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type10>( args. a10) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type11>( args. a11) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type12>( args. a12) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type13>( args. a13) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type14>( args. a14));
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
          , BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9 , BOOST_FWD_REF(Arg10) arg10 , BOOST_FWD_REF(Arg11) arg11 , BOOST_FWD_REF(Arg12) arg12 , BOOST_FWD_REF(Arg13) arg13 , BOOST_FWD_REF(Arg14) arg14 , BOOST_FWD_REF(Arg15) arg15) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                
                
                
                
                func(boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4) , boost::move(arg5) , boost::move(arg6) , boost::move(arg7) , boost::move(arg8) , boost::move(arg9) , boost::move(arg10) , boost::move(arg11) , boost::move(arg12) , boost::move(arg13) , boost::move(arg14) , boost::move(arg15));
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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_void_16<Action>(),
                cont, boost::forward<Func>(func)
              ,
                    boost::forward< typename util::remove_reference<Arguments>::type:: member_type0>( args. a0) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type1>( args. a1) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type2>( args. a2) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type3>( args. a3) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type4>( args. a4) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type5>( args. a5) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type6>( args. a6) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type7>( args. a7) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type8>( args. a8) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type9>( args. a9) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type10>( args. a10) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type11>( args. a11) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type12>( args. a12) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type13>( args. a13) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type14>( args. a14) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type15>( args. a15));
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
          , BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9 , BOOST_FWD_REF(Arg10) arg10 , BOOST_FWD_REF(Arg11) arg11 , BOOST_FWD_REF(Arg12) arg12 , BOOST_FWD_REF(Arg13) arg13 , BOOST_FWD_REF(Arg14) arg14 , BOOST_FWD_REF(Arg15) arg15) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                
                
                
                
                cont->trigger(boost::move(
                    func(boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4) , boost::move(arg5) , boost::move(arg6) , boost::move(arg7) , boost::move(arg8) , boost::move(arg9) , boost::move(arg10) , boost::move(arg11) , boost::move(arg12) , boost::move(arg13) , boost::move(arg14) , boost::move(arg15))
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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_16<Action>(),
                cont, boost::forward<Func>(func)
              ,
                    boost::forward< typename util::remove_reference<Arguments>::type:: member_type0>( args. a0) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type1>( args. a1) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type2>( args. a2) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type3>( args. a3) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type4>( args. a4) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type5>( args. a5) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type6>( args. a6) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type7>( args. a7) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type8>( args. a8) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type9>( args. a9) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type10>( args. a10) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type11>( args. a11) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type12>( args. a12) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type13>( args. a13) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type14>( args. a14) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type15>( args. a15));
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
          , BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9 , BOOST_FWD_REF(Arg10) arg10 , BOOST_FWD_REF(Arg11) arg11 , BOOST_FWD_REF(Arg12) arg12 , BOOST_FWD_REF(Arg13) arg13 , BOOST_FWD_REF(Arg14) arg14 , BOOST_FWD_REF(Arg15) arg15 , BOOST_FWD_REF(Arg16) arg16) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                
                
                
                
                func(boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4) , boost::move(arg5) , boost::move(arg6) , boost::move(arg7) , boost::move(arg8) , boost::move(arg9) , boost::move(arg10) , boost::move(arg11) , boost::move(arg12) , boost::move(arg13) , boost::move(arg14) , boost::move(arg15) , boost::move(arg16));
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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_void_17<Action>(),
                cont, boost::forward<Func>(func)
              ,
                    boost::forward< typename util::remove_reference<Arguments>::type:: member_type0>( args. a0) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type1>( args. a1) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type2>( args. a2) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type3>( args. a3) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type4>( args. a4) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type5>( args. a5) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type6>( args. a6) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type7>( args. a7) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type8>( args. a8) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type9>( args. a9) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type10>( args. a10) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type11>( args. a11) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type12>( args. a12) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type13>( args. a13) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type14>( args. a14) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type15>( args. a15) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type16>( args. a16));
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
          , BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9 , BOOST_FWD_REF(Arg10) arg10 , BOOST_FWD_REF(Arg11) arg11 , BOOST_FWD_REF(Arg12) arg12 , BOOST_FWD_REF(Arg13) arg13 , BOOST_FWD_REF(Arg14) arg14 , BOOST_FWD_REF(Arg15) arg15 , BOOST_FWD_REF(Arg16) arg16) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                
                
                
                
                cont->trigger(boost::move(
                    func(boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4) , boost::move(arg5) , boost::move(arg6) , boost::move(arg7) , boost::move(arg8) , boost::move(arg9) , boost::move(arg10) , boost::move(arg11) , boost::move(arg12) , boost::move(arg13) , boost::move(arg14) , boost::move(arg15) , boost::move(arg16))
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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_17<Action>(),
                cont, boost::forward<Func>(func)
              ,
                    boost::forward< typename util::remove_reference<Arguments>::type:: member_type0>( args. a0) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type1>( args. a1) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type2>( args. a2) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type3>( args. a3) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type4>( args. a4) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type5>( args. a5) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type6>( args. a6) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type7>( args. a7) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type8>( args. a8) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type9>( args. a9) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type10>( args. a10) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type11>( args. a11) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type12>( args. a12) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type13>( args. a13) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type14>( args. a14) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type15>( args. a15) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type16>( args. a16));
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
          , BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9 , BOOST_FWD_REF(Arg10) arg10 , BOOST_FWD_REF(Arg11) arg11 , BOOST_FWD_REF(Arg12) arg12 , BOOST_FWD_REF(Arg13) arg13 , BOOST_FWD_REF(Arg14) arg14 , BOOST_FWD_REF(Arg15) arg15 , BOOST_FWD_REF(Arg16) arg16 , BOOST_FWD_REF(Arg17) arg17) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                
                
                
                
                func(boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4) , boost::move(arg5) , boost::move(arg6) , boost::move(arg7) , boost::move(arg8) , boost::move(arg9) , boost::move(arg10) , boost::move(arg11) , boost::move(arg12) , boost::move(arg13) , boost::move(arg14) , boost::move(arg15) , boost::move(arg16) , boost::move(arg17));
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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_void_18<Action>(),
                cont, boost::forward<Func>(func)
              ,
                    boost::forward< typename util::remove_reference<Arguments>::type:: member_type0>( args. a0) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type1>( args. a1) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type2>( args. a2) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type3>( args. a3) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type4>( args. a4) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type5>( args. a5) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type6>( args. a6) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type7>( args. a7) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type8>( args. a8) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type9>( args. a9) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type10>( args. a10) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type11>( args. a11) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type12>( args. a12) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type13>( args. a13) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type14>( args. a14) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type15>( args. a15) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type16>( args. a16) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type17>( args. a17));
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
          , BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9 , BOOST_FWD_REF(Arg10) arg10 , BOOST_FWD_REF(Arg11) arg11 , BOOST_FWD_REF(Arg12) arg12 , BOOST_FWD_REF(Arg13) arg13 , BOOST_FWD_REF(Arg14) arg14 , BOOST_FWD_REF(Arg15) arg15 , BOOST_FWD_REF(Arg16) arg16 , BOOST_FWD_REF(Arg17) arg17) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                
                
                
                
                cont->trigger(boost::move(
                    func(boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4) , boost::move(arg5) , boost::move(arg6) , boost::move(arg7) , boost::move(arg8) , boost::move(arg9) , boost::move(arg10) , boost::move(arg11) , boost::move(arg12) , boost::move(arg13) , boost::move(arg14) , boost::move(arg15) , boost::move(arg16) , boost::move(arg17))
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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_18<Action>(),
                cont, boost::forward<Func>(func)
              ,
                    boost::forward< typename util::remove_reference<Arguments>::type:: member_type0>( args. a0) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type1>( args. a1) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type2>( args. a2) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type3>( args. a3) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type4>( args. a4) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type5>( args. a5) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type6>( args. a6) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type7>( args. a7) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type8>( args. a8) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type9>( args. a9) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type10>( args. a10) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type11>( args. a11) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type12>( args. a12) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type13>( args. a13) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type14>( args. a14) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type15>( args. a15) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type16>( args. a16) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type17>( args. a17));
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
          , BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9 , BOOST_FWD_REF(Arg10) arg10 , BOOST_FWD_REF(Arg11) arg11 , BOOST_FWD_REF(Arg12) arg12 , BOOST_FWD_REF(Arg13) arg13 , BOOST_FWD_REF(Arg14) arg14 , BOOST_FWD_REF(Arg15) arg15 , BOOST_FWD_REF(Arg16) arg16 , BOOST_FWD_REF(Arg17) arg17 , BOOST_FWD_REF(Arg18) arg18) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                
                
                
                
                func(boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4) , boost::move(arg5) , boost::move(arg6) , boost::move(arg7) , boost::move(arg8) , boost::move(arg9) , boost::move(arg10) , boost::move(arg11) , boost::move(arg12) , boost::move(arg13) , boost::move(arg14) , boost::move(arg15) , boost::move(arg16) , boost::move(arg17) , boost::move(arg18));
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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_void_19<Action>(),
                cont, boost::forward<Func>(func)
              ,
                    boost::forward< typename util::remove_reference<Arguments>::type:: member_type0>( args. a0) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type1>( args. a1) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type2>( args. a2) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type3>( args. a3) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type4>( args. a4) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type5>( args. a5) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type6>( args. a6) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type7>( args. a7) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type8>( args. a8) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type9>( args. a9) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type10>( args. a10) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type11>( args. a11) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type12>( args. a12) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type13>( args. a13) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type14>( args. a14) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type15>( args. a15) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type16>( args. a16) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type17>( args. a17) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type18>( args. a18));
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
          , BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9 , BOOST_FWD_REF(Arg10) arg10 , BOOST_FWD_REF(Arg11) arg11 , BOOST_FWD_REF(Arg12) arg12 , BOOST_FWD_REF(Arg13) arg13 , BOOST_FWD_REF(Arg14) arg14 , BOOST_FWD_REF(Arg15) arg15 , BOOST_FWD_REF(Arg16) arg16 , BOOST_FWD_REF(Arg17) arg17 , BOOST_FWD_REF(Arg18) arg18) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                
                
                
                
                cont->trigger(boost::move(
                    func(boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4) , boost::move(arg5) , boost::move(arg6) , boost::move(arg7) , boost::move(arg8) , boost::move(arg9) , boost::move(arg10) , boost::move(arg11) , boost::move(arg12) , boost::move(arg13) , boost::move(arg14) , boost::move(arg15) , boost::move(arg16) , boost::move(arg17) , boost::move(arg18))
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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_19<Action>(),
                cont, boost::forward<Func>(func)
              ,
                    boost::forward< typename util::remove_reference<Arguments>::type:: member_type0>( args. a0) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type1>( args. a1) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type2>( args. a2) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type3>( args. a3) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type4>( args. a4) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type5>( args. a5) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type6>( args. a6) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type7>( args. a7) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type8>( args. a8) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type9>( args. a9) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type10>( args. a10) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type11>( args. a11) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type12>( args. a12) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type13>( args. a13) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type14>( args. a14) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type15>( args. a15) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type16>( args. a16) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type17>( args. a17) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type18>( args. a18));
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
          , BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9 , BOOST_FWD_REF(Arg10) arg10 , BOOST_FWD_REF(Arg11) arg11 , BOOST_FWD_REF(Arg12) arg12 , BOOST_FWD_REF(Arg13) arg13 , BOOST_FWD_REF(Arg14) arg14 , BOOST_FWD_REF(Arg15) arg15 , BOOST_FWD_REF(Arg16) arg16 , BOOST_FWD_REF(Arg17) arg17 , BOOST_FWD_REF(Arg18) arg18 , BOOST_FWD_REF(Arg19) arg19) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                
                
                
                
                func(boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4) , boost::move(arg5) , boost::move(arg6) , boost::move(arg7) , boost::move(arg8) , boost::move(arg9) , boost::move(arg10) , boost::move(arg11) , boost::move(arg12) , boost::move(arg13) , boost::move(arg14) , boost::move(arg15) , boost::move(arg16) , boost::move(arg17) , boost::move(arg18) , boost::move(arg19));
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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_void_20<Action>(),
                cont, boost::forward<Func>(func)
              ,
                    boost::forward< typename util::remove_reference<Arguments>::type:: member_type0>( args. a0) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type1>( args. a1) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type2>( args. a2) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type3>( args. a3) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type4>( args. a4) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type5>( args. a5) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type6>( args. a6) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type7>( args. a7) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type8>( args. a8) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type9>( args. a9) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type10>( args. a10) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type11>( args. a11) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type12>( args. a12) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type13>( args. a13) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type14>( args. a14) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type15>( args. a15) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type16>( args. a16) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type17>( args. a17) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type18>( args. a18) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type19>( args. a19));
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
          , BOOST_FWD_REF(Arg0) arg0 , BOOST_FWD_REF(Arg1) arg1 , BOOST_FWD_REF(Arg2) arg2 , BOOST_FWD_REF(Arg3) arg3 , BOOST_FWD_REF(Arg4) arg4 , BOOST_FWD_REF(Arg5) arg5 , BOOST_FWD_REF(Arg6) arg6 , BOOST_FWD_REF(Arg7) arg7 , BOOST_FWD_REF(Arg8) arg8 , BOOST_FWD_REF(Arg9) arg9 , BOOST_FWD_REF(Arg10) arg10 , BOOST_FWD_REF(Arg11) arg11 , BOOST_FWD_REF(Arg12) arg12 , BOOST_FWD_REF(Arg13) arg13 , BOOST_FWD_REF(Arg14) arg14 , BOOST_FWD_REF(Arg15) arg15 , BOOST_FWD_REF(Arg16) arg16 , BOOST_FWD_REF(Arg17) arg17 , BOOST_FWD_REF(Arg18) arg18 , BOOST_FWD_REF(Arg19) arg19) const
        {
            try {
                LTM_(debug) << "Executing action("
                    << detail::get_action_name<Action>()
                    << ") with continuation(" << cont->get_gid() << ")";
                
                
                
                
                cont->trigger(boost::move(
                    func(boost::move(arg0) , boost::move(arg1) , boost::move(arg2) , boost::move(arg3) , boost::move(arg4) , boost::move(arg5) , boost::move(arg6) , boost::move(arg7) , boost::move(arg8) , boost::move(arg9) , boost::move(arg10) , boost::move(arg11) , boost::move(arg12) , boost::move(arg13) , boost::move(arg14) , boost::move(arg15) , boost::move(arg16) , boost::move(arg17) , boost::move(arg18) , boost::move(arg19))
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
        call(continuation_type cont, BOOST_FWD_REF(Func) func,
            BOOST_FWD_REF(Arguments) args)
        {
            return HPX_STD_BIND(
                continuation_thread_function_20<Action>(),
                cont, boost::forward<Func>(func)
              ,
                    boost::forward< typename util::remove_reference<Arguments>::type:: member_type0>( args. a0) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type1>( args. a1) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type2>( args. a2) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type3>( args. a3) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type4>( args. a4) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type5>( args. a5) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type6>( args. a6) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type7>( args. a7) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type8>( args. a8) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type9>( args. a9) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type10>( args. a10) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type11>( args. a11) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type12>( args. a12) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type13>( args. a13) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type14>( args. a14) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type15>( args. a15) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type16>( args. a16) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type17>( args. a17) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type18>( args. a18) , boost::forward< typename util::remove_reference<Arguments>::type:: member_type19>( args. a19));
        }
    };
}
