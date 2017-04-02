cmake_minimum_required(VERSION 2.8)
PROJECT(libfullcompiler)

find_library(BUDDY_LIB /src/Debug/bdd.lib)
if (BUDDY_LIB)
  MESSAGE(STATUS "BuDDY library found")
else()
  MESSAGE(FATAL_ERROR "BuDDy library not found")
endif()

find_path(BUDDY_DIR /src/bdd.h)
if (BUDDY_DIR)
  MESSAGE(STATUS "BuDDY include path found")
else()
  MESSAGE(FATAL_ERROR "BuDDy include path not found")
endif()
set(BUDDY_INCLUDE "${BUDDY_DIR}/src")

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME ON)
find_package(Boost REQUIRED timer)

add_definitions(-DCOMPILER)

include_directories("../Utility" "../Core" "../Interface" ${BUDDY_INCLUDE} ${Boost_INCLUDE_DIR})

file(GLOB FULL_COMPILER_HEADER_FILES "./*.hh")
file(GLOB FULL_COMPILER_SOURCE_FILES "./compilationContext.cc")
							
add_library(libfullcompiler ${FULL_COMPILER_SOURCE_FILES} ${FULL_COMPILER_HEADER_FILES})

file(GLOB RUN_TIME_HEADER_FILES "./*.hh")
file(GLOB RUN_TIME_SOURCE_FILES "./runtime.cc")
							
add_library(libruntime ${RUN_TIME_SOURCE_FILES} ${RUN_TIME_HEADER_FILES})