////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(HPX_BABB0428_2085_4DCF_851A_8819D186835E)
#define HPX_BABB0428_2085_4DCF_851A_8819D186835E

#if defined(_GLIBCXX_HAVE_TLS)
#  define HPX_NATIVE_TLS __thread
#elif defined(BOOST_WINDOWS)
#  define HPX_NATIVE_TLS __declspec(thread)
#endif

#include <hpx/config.hpp>

// native implementation
#if defined(HPX_NATIVE_TLS)

#include <boost/assert.hpp>

namespace hpx { namespace util
{

template <typename T, typename Tag>
struct HPX_EXPORT thread_specific_ptr
{
    typedef T element_type;

    T* get() const
    {
        return ptr_;
    }

    T* operator->() const
    {
        return ptr_;
    }

    T& operator*() const
    {
        BOOST_ASSERT(0 != ptr_);
        return *ptr_;
    }

    void reset(
        T* new_value = 0
        )
    {
        if (0 != ptr_)
            delete ptr_;

        ptr_ = new_value; 
    }

  private:
    static HPX_NATIVE_TLS T* ptr_;
};

template <typename T, typename Tag>
HPX_NATIVE_TLS T* thread_specific_ptr<T, Tag>::ptr_;

}}

// fallback implementation
#else

#include <boost/thread/tss.hpp>

namespace hpx { namespace util
{

template <typename T, typename Tag>
struct HPX_EXPORT thread_specific_ptr
{
    typedef typename boost::thread_specific_ptr<T>::element_type element_type;

    T* get() const
    {
        return ptr_.get();
    }

    T* operator->() const
    {
        return ptr_.operator->();
    }

    T& operator*() const
    {
        return ptr_.operator*();
    }

    void reset(
        T* new_value = 0
        )
    {
        ptr_.reset(new_value);
    }

  private:
    static boost::thread_specific_ptr<T> ptr_;
};

template <typename T, typename Tag>
boost::thread_specific_ptr<T> thread_specific_ptr<T, Tag>::ptr_;

}}

#endif

#endif // HPX_BABB0428_2085_4DCF_851A_8819D186835E

