#ifndef QT_PROJECT_1_USER_INTERFACE_H
#define QT_PROJECT_1_USER_INTERFACE_H

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

private:
    Ui::user_interface *ui;
    Repo& repo;

    void populateList();

    void connectSignalsAndSlots();

public slots:
    void press_button();
};


#endif //QT_PROJECT_1_USER_INTERFACE_H
