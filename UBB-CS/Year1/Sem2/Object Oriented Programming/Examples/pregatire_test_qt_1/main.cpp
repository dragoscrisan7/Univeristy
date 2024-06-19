#include <QApplication>
#include <QPushButton>
#include "user_interface.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    user_interface ui;
    ui.show();
    return a.exec();
}
