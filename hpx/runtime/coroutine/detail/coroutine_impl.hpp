//  Copyright (c) 2006, Giovanni P. Deretta
//  Copyright (c) 2007-2013 Hartmut Kaiser
//
//  This code may be used under either of the following two licences:
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
//  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE. OF SUCH DAMAGE.
//
//  Or:
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef HPX_RUNTIME_COROUTINE_DETAIL_COROUTINE_IMPL_HPP
#define HPX_RUNTIME_COROUTINE_DETAIL_COROUTINE_IMPL_HPP

#if defined(HPX_MSVC)
#pragma warning (push)
#pragma warning (disable: 4355) //this used in base member initializer
#endif

#include <hpx/config.hpp>
#include <hpx/runtime/coroutine/detail/config.hpp>
#include <hpx/runtime/coroutine/detail/context_base.hpp>
#include <hpx/runtime/coroutine/detail/coroutine_accessor.hpp>
#include <hpx/runtime/coroutine/detail/coroutine_self.hpp>
#include <hpx/runtime/naming/id_type.hpp>
#include <hpx/runtime/threads/thread_enums.hpp>
#include <hpx/util/assert.hpp>
#include <hpx/util/reinitializable_static.hpp>
#include <hpx/util/unique_function.hpp>

#include <boost/exception_ptr.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/lockfree/stack.hpp>

#include <cstddef>
#include <utility>

namespace hpx { namespace coroutines { namespace detail
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Coroutine>
    struct coroutine_heap
    {
        coroutine_heap()
          : heap_(128)
        {}

        ~coroutine_heap()
        {
            while (Coroutine* next = get_locked())
                delete next;
        }

        Coroutine* allocate()
        {
            return get_locked();
        }

        Coroutine* try_allocate()
        {
            return get_locked();
        }

        void deallocate(Coroutine* p)
        {
            //p->reset();          // reset bound function
            heap_.push(p);
        }

    private:
        Coroutine* get_locked()
        {
            Coroutine* result = 0;
            heap_.pop(result);
            return result;
        }

        boost::lockfree::stack<Coroutine*> heap_;
    };

    ///////////////////////////////////////////////////////////////////////////
    // This type augments the context_base type with the type of the stored
    // functor.
    template <typename CoroutineType>
    class coroutine_impl
      : public context_base
    {
    public:
        typedef CoroutineType coroutine_type;
        typedef coroutine_impl<coroutine_type> type;
        typedef context_base super_type;
        typedef typename coroutine_type::result_type result_type;
        typedef typename coroutine_type::arg_type arg_type;
        typedef typename context_base::thread_id_repr_type thread_id_repr_type;

        typedef util::unique_function_nonser<
            threads::thread_state_enum(threads::thread_state_ex_enum)
        > functor_type;

        typedef boost::intrusive_ptr<type> pointer;

        coroutine_impl(functor_type&& f, naming::id_type&& target,
            thread_id_repr_type id, std::ptrdiff_t stack_size)
          : context_base(*this, stack_size, id)
          , m_arg(0)
          , m_result(0)
          , m_fun(std::move(f))
          , target_(std::move(target))
        {}

        ~coroutine_impl()
        {
            HPX_ASSERT(!m_fun);   // functor should have been reset by now
            HPX_ASSERT(!target_);
        }

        static inline coroutine_impl* create(
            functor_type&& f,
            naming::id_type&& target, thread_id_repr_type id = 0,
            std::ptrdiff_t stack_size = default_stack_size)
        {
            // start looking at the matching heap
            std::size_t const heap_count = get_heap_count(stack_size);
            std::size_t const heap_num = std::size_t(id) / 32; //-V112

            // look through all heaps to find an available coroutine object
            coroutine_impl* p = allocate(heap_num, stack_size);
            if (0 == p)
            {
                for (std::size_t i = 1; i != heap_count && !p; ++i)
                {
                    p = try_allocate(heap_num + i, stack_size);
                }
            }

            // allocate a new coroutine object, if non is available (or all heaps are locked)
            if (NULL == p)
            {
                context_base::increment_allocation_count(heap_num);
                return new coroutine_impl(std::move(f), std::move(target),
                    id, stack_size);
            }

            // if we reuse an existing  object, we need to rebind its function
            p->rebind(std::move(f), std::move(target), id);
            return p;
        }

        static inline void rebind(
            coroutine_impl* p, functor_type&& f,
            naming::id_type&& target, thread_id_repr_type id = 0)
        {
            p->rebind(std::move(f), std::move(target), id);
        }

        static inline void destroy(coroutine_impl* p)
        {
            // always hand the stack back to the matching heap
            deallocate(p, std::size_t(p->get_thread_id()) / 32); //-V112
        }

        void operator()()
        {
            typedef typename super_type::context_exit_status
                context_exit_status;
            context_exit_status status = super_type::ctx_exited_return;

            // loop as long this coroutine has been rebound
            do
            {
                boost::exception_ptr tinfo;
                try
                {
                    this->check_exit_state();

                    HPX_ASSERT(this->count() > 0);

                    typedef typename coroutine_type::self self_type;
                    {
                        self_type* old_self = self_type::get_self();
                        self_type self(this, old_self);
                        reset_self_on_exit on_exit(&self, old_self);

                        this->m_result_last = m_fun(*this->args());

                        // if this thread returned 'terminated' we need to reset the functor
                        // and the bound arguments
                        //
                        // Note: threads::terminated == 5
                        //
                        if (this->m_result_last == 5)
                            this->reset();
                    }

                    // return value to other side of the fence
                    this->bind_result(&this->m_result_last);
                } catch (exit_exception const&) {
                    status = super_type::ctx_exited_exit;
                    tinfo = boost::current_exception();
                    this->reset();            // reset functor
                } catch (boost::exception const&) {
                    status = super_type::ctx_exited_abnormally;
                    tinfo = boost::current_exception();
                    this->reset();
                } catch (std::exception const&) {
                    status = super_type::ctx_exited_abnormally;
                    tinfo = boost::current_exception();
                    this->reset();
                } catch (...) {
                    status = super_type::ctx_exited_abnormally;
                    tinfo = boost::current_exception();
                    this->reset();
                }

                this->do_return(status, tinfo);
            } while (this->m_state == super_type::ctx_running);

            // should not get here, never
            HPX_ASSERT(this->m_state == super_type::ctx_running);
        }

    protected:
        struct reset_self_on_exit
        {
            typedef typename coroutine_type::self self_type;

            reset_self_on_exit(self_type* val, self_type* old_val = 0)
              : old_self(old_val)
            {
                self_type::set_self(val);
            }

            ~reset_self_on_exit()
            {
                self_type::set_self(old_self);
            }

            self_type* old_self;
        };

    public:
        result_type * result()
        {
            HPX_ASSERT(m_result);
            return *this->m_result;
        }

        arg_type * args()
        {
            HPX_ASSERT(m_arg);
            return m_arg;
        };

        void bind_args(arg_type* arg)
        {
            m_arg = arg;
        }

        void bind_result(result_type* res)
        {
            *m_result = res;
        }

        // Another level of indirection is needed to handle
        // yield_to correctly.
        void bind_result_pointer(result_type** resp)
        {
            m_result = resp;
        }

#if defined(HPX_HAVE_THREAD_PHASE_INFORMATION)
        std::size_t get_thread_phase() const
        {
            return this->phase();
        }
#endif

        void reset()
        {
            this->reset_stack();
            m_fun.reset(); // just reset the bound function
            target_ = naming::invalid_id;
            this->super_type::reset();
        }

        void rebind(functor_type && f, naming::id_type && target,
            thread_id_repr_type id)
        {
            this->rebind_stack();     // count how often a coroutines object was reused
            m_fun = std::move(f);
            target_ = std::move(target);
            this->super_type::rebind_base(id);
        }

    private:
        // the memory for the threads is managed by a lockfree caching_freelist
        typedef coroutine_heap<coroutine_impl> heap_type;

        struct heap_tag_small {};
        struct heap_tag_medium {};
        struct heap_tag_large {};
        struct heap_tag_huge {};

        template <std::size_t NumHeaps, typename Tag>
        static heap_type& get_heap(std::size_t i)
        {
            // ensure thread-safe initialization
            util::reinitializable_static<heap_type, Tag, NumHeaps> heap;
            return heap.get(i);
        }

        static heap_type& get_heap(std::size_t i, ptrdiff_t stacksize)
        {
            // FIXME: This should check the sizes in runtime_configuration, not the
            // default macro sizes
            if (stacksize > HPX_MEDIUM_STACK_SIZE)
            {
                if (stacksize > HPX_LARGE_STACK_SIZE)
                    return get_heap<HPX_COROUTINE_NUM_HEAPS / 4,
                    heap_tag_huge>(i % (HPX_COROUTINE_NUM_HEAPS / 4)); //-V112

                return get_heap<HPX_COROUTINE_NUM_HEAPS / 4,
                    heap_tag_large>(i % (HPX_COROUTINE_NUM_HEAPS / 4)); //-V112
            }

            if (stacksize > HPX_SMALL_STACK_SIZE)
                return get_heap<HPX_COROUTINE_NUM_HEAPS / 2,
                heap_tag_medium>(i % (HPX_COROUTINE_NUM_HEAPS / 2));

            return get_heap<HPX_COROUTINE_NUM_HEAPS,
                heap_tag_small>(i % HPX_COROUTINE_NUM_HEAPS);
        }

        static std::size_t get_heap_count(ptrdiff_t stacksize)
        {
            if (stacksize > HPX_MEDIUM_STACK_SIZE)
                return HPX_COROUTINE_NUM_HEAPS / 4; //-V112

            if (stacksize > HPX_SMALL_STACK_SIZE)
                return HPX_COROUTINE_NUM_HEAPS / 2;

            return HPX_COROUTINE_NUM_HEAPS;
        }

        static coroutine_impl* allocate(std::size_t i, ptrdiff_t stacksize)
        {
            return get_heap(i, stacksize).allocate();
        }

        static coroutine_impl* try_allocate(std::size_t i, ptrdiff_t stacksize)
        {
            return get_heap(i, stacksize).try_allocate();
        }

        static void deallocate(coroutine_impl* wrapper, std::size_t i)
        {
            ptrdiff_t stacksize = wrapper->get_stacksize();
            get_heap(i, stacksize).deallocate(wrapper);
        }

#if defined(_DEBUG)
        static heap_type const* get_first_heap_address(ptrdiff_t stacksize)
        {
            return &get_heap(0, stacksize);
        }
#endif

    private:
        result_type m_result_last;
        arg_type* m_arg;
        result_type** m_result;

        functor_type m_fun;
        naming::id_type target_;        // keep target alive, if needed
    };
}}}

#if defined(HPX_MSVC)
#pragma warning(pop)
#endif

#endif /*HPX_RUNTIME_COROUTINE_DETAIL_COROUTINE_IMPL_HPP*/
