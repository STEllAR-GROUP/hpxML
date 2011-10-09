//  Copyright (c) 2007-2011 Hartmut Kaiser
//  Copyright (c) 2011 Bryce Lelbach
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_CONFIG_MAR_24_2008_0943AM)
#define HPX_CONFIG_MAR_24_2008_0943AM

#include <hpx/version.hpp>
#include <hpx/config/branch_hints.hpp>
#include <hpx/config/manual_profiling.hpp>

///////////////////////////////////////////////////////////////////////////////
// Make sure DEBUG macro is defined consistently across platforms
#if defined(_DEBUG) && !defined(DEBUG)
#  define DEBUG
#endif

///////////////////////////////////////////////////////////////////////////////
#if !defined(HPX_DEBUG) && defined(DEBUG)
#  define HPX_DEBUG 1
#endif

#if !defined(HPX_BUILD_TYPE)
#  if defined(HPX_DEBUG)
#    define HPX_BUILD_TYPE "debug"
#  else
#    define HPX_BUILD_TYPE "release"
#  endif
#endif

///////////////////////////////////////////////////////////////////////////////
/// This is the default ip/port number used by the parcel subsystem
#define HPX_INITIAL_IP_PORT         7910
#define HPX_INITIAL_IP_ADDRESS      "127.0.0.1"
#define HPX_RANDOM_PORT_MIN         26001
#define HPX_RANDOM_PORT_MAX         26132

///////////////////////////////////////////////////////////////////////////////
/// This defines if the Intel Thread Building Blocks library will be used
#if !defined(HPX_USE_TBB)
#  define HPX_USE_TBB 0
#endif

///////////////////////////////////////////////////////////////////////////////
/// This defines the maximum number of possible runtime instances in one 
/// executable
#if !defined(HPX_RUNTIME_INSTANCE_LIMIT)
#  define HPX_RUNTIME_INSTANCE_LIMIT 1
#endif

///////////////////////////////////////////////////////////////////////////////
/// This defines the maximum number of arguments an action can take
#if !defined(HPX_ACTION_ARGUMENT_LIMIT)
#  define HPX_ACTION_ARGUMENT_LIMIT 4
#endif

///////////////////////////////////////////////////////////////////////////////
/// This defines the maximum number of arguments \a hpx#lcos#wait can take
#if !defined(HPX_WAIT_ARGUMENT_LIMIT)
#  define HPX_WAIT_ARGUMENT_LIMIT 4
#endif

///////////////////////////////////////////////////////////////////////////////
/// This defines the maximum number of arguments a component constructor can 
/// take
#if !defined(HPX_COMPONENT_CREATE_ARG_MAX)
#  define HPX_COMPONENT_CREATE_ARG_MAX 4
#endif

///////////////////////////////////////////////////////////////////////////////
/// This defines the number of outgoing (parcel-) connections kept alive 
#if !defined(HPX_MAX_PARCEL_CONNECTION_CACHE_SIZE)
#  define HPX_MAX_PARCEL_CONNECTION_CACHE_SIZE 64
#endif

///////////////////////////////////////////////////////////////////////////////
/// This defines the number of AGAS address translations kept in the local 
/// cache. This is just the initial size which may be adjusted depending on the 
/// load of the system, etc. It must be a minimum of 3 for AGAS v3
/// bootstrapping.
#if !defined(HPX_INITIAL_AGAS_GVA_CACHE_SIZE)
#  define HPX_INITIAL_AGAS_GVA_CACHE_SIZE 256
#endif

///////////////////////////////////////////////////////////////////////////////
/// This defines whether to use the portable binary archives for parcel 
/// serialization
#if !defined(HPX_USE_PORTABLE_ARCHIVES)
#  define HPX_USE_PORTABLE_ARCHIVES 1
#endif

///////////////////////////////////////////////////////////////////////////////
/// This defines the initial global reference count associated with any created 
/// object.
#if !defined(HPX_INITIAL_GLOBALCREDIT)
#  define HPX_INITIAL_GLOBALCREDIT 255
#endif

///////////////////////////////////////////////////////////////////////////////
// This defines the default installation location, should be set by build system
#if !defined(HPX_PREFIX)
#  define HPX_PREFIX "."
#endif

///////////////////////////////////////////////////////////////////////////////
// This defines the maximum number of connect retries to the AGAS service 
// allowing for some leeway during startup of the localities 
#if !defined(HPX_MAX_NETWORK_RETRIES)
#  define HPX_MAX_NETWORK_RETRIES 100
#endif

#if !defined(HPX_NETWORK_RETRIES_SLEEP)
#  define HPX_NETWORK_RETRIES_SLEEP 100
#endif

///////////////////////////////////////////////////////////////////////////////
//  Characters used 
//    - to delimit several HPX ini paths
//    - used as file extensions for shared libraries
//    - used as path delimiters
#ifdef BOOST_WINDOWS  // windows
#  define HPX_INI_PATH_DELIMITER            ";"
#  define HPX_SHARED_LIB_EXTENSION          ".dll"
#  define HPX_PATH_DELIMITERS               "\\/"
#else                 // unix like
#  define HPX_INI_PATH_DELIMITER            ":"
#  define HPX_PATH_DELIMITERS               "/"
#  ifdef __APPLE__    // apple
#    define HPX_SHARED_LIB_EXTENSION        ".dylib"
#  else               // linux & co
#    define HPX_SHARED_LIB_EXTENSION        ".so"
#  endif
#endif

///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_WINDOWS)
#  define HPX_MANGLE_COMPONENT_NAME_PREFIX  libhpx_component_
#  if defined(HPX_DEBUG)
#    define HPX_MANGLE_COMPONENT_NAME(n)                                      \
      BOOST_PP_CAT(BOOST_PP_CAT(HPX_MANGLE_COMPONENT_NAME_PREFIX, n), d)      \
      /**/
#    define HPX_MANGLE_COMPONENT_NAME_STR(n)                                  \
      BOOST_PP_STRINGIZE(HPX_MANGLE_COMPONENT_NAME_PREFIX) + n + "d"          \
      /**/
#    define HPX_MANGLE_NAME(n)                                                \
      BOOST_PP_CAT(BOOST_PP_CAT(lib, n), d)                                   \
      /**/
#  else
#    define HPX_MANGLE_COMPONENT_NAME(n)                                      \
      BOOST_PP_CAT(HPX_MANGLE_COMPONENT_NAME_PREFIX, n)                       \
      /**/
#    define HPX_MANGLE_COMPONENT_NAME_STR(n)                                  \
      BOOST_PP_STRINGIZE(HPX_MANGLE_COMPONENT_NAME_PREFIX) + n                \
      /**/
#    define HPX_MANGLE_NAME(n)                                                \
      BOOST_PP_CAT(lib, n)                                                    \
      /**/
#  endif
#elif defined(HPX_DEBUG)
#  define HPX_MANGLE_COMPONENT_NAME(n)      BOOST_PP_CAT(n, d)
#  define HPX_MANGLE_COMPONENT_NAME_STR(n)  n + "d"
#  define HPX_MANGLE_NAME(n)                BOOST_PP_CAT(n, d)
#else
#  define HPX_MANGLE_COMPONENT_NAME(n)      n
#  define HPX_MANGLE_COMPONENT_NAME_STR(n)  n
#  define HPX_MANGLE_NAME(n)                n
#endif

///////////////////////////////////////////////////////////////////////////////
#if !defined(HPX_COMPONENT_NAME)
# define HPX_COMPONENT_NAME hpx
#endif

///////////////////////////////////////////////////////////////////////////////
#if !defined(HPX_LIBRARY)
#  if defined(HPX_COMPONENT_EXPORTS)
#    define HPX_LIBRARY                                                       \
        BOOST_PP_STRINGIZE(HPX_MANGLE_COMPONENT_NAME(HPX_COMPONENT_NAME))     \
        HPX_SHARED_LIB_EXTENSION                                              \
    /**/
#  else
#    define HPX_LIBRARY                                                       \
        BOOST_PP_STRINGIZE(HPX_MANGLE_NAME(HPX_COMPONENT_NAME))               \
        HPX_SHARED_LIB_EXTENSION                                              \
    /**/
#  endif
#endif

#if !defined(HPX_COMPONENT_STRING)
#  define HPX_COMPONENT_STRING BOOST_PP_STRINGIZE(HPX_COMPONENT_NAME)
#endif

#if !defined(HPX_APPLICATION_NAME)
#  define HPX_APPLICATION_NAME "unknown HPX application"
#endif

#if !defined(HPX_APPLICATION_STRING)
#  define HPX_APPLICATION_STRING BOOST_PP_STRINGIZE(HPX_APPLICATION_NAME)
#endif

///////////////////////////////////////////////////////////////////////////////
#if defined(BOOST_WINDOWS)
#  define snprintf _snprintf
#  if !defined(HPX_EMULATE_SWAP_CONTEXT)
#    define HPX_EMULATE_SWAP_CONTEXT 0
#  endif
#endif

///////////////////////////////////////////////////////////////////////////////
#if !defined(HPX_USE_ITT)
#  define HPX_USE_ITT 0
#endif

///////////////////////////////////////////////////////////////////////////////
// Count number of empty (no PX thread available) thread manager loop executions 
#if !defined(HPX_IDLE_LOOP_COUNT_MAX)
#  define HPX_IDLE_LOOP_COUNT_MAX 20000
#endif

///////////////////////////////////////////////////////////////////////////////
#if !defined(HPX_LOCK_LIMIT)
#  define HPX_LOCK_LIMIT 28
#endif

#if !defined(HPX_WRAPPER_HEAP_STEP)
#  define HPX_WRAPPER_HEAP_STEP 0xFFFFU
#endif

#if !defined(HPX_INITIAL_GID_RANGE)
#  define HPX_INITIAL_GID_RANGE 0xFFFFU
#endif

///////////////////////////////////////////////////////////////////////////////
#if !defined(HPX_DEFAULT_STACK_SIZE)
#  if defined(BOOST_WINDOWS)
#    define HPX_DEFAULT_STACK_SIZE 0x4000
#  else
#    if defined(HPX_DEBUG)
#      define HPX_DEFAULT_STACK_SIZE 0x10000 
#    else
#      define HPX_DEFAULT_STACK_SIZE 0x8000 
#    endif 
#  endif
#endif

///////////////////////////////////////////////////////////////////////////////
// Enable usage of std::unique_ptr instead of std::auto_ptr
#if !defined(HPX_HAVE_CXX11_UNIQUE_PTR)
#  define HPX_UNIQUE_PTR ::std::auto_ptr
#else
#  define HPX_UNIQUE_PTR ::std::unique_ptr
#endif

///////////////////////////////////////////////////////////////////////////////
// make sure Chrono is handled properly
#if defined(HPX_INTERNAL_CHRONO) && BOOST_VERSION < 104700 && !defined(BOOST_CHRONO_NO_LIB)
#  define BOOST_CHRONO_NO_LIB
#endif

///////////////////////////////////////////////////////////////////////////////
#define HPX_AGAS_BOOTSTRAP_PREFIX   1U 
#define HPX_AGAS_PRIMARY_NS_MSB     0x0000000100000001ULL
#define HPX_AGAS_PRIMARY_NS_LSB     0x0000000000000001ULL
#define HPX_AGAS_COMPONENT_NS_MSB   0x0000000100000001ULL
#define HPX_AGAS_COMPONENT_NS_LSB   0x0000000000000002ULL
#define HPX_AGAS_SYMBOL_NS_MSB      0x0000000100000001ULL
#define HPX_AGAS_SYMBOL_NS_LSB      0x0000000000000003ULL

#if !defined(HPX_NO_DEPRECATED)
#  define HPX_DEPRECATED_MSG "This function is deprecated and will be removed in the future."
#  if defined(BOOST_MSVC)
#    define HPX_DEPRECATED(x) __declspec(deprecated(x))
#  elif (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
#    define HPX_DEPRECATED(x) __attribute__((__deprecated__))
#  endif
#  if !defined(HPX_DEPRECATED)
#    define HPX_DEPRECATED(x)  /**/
#  endif
#endif

///////////////////////////////////////////////////////////////////////////////
#include <hpx/config/defaults.hpp>

#endif


