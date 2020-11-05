cmake_minimum_required(VERSION 3.6)

project("R-type's server" LANGUAGES CXX)

include_directories(
        ./include
        ../deps
        )

set(CMAKE_EXE_LINKER_FLAGS -lpthread)
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(WARNING_FLAG
        -Wall
        -Wextra
        -Wpedantic)

set(SRC_DIR src/)

set(SRCS
        main.cpp
        Config.cpp
        Server.cpp
        lobby/LobbyManagerThread.cpp
        lobby/LobbyDispatcher.cpp
        lobby/Lobby.cpp
)

list(TRANSFORM SRCS PREPEND ${SRC_DIR})

add_executable(r-type_server ${SRCS})

target_link_libraries(r-type_server PRIVATE ${CONAN_LIBS})
