//
// Created by Dragos on 6/27/2022.
//

#include "PRepo.h"

PRepo::PRepo(){
    read_from_file();
}

PRepo::~PRepo() {
    save_to_file();
}

vector<Participants>& PRepo::getALL() {
    return arr;
}

#include <fstream>

void PRepo::read_from_file() {
    std::ifstream f(file_name);
    while(!f.eof()){
        Participants q;
        f>> q;
        if(q.getName().empty())
            break;
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
