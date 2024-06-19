//
// Created by Dragos on 6/28/2022.
//

#include "User.h"

User::User(const string &name) : name(name) {}

User::User() {
    name = "";
}

User::~User() {

}

const string &User::getName() const {
    return name;
}

void User::setName(const string &name) {
    User::name = name;
}

ostream &operator<<(ostream &os, const User &user) {
    os << user.name;
    return os;
}

vector<string> tokenize(std::string str, char delimiter)
{
    std::vector <std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (getline(ss, token, delimiter))
        result.push_back(token);

    return result;
}

std::istream &operator>>(std::istream &is, User &u){
    std::string line;
    getline(is, line);

    std::vector<std::string> tokens = tokenize(line, ',');
    if (tokens.size() != 1)
        return is;
    u.setName(tokens[0]);
    return is;
}


