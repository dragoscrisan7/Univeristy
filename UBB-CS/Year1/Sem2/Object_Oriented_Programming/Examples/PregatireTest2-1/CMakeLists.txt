cmake_minimum_required(VERSION 3.21)
project(PregatireTest2_1)

set(CMAKE_CXX_STANDARD 14)

add_executable(PregatireTest2_1 main.cpp Measurement.h BMI.cpp BMI.h BP.h Person.cpp Person.h UserInterface.cpp UserInterface.h)
