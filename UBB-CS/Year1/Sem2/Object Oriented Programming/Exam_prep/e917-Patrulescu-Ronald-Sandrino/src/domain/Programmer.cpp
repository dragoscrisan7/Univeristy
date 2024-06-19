//
// Created by kamui on 08.06.2022.
//

#include "Programmer.h"

Programmer::Programmer(const string &name, int revised, int toRevise) : name(name), revised(revised),
                                                                        toRevise(toRevise) {}

const string &Programmer::getName() const {
    return name;
}

int Programmer::getRevised() const {
    return revised;
}

int Programmer::getToRevise() const {
    return toRevise;
}

ostream &operator<<(ostream &os, const Programmer &programmer) {
    os << programmer.name << "," << programmer.revised << "," << programmer.toRevise;
    return os;
}

istream &operator>>(istream &is, Programmer &programmer) {
    getline(is, programmer.name, ',');
    string tmp;
    getline(is, tmp, ',');
    programmer.revised = atoi(tmp.c_str());
    getline(is, tmp, '\n');
    programmer.toRevise = atoi(tmp.c_str());

    return is;
}

void Programmer::revise() {
    revised++;
    toRevise--;
}
