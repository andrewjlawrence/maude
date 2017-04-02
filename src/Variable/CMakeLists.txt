cmake_minimum_required(VERSION 2.8)
PROJECT(libvariable)

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

include_directories("../Utility" "../Interface" "../Core" "../FullCompiler" ${BUDDY_INCLUDE})

file(GLOB VARIABLE_HEADER_FILES "./*.hh")
file(GLOB VARIABLE_SOURCE_FILES "./*.cc")

add_library(libvariable ${VARIABLE_SOURCE_FILES}  ${VARIABLE_HEADER_FILES})
target_link_libraries(libvariable "${BUDDY_LIB}")
