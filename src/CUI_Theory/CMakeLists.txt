cmake_minimum_required(VERSION 2.8)
PROJECT(libCUI_Theory)

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

file(GLOB CUI_THEORY_HEADER_FILES "./*.hh")
file(GLOB CUI_THEORY_SOURCE_FILES "./*.cc")

set_source_files_properties(CUI_LhsCompiler.cc
							CUI_Matcher.cc
							PROPERTIES HEADER_FILE_ONLY TRUE) 
							
							
add_library(libCUI_Theory ${CUI_THEORY_HEADER_FILES} ${CUI_THEORY_SOURCE_FILES})
target_link_libraries(libCUI_Theory )
