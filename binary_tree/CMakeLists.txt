cmake_minimum_required(VERSION 3.10)

set(CMAKE_OSX_ARCHITECTURES arm64)

message("-- Cmake running on platform: " ${CMAKE_HOST_SYSTEM_NAME})

project(binary_tree)

# add the sources here
set(sources
    src/main.c
    src/binary_tree.c
    src/hex_dump.c
)

add_executable(binary_tree ${sources})

target_include_directories(binary_tree PRIVATE inc/)


