//
// Created by kamui on 08.06.2022.
//

#include "SourceFile.h"

SourceFile::SourceFile(const string &name, const string &status, const string &creator, const string &reviewer) : name(
        name), status(status), creator(creator), reviewer(reviewer) {}

const string &SourceFile::getName() const {
    return name;
}

const string &SourceFile::getStatus() const {
    return status;
}

const string &SourceFile::getCreator() const {
    return creator;
}

const string &SourceFile::getReviewer() const {
    return reviewer;
}

ostream &operator<<(ostream &os, const SourceFile &file) {
    os << file.name << "," << file.status << "," << file.creator << "," << file.reviewer;
    return os;
}

istream &operator>>(istream &is, SourceFile &file) {
    getline(is, file.name, ',');
    getline(is, file.status, ',');
    getline(is, file.creator, ',');
    getline(is, file.reviewer, '\n');

    return is;
}

void SourceFile::revise(const string &reviewer) {
    status = "revised";
    this->reviewer = reviewer;
}
