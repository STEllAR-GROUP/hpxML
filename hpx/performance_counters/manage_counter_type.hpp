////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2007-2012 Hartmut Kaiser
//  Copyright (c) 2011 Bryce Adelstein-Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(HPX_F26CC3F9_3E30_4C54_90E0_0CD02146320F)
#define HPX_F26CC3F9_3E30_4C54_90E0_0CD02146320F

#include <hpx/exception.hpp>
#include <hpx/performance_counters/counters.hpp>

namespace hpx { namespace performance_counters
{
    struct manage_counter_type
    {
        manage_counter_type(counter_info const& info)
          : status_(status_invalid_data), info_(info)
        {}

        ~manage_counter_type()
        {
            uninstall();
        }

        counter_status install(error_code& ec = throws)
        {
            if (status_invalid_data != status_) {
                HPX_THROWS_IF(ec, hpx::invalid_status,
                    "manage_counter_type::install",
                    "counter type " + info_.fullname_ +
                    " has been already installed.");
                return status_invalid_data;
            }

            return status_ = add_counter_type(info_, ec);
        }

        void uninstall(error_code& ec = throws)
        {
            if (status_invalid_data != status_)
                remove_counter_type(info_, ec); // ignore errors
        }

    private:
        counter_status status_;
        counter_info info_;
    };

    /// \brief Install a new performance counter type in a way, which will
    ///        uninstall it automatically during shutdown.
    ///
    /// The function \a install_counter_type will register a new counter type
    /// based on the provided \a counter_type_info. The counter type will be
    /// automatically unregistered during system shutdown.
    ///
    /// \param name   [in] The global virtual name of the counter type. This
    ///               name is expected to have the format /objectname/countername.
    /// \param type   [in] The type of the counters of  this counter_type.
    /// \param ec     [in,out] this represents the error status on exit,
    ///               if this is pre-initialized to \a hpx#throws
    ///               the function will throw on error instead.
    ///
    /// \returns      If successful, this function returns \a status_valid_data,
    ///               otherwise it will either throw an exception or return an
    ///               error_code from the enum \a counter_status (also, see
    ///               note related to parameter \a ec).
    ///
    /// \note The counter type registry is a locality based service. You will
    ///       have to register each counter type on every locality a
    ///       corresponding performance counter will be created.
    ///
    /// \note As long as \a ec is not pre-initialized to \a hpx#throws this
    ///       function doesn't throw but returns the result code using the
    ///       parameter \a ec. Otherwise it throws an instance of hpx#exception.
    HPX_EXPORT void install_counter_type(std::string const& name,
        counter_type type, error_code& ec = throws);

    /// \brief Install a new performance counter type in a way, which will
    ///        uninstall it automatically during shutdown.
    ///
    /// The function \a install_counter_type will register a new counter type
    /// based on the provided \a counter_type_info. The counter type will be
    /// automatically unregistered during system shutdown.
    ///
    /// \param name   [in] The global virtual name of the counter type. This
    ///               name is expected to have the format /objectname/countername.
    /// \param type   [in] The type of the counters of  this counter_type.
    /// \param helptext [in] A longer descriptive  text shown to the user to
    ///               explain the nature of the counters created from this
    ///               type.
    /// \param version [in] The version of the counter type. This is currently
    ///               expected to be set to HPX_PERFORMANCE_COUNTER_V1.
    /// \param ec     [in,out] this represents the error status on exit,
    ///               if this is pre-initialized to \a hpx#throws
    ///               the function will throw on error instead.
    ///
    /// \returns      If successful, this function returns \a status_valid_data,
    ///               otherwise it will either throw an exception or return an
    ///               error_code from the enum \a counter_status (also, see
    ///               note related to parameter \a ec).
    ///
    /// \note The counter type registry is a locality based service. You will
    ///       have to register each counter type on every locality a
    ///       corresponding performance counter will be created.
    ///
    /// \note As long as \a ec is not pre-initialized to \a hpx#throws this
    ///       function doesn't throw but returns the result code using the
    ///       parameter \a ec. Otherwise it throws an instance of hpx#exception.
    HPX_EXPORT void install_counter_type(std::string const& name,
        counter_type type, std::string const& helptext,
        boost::uint32_t version = HPX_PERFORMANCE_COUNTER_V1,
        error_code& ec = throws);

    /// A small data structure holding all data needed to install a counter type
    struct raw_counter_type_data
    {
        std::string name_;          ///< Name of the counter type
        counter_type type_;         ///< Type of the counter instances of this
                                    ///< counter type
        std::string helptext_;      ///< Longer descriptive text explaining the
                                    ///< counter type
        boost::uint32_t version_;   ///< Version of this counter type definition
                                    ///< (default: 0x01000000)
    };

    /// Install several new performance counter types in a way, which will
    /// uninstall them automatically during shutdown.
    HPX_EXPORT void install_counter_types(raw_counter_type_data const* data,
        std::size_t count, error_code& ec = throws);
}}

#endif // HPX_F26CC3F9_3E30_4C54_90E0_0CD02146320F

