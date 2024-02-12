#pragma once
#include <vector>
#include "Writer.h"

class WriterRepo {
private:
    std::vector<Writer> arr;
    std::string file_name = "C:\\Users\\Dragos\\CLionProjects\\exam\\writers.txt";

public:
    WriterRepo();
    ~WriterRepo();
    void readFromFile();
    void saveToFile();

    std::vector<Writer> getAllWriters();

};

