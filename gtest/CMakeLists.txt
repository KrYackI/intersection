set(TARGET gtest)
project(${TARGET})

file(GLOB TARGET_SRC "*.c*")
file(GLOB TARGET_HD "*.h*")

add_library(${TARGET} STATIC ${TARGET_SRC} ${TARGET_HD})
target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

#if((${CMAKE_CXX_COMPILER_ID} MATCHES "GNU" OR
#    ${CMAKE_CXX_COMPILER_ID} MATCHES "Clang") AND
#    (${CMAKE_SYSTEM_NAME} MATCHES "Linux"))
#    set(pthread "-pthread")
#endif()
#target_link_libraries(${target} ${pthread})

find_package(Threads)
if(THREADS_HAVE_PTHREAD_ARG)
  target_compile_options(${target} PUBLIC "-pthread")
endif()
if(CMAKE_THREAD_LIBS_INIT)
  target_link_libraries(${target} "${CMAKE_THREAD_LIBS_INIT}")
endif()

