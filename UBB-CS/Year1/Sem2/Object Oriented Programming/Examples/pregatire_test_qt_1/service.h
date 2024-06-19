//
// Created by Oana on 5/23/2022.
//

#pragma once

#include <vector>
#include "Task.h"

class service {
private:
    std::vector<Task> tasks;

public:
    service();

    void read_from_file();

    int total_duration_of_tasks_with_priority(int priority);

    std::vector<Task> sort_tasks();

};


