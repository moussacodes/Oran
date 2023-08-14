
cmake_minimum_required(VERSION 3.10)
project(oran)

include_directories(include)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")

set(SOURCE_FILES
    src/main.c
    src/compiler/lexer.c
    src/compiler/parser.c
    src/utils/common.c
)

add_executable(oran ${SOURCE_FILES})
 