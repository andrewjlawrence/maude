cmake_minimum_required(VERSION 2.8)
PROJECT(main)

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

add_definitions(-DPACKAGE_VERSION="2.7.1")
add_definitions(-DPACKAGE_BUGREPORT="maude-bugs@lists.cs.illinois.edu")

include_directories(${BUDDY_INCLUDE} 
                    ${GMP_INCLUDE}
                    "../Utility"
					"../Interface"
					"../Core"
					"../Variable"
					"../FullCompiler"
					"../Higher"
					"../CUI_Theory" 
					"../S_Theory" 
					"../NA_Theory" 
	                "../FreeTheory" 
					"../ObjectSystem"
					"../Mixfix" 
					"../BuiltIn"
					"../SMT"
					"../MSCP10"
					"../IO_Stuff"
					"../ACU_Persistent"
					"../ACU_Theory"
					"../AU_Persistent" 
					"../AU_Theory"
					"../Meta"
					"../3rdParty"
					"../FullCompiler"
					"../StrategyLanguage"
					"../Mixfix")

file(GLOB MAIN_SOURCE_FILES "./*.cc")
							
add_executable(maude ${MAIN_SOURCE_FILES})
