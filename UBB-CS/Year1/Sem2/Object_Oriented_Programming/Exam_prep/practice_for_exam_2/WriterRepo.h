//
// Created by Oana on 6/7/2022.
//

#pragma once
#include <vector>
#include "Writer.h"

class WriterRepo {
private:
    std::vector<Writer> arr;
    std::string file_name = "C:\\Users\\Dragos\\OneDrive\\Facultate\\Year1Sem2\\Object_Oriented_Programming\\Exam_prep\\practice_for_exam_2\\writers.txt";

public:
    WriterRepo();
    ~WriterRepo();
    void readFromFile();
    void saveToFile();

    std::vector<Writer> getAllWriters();

};

