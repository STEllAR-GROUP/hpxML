//  Copyright (c) 2011 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#if !BOOST_PP_IS_ITERATING

#ifndef HPX_UTIL_FUNCTION_TEMPLATE_HPP
#define HPX_UTIL_FUNCTION_TEMPLATE_HPP

#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

#include <boost/serialization/utility.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/tracking.hpp>
#include <hpx/util/portable_binary_iarchive.hpp>
#include <hpx/util/portable_binary_oarchive.hpp>

#include <hpx/util/detail/vtable_ptr_base_fwd.hpp>
#include <hpx/util/detail/vtable_ptr_fwd.hpp>
#include <hpx/util/detail/serialization_registration.hpp>
#include <hpx/util/safe_bool.hpp>
#include <boost/move/move.hpp>

#ifndef HPX_FUNCTION_VERSION
#define HPX_FUNCTION_VERSION 0x10
#endif

namespace hpx { namespace util {
    namespace detail
    {
        template <
            typename Functor
          , typename Sig
        >
        struct get_table;

        template <bool>
        struct vtable;
    }

    template <
        typename Sig
      , typename IArchive = void
      , typename OArchive = void
    >
    struct function_base;

    template <
        typename Sig
#if HPX_USE_PORTABLE_ARCHIVES != 0
      , typename IArchive = portable_binary_iarchive
      , typename OArchive = portable_binary_oarchive
#else
      , typename IArchive = boost::archive::binary_iarchive
      , typename OArchive = boost::archive::binary_oarchive
#endif
    >
    struct function : function_base<Sig, IArchive, OArchive>
    {
        typedef function_base<Sig, IArchive, OArchive> base_type;
        function() : base_type() {}

        template <typename Functor>
        function(Functor const& f)
            : base_type(f)
        {}

        template <typename Functor>
        function(BOOST_RV_REF(Functor) f)
          : base_type(boost::move(f))
        {}

        function(base_type const& other)
            : base_type(other)
        {}

        function(BOOST_RV_REF(base_type) other)
            : base_type(boost::move(other))
        {}

    private:
        BOOST_COPYABLE_AND_MOVABLE(function);

        friend class boost::serialization::access;

        void load(IArchive &ar, const unsigned version)
        {
            bool is_empty;
            ar & is_empty;

            if(is_empty)
            {
                this->reset();
            }
            else
            {
                typename base_type::vtable_ptr_type *p = 0;
                ar >> p;
                this->vptr = p->get_ptr();
                delete p;
                this->vptr->load_object(&this->object, ar, version);
            }
        }

        void save(OArchive &ar, const unsigned version) const
        {
            bool is_empty = this->empty();
            ar & is_empty;
            if(!this->empty())
            {
                ar << this->vptr;
                this->vptr->save_object(&this->object, ar, version);
            }
        }

        BOOST_SERIALIZATION_SPLIT_MEMBER();

    };

    template <
        typename Sig
    >
    struct function<Sig, void, void> : function_base<Sig, void, void>
    {
        typedef function_base<Sig, void, void> base_type;
        function() : base_type() {}

        template <typename Functor>
        function(Functor const& f)
            : base_type(f)
        {}

        template <typename Functor>
        function(BOOST_RV_REF(Functor) f)
            : base_type(boost::move(f))
        {}

        function(base_type const& other)
            : base_type(other)
        {}

        function(BOOST_RV_REF(base_type) other)
            : base_type(boost::move(other))
        {}
    };
}}

#define BOOST_PP_ITERATION_PARAMS_1                                             \
    (                                                                           \
        3                                                                       \
      , (                                                                       \
            0                                                                   \
          , HPX_FUNCTION_LIMIT                                                  \
          , <hpx/util/detail/function_template.hpp>                             \
        )                                                                       \
    )                                                                           \
/**/
#include BOOST_PP_ITERATE()

#endif

#else

#define N BOOST_PP_ITERATION()

namespace hpx { namespace util {

    template <
        typename R
      BOOST_PP_COMMA_IF(N) BOOST_PP_ENUM_PARAMS(N, typename A)
      , typename IArchive
      , typename OArchive
    >
    struct function_base<
        R(BOOST_PP_ENUM_PARAMS(N, A))
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
                R(BOOST_PP_ENUM_PARAMS(N, A))
              , IArchive
              , OArchive
            > vtable_ptr_type;

        template <typename Functor>
        function_base(Functor const& f)
            : vptr(
                detail::get_table<Functor, R(BOOST_PP_ENUM_PARAMS(N, A))>::template get<
                    IArchive
                  , OArchive
                >()
            )
            , object(0)
        {
            static const bool is_small = sizeof(Functor) <= sizeof(void *);
            if(is_small)
            {
                new (&object) Functor(f);
            }
            else
            {
                object = new Functor(f);
            }
        }

        function_base(function_base const& other)
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
                    vptr->move(&other.object, &object);
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
        function_base & assign(Functor const & f)
        {
            static const bool is_small = sizeof(Functor) <= sizeof(void *);
            vtable_ptr_type * f_vptr
                = detail::get_table<Functor, R(BOOST_PP_ENUM_PARAMS(N, A))>::template get<
                    IArchive
                  , OArchive
                >();

            if(vptr == f_vptr && !empty())
            {
                vptr->destruct(&object);
                if(is_small)
                {
                    new (&object) Functor(f);
                }
                else
                {
                    object = new Functor(f);
                }
            }
            else
            {
                if(!empty())
                {
                    vptr->destruct(&object);
                }

                if(is_small)
                {
                    new (&object) Functor(f);
                }
                else
                {
                    object = new Functor(f);
                }
                vptr = f_vptr;
            }
            return *this;
        }

        template <typename T>
        function_base & operator=(T const& t)
        {
            return assign(t);
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

        R operator()(BOOST_PP_ENUM_BINARY_PARAMS(N, A, a)) const
        {
            BOOST_ASSERT(!empty());
            return vptr->invoke(&object BOOST_PP_COMMA_IF(N) BOOST_PP_ENUM_PARAMS(N, a));
        }

        R operator()(BOOST_PP_ENUM_BINARY_PARAMS(N, A, a))
        {
            BOOST_ASSERT(!empty());
            return vptr->invoke(&object BOOST_PP_COMMA_IF(N) BOOST_PP_ENUM_PARAMS(N, a));
        }

    private:
        BOOST_COPYABLE_AND_MOVABLE(function_base);

    protected:
        vtable_ptr_type *vptr;
        mutable void *object;
    };
}}

#endif

