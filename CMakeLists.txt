cmake_minimum_required(VERSION 3.31)
project(Novo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Novo main.cpp
        src/Lexer.cpp
        src/token.cpp
        src/Parser.cpp
        h/Lexer.h
        h/Token.h
        h/Parser.h)

find_package(LLVM REQUIRED CONFIG)
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

llvm_map_components_to_libnames(LLVM_LIBS core support)
target_link_libraries(Novo ${LLVM_LIBS})

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)
enable_testing()
add_executable(NovoTests
        tests/test_lexer.cpp
        src/Lexer.cpp
        src/Token.cpp
)

target_link_libraries(NovoTests
        PRIVATE
        gtest
        gtest_main
        pthread
        ${LLVM_LIBS}
)

add_test(NAME NovoTests COMMAND NovoTests)
