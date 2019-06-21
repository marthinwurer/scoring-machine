set(CMAKE_TOOLCHAIN_FILE ../Arduino-CMake-NG/cmake/Arduino-Toolchain.cmake)

cmake_minimum_required(VERSION 3.8.2)
project(scoring-machine)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

#set(ARDUINO_DEFAULT_BOARD uno)
##set(ARDUINO_DEFAULT_PORT /dev/ttyUSB0)
#set(ARDUINO_DEFAULT_PORT /dev/ttyACM0)
#
#
#generate_arduino_firmware(scoring-machine
#        SRCS main_loop.cpp side.cpp weapon_select.cpp Epee.cpp Foil.cpp Saber.cpp
#        HDRS side.h weapon_select.h Epee.h config.h Foil.h Saber.h)

arduino_cmake_project(scoring_machine BOARD_NAME uno)
add_arduino_executable(scoring_machine
        main_loop.cpp side.cpp weapon_select.cpp Epee.cpp Foil.cpp Saber.cpp)
target_include_directories(scoring_machine PRIVATE .)
set_target_upload_port(scoring_machine /dev/ttyACM0)
