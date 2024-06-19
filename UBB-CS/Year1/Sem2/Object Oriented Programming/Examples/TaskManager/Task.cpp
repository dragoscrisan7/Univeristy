#include "Task.h"

task::task(const std::string& desc, const int& dur, const int& prio) {
    this->description = desc;
    this->duration = dur;
    this->priority = prio;
}

std::string task::toString() const{
    auto str_duration = std::to_string(this->duration);
    auto str_priority = std::to_string(this->priority);
    task task1("a",10,10);
    return this->description + " | " + str_duration + " | " + str_priority;
}

task::~task() = default;
