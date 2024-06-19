#pragma once
#include <iostream>

class Task{
private:
    std::string description;
    int duration;
    int priority;
public:
    Task();

    Task(std::string desc, int dur, int prio);

    int get_priority() const{return this->priority;}
    int get_duration() const{return this->duration;}
    std::string To_string() const;
};