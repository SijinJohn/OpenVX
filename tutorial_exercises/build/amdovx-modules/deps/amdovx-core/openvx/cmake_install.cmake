# Install script for directory: /home/openvx/openvx_tutorial/tutorial_exercises/amdovx-modules/deps/amdovx-core/openvx

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libopenvx.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libopenvx.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libopenvx.so"
         RPATH "")
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/openvx/openvx_tutorial/tutorial_exercises/build/amdovx-modules/deps/amdovx-core/openvx/libopenvx.so")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libopenvx.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libopenvx.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libopenvx.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES "/home/openvx/openvx_tutorial/tutorial_exercises/amdovx-modules/deps/amdovx-core/openvx/include/vx_ext_amd.h")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/VX" TYPE FILE FILES
    "/home/openvx/openvx_tutorial/tutorial_exercises/amdovx-modules/deps/amdovx-core/openvx/include/VX/vx.h"
    "/home/openvx/openvx_tutorial/tutorial_exercises/amdovx-modules/deps/amdovx-core/openvx/include/VX/vx_api.h"
    "/home/openvx/openvx_tutorial/tutorial_exercises/amdovx-modules/deps/amdovx-core/openvx/include/VX/vx_compatibility.h"
    "/home/openvx/openvx_tutorial/tutorial_exercises/amdovx-modules/deps/amdovx-core/openvx/include/VX/vx_import.h"
    "/home/openvx/openvx_tutorial/tutorial_exercises/amdovx-modules/deps/amdovx-core/openvx/include/VX/vx_kernels.h"
    "/home/openvx/openvx_tutorial/tutorial_exercises/amdovx-modules/deps/amdovx-core/openvx/include/VX/vx_khr_icd.h"
    "/home/openvx/openvx_tutorial/tutorial_exercises/amdovx-modules/deps/amdovx-core/openvx/include/VX/vx_khr_ix.h"
    "/home/openvx/openvx_tutorial/tutorial_exercises/amdovx-modules/deps/amdovx-core/openvx/include/VX/vx_khr_nn.h"
    "/home/openvx/openvx_tutorial/tutorial_exercises/amdovx-modules/deps/amdovx-core/openvx/include/VX/vx_khr_tiling.h"
    "/home/openvx/openvx_tutorial/tutorial_exercises/amdovx-modules/deps/amdovx-core/openvx/include/VX/vx_khr_xml.h"
    "/home/openvx/openvx_tutorial/tutorial_exercises/amdovx-modules/deps/amdovx-core/openvx/include/VX/vx_nodes.h"
    "/home/openvx/openvx_tutorial/tutorial_exercises/amdovx-modules/deps/amdovx-core/openvx/include/VX/vx_types.h"
    "/home/openvx/openvx_tutorial/tutorial_exercises/amdovx-modules/deps/amdovx-core/openvx/include/VX/vx_vendors.h"
    "/home/openvx/openvx_tutorial/tutorial_exercises/amdovx-modules/deps/amdovx-core/openvx/include/VX/vxu.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

