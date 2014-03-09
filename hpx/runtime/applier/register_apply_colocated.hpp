//  Copyright (c) 2014 thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_RUNTIME_APPLIER_REGISTER_APPLY_COLOCATED_MAR_09_2014_1214PM)
#define HPX_RUNTIME_APPLIER_REGISTER_APPLY_COLOCATED_MAR_09_2014_1214PM

#include <hpx/hpx_fwd.hpp>
#include <hpx/runtime/agas/request.hpp>
#include <hpx/runtime/naming/name.hpp>
#include <hpx/util/tuple.hpp>
#include <hpx/util/functional/colocated_helpers.hpp>

#include <boost/preprocessor/repetition/enum_params.hpp>

namespace hpx { namespace detail
{
    template <typename Tuple>
    struct apply_colocated_bound_tuple;

    template <
        BOOST_PP_ENUM_PARAMS(
            HPX_TUPLE_LIMIT
          , typename T
        )
    >
    struct apply_colocated_bound_tuple<
        util::tuple<
            BOOST_PP_ENUM_PARAMS(HPX_TUPLE_LIMIT, T)
        >
    >
    {
        typedef
            util::tuple<
                hpx::util::detail::bound<
                    hpx::util::functional::extract_locality
                  , hpx::util::tuple<hpx::util::detail::placeholder<2ul> >
                >
              , BOOST_PP_ENUM_PARAMS(BOOST_PP_DEC(HPX_TUPLE_LIMIT), T)
            >
            type;
    };
}}

#define HPX_REGISTER_APPLY_COLOCATED_DECLARATION(Action, Name)                \
HPX_UTIL_REGISTER_FUNCTION_DECLARATION(                                       \
    void (hpx::naming::id_type, hpx::agas::response)                          \
  , (hpx::util::functional::detail::apply_continuation_impl<                  \
        hpx::util::detail::bound_action<                                      \
            Action                                                            \
          , hpx::detail::apply_colocated_bound_tuple<                         \
                Action ::arguments_type                                       \
            >::type                                                           \
        >                                                                     \
    >)                                                                        \
  , Name                                                                      \
);                                                                            \
/**/

#define HPX_REGISTER_APPLY_COLOCATED(action, name)                            \
HPX_UTIL_REGISTER_FUNCTION(                                                   \
    void (hpx::naming::id_type, hpx::agas::response)                          \
  , (hpx::util::functional::detail::apply_continuation_impl<                  \
        hpx::util::detail::bound_action<                                      \
            action                                                            \
          , hpx::detail::apply_colocated_bound_tuple<                         \
                action::arguments_type                                        \
            >::type                                                           \
        >                                                                     \
    >)                                                                        \
  , name                                                                      \
);                                                                            \
/**/

#endif
