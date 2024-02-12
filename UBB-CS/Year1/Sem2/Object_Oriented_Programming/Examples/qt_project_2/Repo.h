#pragma once

#include "Item.h"
#include <vector>
#include <fstream>

class Repo{
public:
    vector<Item> items;
    Repo();

    void read_from_file();
    void Sort();
};