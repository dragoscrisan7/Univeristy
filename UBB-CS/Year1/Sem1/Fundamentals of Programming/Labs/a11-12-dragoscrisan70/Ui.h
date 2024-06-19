#pragma once

#include "Service.h"
#include "UserService.h"

class ui
{
private:
    Service *srv;
    UserService *usrv;

    static void print_menu();
    static void print_administrator_menu();
    static void print_user_menu();
    static void selection_menu();

    void add_dog();
    void del_dog();
    void modify_dog();
    void list_dogs();

    void openFile();

    void user_list();
    void adopted_list();
    void user_filtered_list();

    static bool validateString(std::string& input);
public:
    ui(Service* s, UserService* us);

    void run();
};
