cmake_minimum_required(VERSION 3.8)
project(calculator)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")

set(SOURCE_FILES main.cpp tokenstream.cpp program.cpp tokenstream.h program.h)

add_executable(calculator ${SOURCE_FILES})

