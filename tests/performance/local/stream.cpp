//  Copyright (c) 2015 Thomas Heller
//  Copyright (c) 2015 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//
// This code is based on the STREAM benchmark:
// https://www.cs.virginia.edu/stream/ref.html
//
// We adopted the code and HPXifyed it.
//

#include <hpx/hpx_init.hpp>
#include <hpx/hpx.hpp>
#include <hpx/version.hpp>
#include <hpx/include/parallel_algorithm.hpp>
#include <hpx/include/parallel_executors.hpp>
#include <hpx/include/parallel_transform.hpp>
#include <hpx/include/parallel_executor_parameters.hpp>
#include <hpx/include/iostreams.hpp>
#include <hpx/include/threads.hpp>

#include <hpx/parallel/util/numa_allocator.hpp>

#include <boost/format.hpp>
#include <boost/range/functions.hpp>

#include <string>
#include <vector>

#ifndef STREAM_TYPE
#define STREAM_TYPE double
#endif

///////////////////////////////////////////////////////////////////////////////
hpx::threads::topology& retrieve_topology()
{
    static hpx::threads::topology& topo = hpx::threads::create_topology();
    return topo;
}

///////////////////////////////////////////////////////////////////////////////
double mysecond()
{
    return hpx::util::high_resolution_clock::now() * 1e-9;
}

int checktick()
{
    static const std::size_t M = 20;
    int minDelta, Delta;
    double t1, t2, timesfound[M];

    // Collect a sequence of M unique time values from the system.
    for (std::size_t i = 0; i < M; i++) {
        t1 = mysecond();
        while( ((t2=mysecond()) - t1) < 1.0E-6 )
            ;
        timesfound[i] = t1 = t2;
    }

    // Determine the minimum difference between these M values.
    // This result will be our estimate (in microseconds) for the
    // clock granularity.
    minDelta = 1000000;
    for (std::size_t i = 1; i < M; i++) {
        Delta = (int)( 1.0E6 * (timesfound[i]-timesfound[i-1]));
        minDelta = (std::min)(minDelta, (std::max)(Delta,0));
    }

    return(minDelta);
}

template <typename Vector>
void check_results(std::size_t iterations,
    Vector const & a, Vector const & b, Vector const & c)
{
    STREAM_TYPE aj,bj,cj,scalar;
    STREAM_TYPE aSumErr,bSumErr,cSumErr;
    STREAM_TYPE aAvgErr,bAvgErr,cAvgErr;
    double epsilon;
    int ierr,err;

    /* reproduce initialization */
    aj = 1.0;
    bj = 2.0;
    cj = 0.0;
    /* a[] is modified during timing check */
    aj = 2.0E0 * aj;
    /* now execute timing loop */
    scalar = 3.0;
    for (std::size_t k=0; k<iterations; k++)
        {
            cj = aj;
            bj = scalar*cj;
            cj = aj+bj;
            aj = bj+scalar*cj;
        }

    /* accumulate deltas between observed and expected results */
    aSumErr = 0.0;
    bSumErr = 0.0;
    cSumErr = 0.0;
    for (std::size_t j=0; j<a.size(); j++) {
        aSumErr += std::abs(a[j] - aj);
        bSumErr += std::abs(b[j] - bj);
        cSumErr += std::abs(c[j] - cj);
        // if (j == 417) printf("Index 417: c[j]: %f, cj: %f\n",c[j],cj);   // MCCALPIN
    }
    aAvgErr = aSumErr / (STREAM_TYPE) a.size();
    bAvgErr = bSumErr / (STREAM_TYPE) a.size();
    cAvgErr = cSumErr / (STREAM_TYPE) a.size();

    if (sizeof(STREAM_TYPE) == 4) {
        epsilon = 1.e-6;
    }
    else if (sizeof(STREAM_TYPE) == 8) {
        epsilon = 1.e-13;
    }
    else {
        printf("WEIRD: sizeof(STREAM_TYPE) = %zu\n", sizeof(STREAM_TYPE));
        epsilon = 1.e-6;
    }

    err = 0;
    if (std::abs(aAvgErr/aj) > epsilon) {
        err++;
        printf ("Failed Validation on array a[], AvgRelAbsErr > epsilon (%e)\n",
            epsilon);
        printf ("     Expected Value: %e, AvgAbsErr: %e, AvgRelAbsErr: %e\n",
            aj,aAvgErr,std::abs(aAvgErr)/aj);
        ierr = 0;
        for (std::size_t j=0; j<a.size(); j++) {
            if (std::abs(a[j]/aj-1.0) > epsilon) {
                ierr++;
#ifdef VERBOSE
                if (ierr < 10) {
                    printf("         array a: index: %ld, expected: %e, "
                        "observed: %e, relative error: %e\n",
                        j,aj,a[j],std::abs((aj-a[j])/aAvgErr));
                }
#endif
            }
        }
        printf("     For array a[], %d errors were found.\n",ierr);
    }
    if (std::abs(bAvgErr/bj) > epsilon) {
        err++;
        printf ("Failed Validation on array b[], AvgRelAbsErr > epsilon (%e)\n",
            epsilon);
        printf ("     Expected Value: %e, AvgAbsErr: %e, AvgRelAbsErr: %e\n",
            bj,bAvgErr,std::abs(bAvgErr)/bj);
        printf ("     AvgRelAbsErr > Epsilon (%e)\n",epsilon);
        ierr = 0;
        for (std::size_t j=0; j<a.size(); j++) {
            if (std::abs(b[j]/bj-1.0) > epsilon) {
                ierr++;
#ifdef VERBOSE
                if (ierr < 10) {
                    printf("         array b: index: %ld, expected: %e, "
                        "observed: %e, relative error: %e\n",
                        j,bj,b[j],std::abs((bj-b[j])/bAvgErr));
                }
#endif
            }
        }
        printf("     For array b[], %d errors were found.\n",ierr);
    }
    if (std::abs(cAvgErr/cj) > epsilon) {
        err++;
        printf ("Failed Validation on array c[], AvgRelAbsErr > epsilon (%e)\n",
            epsilon);
        printf ("     Expected Value: %e, AvgAbsErr: %e, AvgRelAbsErr: %e\n",
            cj,cAvgErr,std::abs(cAvgErr)/cj);
        printf ("     AvgRelAbsErr > Epsilon (%e)\n",epsilon);
        ierr = 0;
        for (std::size_t j=0; j<a.size(); j++) {
            if (std::abs(c[j]/cj-1.0) > epsilon) {
                ierr++;
#ifdef VERBOSE
                if (ierr < 10) {
                    printf("         array c: index: %ld, expected: %e, "
                        "observed: %e, relative error: %e\n",
                        j,cj,c[j],std::abs((cj-c[j])/cAvgErr));
                }
#endif
            }
        }
        printf("     For array c[], %d errors were found.\n",ierr);
    }
    if (err == 0) {
        printf ("Solution Validates: avg error less than %e on all three arrays\n",
            epsilon);
    }
#ifdef VERBOSE
    printf ("Results Validation Verbose Results: \n");
    printf ("    Expected a(1), b(1), c(1): %f %f %f \n",aj,bj,cj);
    printf ("    Observed a(1), b(1), c(1): %f %f %f \n",a[1],b[1],c[1]);
    printf ("    Rel Errors on a, b, c:     %e %e %e \n",std::abs(aAvgErr/aj),
        std::abs(bAvgErr/bj),std::abs(cAvgErr/cj));
#endif
}

template <typename Vector, typename Policy>
std::vector<std::vector<double> >
numa_domain_worker(std::size_t domain,
    Policy policy,
    hpx::lcos::local::latch& l,
    std::size_t part_size, std::size_t offset, std::size_t iterations,
    Vector& a, Vector& b, Vector& c)
{
    typedef typename Vector::iterator iterator;
    iterator a_begin = a.begin() + offset;
    iterator b_begin = b.begin() + offset;
    iterator c_begin = c.begin() + offset;

    iterator a_end = a_begin + part_size;
    iterator b_end = b_begin + part_size;
    iterator c_end = c_begin + part_size;

    // Initialize arrays
    hpx::parallel::fill(policy, a_begin, a_end, 1.0);
    hpx::parallel::fill(policy, b_begin, b_end, 2.0);
    hpx::parallel::fill(policy, c_begin, c_end, 0.0);

    double t = mysecond();
    hpx::parallel::for_each(policy, a_begin, a_end,
        [&policy](STREAM_TYPE & v)
        {
            v = 2.0 * v;

#if defined(HPX_DEBUG)
            // make sure memory was placed appropriately
            hpx::threads::topology& topo = retrieve_topology();
            hpx::threads::mask_cref_type mem_mask =
                topo.get_thread_affinity_mask_from_lva(
                    reinterpret_cast<hpx::naming::address_type>(&v));

            typedef typename Policy::executor_type executor_type;
            typedef hpx::parallel::executor_information_traits<
                executor_type> traits;

            std::size_t thread_num = hpx::get_worker_thread_num();
            hpx::threads::mask_cref_type thread_mask =
                traits::get_pu_mask(policy.executor(), topo, thread_num);

            HPX_ASSERT(hpx::threads::mask_size(mem_mask) ==
                hpx::threads::mask_size(thread_mask));
            HPX_ASSERT(hpx::threads::bit_and(mem_mask, thread_mask,
                hpx::threads::mask_size(mem_mask)));
#endif
        });
    t = 1.0E6 * (mysecond() - t);

    if (domain == 0)
    {
        // Get initial value for system clock.
        int quantum = checktick();
        if(quantum >= 1)
        {
            std::cout
                << "Your clock granularity/precision appears to be " << quantum
                << " microseconds.\n"
                ;
        }
        else
        {
            std::cout
                << "Your clock granularity appears to be less than one microsecond.\n"
                ;
            quantum = 1;
        }

        std::cout
            << "Each test below will take on the order"
            << " of " << (int) t << " microseconds.\n"
            << "   (= " << (int) (t/quantum) << " clock ticks)\n"
            << "Increase the size of the arrays if this shows that\n"
            << "you are not getting at least 20 clock ticks per test.\n"
            << "-------------------------------------------------------------\n"
            ;

        std::cout
            << "WARNING -- The above is only a rough guideline.\n"
            << "For best results, please be sure you know the\n"
            << "precision of your system timer.\n"
            << "-------------------------------------------------------------\n"
            ;
    }

    // synchronize across NUMA domains
    l.count_down_and_wait();

    ///////////////////////////////////////////////////////////////////////////
    // Main Loop
    std::vector<std::vector<double> > timing(4, std::vector<double>(iterations));

    double scalar = 3.0;
    for(std::size_t iteration = 0; iteration != iterations; ++iteration)
    {
        // Copy
        timing[0][iteration] = mysecond();
        hpx::parallel::copy(policy, a_begin, a_end, c_begin);
        timing[0][iteration] = mysecond() - timing[0][iteration];

        // Scale
        timing[1][iteration] = mysecond();
        hpx::parallel::transform(policy,
            c_begin, c_end, b_begin,
            [scalar](STREAM_TYPE val)
            {
                return scalar * val;
            }
        );
        timing[1][iteration] = mysecond() - timing[1][iteration];

        // Add
        timing[2][iteration] = mysecond();
        hpx::parallel::transform(policy,
            a_begin, a_end, b_begin, b_end, c_begin,
            [](STREAM_TYPE val1, STREAM_TYPE val2)
            {
                return val1 + val2;
            }
        );
        timing[2][iteration] = mysecond() - timing[2][iteration];

        // Triad
        timing[3][iteration] = mysecond();
        hpx::parallel::transform(policy,
            b_begin, b_end, c_begin, c_end, a_begin,
            [scalar](STREAM_TYPE val1, STREAM_TYPE val2)
            {
                return val1 + scalar * val2;
            }
        );
        timing[3][iteration] = mysecond() - timing[3][iteration];
    }

    return timing;
}

///////////////////////////////////////////////////////////////////////////////
std::size_t get_num_numa_nodes(hpx::threads::topology const& topo,
    boost::program_options::variables_map& vm)
{
    std::size_t numa_nodes = topo.get_number_of_numa_nodes();
    if (numa_nodes == 0)
        numa_nodes = topo.get_number_of_sockets();

    std::string num_numa_domains_str = vm["stream-numa-domains"].as<std::string>();
    if (num_numa_domains_str != "all")
    {
        numa_nodes = hpx::util::safe_lexical_cast<std::size_t>(num_numa_domains_str);
    }
    return numa_nodes;
}

std::pair<std::size_t, std::size_t> get_num_numa_pus(
    hpx::threads::topology const& topo, std::size_t numa_nodes,
    boost::program_options::variables_map& vm)
{
    std::size_t numa_pus = hpx::threads::hardware_concurrency() / numa_nodes;

    std::string num_threads_str = vm["stream-threads"].as<std::string>();
    std::size_t pus = numa_pus;

    if(num_threads_str != "all")
    {
        pus = hpx::util::safe_lexical_cast<std::size_t>(num_threads_str);
    }

    return std::make_pair(numa_pus, pus);
}

///////////////////////////////////////////////////////////////////////////////
int hpx_main(boost::program_options::variables_map& vm)
{
    // extract hardware topology
    hpx::threads::topology const& topo = retrieve_topology();

    std::size_t numa_nodes = get_num_numa_nodes(topo, vm);
    std::pair<std::size_t, std::size_t> pus =
        get_num_numa_pus(topo, numa_nodes, vm);

    std::size_t vector_size = vm["vector_size"].as<std::size_t>();
    std::size_t offset = vm["offset"].as<std::size_t>();
    std::size_t iterations = vm["iterations"].as<std::size_t>();

    std::string num_numa_domains_str = vm["stream-numa-domains"].as<std::string>();

    std::string chunker = vm["chunker"].as<std::string>();

    std::cout
        << "-------------------------------------------------------------\n"
        << "Modified STREAM bechmark based on\nHPX version: "
            << hpx::build_string() << "\n"
        << "-------------------------------------------------------------\n"
        << "This system uses " << sizeof(STREAM_TYPE)
            << " bytes per array element.\n"
        << "-------------------------------------------------------------\n"
        << "Array size = " << vector_size << " (elements), "
           "Offset = " << offset << " (elements)\n"
        << "Memory per array = "
            << sizeof(STREAM_TYPE) * (vector_size / 1024. / 1024.) << " MiB "
        << "(= "
            <<  sizeof(STREAM_TYPE) * (vector_size / 1024. / 1024. / 1024.)
            << " GiB).\n"
        << "Each kernel will be executed " << iterations << " times.\n"
        << " The *best* time for each kernel (excluding the first iteration)\n"
        << " will be used to compute the reported bandwidth.\n"
        << "-------------------------------------------------------------\n"
        << "Number of Threads requested = "
            << numa_nodes * pus.second << "\n"
        << "Chunking policy requested: " << chunker << "\n"
        << "-------------------------------------------------------------\n"
        ;

    using namespace hpx::parallel;

    typedef hpx::threads::executors::local_priority_queue_attached_executor
        executor_type;
    typedef std::vector<executor_type> executors_vector;

    executors_vector execs;
    execs.reserve(numa_nodes);

    // creating our executors ....
    for (std::size_t i = 0; i != numa_nodes; ++i)
    {
        // create executor for this NUMA domain
        execs.emplace_back(i * pus.first, pus.second);
    }

    // allocate data
    typedef hpx::parallel::util::numa_allocator<
            STREAM_TYPE, executors_vector
        > allocator_type;
    allocator_type alloc(execs, retrieve_topology());

    typedef std::vector<STREAM_TYPE, allocator_type> vector_type;
    vector_type a(vector_size, STREAM_TYPE(), alloc);
    vector_type b(vector_size, STREAM_TYPE(), alloc);
    vector_type c(vector_size, STREAM_TYPE(), alloc);

    // perform benchmark
    hpx::lcos::local::latch l(numa_nodes);

    double time_total = mysecond();
    std::vector<hpx::future<std::vector<std::vector<double> > > > workers;
    workers.reserve(numa_nodes);

    std::size_t part_size = vector_size / numa_nodes;

    for (std::size_t i = 0; i != numa_nodes; ++i)
    {
        if(chunker == "dynamic")
        {
            auto policy = par.on(execs[i]).with(dynamic_chunk_size());
            workers.push_back(
                hpx::async(execs[i], &numa_domain_worker<vector_type, decltype(policy)>,
                    i, policy, boost::ref(l),
                    part_size, part_size*i, iterations,
                    boost::ref(a), boost::ref(b), boost::ref(c))
            );
        }
        else if(chunker == "auto")
        {
            auto policy = par.on(execs[i]).with(auto_chunk_size());
            workers.push_back(
                hpx::async(execs[i], &numa_domain_worker<vector_type, decltype(policy)>,
                    i, policy, boost::ref(l),
                    part_size, part_size*i, iterations,
                    boost::ref(a), boost::ref(b), boost::ref(c))
            );
        }
        else if(chunker == "guided")
        {
            auto policy = par.on(execs[i]).with(guided_chunk_size());
            workers.push_back(
                hpx::async(execs[i], &numa_domain_worker<vector_type, decltype(policy)>,
                    i, policy, boost::ref(l),
                    part_size, part_size*i, iterations,
                    boost::ref(a), boost::ref(b), boost::ref(c))
            );
        }
        else
        {
            // default
            auto policy = par.on(execs[i]);
            workers.push_back(
                hpx::async(execs[i], &numa_domain_worker<vector_type, decltype(policy)>,
                    i, policy, boost::ref(l),
                    part_size, part_size*i, iterations,
                    boost::ref(a), boost::ref(b), boost::ref(c))
            );
        }
    }

    std::vector<std::vector<std::vector<double> > >
        timings_all = hpx::util::unwrapped(workers);
    time_total = mysecond() - time_total;

    /* --- SUMMARY --- */
    const char *label[4] = {
        "Copy:      ",
        "Scale:     ",
        "Add:       ",
        "Triad:     "
    };

    const double bytes[4] = {
        2 * sizeof(STREAM_TYPE) * static_cast<double>(vector_size),
        2 * sizeof(STREAM_TYPE) * static_cast<double>(vector_size),
        3 * sizeof(STREAM_TYPE) * static_cast<double>(vector_size),
        3 * sizeof(STREAM_TYPE) * static_cast<double>(vector_size)
    };
    std::vector<std::vector<double> > timing(4, std::vector<double>(iterations, 0.0));

    for(auto const & times : timings_all)
    {
        for(std::size_t iteration = 0; iteration != iterations; ++iteration)
        {
            timing[0][iteration] += times[0][iteration];
            timing[1][iteration] += times[1][iteration];
            timing[2][iteration] += times[2][iteration];
            timing[3][iteration] += times[3][iteration];
        }
    }
    for(std::size_t iteration = 0; iteration != iterations; ++iteration)
    {
        timing[0][iteration] /= numa_nodes;
        timing[1][iteration] /= numa_nodes;
        timing[2][iteration] /= numa_nodes;
        timing[3][iteration] /= numa_nodes;
    }
    // Note: skip first iteration
    std::vector<double> avgtime(4, 0.0);
    std::vector<double> mintime(4, (std::numeric_limits<double>::max)());
    std::vector<double> maxtime(4, 0.0);
    for(std::size_t iteration = 1; iteration != iterations; ++iteration)
    {
        for (std::size_t j=0; j<4; j++)
        {
            avgtime[j] = avgtime[j] + timing[j][iteration];
            mintime[j] = (std::min)(mintime[j], timing[j][iteration]);
            maxtime[j] = (std::max)(maxtime[j], timing[j][iteration]);
        }
    }

    printf("Function    Best Rate MB/s  Avg time     Min time     Max time\n");
    for (std::size_t j=0; j<4; j++) {
        avgtime[j] = avgtime[j]/(double)(iterations-1);

        printf("%s%12.1f  %11.6f  %11.6f  %11.6f\n", label[j],
           1.0E-06 * bytes[j]/mintime[j],
           avgtime[j],
           mintime[j],
           maxtime[j]);
    }

    std::cout
        << "\nTotal time: " << time_total
        << " (per iteration: " << time_total/iterations << ")\n";

    std::cout
        << "-------------------------------------------------------------\n"
        ;

    // Check Results ...
    check_results(iterations, a, b, c);

    std::cout
        << "-------------------------------------------------------------\n"
        ;

    return hpx::finalize();
}


// Launch with something like:
//
// --stream-numa-domains=2 --stream-threads=6
//
// Don't use --hpx:threads or --hpx:bind, those are computed internally.
//
int main(int argc, char* argv[])
{
    using namespace boost::program_options;

    options_description cmdline("usage: " HPX_APPLICATION_STRING " [options]");

    cmdline.add_options()
        (   "vector_size",
            boost::program_options::value<std::size_t>()->default_value(1024),
            "size of vector (default: 1024)")
        (   "offset",
            boost::program_options::value<std::size_t>()->default_value(0),
            "offset (default: 0)")
        (   "iterations",
            boost::program_options::value<std::size_t>()->default_value(10),
            "number of iterations to repeat each test. (default: 10)")
        (   "stream-threads",
            boost::program_options::value<std::string>()->default_value("all"),
            "number of threads per NUMA domain to use. (default: all)")
        (   "stream-numa-domains",
            boost::program_options::value<std::string>()->default_value("all"),
            "number of NUMA domains to use. (default: all)")
        (   "chunker",
            boost::program_options::value<std::string>()->default_value("default"),
            "Which chunker to use for the parallel algorithms. "
            "possible values: dynamic, auto, guided. (default: default)")
        ;

    // parse command line here to extract the necessary settings for HPX
    parsed_options opts =
        command_line_parser(argc, argv)
            .allow_unregistered()
            .options(cmdline)
            .style(command_line_style::unix_style)
            .run();

    variables_map vm;
    store(opts, vm);

    hpx::threads::topology const& topo = retrieve_topology();
    std::size_t numa_nodes = get_num_numa_nodes(topo, vm);
    std::pair<std::size_t, std::size_t> pus =
        get_num_numa_pus(topo, numa_nodes, vm);
    std::size_t num_cores = topo.get_number_of_numa_node_cores(0);

    std::vector<std::string> cfg;
    cfg.push_back("hpx.numa_sensitive=2");  // no-cross NUMA stealing

    // block all cores of requested number of NUMA-domains
    cfg.push_back(boost::str(
        boost::format("hpx.cores=%d") % (numa_nodes * num_cores)
    ));
    cfg.push_back(boost::str(
        boost::format("hpx.os_threads=%d") % (numa_nodes * pus.second)
    ));

    std::string node_name("numanode");
    if (topo.get_number_of_numa_nodes() == 0)
        node_name = "socket";

    std::string bind_desc("hpx.bind!=");
    for (std::size_t i = 0; i != numa_nodes; ++i)
    {
        if (i != 0)
            bind_desc += ";";

        std::size_t base_thread = i * pus.second;
        bind_desc += boost::str(
            boost::format("thread:%d-%d=%s:%d.core:0-%d.pu:0")
              % base_thread % (base_thread+pus.second-1)  // thread:%d-%d
              % node_name % i                             // %s:%d
              % (pus.second-1)                            // core:0-%d
        );
    }
    cfg.push_back(bind_desc);

    return hpx::init(cmdline, argc, argv, cfg);
}

