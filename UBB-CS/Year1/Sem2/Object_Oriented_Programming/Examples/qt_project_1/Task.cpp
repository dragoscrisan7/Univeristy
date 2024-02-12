#include "Task.h"

Task::Task() {
    description = "";
    duration = 0;
    priority = 0;
}

std::string Task::To_string() const{
    std::string str = "Description: " + description + ", duration: " + std::to_string(duration) + ", priority: "+std::to_string(priority) + "\n";
    return str;
}

Task::Task(std::string desc, int dur, int prio){
    description = desc;
    duration = dur;
    priority = prio;
}

