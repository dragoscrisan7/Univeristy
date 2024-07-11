#include <QApplication>
#include <QPushButton>
#include "gui.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QRepo qr{};
    PRepo pr{};
    Service srv(qr);

    for(auto &p:pr.getALL()){
        gui* g = new gui(p,srv);
        g->show();
    }

    return a.exec();
}
