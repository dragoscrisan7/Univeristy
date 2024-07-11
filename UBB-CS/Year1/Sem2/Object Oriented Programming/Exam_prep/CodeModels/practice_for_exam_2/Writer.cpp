//
// Created by Oana on 6/7/2022.
//

#include <sstream>
#include "Writer.h"

Writer::Writer(const std::string &name, const std::string &expertise) : name(name), expertise(expertise) {}

const std::string Writer::getName() const {
    return name;
}

void Writer::setName(const std::string name) {
    Writer::name = name;
}

const std::string Writer::getExpertise() const {
    return expertise;
}

void Writer::setExpertise(const std::string expertise) {
    Writer::expertise = expertise;
}

std::ostream &operator<<(std::ostream &os, const Writer &writer) {
    os << writer.name << "," << writer.expertise;
    return os;
}

Writer::Writer() {name="";expertise="";}

Writer::Writer(const Writer &writer) {
    name=writer.name;
    expertise=writer.expertise;
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


std::istream &operator>>(std::istream &is, Writer &writer){
    std::string line;
    getline(is, line);

    std::vector<std::string> tokens = tokenize(line, ',');
    if (tokens.size() != 2)
        return is;
    writer.setName(tokens[0]);
    writer.setExpertise(tokens[1]);
    return is;

}