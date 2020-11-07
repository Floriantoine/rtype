cmake_minimum_required(VERSION 3.5)

set(SRCS
    main.cpp
    tests_entity.cpp
    )

include_directories(../src)

Include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v2.13.1)

FetchContent_MakeAvailable(Catch2)

add_executable(tests ${SRCS})
target_link_libraries(tests Catch2::Catch2)
