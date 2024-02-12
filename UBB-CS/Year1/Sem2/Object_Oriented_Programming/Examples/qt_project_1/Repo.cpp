#include "Repo.h"
#include <sstream>
#include <fstream>
#include <algorithm>


Repo::Repo() = default;

void Repo::loadData() {
    std::ifstream f(R"(C:\Users\Dragos\OneDrive\Facultate\Year1Sem2\Object_Oriented_Programming\Examples\qt_project_1\tasks)");
    if(!f.is_open())
        return;
    std::string text;
    while(std::getline(f, text)){
        std::stringstream s(text);
        std::string d;
        int dur, prio;
        s >> d;
        s >> dur;
        s >> prio;
        Task t{ d, dur, prio};
        this->tasks.push_back(t);
    }
}

bool compare(Task v1,Task v2) {
    if (v1.get_priority() > v2.get_priority()) {
        return false;
    }
    else if (v1.get_priority() == v2.get_priority() && v1.get_duration() > v2.get_duration())
    {
        return false;
    }
    return true;
}

void Repo::sortVector() {
    sort(this->tasks.begin(), this->tasks.end(), compare);
}
