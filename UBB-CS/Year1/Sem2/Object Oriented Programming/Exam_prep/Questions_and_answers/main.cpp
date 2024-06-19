#include <QApplication>
#include <QPushButton>
#include "Repository.h"
#include "gui.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Repository repo{};
    Service srv(repo);

    for(auto &u:repo.get_users()){
        auto GUI = new gui(srv, u);
        GUI->show();
    }

    return a.exec();
}
