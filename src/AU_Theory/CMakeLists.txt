cmake_minimum_required(VERSION 2.8)
PROJECT(libAU_Theory)

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
					"../AU_Persistent"
					"../Utility"
					"../Interface"
					"../Core"
					"../Variable"
					"../FullCompiler" )

file(GLOB AU_THEORY_HEADER_FILES "./*.hh")
file(GLOB AU_THEORY_SOURCE_FILES "./*.cc")

set_source_files_properties(AU_DagOperations.cc
							AU_Normalize.cc
							AU_LhsCompiler.cc
							AU_Matcher.cc
							AU_CollapseMatcher.cc
							AU_FullMatcher.cc
							AU_GreedyMatcher.cc
							AU_DequeMatcher.cc
							PROPERTIES HEADER_FILE_ONLY TRUE) 
							
							
add_library(libAU_Theory ${AU_THEORY_HEADER_FILES} ${AU_THEORY_SOURCE_FILES})
target_link_libraries(libAU_Theory )
