//  Copyright (c) 2011 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/components/remote_object/server/remote_object.hpp>

namespace hpx { namespace components { namespace server
{
    void remote_object::apply(hpx::util::function<void(void**)> f, std::size_t)
    {
        f(&object);
    }

    void remote_object::set_dtor(hpx::util::function<void(void**)> f, std::size_t)
    {
        dtor = f;
    }
}}}
