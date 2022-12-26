cmake_minimum_required(VERSION 3.10)

set(CMAKE_OSX_ARCHITECTURES arm64)

message("-- Cmake running on platform: " ${CMAKE_HOST_SYSTEM_NAME})

project(frame_oop_with_crc)

# add the sources here
set(sources
    src/main.c
    src/frame_oop_with_crc.c
    src/hex_dump.c
)

add_executable(frame_oop_with_crc ${sources})

target_include_directories(frame_oop_with_crc PRIVATE inc/)
