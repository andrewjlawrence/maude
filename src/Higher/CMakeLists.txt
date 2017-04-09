cmake_minimum_required(VERSION 2.8)
PROJECT(libhigher)

find_path(BUDDY_DIR /src/bdd.h)
if (BUDDY_DIR)
  MESSAGE(STATUS "BuDDY include path found")
else()
  MESSAGE(FATAL_ERROR "BuDDy include path not found")
endif()
set(BUDDY_INCLUDE "${BUDDY_DIR}/src")

include_directories(${BUDDY_INCLUDE} 
                    "../Utility"
					"../Interface"
					"../Core"
					"../Variable"
					"../FullCompiler"
					"../Temporal"
					"../FreeTheory"
	                "../NA_Theory" 
					"../BuiltIn" 
					"../Mixfix")

file(GLOB HIGHER_HEADER_FILES "./*.hh")
file(GLOB HIGHER_SOURCE_FILES "./*.cc")				
							
add_library(libhigher ${HIGHER_HEADER_FILES} ${HIGHER_SOURCE_FILES})
