cmake_minimum_required(VERSION 2.8)

project(libhydra)

include(CheckCCompilerFlag)
include(CheckCXXCompilerFlag)

option(LIBBASE64_BUILD_TESTS "Build tests for this library" OFF)

if(LIBBASE64_BUILD_TESTS)
	enable_testing()
endif()

#---
if(MSVC)
	foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
		string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/bin)
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/lib)
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/lib)
	endforeach(OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES)
endif()

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#---

CHECK_C_COMPILER_FLAG("-std=c99" CC_STDC99)
if(CC_STDC99)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
endif()

CHECK_CXX_COMPILER_FLAG("-std=c++11" CXX_STDCPP11)
if(CXX_STDCPP11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()
if(NOT CXX_STDCPP11 AND NOT MSVC)
	message(FATAL_ERROR "Do not know how to enable c++11 on this compiler")
endif()

list(APPEND srcs
	"src/base64.c"
	"src/base64.h"
	"src/base64.cpp")

list(APPEND incs "include/base64/base64.h")

list(APPEND inc_dirs
	"${CMAKE_CURRENT_SOURCE_DIR}/include")

add_library(libbase64 ${srcs} ${incs})
set_target_properties(libbase64 PROPERTIES
	INCLUDE_DIRECTORIES "${inc_dirs}"
	INTERFACE_INCLUDE_DIRECTORIES "${inc_dirs}"
	PREFIX "")

if(LIBBASE64_BUILD_TESTS)
	add_executable(test_libbase64 "tests/test.cpp")
	target_link_libraries(test_libbase64 libbase64)

	add_test(NAME test_libbase64
		COMMAND $<TARGET_FILE:test_libbase64>
		WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")

endif()
