#include "SourceFile.h"

SourceFile::SourceFile(const string &name, const string &creator, const string &status, const string &reviewer) : name(
        name), creator(creator), status(status), reviewer(reviewer) {}

SourceFile::SourceFile() {
    name = "";
    status = "not_reviewed";
    creator = "";
    reviewer = "";
}

const string &SourceFile::getName() const {
    return name;
}

void SourceFile::setName(const string &name) {
    SourceFile::name = name;
}

const string &SourceFile::getCreator() const {
    return creator;
}

void SourceFile::setCreator(const string &creator) {
    SourceFile::creator = creator;
}

const string &SourceFile::getStatus() const {
    return status;
}

void SourceFile::setStatus(const string &status) {
    SourceFile::status = status;
}

const string &SourceFile::getReviewer() const {
    return reviewer;
}

void SourceFile::setReviewer(const string &reviewer) {
    SourceFile::reviewer = reviewer;
}

std::vector<std::string> tokenize(std::string str, char delimiter);

std::istream &operator>>(std::istream &is, SourceFile &sf){
    std::string line;
    getline(is, line);

    std::vector<std::string> tokens = tokenize(line, ',');
    if (tokens.size() != 4)
        return is;
    sf.setName(tokens[0]);
    sf.setCreator(tokens[1]);
    sf.setReviewer(tokens[2]);
    sf.setStatus(tokens[3]);
    return is;
}

ostream &operator<<(ostream &os, const SourceFile &file) {
    os << file.name << "," << file.creator << "," << file.reviewer << "," << file.status;
    return os;
}

void SourceFile::revise(const string &reviewer) {
    status = "revised";
    this->reviewer = reviewer;
}