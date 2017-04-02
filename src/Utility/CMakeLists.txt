cmake_minimum_required(VERSION 2.8)
PROJECT(libutility)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME ON)
find_package(Boost REQUIRED timer)

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


find_library(MPIR_LIB mpir.lib)
if (MPIR_LIB)
  MESSAGE(STATUS "MPIR library found")
else()
  MESSAGE(FATAL_ERROR "MPIR library not found")
endif()

find_path(GMP_INCLUDE gmpxx.h)
if (GMP_INCLUDE)
  MESSAGE(STATUS "gmpxx.h include path found")
else()
  MESSAGE(FATAL_ERROR "gmpxx.h include path not found")
endif()

include_directories(${BUDDY_INCLUDE} ${GMP_INCLUDE} ${Boost_INCLUDE_DIR})
file(GLOB UTILITY_HEADER_FILES "./*.hh")
file(GLOB UTILITY_SOURCE_FILES "./*.cc")

if( WIN32 )
file(GLOB UTILITY_PLATFORM_SOURCE_FILES "./windows/*.cc")
else()
file(GLOB UTILITY_PLATFORM_SOURCE_FILES "./linux/*.cc")
endif()

set_source_files_properties(intContejeanDevie.cc 
                            mpzContejeanDevie.cc 
							mpzGcdBasedSolver.cc
                            mpzGcdInit.cc
                            mpzGcdTrivial.cc
							pigPug-cycleDetection.cc
							wordLevel-simplifyAssignments.cc
							wordLevel-simplifyEquations.cc
							PROPERTIES HEADER_FILE_ONLY TRUE) 
							

 
add_library(libutility ${UTILITY_SOURCE_FILES} ${UTILITY_PLATFORM_SOURCE_FILES} ${UTILITY_HEADER_FILES})
target_link_libraries(libutility "${BUDDY_LIB}" "${MPIR_LIB}")
