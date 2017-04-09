cmake_minimum_required(VERSION 2.8)
PROJECT(libACU_Theory)

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
					"../Utility"
					"../Interface"
					"../Core"
					"../Variable"
					"../FullCompiler" )

file(GLOB ACU_THEORY_HEADER_FILES "./*.hh")
file(GLOB ACU_THEORY_SOURCE_FILES "./*.cc")

set_source_files_properties(ACU_LhsCompiler0.cc 
							ACU_LhsCompiler1.cc 
							ACU_LhsCompiler2.cc 
							ACU_LhsCompiler3.cc 
							ACU_Matcher.cc 
							ACU_GreedyMatcher.cc 
							ACU_CollapseMatcher.cc 
							ACU_TreeMatcher.cc 
							ACU_DagOperations.cc 
							ACU_FastMerge.cc 
							ACU_Normalize.cc 
							ACU_MergeSort.cc 
							PROPERTIES HEADER_FILE_ONLY TRUE) 
							
							
add_library(libACU_Theory ${ACU_THEORY_HEADER_FILES} ${ACU_THEORY_SOURCE_FILES})
