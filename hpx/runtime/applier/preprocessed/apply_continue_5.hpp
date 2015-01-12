// Copyright (c) 2007-2013 Hartmut Kaiser
// Copyright (c) 2012-2013 Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This file has been automatically generated using the Boost.Wave tool.
// Do not edit manually.


namespace hpx
{
    
    template <
        typename Action
       
      , typename F>
    bool apply_continue(naming::id_type const& gid
       
      , F && f)
    {
        typedef typename hpx::actions::extract_action<Action>::type action_type;
        typedef typename action_type::result_type result_type;
        return apply<Action>(
            new hpx::actions::typed_continuation<result_type>(
                std::forward<F>(f))
          , gid
           );
    }
    template <
        typename Component, typename Signature, typename Derived
       
      , typename F>
    bool apply_continue(
        hpx::actions::basic_action<Component, Signature, Derived> 
      , naming::id_type const& gid
       
      , F && f)
    {
        return apply_continue<Derived>(
            gid
           
          , std::forward<F>(f));
    }
    
    template <
        typename Action
       >
    bool apply_continue(
        naming::id_type const& gid
       
      , naming::id_type const& cont)
    {
        typedef typename hpx::actions::extract_action<Action>::type action_type;
        typedef typename action_type::result_type result_type;
        return apply<Action>(
            new hpx::actions::typed_continuation<result_type>(
                cont, make_continuation())
          , gid
           );
    }
    template <
        typename Component, typename Signature, typename Derived
       >
    bool apply_continue(
        hpx::actions::basic_action<Component, Signature, Derived> 
      , naming::id_type const& gid
       
      , naming::id_type const& cont)
    {
        return apply_continue<Derived>(
            gid
           
          , cont);
    }
}
namespace hpx
{
    
    template <
        typename Action
      , typename T0
      , typename F>
    bool apply_continue(naming::id_type const& gid
      , T0 && v0
      , F && f)
    {
        typedef typename hpx::actions::extract_action<Action>::type action_type;
        typedef typename action_type::result_type result_type;
        return apply<Action>(
            new hpx::actions::typed_continuation<result_type>(
                std::forward<F>(f))
          , gid
          , std::forward<T0>( v0 ));
    }
    template <
        typename Component, typename Signature, typename Derived
      , typename T0
      , typename F>
    bool apply_continue(
        hpx::actions::basic_action<Component, Signature, Derived> 
      , naming::id_type const& gid
      , T0 && v0
      , F && f)
    {
        return apply_continue<Derived>(
            gid
          , std::forward<T0>( v0 )
          , std::forward<F>(f));
    }
    
    template <
        typename Action
      , typename T0>
    bool apply_continue(
        naming::id_type const& gid
      , T0 && v0
      , naming::id_type const& cont)
    {
        typedef typename hpx::actions::extract_action<Action>::type action_type;
        typedef typename action_type::result_type result_type;
        return apply<Action>(
            new hpx::actions::typed_continuation<result_type>(
                cont, make_continuation())
          , gid
          , std::forward<T0>( v0 ));
    }
    template <
        typename Component, typename Signature, typename Derived
      , typename T0>
    bool apply_continue(
        hpx::actions::basic_action<Component, Signature, Derived> 
      , naming::id_type const& gid
      , T0 && v0
      , naming::id_type const& cont)
    {
        return apply_continue<Derived>(
            gid
          , std::forward<T0>( v0 )
          , cont);
    }
}
namespace hpx
{
    
    template <
        typename Action
      , typename T0 , typename T1
      , typename F>
    bool apply_continue(naming::id_type const& gid
      , T0 && v0 , T1 && v1
      , F && f)
    {
        typedef typename hpx::actions::extract_action<Action>::type action_type;
        typedef typename action_type::result_type result_type;
        return apply<Action>(
            new hpx::actions::typed_continuation<result_type>(
                std::forward<F>(f))
          , gid
          , std::forward<T0>( v0 ) , std::forward<T1>( v1 ));
    }
    template <
        typename Component, typename Signature, typename Derived
      , typename T0 , typename T1
      , typename F>
    bool apply_continue(
        hpx::actions::basic_action<Component, Signature, Derived> 
      , naming::id_type const& gid
      , T0 && v0 , T1 && v1
      , F && f)
    {
        return apply_continue<Derived>(
            gid
          , std::forward<T0>( v0 ) , std::forward<T1>( v1 )
          , std::forward<F>(f));
    }
    
    template <
        typename Action
      , typename T0 , typename T1>
    bool apply_continue(
        naming::id_type const& gid
      , T0 && v0 , T1 && v1
      , naming::id_type const& cont)
    {
        typedef typename hpx::actions::extract_action<Action>::type action_type;
        typedef typename action_type::result_type result_type;
        return apply<Action>(
            new hpx::actions::typed_continuation<result_type>(
                cont, make_continuation())
          , gid
          , std::forward<T0>( v0 ) , std::forward<T1>( v1 ));
    }
    template <
        typename Component, typename Signature, typename Derived
      , typename T0 , typename T1>
    bool apply_continue(
        hpx::actions::basic_action<Component, Signature, Derived> 
      , naming::id_type const& gid
      , T0 && v0 , T1 && v1
      , naming::id_type const& cont)
    {
        return apply_continue<Derived>(
            gid
          , std::forward<T0>( v0 ) , std::forward<T1>( v1 )
          , cont);
    }
}
namespace hpx
{
    
    template <
        typename Action
      , typename T0 , typename T1 , typename T2
      , typename F>
    bool apply_continue(naming::id_type const& gid
      , T0 && v0 , T1 && v1 , T2 && v2
      , F && f)
    {
        typedef typename hpx::actions::extract_action<Action>::type action_type;
        typedef typename action_type::result_type result_type;
        return apply<Action>(
            new hpx::actions::typed_continuation<result_type>(
                std::forward<F>(f))
          , gid
          , std::forward<T0>( v0 ) , std::forward<T1>( v1 ) , std::forward<T2>( v2 ));
    }
    template <
        typename Component, typename Signature, typename Derived
      , typename T0 , typename T1 , typename T2
      , typename F>
    bool apply_continue(
        hpx::actions::basic_action<Component, Signature, Derived> 
      , naming::id_type const& gid
      , T0 && v0 , T1 && v1 , T2 && v2
      , F && f)
    {
        return apply_continue<Derived>(
            gid
          , std::forward<T0>( v0 ) , std::forward<T1>( v1 ) , std::forward<T2>( v2 )
          , std::forward<F>(f));
    }
    
    template <
        typename Action
      , typename T0 , typename T1 , typename T2>
    bool apply_continue(
        naming::id_type const& gid
      , T0 && v0 , T1 && v1 , T2 && v2
      , naming::id_type const& cont)
    {
        typedef typename hpx::actions::extract_action<Action>::type action_type;
        typedef typename action_type::result_type result_type;
        return apply<Action>(
            new hpx::actions::typed_continuation<result_type>(
                cont, make_continuation())
          , gid
          , std::forward<T0>( v0 ) , std::forward<T1>( v1 ) , std::forward<T2>( v2 ));
    }
    template <
        typename Component, typename Signature, typename Derived
      , typename T0 , typename T1 , typename T2>
    bool apply_continue(
        hpx::actions::basic_action<Component, Signature, Derived> 
      , naming::id_type const& gid
      , T0 && v0 , T1 && v1 , T2 && v2
      , naming::id_type const& cont)
    {
        return apply_continue<Derived>(
            gid
          , std::forward<T0>( v0 ) , std::forward<T1>( v1 ) , std::forward<T2>( v2 )
          , cont);
    }
}
namespace hpx
{
    
    template <
        typename Action
      , typename T0 , typename T1 , typename T2 , typename T3
      , typename F>
    bool apply_continue(naming::id_type const& gid
      , T0 && v0 , T1 && v1 , T2 && v2 , T3 && v3
      , F && f)
    {
        typedef typename hpx::actions::extract_action<Action>::type action_type;
        typedef typename action_type::result_type result_type;
        return apply<Action>(
            new hpx::actions::typed_continuation<result_type>(
                std::forward<F>(f))
          , gid
          , std::forward<T0>( v0 ) , std::forward<T1>( v1 ) , std::forward<T2>( v2 ) , std::forward<T3>( v3 ));
    }
    template <
        typename Component, typename Signature, typename Derived
      , typename T0 , typename T1 , typename T2 , typename T3
      , typename F>
    bool apply_continue(
        hpx::actions::basic_action<Component, Signature, Derived> 
      , naming::id_type const& gid
      , T0 && v0 , T1 && v1 , T2 && v2 , T3 && v3
      , F && f)
    {
        return apply_continue<Derived>(
            gid
          , std::forward<T0>( v0 ) , std::forward<T1>( v1 ) , std::forward<T2>( v2 ) , std::forward<T3>( v3 )
          , std::forward<F>(f));
    }
    
    template <
        typename Action
      , typename T0 , typename T1 , typename T2 , typename T3>
    bool apply_continue(
        naming::id_type const& gid
      , T0 && v0 , T1 && v1 , T2 && v2 , T3 && v3
      , naming::id_type const& cont)
    {
        typedef typename hpx::actions::extract_action<Action>::type action_type;
        typedef typename action_type::result_type result_type;
        return apply<Action>(
            new hpx::actions::typed_continuation<result_type>(
                cont, make_continuation())
          , gid
          , std::forward<T0>( v0 ) , std::forward<T1>( v1 ) , std::forward<T2>( v2 ) , std::forward<T3>( v3 ));
    }
    template <
        typename Component, typename Signature, typename Derived
      , typename T0 , typename T1 , typename T2 , typename T3>
    bool apply_continue(
        hpx::actions::basic_action<Component, Signature, Derived> 
      , naming::id_type const& gid
      , T0 && v0 , T1 && v1 , T2 && v2 , T3 && v3
      , naming::id_type const& cont)
    {
        return apply_continue<Derived>(
            gid
          , std::forward<T0>( v0 ) , std::forward<T1>( v1 ) , std::forward<T2>( v2 ) , std::forward<T3>( v3 )
          , cont);
    }
}
namespace hpx
{
    
    template <
        typename Action
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4
      , typename F>
    bool apply_continue(naming::id_type const& gid
      , T0 && v0 , T1 && v1 , T2 && v2 , T3 && v3 , T4 && v4
      , F && f)
    {
        typedef typename hpx::actions::extract_action<Action>::type action_type;
        typedef typename action_type::result_type result_type;
        return apply<Action>(
            new hpx::actions::typed_continuation<result_type>(
                std::forward<F>(f))
          , gid
          , std::forward<T0>( v0 ) , std::forward<T1>( v1 ) , std::forward<T2>( v2 ) , std::forward<T3>( v3 ) , std::forward<T4>( v4 ));
    }
    template <
        typename Component, typename Signature, typename Derived
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4
      , typename F>
    bool apply_continue(
        hpx::actions::basic_action<Component, Signature, Derived> 
      , naming::id_type const& gid
      , T0 && v0 , T1 && v1 , T2 && v2 , T3 && v3 , T4 && v4
      , F && f)
    {
        return apply_continue<Derived>(
            gid
          , std::forward<T0>( v0 ) , std::forward<T1>( v1 ) , std::forward<T2>( v2 ) , std::forward<T3>( v3 ) , std::forward<T4>( v4 )
          , std::forward<F>(f));
    }
    
    template <
        typename Action
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4>
    bool apply_continue(
        naming::id_type const& gid
      , T0 && v0 , T1 && v1 , T2 && v2 , T3 && v3 , T4 && v4
      , naming::id_type const& cont)
    {
        typedef typename hpx::actions::extract_action<Action>::type action_type;
        typedef typename action_type::result_type result_type;
        return apply<Action>(
            new hpx::actions::typed_continuation<result_type>(
                cont, make_continuation())
          , gid
          , std::forward<T0>( v0 ) , std::forward<T1>( v1 ) , std::forward<T2>( v2 ) , std::forward<T3>( v3 ) , std::forward<T4>( v4 ));
    }
    template <
        typename Component, typename Signature, typename Derived
      , typename T0 , typename T1 , typename T2 , typename T3 , typename T4>
    bool apply_continue(
        hpx::actions::basic_action<Component, Signature, Derived> 
      , naming::id_type const& gid
      , T0 && v0 , T1 && v1 , T2 && v2 , T3 && v3 , T4 && v4
      , naming::id_type const& cont)
    {
        return apply_continue<Derived>(
            gid
          , std::forward<T0>( v0 ) , std::forward<T1>( v1 ) , std::forward<T2>( v2 ) , std::forward<T3>( v3 ) , std::forward<T4>( v4 )
          , cont);
    }
}
