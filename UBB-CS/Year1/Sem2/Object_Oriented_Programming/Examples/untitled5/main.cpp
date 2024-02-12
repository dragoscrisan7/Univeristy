#include <QApplication>
#include <QPushButton>
#include "Service.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Repository repo{};

    return QApplication::exec();
}
