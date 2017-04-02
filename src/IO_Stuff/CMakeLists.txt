cmake_minimum_required(VERSION 2.8)
PROJECT(libiostuff)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME ON)
find_package(Boost REQUIRED filesystem)

if( WIN32 )
file(GLOB IO_PLATFORM_SOURCE_FILES "./windows/*.cc")
else()
file(GLOB IO_PLATFORM_SOURCE_FILES "./linux/*.cc")
endif()

include_directories("../Utility" ${BUDDY_INCLUDE} ${GMP_INCLUDE} ${Boost_INCLUDE_DIR})
file(GLOB IO_HEADER_FILES "./*.hh")
file(GLOB IO_SOURCE_FILES "./*.cc")
 
add_library(libiostuff ${IO_SOURCE_FILES} ${IO_PLATFORM_SOURCE_FILES} ${IO_HEADER_FILES})
target_link_libraries(libiostuff)
