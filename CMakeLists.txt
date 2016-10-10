cmake_minimum_required(VERSION 2.8)
project(ProcessConnect)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
set(SOURCE_FILES ProcessConnect/sources/main.cpp )
set(CHILD_SOURCE_FILES ProcessConnect/sources/child_main.cpp)

add_executable(ProcessConnect ${SOURCE_FILES})
add_executable(ChildProcess ${CHILD_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} )