//
// Created by Oana on 5/2/2022.
//

#pragma once
#include "Measurement.h"
#include "BMI.h"
#include "BP.h"
#include "Person.h"

class UserInterface {
private:
    Person p;
public:
    UserInterface(){}

    void print_menu();

    void add_measurement();

    void list_all_measurements();

    void is_healthy();

    void save_all_measurements();

    void start();

    void initialise_person();
};

