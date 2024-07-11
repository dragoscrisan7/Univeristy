//
// Created by Dragos on 6/29/2022.
//

#ifndef QUESTIONS_AND_ANSWERS_SEARCH_H
#define QUESTIONS_AND_ANSWERS_SEARCH_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class search; }
QT_END_NAMESPACE

class search : public QWidget {
Q_OBJECT

public:
    explicit search(QWidget *parent = nullptr);

    ~search() override;

private:
    Ui::search *ui;
};


#endif //QUESTIONS_AND_ANSWERS_SEARCH_H
