//
// Created by Oana on 6/7/2022.
//

#ifndef PRACTICE_FOR_EXAM_2_GUI_H
#define PRACTICE_FOR_EXAM_2_GUI_H

#include <QWidget>
#include "Service.h"
#include "Writer.h"
#include "TableModel.h"


QT_BEGIN_NAMESPACE
namespace Ui { class GUI; }
QT_END_NAMESPACE

class GUI : public QWidget {
Q_OBJECT

public:
    explicit GUI(Service& service, Writer& writer, TableModel* tableModel, QWidget *parent = nullptr);

    ~GUI() override;

private:
    Ui::GUI *ui;
    Service& service;
    Writer& writer;
    TableModel* model;

    void connectSignalsAndSlots();

    void addIdea();

    void acceptIdea();

    void savePlot();

    void developIdea();

};


#endif //PRACTICE_FOR_EXAM_2_GUI_H
