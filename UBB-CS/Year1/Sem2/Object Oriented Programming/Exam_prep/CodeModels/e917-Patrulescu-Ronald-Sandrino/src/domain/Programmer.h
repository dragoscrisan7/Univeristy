//
// Created by kamui on 08.06.2022.
//

#ifndef E917_PATRULESCU_RONALD_SANDRINO_PROGRAMMER_H
#define E917_PATRULESCU_RONALD_SANDRINO_PROGRAMMER_H
#include <iostream>

using namespace std;

class Programmer {
private:
    string name;
    int revised;
    int toRevise;
public:
    Programmer(const string &name, int revised, int toRevise);
    Programmer() = default;

    const string &getName() const;
    int getRevised() const;
    int getToRevise() const;

    friend ostream &operator<<(ostream &os, const Programmer &programmer);
    friend istream &operator>>(istream &is, Programmer &programmer);

    void revise();
};


#endif //E917_PATRULESCU_RONALD_SANDRINO_PROGRAMMER_H
