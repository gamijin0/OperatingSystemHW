cmake_minimum_required(VERSION 3.6)
project(ProcessConnect_Clipboard)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(MAIN_SOURCE_FILES  sources/main.cpp)
set(CHILD_SOURCE_FILES  sources/child.cpp)
add_executable(ProcessConnect_Clipboard_Main ${MAIN_SOURCE_FILES})
add_executable(ProcessConnect_Clipboard_Child ${CHILD_SOURCE_FILES})