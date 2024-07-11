//
// Created by Dragos on 6/27/2022.
//

#ifndef QUIZ_GUI_H
#define QUIZ_GUI_H

#include <QWidget>
#include "Service.h"
#include <QMessageBox>


QT_BEGIN_NAMESPACE
namespace Ui { class gui; }
QT_END_NAMESPACE

class gui : public QWidget, public Observer {
Q_OBJECT

public:
    explicit gui(Participants& p, Service& srv, QWidget *parent = Q_NULLPTR);

    ~gui() override;

private:
    Ui::gui *ui;
    Participants& p;
    Service& srv;
    vector<int> answ_id;

    void add_question();
    void to_answer();
    void answer_question();
    void update() override;
    void connect();
};


#endif //QUIZ_GUI_H
