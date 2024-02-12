#pragma once
#include <iostream>

class Building{
protected:
    std::string address;
    int constructionYear;
public:
    Building(){
        address = "";
        constructionYear = 0;
    }

    int age(){return 2022 - this->constructionYear;}

    virtual bool mustBeRestored() = 0;
    virtual bool canBeDemolished() = 0;
    virtual std::string toString() = 0;

    ~Building() = default;
};
