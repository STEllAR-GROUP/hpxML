///////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach 
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
///////////////////////////////////////////////////////////////////////////////

#include <hpx/hpx_init.hpp>
#include <hpx/runtime.hpp>
#include <hpx/include/performance_counters.hpp>

using boost::program_options::variables_map;
using boost::program_options::options_description;

using hpx::init;
using hpx::finalize;

using hpx::performance_counters::install_counter;
using hpx::performance_counters::install_counter_type;
using hpx::performance_counters::counter_raw;

///////////////////////////////////////////////////////////////////////////////
boost::int64_t bar() { return 42; }

///////////////////////////////////////////////////////////////////////////////
void startup_()
{
    install_counter_type("/foo/buzz", counter_raw);
    install_counter("/foo(bar)/buzz", bar); 
}

///////////////////////////////////////////////////////////////////////////////
int hpx_main(variables_map& vm)
{
    // Do nothing.
    finalize();
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    // Configure application-specific options
    options_description
       desc_commandline("Usage: " HPX_APPLICATION_STRING " [options]");
    
    // Initialize and run HPX
    return init(desc_commandline, argc, argv, startup_);
}

