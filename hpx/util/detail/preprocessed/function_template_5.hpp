// Copyright (c) 2007-2013 Hartmut Kaiser
// Copyright (c) 2012-2013 Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This file has been automatically generated using the Boost.Wave tool.
// Do not edit manually.


namespace hpx { namespace util {
    template <
        typename R
       
      , typename IArchive
      , typename OArchive
    >
    struct function_base<
        R()
      , IArchive
      , OArchive
    >
    {
        function_base()
            : vptr(0)
            , object(0)
        {}
        ~function_base()
        {
            if(object)
            {
                vptr->static_delete(&object);
            }
        }
        typedef R result_type;
        typedef
            detail::vtable_ptr_base<
                R()
              , IArchive
              , OArchive
            > vtable_ptr_type;
        template <typename Functor>
        explicit function_base(
            BOOST_FWD_REF(Functor) f
          , typename ::boost::disable_if<
                typename boost::is_same<
                    function_base
                  , typename util::decay<Functor>::type
                >::type
            >::type * dummy = 0
        )
            : vptr(0)
            , object(0)
        {
            if (!detail::is_empty_function(f))
            {
                typedef
                    typename util::decay<Functor>::type
                    functor_type;
                vptr = detail::get_table<
                            functor_type
                          , R()
                        >::template get<
                            IArchive
                          , OArchive
                        >();
                if (sizeof(functor_type) <= sizeof(void *)) 
                {
                    new (&object) functor_type(boost::forward<Functor>(f));
                }
                else
                {
                    object = new functor_type(boost::forward<Functor>(f));
                }
            }
        }
        function_base(function_base const & other)
            : vptr(0)
            , object(0)
        {
            assign(other);
        }
        function_base(BOOST_RV_REF(function_base) other)
            : vptr(other.vptr)
            , object(other.object)
        {
            other.vptr = 0;
            other.object = 0;
        }
        function_base &assign(function_base const & other)
        {
            if(&other != this)
            {
                if(vptr == other.vptr && !empty())
                {
                    vptr->copy(&other.object, &object);
                }
                else
                {
                    reset();
                    if(!other.empty())
                    {
                        other.vptr->clone(&other.object, &object);
                        vptr = other.vptr;
                    }
                }
            }
            return *this;
        }
        template <typename Functor>
        function_base & assign(BOOST_FWD_REF(Functor) f)
        {
            if (this == &f)
                return *this;
            typedef
                typename util::decay<Functor>::type
                functor_type;
            vtable_ptr_type * f_vptr
                = detail::get_table<
                      functor_type
                    , R()
                  >::template get<
                      IArchive
                    , OArchive
                  >();
            if(vptr == f_vptr && !empty())
            {
                if (sizeof(functor_type) <= sizeof(void *)) 
                {
                    vptr->destruct(&object);
                    new (&object) functor_type(boost::forward<Functor>(f));
                }
                else if (object)
                {
                    vptr->destruct(&object);
                    new (object) functor_type(boost::forward<Functor>(f));
                }
                else
                {
                    object = new functor_type(boost::forward<Functor>(f));
                }
            }
            else
            {
                if (!empty())
                {
                    vptr->static_delete(&object);
                    vptr = 0;
                    object = 0;
                }
                if (!detail::is_empty_function(f))
                {
                    if (sizeof(functor_type) <= sizeof(void *)) 
                    {
                        new (&object) functor_type(boost::forward<Functor>(f));
                    }
                    else
                    {
                        object = new functor_type(boost::forward<Functor>(f));
                    }
                    vptr = f_vptr;
                }
            }
            return *this;
        }
        template <typename T>
        function_base & operator=(BOOST_FWD_REF(T) t)
        {
            return assign(boost::forward<T>(t));
        }
        function_base & operator=(BOOST_COPY_ASSIGN_REF(function_base) t)
        {
            return assign(t);
        }
        function_base & operator=(BOOST_RV_REF(function_base) t)
        {
            if(this != &t)
            {
                reset();
                vptr = t.vptr;
                object = t.object;
                t.vptr = 0;
                t.object = 0;
            }
            return *this;
        }
        function_base &swap(function_base& f)
        {
            std::swap(vptr, f.vptr);
            std::swap(object, f.object);
            return *this;
        }
        bool empty() const
        {
            return (vptr == 0) && (object == 0);
        }
        operator typename util::safe_bool<function_base>::result_type() const
        {
            return util::safe_bool<function_base>()(!empty());
        }
        bool operator!() const
        {
            return empty();
        }
        void reset()
        {
            if (!empty())
            {
                vptr->static_delete(&object);
                vptr = 0;
                object = 0;
            }
        }
        BOOST_FORCEINLINE R operator()() const
        {
            if (empty()) {
                throw std::runtime_error("function_base::operator(): "
                    "function object should not be empty");
            }
            return vptr->invoke(&object );
        }
        BOOST_FORCEINLINE R operator()()
        {
            if (empty()) {
                throw std::runtime_error("function_base::operator(): "
                    "function object should not be empty");
            }
            return vptr->invoke(&object );
        }
    private:
        BOOST_COPYABLE_AND_MOVABLE(function_base);
    protected:
        vtable_ptr_type *vptr;
        mutable void *object;
    };
}}
namespace hpx { namespace util {
    template <
        typename R
      , typename A0
      , typename IArchive
      , typename OArchive
    >
    struct function_base<
        R(A0)
      , IArchive
      , OArchive
    >
    {
        function_base()
            : vptr(0)
            , object(0)
        {}
        ~function_base()
        {
            if(object)
            {
                vptr->static_delete(&object);
            }
        }
        typedef R result_type;
        typedef
            detail::vtable_ptr_base<
                R(A0)
              , IArchive
              , OArchive
            > vtable_ptr_type;
        template <typename Functor>
        explicit function_base(
            BOOST_FWD_REF(Functor) f
          , typename ::boost::disable_if<
                typename boost::is_same<
                    function_base
                  , typename util::decay<Functor>::type
                >::type
            >::type * dummy = 0
        )
            : vptr(0)
            , object(0)
        {
            if (!detail::is_empty_function(f))
            {
                typedef
                    typename util::decay<Functor>::type
                    functor_type;
                vptr = detail::get_table<
                            functor_type
                          , R(A0)
                        >::template get<
                            IArchive
                          , OArchive
                        >();
                if (sizeof(functor_type) <= sizeof(void *)) 
                {
                    new (&object) functor_type(boost::forward<Functor>(f));
                }
                else
                {
                    object = new functor_type(boost::forward<Functor>(f));
                }
            }
        }
        function_base(function_base const & other)
            : vptr(0)
            , object(0)
        {
            assign(other);
        }
        function_base(BOOST_RV_REF(function_base) other)
            : vptr(other.vptr)
            , object(other.object)
        {
            other.vptr = 0;
            other.object = 0;
        }
        function_base &assign(function_base const & other)
        {
            if(&other != this)
            {
                if(vptr == other.vptr && !empty())
                {
                    vptr->copy(&other.object, &object);
                }
                else
                {
                    reset();
                    if(!other.empty())
                    {
                        other.vptr->clone(&other.object, &object);
                        vptr = other.vptr;
                    }
                }
            }
            return *this;
        }
        template <typename Functor>
        function_base & assign(BOOST_FWD_REF(Functor) f)
        {
            if (this == &f)
                return *this;
            typedef
                typename util::decay<Functor>::type
                functor_type;
            vtable_ptr_type * f_vptr
                = detail::get_table<
                      functor_type
                    , R(A0)
                  >::template get<
                      IArchive
                    , OArchive
                  >();
            if(vptr == f_vptr && !empty())
            {
                if (sizeof(functor_type) <= sizeof(void *)) 
                {
                    vptr->destruct(&object);
                    new (&object) functor_type(boost::forward<Functor>(f));
                }
                else if (object)
                {
                    vptr->destruct(&object);
                    new (object) functor_type(boost::forward<Functor>(f));
                }
                else
                {
                    object = new functor_type(boost::forward<Functor>(f));
                }
            }
            else
            {
                if (!empty())
                {
                    vptr->static_delete(&object);
                    vptr = 0;
                    object = 0;
                }
                if (!detail::is_empty_function(f))
                {
                    if (sizeof(functor_type) <= sizeof(void *)) 
                    {
                        new (&object) functor_type(boost::forward<Functor>(f));
                    }
                    else
                    {
                        object = new functor_type(boost::forward<Functor>(f));
                    }
                    vptr = f_vptr;
                }
            }
            return *this;
        }
        template <typename T>
        function_base & operator=(BOOST_FWD_REF(T) t)
        {
            return assign(boost::forward<T>(t));
        }
        function_base & operator=(BOOST_COPY_ASSIGN_REF(function_base) t)
        {
            return assign(t);
        }
        function_base & operator=(BOOST_RV_REF(function_base) t)
        {
            if(this != &t)
            {
                reset();
                vptr = t.vptr;
                object = t.object;
                t.vptr = 0;
                t.object = 0;
            }
            return *this;
        }
        function_base &swap(function_base& f)
        {
            std::swap(vptr, f.vptr);
            std::swap(object, f.object);
            return *this;
        }
        bool empty() const
        {
            return (vptr == 0) && (object == 0);
        }
        operator typename util::safe_bool<function_base>::result_type() const
        {
            return util::safe_bool<function_base>()(!empty());
        }
        bool operator!() const
        {
            return empty();
        }
        void reset()
        {
            if (!empty())
            {
                vptr->static_delete(&object);
                vptr = 0;
                object = 0;
            }
        }
        BOOST_FORCEINLINE R operator()(A0 a0) const
        {
            if (empty()) {
                throw std::runtime_error("function_base::operator(): "
                    "function object should not be empty");
            }
            return vptr->invoke(&object , a0);
        }
        BOOST_FORCEINLINE R operator()(A0 a0)
        {
            if (empty()) {
                throw std::runtime_error("function_base::operator(): "
                    "function object should not be empty");
            }
            return vptr->invoke(&object , a0);
        }
    private:
        BOOST_COPYABLE_AND_MOVABLE(function_base);
    protected:
        vtable_ptr_type *vptr;
        mutable void *object;
    };
}}
namespace hpx { namespace util {
    template <
        typename R
      , typename A0 , typename A1
      , typename IArchive
      , typename OArchive
    >
    struct function_base<
        R(A0 , A1)
      , IArchive
      , OArchive
    >
    {
        function_base()
            : vptr(0)
            , object(0)
        {}
        ~function_base()
        {
            if(object)
            {
                vptr->static_delete(&object);
            }
        }
        typedef R result_type;
        typedef
            detail::vtable_ptr_base<
                R(A0 , A1)
              , IArchive
              , OArchive
            > vtable_ptr_type;
        template <typename Functor>
        explicit function_base(
            BOOST_FWD_REF(Functor) f
          , typename ::boost::disable_if<
                typename boost::is_same<
                    function_base
                  , typename util::decay<Functor>::type
                >::type
            >::type * dummy = 0
        )
            : vptr(0)
            , object(0)
        {
            if (!detail::is_empty_function(f))
            {
                typedef
                    typename util::decay<Functor>::type
                    functor_type;
                vptr = detail::get_table<
                            functor_type
                          , R(A0 , A1)
                        >::template get<
                            IArchive
                          , OArchive
                        >();
                if (sizeof(functor_type) <= sizeof(void *)) 
                {
                    new (&object) functor_type(boost::forward<Functor>(f));
                }
                else
                {
                    object = new functor_type(boost::forward<Functor>(f));
                }
            }
        }
        function_base(function_base const & other)
            : vptr(0)
            , object(0)
        {
            assign(other);
        }
        function_base(BOOST_RV_REF(function_base) other)
            : vptr(other.vptr)
            , object(other.object)
        {
            other.vptr = 0;
            other.object = 0;
        }
        function_base &assign(function_base const & other)
        {
            if(&other != this)
            {
                if(vptr == other.vptr && !empty())
                {
                    vptr->copy(&other.object, &object);
                }
                else
                {
                    reset();
                    if(!other.empty())
                    {
                        other.vptr->clone(&other.object, &object);
                        vptr = other.vptr;
                    }
                }
            }
            return *this;
        }
        template <typename Functor>
        function_base & assign(BOOST_FWD_REF(Functor) f)
        {
            if (this == &f)
                return *this;
            typedef
                typename util::decay<Functor>::type
                functor_type;
            vtable_ptr_type * f_vptr
                = detail::get_table<
                      functor_type
                    , R(A0 , A1)
                  >::template get<
                      IArchive
                    , OArchive
                  >();
            if(vptr == f_vptr && !empty())
            {
                if (sizeof(functor_type) <= sizeof(void *)) 
                {
                    vptr->destruct(&object);
                    new (&object) functor_type(boost::forward<Functor>(f));
                }
                else if (object)
                {
                    vptr->destruct(&object);
                    new (object) functor_type(boost::forward<Functor>(f));
                }
                else
                {
                    object = new functor_type(boost::forward<Functor>(f));
                }
            }
            else
            {
                if (!empty())
                {
                    vptr->static_delete(&object);
                    vptr = 0;
                    object = 0;
                }
                if (!detail::is_empty_function(f))
                {
                    if (sizeof(functor_type) <= sizeof(void *)) 
                    {
                        new (&object) functor_type(boost::forward<Functor>(f));
                    }
                    else
                    {
                        object = new functor_type(boost::forward<Functor>(f));
                    }
                    vptr = f_vptr;
                }
            }
            return *this;
        }
        template <typename T>
        function_base & operator=(BOOST_FWD_REF(T) t)
        {
            return assign(boost::forward<T>(t));
        }
        function_base & operator=(BOOST_COPY_ASSIGN_REF(function_base) t)
        {
            return assign(t);
        }
        function_base & operator=(BOOST_RV_REF(function_base) t)
        {
            if(this != &t)
            {
                reset();
                vptr = t.vptr;
                object = t.object;
                t.vptr = 0;
                t.object = 0;
            }
            return *this;
        }
        function_base &swap(function_base& f)
        {
            std::swap(vptr, f.vptr);
            std::swap(object, f.object);
            return *this;
        }
        bool empty() const
        {
            return (vptr == 0) && (object == 0);
        }
        operator typename util::safe_bool<function_base>::result_type() const
        {
            return util::safe_bool<function_base>()(!empty());
        }
        bool operator!() const
        {
            return empty();
        }
        void reset()
        {
            if (!empty())
            {
                vptr->static_delete(&object);
                vptr = 0;
                object = 0;
            }
        }
        BOOST_FORCEINLINE R operator()(A0 a0 , A1 a1) const
        {
            if (empty()) {
                throw std::runtime_error("function_base::operator(): "
                    "function object should not be empty");
            }
            return vptr->invoke(&object , a0 , a1);
        }
        BOOST_FORCEINLINE R operator()(A0 a0 , A1 a1)
        {
            if (empty()) {
                throw std::runtime_error("function_base::operator(): "
                    "function object should not be empty");
            }
            return vptr->invoke(&object , a0 , a1);
        }
    private:
        BOOST_COPYABLE_AND_MOVABLE(function_base);
    protected:
        vtable_ptr_type *vptr;
        mutable void *object;
    };
}}
namespace hpx { namespace util {
    template <
        typename R
      , typename A0 , typename A1 , typename A2
      , typename IArchive
      , typename OArchive
    >
    struct function_base<
        R(A0 , A1 , A2)
      , IArchive
      , OArchive
    >
    {
        function_base()
            : vptr(0)
            , object(0)
        {}
        ~function_base()
        {
            if(object)
            {
                vptr->static_delete(&object);
            }
        }
        typedef R result_type;
        typedef
            detail::vtable_ptr_base<
                R(A0 , A1 , A2)
              , IArchive
              , OArchive
            > vtable_ptr_type;
        template <typename Functor>
        explicit function_base(
            BOOST_FWD_REF(Functor) f
          , typename ::boost::disable_if<
                typename boost::is_same<
                    function_base
                  , typename util::decay<Functor>::type
                >::type
            >::type * dummy = 0
        )
            : vptr(0)
            , object(0)
        {
            if (!detail::is_empty_function(f))
            {
                typedef
                    typename util::decay<Functor>::type
                    functor_type;
                vptr = detail::get_table<
                            functor_type
                          , R(A0 , A1 , A2)
                        >::template get<
                            IArchive
                          , OArchive
                        >();
                if (sizeof(functor_type) <= sizeof(void *)) 
                {
                    new (&object) functor_type(boost::forward<Functor>(f));
                }
                else
                {
                    object = new functor_type(boost::forward<Functor>(f));
                }
            }
        }
        function_base(function_base const & other)
            : vptr(0)
            , object(0)
        {
            assign(other);
        }
        function_base(BOOST_RV_REF(function_base) other)
            : vptr(other.vptr)
            , object(other.object)
        {
            other.vptr = 0;
            other.object = 0;
        }
        function_base &assign(function_base const & other)
        {
            if(&other != this)
            {
                if(vptr == other.vptr && !empty())
                {
                    vptr->copy(&other.object, &object);
                }
                else
                {
                    reset();
                    if(!other.empty())
                    {
                        other.vptr->clone(&other.object, &object);
                        vptr = other.vptr;
                    }
                }
            }
            return *this;
        }
        template <typename Functor>
        function_base & assign(BOOST_FWD_REF(Functor) f)
        {
            if (this == &f)
                return *this;
            typedef
                typename util::decay<Functor>::type
                functor_type;
            vtable_ptr_type * f_vptr
                = detail::get_table<
                      functor_type
                    , R(A0 , A1 , A2)
                  >::template get<
                      IArchive
                    , OArchive
                  >();
            if(vptr == f_vptr && !empty())
            {
                if (sizeof(functor_type) <= sizeof(void *)) 
                {
                    vptr->destruct(&object);
                    new (&object) functor_type(boost::forward<Functor>(f));
                }
                else if (object)
                {
                    vptr->destruct(&object);
                    new (object) functor_type(boost::forward<Functor>(f));
                }
                else
                {
                    object = new functor_type(boost::forward<Functor>(f));
                }
            }
            else
            {
                if (!empty())
                {
                    vptr->static_delete(&object);
                    vptr = 0;
                    object = 0;
                }
                if (!detail::is_empty_function(f))
                {
                    if (sizeof(functor_type) <= sizeof(void *)) 
                    {
                        new (&object) functor_type(boost::forward<Functor>(f));
                    }
                    else
                    {
                        object = new functor_type(boost::forward<Functor>(f));
                    }
                    vptr = f_vptr;
                }
            }
            return *this;
        }
        template <typename T>
        function_base & operator=(BOOST_FWD_REF(T) t)
        {
            return assign(boost::forward<T>(t));
        }
        function_base & operator=(BOOST_COPY_ASSIGN_REF(function_base) t)
        {
            return assign(t);
        }
        function_base & operator=(BOOST_RV_REF(function_base) t)
        {
            if(this != &t)
            {
                reset();
                vptr = t.vptr;
                object = t.object;
                t.vptr = 0;
                t.object = 0;
            }
            return *this;
        }
        function_base &swap(function_base& f)
        {
            std::swap(vptr, f.vptr);
            std::swap(object, f.object);
            return *this;
        }
        bool empty() const
        {
            return (vptr == 0) && (object == 0);
        }
        operator typename util::safe_bool<function_base>::result_type() const
        {
            return util::safe_bool<function_base>()(!empty());
        }
        bool operator!() const
        {
            return empty();
        }
        void reset()
        {
            if (!empty())
            {
                vptr->static_delete(&object);
                vptr = 0;
                object = 0;
            }
        }
        BOOST_FORCEINLINE R operator()(A0 a0 , A1 a1 , A2 a2) const
        {
            if (empty()) {
                throw std::runtime_error("function_base::operator(): "
                    "function object should not be empty");
            }
            return vptr->invoke(&object , a0 , a1 , a2);
        }
        BOOST_FORCEINLINE R operator()(A0 a0 , A1 a1 , A2 a2)
        {
            if (empty()) {
                throw std::runtime_error("function_base::operator(): "
                    "function object should not be empty");
            }
            return vptr->invoke(&object , a0 , a1 , a2);
        }
    private:
        BOOST_COPYABLE_AND_MOVABLE(function_base);
    protected:
        vtable_ptr_type *vptr;
        mutable void *object;
    };
}}
namespace hpx { namespace util {
    template <
        typename R
      , typename A0 , typename A1 , typename A2 , typename A3
      , typename IArchive
      , typename OArchive
    >
    struct function_base<
        R(A0 , A1 , A2 , A3)
      , IArchive
      , OArchive
    >
    {
        function_base()
            : vptr(0)
            , object(0)
        {}
        ~function_base()
        {
            if(object)
            {
                vptr->static_delete(&object);
            }
        }
        typedef R result_type;
        typedef
            detail::vtable_ptr_base<
                R(A0 , A1 , A2 , A3)
              , IArchive
              , OArchive
            > vtable_ptr_type;
        template <typename Functor>
        explicit function_base(
            BOOST_FWD_REF(Functor) f
          , typename ::boost::disable_if<
                typename boost::is_same<
                    function_base
                  , typename util::decay<Functor>::type
                >::type
            >::type * dummy = 0
        )
            : vptr(0)
            , object(0)
        {
            if (!detail::is_empty_function(f))
            {
                typedef
                    typename util::decay<Functor>::type
                    functor_type;
                vptr = detail::get_table<
                            functor_type
                          , R(A0 , A1 , A2 , A3)
                        >::template get<
                            IArchive
                          , OArchive
                        >();
                if (sizeof(functor_type) <= sizeof(void *)) 
                {
                    new (&object) functor_type(boost::forward<Functor>(f));
                }
                else
                {
                    object = new functor_type(boost::forward<Functor>(f));
                }
            }
        }
        function_base(function_base const & other)
            : vptr(0)
            , object(0)
        {
            assign(other);
        }
        function_base(BOOST_RV_REF(function_base) other)
            : vptr(other.vptr)
            , object(other.object)
        {
            other.vptr = 0;
            other.object = 0;
        }
        function_base &assign(function_base const & other)
        {
            if(&other != this)
            {
                if(vptr == other.vptr && !empty())
                {
                    vptr->copy(&other.object, &object);
                }
                else
                {
                    reset();
                    if(!other.empty())
                    {
                        other.vptr->clone(&other.object, &object);
                        vptr = other.vptr;
                    }
                }
            }
            return *this;
        }
        template <typename Functor>
        function_base & assign(BOOST_FWD_REF(Functor) f)
        {
            if (this == &f)
                return *this;
            typedef
                typename util::decay<Functor>::type
                functor_type;
            vtable_ptr_type * f_vptr
                = detail::get_table<
                      functor_type
                    , R(A0 , A1 , A2 , A3)
                  >::template get<
                      IArchive
                    , OArchive
                  >();
            if(vptr == f_vptr && !empty())
            {
                if (sizeof(functor_type) <= sizeof(void *)) 
                {
                    vptr->destruct(&object);
                    new (&object) functor_type(boost::forward<Functor>(f));
                }
                else if (object)
                {
                    vptr->destruct(&object);
                    new (object) functor_type(boost::forward<Functor>(f));
                }
                else
                {
                    object = new functor_type(boost::forward<Functor>(f));
                }
            }
            else
            {
                if (!empty())
                {
                    vptr->static_delete(&object);
                    vptr = 0;
                    object = 0;
                }
                if (!detail::is_empty_function(f))
                {
                    if (sizeof(functor_type) <= sizeof(void *)) 
                    {
                        new (&object) functor_type(boost::forward<Functor>(f));
                    }
                    else
                    {
                        object = new functor_type(boost::forward<Functor>(f));
                    }
                    vptr = f_vptr;
                }
            }
            return *this;
        }
        template <typename T>
        function_base & operator=(BOOST_FWD_REF(T) t)
        {
            return assign(boost::forward<T>(t));
        }
        function_base & operator=(BOOST_COPY_ASSIGN_REF(function_base) t)
        {
            return assign(t);
        }
        function_base & operator=(BOOST_RV_REF(function_base) t)
        {
            if(this != &t)
            {
                reset();
                vptr = t.vptr;
                object = t.object;
                t.vptr = 0;
                t.object = 0;
            }
            return *this;
        }
        function_base &swap(function_base& f)
        {
            std::swap(vptr, f.vptr);
            std::swap(object, f.object);
            return *this;
        }
        bool empty() const
        {
            return (vptr == 0) && (object == 0);
        }
        operator typename util::safe_bool<function_base>::result_type() const
        {
            return util::safe_bool<function_base>()(!empty());
        }
        bool operator!() const
        {
            return empty();
        }
        void reset()
        {
            if (!empty())
            {
                vptr->static_delete(&object);
                vptr = 0;
                object = 0;
            }
        }
        BOOST_FORCEINLINE R operator()(A0 a0 , A1 a1 , A2 a2 , A3 a3) const
        {
            if (empty()) {
                throw std::runtime_error("function_base::operator(): "
                    "function object should not be empty");
            }
            return vptr->invoke(&object , a0 , a1 , a2 , a3);
        }
        BOOST_FORCEINLINE R operator()(A0 a0 , A1 a1 , A2 a2 , A3 a3)
        {
            if (empty()) {
                throw std::runtime_error("function_base::operator(): "
                    "function object should not be empty");
            }
            return vptr->invoke(&object , a0 , a1 , a2 , a3);
        }
    private:
        BOOST_COPYABLE_AND_MOVABLE(function_base);
    protected:
        vtable_ptr_type *vptr;
        mutable void *object;
    };
}}
namespace hpx { namespace util {
    template <
        typename R
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4
      , typename IArchive
      , typename OArchive
    >
    struct function_base<
        R(A0 , A1 , A2 , A3 , A4)
      , IArchive
      , OArchive
    >
    {
        function_base()
            : vptr(0)
            , object(0)
        {}
        ~function_base()
        {
            if(object)
            {
                vptr->static_delete(&object);
            }
        }
        typedef R result_type;
        typedef
            detail::vtable_ptr_base<
                R(A0 , A1 , A2 , A3 , A4)
              , IArchive
              , OArchive
            > vtable_ptr_type;
        template <typename Functor>
        explicit function_base(
            BOOST_FWD_REF(Functor) f
          , typename ::boost::disable_if<
                typename boost::is_same<
                    function_base
                  , typename util::decay<Functor>::type
                >::type
            >::type * dummy = 0
        )
            : vptr(0)
            , object(0)
        {
            if (!detail::is_empty_function(f))
            {
                typedef
                    typename util::decay<Functor>::type
                    functor_type;
                vptr = detail::get_table<
                            functor_type
                          , R(A0 , A1 , A2 , A3 , A4)
                        >::template get<
                            IArchive
                          , OArchive
                        >();
                if (sizeof(functor_type) <= sizeof(void *)) 
                {
                    new (&object) functor_type(boost::forward<Functor>(f));
                }
                else
                {
                    object = new functor_type(boost::forward<Functor>(f));
                }
            }
        }
        function_base(function_base const & other)
            : vptr(0)
            , object(0)
        {
            assign(other);
        }
        function_base(BOOST_RV_REF(function_base) other)
            : vptr(other.vptr)
            , object(other.object)
        {
            other.vptr = 0;
            other.object = 0;
        }
        function_base &assign(function_base const & other)
        {
            if(&other != this)
            {
                if(vptr == other.vptr && !empty())
                {
                    vptr->copy(&other.object, &object);
                }
                else
                {
                    reset();
                    if(!other.empty())
                    {
                        other.vptr->clone(&other.object, &object);
                        vptr = other.vptr;
                    }
                }
            }
            return *this;
        }
        template <typename Functor>
        function_base & assign(BOOST_FWD_REF(Functor) f)
        {
            if (this == &f)
                return *this;
            typedef
                typename util::decay<Functor>::type
                functor_type;
            vtable_ptr_type * f_vptr
                = detail::get_table<
                      functor_type
                    , R(A0 , A1 , A2 , A3 , A4)
                  >::template get<
                      IArchive
                    , OArchive
                  >();
            if(vptr == f_vptr && !empty())
            {
                if (sizeof(functor_type) <= sizeof(void *)) 
                {
                    vptr->destruct(&object);
                    new (&object) functor_type(boost::forward<Functor>(f));
                }
                else if (object)
                {
                    vptr->destruct(&object);
                    new (object) functor_type(boost::forward<Functor>(f));
                }
                else
                {
                    object = new functor_type(boost::forward<Functor>(f));
                }
            }
            else
            {
                if (!empty())
                {
                    vptr->static_delete(&object);
                    vptr = 0;
                    object = 0;
                }
                if (!detail::is_empty_function(f))
                {
                    if (sizeof(functor_type) <= sizeof(void *)) 
                    {
                        new (&object) functor_type(boost::forward<Functor>(f));
                    }
                    else
                    {
                        object = new functor_type(boost::forward<Functor>(f));
                    }
                    vptr = f_vptr;
                }
            }
            return *this;
        }
        template <typename T>
        function_base & operator=(BOOST_FWD_REF(T) t)
        {
            return assign(boost::forward<T>(t));
        }
        function_base & operator=(BOOST_COPY_ASSIGN_REF(function_base) t)
        {
            return assign(t);
        }
        function_base & operator=(BOOST_RV_REF(function_base) t)
        {
            if(this != &t)
            {
                reset();
                vptr = t.vptr;
                object = t.object;
                t.vptr = 0;
                t.object = 0;
            }
            return *this;
        }
        function_base &swap(function_base& f)
        {
            std::swap(vptr, f.vptr);
            std::swap(object, f.object);
            return *this;
        }
        bool empty() const
        {
            return (vptr == 0) && (object == 0);
        }
        operator typename util::safe_bool<function_base>::result_type() const
        {
            return util::safe_bool<function_base>()(!empty());
        }
        bool operator!() const
        {
            return empty();
        }
        void reset()
        {
            if (!empty())
            {
                vptr->static_delete(&object);
                vptr = 0;
                object = 0;
            }
        }
        BOOST_FORCEINLINE R operator()(A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4) const
        {
            if (empty()) {
                throw std::runtime_error("function_base::operator(): "
                    "function object should not be empty");
            }
            return vptr->invoke(&object , a0 , a1 , a2 , a3 , a4);
        }
        BOOST_FORCEINLINE R operator()(A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4)
        {
            if (empty()) {
                throw std::runtime_error("function_base::operator(): "
                    "function object should not be empty");
            }
            return vptr->invoke(&object , a0 , a1 , a2 , a3 , a4);
        }
    private:
        BOOST_COPYABLE_AND_MOVABLE(function_base);
    protected:
        vtable_ptr_type *vptr;
        mutable void *object;
    };
}}
namespace hpx { namespace util {
    template <
        typename R
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5
      , typename IArchive
      , typename OArchive
    >
    struct function_base<
        R(A0 , A1 , A2 , A3 , A4 , A5)
      , IArchive
      , OArchive
    >
    {
        function_base()
            : vptr(0)
            , object(0)
        {}
        ~function_base()
        {
            if(object)
            {
                vptr->static_delete(&object);
            }
        }
        typedef R result_type;
        typedef
            detail::vtable_ptr_base<
                R(A0 , A1 , A2 , A3 , A4 , A5)
              , IArchive
              , OArchive
            > vtable_ptr_type;
        template <typename Functor>
        explicit function_base(
            BOOST_FWD_REF(Functor) f
          , typename ::boost::disable_if<
                typename boost::is_same<
                    function_base
                  , typename util::decay<Functor>::type
                >::type
            >::type * dummy = 0
        )
            : vptr(0)
            , object(0)
        {
            if (!detail::is_empty_function(f))
            {
                typedef
                    typename util::decay<Functor>::type
                    functor_type;
                vptr = detail::get_table<
                            functor_type
                          , R(A0 , A1 , A2 , A3 , A4 , A5)
                        >::template get<
                            IArchive
                          , OArchive
                        >();
                if (sizeof(functor_type) <= sizeof(void *)) 
                {
                    new (&object) functor_type(boost::forward<Functor>(f));
                }
                else
                {
                    object = new functor_type(boost::forward<Functor>(f));
                }
            }
        }
        function_base(function_base const & other)
            : vptr(0)
            , object(0)
        {
            assign(other);
        }
        function_base(BOOST_RV_REF(function_base) other)
            : vptr(other.vptr)
            , object(other.object)
        {
            other.vptr = 0;
            other.object = 0;
        }
        function_base &assign(function_base const & other)
        {
            if(&other != this)
            {
                if(vptr == other.vptr && !empty())
                {
                    vptr->copy(&other.object, &object);
                }
                else
                {
                    reset();
                    if(!other.empty())
                    {
                        other.vptr->clone(&other.object, &object);
                        vptr = other.vptr;
                    }
                }
            }
            return *this;
        }
        template <typename Functor>
        function_base & assign(BOOST_FWD_REF(Functor) f)
        {
            if (this == &f)
                return *this;
            typedef
                typename util::decay<Functor>::type
                functor_type;
            vtable_ptr_type * f_vptr
                = detail::get_table<
                      functor_type
                    , R(A0 , A1 , A2 , A3 , A4 , A5)
                  >::template get<
                      IArchive
                    , OArchive
                  >();
            if(vptr == f_vptr && !empty())
            {
                if (sizeof(functor_type) <= sizeof(void *)) 
                {
                    vptr->destruct(&object);
                    new (&object) functor_type(boost::forward<Functor>(f));
                }
                else if (object)
                {
                    vptr->destruct(&object);
                    new (object) functor_type(boost::forward<Functor>(f));
                }
                else
                {
                    object = new functor_type(boost::forward<Functor>(f));
                }
            }
            else
            {
                if (!empty())
                {
                    vptr->static_delete(&object);
                    vptr = 0;
                    object = 0;
                }
                if (!detail::is_empty_function(f))
                {
                    if (sizeof(functor_type) <= sizeof(void *)) 
                    {
                        new (&object) functor_type(boost::forward<Functor>(f));
                    }
                    else
                    {
                        object = new functor_type(boost::forward<Functor>(f));
                    }
                    vptr = f_vptr;
                }
            }
            return *this;
        }
        template <typename T>
        function_base & operator=(BOOST_FWD_REF(T) t)
        {
            return assign(boost::forward<T>(t));
        }
        function_base & operator=(BOOST_COPY_ASSIGN_REF(function_base) t)
        {
            return assign(t);
        }
        function_base & operator=(BOOST_RV_REF(function_base) t)
        {
            if(this != &t)
            {
                reset();
                vptr = t.vptr;
                object = t.object;
                t.vptr = 0;
                t.object = 0;
            }
            return *this;
        }
        function_base &swap(function_base& f)
        {
            std::swap(vptr, f.vptr);
            std::swap(object, f.object);
            return *this;
        }
        bool empty() const
        {
            return (vptr == 0) && (object == 0);
        }
        operator typename util::safe_bool<function_base>::result_type() const
        {
            return util::safe_bool<function_base>()(!empty());
        }
        bool operator!() const
        {
            return empty();
        }
        void reset()
        {
            if (!empty())
            {
                vptr->static_delete(&object);
                vptr = 0;
                object = 0;
            }
        }
        BOOST_FORCEINLINE R operator()(A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5) const
        {
            if (empty()) {
                throw std::runtime_error("function_base::operator(): "
                    "function object should not be empty");
            }
            return vptr->invoke(&object , a0 , a1 , a2 , a3 , a4 , a5);
        }
        BOOST_FORCEINLINE R operator()(A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5)
        {
            if (empty()) {
                throw std::runtime_error("function_base::operator(): "
                    "function object should not be empty");
            }
            return vptr->invoke(&object , a0 , a1 , a2 , a3 , a4 , a5);
        }
    private:
        BOOST_COPYABLE_AND_MOVABLE(function_base);
    protected:
        vtable_ptr_type *vptr;
        mutable void *object;
    };
}}
namespace hpx { namespace util {
    template <
        typename R
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6
      , typename IArchive
      , typename OArchive
    >
    struct function_base<
        R(A0 , A1 , A2 , A3 , A4 , A5 , A6)
      , IArchive
      , OArchive
    >
    {
        function_base()
            : vptr(0)
            , object(0)
        {}
        ~function_base()
        {
            if(object)
            {
                vptr->static_delete(&object);
            }
        }
        typedef R result_type;
        typedef
            detail::vtable_ptr_base<
                R(A0 , A1 , A2 , A3 , A4 , A5 , A6)
              , IArchive
              , OArchive
            > vtable_ptr_type;
        template <typename Functor>
        explicit function_base(
            BOOST_FWD_REF(Functor) f
          , typename ::boost::disable_if<
                typename boost::is_same<
                    function_base
                  , typename util::decay<Functor>::type
                >::type
            >::type * dummy = 0
        )
            : vptr(0)
            , object(0)
        {
            if (!detail::is_empty_function(f))
            {
                typedef
                    typename util::decay<Functor>::type
                    functor_type;
                vptr = detail::get_table<
                            functor_type
                          , R(A0 , A1 , A2 , A3 , A4 , A5 , A6)
                        >::template get<
                            IArchive
                          , OArchive
                        >();
                if (sizeof(functor_type) <= sizeof(void *)) 
                {
                    new (&object) functor_type(boost::forward<Functor>(f));
                }
                else
                {
                    object = new functor_type(boost::forward<Functor>(f));
                }
            }
        }
        function_base(function_base const & other)
            : vptr(0)
            , object(0)
        {
            assign(other);
        }
        function_base(BOOST_RV_REF(function_base) other)
            : vptr(other.vptr)
            , object(other.object)
        {
            other.vptr = 0;
            other.object = 0;
        }
        function_base &assign(function_base const & other)
        {
            if(&other != this)
            {
                if(vptr == other.vptr && !empty())
                {
                    vptr->copy(&other.object, &object);
                }
                else
                {
                    reset();
                    if(!other.empty())
                    {
                        other.vptr->clone(&other.object, &object);
                        vptr = other.vptr;
                    }
                }
            }
            return *this;
        }
        template <typename Functor>
        function_base & assign(BOOST_FWD_REF(Functor) f)
        {
            if (this == &f)
                return *this;
            typedef
                typename util::decay<Functor>::type
                functor_type;
            vtable_ptr_type * f_vptr
                = detail::get_table<
                      functor_type
                    , R(A0 , A1 , A2 , A3 , A4 , A5 , A6)
                  >::template get<
                      IArchive
                    , OArchive
                  >();
            if(vptr == f_vptr && !empty())
            {
                if (sizeof(functor_type) <= sizeof(void *)) 
                {
                    vptr->destruct(&object);
                    new (&object) functor_type(boost::forward<Functor>(f));
                }
                else if (object)
                {
                    vptr->destruct(&object);
                    new (object) functor_type(boost::forward<Functor>(f));
                }
                else
                {
                    object = new functor_type(boost::forward<Functor>(f));
                }
            }
            else
            {
                if (!empty())
                {
                    vptr->static_delete(&object);
                    vptr = 0;
                    object = 0;
                }
                if (!detail::is_empty_function(f))
                {
                    if (sizeof(functor_type) <= sizeof(void *)) 
                    {
                        new (&object) functor_type(boost::forward<Functor>(f));
                    }
                    else
                    {
                        object = new functor_type(boost::forward<Functor>(f));
                    }
                    vptr = f_vptr;
                }
            }
            return *this;
        }
        template <typename T>
        function_base & operator=(BOOST_FWD_REF(T) t)
        {
            return assign(boost::forward<T>(t));
        }
        function_base & operator=(BOOST_COPY_ASSIGN_REF(function_base) t)
        {
            return assign(t);
        }
        function_base & operator=(BOOST_RV_REF(function_base) t)
        {
            if(this != &t)
            {
                reset();
                vptr = t.vptr;
                object = t.object;
                t.vptr = 0;
                t.object = 0;
            }
            return *this;
        }
        function_base &swap(function_base& f)
        {
            std::swap(vptr, f.vptr);
            std::swap(object, f.object);
            return *this;
        }
        bool empty() const
        {
            return (vptr == 0) && (object == 0);
        }
        operator typename util::safe_bool<function_base>::result_type() const
        {
            return util::safe_bool<function_base>()(!empty());
        }
        bool operator!() const
        {
            return empty();
        }
        void reset()
        {
            if (!empty())
            {
                vptr->static_delete(&object);
                vptr = 0;
                object = 0;
            }
        }
        BOOST_FORCEINLINE R operator()(A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6) const
        {
            if (empty()) {
                throw std::runtime_error("function_base::operator(): "
                    "function object should not be empty");
            }
            return vptr->invoke(&object , a0 , a1 , a2 , a3 , a4 , a5 , a6);
        }
        BOOST_FORCEINLINE R operator()(A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6)
        {
            if (empty()) {
                throw std::runtime_error("function_base::operator(): "
                    "function object should not be empty");
            }
            return vptr->invoke(&object , a0 , a1 , a2 , a3 , a4 , a5 , a6);
        }
    private:
        BOOST_COPYABLE_AND_MOVABLE(function_base);
    protected:
        vtable_ptr_type *vptr;
        mutable void *object;
    };
}}
namespace hpx { namespace util {
    template <
        typename R
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7
      , typename IArchive
      , typename OArchive
    >
    struct function_base<
        R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7)
      , IArchive
      , OArchive
    >
    {
        function_base()
            : vptr(0)
            , object(0)
        {}
        ~function_base()
        {
            if(object)
            {
                vptr->static_delete(&object);
            }
        }
        typedef R result_type;
        typedef
            detail::vtable_ptr_base<
                R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7)
              , IArchive
              , OArchive
            > vtable_ptr_type;
        template <typename Functor>
        explicit function_base(
            BOOST_FWD_REF(Functor) f
          , typename ::boost::disable_if<
                typename boost::is_same<
                    function_base
                  , typename util::decay<Functor>::type
                >::type
            >::type * dummy = 0
        )
            : vptr(0)
            , object(0)
        {
            if (!detail::is_empty_function(f))
            {
                typedef
                    typename util::decay<Functor>::type
                    functor_type;
                vptr = detail::get_table<
                            functor_type
                          , R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7)
                        >::template get<
                            IArchive
                          , OArchive
                        >();
                if (sizeof(functor_type) <= sizeof(void *)) 
                {
                    new (&object) functor_type(boost::forward<Functor>(f));
                }
                else
                {
                    object = new functor_type(boost::forward<Functor>(f));
                }
            }
        }
        function_base(function_base const & other)
            : vptr(0)
            , object(0)
        {
            assign(other);
        }
        function_base(BOOST_RV_REF(function_base) other)
            : vptr(other.vptr)
            , object(other.object)
        {
            other.vptr = 0;
            other.object = 0;
        }
        function_base &assign(function_base const & other)
        {
            if(&other != this)
            {
                if(vptr == other.vptr && !empty())
                {
                    vptr->copy(&other.object, &object);
                }
                else
                {
                    reset();
                    if(!other.empty())
                    {
                        other.vptr->clone(&other.object, &object);
                        vptr = other.vptr;
                    }
                }
            }
            return *this;
        }
        template <typename Functor>
        function_base & assign(BOOST_FWD_REF(Functor) f)
        {
            if (this == &f)
                return *this;
            typedef
                typename util::decay<Functor>::type
                functor_type;
            vtable_ptr_type * f_vptr
                = detail::get_table<
                      functor_type
                    , R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7)
                  >::template get<
                      IArchive
                    , OArchive
                  >();
            if(vptr == f_vptr && !empty())
            {
                if (sizeof(functor_type) <= sizeof(void *)) 
                {
                    vptr->destruct(&object);
                    new (&object) functor_type(boost::forward<Functor>(f));
                }
                else if (object)
                {
                    vptr->destruct(&object);
                    new (object) functor_type(boost::forward<Functor>(f));
                }
                else
                {
                    object = new functor_type(boost::forward<Functor>(f));
                }
            }
            else
            {
                if (!empty())
                {
                    vptr->static_delete(&object);
                    vptr = 0;
                    object = 0;
                }
                if (!detail::is_empty_function(f))
                {
                    if (sizeof(functor_type) <= sizeof(void *)) 
                    {
                        new (&object) functor_type(boost::forward<Functor>(f));
                    }
                    else
                    {
                        object = new functor_type(boost::forward<Functor>(f));
                    }
                    vptr = f_vptr;
                }
            }
            return *this;
        }
        template <typename T>
        function_base & operator=(BOOST_FWD_REF(T) t)
        {
            return assign(boost::forward<T>(t));
        }
        function_base & operator=(BOOST_COPY_ASSIGN_REF(function_base) t)
        {
            return assign(t);
        }
        function_base & operator=(BOOST_RV_REF(function_base) t)
        {
            if(this != &t)
            {
                reset();
                vptr = t.vptr;
                object = t.object;
                t.vptr = 0;
                t.object = 0;
            }
            return *this;
        }
        function_base &swap(function_base& f)
        {
            std::swap(vptr, f.vptr);
            std::swap(object, f.object);
            return *this;
        }
        bool empty() const
        {
            return (vptr == 0) && (object == 0);
        }
        operator typename util::safe_bool<function_base>::result_type() const
        {
            return util::safe_bool<function_base>()(!empty());
        }
        bool operator!() const
        {
            return empty();
        }
        void reset()
        {
            if (!empty())
            {
                vptr->static_delete(&object);
                vptr = 0;
                object = 0;
            }
        }
        BOOST_FORCEINLINE R operator()(A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 , A7 a7) const
        {
            if (empty()) {
                throw std::runtime_error("function_base::operator(): "
                    "function object should not be empty");
            }
            return vptr->invoke(&object , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7);
        }
        BOOST_FORCEINLINE R operator()(A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 , A7 a7)
        {
            if (empty()) {
                throw std::runtime_error("function_base::operator(): "
                    "function object should not be empty");
            }
            return vptr->invoke(&object , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7);
        }
    private:
        BOOST_COPYABLE_AND_MOVABLE(function_base);
    protected:
        vtable_ptr_type *vptr;
        mutable void *object;
    };
}}
