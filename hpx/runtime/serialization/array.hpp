//  (C) Copyright 2005 Matthias Troyer and Dave Abrahams
//  Copyright (c) 2015 Anton Bikineev
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef HPX_SERIALIZATION_ARRAY_HPP
#define HPX_SERIALIZATION_ARRAY_HPP

#include <cstddef>

#include <hpx/traits/is_bitwise_serializable.hpp>

#include <boost/array.hpp>
#ifndef BOOST_NO_CXX11_HDR_ARRAY
#include <array>
#endif

namespace hpx { namespace serialization
{
    template <class T>
    class array
    {
    public:
        typedef T value_type;

        array(value_type* t, std::size_t s):
            m_t(t),
            m_element_count(s)
        {}

        value_type* address() const
        {
            return m_t;
        }

        std::size_t count() const
        {
            return m_element_count;
        }

        template <class Archive>
        void serialize_optimized(Archive& ar, unsigned int v, boost::mpl::false_)
        {
#ifdef BOOST_BIG_ENDIAN
            if (ar.endian_little())
            {
                for (std::size_t i = 0; i != m_element_count; ++i)
                    ar & m_t[i];
            }
#else
            if (ar.endian_big())
            {
                for (std::size_t i = 0; i != m_element_count; ++i)
                    ar & m_t[i];
            }
#endif
            else
            {
                // this behaviour has been kept from old version with portable boost archives
                serialize_optimized(ar, v, boost::mpl::true_());
            }
        }

        void serialize_optimized(output_archive& ar, unsigned int, boost::mpl::true_)
        {
            // try using chunking
            ar.save_binary_chunk(m_t, m_element_count * sizeof(T));
        }

        void serialize_optimized(input_archive& ar, unsigned int, boost::mpl::true_)
        {
            // try using chunking
            ar.load_binary_chunk(m_t, m_element_count * sizeof(T));
        }

        template <class Archive>
        void serialize(Archive& ar, unsigned int v)
        {
            typedef typename hpx::traits::is_bitwise_serializable<T>::type
                use_optimized;

            if (ar.disable_array_optimization())
                serialize_optimized(ar, v, boost::mpl::false_());
            else
                serialize_optimized(ar, v, use_optimized());
        }

    private:
        value_type* m_t;
        std::size_t m_element_count;
    };

    // make_array function
    template <class T> BOOST_FORCEINLINE
    array<T> make_array(T* begin, std::size_t size)
    {
        return array<T>(begin, size);
    }

    // implement serialization for arrays
    template <class Archive, class T, std::size_t N>
    void serialize(Archive& ar, T (&a)[N], const unsigned int /* version */)
    {
        ar & hpx::serialization::make_array(a, N);
    }

    // implement serialization for boost::array
    template <class Archive, class T, std::size_t N>
    void serialize(Archive& ar, boost::array<T,N>& a, const unsigned int /* version */)
    {
        ar & hpx::serialization::make_array(a.begin(), a.size());
    }

#ifndef BOOST_NO_CXX11_HDR_ARRAY
  // implement serialization for std::array
    template <class Archive, class T, std::size_t N>
    void serialize(Archive& ar, std::array<T,N>& a, const unsigned int /* version */)
    {
        ar & hpx::serialization::make_array(a.begin(), a.size());
    }
#endif

    // allow our array to be serialized as prvalue
    // compiler should support good ADL implementation
    // but it is rather for all hpx serialization library
    template <typename T> BOOST_FORCEINLINE
    output_archive & operator<<(output_archive & ar, array<T> t)
    {
        ar.invoke(t);
        return ar;
    }

    template <typename T> BOOST_FORCEINLINE
    input_archive & operator>>(input_archive & ar, array<T> t)
    {
        ar.invoke(t);
        return ar;
    }

    template <typename T> BOOST_FORCEINLINE
    output_archive & operator&(output_archive & ar, array<T> t) //-V524
    {
        ar.invoke(t);
        return ar;
    }

    template <typename T> BOOST_FORCEINLINE
    input_archive & operator&(input_archive & ar, array<T> t) //-V524
    {
        ar.invoke(t);
        return ar;
    }

    // serialize plain arrays:
    template <typename T, std::size_t N> BOOST_FORCEINLINE
    output_archive & operator<<(output_archive & ar, T (&t)[N])
    {
        ar.invoke(make_array(t, N));
        return ar;
    }

    template <typename T, std::size_t N> BOOST_FORCEINLINE
    input_archive & operator>>(input_archive & ar, T (&t)[N])
    {
        ar.invoke(make_array(t, N));
        return ar;
    }

    template <typename T, std::size_t N> BOOST_FORCEINLINE
    output_archive & operator&(output_archive & ar, T (&t)[N]) //-V524
    {
        ar.invoke(make_array(t, N));
        return ar;
    }

    template <typename T, std::size_t N> BOOST_FORCEINLINE
    input_archive & operator&(input_archive & ar, T (&t)[N]) //-V524
    {
        ar.invoke(make_array(t, N));
        return ar;
    }
}}

#endif // HPX_SERIALIZATION_ARRAY_HPP
