//
// Created by Dragos on 6/28/2022.
//

#ifndef QUESTIONS_AND_ANSWERS_GUI_H
#define QUESTIONS_AND_ANSWERS_GUI_H

#include <QWidget>
#include "Service.h"

QT_BEGIN_NAMESPACE
namespace Ui { class gui; }
QT_END_NAMESPACE

class gui : public QWidget, public Observer {
Q_OBJECT

public:
    explicit gui(Service& srv, User& u, QWidget *parent = nullptr);

    ~gui() override;

private:
    Ui::gui *ui;
    Service& srv;
    User u;

    void update() override;
    void connect_signals_and_sluts();

    void add_question();
    void add_answer();
    void show_answers();
    void upvote();
    void change_votes();
};


#endif //QUESTIONS_AND_ANSWERS_GUI_H
