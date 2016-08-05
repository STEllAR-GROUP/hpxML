//  Copyright (c) 2007-2012 Hartmut Kaiser
//  Copyright (c) 2014 Agustin Berge
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_UTIL_DATE_TIME_CHRONO_APR_10_2012_0449PM)
#define HPX_UTIL_DATE_TIME_CHRONO_APR_10_2012_0449PM

#include <hpx/config.hpp>

#if HPX_HAVE_BOOST_CHRONO_COMPATIBILITY
#  include <boost/chrono/chrono.hpp>
#endif

#include <chrono>

namespace hpx { namespace util
{
    class steady_time_point
    {
        typedef std::chrono::steady_clock::time_point value_type;

    public:
        steady_time_point(value_type const& abs_time)
          : _abs_time(abs_time)
        {}

        template <typename Clock, typename Duration>
        steady_time_point(std::chrono::time_point<Clock, Duration> const& abs_time)
          : _abs_time(std::chrono::steady_clock::now()
              + (abs_time - Clock::now()))
        {}

#if HPX_HAVE_BOOST_CHRONO_COMPATIBILITY
        template <typename Clock, typename Duration>
        steady_time_point(boost::chrono::time_point<Clock, Duration> const& abs_time)
        {
            std::chrono::nanoseconds duration(
                boost::chrono::duration_cast<boost::chrono::nanoseconds>(
                    abs_time - Clock::now()).count());

            _abs_time = std::chrono::steady_clock::now() + duration;
        }
#endif

        value_type const& value() const HPX_NOEXCEPT
        {
            return _abs_time;
        }

    private:
        value_type _abs_time;
    };

    class steady_duration
    {
        typedef std::chrono::steady_clock::duration value_type;

    public:
        steady_duration(value_type const& rel_time)
          : _rel_time(rel_time)
        {}

        template <typename Rep, typename Period>
        steady_duration(std::chrono::duration<Rep, Period> const& rel_time)
          : _rel_time(std::chrono::duration_cast<value_type>(rel_time))
        {
            if (_rel_time < rel_time)
                ++_rel_time;
        }

#if HPX_HAVE_BOOST_CHRONO_COMPATIBILITY
        template <typename Rep, typename Period>
        steady_duration(boost::chrono::duration<Rep, Period> const& rel_time)
        {
            std::chrono::nanoseconds duration(
                boost::chrono::duration_cast<boost::chrono::nanoseconds>(
                    rel_time).count());

            _rel_time = std::chrono::duration_cast<value_type>(duration);
            if (_rel_time < duration)
                ++_rel_time;
        }
#endif

        value_type const& value() const HPX_NOEXCEPT
        {
            return _rel_time;
        }

        std::chrono::steady_clock::time_point from_now() const HPX_NOEXCEPT
        {
            return std::chrono::steady_clock::now() + _rel_time;
        }

    private:
        value_type _rel_time;
    };
}}

#endif
