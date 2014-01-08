//  Copyright (c) 2007-2013 Hartmut Kaiser
//  Copyright (c)      2013 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/lcos/future.hpp>

#if defined(HPX_ENABLE_DEPRECATED_FUTURE)
HPX_REGISTER_TYPED_CONTINUATION(
    hpx::lcos::future<void>,
    hpx_lcos_future_void_typed_continuation)
#endif
