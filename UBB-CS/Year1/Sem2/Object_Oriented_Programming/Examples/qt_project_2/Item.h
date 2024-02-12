#pragma once

#include <iostream>

using namespace std;

class Item{
private:
    string category;
    string name;
    int quantity;
public:
    Item();
    Item(string c, string n, int q);

    string get_category(){return this->category;}
    string get_name(){return this->name;}
    int get_quantity(){return this->quantity;}

    string To_string();
};