//  Copyright (c) 2011 Thomas Heller
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/hpx.hpp>
#include <hpx/hpx_init.hpp>
#include <hpx/include/iostreams.hpp>
#include <hpx/util/lightweight_test.hpp>

#if HPX_ACTION_ARGUMENT_LIMIT < 10
#error "Please define HPX_ACTION_ARGUMENT_LIMIT to be at least 10."
#endif
#if HPX_COMPONENT_CREATE_ARG_MAX < 10
#error "Please define HPX_COMPONENT_CREATE_ARG_MAX to be at least 10."
#endif

#include <hpx/components/dataflow/dataflow.hpp>
#include <hpx/components/dataflow/dataflow_trigger.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/stringize.hpp>

using boost::program_options::variables_map;
using boost::program_options::options_description;
using boost::program_options::value;

///////////////////////////////////////////////////////////////////////////////
int f(int i, int j)
{
//     hpx::cout << "f\n" << hpx::flush;
    return i + j;
}
typedef hpx::actions::plain_result_action2<int, int, int, &f> f_action;
HPX_REGISTER_PLAIN_ACTION(f_action);

int h(int i, int j)
{
//     hpx::cout << "h\n" << hpx::flush;
    return i + j;
}
typedef hpx::actions::plain_result_action2<int, int, int, &h> h_action;
HPX_REGISTER_PLAIN_ACTION(h_action);

int g()
{
    static int i = 9000;
//     hpx::cout << "g\n" << hpx::flush;
    return ++i;
}
typedef hpx::actions::plain_result_action0<int, &g> g_action;
HPX_REGISTER_PLAIN_ACTION(g_action);

bool called_trigger = false;
void trigger()
{
    called_trigger = true;
//     hpx::cout << "trigger!\n" << hpx::flush;
}
typedef hpx::actions::plain_action0<&trigger> trigger_action;
HPX_REGISTER_PLAIN_ACTION(trigger_action);

boost::uint64_t id(boost::uint64_t i)
{
    return i;
}
typedef hpx::actions::plain_result_action1<boost::uint64_t, boost::uint64_t, &id> id_action;
HPX_REGISTER_PLAIN_ACTION(id_action);

boost::uint64_t add(boost::uint64_t n1, boost::uint64_t n2)
{
    return n1 + n2;
}
typedef hpx::actions::plain_result_action2<
    boost::uint64_t, boost::uint64_t, boost::uint64_t, &add> add_action;
HPX_REGISTER_PLAIN_ACTION(add_action);

///////////////////////////////////////////////////////////////////////////////
hpx::lcos::dataflow_base<boost::uint64_t> fib(boost::uint64_t n)
{
    if(n < 2)
        return hpx::lcos::dataflow<id_action>(hpx::find_here(), n);
    return hpx::lcos::dataflow<add_action>(hpx::find_here(), fib(n-1), fib(n-2));
}

#define M0(Z, N, D)                                                           \
    bool BOOST_PP_CAT(called_f, N) = false;                                   \
    void BOOST_PP_CAT(f, N)()                                                 \
    {                                                                         \
        /*hpx::cout << BOOST_PP_STRINGIZE(BOOST_PP_CAT(f, N)) << "\n" << hpx::flush;*/\
        BOOST_PP_CAT(called_f, N) = true;                                     \
    }                                                                         \
    typedef hpx::actions::plain_action0<&BOOST_PP_CAT(f, N)>                  \
        BOOST_PP_CAT(BOOST_PP_CAT(f, N), action);                             \
    HPX_REGISTER_PLAIN_ACTION(BOOST_PP_CAT(BOOST_PP_CAT(f, N), action));      \
/**/

BOOST_PP_REPEAT(10, M0, _)

///////////////////////////////////////////////////////////////////////////////
int hpx_main(variables_map & vm)
{
    hpx::naming::id_type here = hpx::find_here();

    {
        boost::uint64_t n = 10;

        hpx::lcos::dataflow<g_action> a(here);
        hpx::lcos::dataflow<g_action> b(here);
        hpx::lcos::dataflow<f_action> c(here, a, b);

        // blocks until the result is delivered! (constructs a promise and sets
        // this as the target of the dataflow)
        HPX_TEST_EQ(18003, c.get());

        hpx::util::high_resolution_timer t;
        boost::uint64_t r = fib(n).get();
        double time = t.elapsed();
        hpx::cout << "fib(" << n << ") = " << r << " calculated in "
                  << time << " seconds\n" << hpx::flush;

        HPX_TEST_EQ(55U, r);
        HPX_TEST_EQ(9005, hpx::lcos::dataflow<h_action>(here, a, 4).get());
        HPX_TEST_EQ(9007, hpx::lcos::dataflow<h_action>(here, 5, b).get());
        HPX_TEST_EQ(9003, hpx::lcos::dataflow<g_action>(here,
            hpx::lcos::dataflow<trigger_action>(here)).get());

        std::vector<hpx::lcos::dataflow_base<void> > trigger;
        trigger.push_back(hpx::lcos::dataflow<f1action>(here));
        trigger.push_back(hpx::lcos::dataflow<f2action>(here));
        trigger.push_back(hpx::lcos::dataflow<f3action>(here));
        trigger.push_back(hpx::lcos::dataflow<f4action>(here));
        trigger.push_back(hpx::lcos::dataflow<f5action>(here));
        trigger.push_back(hpx::lcos::dataflow<f6action>(here));
        trigger.push_back(hpx::lcos::dataflow<f7action>(here));
        trigger.push_back(hpx::lcos::dataflow<f8action>(here));

        hpx::lcos::dataflow<f9action>(
            here, hpx::lcos::dataflow_trigger(here, trigger)).get();
        HPX_TEST(called_trigger);
        HPX_TEST(called_f1);
        HPX_TEST(called_f2);
        HPX_TEST(called_f3);
        HPX_TEST(called_f4);
        HPX_TEST(called_f5);
        HPX_TEST(called_f6);
        HPX_TEST(called_f7);
        HPX_TEST(called_f8);
        HPX_TEST(called_f9);

        hpx::cout << "entering destruction test scope\n" << hpx::flush;
        {
            hpx::lcos::dataflow<f_action>(
                here
              , hpx::lcos::dataflow<g_action>(here)
              , hpx::lcos::dataflow<g_action>(here)
            ).get();

            hpx::lcos::dataflow<f1action>(
                here
              , hpx::lcos::dataflow<f2action>(
                    here
                  , hpx::lcos::dataflow<f3action>(
                        here
                      , hpx::lcos::dataflow<f4action>(
                            here
                        )
                    )
                )
            ).get();
        }
        hpx::cout << "leaving destruction test scope\n" << hpx::flush;
    }
    hpx::cout << "end of hpx_main\n" << hpx::flush;
    hpx::finalize();

    return hpx::util::report_errors();
}

int main(int argc, char ** argv)
{
    options_description cmdline("usage: " HPX_APPLICATION_STRING " [options]");
    return hpx::init(cmdline, argc, argv);
}
