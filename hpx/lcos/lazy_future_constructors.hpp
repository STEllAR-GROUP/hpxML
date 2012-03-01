//  Copyright (c) 2007-2010 Hartmut Kaiser, Dylan Stark
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PP_IS_ITERATING

#if !defined(HPX_LCOS_LAZY_FUTURE_CONSTRUCTORS_JUN_27_2008_0440PM)
#define HPX_LCOS_LAZY_FUTURE_CONSTRUCTORS_JUN_27_2008_0440PM

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

#define BOOST_PP_ITERATION_PARAMS_1                                           \
    (3, (2, HPX_ACTION_ARGUMENT_LIMIT,                                        \
    "hpx/lcos/lazy_future_constructors.hpp"))                                       \
    /**/

#include BOOST_PP_ITERATE()

#endif

///////////////////////////////////////////////////////////////////////////////
//  Preprocessor vertical repetition code
///////////////////////////////////////////////////////////////////////////////
#else // defined(BOOST_PP_IS_ITERATING)

#define N BOOST_PP_ITERATION()

    template <BOOST_PP_ENUM_PARAMS(N, typename Arg)>
    void apply(naming::id_type const& gid,
        BOOST_PP_ENUM_BINARY_PARAMS(N, Arg, const& arg))
    {
        util::block_profiler_wrapper<lazy_future_tag> bp(apply_logger_);
        hpx::applier::apply_c<Action>(
            this->get_gid(), gid, BOOST_PP_ENUM_PARAMS(N, arg));
    }

private:
    template <BOOST_PP_ENUM_PARAMS(N, typename Arg)>
    static void BOOST_PP_CAT(invoke,N)(
        hpx::lcos::lazy_future<Action,Result> *th,
        naming::id_type const& gid,
        BOOST_PP_ENUM_BINARY_PARAMS(N, Arg, const& arg))
    {
        if (!((*th->impl_)->is_ready()))
            th->apply(gid, BOOST_PP_ENUM_PARAMS(N, arg));
    }

public:
    template <BOOST_PP_ENUM_PARAMS(N, typename Arg)>
    lazy_future(naming::gid_type const& gid,
            BOOST_PP_ENUM_BINARY_PARAMS(N, Arg, const& arg))
      : apply_logger_("lazy_future::apply"),
        closure_(boost::bind(
          &lazy_future::template BOOST_PP_CAT(invoke,N)<BOOST_PP_ENUM_PARAMS(N,Arg)>,
            this_(), naming::id_type(gid, naming::id_type::unmanaged),
            BOOST_PP_ENUM_PARAMS(N, arg)))
    {
        LLCO_(info) << "lazy_future::lazy_future("
                    << hpx::actions::detail::get_action_name<Action>()
                    << ", "
                    << gid
                    << ") args(" << (N + 1) << ")";
    }

    template <BOOST_PP_ENUM_PARAMS(N, typename Arg)>
    lazy_future(naming::id_type const& gid,
            BOOST_PP_ENUM_BINARY_PARAMS(N, Arg, const& arg))
      : apply_logger_("lazy_future::apply"),
        closure_(boost::bind(
          &lazy_future::template BOOST_PP_CAT(invoke,N)<BOOST_PP_ENUM_PARAMS(N,Arg)>,
            this_(), gid,
            BOOST_PP_ENUM_PARAMS(N, arg)))
    {
        LLCO_(info) << "lazy_future::lazy_future("
                    << hpx::actions::detail::get_action_name<Action>()
                    << ", "
                    << gid
                    << ") args(" << (N + 1) << ")";
    }

#undef N

#endif
