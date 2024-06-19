cmake_minimum_required(VERSION 3.24)
project(Lab_parser)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab_parser main.cpp domain/Grammar.h domain/Grammar.cpp
        domain/Parser.h
        domain/Parser.cpp
        domain/Test.h
        domain/Test.cpp
        domain/SymbolTable.h
        domain/SymbolTable.cpp
        domain/Scanner.h
        domain/Scanner.cpp
        domain/Scanner.cpp
        domain/FA.h
        domain/FA.cpp)
