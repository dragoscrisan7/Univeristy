#pragma once
#include <QWidget>
#include "Repository.h"
#include "Observer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class user_interface; }
QT_END_NAMESPACE

class user_interface : public QWidget, public Observer {
Q_OBJECT

public:
    explicit user_interface(Programmer& p, Repository &repo, QWidget *parent = nullptr);

    ~user_interface() override;

private:
    Ui::user_interface *ui;
    Repository &repo;
    Programmer& p;

    void populate();
    void add_file();

    void connect_sluts_and_buttons();

    void revise();
};
