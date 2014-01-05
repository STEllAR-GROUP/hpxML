
//  Copyright (c) 2012 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_fwd.hpp>
#include <hpx/components/remote_object/object.hpp>
#include <hpx/components/distributing_factory/distributing_factory.hpp>
#include <hpx/components/remote_object/distributed_new.hpp>
#include <hpx/lcos/wait_all.hpp>
#include <hpx/include/iostreams.hpp>

#include "grid.hpp"
#include "row.hpp"

namespace jacobi
{
    grid::grid(std::size_t nx, std::size_t ny, double value)
        //: rows(ny)
    {
        hpx::components::distributing_factory factory;
        factory.create(hpx::find_here());

        // make get the type of the solver component
        hpx::components::component_type
            type = hpx::components::get_component_type<
                server::row
            >();
 
        hpx::components::distributing_factory::result_type rows_allocated =
            factory.create_components(type, ny);

        rows.reserve(ny);
        std::vector<hpx::lcos::unique_future<void> > init_futures;
        init_futures.reserve(ny);
        BOOST_FOREACH(hpx::naming::id_type id, hpx::util::locality_results(rows_allocated))
        {
            row r; r.id = id;
            init_futures.push_back(r.init(nx, value));
            rows.push_back(r);
        }

        hpx::wait_all(init_futures);
    }
}
