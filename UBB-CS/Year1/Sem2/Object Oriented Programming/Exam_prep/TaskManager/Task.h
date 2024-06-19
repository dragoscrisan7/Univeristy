//
// Created by Dragos on 7/5/2022.
//

#ifndef TASKMANAGER_TASK_H
#define TASKMANAGER_TASK_H
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>

using namespace std;

class Task {
private:
    string description, status;
    int id;
public:
    Task(const string &description, const string &status, int id);
    Task();
    virtual ~Task();

    friend ostream &operator<<(ostream &os, const Task &task);
    friend istream &operator>>(istream &is, Task &task);




    const string &getDescription() const;

    void setDescription(const string &description);

    const string &getStatus() const;

    void setStatus(const string &status);

    int getId() const;

    void setId(int id);
};


#endif //TASKMANAGER_TASK_H
