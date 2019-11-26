#set(CMAKE_TOOLCHAIN_FILE ../../../Arduino-CMake-NG/cmake/Arduino-Toolchain.cmake)
project(buzzbox)

#set(ARDUINO_DEFAULT_BOARD uno)
##set(ARDUINO_DEFAULT_PORT /dev/ttyUSB0)
#set(ARDUINO_DEFAULT_PORT /dev/ttyACM0)
#
#
#generate_arduino_firmware(scoring-machine
#        SRCS main_loop.cpp side.cpp weapon_select.cpp Epee.cpp Foil.cpp Saber.cpp
#        HDRS side.h weapon_select.h Epee.h config.h Foil.h Saber.h)

arduino_cmake_project(blink_example BOARD_NAME uno)
add_arduino_executable(blink_example
        blink.cpp)
target_include_directories(buzzbox PRIVATE ..)
set_target_upload_port(blink_example /dev/ttyACM0)
