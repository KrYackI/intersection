set(TARGET ITest)

project(${TARGET})

set(AVL_INCLUDE "/AVL-tree")
set(23_INCLUDE "/2,3-tree")
set(ALG_INCLUDE "/Algorithm")

file(GLOB TARGET_SRC "*.c*")
file(GLOB TARGET_HD "*.h*")

add_executable(${TARGET} ${TARGET_SRC} ${TARGET_HD})

target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..${AVL_INCLUDE})
target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..${23_INCLUDE})
target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..${ALG_INCLUDE})
target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../gtest)

target_link_libraries(${TARGET} PUBLIC gtest)
target_link_libraries(${TARGET} PUBLIC -lAlgorithm)