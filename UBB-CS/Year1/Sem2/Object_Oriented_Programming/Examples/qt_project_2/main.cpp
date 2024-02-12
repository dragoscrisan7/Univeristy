#include <QtWidgets/QApplication>
#include "user_interface2.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Repo r{};

    user_interface2 gui(r);
    gui.show();

    return a.exec();
}
