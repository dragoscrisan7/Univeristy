#ifndef TASKMANAGER_UI_H
#define TASKMANAGER_UI_H
#include "Services.h"

class ui
{
private:
    Services* srv;
    static void print_menu();
    void add_task();
    void show_tasks();
    void show_filtered_tasks();
public:
    ui(Services* srv);
    void run();
};

#endif //TASKMANAGER_UI_H
