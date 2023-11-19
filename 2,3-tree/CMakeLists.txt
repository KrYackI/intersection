set(TARGET 23-tree)

project(${TARGET})

file(GLOB TARGET_SRC "*.c*")
file(GLOB TARGET_HD "*.h*")
add_library(${TARGET} STATIC ${TARGET_SRC} ${TARGET_HD})
target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})