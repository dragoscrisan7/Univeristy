#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class SourceFile {
private:
    string name, creator, status, reviewer;
public:
    SourceFile(const string &name, const string &creator, const string &status, const string &reviewer);
    ~SourceFile() = default;
    SourceFile();

    const string &getName() const;

    void setName(const string &name);

    const string &getCreator() const;

    void setCreator(const string &creator);

    const string &getStatus() const;

    void setStatus(const string &status);

    const string &getReviewer() const;

    void setReviewer(const string &reviewer);

    friend istream &operator>>(istream &is, SourceFile& sf);

    friend ostream &operator<<(ostream &os, const SourceFile &file);

    bool isRevised() const { return status == "revised"; }
    bool isNotRevised() const { return status == "not_revised"; }

    void revise(const string &reviewer);
};

