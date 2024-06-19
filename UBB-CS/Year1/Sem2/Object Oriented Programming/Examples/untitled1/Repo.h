#pragma once

#include "Weather.h"
#include <vector>

class Repo{
public:
    vector<Weather> weathers;
    Repo();
    void loadData();
    void sortVector();
};