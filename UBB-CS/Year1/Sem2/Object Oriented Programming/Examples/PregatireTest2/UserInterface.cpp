//
// Created by Oana on 5/2/2022.
//

#include "UserInterface.h"

void UserInterface::print_menu(){
    std::cout<<"1. Add building.\n";
    std::cout<<"2. Show all buildings.\n";
    std::cout<<"3. Show all buildings that must be restored, older than a given year.\n";
    std::cout<<"4. Save all buildings.\n";
    std::cout<<"5. Exit application.\n";
}

void UserInterface::add_building() {
    std::cout<<"What kind of building is it?\n1.Block\n2.House\n";
    int option;
    std::cin>>option;
    if (option==1)
    {
        std::string address;
        int construction_year, total_apartments, occupied_apartments;
        std::cout<<"Address: ";
        std::cin>>address;
        std::cout<<"Construction year: ";
        std::cin>>construction_year;
        std::cout<<"Total apartments: ";
        std::cin>>total_apartments;
        std::cout<<"Occupied apartments: ";
        std::cin>>occupied_apartments;
        Block* b = new Block{address,construction_year,total_apartments,occupied_apartments};
        service.add_building(b);
    }
    else{
        std::string address;
        int construction_year;
        bool is_historical;
        std::cout<<"Address: ";
        std::cin>>address;
        std::cout<<"Construction year: ";
        std::cin>>construction_year;
        std::cout<<"Is it historical? 1/0\n";
        std::cin>>is_historical;
        House *b = new House(address,construction_year,is_historical);
        service.add_building(b);
    }
    std::cout<<"Added building to list.\n";

}

void UserInterface::show_all_buildings() {
    std::vector<Building*> all_buildings = service.get_all_buildings();
    std::cout<<"All buildings: \n";
    for (auto b: all_buildings)
        std::cout<<(*b).to_string();
}

void UserInterface::show_all_buildings_to_be_restored() {
    std::vector<Building*> to_be_restored = service.get_all_to_be_restored();
    int older_than ;
    std::cout<<"All buildings older than x years. x = ";
    std::cin>>older_than;
    for (auto b : to_be_restored)
        if (2022 - (*b).construction_year> older_than)
            std::cout<<(*b).to_string();
}

void UserInterface::save_all_buildings() {
    std::cout<<"Saving all buildings to be restored to file: restore.txt\n";
    std::vector<Building*> to_be_restored = service.get_all_to_be_restored();
    service.write_to_file("C:/Users/Oana/CLionProjects/PregatireTest2/restore.txt", to_be_restored);
    std::cout<<"Buildings to be restored saved to file.\n Saving all buildings to be demolished to file: demolish.txt\n";
    std::vector<Building*> to_be_demolished = service.get_all_to_be_demolished();
    service.write_to_file("C:/Users/Oana/CLionProjects/PregatireTest2/demolish.txt", to_be_demolished);
    std::cout<<"Buildings to be demolished saved to file.\n";
}

void UserInterface::start() {
    std::cout<<"Welcome to old buildings.\n";
    initialise_service();
    while(true)
    {
        print_menu();
        int option;
        std::cout<<"Choose an option: ";
        std::cin>>option;
        switch(option){
            case 1:
                add_building();
                break;
            case 2:
                show_all_buildings();
                break;
            case 3:
                show_all_buildings_to_be_restored();
                break;
            case 4:
                save_all_buildings();
                break;
            case 5:
                return;
        }
    }

}

void UserInterface::initialise_service() {
    House* h1 = new House("address 1", 1887, true);
    House* h2 = new House("address 2", 1987, false);
    Block* b1 = new Block("address 3", 1950, 20, 19);
    Block* b2 = new Block("address 4", 1978, 30, 1);
    service.add_building(h1);
    service.add_building(h2);
    service.add_building(b1);
    service.add_building(b2);
}


