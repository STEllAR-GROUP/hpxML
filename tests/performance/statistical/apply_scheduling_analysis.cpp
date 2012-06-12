//  Copyright (c)      2012 Daniel Kogler
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "simple_declarations.cpp"
#include "statstd.cpp"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
template <typename Vector, typename Package>
void create_packages(Vector& packages, uint64_t num, double ot){
    uint64_t i = 0;
    packages.reserve(num);

    for(; i < num; ++i)
        packages.push_back(new Package());
}

///////////////////////////////////////////////////////////////////////////////

//this runs a test of checking if a gid is local
template <typename Vector, typename Package, typename Action>
void run_tests(uint64_t);

///////////////////////////////////////////////////////////////////////////////
//all of the measured tests are declared in this section

//measure how long it takes to register work with the thread_manager
template <typename Vector, typename Action>
void register_work(Vector packages, uint64_t num, double ot){
    using namespace hpx;
    uint64_t i = 0;
    string message = "Measuring time required to register work with the "
                     "thread manager:";
    vector<double> time;
    time.reserve(num);

    naming::address addr;
    agas::is_local_address(find_here(), addr);
    naming::address::address_type lva = addr.address_;
    util::tuple0<> env;
    BOOST_RV_REF(HPX_STD_FUNCTION<
        threads::thread_function_type>) func = 
        Action::construct_thread_function(
        lva, boost::forward<util::tuple0<> >(env));
    applier::applier* app = applier::get_applier_ptr();
    threads::thread_priority priority = actions::action_priority<Action>();
    threads::thread_init_data data(boost::move(func), "<unknown>", 
        lva, priority, std::size_t(-1));
    threads::threadmanager_base& base = app->get_thread_manager();
    threads::thread_state_enum state = threads::pending;
    error_code ec = hpx::throws;

    for(; i < num; i++){
        high_resolution_timer t1;
        base.register_work(data, state, ec);
        time.push_back(t1.elapsed());
    }
    printout(time, ot, message);
}

///////////////////////////////////////////////////////////////////////////////
int hpx_main(variables_map& vm){
    uint64_t num = vm["number-spawned"].as<uint64_t>();
    run_tests<vector<void_package0*>, void_package0, void_action0>(num);
    return hpx::finalize();
}

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]){
    // Configure application-specific options.
    options_description
        desc_commandline("usage: " HPX_APPLICATION_STRING " [options]");

    desc_commandline.add_options()
        ("number-spawned,N",
            boost::program_options::value<uint64_t>()
                ->default_value(500000),
            "number of packaged_actions created and run");

    // Initialize and run HPX
    return hpx::init(desc_commandline, argc, argv);
}

///////////////////////////////////////////////////////////////////////////////


//this tests how long is required to check if an address is local
template <typename Vector, typename Package, typename Action>
void run_tests(uint64_t num){
    double ot = timer_overhead(num);
    string message;
    vector<double> time;
    Vector packages;
    create_packages<Vector, Package>(packages, num, ot);

    register_work<Vector, Action>(packages, num, ot);
}
