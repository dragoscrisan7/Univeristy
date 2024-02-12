//
// Created by Dragos on 7/5/2022.
//

#include "SRepo.h"

SRepo::SRepo() {
    read_from_file();
}

SRepo::~SRepo() {
    save_to_file();
}

#include <fstream>

void SRepo::read_from_file() {
    std::ifstream f(file_name);
    while(!f.eof()){
        Stars q;
        f>> q;
        if(q.getName() == "")
            return;
        this->arr.push_back(q);
    }
    f.close();

}

void SRepo::save_to_file() {
    std::ofstream f(file_name);
    f.clear();
    sort(arr.begin(), arr.end(), [](Stars& s1, Stars& s2){return s1.getName()<s2.getName();});
    for(const auto& q:arr){
        f<<q<<"\n";
    }
    f.close();
}

vector<Stars>& SRepo::getAll() {
    return arr;
}

void SRepo::add(Stars& s) {
    arr.push_back(s);
}

