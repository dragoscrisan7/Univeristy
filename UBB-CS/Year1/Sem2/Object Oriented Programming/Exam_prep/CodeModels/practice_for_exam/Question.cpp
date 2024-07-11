//
// Created by Oana on 6/6/2022.
//

#include <vector>
#include <sstream>
#include "Question.h"

Question::Question(int id_, std::string t, std::string ca, int sc) {
    this->id = id_;
    this->text = t;
    this->correct_answer = ca;
    this->score = sc;
}

Question::Question(const Question &q) {
    this->id = q.id;
    this->text = q.text;
    this->correct_answer = q.correct_answer;
    this->score = q.score;
}

Question::Question() {
    id = 0;
    text="";
    correct_answer="";
    score=0;
}



std::ostream &operator<<(std::ostream &os, const Question &question) {
    os << question.id << "," << question.text << "," << question.correct_answer
       << "," << question.score;
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


std::istream &operator>>(std::istream &is, Question &question){
    std::string line;
    getline(is, line);

    std::vector<std::string> tokens = tokenize(line, ',');
    if (tokens.size() != 4)
        return is;
    question.setId(std::stoi(tokens[0]));
    question.setText(tokens[1]);
    question.setCorrectAnswer(tokens[2]);
    question.setScore(std::stoi(tokens[3]));
    return is;
}

int Question::getId() const {
    return id;
}

const std::string &Question::getText() const {
    return text;
}

const std::string &Question::getCorrectAnswer() const {
    return correct_answer;
}

int Question::getScore() const {
    return score;
}

bool Question::operator==(const Question &rhs) const {
    return id == rhs.id;
}

bool Question::operator!=(const Question &rhs) const {
    return !(rhs == *this);
}

void Question::setId(int id) {
    Question::id = id;
}

void Question::setText(const std::string &text) {
    Question::text = text;
}

void Question::setCorrectAnswer(const std::string &correctAnswer) {
    correct_answer = correctAnswer;
}

void Question::setScore(int score) {
    Question::score = score;
}

