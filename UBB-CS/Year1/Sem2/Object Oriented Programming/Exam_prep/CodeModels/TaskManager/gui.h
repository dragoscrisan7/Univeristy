//
// Created by Dragos on 7/5/2022.
//

#ifndef TASKMANAGER_GUI_H
#define TASKMANAGER_GUI_H
#include "Observer.h"
#include "PRepo.h"
#include "Service.h"
#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class gui; }
QT_END_NAMESPACE

class gui : public QWidget, public Observer{
Q_OBJECT

public:
    explicit gui(Service& srv, Programmer pr, QWidget *parent = nullptr);

    ~gui() override;

    void connect();
    void update() override;
    void add();
    void remove();
    void start();
    void done();

    void check_clicked();

private:
    Ui::gui *ui;
    Service& srv;
    Programmer pr;
};


#endif //TASKMANAGER_GUI_H
