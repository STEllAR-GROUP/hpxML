//  Copyright (c) 2011 Bryce Adelstein-Lelbach 
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx_init.hpp>
#include <hpx/util/lightweight_test.hpp>
#include <hpx/runtime/actions/continuation_impl.hpp>

#include <boost/date_time/posix_time/posix_time.hpp>

#include <tests/correctness/agas/components/managed_refcnt_checker.hpp>

using boost::program_options::variables_map;
using boost::program_options::options_description;
using boost::program_options::value;

using hpx::init;
using hpx::finalize;
using hpx::find_here;

using boost::posix_time::milliseconds;

using hpx::naming::id_type;

using hpx::test::managed_refcnt_checker;

///////////////////////////////////////////////////////////////////////////////
int hpx_main(
    variables_map& vm
    )
{
    const boost::uint64_t delay = vm["delay"].as<boost::uint64_t>();

    {
        /// AGAS reference-counting test 3 (from #126):
        ///
        ///     Create two components locally, and have the second component
        ///     store a reference to the first component. Let the original
        ///     references to both components go out of scope. Both components
        ///     should be deleted. 

        managed_refcnt_checker monitor0(find_here());
        managed_refcnt_checker monitor1(find_here());

        {
            // Have the second object store a reference to the first object.
            monitor1.take_reference(monitor0.get_gid());

            // Detach the references.
            id_type id0 = monitor0.detach()
                  , id1 = monitor1.detach();
            
            // Both components should still be alive.
            HPX_TEST_EQ(false, monitor0.ready(milliseconds(delay))); 
            HPX_TEST_EQ(false, monitor1.ready(milliseconds(delay))); 
        }

        // Both components should be out of scope now.
        HPX_TEST_EQ(true, monitor0.ready(milliseconds(delay))); 
        HPX_TEST_EQ(true, monitor1.ready(milliseconds(delay))); 
    }

    finalize();
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
int main(
    int argc
  , char* argv[]
    )
{
    // Configure application-specific options.
    options_description cmdline("usage: " HPX_APPLICATION_STRING " [options]");

    cmdline.add_options()
        ( "delay"
        , value<boost::uint64_t>()->default_value(500)
        , "number of milliseconds to wait for object destruction") 
        ;

    // Initialize and run HPX.
    return init(cmdline, argc, argv);
}

