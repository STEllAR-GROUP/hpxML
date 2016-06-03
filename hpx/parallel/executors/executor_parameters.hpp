//  Copyright (c) 2016 Marcin Copik
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

/// \file parallel/executors/executor_parameters.hpp

#if !defined(HPX_PARALLEL_EXECUTOR_PARAMETERS)
#define HPX_PARALLEL_EXECUTOR_PARAMETERS

#include <hpx/config.hpp>
#include <hpx/traits/is_executor_parameters.hpp>
#include <hpx/parallel/config/inline_namespace.hpp>
#include <hpx/parallel/executors/executor_traits.hpp>
#include <hpx/util/always_void.hpp>

#include <type_traits>
#include <utility>
#include <vector>
#include <cstdarg>

namespace hpx { namespace parallel { HPX_INLINE_NAMESPACE(v3)
{
    namespace detail {

        template<template<typename> class Condition, typename Arg, typename Enable = void>
        struct counter_increment
        {
            constexpr static int value = 0;
        };

        template<template<typename> class Condition, typename Arg>
        struct counter_increment<Condition, Arg, typename std::enable_if< Condition<Arg>::value>::type >
        {
            constexpr static int value = 1;
        };

        template<template<typename> class Condition, typename ...Args>
        struct parameter_type_counter;

        template<template<typename> class Condition>
        struct parameter_type_counter<Condition>
        {
            constexpr static int value = 0;
        };

        /// Return the number of parameters which have been derived from type T.
        /// Useful for checking possible duplicates or ensuring that all passed types
        /// are indeed executor parameters.
        ///
        /// \param T                [in] Parameter to look for
        /// \param Parameters       [in] The executor object to use.
        ///
        //
        template<template<typename> class Condition, typename Arg1, typename ...Args>
        struct parameter_type_counter<Condition, Arg1, Args...>
        {
            constexpr static int value = parameter_type_counter<Condition, Args...>::value + counter_increment<Condition, Arg1>::value;
        };

        template<typename... Params>
        struct executor_parameters : public Params...
        {
        public:
            
            executor_parameters()
            {
                static_assert(parameter_type_counter<hpx::parallel::is_executor_parameters, Params...>::value == sizeof...(Params),
                    "All passed parameters must be a proper executor parameter!");

                static_assert(parameter_type_counter<hpx::parallel::is_executor_parameters_chunk_size, Params...>::value <= 1,
                    "Passing more than one chunk size policy is prohibited!");
            }
            
            template<typename... Params_>
            executor_parameters(Params_ &&... params) : Params(params)...
            {
                static_assert(parameter_type_counter<hpx::parallel::is_executor_parameters, Params...>::value == sizeof...(Params),
                    "All passed parameters must be a proper executor parameter!");

                static_assert(parameter_type_counter<hpx::parallel::is_executor_parameters_chunk_size, Params...>::value <= 1,
                    "Passing more than one chunk size policy is prohibited!");
            }
        };
    }

	template<typename... Params>
	struct executor_parameters_join
	{
        typedef detail::executor_parameters<typename hpx::util::decay<typename hpx::util::decay_unwrap<Params>::type...>::type > type;

		//static type join(Params &&... params)
		//{
		//	return executor_parameters<Params...>(std::forward<Params>(params)...);
		//}
	};

}}}

#endif
