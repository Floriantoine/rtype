cmake_minimum_required(VERSION 3.6)

project("R-type" VERSION 1.0)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(server)
add_subdirectory(client)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)