cmake_minimum_required(VERSION 3.24)
project(FLCD_project)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(FLCD_project
        domain/SymbolTable.cpp
        domain/SymbolTable.h
        main.cpp domain/Scanner.h domain/Scanner.cpp domain/FA.h domain/FA.cpp
        domain/Grammar.cpp
        domain/Grammar.h
        domain/Parser.h
        domain/Parser.cpp
)
