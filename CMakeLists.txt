cmake_minimum_required(VERSION 3.16.0)
project(polyglot-library)

# Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)

if(EXISTS ${LOC_PATH})
  message(FATAL_ERROR "You cannot build in a source directory.")
endif()

set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/output)
set(CPP_STANDARD cxx_std_20)

option(BUILD_LIBRARY_DRIVER "Enable building library driver" OFF)
option(BUILD_LIBRARY_SANDBOX "Enable building library sandbox" OFF)

set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR include CACHE PATH "Installation directory for header files")

add_subdirectory(lib)

if(BUILD_LIBRARY_DRIVER)
  add_subdirectory(driver)
endif()

if(BUILD_LIBRARY_SANDBOX)
  add_subdirectory(sandbox)
endif()
