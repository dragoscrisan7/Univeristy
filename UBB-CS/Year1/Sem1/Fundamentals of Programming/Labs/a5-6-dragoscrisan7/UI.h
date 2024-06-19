#ifndef A5_6_DRAGOSCRISAN7_UI_H
#define A5_6_DRAGOSCRISAN7_UI_H
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

    void user_list();
    void adopted_list();
    void user_filtered_list();

    static bool validateString(std::string& input);
public:
    ui(Service* s, UserService* us);

    void run();
};

#endif //A5_6_DRAGOSCRISAN7_UI_H
