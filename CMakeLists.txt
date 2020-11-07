cmake_minimum_required(VERSION 3.6)

project("R-type" VERSION 1.0)

set(CONAN_DISABLE_CHECK_COMPILER ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()

add_subdirectory(server)
add_subdirectory(client)
add_subdirectory(client/tests)

add_test(r-type_client ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/r-type_client_tests)
