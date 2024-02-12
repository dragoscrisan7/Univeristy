#ifndef UNTITLED1_USER_INTERFACE_H
#define UNTITLED1_USER_INTERFACE_H

#include <QWidget>
#include "Repo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class user_interface; }
QT_END_NAMESPACE

class user_interface : public QWidget {
Q_OBJECT

public:
    explicit user_interface(Repo& r, QWidget *parent = nullptr);

    ~user_interface() override;

    void populateList();

    void connectSignalsAndSlots();
private:
    Ui::user_interface *ui;
    Repo& repo;

    void press_button();
    void press_button2();
};


#endif //UNTITLED1_USER_INTERFACE_H
