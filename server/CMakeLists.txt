cmake_minimum_required(VERSION 3.6)

project("R-type's server" VERSION 1.0)

set(WARNING_FLAG
        -Wall
        -Wextra
        -Wpedantic)

include_directories(./include)

set(CMAKE_EXE_LINKER_FLAGS -lpthread)
add_definitions("-fPIC")
set(THREADS_PREFER_PTHREAD_FLAG ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRCS
        src/main.cpp)

add_executable(r-type_server ${SRCS})

target_link_libraries(r-type_server PRIVATE ${CONAN_LIBS})
