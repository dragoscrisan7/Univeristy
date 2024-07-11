//
// Created by Dragos on 7/5/2022.
//

#ifndef STAR_CATALOGUE_STARS_H
#define STAR_CATALOGUE_STARS_H
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

class Stars {
private:
    string name, constellation;
    int RA, Dec, diameter;
public:
    Stars(const string &name, const string &constellation, int ra, int dec, int diameter);
    Stars();
    virtual ~Stars();

    friend ostream &operator<<(ostream &os, const Stars &stars);
    friend istream &operator>>(istream &is, Stars &stars);




    const string &getName() const;

    void setName(const string &name);

    const string &getConstellation() const;

    void setConstellation(const string &constellation);

    int getRa() const;

    void setRa(int ra);

    int getDec() const;

    void setDec(int dec);

    int getDiameter() const;

    void setDiameter(int diameter);
};


#endif //STAR_CATALOGUE_STARS_H
