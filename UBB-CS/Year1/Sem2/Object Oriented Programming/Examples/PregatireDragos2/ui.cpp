#include "ui.h"
#include <execution>
void UserInterface::menu() {
    cout<<"1.Add new Appliance\n2.Show all appliances\n3.Show all efficient appliances\n4.Save to file\n0.Exit\n";
}

void UserInterface::start() {
    while(true){
        menu();
        int x;
        cin>>x;
        cin.ignore();
        switch (x) {
            case 0:
                return;
            case 1:
                addAppliance();
                break;
            case 2:
                showAll();
                break;
            case 3:
                showAllEfficient();
                break;
            case 4:
                saveToFile();
                break;
        }
    }
}

void UserInterface::addAppliance() {
    cout<<"Type 1 for refrigerator and 2 for dish washer: ";
    int x;
    cin>>x;
    cin.ignore();
    std::string id;
    double weight;
    if(x == 1){
        bool hF;
        std::string el;
        cout<<"id: ";
        cin>>id;
        cout<<"weight: ";
        cin>>weight;
        cout<<"has freezer(1/0): ";
        cin>>hF;
        cout<<"Electricity usage class: ";
        cin>>el;
        auto *r = new Refrigerator(id, weight, el, hF);
        srv.addAppliance(r);
        cout<<"Refrigerator added\n";
    }
    else if(x == 2){
        cout<<"id: ";
        cin>>id;
        cout<<"weight: ";
        cin>>weight;
        double wsl, cefouh;
        cout<<"Washing Cyde Length: ";
        cin>>wsl;
        cout<<"consumed Electricity For One Hour: ";
        cin>>cefouh;
        auto *dw = new DishWasher(id,weight, wsl, cefouh);
        srv.addAppliance(dw);
        cout<<"Dishwasher added\n";
    }
    else
        cout<<"Wrong input";
}

void UserInterface::showAll() {
    for(auto a: srv.getAllAppliances()){
        cout<<a->toString();
    }
}

void UserInterface::showAllEfficient() {
    double value;
    vector<Appliance*> v;
    cout<<"value: ";
    cin>>value;
    cin.ignore();
    v = srv.getAllWithConsumedElectricityLessThan(value);
    for(auto a:v){
        cout<<a->toString();
    }
}

void UserInterface::saveToFile() {
    double value;
    vector<Appliance*> v;
    cout<<"value: ";
    cin>>value;
    cin.ignore();
    for(auto a:srv.getAllAppliances()){
        if(a->consumedElectricity() > value)
            v.push_back(a);
    }

    srv.writeToFile(R"(C:\Users\Dragos\OneDrive\Facultate\Year1Sem2\Object_Oriented_Programming\Examples\PregatireDragos2\saved.txt)", value);
}

bool comp(int a, int b){
    if(a>b)
        return false;
    else
        return true;
}