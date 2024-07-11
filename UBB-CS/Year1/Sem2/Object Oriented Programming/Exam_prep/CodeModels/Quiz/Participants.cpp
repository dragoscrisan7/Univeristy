//
// Created by Dragos on 6/27/2022.
//

#include "Participants.h"

Participants::Participants(const string &name) : name(name) {
    score = 0;
}

Participants::Participants() {
    name = "";
    score = 0;
}

Participants::~Participants() {

}

const string &Participants::getName() const {
    return name;
}

void Participants::setName(const string &name) {
    Participants::name = name;
}

int Participants::getScore() const {
    return score;
}

void Participants::setScore(int score) {
    Participants::score = score;
}

ostream &operator<<(ostream &os, const Participants &participants) {
    os << participants.name << "," << participants.score;
    return os;
}

vector<string> tokenize(string &text, char delim){
    vector<string> result;
    stringstream ss(text);
    string info;
    while(getline(ss,info,delim)){
        result.push_back(info);
    }
    return result;
}

istream &operator>>(istream &is, Participants &participants){
    string line;
    getline(is,line);

    vector<string> result = tokenize(line, ',');
    if(result.size() != 2)
        return is;
    participants.setName(result[0]);
    participants.setScore(0);

    return is;
}

void Participants::raise_score(int score) {
    this->score += score;
}
