set(CMAKE_TOOLCHAIN_FILE ../arduino-cmake/cmake/ArduinoToolchain.cmake)

cmake_minimum_required(VERSION 2.8)
project(scoring-machine)

set(CMAKE_CXX_STANDARD 14)


set(ARDUINO_DEFAULT_BOARD uno)
set(ARDUINO_DEFAULT_PORT /dev/ttyACM0)

generate_arduino_firmware(scoring-machine
        SRCS main_loop.cpp side.cpp weapon_select.cpp
        HDRS side.h weapon_select.h)

