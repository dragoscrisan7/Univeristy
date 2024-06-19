//
// Created by kamui on 08.06.2022.
//

#ifndef E917_PATRULESCU_RONALD_SANDRINO_SOURCEFILE_H
#define E917_PATRULESCU_RONALD_SANDRINO_SOURCEFILE_H
#include <iostream>

using namespace std;

class SourceFile {
private:
    string name;
    string status; // revised/not_revised
    string creator;
    string reviewer;
public:
    SourceFile(const string &name, const string &status, const string &creator, const string &reviewer);
    SourceFile() = default;

    const string &getName() const;
    const string &getStatus() const;
    const string &getCreator() const;
    const string &getReviewer() const;

    bool isRevised() const { return status == "revised"; }
    bool isNotRevised() const { return status == "not_revised"; }

    friend ostream &operator<<(ostream &os, const SourceFile &file);
    friend istream &operator>>(istream &is, SourceFile &file);

    void revise(const string &reviewer);
};


#endif //E917_PATRULESCU_RONALD_SANDRINO_SOURCEFILE_H
