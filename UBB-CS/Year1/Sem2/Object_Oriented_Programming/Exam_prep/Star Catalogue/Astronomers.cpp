//
// Created by Dragos on 7/5/2022.
//

#include "Astronomers.h"

Astronomers::Astronomers(const string &name, const string &constellation) : name(name), constellation(constellation) {}

Astronomers::Astronomers() {
    name = "";
    constellation = "";
}

Astronomers::~Astronomers() {

}

const string &Astronomers::getName() const {
    return name;
}

void Astronomers::setName(const string &name) {
    Astronomers::name = name;
}

const string &Astronomers::getConstellation() const {
    return constellation;
}

void Astronomers::setConstellation(const string &constellation) {
    Astronomers::constellation = constellation;
}

ostream &operator<<(ostream &os, const Astronomers &astronomers) {
    os << astronomers.name << "," << astronomers.constellation;
    return os;
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

std::istream &operator>>(std::istream &is, Astronomers &a){
    std::string line;
    getline(is, line);

    std::vector<std::string> tokens = tokenize(line, ',');
    if (tokens.size() != 2)
        return is;
    a.setName(tokens[0]);
    a.setConstellation(tokens[1]);
    return is;
}
