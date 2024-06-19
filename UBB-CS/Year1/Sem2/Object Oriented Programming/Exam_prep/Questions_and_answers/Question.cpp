//
// Created by Dragos on 6/28/2022.
//

#include "Question.h"

Question::Question(int id, const string &text, const string &userName) : id(id), text(text), user_name(userName) {}

Question::Question() {
    id = -1;
    text = "";
    user_name = "";
}

Question::~Question() {

}

int Question::getId() const {
    return id;
}

void Question::setId(int id) {
    Question::id = id;
}

const string &Question::getText() const {
    return text;
}

void Question::setText(const string &text) {
    Question::text = text;
}

const string &Question::getUserName() const {
    return user_name;
}

void Question::setUserName(const string &userName) {
    user_name = userName;
}

ostream &operator<<(ostream &os, const Question &question) {
    os << question.id << "," << question.text << "," << question.user_name;
    return os;
}

vector<string> tokenize2(std::string str, char delimiter)
{
    std::vector <std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (getline(ss, token, delimiter))
        result.push_back(token);

    return result;
}

std::istream &operator>>(std::istream &is, Question &u){
    std::string line;
    getline(is, line);

    std::vector<std::string> tokens = tokenize2(line, ',');
    if (tokens.size() != 3)
        return is;
    u.setId(stoi(tokens[0]));
    u.setText(tokens[1]);
    u.setUserName(tokens[2]);
    return is;
}