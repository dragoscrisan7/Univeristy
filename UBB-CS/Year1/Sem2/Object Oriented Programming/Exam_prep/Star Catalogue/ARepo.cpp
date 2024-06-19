//
// Created by Dragos on 7/5/2022.
//

#include "ARepo.h"

ARepo::ARepo() {
    read_from_file();
}

ARepo::~ARepo() {
    save_to_file();
}

#include <fstream>

void ARepo::read_from_file() {
    std::ifstream f(file_name);
    while(!f.eof()){
        Astronomers q;
        f>> q;
        if(q.getName() == "")
            return;
        this->arr.push_back(q);
    }
    f.close();

}

void ARepo::save_to_file() {
    std::ofstream f(file_name);
    f.clear();
    for(const auto& q:arr){
        f<<q<<"\n";
    }
    f.close();
}

vector<Astronomers>& ARepo::getAll() {
    return arr;
}
