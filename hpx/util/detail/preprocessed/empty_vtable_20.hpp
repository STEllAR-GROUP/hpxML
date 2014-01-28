// Copyright (c) 2007-2013 Hartmut Kaiser
// Copyright (c) 2012-2013 Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This file has been automatically generated using the Boost.Wave tool.
// Do not edit manually.


namespace hpx { namespace util { namespace detail
{
    template <
        typename R
      
      , typename IArchive
      , typename OArchive
    >
    struct empty_vtable<
        R()
      , IArchive
      , OArchive
    >
        : empty_vtable_base
    {
        typedef R (*functor_type)();
        static vtable_ptr_base<
            R()
          , IArchive
          , OArchive
        > *get_ptr()
        {
            return
                get_empty_table<
                    R()
                >::template get<IArchive, OArchive>();
        }
        BOOST_ATTRIBUTE_NORETURN static R
        invoke(void ** 
            )
        {
            hpx::throw_exception(bad_function_call,
                "empty function object should not be used",
                "empty_vtable::operator()");
        }
    };
}}}
namespace hpx { namespace util { namespace detail
{
    template <
        typename R
      , typename A0
      , typename IArchive
      , typename OArchive
    >
    struct empty_vtable<
        R(A0)
      , IArchive
      , OArchive
    >
        : empty_vtable_base
    {
        typedef R (*functor_type)(A0);
        static vtable_ptr_base<
            R(A0)
          , IArchive
          , OArchive
        > *get_ptr()
        {
            return
                get_empty_table<
                    R(A0)
                >::template get<IArchive, OArchive>();
        }
        BOOST_ATTRIBUTE_NORETURN static R
        invoke(void ** 
            , A0 &&)
        {
            hpx::throw_exception(bad_function_call,
                "empty function object should not be used",
                "empty_vtable::operator()");
        }
    };
}}}
namespace hpx { namespace util { namespace detail
{
    template <
        typename R
      , typename A0 , typename A1
      , typename IArchive
      , typename OArchive
    >
    struct empty_vtable<
        R(A0 , A1)
      , IArchive
      , OArchive
    >
        : empty_vtable_base
    {
        typedef R (*functor_type)(A0 , A1);
        static vtable_ptr_base<
            R(A0 , A1)
          , IArchive
          , OArchive
        > *get_ptr()
        {
            return
                get_empty_table<
                    R(A0 , A1)
                >::template get<IArchive, OArchive>();
        }
        BOOST_ATTRIBUTE_NORETURN static R
        invoke(void ** 
            , A0 && , A1 &&)
        {
            hpx::throw_exception(bad_function_call,
                "empty function object should not be used",
                "empty_vtable::operator()");
        }
    };
}}}
namespace hpx { namespace util { namespace detail
{
    template <
        typename R
      , typename A0 , typename A1 , typename A2
      , typename IArchive
      , typename OArchive
    >
    struct empty_vtable<
        R(A0 , A1 , A2)
      , IArchive
      , OArchive
    >
        : empty_vtable_base
    {
        typedef R (*functor_type)(A0 , A1 , A2);
        static vtable_ptr_base<
            R(A0 , A1 , A2)
          , IArchive
          , OArchive
        > *get_ptr()
        {
            return
                get_empty_table<
                    R(A0 , A1 , A2)
                >::template get<IArchive, OArchive>();
        }
        BOOST_ATTRIBUTE_NORETURN static R
        invoke(void ** 
            , A0 && , A1 && , A2 &&)
        {
            hpx::throw_exception(bad_function_call,
                "empty function object should not be used",
                "empty_vtable::operator()");
        }
    };
}}}
namespace hpx { namespace util { namespace detail
{
    template <
        typename R
      , typename A0 , typename A1 , typename A2 , typename A3
      , typename IArchive
      , typename OArchive
    >
    struct empty_vtable<
        R(A0 , A1 , A2 , A3)
      , IArchive
      , OArchive
    >
        : empty_vtable_base
    {
        typedef R (*functor_type)(A0 , A1 , A2 , A3);
        static vtable_ptr_base<
            R(A0 , A1 , A2 , A3)
          , IArchive
          , OArchive
        > *get_ptr()
        {
            return
                get_empty_table<
                    R(A0 , A1 , A2 , A3)
                >::template get<IArchive, OArchive>();
        }
        BOOST_ATTRIBUTE_NORETURN static R
        invoke(void ** 
            , A0 && , A1 && , A2 && , A3 &&)
        {
            hpx::throw_exception(bad_function_call,
                "empty function object should not be used",
                "empty_vtable::operator()");
        }
    };
}}}
namespace hpx { namespace util { namespace detail
{
    template <
        typename R
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4
      , typename IArchive
      , typename OArchive
    >
    struct empty_vtable<
        R(A0 , A1 , A2 , A3 , A4)
      , IArchive
      , OArchive
    >
        : empty_vtable_base
    {
        typedef R (*functor_type)(A0 , A1 , A2 , A3 , A4);
        static vtable_ptr_base<
            R(A0 , A1 , A2 , A3 , A4)
          , IArchive
          , OArchive
        > *get_ptr()
        {
            return
                get_empty_table<
                    R(A0 , A1 , A2 , A3 , A4)
                >::template get<IArchive, OArchive>();
        }
        BOOST_ATTRIBUTE_NORETURN static R
        invoke(void ** 
            , A0 && , A1 && , A2 && , A3 && , A4 &&)
        {
            hpx::throw_exception(bad_function_call,
                "empty function object should not be used",
                "empty_vtable::operator()");
        }
    };
}}}
namespace hpx { namespace util { namespace detail
{
    template <
        typename R
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5
      , typename IArchive
      , typename OArchive
    >
    struct empty_vtable<
        R(A0 , A1 , A2 , A3 , A4 , A5)
      , IArchive
      , OArchive
    >
        : empty_vtable_base
    {
        typedef R (*functor_type)(A0 , A1 , A2 , A3 , A4 , A5);
        static vtable_ptr_base<
            R(A0 , A1 , A2 , A3 , A4 , A5)
          , IArchive
          , OArchive
        > *get_ptr()
        {
            return
                get_empty_table<
                    R(A0 , A1 , A2 , A3 , A4 , A5)
                >::template get<IArchive, OArchive>();
        }
        BOOST_ATTRIBUTE_NORETURN static R
        invoke(void ** 
            , A0 && , A1 && , A2 && , A3 && , A4 && , A5 &&)
        {
            hpx::throw_exception(bad_function_call,
                "empty function object should not be used",
                "empty_vtable::operator()");
        }
    };
}}}
namespace hpx { namespace util { namespace detail
{
    template <
        typename R
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6
      , typename IArchive
      , typename OArchive
    >
    struct empty_vtable<
        R(A0 , A1 , A2 , A3 , A4 , A5 , A6)
      , IArchive
      , OArchive
    >
        : empty_vtable_base
    {
        typedef R (*functor_type)(A0 , A1 , A2 , A3 , A4 , A5 , A6);
        static vtable_ptr_base<
            R(A0 , A1 , A2 , A3 , A4 , A5 , A6)
          , IArchive
          , OArchive
        > *get_ptr()
        {
            return
                get_empty_table<
                    R(A0 , A1 , A2 , A3 , A4 , A5 , A6)
                >::template get<IArchive, OArchive>();
        }
        BOOST_ATTRIBUTE_NORETURN static R
        invoke(void ** 
            , A0 && , A1 && , A2 && , A3 && , A4 && , A5 && , A6 &&)
        {
            hpx::throw_exception(bad_function_call,
                "empty function object should not be used",
                "empty_vtable::operator()");
        }
    };
}}}
namespace hpx { namespace util { namespace detail
{
    template <
        typename R
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7
      , typename IArchive
      , typename OArchive
    >
    struct empty_vtable<
        R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7)
      , IArchive
      , OArchive
    >
        : empty_vtable_base
    {
        typedef R (*functor_type)(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7);
        static vtable_ptr_base<
            R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7)
          , IArchive
          , OArchive
        > *get_ptr()
        {
            return
                get_empty_table<
                    R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7)
                >::template get<IArchive, OArchive>();
        }
        BOOST_ATTRIBUTE_NORETURN static R
        invoke(void ** 
            , A0 && , A1 && , A2 && , A3 && , A4 && , A5 && , A6 && , A7 &&)
        {
            hpx::throw_exception(bad_function_call,
                "empty function object should not be used",
                "empty_vtable::operator()");
        }
    };
}}}
namespace hpx { namespace util { namespace detail
{
    template <
        typename R
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8
      , typename IArchive
      , typename OArchive
    >
    struct empty_vtable<
        R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8)
      , IArchive
      , OArchive
    >
        : empty_vtable_base
    {
        typedef R (*functor_type)(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8);
        static vtable_ptr_base<
            R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8)
          , IArchive
          , OArchive
        > *get_ptr()
        {
            return
                get_empty_table<
                    R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8)
                >::template get<IArchive, OArchive>();
        }
        BOOST_ATTRIBUTE_NORETURN static R
        invoke(void ** 
            , A0 && , A1 && , A2 && , A3 && , A4 && , A5 && , A6 && , A7 && , A8 &&)
        {
            hpx::throw_exception(bad_function_call,
                "empty function object should not be used",
                "empty_vtable::operator()");
        }
    };
}}}
namespace hpx { namespace util { namespace detail
{
    template <
        typename R
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9
      , typename IArchive
      , typename OArchive
    >
    struct empty_vtable<
        R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9)
      , IArchive
      , OArchive
    >
        : empty_vtable_base
    {
        typedef R (*functor_type)(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9);
        static vtable_ptr_base<
            R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9)
          , IArchive
          , OArchive
        > *get_ptr()
        {
            return
                get_empty_table<
                    R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9)
                >::template get<IArchive, OArchive>();
        }
        BOOST_ATTRIBUTE_NORETURN static R
        invoke(void ** 
            , A0 && , A1 && , A2 && , A3 && , A4 && , A5 && , A6 && , A7 && , A8 && , A9 &&)
        {
            hpx::throw_exception(bad_function_call,
                "empty function object should not be used",
                "empty_vtable::operator()");
        }
    };
}}}
namespace hpx { namespace util { namespace detail
{
    template <
        typename R
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10
      , typename IArchive
      , typename OArchive
    >
    struct empty_vtable<
        R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10)
      , IArchive
      , OArchive
    >
        : empty_vtable_base
    {
        typedef R (*functor_type)(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10);
        static vtable_ptr_base<
            R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10)
          , IArchive
          , OArchive
        > *get_ptr()
        {
            return
                get_empty_table<
                    R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10)
                >::template get<IArchive, OArchive>();
        }
        BOOST_ATTRIBUTE_NORETURN static R
        invoke(void ** 
            , A0 && , A1 && , A2 && , A3 && , A4 && , A5 && , A6 && , A7 && , A8 && , A9 && , A10 &&)
        {
            hpx::throw_exception(bad_function_call,
                "empty function object should not be used",
                "empty_vtable::operator()");
        }
    };
}}}
namespace hpx { namespace util { namespace detail
{
    template <
        typename R
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11
      , typename IArchive
      , typename OArchive
    >
    struct empty_vtable<
        R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11)
      , IArchive
      , OArchive
    >
        : empty_vtable_base
    {
        typedef R (*functor_type)(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11);
        static vtable_ptr_base<
            R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11)
          , IArchive
          , OArchive
        > *get_ptr()
        {
            return
                get_empty_table<
                    R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11)
                >::template get<IArchive, OArchive>();
        }
        BOOST_ATTRIBUTE_NORETURN static R
        invoke(void ** 
            , A0 && , A1 && , A2 && , A3 && , A4 && , A5 && , A6 && , A7 && , A8 && , A9 && , A10 && , A11 &&)
        {
            hpx::throw_exception(bad_function_call,
                "empty function object should not be used",
                "empty_vtable::operator()");
        }
    };
}}}
namespace hpx { namespace util { namespace detail
{
    template <
        typename R
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12
      , typename IArchive
      , typename OArchive
    >
    struct empty_vtable<
        R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12)
      , IArchive
      , OArchive
    >
        : empty_vtable_base
    {
        typedef R (*functor_type)(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12);
        static vtable_ptr_base<
            R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12)
          , IArchive
          , OArchive
        > *get_ptr()
        {
            return
                get_empty_table<
                    R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12)
                >::template get<IArchive, OArchive>();
        }
        BOOST_ATTRIBUTE_NORETURN static R
        invoke(void ** 
            , A0 && , A1 && , A2 && , A3 && , A4 && , A5 && , A6 && , A7 && , A8 && , A9 && , A10 && , A11 && , A12 &&)
        {
            hpx::throw_exception(bad_function_call,
                "empty function object should not be used",
                "empty_vtable::operator()");
        }
    };
}}}
namespace hpx { namespace util { namespace detail
{
    template <
        typename R
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13
      , typename IArchive
      , typename OArchive
    >
    struct empty_vtable<
        R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13)
      , IArchive
      , OArchive
    >
        : empty_vtable_base
    {
        typedef R (*functor_type)(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13);
        static vtable_ptr_base<
            R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13)
          , IArchive
          , OArchive
        > *get_ptr()
        {
            return
                get_empty_table<
                    R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13)
                >::template get<IArchive, OArchive>();
        }
        BOOST_ATTRIBUTE_NORETURN static R
        invoke(void ** 
            , A0 && , A1 && , A2 && , A3 && , A4 && , A5 && , A6 && , A7 && , A8 && , A9 && , A10 && , A11 && , A12 && , A13 &&)
        {
            hpx::throw_exception(bad_function_call,
                "empty function object should not be used",
                "empty_vtable::operator()");
        }
    };
}}}
namespace hpx { namespace util { namespace detail
{
    template <
        typename R
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14
      , typename IArchive
      , typename OArchive
    >
    struct empty_vtable<
        R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14)
      , IArchive
      , OArchive
    >
        : empty_vtable_base
    {
        typedef R (*functor_type)(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14);
        static vtable_ptr_base<
            R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14)
          , IArchive
          , OArchive
        > *get_ptr()
        {
            return
                get_empty_table<
                    R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14)
                >::template get<IArchive, OArchive>();
        }
        BOOST_ATTRIBUTE_NORETURN static R
        invoke(void ** 
            , A0 && , A1 && , A2 && , A3 && , A4 && , A5 && , A6 && , A7 && , A8 && , A9 && , A10 && , A11 && , A12 && , A13 && , A14 &&)
        {
            hpx::throw_exception(bad_function_call,
                "empty function object should not be used",
                "empty_vtable::operator()");
        }
    };
}}}
namespace hpx { namespace util { namespace detail
{
    template <
        typename R
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15
      , typename IArchive
      , typename OArchive
    >
    struct empty_vtable<
        R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15)
      , IArchive
      , OArchive
    >
        : empty_vtable_base
    {
        typedef R (*functor_type)(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15);
        static vtable_ptr_base<
            R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15)
          , IArchive
          , OArchive
        > *get_ptr()
        {
            return
                get_empty_table<
                    R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15)
                >::template get<IArchive, OArchive>();
        }
        BOOST_ATTRIBUTE_NORETURN static R
        invoke(void ** 
            , A0 && , A1 && , A2 && , A3 && , A4 && , A5 && , A6 && , A7 && , A8 && , A9 && , A10 && , A11 && , A12 && , A13 && , A14 && , A15 &&)
        {
            hpx::throw_exception(bad_function_call,
                "empty function object should not be used",
                "empty_vtable::operator()");
        }
    };
}}}
namespace hpx { namespace util { namespace detail
{
    template <
        typename R
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16
      , typename IArchive
      , typename OArchive
    >
    struct empty_vtable<
        R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16)
      , IArchive
      , OArchive
    >
        : empty_vtable_base
    {
        typedef R (*functor_type)(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16);
        static vtable_ptr_base<
            R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16)
          , IArchive
          , OArchive
        > *get_ptr()
        {
            return
                get_empty_table<
                    R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16)
                >::template get<IArchive, OArchive>();
        }
        BOOST_ATTRIBUTE_NORETURN static R
        invoke(void ** 
            , A0 && , A1 && , A2 && , A3 && , A4 && , A5 && , A6 && , A7 && , A8 && , A9 && , A10 && , A11 && , A12 && , A13 && , A14 && , A15 && , A16 &&)
        {
            hpx::throw_exception(bad_function_call,
                "empty function object should not be used",
                "empty_vtable::operator()");
        }
    };
}}}
namespace hpx { namespace util { namespace detail
{
    template <
        typename R
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17
      , typename IArchive
      , typename OArchive
    >
    struct empty_vtable<
        R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17)
      , IArchive
      , OArchive
    >
        : empty_vtable_base
    {
        typedef R (*functor_type)(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17);
        static vtable_ptr_base<
            R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17)
          , IArchive
          , OArchive
        > *get_ptr()
        {
            return
                get_empty_table<
                    R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17)
                >::template get<IArchive, OArchive>();
        }
        BOOST_ATTRIBUTE_NORETURN static R
        invoke(void ** 
            , A0 && , A1 && , A2 && , A3 && , A4 && , A5 && , A6 && , A7 && , A8 && , A9 && , A10 && , A11 && , A12 && , A13 && , A14 && , A15 && , A16 && , A17 &&)
        {
            hpx::throw_exception(bad_function_call,
                "empty function object should not be used",
                "empty_vtable::operator()");
        }
    };
}}}
namespace hpx { namespace util { namespace detail
{
    template <
        typename R
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18
      , typename IArchive
      , typename OArchive
    >
    struct empty_vtable<
        R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18)
      , IArchive
      , OArchive
    >
        : empty_vtable_base
    {
        typedef R (*functor_type)(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18);
        static vtable_ptr_base<
            R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18)
          , IArchive
          , OArchive
        > *get_ptr()
        {
            return
                get_empty_table<
                    R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18)
                >::template get<IArchive, OArchive>();
        }
        BOOST_ATTRIBUTE_NORETURN static R
        invoke(void ** 
            , A0 && , A1 && , A2 && , A3 && , A4 && , A5 && , A6 && , A7 && , A8 && , A9 && , A10 && , A11 && , A12 && , A13 && , A14 && , A15 && , A16 && , A17 && , A18 &&)
        {
            hpx::throw_exception(bad_function_call,
                "empty function object should not be used",
                "empty_vtable::operator()");
        }
    };
}}}
namespace hpx { namespace util { namespace detail
{
    template <
        typename R
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19
      , typename IArchive
      , typename OArchive
    >
    struct empty_vtable<
        R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19)
      , IArchive
      , OArchive
    >
        : empty_vtable_base
    {
        typedef R (*functor_type)(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19);
        static vtable_ptr_base<
            R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19)
          , IArchive
          , OArchive
        > *get_ptr()
        {
            return
                get_empty_table<
                    R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19)
                >::template get<IArchive, OArchive>();
        }
        BOOST_ATTRIBUTE_NORETURN static R
        invoke(void ** 
            , A0 && , A1 && , A2 && , A3 && , A4 && , A5 && , A6 && , A7 && , A8 && , A9 && , A10 && , A11 && , A12 && , A13 && , A14 && , A15 && , A16 && , A17 && , A18 && , A19 &&)
        {
            hpx::throw_exception(bad_function_call,
                "empty function object should not be used",
                "empty_vtable::operator()");
        }
    };
}}}
namespace hpx { namespace util { namespace detail
{
    template <
        typename R
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20
      , typename IArchive
      , typename OArchive
    >
    struct empty_vtable<
        R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20)
      , IArchive
      , OArchive
    >
        : empty_vtable_base
    {
        typedef R (*functor_type)(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20);
        static vtable_ptr_base<
            R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20)
          , IArchive
          , OArchive
        > *get_ptr()
        {
            return
                get_empty_table<
                    R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20)
                >::template get<IArchive, OArchive>();
        }
        BOOST_ATTRIBUTE_NORETURN static R
        invoke(void ** 
            , A0 && , A1 && , A2 && , A3 && , A4 && , A5 && , A6 && , A7 && , A8 && , A9 && , A10 && , A11 && , A12 && , A13 && , A14 && , A15 && , A16 && , A17 && , A18 && , A19 && , A20 &&)
        {
            hpx::throw_exception(bad_function_call,
                "empty function object should not be used",
                "empty_vtable::operator()");
        }
    };
}}}
namespace hpx { namespace util { namespace detail
{
    template <
        typename R
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21
      , typename IArchive
      , typename OArchive
    >
    struct empty_vtable<
        R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21)
      , IArchive
      , OArchive
    >
        : empty_vtable_base
    {
        typedef R (*functor_type)(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21);
        static vtable_ptr_base<
            R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21)
          , IArchive
          , OArchive
        > *get_ptr()
        {
            return
                get_empty_table<
                    R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21)
                >::template get<IArchive, OArchive>();
        }
        BOOST_ATTRIBUTE_NORETURN static R
        invoke(void ** 
            , A0 && , A1 && , A2 && , A3 && , A4 && , A5 && , A6 && , A7 && , A8 && , A9 && , A10 && , A11 && , A12 && , A13 && , A14 && , A15 && , A16 && , A17 && , A18 && , A19 && , A20 && , A21 &&)
        {
            hpx::throw_exception(bad_function_call,
                "empty function object should not be used",
                "empty_vtable::operator()");
        }
    };
}}}
namespace hpx { namespace util { namespace detail
{
    template <
        typename R
      , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22
      , typename IArchive
      , typename OArchive
    >
    struct empty_vtable<
        R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22)
      , IArchive
      , OArchive
    >
        : empty_vtable_base
    {
        typedef R (*functor_type)(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22);
        static vtable_ptr_base<
            R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22)
          , IArchive
          , OArchive
        > *get_ptr()
        {
            return
                get_empty_table<
                    R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22)
                >::template get<IArchive, OArchive>();
        }
        BOOST_ATTRIBUTE_NORETURN static R
        invoke(void ** 
            , A0 && , A1 && , A2 && , A3 && , A4 && , A5 && , A6 && , A7 && , A8 && , A9 && , A10 && , A11 && , A12 && , A13 && , A14 && , A15 && , A16 && , A17 && , A18 && , A19 && , A20 && , A21 && , A22 &&)
        {
            hpx::throw_exception(bad_function_call,
                "empty function object should not be used",
                "empty_vtable::operator()");
        }
    };
}}}
