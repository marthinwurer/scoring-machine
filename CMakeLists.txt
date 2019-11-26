set(CMAKE_TOOLCHAIN_FILE ../Arduino-CMake-NG/cmake/Arduino-Toolchain.cmake)

cmake_minimum_required(VERSION 3.8.2)
project(scoring-machine)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_subdirectory(scoring_machine)
add_subdirectory(buzzbox)
add_subdirectory(blink_example)
