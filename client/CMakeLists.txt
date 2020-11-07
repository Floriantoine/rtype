cmake_minimum_required(VERSION 3.5)

project("R-type's client" LANGUAGES CXX)

include_directories(
	../core
        ../deps
        ../deps/engine
        )

set(WARNING_FLAG
        -Wall
        -Wextra
        -Wpedantic)

include_directories(src)

set(SRCS
        src/main.cpp
        )

add_executable(r-type_client ${SRCS})

target_link_libraries(r-type_client PRIVATE ${CONAN_LIBS})
