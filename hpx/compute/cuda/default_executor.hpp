//  Copyright (c) 2016 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef HPX_COMPUTE_CUDA_DEFAULT_EXECUTOR_HPP
#define HPX_COMPUTE_CUDA_DEFAULT_EXECUTOR_HPP

#include <hpx/config.hpp>

#if defined(HPX_HAVE_CUDA) && defined(__CUDACC__)
#include <hpx/lcos/future.hpp>
#include <hpx/traits/is_executor.hpp>
#include <hpx/util/decay.hpp>
#include <hpx/util/invoke.hpp>

#include <hpx/compute/cuda/allocator.hpp>
#include <hpx/compute/cuda/default_executor_parameters.hpp>
#include <hpx/compute/cuda/detail/launch.hpp>
#include <hpx/compute/cuda/target.hpp>

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

#include <boost/range/functions.hpp>

namespace hpx { namespace compute { namespace cuda
{
    struct default_executor : hpx::parallel::executor_tag
    {
        // By default, this executor relies on a special executor parameters
        // implementation which knows about the specifics of creating the
        // bulk-shape ranges for the accelerator.
        typedef default_executor_parameters executor_parameters_type;
        default_executor(cuda::target const& target)
          : target_(target)
        {}

        std::size_t processing_units_count() const
        {
            return target_.native_handle().processing_units();
        }

        template <typename F, typename ... Ts>
        void apply_execute(F && f, Ts &&... ts) const
        {
            detail::launch(target_, 1, 1,
                std::forward<F>(f), std::forward<Ts>(ts)...);
        }

        template <typename F, typename ... Ts>
        hpx::future<void> async_execute(F && f, Ts &&... ts) const
        {
            apply_execute(std::forward<F>(f), std::forward<Ts>(ts)...);
            return target_.get_future();
        }

        template <typename F, typename ... Ts>
        void execute(F && f, Ts &&... ts) const
        {
            apply_execute(std::forward<F>(f), std::forward<Ts>(ts)...);
            target_.synchronize();
        }

        template <typename F, typename Shape, typename ... Ts>
        void bulk_launch(F && f, Shape const& shape, Ts &&... ts) const
        {
            typedef typename boost::range_const_iterator<Shape>::type
                iterator_type;
            typedef typename std::iterator_traits<iterator_type>::value_type
                value_type;
            for (auto const& s: shape)
            {
                auto begin = hpx::util::get<0>(s);
                std::size_t chunk_size = hpx::util::get<1>(s);
                std::size_t base_idx = hpx::util::get<2>(s);

                // FIXME: make the 1024 to be configurable...
                int threads_per_block =
                    (std::min)(1024, static_cast<int>(chunk_size));
                int num_blocks = static_cast<int>(
                    (chunk_size + threads_per_block - 1) / threads_per_block);

                detail::launch(
                    target_, num_blocks, threads_per_block,
                    [begin] HPX_DEVICE (F f, Ts&... ts)
                    {
                        int idx = blockIdx.x * blockDim.x + threadIdx.x;
                        hpx::util::invoke(f, value_type(begin + idx, 1, idx),
                            ts...);
                    },
                    std::forward<F>(f), std::forward<Ts>(ts)...
                );
            }
        }

        template <typename F, typename Shape, typename ... Ts>
        std::vector<hpx::future<void> >
        bulk_async_execute(F && f, Shape const& shape, Ts &&... ts) const
        {
            bulk_launch(std::forward<F>(f), shape, std::forward<Ts>(ts)...);

            std::vector<hpx::future<void> > result;
            result.push_back(target_.get_future());
            return result;
        }

        template <typename F, typename Shape, typename ... Ts>
        void bulk_execute(F && f, Shape const& shape, Ts &&... ts) const
        {
            bulk_launch(std::forward<F>(f), shape, std::forward<Ts>(ts)...);
            target_.synchronize();
        }

        cuda::target& target()
        {
            return target_;
        }

        cuda::target const& target() const
        {
            return target_;
        }

    private:
        cuda::target target_;
    };
}}}

#endif
#endif
