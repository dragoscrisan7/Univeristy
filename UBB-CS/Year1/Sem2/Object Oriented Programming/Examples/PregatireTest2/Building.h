//
// Created by Oana on 5/2/2022.
//

#pragma once


#include <string>

class Building {
public:
    std::string address;
    int construction_year;
public:
    Building(){
        address="";
        construction_year=0;
    }

    virtual bool must_be_restored() const = 0;
    virtual bool can_be_demolished() const = 0;
    virtual std::string to_string() const = 0;

};

