set(TARGET Intersection)

project(${TARGET})

set(AVL_INCLUDE "/AVL-tree")
set(23_INCLUDE "/2,3-tree")
set(ALG_INCLUDE "/Algorithm")

file(GLOB TARGET_SRC "*.c*")
file(GLOB TARGET_HD "*.h*")

add_executable(${TARGET} ${TARGET_SRC} ${TARGET_HD})

target_link_libraries(${TARGET} PUBLIC AVL-tree)
target_link_libraries(${TARGET} PUBLIC 23-tree)
target_link_libraries(${TARGET} PUBLIC Algorithm)

target_include_directories(${TARGET} PUBLIC ${CMAKE_SOURCE_DIR}${AVL_INCLUDE})
target_include_directories(${TARGET} PUBLIC ${CMAKE_SOURCE_DIR}${23_INCLUDE})
target_include_directories(${TARGET} PUBLIC ${CMAKE_SOURCE_DIR}${ALG_INCLUDE})

option(BUILD_EXP "build program for experiments?" OFF)
if (BUILD_EXP)
	add_definitions(-DEXPERIMENT)
endif()