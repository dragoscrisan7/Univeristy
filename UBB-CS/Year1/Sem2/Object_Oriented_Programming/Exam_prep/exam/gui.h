//
// Created by Dragos on 6/11/2022.
//

#ifndef EXAM_GUI_H
#define EXAM_GUI_H

#include <QWidget>
#include "Service.h"
#include "Writer.h"
#include "TableModel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class gui; }
QT_END_NAMESPACE

class gui : public QWidget {
Q_OBJECT

public:
    explicit gui(Service& service, Writer& writer, TableModel* tableModel, QWidget *parent = nullptr);

    ~gui() override;

private:
    Ui::gui *ui;
    Service& service;
    Writer& writer;
    TableModel* model;

    void connectSignalsAndSlots();

    void addIdea();

    void acceptIdea();

    void savePlot();

    void developIdea();
};


#endif //EXAM_GUI_H
