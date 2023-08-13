cmake_minimum_required(VERSION 3.0)

project(oran)
include_directories(include)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")

add_executable(oran src/main.c)
add_executable(main.out src/main.c)