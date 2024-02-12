//
// Created by Dragos on 6/10/2022.
//

#include "Question.h"
#include <sstream>

Question::Question(const Question& q) {
    id = q.id;
    score = q.score;
    text = q.text;
    correct_answer = q.correct_answer;
}
Question::Question() {
    id = 0;
    score = 0;
    text = "";
    correct_answer = "";
}
Question::Question(int id, const string &text, const string &correctAnswer, int score) : id(id), score(score),
                                                                                         text(text), correct_answer(
                correctAnswer) {}

Question::~Question() {
}


int Question::getId() const {
    return id;
}

void Question::setId(int id) {
    Question::id = id;
}

int Question::getScore() const {
    return score;
}

void Question::setScore(int score) {
    Question::score = score;
}

const string &Question::getText() const {
    return text;
}

void Question::setText(const string &text) {
    Question::text = text;
}

const string &Question::getCorrectAnswer() const {
    return correct_answer;
}

void Question::setCorrectAnswer(const string &correctAnswer) {
    correct_answer = correctAnswer;
}

ostream &operator<<(ostream &os, const Question &question) {
    os << "id: " << question.id << " score: " << question.score << " text: " << question.text << " correct_answer: "
       << question.correct_answer;
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

istream &operator>>(std::istream &is, Question &question){
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

bool Question::operator==(const Question &rhs) const {
    return id == rhs.id;
}
bool Question::operator!=(const Question &rhs) const {
    return !(rhs == *this);
}