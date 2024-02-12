#include <QApplication>
#include <QPushButton>
#include "IdeaRepo.h"
#include "WriterRepo.h"
#include "Service.h"
#include "TableModel.h"
#include "gui.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    IdeaRepo ideaRepo{};
    WriterRepo writerRepo{};
    Service service{ideaRepo};
    TableModel tableModel{service};

    std::vector<Writer> allWriters = writerRepo.getAllWriters();
    for (int i=0;i<allWriters.size();i++){
        gui* GUI = new gui{service, allWriters[i], &tableModel};
        GUI->show();
    }

    return a.exec();
}
