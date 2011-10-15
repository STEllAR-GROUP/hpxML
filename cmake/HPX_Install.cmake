# Copyright (c) 2011 Bryce Lelbach
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying 
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

# Abusive hacks that allow us to have installable targets that are not built
# by default. 

set(HPX_INSTALL_LOADED TRUE)

hpx_include(ParseArguments)

macro(hpx_symlink source destination)
  install(CODE
    "set(symlink_root \"${CMAKE_INSTALL_PREFIX}\")
     execute_process(
       COMMAND \"\${CMAKE_COMMAND}\" -E create_symlink
               \"${source}\" \"${destination}\"
       WORKING_DIRECTORY \"\${symlink_root}\")")
endmacro()

macro(hpx_executable_install name)
  hpx_parse_arguments(${name} "" "ESSENTIAL" ${ARGN})

  set(optional "OPTIONAL")

  if(${name}_ESSENTIAL)
    set(optional "")
  endif()

  get_target_property(location ${name} LOCATION)

  set(install_code
      "file(INSTALL FILES ${location} 
            DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
            TYPE EXECUTABLE 
            ${optional}
            PERMISSIONS OWNER_READ OWNER_EXECUTE OWNER_WRITE
                        GROUP_READ GROUP_EXECUTE
                        WORLD_READ WORLD_EXECUTE)")
  install(CODE "${install_code}")
endmacro()

macro(hpx_library_install lib)
  if(UNIX)
    set(targets ${lib} ${lib}.${HPX_SOVERSION} ${lib}.${HPX_VERSION})
  else()
    set(targets ${lib})
  endif()

  foreach(target ${targets})
    set(install_code
      "file(INSTALL FILES ${CMAKE_BINARY_DIR}/bin/${target}
            DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/hpx
            TYPE SHARED_LIBRARY 
            OPTIONAL
            PERMISSIONS OWNER_READ OWNER_EXECUTE OWNER_WRITE
                        GROUP_READ GROUP_EXECUTE
                        WORLD_READ WORLD_EXECUTE)")
    install(CODE "${install_code}")
  endforeach()
endmacro()

macro(hpx_archive_install lib)
  set(install_code
    "file(INSTALL FILES ${CMAKE_BINARY_DIR}/bin/${lib}
          DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/hpx
          OPTIONAL
          PERMISSIONS OWNER_READ OWNER_READ OWNER_READ
                      GROUP_READ GROUP_READ
                      WORLD_READ WORLD_READ)")
  install(CODE "${install_code}")
endmacro()

macro(hpx_ini_install name ini)
  set(install_code
      "if(EXISTS \"${name}\")
          file(INSTALL FILES ${CMAKE_CURRENT_SOURCE_DIR}/${ini}
               DESTINATION ${CMAKE_INSTALL_PREFIX}/share/hpx/ini
               OPTIONAL
               PERMISSIONS OWNER_READ OWNER_WRITE 
                           GROUP_READ 
                           WORLD_READ)
       endif()")
  install(CODE "${install_code}")
endmacro()

