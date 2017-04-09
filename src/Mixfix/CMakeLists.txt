cmake_minimum_required(VERSION 2.8)
PROJECT(libmixfix)

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
					"../Temporal"
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
					"../ACU_Persistent"
					"../ACU_Theory"
					"../AU_Persistent"
					"../AU_Theory"
					"../Meta"
					"../3rdParty"
					"../StrategyLanguage"
					"../SMT")

file(GLOB MIXFIX_HEADER_FILES "./*.hh")
file(GLOB MIXFIX_SOURCE_FILES "./*.cc")

#[[
FIND_PACKAGE(BISON REQUIRED)
SET(BisonOutput ${CMAKE_SOURCE_DIR}/surface.cc)
IF(BISON_FOUND)
    ADD_CUSTOM_COMMAND(
      OUTPUT ${BisonOutput}
      COMMAND ${BISON_EXECUTABLE}
	          -dv
              ${CMAKE_SOURCE_DIR}/surface.yy
			  --output=${BisonOutput}
      COMMENT "Generating surface.cc"
    )
ENDIF()

FIND_PACKAGE(FLEX REQUIRED)
SET(FlexOutput ${CMAKE_SOURCE_DIR}/lexer.cc)
IF(FLEX_FOUND)
    ADD_CUSTOM_COMMAND(
      OUTPUT ${FlexOutput}
      COMMAND ${FLEX_EXECUTABLE}
              -t
			  -p
			  -p
              ${CMAKE_SOURCE_DIR}/lexer.ll
			  --output=${FlexOutput}
      COMMENT "Generating scanner.cpp"
    )
ENDIF()
]]

add_definitions(-DPACKAGE_BUGREPORT="maude-bugs@lists.cs.illinois.edu")
add_definitions(-DPACKAGE_STRING="Maude 2.7.1")
add_definitions(-DCOMPILER)
add_definitions(-DNOMINMAX)
add_definitions(-DWIN32_LEAN_AND_MEAN)
 
set_source_files_properties(renameModule.cc
	                        parameterization.cc
							lexerAux.cc
							process.cc
							fixUp.cc
							ops.cc
							command.cc
							entry.cc
							prettyPrint.cc
							bufferPrint.cc
							specialSymbolTypes.cc
							specialTokens.cc
							doParse.cc
							makeGrammar.cc
							auxProperty.cc
							termPrint.cc
							dagNodePrint.cc
							sharedPrint.cc
							strategyPrint.cc
							interact.cc
							trial.cc
							execute.cc
							loopMode.cc
							search.cc
							srewrite.cc
							erewrite.cc
							match.cc
							unify.cc
							graphPrint.cc
							ansiEscapeSequences.cc
							PROPERTIES HEADER_FILE_ONLY TRUE) 
							
							
add_library(libmixfix ${MIXFIX_HEADER_FILES} ${MIXFIX_SOURCE_FILES} ${BisonOutput} ${FlexOutput} )
