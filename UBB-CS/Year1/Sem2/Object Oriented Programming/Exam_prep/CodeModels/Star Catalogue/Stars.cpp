//
// Created by Dragos on 7/5/2022.
//

#include "Stars.h"

Stars::Stars(const string &name, const string &constellation, int ra, int dec, int diameter) : name(name),
                                                                                               constellation(
                                                                                                       constellation),
                                                                                               RA(ra), Dec(dec),
                                                                                               diameter(diameter) {}

Stars::~Stars() {

}

Stars::Stars() {
    name = "";
    constellation = "";
    RA = 0;
    Dec = 0;
    diameter = 0;
}

const string &Stars::getName() const {
    return name;
}

void Stars::setName(const string &name) {
    Stars::name = name;
}

const string &Stars::getConstellation() const {
    return constellation;
}

void Stars::setConstellation(const string &constellation) {
    Stars::constellation = constellation;
}

int Stars::getRa() const {
    return RA;
}

void Stars::setRa(int ra) {
    RA = ra;
}

int Stars::getDec() const {
    return Dec;
}

void Stars::setDec(int dec) {
    Dec = dec;
}

int Stars::getDiameter() const {
    return diameter;
}

void Stars::setDiameter(int diameter) {
    Stars::diameter = diameter;
}

ostream &operator<<(ostream &os, const Stars &stars) {
    os <<  stars.name << "," << stars.constellation << "," << stars.RA << "," << stars.Dec << "," << stars.diameter;
    return os;
}

std::vector<std::string> tokenize2(std::string str, char delimiter)
{
    std::vector <std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (getline(ss, token, delimiter))
        result.push_back(token);

    return result;
}

std::istream &operator>>(std::istream &is, Stars &s){
    std::string line;
    getline(is, line);

    std::vector<std::string> tokens = tokenize2(line, ',');
    if (tokens.size() != 5)
        return is;
    s.setName(tokens[0]);
    s.setConstellation(tokens[1]);
    s.setRa(std::stoi(tokens[2]));
    s.setDec(std::stoi(tokens[3]));
    s.setDiameter(std::stoi(tokens[4]));
    return is;
}
