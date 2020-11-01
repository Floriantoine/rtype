cmake_minimum_required(VERSION 3.6)

project("R-type's server" LANGUAGES CXX)

include_directories(
        ./include
        ../deps
        )

set(CMAKE_EXE_LINKER_FLAGS -lpthread)
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(WARNING_FLAG
        -Wall
        -Wextra
        -Wpedantic)

set(SRCS
        src/main.cpp
        src/Network/Server.cpp)

add_executable(r-type_server ${SRCS})

target_link_libraries(r-type_server PRIVATE ${CONAN_LIBS})
