//
// Created by Oana on 5/23/2022.
//

#pragma once

#include <string>

class Task {

private:
    std::string description;
    int duration;
    int priority;

public:
    Task();

    Task(std::string desc, int dur, int pri);

    int get_priority() const;

    int get_duration() const;

    bool operator<(const Task& t);

    friend std::istream& operator>>(std::istream& is, Task& t);

    std::string to_string() const;

};

