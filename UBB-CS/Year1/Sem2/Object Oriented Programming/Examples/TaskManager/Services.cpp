#include "Services.h"

Services::Services(Repository *repo) {
    this->repo = repo;
    this->repo->initialRepo();
}

int Services::add(std::string& desc, int dur, int priority) {
    if(this->repo->find(desc) != -1)
        return 0;
    else{
        task task1(desc, dur, priority);
        this->repo->add(task1);
        return 1;
    }
}

Repository *Services::getRepo() {
    return this->repo;
}

int Services::FilteredTasks(task *valid_tasks, int priority) {
    int cont = 0;
    int length = this->repo->getSize();
    for(int i=0; i<length; i++)
    {
        task task1((*this->repo->getAllRepo())[i]);
        if(task1.getPriority() > priority){
            valid_tasks[cont] = task1;
            cont++;
        }
    }
    for(int i=0 ;i<cont-1; i++)
    {
        for(int j =i+1;j<cont;j++)
        {
            if(valid_tasks[j].getDuration() > valid_tasks[i].getDuration())
            {
                auto task1 = valid_tasks[i];
                valid_tasks[i] = valid_tasks[j];
                valid_tasks[j] = task1;
            }
        }
    }
    return cont;
}
