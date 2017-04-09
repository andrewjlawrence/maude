cmake_minimum_required(VERSION 2.8)
PROJECT(libAU_Persistent)

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
					"../FullCompiler" )

file(GLOB AU_PERSISTENT_HEADER_FILES "./*.hh")
file(GLOB AU_PERSISTENT_SOURCE_FILES "./*.cc")

set_source_files_properties(AU_StackArgVec.cc 
							AU_StackSort.cc
							PROPERTIES HEADER_FILE_ONLY TRUE) 
							
							
add_library(libAU_Persistent ${AU_PERSISTENT_HEADER_FILES} ${AU_PERSISTENT_SOURCE_FILES})
target_link_libraries(libAU_Persistent )
