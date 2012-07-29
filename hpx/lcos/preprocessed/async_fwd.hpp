//  Copyright (c) 2007-2012 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_LCOS_PREPROCESSED_ASYNC_FWD_HPP)
#define HPX_LCOS_PREPROCESSED_ASYNC_FWD_HPP

#if HPX_ACTION_ARGUMENT_LIMIT <= 5
#include <hpx/lcos/preprocessed/async_fwd_5.hpp>
#elif HPX_ACTION_ARGUMENT_LIMIT <= 10
#include <hpx/lcos/preprocessed/async_fwd_10.hpp>
#elif HPX_ACTION_ARGUMENT_LIMIT <= 20
#include <hpx/lcos/preprocessed/async_fwd_20.hpp>
#elif HPX_ACTION_ARGUMENT_LIMIT <= 30
#include <hpx/lcos/preprocessed/async_fwd_30.hpp>
#elif HPX_ACTION_ARGUMENT_LIMIT <= 40
#include <hpx/lcos/preprocessed/async_fwd_40.hpp>
#elif HPX_ACTION_ARGUMENT_LIMIT <= 50
#include <hpx/lcos/preprocessed/async_fwd_50.hpp>
#else
#error "HPX_ACTION_ARGUMENT_LIMIT out of bounds for preprocessed headers"
#endif

#endif
