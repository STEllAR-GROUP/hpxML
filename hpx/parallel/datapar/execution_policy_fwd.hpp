//  Copyright (c) 2016 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_PARALLEL_DATAPAR_EXECUTION_POLICY_FWD_SEP_07_2016_0528AM)
#define HPX_PARALLEL_DATAPAR_EXECUTION_POLICY_FWD_SEP_07_2016_0528AM

#include <hpx/config.hpp>

#if defined(HPX_HAVE_VC_DATAPAR)
#include <hpx/parallel/config/inline_namespace.hpp>

namespace hpx { namespace parallel { HPX_INLINE_NAMESPACE(v1)
{
    struct datapar_execution_policy;

    template <typename Executor, typename Parameters>
    struct datapar_execution_policy_shim;

    struct datapar_task_execution_policy;

    template <typename Executor, typename Parameters>
    struct datapar_task_execution_policy_shim;
}}}

#endif
#endif
