# Install script for directory: /home/damien/Documents/mobj/tme7/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "../install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/tme6" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/tme6")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/tme6"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/damien/Documents/mobj/tme7/build/tme6")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/tme6" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/tme6")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/tme6")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/home/damien/Documents/mobj/tme7/src/Indentation.h"
    "/home/damien/Documents/mobj/tme7/src/XmlUtil.h"
    "/home/damien/Documents/mobj/tme7/src/Term.h"
    "/home/damien/Documents/mobj/tme7/src/Net.h"
    "/home/damien/Documents/mobj/tme7/src/Instance.h"
    "/home/damien/Documents/mobj/tme7/src/Point.h"
    "/home/damien/Documents/mobj/tme7/src/Node.h"
    "/home/damien/Documents/mobj/tme7/src/Cell.h"
    "/home/damien/Documents/mobj/tme7/src/Line.h"
    "/home/damien/Documents/mobj/tme7/src/Box.h"
    "/home/damien/Documents/mobj/tme7/src/Shape.h"
    "/home/damien/Documents/mobj/tme7/src/LineShape.h"
    "/home/damien/Documents/mobj/tme7/src/BoxShape.h"
    "/home/damien/Documents/mobj/tme7/src/EllipseShape.h"
    "/home/damien/Documents/mobj/tme7/src/ArcShape.h"
    "/home/damien/Documents/mobj/tme7/src/TermShape.h"
    "/home/damien/Documents/mobj/tme7/src/Symbol.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

file(WRITE "/home/damien/Documents/mobj/tme7/build/${CMAKE_INSTALL_MANIFEST}" "")
foreach(file ${CMAKE_INSTALL_MANIFEST_FILES})
  file(APPEND "/home/damien/Documents/mobj/tme7/build/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
endforeach()
