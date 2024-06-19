//
// Created by Dragos on 6/27/2022.
//

#include "Questions.h"

Questions::Questions(int id, int score, const string &text, const string &correctAnswer) : id(id), score(score),
                                                                                           text(text), correct_answer(
                correctAnswer) {}

Questions::Questions() {
    id = 0;
    score = 0;
    text = "";
    correct_answer = "";
}

Questions::~Questions() {

}

int Questions::getId() const {
    return id;
}

void Questions::setId(int id) {
    Questions::id = id;
}

int Questions::getScore() const {
    return score;
}

void Questions::setScore(int score) {
    Questions::score = score;
}

const string &Questions::getText() const {
    return text;
}

void Questions::setText(const string &text) {
    Questions::text = text;
}

const string &Questions::getCorrectAnswer() const {
    return correct_answer;
}

void Questions::setCorrectAnswer(const string &correctAnswer) {
    correct_answer = correctAnswer;
}

ostream &operator<<(ostream &os, const Questions &questions) {
    os << questions.id << "," << questions.text << "," << questions.correct_answer << ","<< questions.score;
    return os;
}

vector<string> tokenize(string str, char delimiter){
    vector<string> result;
    string token;
    stringstream ss(str);
    while(getline(ss,token,delimiter)){
        result.push_back(token);
    }

    return result;
}

istream &operator>>(istream &is, Questions &questions){
    string line;
    getline(is, line);

    vector<string> prepared = tokenize(line, ',');
    if(prepared.size() != 4)
        return is;
    questions.setId(stoi(prepared[0]));
    questions.setText(prepared[1]);
    questions.setCorrectAnswer(prepared[2]);
    questions.setScore(stoi(prepared[3]));
    return is;
}
