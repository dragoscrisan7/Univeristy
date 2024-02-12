#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <chrono>
using namespace std;

class RobotFleet;
class Subjekt;

class Robot{
private:
    int id;
    string location;
};
class Observer{
public:
    virtual void refresh() = 0;
    virtual ~Observer() = 0;
};
class FleetLocationMap: public Observer{
    void show(StateA);
};
class Subjekt{
public:
    std::vector<Observer> observers;
    void attach(Observer o){
    }
    void detach(Observer o){
    }
    virtual void notify() = 0;
};

class RobotFleet: public Subjekt{
private:
    std::vector<Robot> robots;
public:
    void addRobot();
    void removeRobot();
    void notify(){
        for(auto o:observers){
            o.update();
        }
    }
};

int main() {
    std::cout << "Hello World"<<std::endl;
    return 0;
}

