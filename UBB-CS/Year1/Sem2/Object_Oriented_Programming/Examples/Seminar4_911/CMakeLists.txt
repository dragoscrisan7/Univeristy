cmake_minimum_required(VERSION 3.21)
project(Seminar4_911)

set(CMAKE_CXX_STANDARD 14)

include_directories(Seminar4_911)

add_executable(Seminar4_911
        Seminar4_911/BMI.cpp
        Seminar4_911/BMI.h
        Seminar4_911/BP.cpp
        Seminar4_911/BP.h
        Seminar4_911/main.cpp
        Seminar4_911/MedicalAanalysis.cpp
        Seminar4_911/MedicalAanalysis.h
        Seminar4_911/Person.cpp
        Seminar4_911/Person.h
        Seminar4_911/UI.cpp
        Seminar4_911/UI.h
        Seminar4_911/Utils.cpp
        Seminar4_911/Utils.h)
