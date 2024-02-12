//
// Created by Dragos on 7/5/2022.
//

#include "TRepo.h"

TRepo::TRepo() {
    read_from_file();
}

TRepo::~TRepo() {
    save_to_file();
}

#include <fstream>

void TRepo::read_from_file() {
    ifstream f(file_name);

    while(!f.eof()){
        Task new_task;
        f>> new_task;
        if(new_task.getDescription() == "")
            return;
        this->arr.push_back(new_task);
    }

    f.close();
}

void TRepo::save_to_file() {
    ofstream f(file_name);
    f.clear();

    for(const auto& task:arr){
        f<<task<<"\n";
    }

    f.close();
}

vector<Task> &TRepo::getAll() {
    return arr;
}

void TRepo::add(Task& t) {
    arr.push_back(t);
}

void TRepo::remove(string &descritpion) {
    auto it = find_if(arr.begin(), arr.end(), [&](Task& t1){return t1.getDescription() == descritpion;});
    arr.erase(it);
}
