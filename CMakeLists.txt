cmake_minimum_required(VERSION 3.23)

project(table_test LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

#################################

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)
set(CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}/build")


#################################

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}" CACHE STRING "install location")

#---- build options --------------------

option(TABLE_BUILD_EXAMPLE "Build table reading example"  ON)

#---- Fortran option -------------------
option(BUILD_FORTRAN_INTERFACE " Build fortran interface" ON)

#---- Main Project Targets -------------

add_subdirectory(src)

#---- Optional Project Targets ---------

#---- Examples -------------------------

if(TABLE_BUILD_EXAMPLE)
    add_subdirectory(examples)
endif()

#---- Fortran Interface ----------------

if(BUILD_FORTRAN_INTERFACE)
    enable_language(Fortran)
    add_subdirectory(src/fortran_wraps)
    add_subdirectory(examples/fortran_examples)
endif()

