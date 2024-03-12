cmake_minimum_required(VERSION 3.10)

set(CMAKE_OSX_ARCHITECTURES arm64)

message("-- Cmake running on platform: " ${CMAKE_HOST_SYSTEM_NAME})

project(capture_screen)

# add the sources here
set(sources
    #src/main.c
    src/serial_comm.c
    #src/capture_api.c
    src/hex_dump.c
)

add_executable(capture_screen ${sources})

target_include_directories(capture_screen PRIVATE inc/)
target_link_libraries(capture_screen PRIVATE "-framework CoreGraphics -pthread")
