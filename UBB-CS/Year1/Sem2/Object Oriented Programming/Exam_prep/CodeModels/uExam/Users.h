//
// Created by Dragos on 7/6/2022.
//

#ifndef UEXAM_USERS_H
#define UEXAM_USERS_H
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

class Users {
private:
    string name;
public:
    Users(const string &name);
    Users();
    virtual ~Users();

    const string &getName() const;
    void setName(const string &name);

    friend ostream &operator<<(ostream &os, const Users &users);
    friend istream &operator>>(istream &is, Users &users);
};


#endif //UEXAM_USERS_H
