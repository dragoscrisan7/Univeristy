#pragma once

#include "Task.h"
#include <vector>

class Repo{
public:
    std::vector<Task> tasks;
    Repo();
    void loadData();
    void sortVector();
};