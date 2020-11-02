cmake_minimum_required(VERSION 3.5)

project("R-type's client" LANGUAGES CXX)

include_directories(
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

include_directories(src)

include_directories(src)

set(SRCS
        src/main.cpp
        src/engine/core/events/EventManager.cpp
        src/engine/core/ecs/component/IComponent.hpp
        src/engine/core/ecs/component/ComponentManager.hpp
        src/engine/core/ecs/memory/IObjectPool.hpp
        src/engine/core/ecs/memory/ObjectPool.hpp
        )

add_executable(r-type_client ${SRCS})

target_link_libraries(r-type_client PRIVATE ${CONAN_LIBS})
