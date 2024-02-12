#include <QApplication>
#include <QPushButton>
#include "IdeaRepo.h"
#include "WriterRepo.h"
#include "gui.h"
#include "Service.h"
#include "TableModel.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    IdeaRepo ideaRepo{};
    WriterRepo writerRepo{};
    Service service{ideaRepo};
    TableModel tableModel{service};

    std::vector<Writer> allWriters = writerRepo.getAllWriters();
    for (int i=0;i<allWriters.size();i++){
        GUI* gui = new GUI{service, allWriters[i], &tableModel};
        gui->show();
    }

    return a.exec();
}
