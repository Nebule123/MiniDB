cmake_minimum_required(VERSION 3.16)

project(MiniDB LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(minidb
    main.cpp
    database.cpp
    command_parser.cpp
)

target_compile_options(minidb PRIVATE
    -Wall
    -Wextra
    -pedantic
)

add_executable(database_test
    tests/database_test.cpp
    database.cpp
)

target_compile_options(database_test PRIVATE
    -Wall
    -Wextra
    -pedantic
)

add_executable(command_parser_test
    tests/command_parser_test.cpp
    command_parser.cpp
)

target_compile_options(command_parser_test PRIVATE
    -Wall
    -Wextra
    -pedantic
)

enable_testing()

add_test(
    NAME database_test
    COMMAND database_test
)

add_test(
    NAME command_parser_test
    COMMAND command_parser_test
)
