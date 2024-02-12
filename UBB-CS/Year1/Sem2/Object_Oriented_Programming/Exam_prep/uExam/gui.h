//
// Created by Dragos on 7/6/2022.
//

#ifndef UEXAM_GUI_H
#define UEXAM_GUI_H
#include <QMessageBox>
#include <QWidget>

#include "Users.h"
#include "Service.h"
#include "Observer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class gui; }
QT_END_NAMESPACE

class gui : public QWidget, public Observer {
Q_OBJECT

public:
    explicit gui(Service& srv, Users u, QWidget *parent = nullptr);

    ~gui() override;
    void update() override;
    void connect();

    void add_subscription();
    void add_post();
    void update_post();
private:
    Ui::gui *ui;
    Service& srv;
    Users user;
};


#endif //UEXAM_GUI_H
