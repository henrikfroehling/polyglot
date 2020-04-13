cmake_minimum_required(VERSION 3.15.0)
project(polyglot-library)

# Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)

if(EXISTS ${LOC_PATH})
  message(FATAL_ERROR "You cannot build in a source directory.")
endif()

set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/output)

add_subdirectory(lib)
add_subdirectory(driver)
