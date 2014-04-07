//  Copyright (c) 2014 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef HPX_EXAMPLES_MINI_GHOST_GLOBAL_SUM_HPP
#define HPX_EXAMPLES_MINI_GHOST_GLOBAL_SUM_HPP

#include <hpx/include/local_lcos.hpp>

namespace mini_ghost {
    template <typename T>
    struct global_sum
    {
    private:
        typedef hpx::lcos::local::spinlock mutex_type;

    public:
        global_sum()
          : value_()
        {
        }
        global_sum(global_sum const& rhs)
          : value_(rhs.value_)
        {
        }

        hpx::future<T> add(std::size_t n, std::size_t & generation)
        {
            generation = 0;
            hpx::future<void> f = gate_.get_future(n, &generation);
            value_ = 0;

            /*
            Action action;
            hpx::lcos::broadcast_with_index(action, component->stepper_ids, generation, value);
            */

            return f.then([this](hpx::future<void>) -> T { T v = value_; value_ = T(0); return v; });
        }

        void set_data(std::size_t generation, std::size_t which, T value)
        {
            gate_.synchronize(generation, "global_sum::set_data");
            {
                mutex_type::scoped_lock l(mtx_);
                value_ += value;
            }

            gate_.set(which);         // trigger corresponding and-gate input
        }

    private:
        mutable mutex_type mtx_;

        T value_;

        hpx::lcos::local::base_and_gate<> gate_;        // synchronization gate
    };
}

#endif
