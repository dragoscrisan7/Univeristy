#ifndef TASKMANAGER_SERVICES_H
#define TASKMANAGER_SERVICES_H
#include "Repository.h"

class Services
{
private:
    Repository* repo;
public:
    Services(Repository* repo);
    int add(std::string& desc, int dur, int priority);
    Repository* getRepo();
    int FilteredTasks(task* valid_tasks, int priority);
};

#endif //TASKMANAGER_SERVICES_H
