//
// Created by Dragos on 6/28/2022.
//

#ifndef QUESTIONS_AND_ANSWERS_USER_H
#define QUESTIONS_AND_ANSWERS_USER_H
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class User {
private:
    string name;
public:
    User(const string &name);

    User();

    virtual ~User();

    const string &getName() const;

    void setName(const string &name);

    friend ostream &operator<<(ostream &os, const User &user);
    friend istream &operator>>(istream &is, User &user);
};


#endif //QUESTIONS_AND_ANSWERS_USER_H
