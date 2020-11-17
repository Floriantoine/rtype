cmake_minimum_required(VERSION 3.5)

include_directories( 
    ../utils
    ../core
)

set(SRCS
    main.cpp
    tests_protocol.cpp
)

add_executable(r-type_core_tests ${SRCS})
target_link_libraries(r-type_core_tests PRIVATE ${CONAN_LIBS})
