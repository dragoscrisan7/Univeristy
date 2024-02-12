//
// Created by Oana on 5/23/2022.
//

#pragma once

#include <QWidget>
#include "service.h"


QT_BEGIN_NAMESPACE
namespace Ui { class user_interface; }
QT_END_NAMESPACE

class user_interface : public QWidget {
Q_OBJECT

public:
    explicit user_interface(QWidget *parent = nullptr);

    ~user_interface() override;

private:
    Ui::user_interface *ui;
    service serv;

    void connect_signals_and_slots();

    void populate_list();

    void show_duration();


};



