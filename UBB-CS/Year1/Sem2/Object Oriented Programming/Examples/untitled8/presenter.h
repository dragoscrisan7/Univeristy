#ifndef UNTITLED8_PRESENTER_H
#define UNTITLED8_PRESENTER_H

#include <QWidget>
#include "Participant.h"
#include "Observer.h"
#include "Service.h"
#include "ui_Presenter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Presenter; }
QT_END_NAMESPACE

class Presenter : public QWidget, public Observer {
Q_OBJECT

public:
    explicit Presenter(Service& s, Participant& p, QWidget *parent = nullptr);

    ~Presenter() override;

private:
    Ui::Presenter *ui;
    Participant& p;
    Service& srv;
    vector<int> answered;

    void update();
    void add_question();
    void answer_question();
};


#endif //UNTITLED8_PRESENTER_H
