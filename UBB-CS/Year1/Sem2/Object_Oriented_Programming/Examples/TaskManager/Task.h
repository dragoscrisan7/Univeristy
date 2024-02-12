#ifndef TASKMANAGER_TASK_H
#define TASKMANAGER_TASK_H
#include <iostream>

class task{
private:
    std::string description;
    int duration;
    int priority;
public:
    task(const std::string& desc, const int& dur, const int& prio);
    task(){priority = 0;}
    ~task();

    int getDuration() const{return duration;}
    int getPriority() const{return priority;}
    std::string getDescription(){return description;}

    std::string toString() const;
};

#endif //TASKMANAGER_TASK_H
