cmake_minimum_required(VERSION 2.8)
PROJECT(libmeta)

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
					"../MSCP10"
					"../IO_Stuff"
					"../StrategyLanguage"
					"../3rdParty"
					"../SMT")

file(GLOB META_HEADER_FILES "./*.hh")
file(GLOB META_SOURCE_FILES "./*.cc")

set_source_files_properties(metaDown.cc
							metaDownRenamings.cc
							metaDownOps.cc
							metaDownFixUps.cc
							metaLevelSignature.cc
							metaUp.cc
							metaUpModule.cc
							descentFunctions.cc
							ascentFunctions.cc
							metaApply.cc
							metaMatch.cc
							metaUnify.cc
							metaSearch.cc
							metaNarrow.cc
							descentSignature.cc
							interpreterSignature.cc
							metaUpView.cc
							metaVariant.cc
							PROPERTIES HEADER_FILE_ONLY TRUE) 
							
add_library(libmeta ${META_HEADER_FILES} ${META_SOURCE_FILES})
