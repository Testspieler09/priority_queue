cmake_minimum_required(VERSION 3.20)
project(PriorityQueue VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(priority_queue SHARED
				src/core.c
				src/utils.c
)

target_include_directories(priority_queue PUBLIC
				${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(priority_queue PRIVATE -Wall -Wextra -Wpedantic)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/examples/CMakeLists.txt)
	add_subdirectory(examples)
endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests/CMakeLists.txt)
	add_subdirectory(tests)
endif()
