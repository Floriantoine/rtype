cmake_minimum_required(VERSION 3.6)

project("R-type" VERSION 1.0)

set(CMAKE_CXX_COMPILER_VERSION 9)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(server)
add_subdirectory(client)
