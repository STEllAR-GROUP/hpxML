//  Copyright (c)      2014 Thomas Heller
//  Copyright (c) 2007-2013 Hartmut Kaiser
//  Copyright (c) 2007 Richard D. Guidry Jr.
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_PARCELSET_LOCALITY_HPP)
#define HPX_PARCELSET_LOCALITY_HPP

#include <hpx/config.hpp>

#include <hpx/hpx_fwd.hpp>
#include <hpx/exception.hpp>
#include <hpx/util/safe_bool.hpp>

#include <boost/config.hpp>
#include <boost/cstdint.hpp>
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/or.hpp>

#include <hpx/config/warnings_prefix.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace parcelset
{
    namespace detail {
        BOOST_MPL_HAS_XXX_TRAIT_DEF(iterator_category);
    };

    class locality
    {
        template <typename Impl>
        class impl;

        class impl_base
        {
        public:
            virtual ~impl_base() {}

            virtual bool equal(impl_base const & rhs) const = 0;
            virtual bool less_than(impl_base const & rhs) const = 0;
            virtual bool valid() const = 0;
            virtual connection_type get_type() const = 0;
            virtual std::ostream & print(std::ostream & os) const = 0;
            virtual void save(util::portable_binary_oarchive & ar) const = 0;
            virtual void load(util::portable_binary_iarchive & ar) = 0;
            virtual impl_base * clone() const = 0;
            virtual impl_base * move() = 0;

            template <typename Impl>
            Impl & get()
            {
                HPX_ASSERT(Impl::get_type() == get_type());
                return static_cast<impl<Impl>*>(this)->impl_;
            }

            template <typename Impl>
            Impl const & get() const
            {
                HPX_ASSERT(Impl::get_type() == get_type());
                return static_cast<const impl<Impl>*>(this)->impl_;
            }
        };

    public:
        locality()
        {}

        template <typename Impl>
        locality(Impl && i
          , typename boost::disable_if<
                boost::mpl::or_<
                    boost::is_same<locality, typename util::decay<Impl>::type>
                  , detail::has_iterator_category<typename util::decay<Impl>::type>
                >
            >::type* = 0
        )
          : impl_(new impl<typename util::decay<Impl>::type>(std::forward<Impl>(i)))
        {}

        locality(locality const & other)
          : impl_(other.impl_ ? other.impl_->clone() : 0)
        {
        }

        locality(locality && other)
          : impl_(other.impl_ ? other.impl_->move() : 0)
        {
        }

        locality & operator=(locality const & other)
        {
            if(this != &other)
            {
                if(other.impl_)
                {
                    impl_.reset(other.impl_->clone());
                }
                else
                {
                    impl_.reset();
                }
            }
            return *this;
        }

        locality & operator=(locality && other)
        {
            if(this != &other)
            {
                if(other.impl_)
                {
                    impl_.reset(other.impl_->move());
                }
                else
                {
                    impl_.reset();
                }
            }
            return *this;
        }

        ///////////////////////////////////////////////////////////////////////
        operator util::safe_bool<locality>::result_type() const
        {
            return util::safe_bool<locality>()(impl_ ? impl_->valid(): false);
        }

        connection_type get_type() const
        {
            return impl_ ? impl_->get_type() : parcelset::connection_unknown;
        }

        template <typename Impl>
        Impl & get()
        {
            HPX_ASSERT(impl_);
            return impl_->get<Impl>();
        }

        template <typename Impl>
        Impl const & get() const
        {
            HPX_ASSERT(impl_);
            return impl_->get<Impl>();
        }

    private:
        friend bool operator==(locality const& lhs, locality const& rhs)
        {
            if(lhs.impl_ == rhs.impl_) return true;
            if(!lhs.impl_ || !rhs.impl_) return false;
            return lhs.impl_->equal(*rhs.impl_);
        }

        friend bool operator!=(locality const& lhs, locality const& rhs)
        {
            return !(lhs == rhs);
        }

        friend bool operator< (locality const& lhs, locality const& rhs)
        {
            if(lhs.impl_ == rhs.impl_) return false;
            if(!lhs.impl_ || ! rhs.impl_) return false;
            return lhs.impl_->less_than(*rhs.impl_);
        }

        friend bool operator> (locality const& lhs, locality const& rhs)
        {
            if(lhs.impl_ == rhs.impl_) return false;
            if(!lhs.impl_ || ! rhs.impl_) return false;
            return !(lhs < rhs) && !(lhs == rhs);
        }

        friend std::ostream& operator<< (std::ostream& os, locality const& l)
        {
            if(!l.impl_) return os;
            return l.impl_->print(os);
        }

        // serialization support
        friend class boost::serialization::access;

        void save(util::portable_binary_oarchive & ar, const unsigned int version) const;

        void load(util::portable_binary_iarchive & ar, const unsigned int version);

        BOOST_SERIALIZATION_SPLIT_MEMBER()

        HPX_STD_UNIQUE_PTR<impl_base> impl_;

        template <typename Impl>
        class impl : public impl_base
        {
        public:
            explicit impl(Impl && i) : impl_(std::move(i)) {}
            explicit impl(Impl const & i) : impl_(i) {}

            bool equal(impl_base const & rhs) const
            {
                if(get_type() != rhs.get_type()) return false;
                return impl_ == rhs.get<Impl>();
            }

            bool less_than(impl_base const & rhs) const
            {
                return get_type() < rhs.get_type() ||
                    (get_type() == rhs.get_type() && impl_ < rhs.get<Impl>());
            }

            bool valid() const
            {
                return !!impl_;
            }

            connection_type get_type() const
            {
                return Impl::get_type();
            }

            std::ostream & print(std::ostream & os) const
            {
                os << impl_;
                return os;
            }

            void save(util::portable_binary_oarchive & ar) const
            {
                impl_.save(ar);
            }

            void load(util::portable_binary_iarchive & ar)
            {
                impl_.load(ar);
            }

            impl_base * clone() const
            {
                return new impl<Impl>(impl_);
            }

            impl_base * move()
            {
                return new impl<Impl>(std::move(impl_));
            }

            Impl impl_;
        };
    };

    std::ostream& operator<< (std::ostream& os, endpoints_type const& endpoints);
}}

#endif
