cmake_minimum_required(VERSION 3.5)

set(SRCS
    main.cpp
    tests_entity.cpp
    )

include_directories(../src)

add_executable(r-type_client_tests ${SRCS})
target_link_libraries(r-type_client_tests PRIVATE ${CONAN_LIBS})
