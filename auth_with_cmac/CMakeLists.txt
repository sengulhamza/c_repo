cmake_minimum_required(VERSION 3.10)

set(CMAKE_OSX_ARCHITECTURES arm64)

message("-- Cmake running on platform: " ${CMAKE_HOST_SYSTEM_NAME})

if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Darwin")
    # for MacOS X or iOS, watchOS, tvOS (since 3.10.3)
    set(OPENSSL_ROOT_DIR /opt/homebrew/Cellar/openssl@1.1/1.1.1s/)
elseif(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")
    set(OPENSSL_ROOT_DIR /usr/include/openssl/)
endif()


project(auth_with_cmac)

# Find the OpenSSL library and add it to the project
find_package(OpenSSL 1.1 REQUIRED)

# add the sources here
set(sources
    src/main.c
    src/auth_with_cmac.c
    src/hex_dump.c
)

add_executable(auth_with_cmac ${sources})

target_include_directories(auth_with_cmac PRIVATE inc/)
# Link the main executable with the OpenSSL library
target_link_libraries(auth_with_cmac OpenSSL::SSL)
