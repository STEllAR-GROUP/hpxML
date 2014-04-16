//  Copyright (c) 2011-2014 Bryce Adelstein-Lelbach
//  Copyright (c) 2007-2014 Hartmut Kaiser
//  Copyright (c) 2013-2014 Thomas Heller
//  Copyright (c) 2013-2014 Patricia Grubel
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "htts2.hpp"

#include <omp.h>

template <typename BaseClock = boost::chrono::steady_clock>
struct omp_driver : htts2::driver
{
    omp_driver(int argc, char** argv)
      : htts2::driver(argc, argv)
    {}

    void run()
    {
        omp_set_num_threads(this->osthreads_);

        // Cold run
        kernel();

        // Hot run
        results_type results = kernel();
        print_results(results);
    }

  private:
    struct results_type
    {
        results_type()
          : total_walltime_(0.0)
          , warmup_walltime_(0.0)
        {}
        
        results_type(
            double total_walltime,    // nanoseconds
            double warmup_walltime    // nanoseconds
            )
          : total_walltime_(total_walltime)
          , warmup_walltime_(warmup_walltime)
        {}

        results_type(results_type const&) = default;

        double total_walltime_;
        double warmup_walltime_;
    };

    results_type kernel() 
    {
        ///////////////////////////////////////////////////////////////////////

        results_type results;

        htts2::timer<BaseClock> t;
    
        ///////////////////////////////////////////////////////////////////////
        // Warmup Phase
        #pragma omp parallel
        #pragma omp single
        {
            // One stager per OS-thread.
//            #pragma omp parallel for schedule(static, 1) 
            for (boost::uint64_t n = 0; n < this->osthreads_; ++n)
                #pragma omp task untied
                for (boost::uint64_t m = 0; m < this->tasks_; ++m)
                    #pragma omp task untied
                    htts2::payload<BaseClock>(this->payload_duration_ /* = p */);

            results.warmup_walltime_ = t.elapsed();

            ///////////////////////////////////////////////////////////////////
            // Compute + Cooldown Phase 

            #pragma omp taskwait

            // w_M [nanoseconds]
            results.total_walltime_ = t.elapsed();
        }

        return results;

        ///////////////////////////////////////////////////////////////////////
    }

    void print_results(results_type results) const
    {
        if (this->io_ == htts2::csv_with_headers)
            std::cout
                << "OS-threads (Independent Variable),"
                << "Tasks per OS-thread (Control Variable) [tasks/OS-threads],"
                << "Payload Duration (Control Variable) [nanoseconds],"
                << "Total Walltime [nanoseconds],"
                << "Warmup Walltime [nanoseconds],"
                << "\n";

        std::cout
            << ( boost::format("%lu,%lu,%lu,%.14g,%.14g\n")
               % this->osthreads_ 
               % this->tasks_ 
               % this->payload_duration_ 
               % results.total_walltime_ 
               % results.warmup_walltime_
               )
            ; 
    }
};

int main(int argc, char** argv)
{
    omp_driver<> d(argc, argv);

    d.run();

    return 0;
}

