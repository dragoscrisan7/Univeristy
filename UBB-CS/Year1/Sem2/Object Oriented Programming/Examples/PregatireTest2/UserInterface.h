//
// Created by Oana on 5/2/2022.
//

#pragma once

#include "Service.h"
#include <iostream>

class UserInterface {
private:
    Service service;
public:
    ///Constructors
    UserInterface(){}
    UserInterface(Service serv){service=serv;}

    void initialise_service();

    ///Actual code
    void print_menu();

    void add_building();

    void show_all_buildings();

    void show_all_buildings_to_be_restored();

    void save_all_buildings();

    void start();



};

