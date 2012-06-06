//  Copyright (c) 2007-2012 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_TRAITS_GET_REMOTE_RESULT_FEB_10_2011_1123AM)
#define HPX_TRAITS_GET_REMOTE_RESULT_FEB_10_2011_1123AM

#include <hpx/traits.hpp>
#include <hpx/util/unused.hpp>

#include <boost/config.hpp>
#include <boost/move/move.hpp>

namespace hpx { namespace traits
{
    template <typename Result, typename RemoteResult, typename Enable>
    struct get_remote_result
    {
        static Result call(RemoteResult const& rhs)
        {
            return Result(rhs);
        }

        static Result call(BOOST_RV_REF(RemoteResult) rhs)
        {
          return Result(boost::move(rhs));
        }
    };

    template <typename Result>
    struct get_remote_result<Result, Result>
    {
        static Result const& call(Result const& rhs)
        {
            return rhs;
        }
#if !defined(BOOST_NO_RVALUE_REFERENCES)
        static Result&& call(Result&& rhs)
        {
          return boost::move(rhs);
        }
#else
        static ::boost::rv<Result>& call(BOOST_RV_REF(Result) rhs)
        {
          return boost::move(rhs);
        }
#endif
    };
}}

#endif
