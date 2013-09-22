// Copyright (c) 2007-2013 Hartmut Kaiser
// Copyright (c) 2012-2013 Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This file has been automatically generated using the Boost.Wave tool.
// Do not edit manually.


namespace hpx
{
    
    template <typename R0>
    lcos::future<HPX_STD_TUPLE<lcos::future<R0> > >
    when_all(lcos::future<R0> f0,
        error_code& ec = throws)
    {
        typedef HPX_STD_TUPLE<lcos::future<R0> >
            result_type;
        return when_n(1, f0, ec);
    }
    template <typename R0>
    HPX_STD_TUPLE<lcos::future<R0> >
    wait_all(lcos::future<R0> f0,
        error_code& ec = throws)
    {
        typedef HPX_STD_TUPLE<lcos::future<R0> >
            result_type;
        lcos::future<result_type> f = when_all(
            f0, ec);
        if (!f.valid()) {
            HPX_THROWS_IF(ec, uninitialized_value, "lcos::wait_all",
                "lcos::when_all didn't return a valid future");
            return result_type();
        }
        return f.get(ec);
    }
}
namespace hpx
{
    
    template <typename R0 , typename R1>
    lcos::future<HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> > >
    when_all(lcos::future<R0> f0 , lcos::future<R1> f1,
        error_code& ec = throws)
    {
        typedef HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> >
            result_type;
        return when_n(2, f0 , f1, ec);
    }
    template <typename R0 , typename R1>
    HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> >
    wait_all(lcos::future<R0> f0 , lcos::future<R1> f1,
        error_code& ec = throws)
    {
        typedef HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> >
            result_type;
        lcos::future<result_type> f = when_all(
            f0 , f1, ec);
        if (!f.valid()) {
            HPX_THROWS_IF(ec, uninitialized_value, "lcos::wait_all",
                "lcos::when_all didn't return a valid future");
            return result_type();
        }
        return f.get(ec);
    }
}
namespace hpx
{
    
    template <typename R0 , typename R1 , typename R2>
    lcos::future<HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> > >
    when_all(lcos::future<R0> f0 , lcos::future<R1> f1 , lcos::future<R2> f2,
        error_code& ec = throws)
    {
        typedef HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> >
            result_type;
        return when_n(3, f0 , f1 , f2, ec);
    }
    template <typename R0 , typename R1 , typename R2>
    HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> >
    wait_all(lcos::future<R0> f0 , lcos::future<R1> f1 , lcos::future<R2> f2,
        error_code& ec = throws)
    {
        typedef HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> >
            result_type;
        lcos::future<result_type> f = when_all(
            f0 , f1 , f2, ec);
        if (!f.valid()) {
            HPX_THROWS_IF(ec, uninitialized_value, "lcos::wait_all",
                "lcos::when_all didn't return a valid future");
            return result_type();
        }
        return f.get(ec);
    }
}
namespace hpx
{
    
    template <typename R0 , typename R1 , typename R2 , typename R3>
    lcos::future<HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> , lcos::future<R3> > >
    when_all(lcos::future<R0> f0 , lcos::future<R1> f1 , lcos::future<R2> f2 , lcos::future<R3> f3,
        error_code& ec = throws)
    {
        typedef HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> , lcos::future<R3> >
            result_type;
        return when_n(4, f0 , f1 , f2 , f3, ec);
    }
    template <typename R0 , typename R1 , typename R2 , typename R3>
    HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> , lcos::future<R3> >
    wait_all(lcos::future<R0> f0 , lcos::future<R1> f1 , lcos::future<R2> f2 , lcos::future<R3> f3,
        error_code& ec = throws)
    {
        typedef HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> , lcos::future<R3> >
            result_type;
        lcos::future<result_type> f = when_all(
            f0 , f1 , f2 , f3, ec);
        if (!f.valid()) {
            HPX_THROWS_IF(ec, uninitialized_value, "lcos::wait_all",
                "lcos::when_all didn't return a valid future");
            return result_type();
        }
        return f.get(ec);
    }
}
namespace hpx
{
    
    template <typename R0 , typename R1 , typename R2 , typename R3 , typename R4>
    lcos::future<HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> , lcos::future<R3> , lcos::future<R4> > >
    when_all(lcos::future<R0> f0 , lcos::future<R1> f1 , lcos::future<R2> f2 , lcos::future<R3> f3 , lcos::future<R4> f4,
        error_code& ec = throws)
    {
        typedef HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> , lcos::future<R3> , lcos::future<R4> >
            result_type;
        return when_n(5, f0 , f1 , f2 , f3 , f4, ec);
    }
    template <typename R0 , typename R1 , typename R2 , typename R3 , typename R4>
    HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> , lcos::future<R3> , lcos::future<R4> >
    wait_all(lcos::future<R0> f0 , lcos::future<R1> f1 , lcos::future<R2> f2 , lcos::future<R3> f3 , lcos::future<R4> f4,
        error_code& ec = throws)
    {
        typedef HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> , lcos::future<R3> , lcos::future<R4> >
            result_type;
        lcos::future<result_type> f = when_all(
            f0 , f1 , f2 , f3 , f4, ec);
        if (!f.valid()) {
            HPX_THROWS_IF(ec, uninitialized_value, "lcos::wait_all",
                "lcos::when_all didn't return a valid future");
            return result_type();
        }
        return f.get(ec);
    }
}
namespace hpx
{
    
    template <typename R0 , typename R1 , typename R2 , typename R3 , typename R4 , typename R5>
    lcos::future<HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> , lcos::future<R3> , lcos::future<R4> , lcos::future<R5> > >
    when_all(lcos::future<R0> f0 , lcos::future<R1> f1 , lcos::future<R2> f2 , lcos::future<R3> f3 , lcos::future<R4> f4 , lcos::future<R5> f5,
        error_code& ec = throws)
    {
        typedef HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> , lcos::future<R3> , lcos::future<R4> , lcos::future<R5> >
            result_type;
        return when_n(6, f0 , f1 , f2 , f3 , f4 , f5, ec);
    }
    template <typename R0 , typename R1 , typename R2 , typename R3 , typename R4 , typename R5>
    HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> , lcos::future<R3> , lcos::future<R4> , lcos::future<R5> >
    wait_all(lcos::future<R0> f0 , lcos::future<R1> f1 , lcos::future<R2> f2 , lcos::future<R3> f3 , lcos::future<R4> f4 , lcos::future<R5> f5,
        error_code& ec = throws)
    {
        typedef HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> , lcos::future<R3> , lcos::future<R4> , lcos::future<R5> >
            result_type;
        lcos::future<result_type> f = when_all(
            f0 , f1 , f2 , f3 , f4 , f5, ec);
        if (!f.valid()) {
            HPX_THROWS_IF(ec, uninitialized_value, "lcos::wait_all",
                "lcos::when_all didn't return a valid future");
            return result_type();
        }
        return f.get(ec);
    }
}
namespace hpx
{
    
    template <typename R0 , typename R1 , typename R2 , typename R3 , typename R4 , typename R5 , typename R6>
    lcos::future<HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> , lcos::future<R3> , lcos::future<R4> , lcos::future<R5> , lcos::future<R6> > >
    when_all(lcos::future<R0> f0 , lcos::future<R1> f1 , lcos::future<R2> f2 , lcos::future<R3> f3 , lcos::future<R4> f4 , lcos::future<R5> f5 , lcos::future<R6> f6,
        error_code& ec = throws)
    {
        typedef HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> , lcos::future<R3> , lcos::future<R4> , lcos::future<R5> , lcos::future<R6> >
            result_type;
        return when_n(7, f0 , f1 , f2 , f3 , f4 , f5 , f6, ec);
    }
    template <typename R0 , typename R1 , typename R2 , typename R3 , typename R4 , typename R5 , typename R6>
    HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> , lcos::future<R3> , lcos::future<R4> , lcos::future<R5> , lcos::future<R6> >
    wait_all(lcos::future<R0> f0 , lcos::future<R1> f1 , lcos::future<R2> f2 , lcos::future<R3> f3 , lcos::future<R4> f4 , lcos::future<R5> f5 , lcos::future<R6> f6,
        error_code& ec = throws)
    {
        typedef HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> , lcos::future<R3> , lcos::future<R4> , lcos::future<R5> , lcos::future<R6> >
            result_type;
        lcos::future<result_type> f = when_all(
            f0 , f1 , f2 , f3 , f4 , f5 , f6, ec);
        if (!f.valid()) {
            HPX_THROWS_IF(ec, uninitialized_value, "lcos::wait_all",
                "lcos::when_all didn't return a valid future");
            return result_type();
        }
        return f.get(ec);
    }
}
namespace hpx
{
    
    template <typename R0 , typename R1 , typename R2 , typename R3 , typename R4 , typename R5 , typename R6 , typename R7>
    lcos::future<HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> , lcos::future<R3> , lcos::future<R4> , lcos::future<R5> , lcos::future<R6> , lcos::future<R7> > >
    when_all(lcos::future<R0> f0 , lcos::future<R1> f1 , lcos::future<R2> f2 , lcos::future<R3> f3 , lcos::future<R4> f4 , lcos::future<R5> f5 , lcos::future<R6> f6 , lcos::future<R7> f7,
        error_code& ec = throws)
    {
        typedef HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> , lcos::future<R3> , lcos::future<R4> , lcos::future<R5> , lcos::future<R6> , lcos::future<R7> >
            result_type;
        return when_n(8, f0 , f1 , f2 , f3 , f4 , f5 , f6 , f7, ec);
    }
    template <typename R0 , typename R1 , typename R2 , typename R3 , typename R4 , typename R5 , typename R6 , typename R7>
    HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> , lcos::future<R3> , lcos::future<R4> , lcos::future<R5> , lcos::future<R6> , lcos::future<R7> >
    wait_all(lcos::future<R0> f0 , lcos::future<R1> f1 , lcos::future<R2> f2 , lcos::future<R3> f3 , lcos::future<R4> f4 , lcos::future<R5> f5 , lcos::future<R6> f6 , lcos::future<R7> f7,
        error_code& ec = throws)
    {
        typedef HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> , lcos::future<R3> , lcos::future<R4> , lcos::future<R5> , lcos::future<R6> , lcos::future<R7> >
            result_type;
        lcos::future<result_type> f = when_all(
            f0 , f1 , f2 , f3 , f4 , f5 , f6 , f7, ec);
        if (!f.valid()) {
            HPX_THROWS_IF(ec, uninitialized_value, "lcos::wait_all",
                "lcos::when_all didn't return a valid future");
            return result_type();
        }
        return f.get(ec);
    }
}
namespace hpx
{
    
    template <typename R0 , typename R1 , typename R2 , typename R3 , typename R4 , typename R5 , typename R6 , typename R7 , typename R8>
    lcos::future<HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> , lcos::future<R3> , lcos::future<R4> , lcos::future<R5> , lcos::future<R6> , lcos::future<R7> , lcos::future<R8> > >
    when_all(lcos::future<R0> f0 , lcos::future<R1> f1 , lcos::future<R2> f2 , lcos::future<R3> f3 , lcos::future<R4> f4 , lcos::future<R5> f5 , lcos::future<R6> f6 , lcos::future<R7> f7 , lcos::future<R8> f8,
        error_code& ec = throws)
    {
        typedef HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> , lcos::future<R3> , lcos::future<R4> , lcos::future<R5> , lcos::future<R6> , lcos::future<R7> , lcos::future<R8> >
            result_type;
        return when_n(9, f0 , f1 , f2 , f3 , f4 , f5 , f6 , f7 , f8, ec);
    }
    template <typename R0 , typename R1 , typename R2 , typename R3 , typename R4 , typename R5 , typename R6 , typename R7 , typename R8>
    HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> , lcos::future<R3> , lcos::future<R4> , lcos::future<R5> , lcos::future<R6> , lcos::future<R7> , lcos::future<R8> >
    wait_all(lcos::future<R0> f0 , lcos::future<R1> f1 , lcos::future<R2> f2 , lcos::future<R3> f3 , lcos::future<R4> f4 , lcos::future<R5> f5 , lcos::future<R6> f6 , lcos::future<R7> f7 , lcos::future<R8> f8,
        error_code& ec = throws)
    {
        typedef HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> , lcos::future<R3> , lcos::future<R4> , lcos::future<R5> , lcos::future<R6> , lcos::future<R7> , lcos::future<R8> >
            result_type;
        lcos::future<result_type> f = when_all(
            f0 , f1 , f2 , f3 , f4 , f5 , f6 , f7 , f8, ec);
        if (!f.valid()) {
            HPX_THROWS_IF(ec, uninitialized_value, "lcos::wait_all",
                "lcos::when_all didn't return a valid future");
            return result_type();
        }
        return f.get(ec);
    }
}
namespace hpx
{
    
    template <typename R0 , typename R1 , typename R2 , typename R3 , typename R4 , typename R5 , typename R6 , typename R7 , typename R8 , typename R9>
    lcos::future<HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> , lcos::future<R3> , lcos::future<R4> , lcos::future<R5> , lcos::future<R6> , lcos::future<R7> , lcos::future<R8> , lcos::future<R9> > >
    when_all(lcos::future<R0> f0 , lcos::future<R1> f1 , lcos::future<R2> f2 , lcos::future<R3> f3 , lcos::future<R4> f4 , lcos::future<R5> f5 , lcos::future<R6> f6 , lcos::future<R7> f7 , lcos::future<R8> f8 , lcos::future<R9> f9,
        error_code& ec = throws)
    {
        typedef HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> , lcos::future<R3> , lcos::future<R4> , lcos::future<R5> , lcos::future<R6> , lcos::future<R7> , lcos::future<R8> , lcos::future<R9> >
            result_type;
        return when_n(10, f0 , f1 , f2 , f3 , f4 , f5 , f6 , f7 , f8 , f9, ec);
    }
    template <typename R0 , typename R1 , typename R2 , typename R3 , typename R4 , typename R5 , typename R6 , typename R7 , typename R8 , typename R9>
    HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> , lcos::future<R3> , lcos::future<R4> , lcos::future<R5> , lcos::future<R6> , lcos::future<R7> , lcos::future<R8> , lcos::future<R9> >
    wait_all(lcos::future<R0> f0 , lcos::future<R1> f1 , lcos::future<R2> f2 , lcos::future<R3> f3 , lcos::future<R4> f4 , lcos::future<R5> f5 , lcos::future<R6> f6 , lcos::future<R7> f7 , lcos::future<R8> f8 , lcos::future<R9> f9,
        error_code& ec = throws)
    {
        typedef HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> , lcos::future<R3> , lcos::future<R4> , lcos::future<R5> , lcos::future<R6> , lcos::future<R7> , lcos::future<R8> , lcos::future<R9> >
            result_type;
        lcos::future<result_type> f = when_all(
            f0 , f1 , f2 , f3 , f4 , f5 , f6 , f7 , f8 , f9, ec);
        if (!f.valid()) {
            HPX_THROWS_IF(ec, uninitialized_value, "lcos::wait_all",
                "lcos::when_all didn't return a valid future");
            return result_type();
        }
        return f.get(ec);
    }
}
namespace hpx
{
    
    template <typename R0 , typename R1 , typename R2 , typename R3 , typename R4 , typename R5 , typename R6 , typename R7 , typename R8 , typename R9 , typename R10>
    lcos::future<HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> , lcos::future<R3> , lcos::future<R4> , lcos::future<R5> , lcos::future<R6> , lcos::future<R7> , lcos::future<R8> , lcos::future<R9> , lcos::future<R10> > >
    when_all(lcos::future<R0> f0 , lcos::future<R1> f1 , lcos::future<R2> f2 , lcos::future<R3> f3 , lcos::future<R4> f4 , lcos::future<R5> f5 , lcos::future<R6> f6 , lcos::future<R7> f7 , lcos::future<R8> f8 , lcos::future<R9> f9 , lcos::future<R10> f10,
        error_code& ec = throws)
    {
        typedef HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> , lcos::future<R3> , lcos::future<R4> , lcos::future<R5> , lcos::future<R6> , lcos::future<R7> , lcos::future<R8> , lcos::future<R9> , lcos::future<R10> >
            result_type;
        return when_n(11, f0 , f1 , f2 , f3 , f4 , f5 , f6 , f7 , f8 , f9 , f10, ec);
    }
    template <typename R0 , typename R1 , typename R2 , typename R3 , typename R4 , typename R5 , typename R6 , typename R7 , typename R8 , typename R9 , typename R10>
    HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> , lcos::future<R3> , lcos::future<R4> , lcos::future<R5> , lcos::future<R6> , lcos::future<R7> , lcos::future<R8> , lcos::future<R9> , lcos::future<R10> >
    wait_all(lcos::future<R0> f0 , lcos::future<R1> f1 , lcos::future<R2> f2 , lcos::future<R3> f3 , lcos::future<R4> f4 , lcos::future<R5> f5 , lcos::future<R6> f6 , lcos::future<R7> f7 , lcos::future<R8> f8 , lcos::future<R9> f9 , lcos::future<R10> f10,
        error_code& ec = throws)
    {
        typedef HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> , lcos::future<R3> , lcos::future<R4> , lcos::future<R5> , lcos::future<R6> , lcos::future<R7> , lcos::future<R8> , lcos::future<R9> , lcos::future<R10> >
            result_type;
        lcos::future<result_type> f = when_all(
            f0 , f1 , f2 , f3 , f4 , f5 , f6 , f7 , f8 , f9 , f10, ec);
        if (!f.valid()) {
            HPX_THROWS_IF(ec, uninitialized_value, "lcos::wait_all",
                "lcos::when_all didn't return a valid future");
            return result_type();
        }
        return f.get(ec);
    }
}
namespace hpx
{
    
    template <typename R0 , typename R1 , typename R2 , typename R3 , typename R4 , typename R5 , typename R6 , typename R7 , typename R8 , typename R9 , typename R10 , typename R11>
    lcos::future<HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> , lcos::future<R3> , lcos::future<R4> , lcos::future<R5> , lcos::future<R6> , lcos::future<R7> , lcos::future<R8> , lcos::future<R9> , lcos::future<R10> , lcos::future<R11> > >
    when_all(lcos::future<R0> f0 , lcos::future<R1> f1 , lcos::future<R2> f2 , lcos::future<R3> f3 , lcos::future<R4> f4 , lcos::future<R5> f5 , lcos::future<R6> f6 , lcos::future<R7> f7 , lcos::future<R8> f8 , lcos::future<R9> f9 , lcos::future<R10> f10 , lcos::future<R11> f11,
        error_code& ec = throws)
    {
        typedef HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> , lcos::future<R3> , lcos::future<R4> , lcos::future<R5> , lcos::future<R6> , lcos::future<R7> , lcos::future<R8> , lcos::future<R9> , lcos::future<R10> , lcos::future<R11> >
            result_type;
        return when_n(12, f0 , f1 , f2 , f3 , f4 , f5 , f6 , f7 , f8 , f9 , f10 , f11, ec);
    }
    template <typename R0 , typename R1 , typename R2 , typename R3 , typename R4 , typename R5 , typename R6 , typename R7 , typename R8 , typename R9 , typename R10 , typename R11>
    HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> , lcos::future<R3> , lcos::future<R4> , lcos::future<R5> , lcos::future<R6> , lcos::future<R7> , lcos::future<R8> , lcos::future<R9> , lcos::future<R10> , lcos::future<R11> >
    wait_all(lcos::future<R0> f0 , lcos::future<R1> f1 , lcos::future<R2> f2 , lcos::future<R3> f3 , lcos::future<R4> f4 , lcos::future<R5> f5 , lcos::future<R6> f6 , lcos::future<R7> f7 , lcos::future<R8> f8 , lcos::future<R9> f9 , lcos::future<R10> f10 , lcos::future<R11> f11,
        error_code& ec = throws)
    {
        typedef HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> , lcos::future<R3> , lcos::future<R4> , lcos::future<R5> , lcos::future<R6> , lcos::future<R7> , lcos::future<R8> , lcos::future<R9> , lcos::future<R10> , lcos::future<R11> >
            result_type;
        lcos::future<result_type> f = when_all(
            f0 , f1 , f2 , f3 , f4 , f5 , f6 , f7 , f8 , f9 , f10 , f11, ec);
        if (!f.valid()) {
            HPX_THROWS_IF(ec, uninitialized_value, "lcos::wait_all",
                "lcos::when_all didn't return a valid future");
            return result_type();
        }
        return f.get(ec);
    }
}
namespace hpx
{
    
    template <typename R0 , typename R1 , typename R2 , typename R3 , typename R4 , typename R5 , typename R6 , typename R7 , typename R8 , typename R9 , typename R10 , typename R11 , typename R12>
    lcos::future<HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> , lcos::future<R3> , lcos::future<R4> , lcos::future<R5> , lcos::future<R6> , lcos::future<R7> , lcos::future<R8> , lcos::future<R9> , lcos::future<R10> , lcos::future<R11> , lcos::future<R12> > >
    when_all(lcos::future<R0> f0 , lcos::future<R1> f1 , lcos::future<R2> f2 , lcos::future<R3> f3 , lcos::future<R4> f4 , lcos::future<R5> f5 , lcos::future<R6> f6 , lcos::future<R7> f7 , lcos::future<R8> f8 , lcos::future<R9> f9 , lcos::future<R10> f10 , lcos::future<R11> f11 , lcos::future<R12> f12,
        error_code& ec = throws)
    {
        typedef HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> , lcos::future<R3> , lcos::future<R4> , lcos::future<R5> , lcos::future<R6> , lcos::future<R7> , lcos::future<R8> , lcos::future<R9> , lcos::future<R10> , lcos::future<R11> , lcos::future<R12> >
            result_type;
        return when_n(13, f0 , f1 , f2 , f3 , f4 , f5 , f6 , f7 , f8 , f9 , f10 , f11 , f12, ec);
    }
    template <typename R0 , typename R1 , typename R2 , typename R3 , typename R4 , typename R5 , typename R6 , typename R7 , typename R8 , typename R9 , typename R10 , typename R11 , typename R12>
    HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> , lcos::future<R3> , lcos::future<R4> , lcos::future<R5> , lcos::future<R6> , lcos::future<R7> , lcos::future<R8> , lcos::future<R9> , lcos::future<R10> , lcos::future<R11> , lcos::future<R12> >
    wait_all(lcos::future<R0> f0 , lcos::future<R1> f1 , lcos::future<R2> f2 , lcos::future<R3> f3 , lcos::future<R4> f4 , lcos::future<R5> f5 , lcos::future<R6> f6 , lcos::future<R7> f7 , lcos::future<R8> f8 , lcos::future<R9> f9 , lcos::future<R10> f10 , lcos::future<R11> f11 , lcos::future<R12> f12,
        error_code& ec = throws)
    {
        typedef HPX_STD_TUPLE<lcos::future<R0> , lcos::future<R1> , lcos::future<R2> , lcos::future<R3> , lcos::future<R4> , lcos::future<R5> , lcos::future<R6> , lcos::future<R7> , lcos::future<R8> , lcos::future<R9> , lcos::future<R10> , lcos::future<R11> , lcos::future<R12> >
            result_type;
        lcos::future<result_type> f = when_all(
            f0 , f1 , f2 , f3 , f4 , f5 , f6 , f7 , f8 , f9 , f10 , f11 , f12, ec);
        if (!f.valid()) {
            HPX_THROWS_IF(ec, uninitialized_value, "lcos::wait_all",
                "lcos::when_all didn't return a valid future");
            return result_type();
        }
        return f.get(ec);
    }
}
