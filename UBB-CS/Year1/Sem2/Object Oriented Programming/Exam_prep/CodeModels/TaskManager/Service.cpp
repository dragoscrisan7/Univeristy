//
// Created by Dragos on 7/5/2022.
//

#include "Service.h"

Service::Service(TRepo &trepo) : trepo(trepo) {}

Service::~Service() {

}

void Service::remove(string& desc) {
    trepo.remove(desc);
    notify_all_observables();
}

void Service::add(string& desc, string& status, int id) {
    Task t(desc,status,id);
    trepo.add(t);
    notify_all_observables();
}

vector<Task> Service::sorted_by_status() {
    vector<Task> sbs = trepo.getAll();

    sort(sbs.begin(),sbs.end(),[](Task t1, Task t2){return t1.getStatus()<t2.getStatus();});

    return sbs;
}
