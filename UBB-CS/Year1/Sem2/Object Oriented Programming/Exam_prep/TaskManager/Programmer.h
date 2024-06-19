//
// Created by Dragos on 7/5/2022.
//

#ifndef TASKMANAGER_PROGRAMMER_H
#define TASKMANAGER_PROGRAMMER_H
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>

using namespace std;

class Programmer {
private:
    int id;
    string name;
public:
    Programmer(int id, const string &name);
    Programmer();
    virtual ~Programmer();

    friend istream &operator>>(istream &is, Programmer &programmer);
    friend ostream &operator<<(ostream &os, const Programmer &programmer);



    int getId() const;

    void setId(int id);

    const string &getName() const;

    void setName(const string &name);
};


#endif //TASKMANAGER_PROGRAMMER_H
