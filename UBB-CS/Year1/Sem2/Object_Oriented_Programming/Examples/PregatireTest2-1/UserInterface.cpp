//
// Created by Oana on 5/2/2022.
//

#include "UserInterface.h"
#include <iostream>
#include <exception>

void UserInterface::print_menu() {
    std::cout<<"1. Add measurement.\n";
    std::cout<<"2. Show all measurements.\n";
    std::cout<<"3. Check for health.\n";
    std::cout<<"4. Save all measurements to file.\n";
    std::cout<<"5. Exit.\n";
}

void UserInterface::add_measurement() {
    std::cout<<"Which kind of measurement will be added?\n1.BMI\n2.BP\n";
    std::cout<<"Choose: ";
    int option;
    std::cin>>option;
    std::string date;
    try {
        std::cout << "Date of measurement: ";
        std::cin >> date;
        if(date.length() != 10)
           throw std::exception();
    }
    catch (...) {
        std::cout<<"Incorrect date format.\n";
        return;
    }
    if (option==1)
    {
        double value;
        std::cout<<"BMI Value: ";
        std::cin>>value;
        auto m = new BMI(value, date);
        p.add_measurement(m);
    }
    else{
        int sys,dia;
        std::cout<<"Systolic value: ";
        std::cin>>sys;
        std::cout<<"Diastolic value: ";
        std::cin>>dia;
        auto m = new BP(sys, dia, date);
        p.add_measurement(m);
    }
    std::cout<<"Measurement added.\n";
}

void UserInterface::list_all_measurements() {
    std::vector<Measurement*> all_measurements = p.get_all_measurements();
    std::cout<<p.name<<"\n";
    for (auto m : all_measurements)
        std::cout<<m->to_string();
}

void UserInterface::is_healthy() {
    int month;
    std::cout<<"Input for the current month: ";
    std::cin>>month;
    if (p.is_healthy(month))
        std::cout<<p.name<<" is healthy\n";
    else
        std::cout<<p.name<<" isn't healthy.\n";
}

void UserInterface::save_all_measurements() {
    std::cout<<"Save all measurements after a given date: ";
    std::string date;
    std::cin>>date;
    p.write_to_file("C:/Users/Oana/CLionProjects/PregatireTest2-1/save.txt", date);
    std::cout<<"Measurements saved to file.\n";

}

void UserInterface::start() {
    std::cout<<"Welcome.\n";
    p.name = "oana";
    initialise_person();
    while(true)
    {
        int option;
        print_menu();
        std::cout<<"Choose an option: ";
        std::cin>>option;
        switch(option)
        {
            case 1:
                add_measurement();
                break;
            case 2:
                list_all_measurements();
                break;
            case 3:
                is_healthy();
                break;
            case 4:
                save_all_measurements();
                break;
            case 5:
                return;
        }
    }

}

void UserInterface::initialise_person() {
    auto b1 = new BMI(16, "2022.03.04");
    auto b2 = new BMI(21.5,"2022.04.19");
    BP* b3 = new BP(101,65,"2022.04.16");
    BP* b4 = new BP(105, 68, "2022.05.02");
    BMI* b5 = new BMI(28,"2022.03.16");
    p.add_measurement(b1);
    p.add_measurement(b2);
    p.add_measurement(b3);
    p.add_measurement(b4);
    p.add_measurement(b5);
}



