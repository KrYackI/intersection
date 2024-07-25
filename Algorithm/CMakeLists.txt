set(TARGET Algorithm)

project(${TARGET})

file(GLOB TARGET_SRC "*.c*")
file(GLOB TARGET_HD "*.h*")
add_library(${TARGET} STATIC ${TARGET_SRC} ${TARGET_HD})
target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../AVL-tree/)
target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../2,3-tree)

target_link_libraries(${TARGET} PUBLIC -lAVL-tree)
target_link_libraries(${TARGET} PUBLIC -l23-tree)