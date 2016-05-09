
#include <iostream>     
#include <iterator>


#include <hpx/hpx_init.hpp>
#include <hpx/hpx.hpp>
#include <hpx/include/parallel_algorithm.hpp>
#include <hpx/include/parallel_executors.hpp>
#include <hpx/include/parallel_transform.hpp>
#include <hpx/include/parallel_executor_parameters.hpp>

#include <initializer_list>
#include <x86intrin.h>

///ii



template<typename T>
struct prefetcher_context
{
	using value_type = T;
    
	std::size_t i_begin; 
	std::size_t i_end;
	std::size_t prefetcher_distance_factor;   
	std::vector< T * > m;
    
	explicit prefetcher_context (std::size_t idx_begin, std::size_t idx_end, std::size_t p_factor, std::initializer_list< T * > &&l) 
	: i_begin(idx_begin), i_end((idx_end * sizeof(T)) / 64), prefetcher_distance_factor(p_factor), m(l) {}

	explicit prefetcher_context (std::size_t idx_begin, std::size_t idx_end, std::initializer_list< T * > &&l) 
	: i_begin(idx_begin), i_end((idx_end * sizeof(T)) / 64), prefetcher_distance_factor(1), m(l) {}

	//our_iterator<value_type> begin() {return our_iterator<value_type>(i_begin, m, prefetcher_distance_factor); }
	//our_iterator<value_type> end() {return our_iterator<value_type>(i_end, m, prefetcher_distance_factor);}		
};


template<typename T>
class our_iterator : public std::iterator<std::input_iterator_tag, T>
{

	int chunk_size_count;	
	int cache_size;
	int prefetcher_distance_factor;
	int idx;
	std::vector< T * > M_;
	
public:

	explicit our_iterator(std::size_t count, std::vector< T * > const & A, std::size_t factor) 
	: chunk_size_count(count), cache_size(sizeof(T)), prefetcher_distance_factor(factor), M_(A) 
	{
        	idx = chunk_size_count * cache_size * prefetcher_distance_factor;
        }

	our_iterator& operator++() {++chunk_size_count; return *this;}
	our_iterator operator++(int) {our_iterator copy(*this); operator++(); return copy;}

	bool operator==(const our_iterator& other) {return chunk_size_count==other.chunk_size_count;}
	bool operator!=(const our_iterator& other) {return chunk_size_count!=other.chunk_size_count;}

	int operator*() 
	{
		idx = chunk_size_count * cache_size * prefetcher_distance_factor;
        	for (auto& x: M_) 
            		_mm_prefetch(((char*)(&x[idx])), _MM_HINT_T0);
		return idx;
	}

};

/*
template<typename Prefetcher_context, std::size_t it_begin, std::size_t it_end >
struct unroll_range
{
	using value_type = typename Prefetcher_context::value_type;
	std::size_t prefetcher_distance_factor;
	Prefetcher_context A_; 
	unroll_range(std::size_t factor, Prefetcher_context const & A) : prefetcher_distance_factor(factor), A_(A) {} 
    
	our_iterator<value_type> begin() {return our_iterator<value_type>(it_begin, A_,prefetcher_distance_factor); }
	our_iterator<value_type> end() {return our_iterator<value_type>(it_end, A_,prefetcher_distance_factor);}

};
*/
////////////////////////////////////////////////////////////////////////

int hpx_main(int argc, char* argv[])
{

	std::vector<double> a(64,1.2);
	std::vector<double> b(64,3.2);
	std::vector<double> c(64,1.5);
        std::size_t prefetcher_distance_factor=1;


	auto ctx = prefetcher_context(0,64,{a.data(),b.data(),c.data()});
/*
	constexpr std::size_t cache_size = sizeof(double);
	constexpr long unsigned int first = 0;
	constexpr long unsigned int last =ceil((double) 64 / cache_size); 
        unroll_range<prefetcher_context<double>, first, last  > my_range(prefetcher_distance_factor, A);
       
        std::for_each( my_range.begin(), my_range.end(), [&](int i)
	{ 
		std::cout<<"address is "<<i<<std::endl;
		std::size_t from = i;
		std::size_t up = i + prefetcher_distance_factor * cache_size;
		for(int j=from ; j<std::min(up,a.size()); ++j)
		{
			a[j]=b[j]+c[j] * 2.5;
			std::cout<<"a["<<j<<"] = "<<a[j]<<std::endl;

		}

	});

*/

	return hpx::finalize();

}

int main(int argc, char* argv[])
{
	return hpx::init(argc, argv);
}

