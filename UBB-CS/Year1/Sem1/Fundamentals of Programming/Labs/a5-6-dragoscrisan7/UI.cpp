#include "UI.h"
#include <iostream>
#include <unistd.h>

using namespace std;

ui::ui(Service *service, UserService* uservice) {
    this->srv = service;
    this->usrv = uservice;
}
void ui::print_menu() {
    cout<<"1. Administrator mode"<<endl;
    cout<<"2. User mode"<<endl;
    cout<<"0. Exit"<<endl;
}
void ui::print_administrator_menu() {
    cout<<"1. Add a dog"<<endl;
    cout<<"2. Delete a dog"<<endl;
    cout<<"3. Modify a dog"<<endl;
    cout<<"4. See list of dogs"<<endl;
    cout<<"0. Return to menu"<<endl;
}
void ui::print_user_menu() {
    cout<<"1. See all dogs"<<endl;
    cout<<"2. See dogs of given breed and under given age"<<endl;
    cout<<"3. See adoption list"<<endl;
    cout<<"0.Return to menu"<<endl;
}
void ui::selection_menu() {
    cout<<"\n1. Adopt dog"<<endl;
    cout<<"2. Next dog"<<endl;
    cout<<"0. Exit"<<endl;
}
bool ui::validateString(std::string& input) {
    for(int i = 0; i <input.length(); i++)
        if (isdigit(input[i]) != false)
            return false;
    return true;
}

void ui::add_dog() {
    cout<<"Dog name: ";
    std::string name;
    getline(cin,name);
    if ((!validateString(name)) || (name.length() == 0))
        throw std::invalid_argument("Name input not valid!");
    cout<<"Dog breed: ";
    std::string breed;
    getline(cin, breed);
    if ((!validateString(breed)) || (breed.length() == 0))
        throw std::invalid_argument("Breed input not valid!");
    cout<<"Dog Photograph: ";
    std::string photograph;
    getline(cin, photograph);
    if ((!validateString(photograph)) || (photograph.length() == 0) || photograph.find("www") == string::npos)
        throw std::invalid_argument("Photograph input not valid!");
    cout<<"Dog age: ";
    int age;
    cin>>age;
    cin.ignore();
    if(age < 0)
        throw std::invalid_argument("Age cannot be lower than 0");

    srv->addDoggo(name, breed,photograph,age);
}

void ui::del_dog() {
    cout<<"Dog name: ";
    std::string name;
    getline(cin,name);
    if ((!validateString(name)) || (name.length() == 0))
        throw std::invalid_argument("Name input not valid!");

    srv->delDoggo(name);
}

void ui::modify_dog() {
    cout<<"Dog name: ";
    std::string name;
    getline(cin,name);
    if ((!validateString(name)) || (name.length() == 0))
        throw std::invalid_argument("Name input not valid!");

    cout<<"Dog name: ";
    std::string name2;
    getline(cin,name2);
    if ((!validateString(name)) || (name.length() == 0))
       throw std::invalid_argument("Name input not valid!");
    cout<<"Dog breed: ";
    std::string breed2;
    getline(cin, breed2);
    if ((!validateString(breed2)) || (breed2.length() == 0))
        throw std::invalid_argument("Breed input not valid!");
    cout<<"Dog Photograph: ";
    std::string photograph2;
    getline(cin, photograph2);
    if ((!validateString(photograph2)) || (photograph2.length() == 0) || photograph2.find("www") == string::npos)
        throw std::invalid_argument("Photograph input not valid!");
    cout<<"Dog age: ";
    int age2;
    cin>>age2;
    cin.ignore();
    if(age2 < 0)
        throw std::invalid_argument("Age cannot be lower than 0");


    srv->updateDoggo(name,name2,breed2,photograph2,age2);
}

void ui::list_dogs() {
    Repository* repo = srv->getRepo();
    for(int i =0; i< repo->getSize(); i++)
    {
        cout<<(*repo->getAllRepo())[i].toString()<<endl;
    }
}

void ui::user_list() {
    Repository* repo = srv->getRepo();
    int i = 0;
    while(true)
    {
        cout<<(*repo->getAllRepo())[i].toString();
        selection_menu();
        int command = { 0 };
        cout<<"Input command: ";
        cin>>command;
        cin.ignore();
        if(command == 0)
            break;
        else if(repo->getSize() == 0) {
            cout<<"All dogs were adopted"<<endl;
            break;
        }
        else if(command == 1) {
            usrv->add_adopted_dog((*repo->getAllRepo())[i].get_name(), (*repo->getAllRepo())[i].get_breed(),
                                  (*repo->getAllRepo())[i].get_photograph(), (*repo->getAllRepo())[i].get_age());
            srv->delDoggo((*repo->getAllRepo())[i].get_name());
            cout<<"Dog successfully adopted"<<endl;
            sleep(1);
            if(i == repo->getSize()-1)
                i = 0;
        }
        else if(command == 2){
            if(i == repo->getSize()-1)
                i = 0;
            else
                i++;
        }
        else
            cout<<"Wrong input";
    }
}
void ui::adopted_list(){
    user_repo* urepo = usrv->getRepo();
    for(int i =0; i< urepo->getSize(); i++)
    {
        cout<<(*urepo->getAllAdopted())[i].toString()<<endl;
    }
}
void ui::user_filtered_list()
{
    cout<<"Dog breed: ";
    std::string breed;
    getline(cin, breed);
    if ((!validateString(breed)) || (breed.length() == 0))
        throw std::invalid_argument("Breed input not valid!");
    cout<<"Dog age: ";
    int age2;
    cin>>age2;
    cin.ignore();
    if(age2 < 0)
        throw std::invalid_argument("Age cannot be lower than 0");

    auto* valid_dogs = new dog [srv->getRepo()->getSize()];
    int length = usrv->get_all_filtered(valid_dogs, breed, age2);
    int i = 0;
    if(length == 0)
        cout<<"No dogs match your criteria"<<endl;
    else{
        while(true)
        {
            cout<<valid_dogs[i].toString();
            selection_menu();
            int command = { 0 };
            cout<<"Input command: ";
            cin>>command;
            cin.ignore();
            if(command == 0)
                break;
            else if(length == 0) {
                cout<<"All dogs in this criteria are already adopted"<<endl;
                break;
            }
            else if(command == 1) {
                usrv->add_adopted_dog(valid_dogs[i].get_name(), valid_dogs[i].get_breed(),
                                      valid_dogs[i].get_photograph(), valid_dogs[i].get_age());
                srv->delDoggo(valid_dogs[i].get_name());
                cout<<"Dog successfully adopted"<<endl;
                length--;
                sleep(1);
                if(i == length-1)
                    i = 0;
            }
            else if(command == 2){
                if(i == length-1)
                    i = 0;
                else
                    i++;
            }
            else
                cout<<"Wrong input";
            length = usrv->get_all_filtered(valid_dogs, breed, age2);
            if(length == 0) {
                cout << "All dogs in this criteria are already adopted" << endl;
                break;
            }
        }
    }
}

void ui::run() {
    sleep(1);
    cout<<"Welcome to Keep calm and adopt a pet, or more"<<endl;
    while(true)
    {
        ui::print_menu();
        int command = { 0 };
        cout<<"Input command: ";
        cin>>command;
        cin.ignore();
        if(command == 0)
            break;
        else if(command == 1)
        {
            while(true)
            {
                print_administrator_menu();
                int command2 = { 0 };
                cout<<"Input command: ";
                cin>>command2;
                cin.ignore();
                if(command2 == 0)
                    break;
                else if (command2 == 1)
                {
                    try{
                        ui::add_dog();
                    }
                    catch (std::invalid_argument& e){
                        std::cerr << e.what() << std::endl;
                    }
                }
                else if (command2 == 2)
                {
                    try{
                        ui::del_dog();
                    }
                    catch (std::invalid_argument& e){
                        std::cerr << e.what() << std::endl;
                    }

                }
                else if (command2 == 3)
                {
                    try{
                        ui::modify_dog();
                    }
                    catch (std::invalid_argument& e){
                        std::cerr << e.what() << std::endl;
                    }
                }
                else if (command2 == 4)
                {
                    ui::list_dogs();
                }
                else {
                    cout << "Wrong input" << endl;
                }
                sleep(1);
            }
        }
        else if(command == 2)
        {
            while(true)
            {
                ui::print_user_menu();
                int command2 = { 0 };
                cout<<"Input command: ";
                cin>>command2;
                cin.ignore();
                if(command2 == 0)
                    break;
                else if (command2 == 1)
                {
                    try{
                        ui::user_list();
                    }
                    catch (std::invalid_argument& e){
                        std::cerr << e.what() << std::endl;
                    }

                }
                else if (command2 == 2)
                {
                    try{
                        ui::user_filtered_list();
                    }
                    catch (std::invalid_argument& e){
                        std::cerr << e.what() << std::endl;
                    }
                }
                else if (command2 == 3)
                {
                    try{
                        ui::adopted_list();
                    }
                    catch (std::invalid_argument& e){
                        std::cerr << e.what() << std::endl;
                    }
                }
                else
                {
                    cout<<"Wrong input"<<endl;
                }
                sleep(1);
            }
        }
        else
            cout<<"Wrong input"<<endl;
    }
}
