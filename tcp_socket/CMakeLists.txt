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
    src/hex_dump.c
)

add_executable(tcp_server ${sources})
add_executable(tcp_client ${sources_client})

target_include_directories(tcp_server PRIVATE inc/)
target_include_directories(tcp_client PRIVATE inc/)
