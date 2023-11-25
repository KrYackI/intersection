cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(Intersections)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CONFIGURATION_TYPES Release)

add_subdirectory(2,3-tree)
add_subdirectory(AVL-tree)
add_subdirectory(Algorithm)
add_subdirectory(Intersection)

option(BUILD_TEST "build test?" OFF)

if(BTEST)
	add_subdirectory(gtest)
	add_subdirectory(ITest)
endif()