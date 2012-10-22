// Copyright (c) 2007-2012 Hartmut Kaiser
// Copyright (c)      2012 Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This file has been automatically generated using the Boost.Wave tool.
// Do not edit manually.


namespace hpx
{
    
    template <typename T>
    lcos::future<std::vector<lcos::future<T> > >
    when_all (lcos::future<T> f0)
    {
        std::vector<lcos::future<T> > lazy_values;
        lazy_values.reserve(1);
        lazy_values.push_back(f0);
        typedef std::vector<lcos::future<T> > return_type;
        lcos::local::futures_factory<return_type()> p(
            detail::when_all<T>(boost::move(lazy_values)));
        p.apply();
        return p.get_future();
    }
    template <typename T>
    std::vector<lcos::future<T> >
    wait_all(lcos::future<T> f0)
    {
        return when_all(f0).get();
    }
}
namespace hpx
{
    
    template <typename T>
    lcos::future<std::vector<lcos::future<T> > >
    when_all (lcos::future<T> f0 , lcos::future<T> f1)
    {
        std::vector<lcos::future<T> > lazy_values;
        lazy_values.reserve(2);
        lazy_values.push_back(f0); lazy_values.push_back(f1);
        typedef std::vector<lcos::future<T> > return_type;
        lcos::local::futures_factory<return_type()> p(
            detail::when_all<T>(boost::move(lazy_values)));
        p.apply();
        return p.get_future();
    }
    template <typename T>
    std::vector<lcos::future<T> >
    wait_all(lcos::future<T> f0 , lcos::future<T> f1)
    {
        return when_all(f0 , f1).get();
    }
}
namespace hpx
{
    
    template <typename T>
    lcos::future<std::vector<lcos::future<T> > >
    when_all (lcos::future<T> f0 , lcos::future<T> f1 , lcos::future<T> f2)
    {
        std::vector<lcos::future<T> > lazy_values;
        lazy_values.reserve(3);
        lazy_values.push_back(f0); lazy_values.push_back(f1); lazy_values.push_back(f2);
        typedef std::vector<lcos::future<T> > return_type;
        lcos::local::futures_factory<return_type()> p(
            detail::when_all<T>(boost::move(lazy_values)));
        p.apply();
        return p.get_future();
    }
    template <typename T>
    std::vector<lcos::future<T> >
    wait_all(lcos::future<T> f0 , lcos::future<T> f1 , lcos::future<T> f2)
    {
        return when_all(f0 , f1 , f2).get();
    }
}
namespace hpx
{
    
    template <typename T>
    lcos::future<std::vector<lcos::future<T> > >
    when_all (lcos::future<T> f0 , lcos::future<T> f1 , lcos::future<T> f2 , lcos::future<T> f3)
    {
        std::vector<lcos::future<T> > lazy_values;
        lazy_values.reserve(4);
        lazy_values.push_back(f0); lazy_values.push_back(f1); lazy_values.push_back(f2); lazy_values.push_back(f3);
        typedef std::vector<lcos::future<T> > return_type;
        lcos::local::futures_factory<return_type()> p(
            detail::when_all<T>(boost::move(lazy_values)));
        p.apply();
        return p.get_future();
    }
    template <typename T>
    std::vector<lcos::future<T> >
    wait_all(lcos::future<T> f0 , lcos::future<T> f1 , lcos::future<T> f2 , lcos::future<T> f3)
    {
        return when_all(f0 , f1 , f2 , f3).get();
    }
}
namespace hpx
{
    
    template <typename T>
    lcos::future<std::vector<lcos::future<T> > >
    when_all (lcos::future<T> f0 , lcos::future<T> f1 , lcos::future<T> f2 , lcos::future<T> f3 , lcos::future<T> f4)
    {
        std::vector<lcos::future<T> > lazy_values;
        lazy_values.reserve(5);
        lazy_values.push_back(f0); lazy_values.push_back(f1); lazy_values.push_back(f2); lazy_values.push_back(f3); lazy_values.push_back(f4);
        typedef std::vector<lcos::future<T> > return_type;
        lcos::local::futures_factory<return_type()> p(
            detail::when_all<T>(boost::move(lazy_values)));
        p.apply();
        return p.get_future();
    }
    template <typename T>
    std::vector<lcos::future<T> >
    wait_all(lcos::future<T> f0 , lcos::future<T> f1 , lcos::future<T> f2 , lcos::future<T> f3 , lcos::future<T> f4)
    {
        return when_all(f0 , f1 , f2 , f3 , f4).get();
    }
}
