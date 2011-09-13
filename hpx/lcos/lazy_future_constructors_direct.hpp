//  Copyright (c) 2007-2010 Hartmut Kaiser, Dylan Stark
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PP_IS_ITERATING

#if !defined(HPX_LCOS_LAZY_FUTURE_CONSTRUCTORS_DIRECT_JUL_01_2008_0116PM)
#define HPX_LCOS_LAZY_FUTURE_CONSTRUCTORS_DIRECT_JUL_01_2008_0116PM

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

#define BOOST_PP_ITERATION_PARAMS_1                                           \
    (3, (2, HPX_ACTION_ARGUMENT_LIMIT,                                        \
    "hpx/lcos/lazy_future_constructors_direct.hpp"))                         \
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
        util::block_profiler_wrapper<lazy_future_direct_tag> bp(apply_logger_);

        naming::address addr;
        if (hpx::applier::get_applier().address_is_local(gid, addr)) {
            // local, direct execution
            BOOST_ASSERT(components::types_are_compatible(addr.type_, 
                components::get_component_type<typename Action::component_type>()));
            (*this->impl_)->set_data(0, Action::execute_function_nonvirt(
                addr.address_, BOOST_PP_ENUM_PARAMS(N, arg)));
        }
        else {
            // remote execution
            hpx::applier::apply_c<Action>(addr, this->get_gid(), gid, 
                BOOST_PP_ENUM_PARAMS(N, arg));
        }
    }

private:
    template <BOOST_PP_ENUM_PARAMS(N, typename Arg)>
    static void BOOST_PP_CAT(invoke,N)(
        hpx::lcos::lazy_future<Action,Result,boost::mpl::true_> *th, 
        naming::id_type const& gid, 
        BOOST_PP_ENUM_BINARY_PARAMS(N, Arg, const& arg))
    {
        if (!((*th->impl_)->ready()))
            th->apply(gid, BOOST_PP_ENUM_PARAMS(N, arg));
    }

public:
    template <BOOST_PP_ENUM_PARAMS(N, typename Arg)>
    lazy_future(naming::gid_type const& gid, 
            BOOST_PP_ENUM_BINARY_PARAMS(N, Arg, const& arg))
      : apply_logger_("lazy_future_direct::apply"),
        closure_(boost::bind(
            &lazy_future::template BOOST_PP_CAT(invoke,N)<BOOST_PP_ENUM_PARAMS(N, Arg)>, 
            this, naming::id_type(gid, naming::id_type::unmanaged), 
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
      : apply_logger_("lazy_future_direct::apply"),
        closure_(boost::bind(
            &lazy_future::template BOOST_PP_CAT(invoke,N)<BOOST_PP_ENUM_PARAMS(N, Arg)>, 
            this, gid,
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
