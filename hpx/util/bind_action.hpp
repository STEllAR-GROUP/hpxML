//  Copyright (c) 2012 Hartmut Kaiser
//  Copyright (c) 2011 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !BOOST_PP_IS_ITERATING

#ifndef HPX_UTIL_BIND_ACTION_HPP
#define HPX_UTIL_BIND_ACTION_HPP

#include <hpx/config.hpp>
#include <hpx/util/tuple.hpp>
#include <hpx/util/detail/remove_reference.hpp>
#include <hpx/util/bind_action.hpp>
#include <hpx/lcos/async.hpp>

#include <boost/serialization/serialization.hpp>

///////////////////////////////////////////////////////////////////////////////
#define HPX_UTIL_BIND_FWD_REF_PARAMS(Z, N, D)                                   \
    BOOST_FWD_REF(BOOST_PP_CAT(A, N)) BOOST_PP_CAT(a, N)                        \
/**/

#define HPX_UTIL_BIND_FWD_PARAMS(Z, N, D)                                       \
    boost::forward<BOOST_PP_CAT(D, N)>(BOOST_PP_CAT(a, N))                      \
/**/

#define HPX_UTIL_BIND_EVAL(Z, N, D)                                             \
    hpx::util::detail::eval(env, BOOST_PP_CAT(arg, N))                          \
/**/

#define HPX_UTIL_BIND_REMOVE_REFERENCE(Z, N, D)                                 \
    typename boost::remove_const<                                               \
        typename detail::remove_reference<BOOST_PP_CAT(D, N)>::type>::type      \
/**/

#define HPX_UTIL_BIND_REFERENCE(Z, N, D)                                        \
    typename detail::env_value_type<BOOST_FWD_REF(BOOST_PP_CAT(D, N))>::type    \
/**/

#define HPX_UTIL_BIND_FUNCTOR_OPERATOR(Z, N, D)                                 \
    template <BOOST_PP_ENUM_PARAMS(N, typename A)>                              \
    result_type operator()(BOOST_PP_ENUM(N, HPX_UTIL_BIND_FWD_REF_PARAMS, _)) const  \
    {                                                                           \
        typedef                                                                 \
            BOOST_PP_CAT(hpx::util::tuple, N)<                                  \
                BOOST_PP_ENUM(N, HPX_UTIL_BIND_REFERENCE, A)                    \
            >                                                                   \
            env_type;                                                           \
        env_type env(BOOST_PP_ENUM(N, HPX_UTIL_BIND_FWD_PARAMS, A));            \
        return eval(env, f) D;                                                  \
    }                                                                           \
                                                                                \
    template <BOOST_PP_ENUM_PARAMS(N, typename A)>                              \
    result_type operator()(BOOST_PP_ENUM(N, HPX_UTIL_BIND_FWD_REF_PARAMS, _))   \
    {                                                                           \
        typedef                                                                 \
            BOOST_PP_CAT(hpx::util::tuple, N)<                                  \
                BOOST_PP_ENUM(N, HPX_UTIL_BIND_REFERENCE, A)                    \
            >                                                                   \
            env_type;                                                           \
        env_type env(BOOST_PP_ENUM(N, HPX_UTIL_BIND_FWD_PARAMS, A));            \
        return eval(env, f) D;                                                  \
    }                                                                           \
/**/

#define BOOST_PP_ITERATION_PARAMS_1                                             \
    (                                                                           \
        3                                                                       \
      , (                                                                       \
            1                                                                   \
          , HPX_FUNCTION_LIMIT                                                  \
          , <hpx/util/bind_action.hpp>                                          \
        )                                                                       \
    )                                                                           \
/**/
#include BOOST_PP_ITERATE()

#undef HPX_UTIL_BIND_FWD_REF_PARAMS
#undef HPX_UTIL_BIND_FWD_PARAMS
#undef HPX_UTIL_BIND_EVAL
#undef HPX_UTIL_BIND_REMOVE_REFERENCE
#undef HPX_UTIL_BIND_REFERENCE
#undef HPX_UTIL_BIND_FUNCTOR_OPERATOR

namespace boost { namespace serialization
{
    // serialization of placeholders is trivial, just provide empty functions
    template <int N>
    void serialize(hpx::util::portable_binary_iarchive&,
        hpx::util::placeholders::arg<N>&, unsigned int const)
    {}
    template <int N>
    void serialize(hpx::util::portable_binary_oarchive&,
        hpx::util::placeholders::arg<N>&, unsigned int const)
    {}
}}

#endif

#else  // !BOOST_PP_IS_ITERATING

#define N BOOST_PP_ITERATION()
#define NN N

#define HPX_UTIL_BIND_INIT_MEMBER(Z, N, D)                                      \
    BOOST_PP_CAT(arg, N)(boost::forward<BOOST_PP_CAT(A, N)>(BOOST_PP_CAT(a, N)))\
/**/
#define HPX_UTIL_BIND_MEMBER(Z, N, D)                                           \
    BOOST_PP_CAT(Arg, N) BOOST_PP_CAT(arg, N);                                  \
/**/

#define HPX_UTIL_BIND_INIT_COPY_MEMBER(Z, N, D)                                 \
    BOOST_PP_CAT(arg, N)(other.BOOST_PP_CAT(arg, N))                            \
/**/

#define HPX_UTIL_BIND_INIT_MOVE_MEMBER(Z, N, D)                                 \
    BOOST_PP_CAT(arg, N)(boost::move(other.BOOST_PP_CAT(arg, N)))               \
/**/

#define HPX_UTIL_BIND_ASSIGN_MEMBER(Z, N, D)                                    \
    BOOST_PP_CAT(arg, N) = other.BOOST_PP_CAT(arg, N);                          \
/**/

#define HPX_UTIL_BIND_MOVE_MEMBER(Z, N, D)                                      \
    BOOST_PP_CAT(arg, N) = boost::move(other.BOOST_PP_CAT(arg, N));             \
/**/

namespace hpx { namespace util
{
    ///////////////////////////////////////////////////////////////////////////
    // actions
    namespace detail
    {
        template <
            typename Action
          BOOST_PP_COMMA_IF(N) BOOST_PP_ENUM_PARAMS(N, typename Arg)
          , typename Result =
                typename traits::promise_local_result<
                    typename hpx::actions::extract_action<Action>::result_type
                >::type
        >
        struct BOOST_PP_CAT(bound_action, N)
        {
            typedef Result result_type;

            template <BOOST_PP_ENUM_PARAMS(N, typename A)>
            BOOST_PP_CAT(bound_action, N)(
                BOOST_PP_ENUM(N, HPX_UTIL_BIND_FWD_REF_PARAMS, _)
            )
                : BOOST_PP_ENUM(N, HPX_UTIL_BIND_INIT_MEMBER, _)
            {}

            BOOST_PP_CAT(bound_action, N)(
                    BOOST_PP_CAT(bound_action, N) const & other)
                : BOOST_PP_ENUM(N, HPX_UTIL_BIND_INIT_COPY_MEMBER, _)
            {}

            BOOST_PP_CAT(bound_action, N)(BOOST_RV_REF(
                    BOOST_PP_CAT(bound_action, N)) other)
                : BOOST_PP_ENUM(N, HPX_UTIL_BIND_INIT_MOVE_MEMBER, _)
            {}

            BOOST_PP_CAT(bound_action, N) & operator=(
                BOOST_COPY_ASSIGN_REF(BOOST_PP_CAT(bound_action, N)) other)
            {
                BOOST_PP_REPEAT(N, HPX_UTIL_BIND_ASSIGN_MEMBER, _)
                return *this;
            }

            BOOST_PP_CAT(bound_action, N) & operator=(
                BOOST_RV_REF(BOOST_PP_CAT(bound_action, N)) other)
            {
                BOOST_PP_REPEAT(N, HPX_UTIL_BIND_MOVE_MEMBER, _)
                return *this;
            }

            result_type operator()()
            {
                typedef hpx::util::tuple0<> env_type;
                env_type env;
                return hpx::lcos::async<Action>(
                    hpx::util::detail::eval(env, arg0)
                  BOOST_PP_COMMA_IF(BOOST_PP_DEC(N))
                        BOOST_PP_ENUM_SHIFTED(N, HPX_UTIL_BIND_EVAL, _)).get();
            }

            result_type operator()() const
            {
                typedef hpx::util::tuple0<> env_type;
                env_type env;
                return hpx::lcos::async<Action>(
                    hpx::util::detail::eval(env, arg0)
                  BOOST_PP_COMMA_IF(BOOST_PP_DEC(N))
                        BOOST_PP_ENUM_SHIFTED(N, HPX_UTIL_BIND_EVAL, _)).get();
            }

#define HPX_UTIL_BIND_ACTION_OPERATOR(Z, N, D)                                  \
    template <BOOST_PP_ENUM_PARAMS(N, typename A)>                              \
    result_type operator()(BOOST_PP_ENUM(N, HPX_UTIL_BIND_FWD_REF_PARAMS, _))   \
    {                                                                           \
        typedef                                                                 \
            BOOST_PP_CAT(hpx::util::tuple, N)<                                  \
                BOOST_PP_ENUM(N, HPX_UTIL_BIND_REFERENCE, A)                    \
            >                                                                   \
            env_type;                                                           \
        env_type env(BOOST_PP_ENUM(N, HPX_UTIL_BIND_FWD_PARAMS, A));            \
        return hpx::lcos::async<Action>(                                        \
            hpx::util::detail::eval(env, arg0)                                  \
          BOOST_PP_COMMA_IF(BOOST_PP_DEC(N))                                    \
                BOOST_PP_ENUM_SHIFTED(N, HPX_UTIL_BIND_EVAL, _)).get();         \
    }                                                                           \
    template <BOOST_PP_ENUM_PARAMS(N, typename A)>                              \
    result_type operator()(BOOST_PP_ENUM(N, HPX_UTIL_BIND_FWD_REF_PARAMS, _)) const \
    {                                                                           \
        typedef                                                                 \
            BOOST_PP_CAT(hpx::util::tuple, N)<                                  \
                BOOST_PP_ENUM(N, HPX_UTIL_BIND_REFERENCE, A)                    \
            >                                                                   \
            env_type;                                                           \
        env_type env(BOOST_PP_ENUM(N, HPX_UTIL_BIND_FWD_PARAMS, A));            \
        return hpx::lcos::async<Action>(                                        \
            hpx::util::detail::eval(env, arg0)                                  \
          BOOST_PP_COMMA_IF(BOOST_PP_DEC(N))                                    \
                BOOST_PP_ENUM_SHIFTED(N, HPX_UTIL_BIND_EVAL, _)).get();         \
    }                                                                           \
/**/
            BOOST_PP_REPEAT_FROM_TO(
                1
              , HPX_FUNCTION_LIMIT
              , HPX_UTIL_BIND_ACTION_OPERATOR, _
            )
#undef HPX_UTIL_BIND_ACTION_OPERATOR

            BOOST_PP_REPEAT(N, HPX_UTIL_BIND_MEMBER, _)
        };

        template <
            typename Action
          BOOST_PP_COMMA_IF(N) BOOST_PP_ENUM_PARAMS(N, typename Arg)
        >
        struct BOOST_PP_CAT(bound_action, N)<
                Action
              BOOST_PP_COMMA_IF(N) BOOST_PP_ENUM_PARAMS(N, Arg)
              , void
            >
        {
            typedef void result_type;

            template <BOOST_PP_ENUM_PARAMS(N, typename A)>
            BOOST_PP_CAT(bound_action, N)(
                BOOST_PP_ENUM(N, HPX_UTIL_BIND_FWD_REF_PARAMS, _)
            )
                : BOOST_PP_ENUM(N, HPX_UTIL_BIND_INIT_MEMBER, _)
            {}

            BOOST_PP_CAT(bound_action, N)(
                    BOOST_PP_CAT(bound_action, N) const & other)
                : BOOST_PP_ENUM(N, HPX_UTIL_BIND_INIT_COPY_MEMBER, _)
            {}

            BOOST_PP_CAT(bound_action, N)(BOOST_RV_REF(
                    BOOST_PP_CAT(bound_action, N)) other)
                : BOOST_PP_ENUM(N, HPX_UTIL_BIND_INIT_MOVE_MEMBER, _)
            {}

            BOOST_PP_CAT(bound_action, N) & operator=(
                BOOST_COPY_ASSIGN_REF(BOOST_PP_CAT(bound_action, N)) other)
            {
                BOOST_PP_REPEAT(N, HPX_UTIL_BIND_ASSIGN_MEMBER, _)
                return *this;
            }

            BOOST_PP_CAT(bound_action, N) & operator=(
                BOOST_RV_REF(BOOST_PP_CAT(bound_action, N)) other)
            {
                BOOST_PP_REPEAT(N, HPX_UTIL_BIND_MOVE_MEMBER, _)
                return *this;
            }

            void operator()()
            {
                typedef hpx::util::tuple0<> env_type;
                env_type env;
                hpx::applier::apply<Action>(
                    hpx::util::detail::eval(env, arg0)
                  BOOST_PP_COMMA_IF(BOOST_PP_DEC(N))
                        BOOST_PP_ENUM_SHIFTED(N, HPX_UTIL_BIND_EVAL, _));
            }

            void operator()() const
            {
                typedef hpx::util::tuple0<> env_type;
                env_type env;
                hpx::applier::apply<Action>(
                    hpx::util::detail::eval(env, arg0)
                  BOOST_PP_COMMA_IF(BOOST_PP_DEC(N))
                        BOOST_PP_ENUM_SHIFTED(N, HPX_UTIL_BIND_EVAL, _));
            }

#define HPX_UTIL_BIND_ACTION_OPERATOR(Z, N, D)                                  \
    template <BOOST_PP_ENUM_PARAMS(N, typename A)>                              \
    void operator()(BOOST_PP_ENUM(N, HPX_UTIL_BIND_FWD_REF_PARAMS, _))          \
    {                                                                           \
        typedef                                                                 \
            BOOST_PP_CAT(hpx::util::tuple, N)<                                  \
                BOOST_PP_ENUM(N, HPX_UTIL_BIND_REFERENCE, A)                    \
            >                                                                   \
            env_type;                                                           \
        env_type env(BOOST_PP_ENUM(N, HPX_UTIL_BIND_FWD_PARAMS, A));            \
        hpx::applier::apply<Action>(                                            \
            hpx::util::detail::eval(env, arg0)                                  \
          BOOST_PP_COMMA_IF(BOOST_PP_DEC(N))                                    \
                BOOST_PP_ENUM_SHIFTED(N, HPX_UTIL_BIND_EVAL, _)).get();         \
    }                                                                           \
    template <BOOST_PP_ENUM_PARAMS(N, typename A)>                              \
    void operator()(BOOST_PP_ENUM(N, HPX_UTIL_BIND_FWD_REF_PARAMS, _)) const    \
    {                                                                           \
        typedef                                                                 \
            BOOST_PP_CAT(hpx::util::tuple, N)<                                  \
                BOOST_PP_ENUM(N, HPX_UTIL_BIND_REFERENCE, A)                    \
            >                                                                   \
            env_type;                                                           \
        env_type env(BOOST_PP_ENUM(N, HPX_UTIL_BIND_FWD_PARAMS, A));            \
        hpx::applier::apply<Action>(                                            \
            hpx::util::detail::eval(env, arg0)                                  \
          BOOST_PP_COMMA_IF(BOOST_PP_DEC(N))                                    \
                BOOST_PP_ENUM_SHIFTED(N, HPX_UTIL_BIND_EVAL, _)).get();         \
    }                                                                           \
/**/
            BOOST_PP_REPEAT_FROM_TO(
                1
              , HPX_FUNCTION_LIMIT
              , HPX_UTIL_BIND_ACTION_OPERATOR, _
            )
#undef HPX_UTIL_BIND_ACTION_OPERATOR

            BOOST_PP_REPEAT(N, HPX_UTIL_BIND_MEMBER, _)
        };

        ///////////////////////////////////////////////////////////////////////
        template <
            typename Env
          , typename Action
          BOOST_PP_COMMA_IF(N) BOOST_PP_ENUM_PARAMS(N, typename Arg)
        >
        typename traits::promise_local_result<
            typename hpx::actions::extract_action<Action>::result_type
        >::type
        eval(
            Env const & env
          , BOOST_PP_CAT(detail::bound_action, N)<
                Action
              BOOST_PP_COMMA_IF(N) BOOST_PP_ENUM_PARAMS(N, Arg)
            > const & f
        )
        {
            return
                boost::fusion::fused<
                    BOOST_PP_CAT(detail::bound_action, N)<
                        Action
                      BOOST_PP_COMMA_IF(N) BOOST_PP_ENUM_PARAMS(N, Arg)
                    >
                >(f)(
                    env
                 );
        }
    }

    template <
        typename Action
      BOOST_PP_COMMA_IF(N) BOOST_PP_ENUM_PARAMS(N, typename A)
    >
    BOOST_PP_CAT(detail::bound_action, N)<
        Action
      BOOST_PP_COMMA_IF(N) BOOST_PP_ENUM(N, HPX_UTIL_BIND_REMOVE_REFERENCE, A)
    >
    bind(
        BOOST_PP_ENUM(N, HPX_UTIL_BIND_FWD_REF_PARAMS, _)
    )
    {
        return
            BOOST_PP_CAT(detail::bound_action, N)<
                Action
              BOOST_PP_COMMA_IF(N)
                  BOOST_PP_ENUM(N, HPX_UTIL_BIND_REMOVE_REFERENCE, A)
            > (BOOST_PP_ENUM(N, HPX_UTIL_BIND_FWD_PARAMS, A));
    }
}}

namespace boost { namespace serialization
{
    // serialization of the bound object, just serialize members
#define HPX_UTIL_BIND_SERIALIZE_MEMBER(Z, N, _) ar & BOOST_PP_CAT(arg, N);

    template <
        typename Action
      BOOST_PP_COMMA_IF(N) BOOST_PP_ENUM_PARAMS(N, typename Arg)
      , typename Result
    >
    void serialize(hpx::util::portable_binary_iarchive& ar
      , BOOST_PP_CAT(hpx::util::detail::bound_action, N)<
            Action
          BOOST_PP_COMMA_IF(N) BOOST_PP_ENUM_PARAMS(N, Arg)
          , Result
        >& bound
      , unsigned int const)
    {
        BOOST_PP_REPEAT(N, HPX_UTIL_BIND_SERIALIZE_MEMBER, _)
    }
    template <
        typename Action
      BOOST_PP_COMMA_IF(N) BOOST_PP_ENUM_PARAMS(N, typename Arg)
      , typename Result
    >
    void serialize(hpx::util::portable_binary_oarchive& ar
      , BOOST_PP_CAT(hpx::util::detail::bound_action, N)<
            Action
          BOOST_PP_COMMA_IF(N) BOOST_PP_ENUM_PARAMS(N, Arg)
          , Result
        >& bound
      , unsigned int const)
    {
        BOOST_PP_REPEAT(N, HPX_UTIL_BIND_SERIALIZE_MEMBER, _)
    }

#undef HPX_UTIL_BIND_SERIALIZE_MEMBER
}}

#undef HPX_UTIL_BIND_MOVE_MEMBER
#undef HPX_UTIL_BIND_ASSIGN_MEMBER
#undef HPX_UTIL_BIND_INIT_MOVE_MEMBER
#undef HPX_UTIL_BIND_INIT_COPY_MEMBER
#undef HPX_UTIL_BIND_MEMBER
#undef HPX_UTIL_BIND_INIT_MEMBER

#undef NN
#undef N

#endif
