//
// Created by Oana on 6/7/2022.
//

#include "WriterRepo.h"
#include <fstream>

WriterRepo::WriterRepo() {
    readFromFile();

}

WriterRepo::~WriterRepo() {
    //saveToFile();

}

void WriterRepo::readFromFile() {
    std::ifstream f(file_name);
    Writer input{};
    while(f>>input){
        arr.push_back(input);
    }
    f.close();
}

void WriterRepo::saveToFile() {
    std::ofstream f(file_name);
    for (auto writer: arr)
        f<<writer<<"\n";
    f.close();
}

std::vector<Writer> WriterRepo::getAllWriters() {
    return arr;
}
