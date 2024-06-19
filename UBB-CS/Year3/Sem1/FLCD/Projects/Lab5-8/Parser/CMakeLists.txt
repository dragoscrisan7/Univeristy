cmake_minimum_required(VERSION 3.21)
project(Parser)

set(CMAKE_CXX_STANDARD 17)

include_directories(Lab_parser/domain)

add_executable(Parser
        Lab_parser/domain/Grammar.cpp
        Lab_parser/domain/Grammar.h
        Lab_parser/main.cpp
        Lab_parser/domain/Parser.cpp
        Lab_parser/domain/Test.cpp
        Lab_parser/domain/SymbolTable.h
        Lab_parser/domain/SymbolTable.cpp
        Lab_parser/domain/Scanner.h
        Lab_parser/domain/Scanner.cpp
        Lab_parser/domain/Scanner.cpp
        Lab_parser/domain/FA.h
        Lab_parser/domain/FA.cpp)
