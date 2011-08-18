////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include <boost/cstdint.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>

boost::uint64_t jacobsthal(boost::uint64_t n)
{
    if (0 == n)
        return 0;
    else if (1 == n)
        return 1;
    else
        return jacobsthal(n - 1) + 2 * jacobsthal(n - 2); 
}

int main(int argc, char** argv)
{
    try
    {
        if (2 != argc)
            throw std::exception();

        const boost::uint64_t n = boost::lexical_cast<boost::uint64_t>(argv[1]);

        std::cout
            << ( boost::format("jacobsthal(%1%) == %2%\n")
               % n % jacobsthal(n));
    }

    catch (std::exception&)
    {
        std::cerr << (boost::format("Usage: %1% N\n") % argv[0]);
        return 1;
    }  
}

