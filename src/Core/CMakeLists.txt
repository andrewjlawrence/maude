cmake_minimum_required(VERSION 2.8)
PROJECT(libcore)

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


include_directories("../Utility" "../Interface" "../FullCompiler" "../Variable" ${GMP_INCLUDE} ${BUDDY_INCLUDE})

file(GLOB CORE_HEADER_FILES "./*.hh")
file(GLOB CORE_SOURCE_FILES "./*.cc")

set_source_files_properties(run.cc 
                            ctorDiagram.cc 
							sortErrorAnalysis.cc
							PROPERTIES HEADER_FILE_ONLY TRUE) 
							 
add_library(libcore ${CORE_SOURCE_FILES} ${CORE_HEADER_FILES})

