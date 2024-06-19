//
// Created by Dragos on 7/5/2022.
//

#ifndef TASKMANAGER_SERVICE_H
#define TASKMANAGER_SERVICE_H
#include "TRepo.h"
#include "Observer.h"

class Service : public Observable{
private:
    TRepo& trepo;
public:
    Service(TRepo &trepo);

    virtual ~Service();

    void add(string& desc, string& status, int id);
    void remove(string& desc);
    vector<Task> sorted_by_status();
};


#endif //TASKMANAGER_SERVICE_H
