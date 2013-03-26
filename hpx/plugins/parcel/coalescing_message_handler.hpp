//  Copyright (c) 2007-2013 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_RUNTIME_PARCELSET_POLICIES_COALESCING_MESSAGE_HANDLER_FEB_24_2013_0302PM)
#define HPX_RUNTIME_PARCELSET_POLICIES_COALESCING_MESSAGE_HANDLER_FEB_24_2013_0302PM

#include <hpx/hpx_fwd.hpp>

#if defined(HPX_HAVE_PARCEL_COALESCING)

#include <hpx/runtime/parcelset/policies/message_handler.hpp>
#include <hpx/util/reinitializable_static.hpp>

#include <boost/preprocessor/stringize.hpp>

#include <hpx/config/warnings_prefix.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace plugins { namespace parcel
{
    struct HPX_LIBRARY_EXPORT coalescing_message_handler
      : parcelset::policies::message_handler
    {
        typedef parcelset::policies::message_handler::write_handler_type
            write_handler_type;

        coalescing_message_handler(std::size_t num);
        ~coalescing_message_handler();

        void put_parcel(parcelset::parcelport* set, parcelset::parcel& p,
            write_handler_type f);

    private:
        std::size_t buffer_size_;
    };
}}}

#include <hpx/config/warnings_suffix.hpp>

///////////////////////////////////////////////////////////////////////////////
#define HPX_ACTION_USES_MESSAGE_COALESCING(action_type, num)                  \
    namespace hpx { namespace traits                                          \
    {                                                                         \
        template <>                                                           \
        struct action_message_handler<action_type>                            \
        {                                                                     \
            static parcelset::policies::message_handler* call(                \
                parcelset::parcelhandler* ph)                                 \
            {                                                                 \
                return ph->get_message_handler<                               \
                    hpx::plugins::parcel::coalescing_message_handler          \
                >(BOOST_PP_STRINGIZE(action_type), num);                      \
            }                                                                 \
        };                                                                    \
    }}                                                                        \
/**/

#else

#define HPX_ACTION_USES_MESSAGE_COALESCING(action_type, num)

#endif

#endif
