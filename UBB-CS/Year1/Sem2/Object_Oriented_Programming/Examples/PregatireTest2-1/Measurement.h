//
// Created by Oana on 5/2/2022.
//

#pragma once
#include <string>
class Measurement {
public:
    virtual bool is_normal() const = 0;
    virtual std::string to_string() const = 0;

    std::string date;

};


