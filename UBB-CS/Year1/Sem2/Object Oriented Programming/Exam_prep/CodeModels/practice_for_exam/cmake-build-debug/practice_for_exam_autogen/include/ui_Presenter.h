/********************************************************************************
** Form generated from reading UI file 'presenter.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRESENTER_H
#define UI_PRESENTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Presenter
{
public:
    QGridLayout *gridLayout;
    QListWidget *listWidget;
    QLabel *questions;
    QHBoxLayout *horizontalLayout;
    QLabel *label_answer;
    QLineEdit *answerLineEdit;
    QLabel *label_id;
    QLineEdit *idLineEdit;
    QLabel *label_text;
    QLineEdit *textLineEdit;
    QPushButton *addButton;
    QLabel *label_correct_answer;
    QLineEdit *correctAnswerLineEdit;
    QLabel *label_score;
    QLineEdit *scoreLineEdit;
    QPushButton *answerButton;

    void setupUi(QWidget *Presenter)
    {
        if (Presenter->objectName().isEmpty())
            Presenter->setObjectName(QString::fromUtf8("Presenter"));
        Presenter->resize(580, 599);
        gridLayout = new QGridLayout(Presenter);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        listWidget = new QListWidget(Presenter);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        gridLayout->addWidget(listWidget, 0, 0, 1, 3);

        questions = new QLabel(Presenter);
        questions->setObjectName(QString::fromUtf8("questions"));

        gridLayout->addWidget(questions, 0, 3, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_answer = new QLabel(Presenter);
        label_answer->setObjectName(QString::fromUtf8("label_answer"));

        horizontalLayout->addWidget(label_answer);

        answerLineEdit = new QLineEdit(Presenter);
        answerLineEdit->setObjectName(QString::fromUtf8("answerLineEdit"));

        horizontalLayout->addWidget(answerLineEdit);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 2);

        label_id = new QLabel(Presenter);
        label_id->setObjectName(QString::fromUtf8("label_id"));

        gridLayout->addWidget(label_id, 2, 0, 1, 1);

        idLineEdit = new QLineEdit(Presenter);
        idLineEdit->setObjectName(QString::fromUtf8("idLineEdit"));

        gridLayout->addWidget(idLineEdit, 2, 1, 1, 1);

        label_text = new QLabel(Presenter);
        label_text->setObjectName(QString::fromUtf8("label_text"));

        gridLayout->addWidget(label_text, 3, 0, 1, 1);

        textLineEdit = new QLineEdit(Presenter);
        textLineEdit->setObjectName(QString::fromUtf8("textLineEdit"));

        gridLayout->addWidget(textLineEdit, 3, 1, 1, 1);

        addButton = new QPushButton(Presenter);
        addButton->setObjectName(QString::fromUtf8("addButton"));

        gridLayout->addWidget(addButton, 3, 2, 2, 2);

        label_correct_answer = new QLabel(Presenter);
        label_correct_answer->setObjectName(QString::fromUtf8("label_correct_answer"));

        gridLayout->addWidget(label_correct_answer, 4, 0, 1, 1);

        correctAnswerLineEdit = new QLineEdit(Presenter);
        correctAnswerLineEdit->setObjectName(QString::fromUtf8("correctAnswerLineEdit"));

        gridLayout->addWidget(correctAnswerLineEdit, 4, 1, 1, 1);

        label_score = new QLabel(Presenter);
        label_score->setObjectName(QString::fromUtf8("label_score"));

        gridLayout->addWidget(label_score, 5, 0, 1, 1);

        scoreLineEdit = new QLineEdit(Presenter);
        scoreLineEdit->setObjectName(QString::fromUtf8("scoreLineEdit"));

        gridLayout->addWidget(scoreLineEdit, 5, 1, 1, 1);

        answerButton = new QPushButton(Presenter);
        answerButton->setObjectName(QString::fromUtf8("answerButton"));

        gridLayout->addWidget(answerButton, 1, 3, 1, 1);


        retranslateUi(Presenter);

        QMetaObject::connectSlotsByName(Presenter);
    } // setupUi

    void retranslateUi(QWidget *Presenter)
    {
        Presenter->setWindowTitle(QCoreApplication::translate("Presenter", "Presenter", nullptr));
        questions->setText(QCoreApplication::translate("Presenter", "Questions", nullptr));
        label_answer->setText(QCoreApplication::translate("Presenter", "Answer", nullptr));
        label_id->setText(QCoreApplication::translate("Presenter", "Id", nullptr));
        label_text->setText(QCoreApplication::translate("Presenter", "Text", nullptr));
        addButton->setText(QCoreApplication::translate("Presenter", "Add question", nullptr));
        label_correct_answer->setText(QCoreApplication::translate("Presenter", "Correct answer", nullptr));
        label_score->setText(QCoreApplication::translate("Presenter", "Score", nullptr));
        answerButton->setText(QCoreApplication::translate("Presenter", "Answer question", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Presenter: public Ui_Presenter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRESENTER_H
