cmake_minimum_required(VERSION 3.10)

set(CMAKE_OSX_ARCHITECTURES arm64)

message("-- Cmake running on platform: " ${CMAKE_HOST_SYSTEM_NAME})

project(tcp_listener)

# add the sources here
set(sources
    src/tcp_sock_server.c
    src/hex_dump.c
)

# add the sources here
set(sources_client
    src/tcp_sock_client.c
)

add_executable(tcp_listener ${sources})
add_executable(tcp_listener_client ${sources_client})

target_include_directories(tcp_listener PRIVATE inc/)
