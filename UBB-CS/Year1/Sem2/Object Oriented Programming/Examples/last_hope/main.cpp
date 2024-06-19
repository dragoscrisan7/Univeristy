#include <QApplication>
#include <QPushButton>
#include "user_interface.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Repository repo;

    for(auto p:repo.getProgrammers()){
        user_interface *user_i;
        user_i = new user_interface(p, repo);
        user_i->setWindowTitle(QString::fromStdString(p.getName()));
        user_i->show();
    }

    return a.exec();
}
