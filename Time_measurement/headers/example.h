    using namespace hpx::parallel;

    double time_now;
    double N_rep=10;
    double mean_time=0;
    double elasped_time;
    for(int j(0);j<N_rep+1;j++){
        time_now=mysecond();
        for_each(execution::par.with(dynamic_chunk_size(vector_size*chunk_candidate)), range.begin(), range.end(), f);
        elapsed_time= mysecond() - time_now;
        if(j!=0){
            mean_time+=elapsed_time;
        }
    }
    std::cout<<mean_time/N_rep;






