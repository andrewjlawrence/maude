cmake_minimum_required(VERSION 2.8)
PROJECT(libfreeTheory)

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

file(GLOB FREE_THEORY_HEADER_FILES "./*.hh")
file(GLOB FREE_THEORY_SOURCE_FILES "./*.cc")


set_source_files_properties(freeNetExec.cc
							freeTermFullCompiler.cc
							freeLhsCompiler.cc
							freePreNetSubsumption.cc
							freePreNetSemiCompiler.cc
							freePreNetFullCompiler.cc
							PROPERTIES HEADER_FILE_ONLY TRUE) 
							
							
add_library(libfreeTheory ${FREE_THEORY_HEADER_FILES} ${FREE_THEORY_SOURCE_FILES})
target_link_libraries(libfreeTheory)
