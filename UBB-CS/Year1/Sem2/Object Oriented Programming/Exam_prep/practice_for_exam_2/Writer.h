//
// Created by Oana on 6/7/2022.
//

#pragma once
#include <string>
#include <vector>
#include <ostream>

class Writer {
private:
    std::string name;
    std::string expertise;
public:

    Writer(const std::string &name, const std::string &expertise);

    Writer();

    Writer(const Writer& writer);

    const std::string getName() const;

    void setName(const std::string name);

    friend std::ostream &operator<<(std::ostream &os, const Writer &writer);

    friend std::istream &operator>>(std::istream &is, Writer &writer);

    const std::string getExpertise() const;

    void setExpertise(const std::string expertise);
};

