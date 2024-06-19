//
// Created by Oana on 6/6/2022.
//

#include <vector>
#include <sstream>
#include "Participant.h"

Participant::Participant(const std::string &name, int score) : name(name), score(score) {}

Participant::Participant() {score=0;name="";}

Participant::Participant(const Participant &p) {
    this->name=p.name;
    this->score=p.score;
}

const std::string &Participant::getName() const {
    return name;
}

void Participant::setName(const std::string &name) {
    Participant::name = name;
}

int Participant::getScore() const {
    return score;
}

void Participant::setScore(int score) {
    Participant::score = score;
}

std::ostream &operator<<(std::ostream &os, const Participant &participant) {
    os << participant.name << "," << participant.score;
    return os;
}

std::vector<std::string> tokenize(std::string str, char delimiter);
//{
//    std::vector <std::string> result;
//    std::stringstream ss(str);
//    std::string token;
//    while (getline(ss, token, delimiter))
//        result.push_back(token);
//
//    return result;
//}


std::istream &operator>>(std::istream &is, Participant &participant){
    std::string line;
    getline(is, line);

    std::vector<std::string> tokens = tokenize(line, ',');
    if (tokens.size() != 2)
        return is;
    participant.setName(tokens[0]);
    participant.setScore(std::stoi(tokens[1]));
    return is;
}



