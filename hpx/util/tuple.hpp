//  Copyright (c) 2011-2013 Thomas Heller
//  Copyright (c) 2011-2013 Hartmut Kaiser
//  Copyright (c) 2013 Agustin Berge
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef HPX_UTIL_TUPLE_HPP
#define HPX_UTIL_TUPLE_HPP

#include <hpx/config.hpp>
#include <hpx/runtime/serialization/serialize.hpp>
#include <hpx/runtime/serialization/serialize_sequence.hpp>
#include <hpx/traits/is_bitwise_serializable.hpp>
#include <hpx/traits/serialize_as_future.hpp>
#include <hpx/util/decay.hpp>
#include <hpx/util/move.hpp>
#include <hpx/util/detail/pack.hpp>
#include <hpx/util/detail/qualify_as.hpp>

#include <boost/array.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_cv.hpp>
#include <boost/type_traits/add_volatile.hpp>
#include <boost/type_traits/is_empty.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/utility/swap.hpp>

#include <cstddef> // for size_t
#include <utility>
#include <algorithm>

#if defined(BOOST_MSVC)
#pragma warning(push)
#pragma warning(disable: 4520) // multiple default constructors specified
#endif

namespace hpx { namespace util
{
    template <typename ...Ts>
    class tuple;

    template <class T>
    struct tuple_size; // undefined

    template <std::size_t I, typename T>
    struct tuple_element; // undefined

    template <std::size_t I, typename Tuple>
    BOOST_CONSTEXPR BOOST_FORCEINLINE
    typename tuple_element<I, Tuple>::type&
    get(Tuple& t) BOOST_NOEXCEPT;

    template <std::size_t I, typename Tuple>
    BOOST_CONSTEXPR BOOST_FORCEINLINE
    typename tuple_element<I, Tuple>::type const&
    get(Tuple const& t) BOOST_NOEXCEPT;

    template <std::size_t I, typename Tuple>
    BOOST_CONSTEXPR BOOST_FORCEINLINE
    typename tuple_element<I, Tuple>::type&&
    get(Tuple&& t) BOOST_NOEXCEPT;

    namespace detail
    {
        ///////////////////////////////////////////////////////////////////////
        template <std::size_t I, typename T, typename Enable = void>
        struct tuple_member //-V690
        {
        public:
            BOOST_CONSTEXPR tuple_member()
              : _value()
            {}

            template <typename U>
            explicit BOOST_CONSTEXPR tuple_member(U&& value)
              : _value(std::forward<U>(value))
            {}

            BOOST_CONSTEXPR tuple_member(tuple_member const& other)
              : _value(other.value())
            {}

            BOOST_CONSTEXPR tuple_member(tuple_member&& other)
              : _value(std::forward<T>(other.value()))
            {}

            T& value() BOOST_NOEXCEPT { return _value; }
            T const& value() const BOOST_NOEXCEPT { return _value; }

        private:
            T _value;
        };

        template <std::size_t I, typename T>
        struct tuple_member<I, T,
            typename boost::enable_if_c<boost::is_empty<T>::value>::type
        > : T
        {
        public:
            BOOST_CONSTEXPR tuple_member()
              : T()
            {}

            template <typename U>
            explicit BOOST_CONSTEXPR tuple_member(U&& value)
              : T(std::forward<U>(value))
            {}

            BOOST_CONSTEXPR tuple_member(tuple_member const& other)
              : T(other.value())
            {}

            BOOST_CONSTEXPR tuple_member(tuple_member&& other)
              : T(std::forward<T>(other.value()))
            {}

            T& value() BOOST_NOEXCEPT { return *this; }
            T const& value() const BOOST_NOEXCEPT { return *this; }
        };

        ///////////////////////////////////////////////////////////////////////
        template <typename Indices, typename TTuple, typename UTuple>
        struct are_tuples_compatible_impl;

        template <std::size_t ...Is, typename ...Ts, typename UTuple>
        struct are_tuples_compatible_impl<
            detail::pack_c<std::size_t, Is...>, tuple<Ts...>, UTuple
        >
        {
            typedef char(&no_type)[1];
            typedef char(&yes_type)[2];

            static no_type call(...);
            static yes_type call(Ts...);

            static bool const value =
                sizeof(
                    call(util::get<Is>(boost::declval<UTuple>())...)
                ) == sizeof(yes_type);

            typedef boost::mpl::bool_<value> type;
            type m_;
        };

        template <typename TTuple, typename UTuple, typename Enable = void>
        struct are_tuples_compatible
          : boost::mpl::false_
        {};

        template <typename ...Ts, typename UTuple>
        struct are_tuples_compatible<
            tuple<Ts...>, UTuple
          , typename boost::enable_if_c<
                tuple_size<
                    typename boost::remove_reference<UTuple>::type
                >::value == detail::pack<Ts...>::size
            >::type
        > : are_tuples_compatible_impl<
                typename detail::make_index_pack<sizeof...(Ts)>::type
              , tuple<Ts...>, UTuple
            >
        {};

        template <typename TTuple, typename UTuple>
        struct are_tuples_compatible_not_same
          : boost::mpl::if_c<
                boost::is_same<
                    typename decay<TTuple>::type, typename decay<UTuple>::type
                >::value
              , boost::mpl::false_
              , are_tuples_compatible<TTuple, UTuple>
            >::type
        {};

        ///////////////////////////////////////////////////////////////////////
        template <typename Is, typename ...Ts>
        struct tuple_impl;

        template <std::size_t ...Is, typename ...Ts>
        struct tuple_impl<detail::pack_c<std::size_t, Is...>, Ts...>
          : tuple_member<Is, Ts>...
        {
            // 20.4.2.1, tuple construction
            BOOST_CONSTEXPR tuple_impl()
              : tuple_member<Is, Ts>()...
            {}

            template <typename ...Us, typename Enable =
                typename boost::enable_if_c<
                    detail::pack<Us...>::size == detail::pack<Ts...>::size
                >::type>
            explicit BOOST_CONSTEXPR tuple_impl(Us&&... vs)
              : tuple_member<Is, Ts>(std::forward<Us>(vs))...
            {}

            BOOST_CONSTEXPR tuple_impl(tuple_impl const& other)
              : tuple_member<Is, Ts>(static_cast<tuple_member<Is, Ts> const&>(other))...
            {}

            BOOST_CONSTEXPR tuple_impl(tuple_impl&& other)
              : tuple_member<Is, Ts>(static_cast<tuple_member<Is, Ts>&&>(other))...
            {}

            template <typename UTuple, typename Enable =
                typename boost::enable_if_c<
                    are_tuples_compatible_not_same<tuple<Ts...>, UTuple&&>::value
                >::type>
            BOOST_CONSTEXPR tuple_impl(UTuple&& other)
              : tuple_member<Is, Ts>(util::get<Is>(std::forward<UTuple>(other)))...
            {}

            tuple_impl& operator=(tuple_impl const& other)
            {
                int const _sequencer[]= {
                    ((this->get<Is>() = other.template get<Is>()), 0)...
                };
                (void)_sequencer;
                return *this;
            }

            tuple_impl& operator=(tuple_impl&& other)
            {
                int const _sequencer[]= {
                    ((this->get<Is>() = other.template get<Is>()), 0)...
                };
                (void)_sequencer;
                return *this;
            }

            template <typename UTuple>
            tuple_impl& operator=(UTuple&& other)
            {
                int const _sequencer[]= {
                    ((this->get<Is>() = util::get<Is>(other)), 0)...
                };
                (void)_sequencer;
                return *this;
            }

            void swap(tuple_impl& other)
            {
                int const _sequencer[] = {
                    ((boost::swap(this->get<Is>(), other.template get<Is>())), 0)...
                };
                (void)_sequencer;
            }

            template <std::size_t I>
            typename detail::at_index<I, Ts...>::type&
            get() BOOST_NOEXCEPT
            {
                return static_cast<tuple_member<
                        I, typename detail::at_index<I, Ts...>::type
                    >&>(*this).value();
            }

            template <std::size_t I>
            typename detail::at_index<I, Ts...>::type const&
            get() const BOOST_NOEXCEPT
            {
                return static_cast<tuple_member<
                        I, typename detail::at_index<I, Ts...>::type
                    > const&>(*this).value();
            }
        };

        ///////////////////////////////////////////////////////////////////////
        struct ignore_type
        {
            template <typename T>
            void operator=(T&& t) const
            {}
        };
    }

    // 20.4.2, class template tuple
    template <>
    class tuple<>
    {
    public:
        // 20.4.2.1, tuple construction

        // constexpr tuple();
        // Value initializes each element.
        BOOST_CONSTEXPR tuple()
        {}

        // tuple(const tuple& u) = default;
        // Initializes each element of *this with the corresponding element
        // of u.
        BOOST_CONSTEXPR tuple(tuple const& /*other*/)
        {}

        // tuple(tuple&& u) = default;
        // For all i, initializes the ith element of *this with
        // std::forward<Ti>(get<i>(u)).
        BOOST_CONSTEXPR tuple(tuple&& /*other*/)
        {}

        // 20.4.2.2, tuple assignment

        // tuple& operator=(const tuple& u);
        // Assigns each element of u to the corresponding element of *this.
        tuple& operator=(tuple const& /*other*/) BOOST_NOEXCEPT
        {
            return *this;
        }

        // tuple& operator=(tuple&& u) noexcept(see below );
        // For all i, assigns std::forward<Ti>(get<i>(u)) to get<i>(*this).
        tuple& operator=(tuple&& /*other*/) BOOST_NOEXCEPT
        {
            return *this;
        }

        // 20.4.2.3, tuple swap

        // void swap(tuple& rhs) noexcept(see below);
        // Calls swap for each element in *this and its corresponding element
        // in rhs.
        void swap(tuple& /*other*/) BOOST_NOEXCEPT
        {}
    };

    template <typename ...Ts>
    class tuple
    {
    public: // exposition-only
        detail::tuple_impl<
            typename detail::make_index_pack<sizeof...(Ts)>::type
          , Ts...> _impl;

    public:
        // 20.4.2.1, tuple construction

        // constexpr tuple();
        // Value initializes each element.
        BOOST_CONSTEXPR tuple()
          : _impl()
        {}

        // explicit constexpr tuple(const Types&...);
        // Initializes each element with the value of the corresponding
        // parameter.
        explicit BOOST_CONSTEXPR tuple(Ts const&... vs)
          : _impl(vs...)
        {}

        // template <class... UTypes>
        // explicit constexpr tuple(UTypes&&... u);
        // Initializes the elements in the tuple with the corresponding value
        // in std::forward<UTypes>(u).
        // This constructor shall not participate in overload resolution
        // unless each type in UTypes is implicitly convertible to its
        // corresponding type in Types.
        template <typename U, typename ...Us, typename Enable =
            typename boost::enable_if_c<
                detail::pack<U, Us...>::size == detail::pack<Ts...>::size
             && boost::mpl::eval_if_c<
                    detail::pack<Us...>::size == 0
                  , boost::mpl::eval_if_c<
                        boost::is_same<tuple, typename decay<U>::type>::value
                     || detail::are_tuples_compatible_not_same<tuple, U&&>::value
                      , boost::mpl::false_
                      , detail::are_tuples_compatible<tuple, tuple<U>&&>
                    >
                  , detail::are_tuples_compatible<tuple, tuple<U, Us...>&&>
                >::type::value
            >::type>
        explicit BOOST_CONSTEXPR tuple(U&& v, Us&&... vs)
          : _impl(std::forward<U>(v), std::forward<Us>(vs)...)
        {}

        // tuple(const tuple& u) = default;
        // Initializes each element of *this with the corresponding element
        // of u.
        BOOST_CONSTEXPR tuple(tuple const& other)
          : _impl(other._impl)
        {}

        // tuple(tuple&& u) = default;
        // For all i, initializes the ith element of *this with
        // std::forward<Ti>(get<i>(u)).
        BOOST_CONSTEXPR tuple(tuple&& other)
          : _impl(std::move(other._impl))
        {}

        // template <class... UTypes> constexpr tuple(const tuple<UTypes...>& u);
        // template <class... UTypes> constexpr tuple(tuple<UTypes...>&& u);
        // For all i, initializes the ith element of *this with
        // get<i>(std::forward<U>(u).
        // This constructor shall not participate in overload resolution
        // unless each type in UTypes is implicitly convertible to its
        // corresponding type in Types
        template <typename UTuple, typename Enable =
            typename boost::enable_if_c<
                detail::are_tuples_compatible_not_same<tuple, UTuple&&>::value
            >::type>
        BOOST_CONSTEXPR tuple(UTuple&& other)
          : _impl(std::forward<UTuple>(other))
        {}

        // 20.4.2.2, tuple assignment

        // tuple& operator=(const tuple& u);
        // Assigns each element of u to the corresponding element of *this.
        tuple& operator=(tuple const& other)
        {
            _impl = other._impl;
            return *this;
        }

        // tuple& operator=(tuple&& u) noexcept(see below);
        // For all i, assigns std::forward<Ti>(get<i>(u)) to get<i>(*this).
        tuple& operator=(tuple&& other)
        {
            _impl = std::move(other._impl);
            return *this;
        }

        // template <class... UTypes> tuple& operator=(const tuple<UTypes...>& u);
        // template <class... UTypes> tuple& operator=(tuple<UTypes...>&& u);
        // For all i, assigns get<i>(std::forward<U>(u)) to get<i>(*this).
        template <typename UTuple>
        typename boost::enable_if_c<
            tuple_size<typename decay<UTuple>::type>::value == detail::pack<Ts...>::size
          , tuple&
        >::type operator=(UTuple&& other)
        {
            _impl = std::forward<UTuple>(other);
            return *this;
        }

        // 20.4.2.3, tuple swap

        // void swap(tuple& rhs) noexcept(see below );
        // Calls swap for each element in *this and its corresponding element
        // in rhs.
        void swap(tuple& other)
        {
            _impl.swap(other._impl);
        }
    };

    // 20.4.2.5, tuple helper classes

    // template <class Tuple>
    // class tuple_size
    template <class T>
    struct tuple_size
    {};

    template <class T>
    struct tuple_size<const T>
      : tuple_size<T>
    {};

    template <class T>
    struct tuple_size<volatile T>
      : tuple_size<T>
    {};

    template <class T>
    struct tuple_size<const volatile T>
      : tuple_size<T>
    {};

    template <typename ...Ts>
    struct tuple_size<tuple<Ts...> >
      : boost::mpl::size_t<sizeof...(Ts)>
    {};

    template <typename T0, typename T1>
    struct tuple_size<std::pair<T0, T1> >
      : boost::mpl::size_t<2>
    {};

    template <typename Type, std::size_t Size>
    struct tuple_size<boost::array<Type, Size> >
      : boost::mpl::size_t<Size>
    {};

    // template <size_t I, class Tuple>
    // class tuple_element
    template <std::size_t I, typename T>
    struct tuple_element
    {};

    template <std::size_t I, typename T>
    struct tuple_element<I, const T>
      : boost::add_const<typename tuple_element<I, T>::type>
    {};

    template <std::size_t I, typename T>
    struct tuple_element<I, volatile T>
      : boost::add_volatile<typename tuple_element<I, T>::type>
    {};

    template <std::size_t I, typename T>
    struct tuple_element<I, const volatile T>
      : boost::add_cv<typename tuple_element<I, T>::type>
    {};

    template <std::size_t I, typename ...Ts>
    struct tuple_element<I, tuple<Ts...> >
    {
        typedef typename detail::at_index<I, Ts...>::type type;

        static BOOST_CONSTEXPR BOOST_FORCEINLINE type&
        get(tuple<Ts...>& tuple) BOOST_NOEXCEPT
        {
            return tuple._impl.template get<I>();
        }

        static BOOST_CONSTEXPR BOOST_FORCEINLINE type const&
        get(tuple<Ts...> const& tuple) BOOST_NOEXCEPT
        {
            return tuple._impl.template get<I>();
        }
    };

    template <typename T0, typename T1>
    struct tuple_element<0, std::pair<T0, T1> >
    {
        typedef T0 type;

        static BOOST_CONSTEXPR BOOST_FORCEINLINE type&
        get(std::pair<T0, T1>& tuple) BOOST_NOEXCEPT
        {
            return tuple.first;
        }

        static BOOST_CONSTEXPR BOOST_FORCEINLINE type const&
        get(std::pair<T0, T1> const& tuple) BOOST_NOEXCEPT
        {
            return tuple.first;
        }
    };

    template <typename T0, typename T1>
    struct tuple_element<1, std::pair<T0, T1> >
    {
        typedef T1 type;

        static BOOST_CONSTEXPR BOOST_FORCEINLINE type&
        get(std::pair<T0, T1>& tuple) BOOST_NOEXCEPT
        {
            return tuple.second;
        }

        static BOOST_CONSTEXPR BOOST_FORCEINLINE type const&
        get(std::pair<T0, T1> const& tuple) BOOST_NOEXCEPT
        {
            return tuple.second;
        }
    };

    template <std::size_t I, typename Type, std::size_t Size>
    struct tuple_element<I, boost::array<Type, Size> >
    {
        typedef Type type;

        static BOOST_CONSTEXPR BOOST_FORCEINLINE type&
        get(boost::array<Type, Size>& tuple) BOOST_NOEXCEPT
        {
            return tuple[I];
        }

        static BOOST_CONSTEXPR BOOST_FORCEINLINE type const&
        get(boost::array<Type, Size> const& tuple) BOOST_NOEXCEPT
        {
            return tuple[I];
        }
    };

    template <typename Tuple>
    struct tuple_decay
    {};

    template <typename ...Ts>
    struct tuple_decay<tuple<Ts...> >
    {
        typedef tuple<typename decay<Ts>::type...> type;
    };

    // 20.4.2.6, element access

    // template <size_t I, class... Types>
    // constexpr typename tuple_element<I, tuple<Types...> >::type&
    // get(tuple<Types...>& t) noexcept;
    template <std::size_t I, typename Tuple>
    BOOST_CONSTEXPR BOOST_FORCEINLINE
    typename tuple_element<I, Tuple>::type&
    get(Tuple& t) BOOST_NOEXCEPT
    {
        return tuple_element<I, Tuple>::get(t);
    }

    // template <size_t I, class... Types>
    // constexpr typename tuple_element<I, tuple<Types...> >::type const&
    // get(const tuple<Types...>& t) noexcept;
    template <std::size_t I, typename Tuple>
    BOOST_CONSTEXPR BOOST_FORCEINLINE
    typename tuple_element<I, Tuple>::type const&
    get(Tuple const& t) BOOST_NOEXCEPT
    {
        return tuple_element<I, Tuple>::get(t);
    }

    // template <size_t I, class... Types>
    // constexpr typename tuple_element<I, tuple<Types...> >::type&&
    // get(tuple<Types...>&& t) noexcept;
    template <std::size_t I, typename Tuple>
    BOOST_CONSTEXPR BOOST_FORCEINLINE
    typename tuple_element<I, Tuple>::type&&
    get(Tuple&& t) BOOST_NOEXCEPT
    {
        return std::forward<
            typename tuple_element<I, Tuple>::type>(util::get<I>(t));
    }

    // 20.4.2.4, tuple creation functions
    detail::ignore_type const ignore = {};

    // template<class... Types>
    // constexpr tuple<VTypes...> make_tuple(Types&&... t);
    template <typename ...Ts>
    BOOST_CONSTEXPR BOOST_FORCEINLINE
    tuple<typename decay_unwrap<Ts>::type...>
    make_tuple(Ts&&... vs)
    {
        return tuple<typename decay_unwrap<Ts>::type...>(
            std::forward<Ts>(vs)...);
    }

    // template<class... Types>
    // tuple<Types&&...> forward_as_tuple(Types&&... t) noexcept;
    // Constructs a tuple of references to the arguments in t suitable for
    // forwarding as arguments to a function. Because the result may contain
    // references to temporary variables, a program shall ensure that the
    // return value of this function does not outlive any of its arguments.
    template <typename ...Ts>
    BOOST_FORCEINLINE
    tuple<Ts&&...>
    forward_as_tuple(Ts&&... vs) BOOST_NOEXCEPT
    {
        return tuple<Ts&&...>(std::forward<Ts>(vs)...);
    }

    // template<class... Types>
    // tuple<Types&...> tie(Types&... t) noexcept;
    template <typename ...Ts>
    BOOST_FORCEINLINE
    tuple<Ts&...>
    tie(Ts&... vs) BOOST_NOEXCEPT
    {
        return tuple<Ts&...>(vs...);
    }

    //template <class... Tuples>
    //constexpr tuple<Ctypes ...> tuple_cat(Tuples&&...);
    namespace detail
    {
        template <std::size_t Size, typename Tuples>
        struct tuple_cat_size_impl;

        template <std::size_t Size>
        struct tuple_cat_size_impl<Size, detail::pack<> >
          : boost::mpl::size_t<Size>
        {};

        template <std::size_t Size, typename HeadTuple, typename ...TailTuples>
        struct tuple_cat_size_impl<
            Size, detail::pack<HeadTuple, TailTuples...>
        > : tuple_cat_size_impl<
                (Size + tuple_size<HeadTuple>::value), detail::pack<TailTuples...>
            >
        {};

        template <typename ...Tuples>
        struct tuple_cat_size
          : tuple_cat_size_impl<0, detail::pack<Tuples...> >
        {};

        ///////////////////////////////////////////////////////////////////////
        template <std::size_t I, typename Tuples, typename Enable = void>
        struct tuple_cat_element;

        template <std::size_t I, typename HeadTuple, typename ...TailTuples>
        struct tuple_cat_element<
            I, detail::pack<HeadTuple, TailTuples...>
          , typename boost::enable_if_c<
                (I < tuple_size<HeadTuple>::value)
            >::type
        > : tuple_element<I, HeadTuple>
        {
            typedef tuple_element<I, HeadTuple> base_type;

            template <typename HeadTuple_, typename ...TailTuples_>
            static BOOST_CONSTEXPR BOOST_FORCEINLINE
            typename detail::qualify_as<
                typename base_type::type
              , HeadTuple_&
            >::type
            get(HeadTuple_& head, TailTuples_& ...tail) BOOST_NOEXCEPT
            {
                return base_type::get(head);
            }
        };

        template <std::size_t I, typename HeadTuple, typename ...TailTuples>
        struct tuple_cat_element<
            I, detail::pack<HeadTuple, TailTuples...>
          , typename boost::enable_if_c<
                (I >= tuple_size<HeadTuple>::value)
            >::type
        > : tuple_cat_element<
                I - tuple_size<HeadTuple>::value
              , detail::pack<TailTuples...>
            >
        {
            typedef tuple_cat_element<
                I - tuple_size<HeadTuple>::value
              , detail::pack<TailTuples...>
            > base_type;

            template <typename HeadTuple_, typename ...TailTuples_>
            static BOOST_CONSTEXPR BOOST_FORCEINLINE
            typename detail::qualify_as<
                typename base_type::type
              , HeadTuple_&
            >::type
            get(HeadTuple_& head, TailTuples_& ...tail) BOOST_NOEXCEPT
            {
                return base_type::get(tail...);
            }
        };

        ///////////////////////////////////////////////////////////////////////
        template <typename Indices, typename Tuples>
        struct tuple_cat_result_impl;

        template <std::size_t ...Is, typename ...Tuples>
        struct tuple_cat_result_impl<
            detail::pack_c<std::size_t, Is...>, detail::pack<Tuples...>
        >
        {
            typedef tuple<
                typename tuple_cat_element<Is, detail::pack<Tuples...> >::type...
            > type;

            template <typename ...Tuples_>
            static BOOST_CONSTEXPR BOOST_FORCEINLINE
            type make(Tuples_&&... tuples)
            {
                return type(tuple_cat_element<Is, detail::pack<Tuples...> >::get(
                    std::forward<Tuples_>(tuples)...)...);
            }
        };

        template <typename ...Tuples>
        struct tuple_cat_result
          : tuple_cat_result_impl<
                typename make_index_pack<tuple_cat_size<Tuples...>::value>::type
              , detail::pack<Tuples...>
            >
        {};
    }

    template <typename ...Tuples>
    BOOST_CONSTEXPR BOOST_FORCEINLINE
    typename detail::tuple_cat_result<Tuples...>::type
    tuple_cat(Tuples&&... tuples)
    {
        return detail::tuple_cat_result<Tuples...>::make(
            std::forward<Tuples>(tuples)...);
    }

    // 20.4.2.7, relational operators

    // template<class... TTypes, class... UTypes>
    // constexpr bool operator==
    //     (const tuple<TTypes...>& t, const tuple<UTypes...>& u);
    // The elementary comparisons are performed in order from the zeroth index
    // upwards. No comparisons or element accesses are performed after the
    // first equality comparison that evaluates to false.
    namespace detail
    {
        template <std::size_t I, std::size_t Size>
        struct tuple_equal_to
        {
            template <typename TTuple, typename UTuple>
            static BOOST_CONSTEXPR BOOST_FORCEINLINE
            bool call(TTuple const& t, UTuple const&u)
            {
                return
                    util::get<I>(t) == util::get<I>(u)
                 && tuple_equal_to<I + 1, Size>::call(t, u);
            }
        };

        template <std::size_t Size>
        struct tuple_equal_to<Size, Size>
        {
            template <typename TTuple, typename UTuple>
            static BOOST_CONSTEXPR BOOST_FORCEINLINE
            bool call(TTuple const& t, UTuple const&u)
            {
                return true;
            }
        };
    }

    template <typename ...Ts, typename ...Us>
    BOOST_CONSTEXPR BOOST_FORCEINLINE
    typename boost::enable_if_c<sizeof...(Ts) == sizeof...(Us), bool>::type
    operator==(tuple<Ts...> const& t, tuple<Us...> const& u)
    {
        return detail::tuple_equal_to<0, sizeof...(Ts)>::call(t, u);
    }

    // template<class... TTypes, class... UTypes>
    // constexpr bool operator!=
    //     (const tuple<TTypes...>& t, const tuple<UTypes...>& u);
    template <typename ...Ts, typename ...Us>
    BOOST_CONSTEXPR BOOST_FORCEINLINE
    typename boost::enable_if_c<sizeof...(Ts) == sizeof...(Us), bool>::type
    operator!=(tuple<Ts...> const& t, tuple<Us...> const& u)
    {
        return !(t == u);
    }

    // template<class... TTypes, class... UTypes>
    // constexpr bool operator<
    //     (const tuple<TTypes...>& t, const tuple<UTypes...>& u);
    // The result is defined as: (bool)(get<0>(t) < get<0>(u)) ||
    // (!(bool)(get<0>(u) < get<0>(t)) && ttail < utail), where rtail for some
    // tuple r is a tuple containing all but the first element of r. For any
    // two zero-length tuples e and f, e < f returns false.
    namespace detail
    {
        template <std::size_t I, std::size_t Size>
        struct tuple_less_than
        {
            template <typename TTuple, typename UTuple>
            static BOOST_CONSTEXPR BOOST_FORCEINLINE
            bool call(TTuple const& t, UTuple const&u)
            {
                return
                    util::get<I>(t) < util::get<I>(u)
                 || (
                        !(util::get<I>(u) < util::get<I>(t))
                     && tuple_less_than<I + 1, Size>::call(t, u)
                    );
            }
        };

        template <std::size_t Size>
        struct tuple_less_than<Size, Size>
        {
            template <typename TTuple, typename UTuple>
            static BOOST_CONSTEXPR BOOST_FORCEINLINE
            bool call(TTuple const& t, UTuple const&u)
            {
                return false;
            }
        };
    }

    template <typename ...Ts, typename ...Us>
    BOOST_CONSTEXPR BOOST_FORCEINLINE
    typename boost::enable_if_c<sizeof...(Ts) == sizeof...(Us), bool>::type
    operator<(tuple<Ts...> const& t, tuple<Us...> const& u)
    {
        return detail::tuple_less_than<0, sizeof...(Ts)>::call(t, u);
    }

    // template<class... TTypes, class... UTypes>
    // constexpr bool operator>
    //     (const tuple<TTypes...>& t, const tuple<UTypes...>& u);
    template <typename ...Ts, typename ...Us>
    BOOST_CONSTEXPR BOOST_FORCEINLINE
    typename boost::enable_if_c<sizeof...(Ts) == sizeof...(Us), bool>::type
    operator>(tuple<Ts...> const& t, tuple<Us...> const& u)
    {
        return u < t;
    }

    // template<class... TTypes, class... UTypes>
    // constexpr bool operator<=
    //     (const tuple<TTypes...>& t, const tuple<UTypes...>& u);
    template <typename ...Ts, typename ...Us>
    BOOST_CONSTEXPR BOOST_FORCEINLINE
    typename boost::enable_if_c<sizeof...(Ts) == sizeof...(Us), bool>::type
    operator<=(tuple<Ts...> const& t, tuple<Us...> const& u)
    {
        return !(u < t);
    }

    // template<class... TTypes, class... UTypes>
    // constexpr bool operator>=
    //     (const tuple<TTypes...>& t, const tuple<UTypes...>& u);
    template <typename ...Ts, typename ...Us>
    BOOST_CONSTEXPR BOOST_FORCEINLINE
    typename boost::enable_if_c<sizeof...(Ts) == sizeof...(Us), bool>::type
    operator>=(tuple<Ts...> const& t, tuple<Us...> const& u)
    {
        return !(t < u);
    }

    // 20.4.2.9, specialized algorithms

    // template <class... Types>
    // void swap(tuple<Types...>& x, tuple<Types...>& y) noexcept(x.swap(y));
    // x.swap(y)
    template <typename ...Ts>
    BOOST_FORCEINLINE
    void swap(tuple<Ts...>& x, tuple<Ts...>& y)
        BOOST_NOEXCEPT_IF(BOOST_NOEXCEPT_EXPR((x.swap(y))))
    {
        x.swap(y);
    }
}}

#include <hpx/util/detail/fusion_adapt_tuple.hpp>

namespace hpx { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename ...Ts>
    struct is_bitwise_serializable<
        ::hpx::util::tuple<Ts...>
    > : ::hpx::util::detail::all_of<
            hpx::traits::is_bitwise_serializable<Ts>...
        >
    {};

    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        template <typename Is, typename ...Ts>
        struct serialize_as_future_helper;

        template <std::size_t ...Is, typename ...Ts>
        struct serialize_as_future_helper<
                util::detail::pack_c<std::size_t, Is...>, Ts...
            >
        {
            static bool call_if(util::tuple<Ts...>& t)
            {
                bool const _sequencer[] = {
                    serialize_as_future<Ts>::call_if(util::get<Is>(t))...
                };

                return std::any_of(_sequencer,
                    _sequencer+sizeof(_sequencer)/sizeof(_sequencer[0]),
                    [](bool b) { return b; });
            }

            static void call(util::tuple<Ts...>& t)
            {
                int const _sequencer[] = {
                    (serialize_as_future<Ts>::call(util::get<Is>(t)), 0)...
                };
                (void)_sequencer;
            }
        };
    }

    template <>
    struct serialize_as_future<util::tuple<> >
      : boost::mpl::false_
    {
        static BOOST_FORCEINLINE bool call_if(util::tuple<>&) { return false; }
        static BOOST_FORCEINLINE void call(util::tuple<>&) {}
    };

    template <typename ...Ts>
    struct serialize_as_future<util::tuple<Ts...> >
      : util::detail::any_of<serialize_as_future<Ts>...>
    {
        static bool call_if(util::tuple<Ts...>& t)
        {
            return util::detail::any_of<serialize_as_future<Ts>...>::value ||
                traits::detail::serialize_as_future_helper<
                    typename util::detail::make_index_pack<sizeof...(Ts)>::type,
                    Ts...
                >::call_if(t);
        }

        static void call(util::tuple<Ts...>& t)
        {
            traits::detail::serialize_as_future_helper<
                typename util::detail::make_index_pack<sizeof...(Ts)>::type,
                Ts...
            >::call(t);
        }
    };
}}

namespace hpx { namespace serialization {

    ///////////////////////////////////////////////////////////////////////////
    template <typename Archive, typename ...Ts>
    BOOST_FORCEINLINE
    void serialize(
        Archive& ar
      , ::hpx::util::tuple<Ts...>& t
      , unsigned int const version
    )
    {
        ::hpx::serialization::serialize_sequence(ar, t);
    }

    // These are needed to avoid conflicts with serialize_empty_type
    BOOST_FORCEINLINE
    void serialize(
        serialization::output_archive&
      , ::hpx::util::tuple<>&
      , unsigned int const
    )
    {}

    BOOST_FORCEINLINE
    void serialize(
        serialization::input_archive&
      , ::hpx::util::tuple<>&
      , unsigned int const
    )
    {}
}}

#if defined(BOOST_MSVC)
#pragma warning(pop)
#endif

#endif
