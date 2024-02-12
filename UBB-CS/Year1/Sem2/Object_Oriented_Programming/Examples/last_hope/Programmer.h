#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Programmer {
private:
    int revised, must_revise;
    string name;
public:
    Programmer(int revised, int mustRevise, const string &name);
    ~Programmer() = default;
    Programmer();

    int getRevised() const;

    void setRevised(int revised);

    int getMustRevise() const;

    void setMustRevise(int mustRevise);

    const string &getName() const;

    void setName(const string &name);

    friend istream &operator>>(istream &is, Programmer& p);

    friend ostream &operator<<(ostream &os, const Programmer &programmer);

    void revise(){revised++;must_revise--;}
};

