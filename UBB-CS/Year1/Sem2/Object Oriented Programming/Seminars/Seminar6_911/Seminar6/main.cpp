#include "Seminar6.h"
#include <QtWidgets/QApplication>
#include "TeachersWidget.h"
#include "StudentsModel.h"
#include <QSortFilterProxyModel>
#include <QRegularExpression>
#include <memory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    Repository repo{"Students.txt"};

    auto model = std::make_unique<StudentsModel>(repo);

    auto mainTeacher = std::make_unique<TeachersWidget>(model.get());
    mainTeacher->setWindowTitle("Main teacher");
    mainTeacher->show();

    auto filteredModel = std::make_unique<QSortFilterProxyModel>();
    filteredModel->setSourceModel(model.get());
    filteredModel->setFilterRegularExpression(QRegularExpression("911"));
    filteredModel->setFilterKeyColumn(1);
    auto teacherFor911 = std::make_unique<TeachersWidget>(filteredModel.get());
    teacherFor911->setWindowTitle("Teacher for 911");
    teacherFor911->show();

    return a.exec();
}
