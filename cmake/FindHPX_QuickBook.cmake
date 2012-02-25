# Copyright (c) 2011-2012 Bryce Adelstein-Lelbach
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

if(NOT HPX_FINDPROGRAM_LOADED)
  include(HPX_FindProgram)
endif()

if(BOOST_USE_SYSTEM)
  set(QUICKBOOK_USE_SYSTEM ON)
endif()

if(BOOST_ROOT)
  set(QUICKBOOK_ROOT ${BOOST_ROOT})
else()
  if($ENV{BOOST_ROOT})
    set(QUICKBOOK_ROOT $ENV{BOOST_ROOT})
  endif()
endif()

hpx_find_program(QUICKBOOK
  PROGRAMS quickbook
  PROGRAM_PATHS bin dist/bin)

