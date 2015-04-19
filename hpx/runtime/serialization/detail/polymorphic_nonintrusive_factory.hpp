//  Copyright (c) 2014 Thomas Heller
//  Copyright (c) 2015 Anton Bikineev
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef HPX_SERIALIZATION_POLYMORPHIC_NONINTRUSIVE_FACTORY_HPP
#define HPX_SERIALIZATION_POLYMORPHIC_NONINTRUSIVE_FACTORY_HPP

#include <hpx/runtime/serialization/serialization_fwd.hpp>
#include <hpx/util/jenkins_hash.hpp>
#include <hpx/util/static.hpp>
#include <hpx/util/demangle_helper.hpp>
#include <hpx/traits/polymorphic_traits.hpp>
#include <hpx/traits/needs_automatic_registration.hpp>

#include <boost/noncopyable.hpp>
#include <boost/unordered_map.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_abstract.hpp>

#include <hpx/config/warnings_prefix.hpp>

namespace hpx { namespace serialization { namespace detail
{
        template <typename T>
        char const* get_serialization_name()
#ifdef HPX_DISABLE_AUTOMATIC_SERIALIZATION_REGISTRATION
        ;
#else
        {
            /// If you encounter this assert while compiling code, that means that
            /// you have a HPX_REGISTER_ACTION macro somewhere in a source file,
            /// but the header in which the action is defined misses a
            /// HPX_REGISTER_ACTION_DECLARATION
            BOOST_MPL_ASSERT_MSG(
                traits::needs_automatic_registration<T>::value
              , HPX_REGISTER_ACTION_DECLARATION_MISSING
              , (T)
            );
            return util::type_id<T>::typeid_.type_id();
        }
#endif

    struct function_bunch_type
    {
        typedef void (*save_function_type) (output_archive& , const void* base);
        typedef void (*load_function_type) (input_archive& , void* base);
        typedef void* (*create_function_type) ();

        save_function_type save_function;
        load_function_type load_function;
        create_function_type create_function;
    };

    class HPX_EXPORT polymorphic_nonintrusive_factory: boost::noncopyable
    {
    public:
        typedef boost::unordered_map<std::string,
                  function_bunch_type, hpx::util::jenkins_hash> serializer_map_type;

        static polymorphic_nonintrusive_factory& instance()
        {
            hpx::util::static_<polymorphic_nonintrusive_factory> factory;
            return factory.get();
        }

        void register_class(const std::string& class_name,
            const function_bunch_type& bunch)
        {
            if(class_name.empty())
            {
                HPX_THROW_EXCEPTION(serialization_error
                  , "polymorphic_nonintrusive_factory::register_class"
                  , "Cannot register a factory with an empty name");
            }
            auto it = map_.find(class_name);
            if(it == map_.end())
                map_.emplace(class_name, bunch);
        }

        // the following templates are defined in *.ipp file
        template <class T>
        void save(output_archive& ar, const T& t);

        template <class T>
        void load(input_archive& ar, T& t);

        // use raw pointer to construct either
        // shared_ptr or intrusive_ptr from it
        template <class T>
        T* load(input_archive& ar);

    private:
        polymorphic_nonintrusive_factory()
        {
        }

        friend struct hpx::util::static_<polymorphic_nonintrusive_factory>;

        serializer_map_type map_;
    };

    template <class Derived, class Enable = void>
    struct register_class;

    template <class Derived>
    struct register_class<Derived,
      typename boost::disable_if<boost::is_abstract<Derived> >::type>
    {
        static void save(output_archive& ar, const void* base)
        {
            serialize(ar, *static_cast<Derived*>(const_cast<void*>(base)), 0);
        }

        static void load(input_archive& ar, void* base)
        {
            serialize(ar, *static_cast<Derived*>(base), 0);
        }

        // this function is needed for pointer type serialization
        static void* create()
        {
            return new Derived;
        }

        register_class()
        {
            function_bunch_type bunch = {
                &register_class<Derived>::save,
                &register_class<Derived>::load,
                &register_class<Derived>::create
            };

            polymorphic_nonintrusive_factory::instance().
                register_class(
                    get_serialization_name<Derived>(),
                    bunch
                );
        }

        static register_class instance;
    };

    template <class Derived>
    struct register_class<Derived,
        typename boost::enable_if<boost::is_abstract<Derived> >::type >
    {
        static void save(output_archive& ar, const void* base)
        {
            serialize(ar, *static_cast<Derived*>(const_cast<void*>(base)), 0);
        }

        static void load(input_archive& ar, void* base)
        {
            serialize(ar, *static_cast<Derived*>(base), 0);
        }

        register_class()
        {
            function_bunch_type bunch = {
                &register_class<Derived>::save,
                &register_class<Derived>::load,
                static_cast<void* (*)()>(0)
            };

            polymorphic_nonintrusive_factory::instance().
                register_class(
                    get_serialization_name<Derived>(),
                    bunch
                );
        }

        static register_class instance;
    };

    template <class T>
    register_class<T, typename boost::disable_if<boost::is_abstract<T> >::type>
        register_class<T, typename boost::disable_if<boost::is_abstract<T> >::type>::
            instance;

    template <class T>
    register_class<T, typename boost::enable_if<boost::is_abstract<T> >::type>
        register_class<T, typename boost::enable_if<boost::is_abstract<T> >::type>::
            instance;

}}}

#include <hpx/config/warnings_suffix.hpp>

#define HPX_SERIALIZATION_REGISTER_CLASS_DECLARATION(Class)                   \
    namespace hpx { namespace serialization { namespace detail {              \
        template <> HPX_ALWAYS_EXPORT                                         \
        char const* get_serialization_name<Class>();                          \
    }}}                                                                       \
    namespace hpx { namespace traits {                                        \
        template <>                                                           \
        struct needs_automatic_registration<action>                           \
          : boost::mpl::false_                                                \
        {};                                                                   \
    }}                                                                        \
    HPX_TRAITS_NONINTRUSIVE_POLYMORPHIC(Class);                               \

#define HPX_SERIALIZATION_REGISTER_CLASS_NAME(Class, Name)                    \
    namespace hpx { namespace serialization { namespace detail {              \
        template <> HPX_ALWAYS_EXPORT                                         \
        char const* get_serialization_name<Class>()                           \
        {                                                                     \
            return BOOST_PP_STRINGIZE(Name);                                  \
        }                                                                     \
    }}}                                                                       \
    template hpx::serialization::detail::register_class<Class>                \
        hpx::serialization::detail::register_class<Class>::instance;          \
/**/
#define HPX_SERIALIZATION_REGISTER_CLASS(Class)                               \
    HPX_SERIALIZATION_REGISTER_CLASS_NAME(Class, Class)                       \

#endif
