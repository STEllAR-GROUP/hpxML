//  (C) Copyright 2005 Matthias Troyer and Dave Abrahams
//  Copyright (c) 2015 Anton Bikineev
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef HPX_SERIALIZATION_ARRAY_HPP
#define HPX_SERIALIZATION_ARRAY_HPP

#include <cstddef>

#include <hpx/serialization/serialize.hpp>
#include <hpx/traits/is_bitwise_serializable.hpp>

namespace hpx { namespace serialization {

  template <class T>
  class array
  {
  public:
    typedef T value_type;

    array(value_type* t, std::size_t s):
      m_t(t),
      m_element_count(s)
    {}

    array(const array& rhs):
      m_t(rhs.m_t),
      m_element_count(rhs.m_element_count)
    {}

    array& operator=(const array& rhs)
    {
      if (this == &rhs) return *this;

      m_t = rhs.m_t;
      m_element_count = rhs.m_element_count;
    }

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
        ar.save_binary(m_t, m_element_count * sizeof(T));
    }

    void serialize_optimized(input_archive& ar, unsigned int, boost::mpl::true_)
    {
        ar.load_binary(m_t, m_element_count * sizeof(T));
    }

    template <class Archive>
    void serialize(Archive& ar, unsigned int v)
    {
      typedef typename hpx::traits::is_bitwise_serializable<T>::type
        use_optimized;

      if (ar.disable_array_optimization()) //TODO: move to another layer
        serialize_optimized(ar, v, boost::mpl::false_());
      else
        serialize_optimized(ar, v, use_optimized());
    }

  private:
    value_type* m_t;
    std::size_t m_element_count;
  };

  template <>
  template <class Archive>
  void array<float>::serialize(Archive& ar, unsigned int v)
  {
    serialize_optimized(ar, v, boost::mpl::true_());
  }

  template <>
  template <class Archive>
  void array<double>::serialize(Archive& ar, unsigned int v)
  {
    serialize_optimized(ar, v, boost::mpl::true_());
  }

  template <>
  template <class Archive>
  void array<char>::serialize(Archive& ar, unsigned int v)
  {
    serialize_optimized(ar, v, boost::mpl::true_());
  }

  template <>
  template <class Archive>
  void array<signed char>::serialize(Archive& ar, unsigned int v)
  {
    serialize_optimized(ar, v, boost::mpl::true_());
  }

  template <>
  template <class Archive>
  void array<unsigned char>::serialize(Archive& ar, unsigned int v)
  {
    serialize_optimized(ar, v, boost::mpl::true_());
  }

  template <>
  template <class Archive>
  void array<bool>::serialize(Archive& ar, unsigned int v)
  {
    serialize_optimized(ar, v, boost::mpl::true_());
  }

  template <class T> BOOST_FORCEINLINE
  array<T> make_array(T* begin, std::size_t size)
  {
    return array<T>(begin, size);
  }

}}

#endif // HPX_SERIALIZATION_ARRAY_HPP
