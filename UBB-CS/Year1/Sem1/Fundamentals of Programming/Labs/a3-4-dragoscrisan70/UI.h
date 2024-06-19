#ifndef A3_4_DRAGOSCRISAN7_UI_H
#define A3_4_DRAGOSCRISAN7_UI_H
#include <Services.h>

typedef struct
{
    Service* serv;
}Ui;

Ui* createUI(Service* s);
void destroyUI(Ui* ui);

void run(Ui* ui);

#endif //A3_4_DRAGOSCRISAN7_UI_H
