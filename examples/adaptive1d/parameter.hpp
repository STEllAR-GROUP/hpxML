//  Copyright (c) 2009-2011 Matt Anderson
//  Copyrigth (c)      2011 Bryce Lelbach
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_COMPONENTS_PARAMETER_AUG_19_2011_0834AM)
#define HPX_COMPONENTS_PARAMETER_AUG_19_2011_0834AM

#include <vector>

#include <boost/config.hpp>

#if !defined(NUM_EQUATIONS)
    #define NUM_EQUATIONS 9
#endif

#if !defined(MAX_LEVELS)
    #define MAX_LEVELS 20
#endif

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace components { namespace adaptive1d 
{

typedef double double_type;

namespace detail {

struct HPX_COMPONENT_EXPORT parameter
{
    std::size_t loglevel;
    std::size_t nt0;
    std::size_t nx0;
    std::size_t allowedl;
    std::size_t grain_size;
    std::size_t num_neighbors;
    double out_every;

    // Application parameters
    double cfl;
    double disip;
    double Rmin;
    double Rout;
    double tau;
    double lambda;
    double v;
    double amp;
    double x0;
    double id_sigma;

    // Derived parameter
    double h;
};

} // detail

struct HPX_COMPONENT_EXPORT parameter 
{
    typedef detail::parameter value_type;
    typedef value_type& reference;
    typedef value_type const& const_reference;
    typedef value_type* pointer;
    typedef value_type const* const_pointer;

    boost::shared_ptr<value_type> p;

    parameter() : p(new value_type) {}

    pointer operator->()
    { return p.get(); }
    
    const_pointer operator->() const
    { return p.get(); }
    
    reference operator*()
    { return *p; }
    
    const_reference operator*() const
    { return *p; }
};

///////////////////////////////////////////////////////////////////////////////
}}}

#include <examples/adaptive1d/serialize_parameter.hpp>

#endif 

