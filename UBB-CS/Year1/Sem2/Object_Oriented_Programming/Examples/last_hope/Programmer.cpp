//
// Created by Dragos on 6/11/2022.
//

#include "Programmer.h"

Programmer::Programmer(int revised, int mustRevise, const string &name) : revised(revised), must_revise(mustRevise),
                                                                          name(name) {}

Programmer::Programmer() {
    name = "";
    revised = 0;
    must_revise = 0;
}

int Programmer::getRevised() const {
    return revised;
}

void Programmer::setRevised(int revised) {
    Programmer::revised = revised;
}

int Programmer::getMustRevise() const {
    return must_revise;
}

void Programmer::setMustRevise(int mustRevise) {
    must_revise = mustRevise;
}

const string &Programmer::getName() const {
    return name;
}

void Programmer::setName(const string &name) {
    Programmer::name = name;
}

std::vector<std::string> tokenize(std::string str, char delimiter)
{
    std::vector <std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (getline(ss, token, delimiter))
        result.push_back(token);

    return result;
}

istream &operator>>(istream &is, Programmer& p) {
    std::string line;
    getline(is, line);

    std::vector<std::string> tokens = tokenize(line, ',');
    if (tokens.size() != 3)
        return is;
    p.setName(tokens[0]);
    p.setRevised(std::stoi(tokens[1]));
    p.setMustRevise(std::stoi(tokens[2]));
    return is;
}

ostream &operator<<(ostream &os, const Programmer &programmer) {
    os << programmer.name << "," << programmer.revised << "," << programmer.must_revise;
    return os;
}

