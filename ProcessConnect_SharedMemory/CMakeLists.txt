cmake_minimum_required(VERSION 2.8)
project(ProcessConnect)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
set(SOURCE_FILES sources/main.cpp)
set(CHILD_SOURCE_FILES sources/child_main.cpp)
set(EXECUTABLE_OUTPUT_PATH tmp)

add_executable(ProcessConnect_main ${SOURCE_FILES})
add_executable(ProcessConnect_child ${CHILD_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} )