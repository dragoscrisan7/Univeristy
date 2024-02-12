#include "Ui.h"
#include <iostream>

using namespace std;

ui::ui(Services *srv) {
    this->srv = srv;
}

void ui::print_menu() {
    cout<<"1.Add a new task"<<endl;
    cout<<"2.Show all tasks"<<endl;
    cout<<"3.Show all tasks with less priority than selected"<<endl;
    cout<<"0.Exit"<<endl;
}

void ui::run() {
    while(true)
    {
        ui::print_menu();
        int command = { 0 };
        cout<<"Input command: ";
        cin>>command;
        cin.ignore();
        if(command == 0)
            break;
        else if(command == 1) {
            ui::add_task();
        }
        else if(command == 2){
            ui::show_tasks();
        }
        else if(command == 3){
            ui::show_filtered_tasks();
        }
        else
            cout<<"Wrong input"<<endl;
    }
}

void ui::add_task() {
    string desc;
    cout<<"Description: ";
    getline(cin,desc);
    int duration;
    cout<<"Duration: ";
    cin>>duration;
    cin.ignore();
    int priority;
    cout<<"Priority: ";
    cin>>priority;
    cin.ignore();

    int c = srv->add(desc,duration,priority);
    if(c==1)
        std::cout<<"Task succesfully added"<<std::endl;
    else if(c==0)
        cout<<"Task already exists"<<std::endl;
}

void ui::show_tasks() {
    Repository* repo = srv->getRepo();
    for(int i=0; i<repo->getSize(); i++)
        cout<<(*repo->getAllRepo())[i].toString()<<endl;
}

void ui::show_filtered_tasks() {
    int priority;
    cout<<"Priority: ";
    cin>>priority;
    cin.ignore();

    auto* valid_tasks = new task[srv->getRepo()->getSize()];
    int length = srv->FilteredTasks(valid_tasks, priority);
    if(length == 0)
        cout<<"No tasks match your criteria"<<endl;
    else
    {
        for(int j=0; j<length; j++)
            cout<<valid_tasks[j].toString()<<endl;
    }
}



