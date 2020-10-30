cmake_minimum_required(VERSION 3.5)

project(client LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRCS
        src/main.cpp)

add_executable(r-type_client ${SRCS})

target_link_libraries(r-type_client PRIVATE ${CONAN_LIBS})

