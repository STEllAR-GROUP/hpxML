//  Copyright (c)      2012 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PP_IS_ITERATING

#ifndef HPX_RUNTIME_COMPONENTS_SERVER_CREATE_ONE_COMPONENT_FUNCTOR_HPP
#define HPX_RUNTIME_COMPONENTS_SERVER_CREATE_ONE_COMPONENT_FUNCTOR_HPP

#include <boost/utility/enable_if.hpp>
#include <hpx/util/detail/remove_reference.hpp>
#include <boost/type_traits/remove_const.hpp>

#define HPX_MOVE_ARGS(z, n, _)                                                \
    boost::move(BOOST_PP_CAT(a, n))                                           \
    /**/

#define HPX_FORWARD_ARGS(z, n, _)                                             \
    boost::forward<BOOST_PP_CAT(A, n)>(BOOST_PP_CAT(a, n))                    \
    /**/

#define HPX_FWD_REF_ARGS(z, n, _)                                             \
    BOOST_FWD_REF(BOOST_PP_CAT(A, n)) BOOST_PP_CAT(a, n)                       \
    /**/

#define HPX_FWD_REF_ARGS2(z, n, _)                                             \
    BOOST_FWD_REF(BOOST_PP_CAT(T, n)) BOOST_PP_CAT(t, n)                       \
    /**/

namespace hpx { namespace components { namespace server
{

#define HPX_RUNTIME_SUPPORT_CREATE_ONE_M0(Z, N, D)                            \
        BOOST_PP_CAT(a, N)(boost::forward<BOOST_PP_CAT(T, N)>(BOOST_PP_CAT(t, N)))                   \
    /**/
#define HPX_RUNTIME_SUPPORT_CREATE_ONE_M1(Z, N, D)                            \
        typename boost::remove_const<typename hpx::util::detail::remove_reference<BOOST_PP_CAT(A, N)>::type>::type\
            BOOST_PP_CAT(a, N);                                               \
    /**/
#define HPX_RUNTIME_SUPPORT_CREATE_ONE_M2(Z, N, D)                            \
        BOOST_PP_CAT(a, N)(other. BOOST_PP_CAT(a, N))                         \
    /**/
#define HPX_RUNTIME_SUPPORT_CREATE_ONE_M3(Z, N, D)                            \
        BOOST_PP_CAT(a, N)(boost::move(other. BOOST_PP_CAT(a, N)))            \
    /**/
#define HPX_RUNTIME_SUPPORT_CREATE_ONE_M4(Z, N, D)                            \
        BOOST_PP_CAT(a, N) = other. BOOST_PP_CAT(a, N);                       \
    /**/
#define HPX_RUNTIME_SUPPORT_CREATE_ONE_M5(Z, N, D)                            \
        BOOST_PP_CAT(a, N) = boost::move(other. BOOST_PP_CAT(a, N));          \
    /**/

#define BOOST_PP_ITERATION_PARAMS_1                                           \
    (                                                                         \
        3                                                                     \
      , (                                                                     \
            1                                                                 \
          , HPX_ACTION_ARGUMENT_LIMIT                                         \
          , "hpx/runtime/components/server/create_one_component_functor.hpp"  \
        )                                                                     \
    )                                                                         \
    /**/

#include BOOST_PP_ITERATE()
}}}

#undef HPX_RUNTIME_SUPPORT_CREATE_ONE_COMPONENT
#undef HPX_RUNTIME_SUPPORT_CREATE_ONE_M0
#undef HPX_RUNTIME_SUPPORT_CREATE_ONE_M1
#undef HPX_RUNTIME_SUPPORT_CREATE_ONE_M2
#undef HPX_RUNTIME_SUPPORT_CREATE_ONE_M3
#undef HPX_FORWARD_ARGS
#undef HPX_FWD_REF_ARGS
#undef HPX_FWD_REF_ARGS2
#undef HPX_MOVE_ARGS

#endif

#else

#define N BOOST_PP_ITERATION()
        
        template <typename Component, BOOST_PP_ENUM_PARAMS(N, typename A)>
        struct BOOST_PP_CAT(create_one_component_functor, N)
        {
            typedef void result_type;

            BOOST_PP_CAT(create_one_component_functor, N)(
                BOOST_PP_CAT(create_one_component_functor, N) const & other)
              : BOOST_PP_ENUM(N, HPX_RUNTIME_SUPPORT_CREATE_ONE_M2, _)
            {}

            BOOST_PP_CAT(create_one_component_functor, N)(
                BOOST_RV_REF(BOOST_PP_CAT(create_one_component_functor, N)) other)
              : BOOST_PP_ENUM(N, HPX_RUNTIME_SUPPORT_CREATE_ONE_M3, _)
            {}

            BOOST_PP_CAT(create_one_component_functor, N) & operator=(
                BOOST_COPY_ASSIGN_REF(BOOST_PP_CAT(create_one_component_functor, N)) other)
            {
                BOOST_PP_REPEAT(N, HPX_RUNTIME_SUPPORT_CREATE_ONE_M4, _)
                return *this;
            }

            BOOST_PP_CAT(create_one_component_functor, N) & operator=(
                BOOST_RV_REF(BOOST_PP_CAT(create_one_component_functor, N)) other)
            {
                BOOST_PP_REPEAT(N, HPX_RUNTIME_SUPPORT_CREATE_ONE_M5, _)
                return *this;
            }

            template <BOOST_PP_ENUM_PARAMS(N, typename T)>
#if N == 1
            explicit
#endif
            BOOST_PP_CAT(create_one_component_functor, N)(
                BOOST_PP_ENUM(N, HPX_FWD_REF_ARGS2, _)
#if N == 1
              , typename ::boost::disable_if<
                    typename boost::is_same<
                        BOOST_PP_CAT(create_one_component_functor, N)
                      , typename boost::remove_const<
                            typename hpx::util::detail::remove_reference<
                                T0
                            >::type
                        >::type
                    >::type
                >::type * dummy = 0
#endif
            )
              : BOOST_PP_ENUM(N, HPX_RUNTIME_SUPPORT_CREATE_ONE_M0, _)
            {}

            result_type operator()(void* p)
            {
                new (p) Component(BOOST_PP_ENUM(N, HPX_MOVE_ARGS, _));
            }
            BOOST_PP_REPEAT(N, HPX_RUNTIME_SUPPORT_CREATE_ONE_M1, _)

            private:

                BOOST_COPYABLE_AND_MOVABLE(BOOST_PP_CAT(create_one_component_functor, N))
        };

        template <typename Component, BOOST_PP_ENUM_PARAMS(N, typename A)>
        naming::gid_type create_one_functor(
            component_factory_base* factory,
            BOOST_PP_ENUM(N, HPX_FWD_REF_ARGS, _))
        {
            return factory->create_one_functor(
                BOOST_PP_CAT(create_one_component_functor, N)<
                    Component, BOOST_PP_ENUM_PARAMS(N, A)>(
                        BOOST_PP_ENUM(N, HPX_FORWARD_ARGS, _))
            );
        }

#undef N

#endif
