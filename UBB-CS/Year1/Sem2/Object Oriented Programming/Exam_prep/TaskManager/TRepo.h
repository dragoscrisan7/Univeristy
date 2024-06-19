//
// Created by Dragos on 7/5/2022.
//

#ifndef TASKMANAGER_TREPO_H
#define TASKMANAGER_TREPO_H
#include "Task.h"

class TRepo {
private:
    vector<Task> arr;
    string file_name = "C:\\Users\\Dragos\\CLionProjects\\TaskManager\\Tasks.txt";
public:
    TRepo();

    virtual ~TRepo();

    void read_from_file();
    void save_to_file();
    void add(Task& t);
    void remove(string& descritpion);
    vector<Task>& getAll();
};


#endif //TASKMANAGER_TREPO_H
