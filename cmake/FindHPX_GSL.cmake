# Copyright (c) 2011 Bryce Lelbach
# Copyright (c) 2011 Matt Anderson
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

if(NOT HPX_FINDPACKAGE_LOADED)
  include(HPX_FindPackage)
endif()

if(GSL_USE_SYSTEM)
  set(GSLCBLAS_CPP_USE_SYSTEM ON)
endif()

if(GSL_ROOT)
  set(GSLCBLAS_ROOT ${GSL_ROOT})
endif()

hpx_find_package(GSL
  LIBRARIES gsl libgsl 
  LIBRARY_PATHS lib64 lib
  HEADERS gsl_test.h
  HEADER_PATHS include include/gsl)

hpx_find_package(GSLCBLAS
  LIBRARIES gslcblas libgslcblas
  LIBRARY_PATHS lib64 lib
  HEADERS gsl_test.h
  HEADER_PATHS include include/gsl)

