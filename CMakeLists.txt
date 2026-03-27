cmake_minimum_required(VERSION 3.14)
project(MathLib CXX)

add_library(math_lib INTERFACE)
target_include_directories(math_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
