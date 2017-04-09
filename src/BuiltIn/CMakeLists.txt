cmake_minimum_required(VERSION 2.8)
PROJECT(libbuiltIn)

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

include_directories(${BUDDY_INCLUDE} 
                    ${GMP_INCLUDE}
                    "../ACU_Persistent"
					"../ACU_Theory"
					"../NA_Theory"
					"../CUI_Theory"
					"../S_Theory"
					"../FreeTheory"
					"../3rdParty"
					"../Utility"
					"../Interface"
					"../Core"
					"../Variable"
					"../FullCompiler" )

file(GLOB BUILT_IN_HEADER_FILES "./*.hh")
file(GLOB BUILT_IN_SOURCE_FILES "./*.cc")

set_source_files_properties(matrixOpSignature.cc
							PROPERTIES HEADER_FILE_ONLY TRUE) 
														
add_library(libbuiltIn ${BUILT_IN_HEADER_FILES} ${BUILT_IN_SOURCE_FILES})
