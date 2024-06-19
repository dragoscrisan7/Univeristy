#include "ui.h"

using namespace std;

void UserInterface::start() {
    while(true){
        menu();
        int option;
        std::cin>>option;
        std::cin.ignore();
        if(option == 0)
            break;
        else{
            if(option == 1){
                add_building();
            }
            else if(option == 2){
                show_all_buildings();
            }
            else if(option == 3) {
                int year;
                cout<<"year: ";
                cin>>year;
                cin.ignore();
                show_all_buildings_to_be_restored(year);
            }
            else if(option == 4){
                save_all_buildings();
            }
            else {
                std::cout << "wrong input\n";
                break;
            }
        }
    }
}

void UserInterface::menu() {
    cout<<"1.Add building\n2.Show all buildings\n3.Show all buildings that must be restored, older than a given year\n";
    cout<<"4.Save all buildings to file\n0.Exit\n";
}

void UserInterface::add_building() {
    cout<<"Press 1 for block and 2 for house\n";
    int opt;
    cin>>opt;
    cin.ignore();
    if(opt == 1){
        string ad;
        int cY, tA, oA;
        cout<<"address: ";
        cin>>ad;
        cout<<"construction year: ";
        cin>>cY;
        cout<<"Total apartments: ";
        cin>>tA;
        cout<<"Occupied apartments: ";
        cin>>oA;
        auto *b = new Block(ad,cY,tA,oA);
        srv.addBuilding(b);
        cout<<"Block added"<<endl;
    }
    else if(opt == 2){
        string ad;
        int cY;
        bool iH;
        cout<<"address: ";
        cin>>ad;
        cout<<"construction year: ";
        cin>>cY;
        cout<<"is historical: ";
        cin>>iH;
        auto *h = new House(ad,cY,iH);
        srv.addBuilding(h);
        cout<<"House added"<<endl;
    }
    else
        std::cout<<"wrong input\n";
}

void UserInterface::show_all_buildings() {
    auto buildings = srv.getAllBuildings();
    for(auto b:buildings){
        cout<<b->toString();
    }
}

void UserInterface::show_all_buildings_to_be_restored(int year) {
    for(auto b:srv.getAllBuildings()){
        if(b->mustBeRestored() && b->age()>year)
            cout<<b->toString();
    }
}

void UserInterface::save_all_buildings() {
    std::vector<Building*> v = srv.getAllToBeRestored();
    srv.writeToFile(R"(C:\Users\Dragos\OneDrive\Facultate\Year1Sem2\Object_Oriented_Programming\Examples\PregatireDragos\restored.txt)", v);
    std::vector<Building*> v2 = srv.getAllToBeDemolished();
    srv.writeToFile(R"(C:\Users\Dragos\OneDrive\Facultate\Year1Sem2\Object_Oriented_Programming\Examples\PregatireDragos\demolished.txt)",v2);
}
