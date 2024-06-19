#include "user_interface.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repo r{};

    user_interface gui{r};
    gui.show();

    return a.exec();
}