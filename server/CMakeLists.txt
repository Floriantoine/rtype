cmake_minimum_required(VERSION 3.6)

project("R-type's server" LANGUAGES CXX)

set(SRC_DIR src/)

include_directories(
        ../deps
        ../deps/core
        ${SRC_DIR}
        ${SRC_DIR}/Network
)

set(CMAKE_CXX_STANDARD 20)

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
        handlers/AHandler.cpp
        handlers/AHandlerUDP.cpp
        handlers/TCP/AskJoinHandler/AskJoinHandler.cpp
        handlers/TCP/CreateHandler/CreateHandler.cpp
        handlers/UDP/ChargeHandler/ChargeHandler.cpp
        handlers/UDP/DestroyHandler/DestroyHandler.cpp
        handlers/UDP/DropHandler/DropHandler.cpp
        handlers/UDP/GameStateHandler/GameStateHandler.cpp
        handlers/UDP/GrabHandler/GrabHandler.cpp
        handlers/UDP/HitHandler/HitHandler.cpp
        handlers/UDP/JoinHandler/JoinHandler.cpp
        handlers/UDP/LeaveHandler/LeaveHandler.cpp
        handlers/UDP/MoveHandler/MoveHandler.cpp
        handlers/UDP/ShootHandler/ShootHandler.cpp
        handlers/UDP/SpawnHandler/SpawnHandler.cpp
)

list(TRANSFORM SRCS PREPEND ${SRC_DIR})

add_executable(r-type_server ${SRCS})

target_link_libraries(r-type_server PRIVATE ${CONAN_LIBS})
