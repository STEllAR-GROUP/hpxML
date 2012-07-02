
//  Copyright (c) 2011 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#define NNN BOOST_PP_FRAME_ITERATION(2)

    template <BOOST_PP_ENUM_PARAMS(NNN, typename A)>
    result_type operator()(BOOST_PP_ENUM(NNN, HPX_UTIL_BIND_FWD_REF_PARAMS, _))
    {
        using detail::get_pointer;
        typedef
            BOOST_PP_CAT(hpx::util::tuple, NNN)<
                BOOST_PP_ENUM(NNN, HPX_UTIL_BIND_REFERENCE, A)
            >
            env_type;
        env_type env(BOOST_PP_ENUM(NNN, HPX_UTIL_BIND_FWD_PARAMS, A));
        return
            (get_pointer(detail::eval(env, arg0))->*f)
                (BOOST_PP_ENUM_SHIFTED(NN, HPX_UTIL_BIND_EVAL, _));
    }
    template <BOOST_PP_ENUM_PARAMS(NNN, typename A)>
    result_type operator()(BOOST_PP_ENUM(NNN, HPX_UTIL_BIND_FWD_REF_PARAMS, _)) const
    {
        using detail::get_pointer;
        typedef
            BOOST_PP_CAT(hpx::util::tuple, NNN)<
                BOOST_PP_ENUM(NNN, HPX_UTIL_BIND_REFERENCE, A)
            >
            env_type;
        env_type env(BOOST_PP_ENUM(NNN, HPX_UTIL_BIND_FWD_PARAMS, A));
        return
            (get_pointer(detail::eval(env, arg0))->*f)
                (BOOST_PP_ENUM_SHIFTED(NN, HPX_UTIL_BIND_EVAL, _));
    }

#undef NNN
