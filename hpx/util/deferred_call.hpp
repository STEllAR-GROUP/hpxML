//  Copyright (c) 2014-2015 Agustin Berge
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef HPX_UTIL_DEFERRED_CALL_HPP
#define HPX_UTIL_DEFERRED_CALL_HPP

#include <hpx/config.hpp>
#include <hpx/traits/is_callable.hpp>
#include <hpx/util/decay.hpp>
#include <hpx/util/invoke_fused.hpp>
#include <hpx/util/tuple.hpp>

#include <boost/static_assert.hpp>

#include <type_traits>
#include <utility>

namespace hpx { namespace util
{
    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        template <typename T>
        struct deferred_result_of;

        template <typename F, typename ...Ts>
        struct deferred_result_of<F(Ts...)>
          : util::result_of<
                typename util::decay_unwrap<F>::type(
                    typename util::decay_unwrap<Ts>::type...)
            >
        {};

        ///////////////////////////////////////////////////////////////////////
        template <typename T>
        class deferred;

        template <typename F, typename ...Ts>
        class deferred<F(Ts...)>
        {
        public:
            deferred() {} // needed for serialization

            explicit deferred(F&& f, Ts&&... vs)
              : _f(std::forward<F>(f))
              , _args(std::forward<Ts>(vs)...)
            {}

#if defined(HPX_HAVE_CXX11_DEFAULTED_FUNCTIONS)
            deferred(deferred&&) = default;
#else
            deferred(deferred&& other)
              : _f(std::move(other._f))
              , _args(std::move(other._args))
            {}
#endif

#if defined(HPX_HAVE_CXX11_DELETED_FUNCTIONS)
            deferred& operator=(deferred&&) = delete;
#endif

            inline typename deferred_result_of<F(Ts...)>::type
            operator()()
            {
                return util::invoke_fused(std::move(_f), std::move(_args));
            }

            template <typename Archive>
            void serialize(Archive& ar, unsigned int const /*version*/)
            {
                ar & _f;
                ar & _args;
            }

        private:
            typename util::decay_unwrap<F>::type _f;
            util::tuple<typename util::decay_unwrap<Ts>::type...> _args;
        };
    }

    template <typename F, typename ...Ts>
    inline detail::deferred<F(Ts&&...)>
    deferred_call(F&& f, Ts&&... vs)
    {
        BOOST_STATIC_ASSERT(
            traits::detail::is_deferred_callable<F(Ts&&...)>::value);

        return detail::deferred<F(Ts&&...)>(
            std::forward<F>(f), std::forward<Ts>(vs)...);
    }

    // nullary functions do not need to be bound again
    template <typename F>
    inline typename std::decay<F>::type
    deferred_call(F&& f)
    {
        BOOST_STATIC_ASSERT(
            traits::detail::is_deferred_callable<F()>::value);

        return std::forward<F>(f);
    }
}}

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace serialization
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Archive, typename T>
    HPX_FORCEINLINE
    void serialize(
        Archive& ar
      , ::hpx::util::detail::deferred<T>& d
      , unsigned int const version = 0
    )
    {
        d.serialize(ar, version);
    }
}}

#endif
