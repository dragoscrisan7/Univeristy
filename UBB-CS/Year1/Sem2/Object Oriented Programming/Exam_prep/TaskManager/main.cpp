#include <QApplication>
#include <QPushButton>
#include "gui.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    PRepo prepo{};
    TRepo trepo{};
    Service srv(trepo);

    for(auto& programmer:prepo.getAll()){
        auto GUI = new gui(srv,programmer);
        GUI->show();
    }

    return QApplication::exec();
}
