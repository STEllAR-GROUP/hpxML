//  Copyright (c) 2007-2017 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

/// \file hpx/runtime/launch_policy.hpp

#if !defined(HPX_RUNTIME_LAUNCH_POLICY_AUG_13_2015_0647PM)
#define HPX_RUNTIME_LAUNCH_POLICY_AUG_13_2015_0647PM

#include <hpx/config.hpp>
#include <hpx/runtime/threads/thread_enums.hpp>
#include <hpx/runtime/serialization/serialization_fwd.hpp>

namespace hpx
{
    /// \cond NOINTERNAL
    namespace detail
    {
        enum class launch_policy
        {
            async = 0x01,
            deferred = 0x02,
            task = 0x04,  // see N3632
            sync = 0x08,
            fork = 0x10,  // same as async, but forces continuation stealing
            apply = 0x20,

            sync_policies = 0x0a,       // sync | deferred
            async_policies = 0x15,      // async | task | fork
            all = 0x3f                  // async | deferred | task | sync |
                                        // fork | apply
        };

        struct policy_holder
        {
            HPX_CONSTEXPR explicit policy_holder(launch_policy p,
                    threads::thread_priority priority =
                        threads::thread_priority_default) HPX_NOEXCEPT
              : policy_(p),
                priority_(priority)
            {}

            HPX_CONSTEXPR operator launch_policy() const HPX_NOEXCEPT
            {
                return policy_;
            }

            HPX_CONSTEXPR explicit operator bool() const HPX_NOEXCEPT
            {
                return static_cast<int>(policy_) != 0;
            }

            HPX_CONSTEXPR threads::thread_priority priority() const
            {
                return priority_;
            }

            launch_policy policy_;
            threads::thread_priority priority_;

        private:
            friend class serialization::access;

            HPX_EXPORT void load(serialization::input_archive& ar, unsigned);
            HPX_EXPORT void save(serialization::output_archive& ar, unsigned) const;

            HPX_SERIALIZATION_SPLIT_MEMBER()
        };

        struct async_policy : policy_holder
        {
            HPX_CONSTEXPR async_policy(threads::thread_priority priority =
                    threads::thread_priority_default) HPX_NOEXCEPT
              : policy_holder(launch_policy::async, priority)
            {}

            HPX_CONSTEXPR async_policy operator()(
                threads::thread_priority priority) const HPX_NOEXCEPT
            {
                return async_policy(priority);
            }
        };

        struct fork_policy : policy_holder
        {
            HPX_CONSTEXPR fork_policy(threads::thread_priority priority =
                    threads::thread_priority_boost) HPX_NOEXCEPT
              : policy_holder(launch_policy::fork, priority)
            {}

            HPX_CONSTEXPR fork_policy operator()(
                threads::thread_priority priority) const HPX_NOEXCEPT
            {
                return fork_policy(priority);
            }
        };

        struct sync_policy : policy_holder
        {
            HPX_CONSTEXPR sync_policy() HPX_NOEXCEPT
              : policy_holder(launch_policy::sync)
            {}
        };

        struct deferred_policy : policy_holder
        {
            HPX_CONSTEXPR deferred_policy() HPX_NOEXCEPT
              : policy_holder(launch_policy::deferred)
            {}
        };

        struct apply_policy : policy_holder
        {
            HPX_CONSTEXPR apply_policy() HPX_NOEXCEPT
              : policy_holder(launch_policy::apply)
            {}
        };

        ///////////////////////////////////////////////////////////////////////////
        HPX_CONSTEXPR inline policy_holder
        operator&(policy_holder lhs, policy_holder rhs) HPX_NOEXCEPT
        {
            return policy_holder(static_cast<launch_policy>(
                    static_cast<int>(lhs.policy_) & static_cast<int>(rhs.policy_)
                ));
        }

        HPX_CONSTEXPR inline policy_holder
        operator|(policy_holder lhs, policy_holder rhs) HPX_NOEXCEPT
        {
            return policy_holder(static_cast<launch_policy>(
                    static_cast<int>(lhs.policy_) | static_cast<int>(rhs.policy_)
                ));
        }

        HPX_CONSTEXPR inline policy_holder
        operator^(policy_holder lhs, policy_holder rhs) HPX_NOEXCEPT
        {
            return policy_holder(static_cast<launch_policy>(
                    static_cast<int>(lhs.policy_) ^ static_cast<int>(rhs.policy_)
                ));
        }

        HPX_CONSTEXPR inline policy_holder
        operator~(policy_holder p) HPX_NOEXCEPT
        {
            return policy_holder(static_cast<launch_policy>(
                    ~static_cast<int>(p.policy_)
                ));
        }

        inline policy_holder
        operator&=(policy_holder& lhs, policy_holder rhs) HPX_NOEXCEPT
        {
            lhs = lhs & rhs;
            return lhs;
        }

        inline policy_holder
        operator|=(policy_holder& lhs, policy_holder rhs) HPX_NOEXCEPT
        {
            lhs = lhs | rhs;
            return lhs;
        }

        inline policy_holder
        operator^=(policy_holder& lhs, policy_holder rhs) HPX_NOEXCEPT
        {
            lhs = lhs ^ rhs;
            return lhs;
        }

        HPX_CONSTEXPR inline bool
        operator==(policy_holder lhs, policy_holder rhs) HPX_NOEXCEPT
        {
            return static_cast<int>(lhs.policy_) == static_cast<int>(rhs.policy_);
        }

        HPX_CONSTEXPR inline bool
        operator!=(policy_holder lhs, policy_holder rhs) HPX_NOEXCEPT
        {
            return static_cast<int>(lhs.policy_) != static_cast<int>(rhs.policy_);
        }
    }
    /// \endcond

    ///////////////////////////////////////////////////////////////////////
    /// Launch policies for \a hpx::async etc.
    struct launch : detail::policy_holder
    {
        ///////////////////////////////////////////////////////////////////////
        /// Default constructor. This creates a launch policy representing all
        /// possible launch modes
        HPX_CONSTEXPR launch() HPX_NOEXCEPT
          : detail::policy_holder{detail::launch_policy::all}
        {}

        /// \cond NOINTERNAL
        HPX_CONSTEXPR launch(detail::policy_holder ph) HPX_NOEXCEPT
          : detail::policy_holder{ph}
        {}
        /// \endcond

        /// Create a launch policy representing asynchronous execution
        HPX_CONSTEXPR launch(detail::async_policy) HPX_NOEXCEPT
          : detail::policy_holder{detail::launch_policy::async}
        {}

        /// Create a launch policy representing asynchronous execution. The
        /// new thread is executed in a preferred way
        HPX_CONSTEXPR launch(detail::fork_policy) HPX_NOEXCEPT
          : detail::policy_holder{detail::launch_policy::fork}
        {}

        /// Create a launch policy representing synchronous execution
        HPX_CONSTEXPR launch(detail::sync_policy) HPX_NOEXCEPT
          : detail::policy_holder{detail::launch_policy::sync}
        {}

        /// Create a launch policy representing deferred execution
        HPX_CONSTEXPR launch(detail::deferred_policy) HPX_NOEXCEPT
          : detail::policy_holder{detail::launch_policy::deferred}
        {}

        /// Create a launch policy representing fire and forget execution
        HPX_CONSTEXPR launch(detail::apply_policy) HPX_NOEXCEPT
          : detail::policy_holder{detail::launch_policy::apply}
        {}

        ///////////////////////////////////////////////////////////////////////
        /// \cond NOINTERNAL
        using async_policy = detail::async_policy;
        using fork_policy = detail::fork_policy;
        using sync_policy = detail::sync_policy;
        using deferred_policy = detail::deferred_policy;
        using apply_policy = detail::apply_policy;
        /// \endcond

        ///////////////////////////////////////////////////////////////////////
        /// Predefined launch policy representing asynchronous execution
        HPX_EXPORT static const detail::async_policy async;

        /// Predefined launch policy representing asynchronous execution.The
        /// new thread is executed in a preferred way
        HPX_EXPORT static const detail::fork_policy fork;

        /// Predefined launch policy representing synchronous execution
        HPX_EXPORT static const detail::sync_policy sync;

        /// Predefined launch policy representing deferred execution
        HPX_EXPORT static const detail::deferred_policy deferred;

        /// Predefined launch policy representing fire and forget execution
        HPX_EXPORT static const detail::apply_policy apply;

        /// \cond NOINTERNAL
        HPX_EXPORT static const detail::policy_holder all;
        HPX_EXPORT static const detail::policy_holder sync_policies;
        HPX_EXPORT static const detail::policy_holder async_policies;
    };

    ///////////////////////////////////////////////////////////////////////////
    /// \cond NOINTERNAL
    namespace detail
    {
        HPX_FORCEINLINE HPX_CONSTEXPR
        bool has_async_policy(launch p) HPX_NOEXCEPT
        {
            return bool(
                p & detail::policy_holder{detail::launch_policy::async_policies}
            );
        }
    }
    /// \endcond
}

#endif
