////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2007 Douglas Gregor
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

template <typename... Elements>
struct tuple {};

int main()
{
   tuple<int, int, int, long, float, tuple<bool> > t;
   return 0;
}

