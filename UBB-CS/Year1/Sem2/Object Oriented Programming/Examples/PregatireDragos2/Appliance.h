#pragma once
#include <iostream>

class Appliance{
protected:
    std::string id;
    double weight;
public:
    virtual double consumedElectricity() = 0;
    virtual std::string toString() = 0;
};
