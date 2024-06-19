#include "Ui.h"
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
    cout<<"4. Open file containing adoption list"<<endl;
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
    cout<<"Dog breed: ";
    std::string breed;
    getline(cin, breed);
    cout<<"Dog Photograph: ";
    std::string photograph;
    getline(cin, photograph);
    cout<<"Dog age: ";
    int age;
    cin>>age;
    cin.ignore();
    dog dog1(name, breed, photograph, age);
    srv->addDoggo(name, breed,photograph,age);
}

void ui::del_dog() {
    cout<<"Dog name: ";
    std::string name;
    getline(cin,name);
    cout<<"Dog breed: ";
    std::string breed;
    getline(cin, breed);

    srv->delDoggo(name,breed);
}

void ui::modify_dog() {
    cout<<"Dog name: ";
    std::string name;
    getline(cin,name);
    cout<<"Dog breed: ";
    std::string breed;
    getline(cin, breed);

    cout<<"Dog name: ";
    std::string name2;
    getline(cin,name2);
    cout<<"Dog breed: ";
    std::string breed2;
    getline(cin, breed2);
    cout<<"Dog Photograph: ";
    std::string photograph2;
    getline(cin, photograph2);
    cout<<"Dog age: ";
    int age2;
    cin>>age2;
    cin.ignore();

    srv->updateDoggo(name,breed,name2,breed2,photograph2,age2);
}

void ui::list_dogs() {
    Repository* repo = srv->getRepo();
    for(int i =0; i< repo->getSize(); i++)
    {
        cout<<repo->getDog()[i].toString()<<endl;
    }
}

void ui::user_list() {
    Repository* repo = srv->getRepo();
    int i = 0;
    while(true)
    {
        cout<<repo->getDog()[i].toString();
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
            usrv->add_adopted_dog(repo->getDog()[i].get_name(), repo->getDog()[i].get_breed(),
                                  repo->getDog()[i].get_photograph(), repo->getDog()[i].get_age());
            cout<<"Dog successfully adopted"<<endl;
            sleep(1);
            if(i >= repo->getSize()-1)
                i = 0;
        }
        else if(command == 2){
            if(i >= repo->getSize()-1)
                i = 0;
            else
                i++;
        }
        else
            cout<<"Wrong input";
    }
}
void ui::adopted_list(){
    UserRepo* urepo = usrv->getRepo();
    for(int i =0; i< urepo->getSize(); i++)
    {
        cout<<urepo->getDog()[i].toString()<<endl;
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
    vector<dog> valid_dogs;
    ///auto* valid_dogs = new dog [srv->getRepo()->getSize()];
    int length = usrv->get_all_filtered(valid_dogs, breed, age2);
    auto it = valid_dogs.begin();
    if(length == 0)
        cout<<"No dogs match your criteria"<<endl;
    else{
        while(true)
        {
            cout<<(*it).toString();
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
                usrv->add_adopted_dog((*it).get_name(), (*it).get_breed(),
                                      (*it).get_photograph(), (*it).get_age());
                valid_dogs.erase(it);
                cout<<"Dog successfully adopted"<<endl;
                length--;
                sleep(1);
                if(it >= valid_dogs.end())
                    it = valid_dogs.begin();
            }
            else if(command == 2){
                it++;
                if(it >= valid_dogs.end())
                    it = valid_dogs.begin();
            }
            else
                cout<<"Wrong input";
            sleep(1);
            if(length == 0) {
                cout << "All dogs in this criteria are already adopted" << endl;
                break;
            }
        }
    }
}

void ui::openFile() {
    if(usrv->getRepo()->getSize() == 0)
        cout<<"There are no dogs adopted yet"<<endl;
    else
        usrv->openFile();
}

void ui::run() {
    cout<<"Welcome to Keep calm and adopt a pet, or more"<<endl;
    std::cout<<"Please choose the file destination: 1.csv or 2.html\n";
    int type;
    std::cin>>type;
    std::cin.ignore();
    string filetype;
    usrv->repoType(type);
    sleep(1);
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
                else if ( command2 == 4){
                    ui::openFile();
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
