cmake_minimum_required(VERSION 3.16)
project("Calc2")
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANTDARD 17)
set(CMAKE_CXX_FLAGS 
    "${CMAKE_CXX_FLAGS}-Wall -Werror -g -ggdb"
    )
add_executable(calc2
    src/main.cpp
    src/program.cpp
    src/program.h
    src/expression.cpp
    src/expression.h
    src/tokenstring.cpp
    src/tokenstring.h
    src/token.cpp
    src/token.h
)
