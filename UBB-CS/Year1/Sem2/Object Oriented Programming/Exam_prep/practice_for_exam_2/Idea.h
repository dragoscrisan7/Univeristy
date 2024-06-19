//
// Created by Oana on 6/7/2022.
//

#pragma once
#include <vector>
#include <string>
#include <ostream>

class Idea {
private:
    std::string description;
    std::string status;
    std::string creator;
    int act;
public:
    const std::string &getDescription() const;

    void setDescription(const std::string description);

    const std::string &getStatus() const;

    void setStatus(const std::string status);

    const std::string &getCreator() const;

    void setCreator(const std::string creator);

    int getAct() const;

    void setAct(int act);

    friend std::ostream &operator<<(std::ostream &os, const Idea &idea);

    friend std::istream &operator>>(std::istream &is, Idea &idea);

    Idea();

    Idea(const std::string &description, const std::string &status, const std::string &creator, int act);

    Idea(const Idea& idea);

};

