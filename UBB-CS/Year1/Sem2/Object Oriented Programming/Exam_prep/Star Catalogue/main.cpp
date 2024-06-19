#include <QApplication>
#include <QPushButton>
#include "gui.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    ARepo arepo{};
    SRepo srepo{};
    Service srv(srepo);

    for(auto& a: arepo.getAll()){
        auto GUI = new gui(srv,a);
        GUI->show();
    }

    return QApplication::exec();
}
