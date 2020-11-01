cmake_minimum_required(VERSION 3.6)

project("R-type's server" LANGUAGES CXX)

set(SRC_DIR src/)

include_directories(
	./include
        ../deps
        ${SRC_DIR}
)

set(CMAKE_EXE_LINKER_FLAGS -lpthread)
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(WARNING_FLAG
        -Wall
        -Wextra
        -Wpedantic)

set(SRCS
        main.cpp
        Exception.cpp
        Config.cpp
        GameServer.cpp
        lobby/LobbyIDGenerator.cpp
        lobby/LobbyManagerThread.cpp
        lobby/LobbyDispatcher.cpp
        lobby/Lobby.cpp
	Network/Server.cpp
)

list(TRANSFORM SRCS PREPEND ${SRC_DIR})

add_executable(r-type_server ${SRCS})

target_link_libraries(r-type_server PRIVATE ${CONAN_LIBS})
