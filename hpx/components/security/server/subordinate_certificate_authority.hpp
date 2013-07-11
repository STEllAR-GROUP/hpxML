//  Copyright (c) 2013 Jeroen Habraken
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef HPX_COMPONENTS_SECURITY_SERVER_SUBORDINATE_CERTIFICATE_AUTHORITY_HPP
#define HPX_COMPONENTS_SECURITY_SERVER_SUBORDINATE_CERTIFICATE_AUTHORITY_HPP

#include <hpx/hpx_fwd.hpp>
#include <hpx/include/actions.hpp>
#include <hpx/include/components.hpp>

#include "certificate_authority_base.hpp"

namespace hpx { namespace components { namespace security { namespace server
{
    class HPX_COMPONENT_EXPORT subordinate_certificate_authority
      : public certificate_authority_base
      , public simple_component_base<subordinate_certificate_authority>
    {
    public:
        typedef subordinate_certificate_authority type_holder;
        typedef certificate_authority_base base_type_holder;

        subordinate_certificate_authority();
        subordinate_certificate_authority(naming::id_type const &);
        subordinate_certificate_authority(key_pair const &, naming::id_type const &);

        signed_type<certificate> sign_certificate_signing_request(
            signed_type<certificate_signing_request> const &) const;

        naming::gid_type get_base_gid() const
        {
            typedef simple_component_base<subordinate_certificate_authority>
                component_base_type;
            return this->component_base_type::get_base_gid();
        }
    };
}}}}

#endif
