cmake_minimum_required(VERSION 3.5)

project("R-type's client" LANGUAGES CXX)

set(SRC_DIR src/)

include_directories(
        ./src
        ../deps
        ../deps/engine
        ../deps/core
        ${SRC_DIR}
        ${SRC_DIR}/Network
        )

set(WARNING_FLAG
        -Wall
        -Wextra
        -Wpedantic)

set(SRCS
        main.cpp
        Network/Client.cpp
        Exception.cpp
        GameClient.cpp
        game/Game.cpp
        game/behaviours/BugBehaviour.cpp
        game/behaviours/CameraBehaviour.cpp
        game/behaviours/MissilePlayerBehaviour.cpp
        game/behaviours/PataBehaviour.cpp
        game/behaviours/PlayerBehaviour.cpp
        game/behaviours/ScantBehaviour.cpp
        game/behaviours/ButtonBehaviour.cpp
        game/behaviours/TextInputBehaviour.cpp
        game/components/AnimationComponent.cpp
        game/components/ColorComponent.cpp
        game/components/InputComponent.cpp
        game/components/ScaleComponent.cpp
        game/components/TextComponent.cpp
        game/systems/TextSystem.cpp
        game/systems/InputSystem.cpp
        game/systems/EventSystem.cpp
        game/systems/AnimationSystem.cpp
        game/systems/BackgroundSystem.cpp
        game/systems/SpriteSystem.cpp
)

list(TRANSFORM SRCS PREPEND ${SRC_DIR})

add_executable(r-type_client ${SRCS})

target_link_libraries(r-type_client PRIVATE ${CONAN_LIBS})
