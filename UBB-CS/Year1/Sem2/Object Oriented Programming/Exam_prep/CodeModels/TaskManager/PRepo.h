//
// Created by Dragos on 7/5/2022.
//

#ifndef TASKMANAGER_PREPO_H
#define TASKMANAGER_PREPO_H
#include "Programmer.h"

class PRepo {
private:
    vector<Programmer> arr;
    string file_name = "C:\\Users\\Dragos\\CLionProjects\\TaskManager\\Programmers.txt";
public:
    PRepo();

    virtual ~PRepo();

    void read_from_file();
    void save_to_file();
    vector<Programmer>& getAll();
};


#endif //TASKMANAGER_PREPO_H
