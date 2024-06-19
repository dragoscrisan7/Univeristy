//
// Created by Dragos on 6/28/2022.
//

#include "Answer.h"

Answer::Answer(int id, int qid, const string &text, const string &userName, int votes) : id(id), qid(qid), text(text),
                                                                                         user_name(userName),
                                                                                         votes(votes) {}

Answer::Answer() {
    id = -1;
    qid = -1;
    text = "";
    user_name = "";
    votes = 0;
}

Answer::~Answer() {

}

int Answer::getId() const {
    return id;
}

void Answer::setId(int id) {
    Answer::id = id;
}

int Answer::getQid() const {
    return qid;
}

void Answer::setQid(int qid) {
    Answer::qid = qid;
}

const string &Answer::getText() const {
    return text;
}

void Answer::setText(const string &text) {
    Answer::text = text;
}

const string &Answer::getUserName() const {
    return user_name;
}

void Answer::setUserName(const string &userName) {
    user_name = userName;
}

int Answer::getVotes() const {
    return votes;
}

void Answer::setVotes(int votes) {
    Answer::votes = votes;
}

ostream &operator<<(ostream &os, const Answer &answer) {
    os << answer.id << "," << answer.qid << "," << answer.text << "," << answer.user_name << "," << answer.votes;
    return os;
}

vector<string> tokenize3(std::string str, char delimiter)
{
    std::vector <std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (getline(ss, token, delimiter))
        result.push_back(token);

    return result;
}

std::istream &operator>>(std::istream &is, Answer &u){
    std::string line;
    getline(is, line);

    std::vector<std::string> tokens = tokenize3(line, ',');
    if (tokens.size() != 5)
        return is;
    u.setId(stoi(tokens[0]));
    u.setQid(stoi(tokens[1]));
    u.setText(tokens[2]);
    u.setUserName(tokens[3]);
    u.setVotes(stoi(tokens[4]));
    return is;
}
