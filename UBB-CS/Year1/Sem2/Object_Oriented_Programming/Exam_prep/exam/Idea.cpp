#include "Idea.h"
#include <sstream>

const std::string &Idea::getDescription() const {
    return description;
}

void Idea::setDescription(const std::string description) {
    Idea::description = description;
}

const std::string &Idea::getStatus() const {
    return status;
}

void Idea::setStatus(const std::string status) {
    Idea::status = status;
}

const std::string &Idea::getCreator() const {
    return creator;
}

void Idea::setCreator(const std::string creator) {
    Idea::creator = creator;
}

int Idea::getAct() const {
    return act;
}

void Idea::setAct(int act) {
    Idea::act = act;
}

Idea::Idea(const std::string &description, const std::string &status, const std::string &creator, int act)
        : description(description), status(status), creator(creator), act(act) {}

Idea::Idea() {}

Idea::Idea(const Idea &idea) {
    description=idea.description;
    status=idea.status;
    creator=idea.creator;
    act=idea.act;
}

std::ostream &operator<<(std::ostream &os, const Idea &idea) {
    os << idea.description << "," << idea.status << "," << idea.creator << ","
       << idea.act;
    return os;
}

std::vector<std::string> tokenize(std::string str, char delimiter);

std::istream &operator>>(std::istream &is, Idea &idea){
    std::string line;
    getline(is, line);

    std::vector<std::string> tokens = tokenize(line, ',');
    if (tokens.size() != 4)
        return is;
    idea.description=tokens[0];
    idea.status=tokens[1];
    idea.creator=tokens[2];
    idea.act=std::stoi(tokens[3]);
    return is;
}
