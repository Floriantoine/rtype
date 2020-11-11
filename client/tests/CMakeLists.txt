cmake_minimum_required(VERSION 3.5)

include_directories(
    ../src
    ../../deps
    ../../deps/engine
    )

set(SRCS
    main.cpp
    tests_entity.cpp
    )

add_executable(r-type_client_tests ${SRCS})
target_link_libraries(r-type_client_tests PRIVATE ${CONAN_LIBS})
