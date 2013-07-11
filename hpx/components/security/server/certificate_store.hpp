//  Copyright (c) 2013 Jeroen Habraken
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef HPX_COMPONENTS_SECURITY_SERVER_CERTIFICATE_STORE_HPP
#define HPX_COMPONENTS_SECURITY_SERVER_CERTIFICATE_STORE_HPP

#include <boost/optional.hpp>
#include <hpx/hpx_fwd.hpp>
#include <hpx/exception.hpp>

#include "certificate.hpp"
#include "identity.hpp"
#include "public_key.hpp"
#include "signed_type.hpp"

namespace hpx { namespace components { namespace security { namespace server
{
    class certificate_store
    {
        typedef std::map<identity, signed_type<certificate> > store_type;

    public:
        certificate_store(signed_type<certificate> const & signed_certificate)
        {
            certificate const & certificate = signed_certificate.get_type();

            if (certificate.get_issuer() != certificate.get_subject())
            {
                HPX_THROW_EXCEPTION(
                    hpx::security_error
                  , "certificate_store::certificate_store"
                  , "The certificate is not self-signed"
                )
            }

            public_key const & issuer_public_key =
                certificate.get_subject_public_key();
            if (issuer_public_key.verify(signed_certificate) == false)
            {
                HPX_THROW_EXCEPTION(
                    hpx::security_error
                  , "certificate_store::certificate_store"
                  , "The certificate signature is invalid"
                )
            }

            store_.insert(
                std::make_pair(certificate.get_subject(), signed_certificate));
        }

        bool insert(signed_type<certificate> const & signed_certificate)
        {
            certificate const & certificate = signed_certificate.get_type();

            store_type::const_iterator issuer =
                store_.find(certificate.get_issuer());
            if (issuer == store_.end())
            {
                HPX_THROW_EXCEPTION(
                    hpx::security_error
                  , "certificate_store::insert"
                  , "The certificate issuer is unknown"
                )
            }

            // TODO, verify capabilities

            public_key const & issuer_public_key =
                issuer->second.get_type().get_subject_public_key();
            if (issuer_public_key.verify(signed_certificate) == false)
            {
                HPX_THROW_EXCEPTION(
                    hpx::security_error
                  , "certificate_store::certificate_store"
                  , "The certificate signature is invalid"
                )
            }

            return store_.insert(
                std::make_pair(certificate.get_subject(), signed_certificate)
            ).second;
        }

        boost::optional<signed_type<certificate> >
        at(identity const & subject) const
        {
            store_type::const_iterator iterator = store_.find(subject);

            if (iterator != store_.end())
                return iterator->second;

            return boost::none;
        }

    private:
        store_type store_;
    };
}}}}

#endif
