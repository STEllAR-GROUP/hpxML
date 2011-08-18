////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include <boost/cstdint.hpp>
#include <boost/bigint.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>

#include <hpx/util/high_resolution_timer.hpp>

using boost::bigint;

using hpx::util::high_resolution_timer;

bigint fibonacci(boost::uint64_t n)
{
    if (2 > n)
        return n;
    else
        return fibonacci(n - 1) + fibonacci(n - 2);
}

int main(int argc, char** argv)
{
    try
    {
        if (2 != argc)
            throw std::exception();

        const boost::uint64_t n = boost::lexical_cast<boost::uint64_t>(argv[1]);

        high_resolution_timer t;

        bigint r = fibonacci(n); 

        double elapsed = t.elapsed();

        std::cout
            << ( boost::format("fibonacci(%1%) == %2%\n"
                               "elapsed time == %3%\n")
               % n % r % elapsed);
    }

    catch (std::exception&)
    {
        std::cerr << (boost::format("Usage: %1% N\n") % argv[0]);
        return 1;
    }  
}

