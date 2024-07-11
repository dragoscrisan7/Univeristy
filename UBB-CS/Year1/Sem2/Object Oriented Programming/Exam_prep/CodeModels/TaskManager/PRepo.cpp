//
// Created by Dragos on 7/5/2022.
//

#include "PRepo.h"

PRepo::PRepo() {
    read_from_file();
}

PRepo::~PRepo() {

}
#include <fstream>

void PRepo::read_from_file() {
    std::ifstream f(file_name);
    while(!f.eof()){
        Programmer q;
        f>> q;
        if(q.getName() == "")
            return;
        this->arr.push_back(q);
    }
    f.close();

}

void PRepo::save_to_file() {
    std::ofstream f(file_name);
    f.clear();
    for(const auto& q:arr){
        f<<q<<"\n";
    }
    f.close();
}

vector<Programmer> &PRepo::getAll() {
    return arr;
}
