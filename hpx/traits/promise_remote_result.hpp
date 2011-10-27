//  Copyright (c) 2007-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_TRAITS_PROMISE_REMOTE_RESULT_OCT_27_2011_0416PM)
#define HPX_TRAITS_PROMISE_REMOTE_RESULT_OCT_27_2011_0416PM

#include <hpx/traits.hpp>

namespace hpx { namespace traits
{
    template <typename Result, typename Enable>
    struct promise_remote_result
      : boost::mpl::identity<Result>
    {};

    template <>
    struct promise_remote_result<void>
      : boost::mpl::identity<util::unused_type>
    {};
}}

#endif
