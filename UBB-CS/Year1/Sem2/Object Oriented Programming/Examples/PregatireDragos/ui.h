#pragma once
#include "Service.h"

class UserInterface{
private:
    Service srv;
public:
    UserInterface() = default;
    UserInterface(Service srv){this->srv = srv;}

    void add_building();

    void show_all_buildings();

    void show_all_buildings_to_be_restored(int year);

    void save_all_buildings();

    static void menu();
    void start();
};