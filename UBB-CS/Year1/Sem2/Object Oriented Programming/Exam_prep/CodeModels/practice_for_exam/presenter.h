//
// Created by Oana on 6/6/2022.
//

#ifndef PRACTICE_FOR_EXAM_PRESENTER_H
#define PRACTICE_FOR_EXAM_PRESENTER_H

#include <QWidget>
#include "Observer.h"
#include "Participant.h"
#include "Service.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Presenter; }
QT_END_NAMESPACE

class Presenter : public QWidget, public Observer {
Q_OBJECT

public:
    explicit Presenter(Service &service, Participant& p, QWidget *parent =Q_NULLPTR);

    ~Presenter() override;

private:
    Ui::Presenter *ui;
    Participant& participant;
    Service& service;
    std::vector<int> answered;

    void connect_sluts_and_signals();
    void add_question();
    void check_question();

    void answer_question();

    void update() override;
};


#endif //PRACTICE_FOR_EXAM_PRESENTER_H
