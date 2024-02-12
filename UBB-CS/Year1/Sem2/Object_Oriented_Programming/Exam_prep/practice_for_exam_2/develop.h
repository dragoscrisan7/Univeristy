//
// Created by Oana on 6/7/2022.
//

#ifndef PRACTICE_FOR_EXAM_2_DEVELOP_H
#define PRACTICE_FOR_EXAM_2_DEVELOP_H

#include <QWidget>
#include "Idea.h"
#include "TableModel.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Develop; }
QT_END_NAMESPACE

class Develop : public QWidget {
Q_OBJECT

public:
    explicit Develop(Idea& idea, QWidget *parent = nullptr);

    ~Develop() override;

private:
    Ui::Develop *ui;
    Idea& idea;

    void connectSignalsAndSlots();

    void save();
};


#endif //PRACTICE_FOR_EXAM_2_DEVELOP_H
