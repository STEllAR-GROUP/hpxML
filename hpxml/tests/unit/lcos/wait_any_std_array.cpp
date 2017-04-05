//  Copyright (c) 2017 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/config.hpp>

#if defined(HPX_HAVE_CXX11_STD_ARRAY)
#include <hpx/hpx_main.hpp>
#include <hpx/include/future.hpp>
#include <hpx/lcos/wait_any.hpp>

#include <array>

int main()
{
    std::array<hpx::future<int>, 2> future_array{
        { hpx::make_ready_future(0), hpx::make_ready_future(0) }
    };

    hpx::wait_any(future_array);

    return 0;
}
#endif
