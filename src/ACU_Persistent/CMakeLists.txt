cmake_minimum_required(VERSION 2.8)
PROJECT(libACU_Persistent)

find_path(BUDDY_DIR /src/bdd.h)
if (BUDDY_DIR)
  MESSAGE(STATUS "BuDDY include path found")
else()
  MESSAGE(FATAL_ERROR "BuDDy include path not found")
endif()
set(BUDDY_INCLUDE "${BUDDY_DIR}/src")

include_directories(${BUDDY_INCLUDE} "../Utility" "../Interface" "../Core" "../Variable" "../FullCompiler" )

file(GLOB ACU_PERSISTENT_HEADER_FILES "./*.hh")
file(GLOB ACU_PERSISTENT_SOURCE_FILES "./*.cc")

set_source_files_properties(ACU_Find.cc 
	                        ACU_Insert.cc 
	                        ACU_Copy.cc 
							ACU_Delete.cc 
							ACU_Rebalance.cc
							PROPERTIES HEADER_FILE_ONLY TRUE) 
							
							
add_library(libACU_Persistent ${ACU_PERSISTENT_HEADER_FILES} ${ACU_PERSISTENT_SOURCE_FILES})
target_link_libraries(libACU_Persistent )
