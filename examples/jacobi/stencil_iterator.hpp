
//  Copyright (c) 2012 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef JACOBI_STENCIL_ITERATOR_HPP
#define JACOBI_STENCIL_ITERATOR_HPP

#include "row_range.hpp"

#include <hpx/include/naming.hpp>
#include <hpx/include/lcos.hpp>
#include <hpx/components/dataflow/dataflow_base.hpp>

namespace jacobi
{
    struct row;

    struct stencil_iterator
    {
        stencil_iterator() {}

        hpx::lcos::future<void> init(
            jacobi::row const & r
          , std::size_t y_
          , std::size_t nx_
          , std::size_t ny_
          , std::size_t l
        );
        hpx::lcos::future<void> setup_boundary(stencil_iterator const & top, stencil_iterator const & bottom);

        hpx::lcos::future<void> run(std::size_t max_iterations);

        hpx::lcos::dataflow_base<row_range> get(std::size_t iter, std::size_t begin, std::size_t end);

        template <typename Archive>
        void serialize(Archive & ar, unsigned)
        {
            ar & id;
        }

        hpx::naming::id_type id;
    };
}

#endif
