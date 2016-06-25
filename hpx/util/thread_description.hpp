//  Copyright (c) 2016 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_RUNTIME_THREADS_DETAIL_THREAD_DESCRIPTION_FEB_19_2016_0200PM)
#define HPX_RUNTIME_THREADS_DETAIL_THREAD_DESCRIPTION_FEB_19_2016_0200PM

#include <hpx/config.hpp>
#include <hpx/runtime/actions/basic_action_fwd.hpp>
#include <hpx/runtime/threads/thread_data_fwd.hpp>
#include <hpx/traits/get_function_address.hpp>
#include <hpx/traits/is_action.hpp>
#include <hpx/util/assert.hpp>

#include <iosfwd>
#include <string>
#include <type_traits>
#include <utility>

namespace hpx { namespace util
{
#if defined(HPX_HAVE_THREAD_DESCRIPTION)
    ///////////////////////////////////////////////////////////////////////////
    struct thread_description
    {
    public:
        enum data_type
        {
            data_type_description = 0,
            data_type_address = 1
        };

    private:
        union data
        {
            char const* desc_; //-V117
            std::size_t addr_; //-V117
        };

        data_type type_;
        data data_;

#if !defined(HPX_HAVE_THREAD_DESCRIPTION_FULL)
        HPX_EXPORT void init_from_alternative_name(char const* altname);
#endif

    public:
        thread_description() HPX_NOEXCEPT
          : type_(data_type_description)
        {
            data_.desc_ = "<unknown>";
        }

        thread_description(char const* desc) HPX_NOEXCEPT
          : type_(data_type_description)
        {
            data_.desc_ = desc;
        }

        template <typename F, typename =
            typename std::enable_if<
                !std::is_same<F, thread_description>::value &&
                !traits::is_action<F>::value
            >::type>
        explicit thread_description(F const& f,
                char const* altname = nullptr) HPX_NOEXCEPT
          : type_(data_type_description)
        {
#if defined(HPX_HAVE_THREAD_DESCRIPTION_FULL)
            type_ = data_type_address;
            data_.addr_ = traits::get_function_address<F>::call(f);
#else
            init_from_alternative_name(altname);
#endif
        }

        template <typename Action, typename =
            typename std::enable_if<
                traits::is_action<Action>::value
            >::type>
        explicit thread_description(Action,
                char const* altname = nullptr) HPX_NOEXCEPT
          : type_(data_type_description)
        {
            data_.desc_ = hpx::actions::detail::get_action_name<Action>();
        }

        data_type kind() const HPX_NOEXCEPT
        {
            return type_;
        }

        char const* get_description() const HPX_NOEXCEPT
        {
            HPX_ASSERT(type_ == data_type_description);
            return data_.desc_;
        }

        std::size_t get_address() const HPX_NOEXCEPT
        {
            HPX_ASSERT(type_ == data_type_address);
            return data_.addr_;
        }

        explicit operator bool() const HPX_NOEXCEPT
        {
            return valid();
        }

        bool valid() const HPX_NOEXCEPT
        {
            if (type_ == data_type_description)
                return nullptr != data_.desc_;

            HPX_ASSERT(type_ == data_type_address);
            return 0 != data_.addr_;
        }
    };
#else
    ///////////////////////////////////////////////////////////////////////////
    struct thread_description
    {
    public:
        enum data_type
        {
            data_type_description = 0,
            data_type_address = 1
        };

    private:
        // expose for ABI compatibility reasons
        HPX_EXPORT void init_from_alternative_name(char const* altname);

    public:
        thread_description() HPX_NOEXCEPT
        {
        }

        thread_description(char const* desc) HPX_NOEXCEPT
        {
        }

        template <typename F, typename =
            typename std::enable_if<
                !std::is_same<F, thread_description>::value &&
                !traits::is_action<F>::value
            >::type>
        explicit thread_description(F const& f,
            char const* altname = nullptr) HPX_NOEXCEPT
        {
        }

        template <typename Action, typename =
            typename std::enable_if<
                traits::is_action<Action>::value
            >::type>
        explicit thread_description(Action,
            char const* altname = nullptr) HPX_NOEXCEPT
        {
        }

        data_type kind() const HPX_NOEXCEPT
        {
            return data_type_description;
        }

        char const* get_description() const HPX_NOEXCEPT
        {
            return "<unknown>";
        }

        std::size_t get_address() const HPX_NOEXCEPT
        {
            return 0;
        }

        explicit operator bool() const HPX_NOEXCEPT
        {
            return valid();
        }

        bool valid() const HPX_NOEXCEPT
        {
            return true;
        }
    };
#endif

    HPX_EXPORT std::ostream& operator<<(std::ostream&, thread_description const&);
    HPX_EXPORT std::string as_string(thread_description const& desc);
}}

#endif

