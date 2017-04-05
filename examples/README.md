
# Expected Results

These examples are provide to show how you can implement hpxml for loops to acheive better parallel perfromance. 

In each example, there are three different loops:


	hpx::parallel::for_each(hpx::parallel::par, time_range.begin(), time_range.end(), f);

	hpx::parallel::for_each(hpx::parallel::par.with(hpx::parallel::adaptive_chunk_size()), time_range.begin(), time_range.end(), f);	

	hpx::parallel::for_each(hpx::parallel::execution::make_prefetcher_policy(policy, prefetching_distance_factor, ...), time_range.begin(), time_range.end(), f);
	...

After compiling using Clang and LoopConvert (our ClangTool), the above loops will automatically changed to :

	hpx::parallel::for_each(hpx::parallel::par, time_range.begin(), time_range.end(), f);

	hpx::parallel::for_each(hpx::parallel::par.with(hpx::parallel::chunk_size_determination(EXTRACTED_STATICE_DYNAMIC_FEATURES)), time_range.begin(), time_range.end(), f);	

	hpx::parallel::for_each(hpx::parallel::execution::make_prefetcher_policy(policy, hpx::parallel::prefetching_distance_determination(EXTRACTED_STATICE_DYNAMIC_FEATURES), ...), time_range.begin(), time_range.end(), f);
	...

# Instructions

Follow below instructions to compile the provided examples:

	mkdir build & cd build
	cmake -DCMAKE_CXX_COMPILER=/path/to/clang++ -DHPX_DIR=/path/to/hpx/build/lib/cmake/hpx -DCMAKE_BUILD_TYPE=Release -std=c++11 ..
	/path/to/loop-convert ../main.cpp -- -std=c++11 -I/pat/to/hpx -I/path/to/hpx/build -I/path/to/boost
	make -j


Now, run the executable files and enjoy the results ;)