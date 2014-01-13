//  Copyright (c) 2011 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef HPX_COMPONENTS_REMOTE_OBJECT_OBJECT_HPP
#define HPX_COMPONENTS_REMOTE_OBJECT_OBJECT_HPP

#include <hpx/util/move.hpp>
#include <hpx/components/remote_object/stubs/remote_object.hpp>
#include <hpx/lcos/future.hpp>
#include <hpx/traits/promise_remote_result.hpp>
#include <hpx/runtime/naming/address.hpp>
#include <hpx/util/decay.hpp>

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

namespace hpx { namespace components
{
    namespace remote_object
    {
        // helper functor, casts void pointer to the right object type and
        // invokes the passed functor
        template <typename T, typename F>
        struct invoke_apply_fun
        {

            typedef
                typename util::result_of<typename hpx::util::decay<F>::type(T &)>::type
                result_type;

            invoke_apply_fun() {}

            template <typename Functor>
            invoke_apply_fun(
                Functor && f_
              , typename ::boost::disable_if<
                    typename boost::is_same<
                        invoke_apply_fun
                      , typename util::decay<Functor>::type
                    >::type
                >::type * = 0
            )
                : f(std::forward<Functor>(f_))
            {}

            invoke_apply_fun(invoke_apply_fun const & other)
                : f(other.f)
            {}

            invoke_apply_fun(invoke_apply_fun && other)
                : f(std::move(other.f))
            {}

            invoke_apply_fun & operator=(invoke_apply_fun const & other)
            {
                f = other.f;
                return *this;
            }

            invoke_apply_fun & operator=(invoke_apply_fun && other)
            {
                f = std::move(other.f);
                return *this;
            }

            result_type operator()(void ** p) const
            {
                return f(*reinterpret_cast<T *>(*p));
            }

            template <typename A>
            result_type operator()(void ** p, A && a) const
            {
                return f(*reinterpret_cast<T *>(*p), std::forward<A>(a));
            }

            template <typename Archive>
            void serialize(Archive & ar, unsigned)
            {
                ar & f;
            }

            typename util::decay<F>::type f;

        };
    }

    template <typename T>
    struct object
    {
        object() {}
        explicit object(naming::id_type const & gid) : gid_(gid) {}
        naming::id_type gid_;
        template <typename F>
        lcos::unique_future<
            typename util::result_of<typename hpx::util::decay<F>::type(T &)>::type
        >
        operator<=(F && f) const
        {
            return
                stubs::remote_object::apply_async(
                    gid_
                  , std::move(remote_object::invoke_apply_fun<T, F>(std::forward<F>(f)))
                );
        }

        template <typename F>
        lcos::unique_future<
            typename util::result_of<typename hpx::util::decay<F>::type(T &)>::type
        >
        apply(F && f) const
        {
            return
                stubs::remote_object::apply_async(
                    gid_
                  , std::move(remote_object::invoke_apply_fun<T, F>(std::forward<F>(f)))
                );
        }

        template <typename Archive>
        void serialize(Archive & ar, unsigned)
        {
            ar & gid_;
        }
    };
}}

namespace hpx { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct promise_remote_result<hpx::components::object<T> >
    {
        typedef ::hpx::naming::id_type type;
    };

    ///////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct component_type_database<
        hpx::lcos::base_lco_with_value<
            hpx::components::object<T>
          , hpx::naming::id_type
        >
    >
    {
        HPX_ALWAYS_EXPORT static components::component_type
        get()
        {
            return hpx::components::component_base_lco_with_value;
        }
        HPX_ALWAYS_EXPORT static void
        set(components::component_type)
        {
            HPX_ASSERT(false);
        }
    };
}}

#endif
