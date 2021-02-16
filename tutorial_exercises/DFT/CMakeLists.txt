cmake_minimum_required(VERSION 2.8)
project(DFT)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include/)
file(GLOB sources "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")

add_library(dft ${sources})

add_executable(test_dft main.cpp)

target_link_libraries(test_dft PUBLIC dft)
