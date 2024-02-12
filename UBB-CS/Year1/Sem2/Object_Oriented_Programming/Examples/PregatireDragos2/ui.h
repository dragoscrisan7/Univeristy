#pragma once
#include "Service.h"

using namespace std;

class UserInterface{
private:
    Service srv;
public:
    UserInterface() = default;
    UserInterface(Service srv){this->srv = srv;}

    void menu();
    void start();

    void addAppliance();
    void showAll();
    void showAllEfficient();
    void saveToFile();
};