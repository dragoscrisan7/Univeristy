//
// Created by Dragos on 7/5/2022.
//

#ifndef STAR_CATALOGUE_ASTRONOMERS_H
#define STAR_CATALOGUE_ASTRONOMERS_H
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

class Astronomers {
private:
    string name, constellation;
public:
    Astronomers(const string &name, const string &constellation);
    Astronomers();
    virtual ~Astronomers();

    friend ostream &operator<<(ostream &os, const Astronomers &astronomers);
    friend istream &operator>>(istream &is, Astronomers &astronomers);

    const string &getName() const;

    void setName(const string &name);

    const string &getConstellation() const;

    void setConstellation(const string &constellation);
};


#endif //STAR_CATALOGUE_ASTRONOMERS_H
