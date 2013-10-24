//  Copyright (c) 2006, Giovanni P. Deretta
//  Copyright (c) 2007 Robert Perricone
//  Copyright (c) 2007-2012 Hartmut Kaiser
//  Copyright (c) 2011 Bryce Adelstein-Lelbach
//  Copyright (c) 2013 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef HPX_COROUTINE_CONTEXT_LINUX_HPP_20071126
#define HPX_COROUTINE_CONTEXT_LINUX_HPP_20071126

#if defined(__linux) || defined(linux) || defined(__linux__)

#include <sys/param.h>
#include <cstdlib>
#include <cstddef>
#include <stdexcept>

#include <boost/format.hpp>
#include <boost/cstdint.hpp>
#include <boost/assert.hpp>
#include <boost/atomic.hpp>

#include <hpx/config/forceinline.hpp>
#include <hpx/util/coroutine/detail/config.hpp>
#include <hpx/util/coroutine/detail/posix_utility.hpp>
#include <hpx/util/coroutine/detail/swap_context.hpp>
#include <hpx/util/get_and_reset_value.hpp>

#if defined(HPX_HAVE_VALGRIND)
#if defined(__GNUG__) && !defined(__INTEL_COMPILER)
#if defined(HPX_GCC_DIAGNOSTIC_PRAGMA_CONTEXTS)
#pragma GCC diagnostic push
#endif
#pragma GCC diagnostic ignored "-Wpointer-arith"
#endif
#include <valgrind/valgrind.h>
#endif

/*
 * Defining HPX_COROUTINE_NO_SEPARATE_CALL_SITES will disable separate
 * invoke, yield and yield_to swap_context functions. Separate calls sites
 * increase performance by 25% at least on P4 for invoke+yield back loops
 * at the cost of a slightly higher instruction cache use and is thus enabled by
 * default.
 */

#if defined(__x86_64__)
extern "C" void swapcontext_stack (void***, void**) throw();
extern "C" void swapcontext_stack2 (void***, void**) throw();
extern "C" void swapcontext_stack3 (void***, void**) throw();
#else
extern "C" void swapcontext_stack (void***, void**) throw() __attribute((regparm(2)));
extern "C" void swapcontext_stack2 (void***, void**) throw()__attribute((regparm(2)));
extern "C" void swapcontext_stack3 (void***, void**) throw()__attribute((regparm(2)));
#endif

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace util { namespace coroutines 
{

  // some platforms need special preparation of the main thread
  struct prepare_main_thread
  {
      prepare_main_thread() {}
      ~prepare_main_thread() {}
  };

  namespace detail { namespace lx
  {
    template <typename TO, typename FROM> 
    TO nasty_cast(FROM f)
    {
      union {
        FROM f; TO t;
      } u;
      u.f = f;
      return u.t;
    }

    template<typename T>
    BOOST_FORCEINLINE void trampoline(T* fun);

    template<typename T>
    void trampoline(T* fun)
    {
      (*fun)();
      std::abort();
    }

    class x86_linux_context_impl;

    class x86_linux_context_impl_base : detail::context_impl_base
    {
    public:
      x86_linux_context_impl_base() {}

      void prefetch() const
      {
#if defined(__x86_64__)
        BOOST_ASSERT(sizeof(void*) == 8);
#else
        BOOST_ASSERT(sizeof(void*) == 4);
#endif

        __builtin_prefetch (m_sp, 1, 3);
        __builtin_prefetch (m_sp, 0, 3);
        __builtin_prefetch (static_cast<void**>(m_sp)+64/sizeof(void*), 1, 3);
        __builtin_prefetch (static_cast<void**>(m_sp)+64/sizeof(void*), 0, 3);
#if !defined(__x86_64__)
        __builtin_prefetch (static_cast<void**>(m_sp)+32/sizeof(void*), 1, 3);
        __builtin_prefetch (static_cast<void**>(m_sp)+32/sizeof(void*), 0, 3);
        __builtin_prefetch (static_cast<void**>(m_sp)-32/sizeof(void*), 1, 3);
        __builtin_prefetch (static_cast<void**>(m_sp)-32/sizeof(void*), 0, 3);
#endif
        __builtin_prefetch (static_cast<void**>(m_sp)-64/sizeof(void*), 1, 3);
        __builtin_prefetch (static_cast<void**>(m_sp)-64/sizeof(void*), 0, 3);
      }

      /**
       * Free function. Saves the current context in @p from
       * and restores the context in @p to.
       * @note This function is found by ADL.
       */
      friend void swap_context(x86_linux_context_impl_base& from,
          x86_linux_context_impl const& to, default_hint);

      friend void swap_context(x86_linux_context_impl& from,
          x86_linux_context_impl_base const& to, yield_hint);

      friend void swap_context(x86_linux_context_impl& from,
          x86_linux_context_impl_base const& to, yield_to_hint);

    protected:
      void ** m_sp;
    };

    class x86_linux_context_impl : public x86_linux_context_impl_base
    {
    public:
      enum { default_stack_size = 4*EXEC_PAGESIZE };

      typedef x86_linux_context_impl_base context_impl_base;

      x86_linux_context_impl()
        : m_stack(0)
      {}

      /**
       * Create a context that on restore invokes Functor on
       *  a new stack. The stack size can be optionally specified.
       */
      template<typename Functor>
      x86_linux_context_impl(Functor& cb, std::ptrdiff_t stack_size = -1)
        : m_stack_size(stack_size == -1
                      ? static_cast<std::ptrdiff_t>(default_stack_size)
                      : stack_size),
          m_stack(0)
      {
        if (0 != (m_stack_size % EXEC_PAGESIZE))
        {
            throw std::runtime_error(
                boost::str(boost::format(
                    "stack size of %1% is not page aligned, page size is %2%")
                    % m_stack_size % EXEC_PAGESIZE));
        }

        if (0 >= m_stack_size)
        {
            throw std::runtime_error(
                boost::str(boost::format("stack size of %1% is invalid") % m_stack_size));
        }

        m_stack = posix::alloc_stack(static_cast<std::size_t>(m_stack_size));
        BOOST_ASSERT(m_stack);
        posix::watermark_stack(m_stack, static_cast<std::size_t>(m_stack_size));
        
        typedef void fun(Functor*);
        fun * funp = trampoline;

        m_cb = &cb;
        m_funp = nasty_cast<void*>(funp);
        init_stack();

#if defined(HPX_HAVE_VALGRIND) && !defined(NVALGRIND)
        valgrind_id = VALGRIND_STACK_REGISTER(m_stack, m_stack + m_stack_size);
#endif
      }

      void init_stack()
      {
        m_sp = (static_cast<void**>(m_stack)
                + static_cast<std::size_t>(m_stack_size)/sizeof(void*))
                - context_size;
        //std::memset(m_sp, 0, context_size * sizeof(std::size_t));
        m_sp[cb_idx]   = m_cb;
        m_sp[funp_idx] = m_funp;
      }

      ~x86_linux_context_impl()
      {
        if(m_stack)
        {
          posix::free_stack(m_stack, static_cast<std::size_t>(m_stack_size));
#if defined(HPX_HAVE_VALGRIND) && !defined(NVALGRIND)
          VALGRIND_STACK_DEREGISTER(valgrind_id);
#endif
        }
      }

      // Return the size of the reserved stack address space.
      std::ptrdiff_t get_stacksize() const
      {
          return m_stack_size;
      }

      void reset_stack()
      {
        if(m_stack) {
          if(posix::reset_stack(m_stack, static_cast<std::size_t>(m_stack_size)))
            increment_stack_unbind_count();
        }
      }

      void rebind_stack()
      {
        if(m_stack) {
          increment_stack_recycle_count();
          // On rebind, we re initialize our stack to ensure a virgin stack
          BOOST_ASSERT(
            m_sp != (static_cast<void**>(m_stack)
                + static_cast<std::size_t>(m_stack_size)/sizeof(void*))
                - context_size);
          init_stack();
          BOOST_ASSERT(
            m_sp == (static_cast<void**>(m_stack)
                + static_cast<std::size_t>(m_stack_size)/sizeof(void*))
                - context_size);
        }
      }

      typedef boost::atomic<boost::int64_t> counter_type;

      static counter_type& get_stack_unbind_counter()
      {
          static counter_type counter(0);
          return counter;
      }
      static boost::uint64_t get_stack_unbind_count(bool reset)
      {
          return util::get_and_reset_value(get_stack_unbind_counter(), reset);
      }
      static boost::uint64_t increment_stack_unbind_count()
      {
          return ++get_stack_unbind_counter();
      }

      static counter_type& get_stack_recycle_counter()
      {
          static counter_type counter(0);
          return counter;
      }
      static boost::uint64_t get_stack_recycle_count(bool reset)
      {
          return util::get_and_reset_value(get_stack_recycle_counter(), reset);
      }
      static boost::uint64_t increment_stack_recycle_count()
      {
          return ++get_stack_recycle_counter();
      }

      friend void swap_context(x86_linux_context_impl_base& from,
          x86_linux_context_impl const& to, default_hint);

      friend void swap_context(x86_linux_context_impl& from,
          x86_linux_context_impl_base const& to, yield_hint);

      friend void swap_context(x86_linux_context_impl& from,
          x86_linux_context_impl_base const& to, yield_to_hint);

      // global functions to be called for each OS-thread after it started
      // running and before it exits
      static void thread_startup(char const* /*thread_type*/)
      {
      }

      static void thread_shutdown()
      {
      }

    private:
#if defined(__x86_64__)
      /** structure of context_data:
       * 11: additional alignment
       * 10: parm 0 of trampoline
       * 9:  dummy return address for trampoline
       * 8:  return addr (here: start addr)
       * 7:  rbp
       * 6:  rbx
       * 5:  rsi
       * 4:  rdi
       * 3:  r12
       * 2:  r13
       * 1:  r14
       * 0:  r15
       **/
      static const std::size_t context_size = 12;
      static const std::size_t cb_idx = 10;
      static const std::size_t funp_idx = 8;
#else
      /** structure of context_data:
       * 6: parm 0 of trampoline
       * 5: dummy return address for trampoline
       * 4: return addr (here: start addr)
       * 3: ebp
       * 2: ebx
       * 1: esi
       * 0: edi
       **/
      static const std::size_t context_size = 7;
      static const std::size_t cb_idx = 6;
      static const std::size_t funp_idx = 4;
#endif
      std::ptrdiff_t m_stack_size;
      void * m_stack;
      void * m_cb;
      void * m_funp;
#if defined(HPX_HAVE_VALGRIND) && !defined(NVALGRIND)
      unsigned valgrind_id;
#endif
    };

    typedef x86_linux_context_impl context_impl;

    /**
     * Free function. Saves the current context in @p from
     * and restores the context in @p to.
     * @note This function is found by ADL.
     */
    inline void swap_context(x86_linux_context_impl_base& from,
        x86_linux_context_impl const& to, default_hint)
    {
//        BOOST_ASSERT(*(void**)to.m_stack == (void*)~0);
        to.prefetch();
        swapcontext_stack(&from.m_sp, to.m_sp);
    }

    inline void swap_context(x86_linux_context_impl& from,
        x86_linux_context_impl_base const& to, yield_hint)
    {
//        BOOST_ASSERT(*(void**)from.m_stack == (void*)~0);
        to.prefetch();
#ifndef HPX_COROUTINE_NO_SEPARATE_CALL_SITES
        swapcontext_stack2(&from.m_sp, to.m_sp);
#else
        swapcontext_stack(&from.m_sp, to.m_sp);
#endif
    }

    inline void swap_context(x86_linux_context_impl& from,
        x86_linux_context_impl_base const& to, yield_to_hint)
    {
//        BOOST_ASSERT(*(void**)from.m_stack == (void*)~0);
        to.prefetch();
#ifndef HPX_COROUTINE_NO_SEPARATE_CALL_SITES
        swapcontext_stack3(&from.m_sp, to.m_sp);
#else
        swapcontext_stack(&from.m_sp, to.m_sp);
#endif
    }

  }

}}}}

#if defined(HPX_HAVE_VALGRIND)
#if defined(__GNUG__) && !defined(__INTEL_COMPILER)
#if defined(HPX_GCC_DIAGNOSTIC_PRAGMA_CONTEXTS)
#pragma GCC diagnostic pop
#endif
#endif
#endif

#else

#error This header can only be included when compiling for linux systems.

#endif

#endif

