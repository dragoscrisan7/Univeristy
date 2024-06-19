//
// Created by Dragos on 7/5/2022.
//

#include "Programmer.h"

Programmer::Programmer(int id, const string &name) : id(id), name(name) {}

Programmer::Programmer() {
    id = 0;
    name = "";
}

Programmer::~Programmer() {

}

int Programmer::getId() const {
    return id;
}

void Programmer::setId(int id) {
    Programmer::id = id;
}

const string &Programmer::getName() const {
    return name;
}

void Programmer::setName(const string &name) {
    Programmer::name = name;
}

ostream &operator<<(ostream &os, const Programmer &programmer) {
    os <<  programmer.id << "," << programmer.name;
    return os;
}

vector<string> separate_strings(string line, char delimiter)
{
    vector<string> separated;
    stringstream l(line);
    string token;
    while (getline(l, token, delimiter))
        separated.push_back(token);

    return separated;
}

std::istream &operator>>(std::istream &is, Programmer &p){
    string line;
    getline(is, line);

    vector<string> tokens = separate_strings(line, ',');
    if (tokens.size() != 2)
        return is;
    p.setId(stoi(tokens[0]));
    p.setName(tokens[1]);
    return is;
}
