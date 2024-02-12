#include "Repository.h"

Repository::Repository(DynamicVector<task> *dyn) {
    this->dyn = dyn;
}

int Repository::getSize() {
    return this->dyn->getSize();
}

void Repository::add(const task &t) {
    this->dyn->add(t);
}

void Repository::initialRepo() {
    task task1("Solve_OOP_assignment", 120, 1);
    task task2("Respond_to_emails", 45, 2);
    task task3("Eat_sushi", 30, 3);
    task task4("Visit_parent", 240, 1);
    task task5("Buy_a_jacket", 120, 2);
    this->dyn->add(task1);
    this->dyn->add(task2);
    this->dyn->add(task3);
    this->dyn->add(task4);
    this->dyn->add(task5);
}

DynamicVector<task> *Repository::getAllRepo() {
    return this->dyn;
}

int Repository::find(std::string &desc) {
    for(int i=0;i<dyn->getSize();i++){
        if((*dyn)[i].getDescription() == desc)
            return i;
    }
    return -1;
}

