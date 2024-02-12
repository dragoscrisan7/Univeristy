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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Presenter
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QListWidget *listWidget;
    QLabel *q_label;
    QHBoxLayout *horizontalLayout_8;
    QHBoxLayout *horizontalLayout_6;
    QLabel *answerlabel;
    QLineEdit *answerLine;
    QPushButton *answerButton;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *idLabel;
    QLineEdit *idLine;
    QHBoxLayout *horizontalLayout_3;
    QLabel *scoreLabel;
    QLineEdit *scoreLine;
    QHBoxLayout *horizontalLayout_4;
    QLabel *textLabel;
    QLineEdit *textLine;
    QHBoxLayout *horizontalLayout_5;
    QLabel *correctAnsweLabel;
    QLineEdit *correctAnswerLine;
    QPushButton *questionButton;

    void setupUi(QWidget *Presenter)
    {
        if (Presenter->objectName().isEmpty())
            Presenter->setObjectName(QString::fromUtf8("Presenter"));
        Presenter->resize(544, 411);
        verticalLayout_2 = new QVBoxLayout(Presenter);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        listWidget = new QListWidget(Presenter);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        horizontalLayout->addWidget(listWidget);

        q_label = new QLabel(Presenter);
        q_label->setObjectName(QString::fromUtf8("q_label"));

        horizontalLayout->addWidget(q_label);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        answerlabel = new QLabel(Presenter);
        answerlabel->setObjectName(QString::fromUtf8("answerlabel"));

        horizontalLayout_6->addWidget(answerlabel);

        answerLine = new QLineEdit(Presenter);
        answerLine->setObjectName(QString::fromUtf8("answerLine"));

        horizontalLayout_6->addWidget(answerLine);


        horizontalLayout_8->addLayout(horizontalLayout_6);

        answerButton = new QPushButton(Presenter);
        answerButton->setObjectName(QString::fromUtf8("answerButton"));

        horizontalLayout_8->addWidget(answerButton);


        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        idLabel = new QLabel(Presenter);
        idLabel->setObjectName(QString::fromUtf8("idLabel"));

        horizontalLayout_2->addWidget(idLabel);

        idLine = new QLineEdit(Presenter);
        idLine->setObjectName(QString::fromUtf8("idLine"));

        horizontalLayout_2->addWidget(idLine);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        scoreLabel = new QLabel(Presenter);
        scoreLabel->setObjectName(QString::fromUtf8("scoreLabel"));

        horizontalLayout_3->addWidget(scoreLabel);

        scoreLine = new QLineEdit(Presenter);
        scoreLine->setObjectName(QString::fromUtf8("scoreLine"));

        horizontalLayout_3->addWidget(scoreLine);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        textLabel = new QLabel(Presenter);
        textLabel->setObjectName(QString::fromUtf8("textLabel"));

        horizontalLayout_4->addWidget(textLabel);

        textLine = new QLineEdit(Presenter);
        textLine->setObjectName(QString::fromUtf8("textLine"));

        horizontalLayout_4->addWidget(textLine);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        correctAnsweLabel = new QLabel(Presenter);
        correctAnsweLabel->setObjectName(QString::fromUtf8("correctAnsweLabel"));

        horizontalLayout_5->addWidget(correctAnsweLabel);

        correctAnswerLine = new QLineEdit(Presenter);
        correctAnswerLine->setObjectName(QString::fromUtf8("correctAnswerLine"));

        horizontalLayout_5->addWidget(correctAnswerLine);


        verticalLayout->addLayout(horizontalLayout_5);


        horizontalLayout_7->addLayout(verticalLayout);

        questionButton = new QPushButton(Presenter);
        questionButton->setObjectName(QString::fromUtf8("questionButton"));

        horizontalLayout_7->addWidget(questionButton);


        verticalLayout_2->addLayout(horizontalLayout_7);


        retranslateUi(Presenter);

        QMetaObject::connectSlotsByName(Presenter);
    } // setupUi

    void retranslateUi(QWidget *Presenter)
    {
        Presenter->setWindowTitle(QCoreApplication::translate("Presenter", "Presenter", nullptr));
        q_label->setText(QCoreApplication::translate("Presenter", "Questions", nullptr));
        answerlabel->setText(QCoreApplication::translate("Presenter", "Answer", nullptr));
        answerButton->setText(QCoreApplication::translate("Presenter", "Answer", nullptr));
        idLabel->setText(QCoreApplication::translate("Presenter", "Id", nullptr));
        scoreLabel->setText(QCoreApplication::translate("Presenter", "Score", nullptr));
        textLabel->setText(QCoreApplication::translate("Presenter", "Text", nullptr));
        correctAnsweLabel->setText(QCoreApplication::translate("Presenter", "Correct Answer", nullptr));
        questionButton->setText(QCoreApplication::translate("Presenter", "Add Question", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Presenter: public Ui_Presenter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRESENTER_H
