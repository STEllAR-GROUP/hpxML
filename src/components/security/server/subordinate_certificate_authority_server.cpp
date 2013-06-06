//  Copyright (c) 2013 Jeroen Habraken
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/components/security/certificate_authority_base.hpp>
#include <hpx/components/security/server/subordinate_certificate_authority.hpp>

#include <iostream>

namespace hpx { namespace components { namespace security { namespace server
{
    boost::uint64_t get_subordinate_certificate_authority_msb()
    {
        return naming::replace_locality_id(
            HPX_SUBORDINATE_CERTIFICATE_AUTHORITY_MSB
          , get_locality_id());
    }

    subordinate_certificate_authority::subordinate_certificate_authority()
      : certificate_authority_base()
      , fixed_component_base<subordinate_certificate_authority>(
            get_subordinate_certificate_authority_msb()
          , HPX_SUBORDINATE_CERTIFICATE_AUTHORITY_LSB)
    {
    }

    subordinate_certificate_authority::subordinate_certificate_authority(
        naming::id_type const & issuer_id)
      : certificate_authority_base()
      , fixed_component_base<subordinate_certificate_authority>(
            get_subordinate_certificate_authority_msb()
          , HPX_SUBORDINATE_CERTIFICATE_AUTHORITY_LSB)
    {
        security::certificate_authority_base issuer(issuer_id);

        signed_type<certificate_signing_request> signed_csr =
            key_pair_.sign(certificate_signing_request(
                get_gid().get_gid(), key_pair_.get_public_key()));

        certificate_ = issuer.sign_certificate_signing_request(signed_csr);
    }

    subordinate_certificate_authority::subordinate_certificate_authority(
        key_pair const & key_pair
      , naming::id_type const & issuer_id)
      : certificate_authority_base(key_pair)
      , fixed_component_base<subordinate_certificate_authority>(
            get_subordinate_certificate_authority_msb()
          , HPX_SUBORDINATE_CERTIFICATE_AUTHORITY_LSB)
    {
        security::certificate_authority_base issuer(issuer_id);

        signed_type<certificate_signing_request> signed_csr =
            key_pair_.sign(certificate_signing_request(
                get_gid().get_gid(), key_pair_.get_public_key()));

        certificate_ = issuer.sign_certificate_signing_request(signed_csr);
    }

    signed_type<certificate>
    subordinate_certificate_authority::sign_certificate_signing_request(
        signed_type<certificate_signing_request> const & signed_csr) const
    {
        certificate_signing_request const & csr = signed_csr.get_type();
        if (csr.get_subject_public_key().verify(signed_csr) == false)
        {
            HPX_THROW_EXCEPTION(
                hpx::security_error
              , "root_certificate_authority::sign_certificate_signing_request"
              , boost::str(boost::format(
                    "the certificate signing request signature is invalid: %1%") %
                    signed_csr)
            )
        }

        // TODO, capability checks

        signed_type<certificate> signed_certificate;

        signed_certificate = key_pair_.sign(certificate(
            get_gid().get_gid(), csr));

        return signed_certificate;
    }
}}}}
