//  Copyright (c) 2007-2014 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_COMPONENTS_SERVER_MIGRATION_SUPPORT_FEB_03_2014_0230PM)
#define HPX_COMPONENTS_SERVER_MIGRATION_SUPPORT_FEB_03_2014_0230PM

#include <hpx/hpx_fwd.hpp>
#include <hpx/lcos/local/spinlock.hpp>

namespace hpx { namespace components
{
    /// This hook has to be inserted into the derivation chain of any component
    /// for it to support migration.
    template <typename BaseComponent, typename Mutex = lcos::local::spinlock>
    struct migration_support : BaseComponent
    {
    private:
        typedef Mutex mutex_type;
        typedef BaseComponent base_type;
        typedef typename base_type::this_component_type this_component_type;

    public:
        migration_support()
          : pin_count_(0)
        {}

        template <typename Arg>
        migration_support(Arg && arg)
          : base_type(std::forward<Arg>(arg))
          , pin_count_(0)
        {}

        ~migration_support()
        {
            // prevent base destructor from unregistering the gid if this
            // instance has been migrated
            if (pin_count_ == ~0x0)
                this->gid_ = naming::invalid_gid;
        }

        // This component type supports migration.
        static BOOST_CONSTEXPR bool supports_migration() { return true; }

        // Pinning functionality
        void pin()
        {
            typename mutex_type::scoped_lock l(mtx_);
            ++pin_count_;
        }
        void unpin()
        {
            typename mutex_type::scoped_lock l(mtx_);
            HPX_ASSERT(pin_count_ != 0);
            if (pin_count_ != ~0x0)
                --pin_count_;
        }
        boost::uint32_t pin_count() const
        {
            typename mutex_type::scoped_lock l(mtx_);
            return pin_count_;
        }
        void mark_as_migrated()
        {
            typename mutex_type::scoped_lock l(mtx_);
            HPX_ASSERT(1 == pin_count_);
            pin_count_ = ~0x0;
        }

        /// This is the hook implementation for decorate_action which makes
        /// sure that the object becomes pinned during the execution of an
        /// action.
        static HPX_STD_FUNCTION<threads::thread_function_type>
        wrap_action(HPX_STD_FUNCTION<threads::thread_function_type> f,
            naming::address::address_type lva)
        {
            using util::placeholders::_1;
            return util::bind(&migration_support::thread_function,
                get_lva<this_component_type>::call(lva),
                _1, base_type::wrap_action(std::move(f), lva));
        }

    protected:
        struct scoped_pinner
        {
            scoped_pinner(migration_support& outer)
              : outer_(outer)
            {
                outer.pin();
            }
            ~scoped_pinner()
            {
                outer_.unpin();
            }

            migration_support& outer_;
        };

        // Execute the wrapped action. This pins the object making sure that
        // no migration will happen while an operation is in flight.
        threads::thread_state_enum thread_function(
            threads::thread_state_ex_enum state,
            HPX_STD_FUNCTION<threads::thread_function_type> const& f)
        {
            scoped_pinner sp(*this);
            return f(state);
        }

    private:
        mutable mutex_type mtx_;
        boost::uint32_t pin_count_;
    };
}}

#endif
