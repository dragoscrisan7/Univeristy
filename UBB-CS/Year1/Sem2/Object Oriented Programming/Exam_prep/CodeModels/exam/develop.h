//
// Created by Dragos on 6/11/2022.
//

#ifndef EXAM_DEVELOP_H
#define EXAM_DEVELOP_H

#include <QWidget>
#include "Idea.h"
#include "TableModel.h"


QT_BEGIN_NAMESPACE
namespace Ui { class develop; }
QT_END_NAMESPACE

class develop : public QWidget {
Q_OBJECT

public:
    explicit develop(Idea& idea, QWidget *parent = nullptr);

    ~develop() override;

private:
    Ui::develop *ui;
    Idea& idea;

    void connectSignalsAndSlots();

    void save();
};


#endif //EXAM_DEVELOP_H
