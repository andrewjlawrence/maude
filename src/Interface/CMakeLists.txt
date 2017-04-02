cmake_minimum_required(VERSION 2.8)
PROJECT(libinterface)

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

include_directories("../Utility" "../Core" "../Variable" "../FullCompiler" ${BUDDY_INCLUDE})

file(GLOB INTERFACE_HEADER_FILES "./*.hh")
file(GLOB INTERFACE_SOURCE_FILES "./*.cc")
							
add_library(libinterface ${INTERFACE_SOURCE_FILES} ${INTERFACE_HEADER_FILES})
target_link_libraries(libinterface "${BUDDY_LIB}")
