//
// Created by Oana on 5/23/2022.
//

#include <fstream>
#include "service.h"

service::service() {

}

void service::read_from_file() {
    std::ifstream f(R"(C:\Users\Dragos\OneDrive\Facultate\Year1Sem2\Object_Oriented_Programming\Examples\pregatire_test_qt_1\read_tasks.txt)");
    if (!f.is_open())
        return;
    tasks.clear();
    Task input{};
    while(f>>input){
        tasks.push_back(input);
    }
    f.close();

}

int service::total_duration_of_tasks_with_priority(int priority) {
    int total = 0;
    for (auto t: tasks){
        if (t.get_priority() == priority)
            total+=t.get_duration();
    }
    if (total==0)
        return -1;
    return total;
}

std::vector<Task> service::sort_tasks() {
    std::vector<Task> tasks_sorted = tasks;
    for (int i=0;i<tasks_sorted.size()-1;i++)
        for(int j=i+1;j<tasks_sorted.size();j++)
            if(tasks_sorted[j]<tasks_sorted[i])
                std::swap(tasks_sorted[i],tasks_sorted[j]);
    return tasks_sorted;
}
