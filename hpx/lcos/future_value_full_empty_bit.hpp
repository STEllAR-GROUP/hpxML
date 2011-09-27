//  Copyright (c) 2007-2011 Hartmut Kaiser
//  Copyright (c) 2011      Bryce Adelstein-Lelbach
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_LCOS_FUTURE_VALUE_FULL_EMPTY_FEB_03_2009_0841AMM)
#define HPX_LCOS_FUTURE_VALUE_FULL_EMPTY_FEB_03_2009_0841AMM

#include <hpx/hpx_fwd.hpp>
#include <hpx/runtime/applier/applier.hpp>
#include <hpx/runtime/threads/thread.hpp>
#include <hpx/runtime/actions/component_action.hpp>
#include <hpx/runtime/components/component_type.hpp>
#include <hpx/runtime/components/server/managed_component_base.hpp>
#include <hpx/lcos/base_lco.hpp>
#include <hpx/lcos/get_result.hpp>
#include <hpx/util/full_empty_memory.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/variant.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/identity.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace lcos { namespace detail 
{
    /// A future_value can be used by a single thread to invoke a (remote) 
    /// action and wait for the result. 
    template <typename Result, typename RemoteResult, int N>
    class future_value : public lcos::base_lco_with_value<Result, RemoteResult>
    {
    private:
        // make sure N is in a reasonable range
        BOOST_STATIC_ASSERT(N > 0);   // N must be greater than zero

    protected:
        typedef Result result_type;
        typedef boost::exception_ptr error_type;
        typedef boost::variant<result_type, error_type> data_type;

    public:
        // This is the component id. Every component needs to have an embedded
        // enumerator 'value' which is used by the generic action implementation
        // to associate this component with a given action.
        enum { value = components::component_future };

        future_value() {}

        /// Reset the future_value to allow to restart an asynchronous 
        /// operation. Allows any subsequent set_data operation to succeed.
        void reset()
        {
            data_->set_empty();
        }

        /// Return whether or not the data is available for this
        /// \a future_value.
        bool ready() const
        {
            return !(data_->is_empty());
        }

        /// Get the result of the requested action. This call blocks (yields 
        /// control) if the result is not ready. As soon as the result has been 
        /// returned and the waiting thread has been re-scheduled by the thread
        /// manager the function \a lazy_future#get will return.
        ///
        /// \param slot   [in] The number of the slot the value has to be 
        ///               returned for. This number must be positive, but 
        ///               smaller than the template parameter \a N.
        /// \param self   [in] The \a thread which will be unconditionally
        ///               blocked (yielded) while waiting for the result. 
        /// \param ec     [in,out] this represents the error status on exit,
        ///               if this is pre-initialized to \a hpx#throws
        ///               the function will throw on error instead. If the
        ///               operation blocks and is aborted because the object
        ///               went out of scope, the code \a hpx#yield_aborted is
        ///               set or thrown. 
        ///
        /// \note         If there has been an error reported (using the action
        ///               \a base_lco#set_error), this function will throw an
        ///               exception encapsulating the reported error code and 
        ///               error description if <code>&ec == &throws</code>.
        Result get_data(int slot, error_code& ec = throws) 
        {
            if (slot < 0 || slot >= N) {
                HPX_THROWS_IF(ec, bad_parameter, 
                    "future_value<Result, N>::get_data", "slot index out of range");
                return Result();
            }

            // yields control if needed
            data_type d;
            data_[slot].read(d, ec);
            if (ec) return Result();    

            // the thread has been re-activated by one of the actions 
            // supported by this future_value (see \a future_value::set_event
            // and future_value::set_error).
            if (1 == d.which())
            {
                // an error has been reported in the meantime, throw or set
                // the error code 
                error_type e = boost::get<error_type>(d);
                if (&ec == &throws) {
                    // REVIEW: should HPX_RETHROW_EXCEPTION be used instead?
                    boost::rethrow_exception(e);
                    // never reached
                }
                else {
                    try {
                        boost::rethrow_exception(e);
                    }
                    catch (hpx::exception const& he) {
                        ec = make_error_code(he.get_error(), he.what(), 
                            hpx::rethrow);
                    }
                }       
                return Result();
            }

            if (&ec != &throws)
                ec = make_success_code();

            // no error has been reported, return the result
            return boost::get<result_type>(d);
        }

        // helper functions for setting data (if successful) or the error (if
        // non-successful)
        void set_data(int slot, RemoteResult const& result)
        {
            // set the received result, reset error status
            if (slot < 0 || slot >= N) {
                HPX_THROW_EXCEPTION(bad_parameter, 
                    "future_value::set_data<Result, N>", 
                    "slot index out of range");
                return;
            }

            // store the value
            data_[slot].set(
                data_type(get_result<Result, RemoteResult>::call(result)));
        }

        // trigger the future with the given error condition
        void set_error(int slot, boost::exception_ptr const& e)
        {
            if (slot < 0 || slot >= N) {
                HPX_THROW_EXCEPTION(bad_parameter, 
                    "future_value<Result, N>::set_error", 
                    "slot index out of range");
                return;
            }

            // store the error code
            data_[slot].set(data_type(e));
        }

        ///////////////////////////////////////////////////////////////////////
        // exposed functionality of this component

        // trigger the future, set the result
        void set_result (RemoteResult const& result)
        {
            set_data(0, result);    // set the received result, reset error status
        }

        void set_error (boost::exception_ptr const& e)
        {
            set_error(0, e);        // set the received error
        }

        Result get_value()
        {
            return get_data(0);
        }

        template <typename ManagedType>
        naming::id_type const& get_gid(ManagedType* p) const
        {
            if (!id_) {
                naming::gid_type gid = p->get_base_gid(); 
                naming::strip_credit_from_gid(gid);
                id_ = naming::id_type(gid, naming::id_type::unmanaged);
            }
            return id_;
        }

    private:
        util::full_empty<data_type> data_[N];
        mutable naming::id_type id_;
    };

    ///////////////////////////////////////////////////////////////////////////
    /// A future_value can be used by a single thread to invoke a (remote) 
    /// action and wait for the result. This specialization wraps the result
    /// value (a gid_type) into a managed id_type.
    template <int N>
    class future_value<naming::id_type, naming::gid_type, N>
      : public lcos::base_lco_with_value<naming::id_type, naming::gid_type>
    {
    private:
        // make sure N is in a reasonable range
        BOOST_STATIC_ASSERT(N > 0);   // N must be greater than zero

    protected:
        typedef naming::id_type result_type;
        typedef boost::exception_ptr error_type;
        typedef boost::variant<result_type, error_type> data_type;

    public:
        future_value() {}

        /// Reset the future_value to allow to restart an asynchronous 
        /// operation. Allows any subsequent set_data operation to succeed.
        void reset()
        {
            data_->set_empty();
        }

        /// Return whether or not the data is available for this
        /// \a future_value.
        bool ready()
        {
            return !(data_->is_empty());
        }

        /// Get the result of the requested action. This call blocks (yields 
        /// control) if the result is not ready. As soon as the result has been 
        /// returned and the waiting thread has been re-scheduled by the thread
        /// manager the function \a lazy_future#get will return.
        ///
        /// \param slot   [in] The number of the slot the value has to be 
        ///               returned for. This number must be positive, but 
        ///               smaller than the template parameter \a N.
        /// \param self   [in] The \a thread which will be unconditionally
        ///               blocked (yielded) while waiting for the result. 
        /// \param ec     [in,out] this represents the error status on exit,
        ///               if this is pre-initialized to \a hpx#throws
        ///               the function will throw on error instead. If the
        ///               operation blocks and is aborted because the object
        ///               went out of scope, the code \a hpx#yield_aborted is
        ///               set or thrown. 
        ///
        /// \note         If there has been an error reported (using the action
        ///               \a base_lco#set_error), this function will throw an
        ///               exception encapsulating the reported error code and 
        ///               error description if <code>&ec == &throws</code>.
        result_type get_data(int slot, error_code& ec = throws) 
        {
            if (slot < 0 || slot >= N) {
                HPX_THROWS_IF(ec, bad_parameter, 
                    "future_value<Result, N>::get_data", "slot index out of range");
                return naming::invalid_id;
            }

            // yields control if needed
            data_type d;
            data_[slot].read(d, ec);
            if (ec) return naming::invalid_id;  

            // the thread has been re-activated by one of the actions 
            // supported by this future_value (see \a future_value::set_event
            // and future_value::set_error).
            if (1 == d.which())
            {
                // an error has been reported in the meantime, throw or set
                // the error code 
                error_type e = boost::get<error_type>(d);
                if (&ec == &throws) {
                    // REVIEW: should HPX_RETHROW_EXCEPTION be used instead?
                    boost::rethrow_exception(e);
                    // never reached
                }
                else {
                    try {
                        boost::rethrow_exception(e);
                    }
                    catch (hpx::exception const& he) {
                        ec = make_error_code(he.get_error(), he.what(), 
                            hpx::rethrow);
                    }
                }       
                return naming::invalid_id;
            }

            if (&ec != &throws)
                ec = make_success_code();

            // no error has been reported, return the result
            return boost::get<naming::id_type>(d);
        }

        // helper functions for setting data (if successful) or the error (if
        // non-successful)
        void set_data(int slot, naming::gid_type const& result)
        {
            // set the received result, reset error status
            if (slot < 0 || slot >= N) {
                HPX_THROW_EXCEPTION(bad_parameter, 
                    "future_value::set_data<Result, N>", 
                    "slot index out of range");
                return;
            }

            // store the value as a managed id
            data_[slot].set(
                data_type(naming::id_type(result, naming::id_type::managed)));
        }

        // trigger the future with the given error condition
        void set_error(int slot, boost::exception_ptr const& e)
        {
            if (slot < 0 || slot >= N) {
                HPX_THROW_EXCEPTION(bad_parameter, 
                    "future_value<Result, N>::set_error", 
                    "slot index out of range");
                return;
            }

            // store the error code
            data_[slot].set(data_type(e));
        }

        ///////////////////////////////////////////////////////////////////////
        // exposed functionality of this component

        // trigger the future, set the result
        void set_result (naming::gid_type const& result)
        {
            set_data(0, result);    // set the received result, reset error status
        }

        void set_error (boost::exception_ptr const& e)
        {
            set_error(0, e);        // set the received error
        }

        result_type get_value()
        {
            return get_data(0);
        }

        template <typename ManagedType>
        naming::id_type const& get_gid(ManagedType* p) const
        {
            if (!id_) {
                naming::gid_type gid = p->get_base_gid(); 
                naming::strip_credit_from_gid(gid);
                id_ = naming::id_type(gid, naming::id_type::unmanaged);
            }
            return id_;
        }

    private:
        util::full_empty<data_type> data_[N];
        mutable naming::id_type id_;
    };

    ///////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct log_on_exit
    {
        log_on_exit(boost::shared_ptr<T> const& impl, error_code const& ec)
          : impl_(impl), ec_(ec)
        {
            LLCO_(info) << "future_value::get(" << impl_->get_gid()
                        << "), throws(" << ((&ec_ == &throws) ? "true" : "false")
                        << ")";
        }
        ~log_on_exit()
        {
            LLCO_(info) << "future_value::got(" << impl_->get_gid() 
                        << "), throws(" << ((&ec_ == &throws) ? "true" : "false")
                        << ")";
        }
        boost::shared_ptr<T> const& impl_;
        error_code const& ec_;
    };
}}}

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace lcos 
{
    ///////////////////////////////////////////////////////////////////////////
    /// \class future_value future_value.hpp hpx/lcos/future_value.hpp
    ///
    /// A future_value can be used by a single \a thread to invoke a 
    /// (remote) action and wait for the result. The result is expected to be 
    /// sent back to the future_value using the LCO's set_event action
    ///
    /// A future_value is one of the simplest synchronization primitives 
    /// provided by HPX. It allows to synchronize on a eager evaluated remote
    /// operation returning a result of the type \a Result. The \a future_value
    /// allows to synchronize exactly one \a thread (the one passed during 
    /// construction time).
    ///
    /// \code
    ///     // Create the future_value (the expected result is a id_type)
    ///     lcos::future_value<naming::id_type> f;
    ///
    ///     // initiate the action supplying the future_value as a 
    ///     // continuation
    ///     applier_.appy<some_action>(new continuation(f.get_gid()), ...);
    ///
    ///     // Wait for the result to be returned, yielding control 
    ///     // in the meantime.
    ///     naming::id_type result = f.get(thread_self);
    ///     // ...
    /// \endcode
    ///
    /// \tparam Result   The template parameter \a Result defines the type this 
    ///                  future_value is expected to return from 
    ///                  \a future_value#get.
    ///
    /// \note            The action executed using the future_value as a 
    ///                  continuation must return a value of a type convertible 
    ///                  to the type as specified by the template parameter 
    ///                  \a Result
    template <typename Result>
    struct future_value_remote_result
      : boost::mpl::identity<Result>
    {};

    template <typename Result>
    struct future_value_local_result 
      : boost::mpl::identity<Result> 
    {};

    ///////////////////////////////////////////////////////////////////////////
    template <typename Result, typename RemoteResult, int N>
    class future_value 
    {
    public:
        typedef detail::future_value<Result, RemoteResult, N> wrapped_type;
        typedef components::managed_component<wrapped_type> wrapping_type;

        /// Construct a new \a future instance. The supplied 
        /// \a thread will be notified as soon as the result of the 
        /// operation associated with this future instance has been 
        /// returned.
        /// 
        /// \note         The result of the requested operation is expected to 
        ///               be returned as the first parameter using a 
        ///               \a base_lco#set_result action. Any error has to be 
        ///               reported using a \a base_lco::set_error action. The 
        ///               target for either of these actions has to be this 
        ///               future instance (as it has to be sent along 
        ///               with the action as the continuation parameter).
        future_value()
          : impl_(new wrapping_type(new wrapped_type()))
        {
            LLCO_(info) << "future_value::future_value(" << impl_->get_gid() << ")";
        }

        /// Reset the future_value to allow to restart an asynchronous 
        /// operation. Allows any subsequent set_data operation to succeed.
        void reset()
        {
            (*impl_)->reset();
        }

        /// \brief Return the global id of this \a future instance
        naming::id_type const& get_gid() const
        {
            return (*impl_)->get_gid(impl_.get());
        }

        /// Return whether or not the data is available for this
        /// \a future_value.
        bool ready() const
        {
            return (*impl_)->ready();
        }

        typedef Result result_type;

        ~future_value()
        {}

        /// Get the result of the requested action. This call blocks (yields 
        /// control) if the result is not ready. As soon as the result has been 
        /// returned and the waiting thread has been re-scheduled by the thread
        /// manager the function \a eager_future#get will return.
        ///
        /// \param self   [in] The \a thread which will be unconditionally
        ///               blocked (yielded) while waiting for the result. 
        /// \param ec     [in,out] this represents the error status on exit,
        ///               if this is pre-initialized to \a hpx#throws
        ///               the function will throw on error instead. If the
        ///               operation blocks and is aborted because the object
        ///               went out of scope, the code \a hpx#yield_aborted is
        ///               set or thrown. 
        ///
        /// \note         If there has been an error reported (using the action
        ///               \a base_lco#set_error), this function will throw an
        ///               exception encapsulating the reported error code and 
        ///               error description if <code>&ec == &throws</code>.
        Result get(int slot, error_code& ec = throws) const
        {
            detail::log_on_exit<wrapping_type> on_exit(impl_, ec);
            return (*impl_)->get_data(slot, ec);
        }

        Result get(error_code& ec = throws) const
        {
            detail::log_on_exit<wrapping_type> on_exit(impl_, ec);
            return (*impl_)->get_data(0, ec);
        }

        void invalidate(int slot, boost::exception_ptr const& e)
        {
            (*impl_)->set_error(slot, e); // set the received error
        }

        void invalidate(boost::exception_ptr const& e)
        {
            (*impl_)->set_error(0, e); // set the received error
        }

    protected:
        boost::shared_ptr<wrapping_type> impl_;
    };

    ///////////////////////////////////////////////////////////////////////////
    template <>
    struct future_value_remote_result<void>
      : boost::mpl::identity<util::unused_type>
    {};

    template <>
    struct future_value_local_result<util::unused_type> 
        : boost::mpl::identity<void> 
    {};

    template <int N>
    class future_value<void, util::unused_type, N>
    {
    public:
        typedef detail::future_value<util::unused_type, util::unused_type, N> 
            wrapped_type;
        typedef components::managed_component<wrapped_type> wrapping_type;

        /// Construct a new \a future instance. The supplied 
        /// \a thread will be notified as soon as the result of the 
        /// operation associated with this future instance has been 
        /// returned.
        /// 
        /// \note         The result of the requested operation is expected to 
        ///               be returned as the first parameter using a 
        ///               \a base_lco#set_result action. Any error has to be 
        ///               reported using a \a base_lco::set_error action. The 
        ///               target for either of these actions has to be this 
        ///               future instance (as it has to be sent along 
        ///               with the action as the continuation parameter).
        future_value()
          : impl_(new wrapping_type(new wrapped_type()))
        {
            LLCO_(info) << "future_value<void>::future_value(" << impl_->get_gid() << ")";
        }

        /// Reset the future_value to allow to restart an asynchronous 
        /// operation. Allows any subsequent set_data operation to succeed.
        void reset()
        {
            (*impl_)->reset();
        }

        /// \brief Return the global id of this \a future instance
        naming::id_type const& get_gid() const
        {
            return (*impl_)->get_gid(impl_.get());
        }

        /// Return whether or not the data is available for this
        /// \a future_value.
        bool ready()
        {
            return (*impl_)->ready();
        }

        typedef util::unused_type result_type;

        ~future_value()
        {}

        /// Get the result of the requested action. This call blocks (yields 
        /// control) if the result is not ready. As soon as the result has been 
        /// returned and the waiting thread has been re-scheduled by the thread
        /// manager the function \a eager_future#get will return.
        ///
        /// \param self   [in] The \a thread which will be unconditionally
        ///               blocked (yielded) while waiting for the result. 
        /// \param ec     [in,out] this represents the error status on exit,
        ///               if this is pre-initialized to \a hpx#throws
        ///               the function will throw on error instead.
        ///
        /// \note         If there has been an error reported (using the action
        ///               \a base_lco#set_error), this function will throw an
        ///               exception encapsulating the reported error code and 
        ///               error description if <code>&ec == &throws</code>.
        util::unused_type get(int slot, error_code& ec = throws) const
        {
            detail::log_on_exit<wrapping_type> on_exit(impl_, ec);
            return (*impl_)->get_data(slot, ec);
        }

        util::unused_type get(error_code& ec = throws) const
        {
            detail::log_on_exit<wrapping_type> on_exit(impl_, ec);
            return (*impl_)->get_data(0, ec);
        }

        void invalidate(int slot, boost::exception_ptr const& e)
        {
            (*impl_)->set_error(slot, e); // set the received error
        }

        void invalidate(boost::exception_ptr const& e)
        {
            (*impl_)->set_error(0, e); // set the received error
        }

    protected:
        boost::shared_ptr<wrapping_type> impl_;
    };
}}

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace components
{
    template <typename Result, typename RemoteResult, int N>
    struct component_type_database<
        lcos::detail::future_value<Result, RemoteResult, N> >
    { 
        static component_type get() 
        {
            return component_type_database<
                lcos::base_lco_with_value<Result, RemoteResult> 
            >::get(); 
        }

        static void set(component_type t) 
        {
            component_type_database<
                lcos::base_lco_with_value<Result, RemoteResult> 
            >::set(t); 
        }
    };
}}

#endif
