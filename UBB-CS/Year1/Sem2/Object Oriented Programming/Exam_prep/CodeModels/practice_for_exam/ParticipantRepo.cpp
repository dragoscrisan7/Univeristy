//
// Created by Oana on 6/6/2022.
//

#include <fstream>
#include "ParticipantRepo.h"

void ParticipantRepo::read_from_file() {
    std::ifstream f(file_name);
    while(!f.eof()){
        Participant p;
        p.setScore(0);
        f>>p;
        arr.push_back(p);
    }
    f.close();
}

void ParticipantRepo::save_to_file() {
    std::ofstream f(file_name);
    f.clear();
    for(auto p: arr)
        f<<p<<"\n";
    f.close();
}

ParticipantRepo::ParticipantRepo() {
    read_from_file();
}

ParticipantRepo::~ParticipantRepo() {
    save_to_file();
}

std::vector<Participant> &ParticipantRepo::get_participants() {
    return this->arr;
}
