#ifndef TASKMANAGER_REPOSITORY_H
#define TASKMANAGER_REPOSITORY_H
#include "DynamicArray.h"

class Repository{
private:
    DynamicVector<task>* dyn;
public:
    Repository(DynamicVector<task>* dyn);
    Repository() = default;
    int getSize();
    void add(const task& t);
    void initialRepo();
    DynamicVector<task>* getAllRepo();
    int find(std::string& desc);
};

#endif //TASKMANAGER_REPOSITORY_H
