#ifndef QT_PROJECT_2_USER_INTERFACE2_H
#define QT_PROJECT_2_USER_INTERFACE2_H

#include <QWidget>
#include "Repo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class user_interface2; }
QT_END_NAMESPACE

class user_interface2 : public QWidget {
Q_OBJECT

public:
    explicit user_interface2(Repo& r, QWidget *parent = nullptr);

    ~user_interface2() override;

private:
    Ui::user_interface2 *ui;
    Repo& repo;

    void Populate();

    void connectSignalsAndSlots();

public slots:
    void Press_Button();
    void Press_Button2();
};


#endif //QT_PROJECT_2_USER_INTERFACE2_H
