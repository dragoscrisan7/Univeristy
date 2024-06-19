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

class Ui_presenter
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QListWidget *listWidget;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_7;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_5;
    QLineEdit *lineEdit;
    QPushButton *answerButton;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLineEdit *idLineEdit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QLineEdit *textLineEdit;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QLineEdit *correctAnswerLineEdit;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_4;
    QLineEdit *scoreLineEdit;
    QPushButton *addButton;

    void setupUi(QWidget *presenter)
    {
        if (presenter->objectName().isEmpty())
            presenter->setObjectName(QString::fromUtf8("presenter"));
        presenter->resize(490, 440);
        verticalLayout_2 = new QVBoxLayout(presenter);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        listWidget = new QListWidget(presenter);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        horizontalLayout->addWidget(listWidget);

        label_6 = new QLabel(presenter);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout->addWidget(label_6);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_5 = new QLabel(presenter);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_2->addWidget(label_5);

        lineEdit = new QLineEdit(presenter);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout_2->addWidget(lineEdit);


        horizontalLayout_7->addLayout(horizontalLayout_2);

        answerButton = new QPushButton(presenter);
        answerButton->setObjectName(QString::fromUtf8("answerButton"));

        horizontalLayout_7->addWidget(answerButton);


        verticalLayout_2->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(presenter);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_3->addWidget(label);

        idLineEdit = new QLineEdit(presenter);
        idLineEdit->setObjectName(QString::fromUtf8("idLineEdit"));

        horizontalLayout_3->addWidget(idLineEdit);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_2 = new QLabel(presenter);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_4->addWidget(label_2);

        textLineEdit = new QLineEdit(presenter);
        textLineEdit->setObjectName(QString::fromUtf8("textLineEdit"));

        horizontalLayout_4->addWidget(textLineEdit);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_3 = new QLabel(presenter);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_5->addWidget(label_3);

        correctAnswerLineEdit = new QLineEdit(presenter);
        correctAnswerLineEdit->setObjectName(QString::fromUtf8("correctAnswerLineEdit"));

        horizontalLayout_5->addWidget(correctAnswerLineEdit);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_4 = new QLabel(presenter);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_6->addWidget(label_4);

        scoreLineEdit = new QLineEdit(presenter);
        scoreLineEdit->setObjectName(QString::fromUtf8("scoreLineEdit"));

        horizontalLayout_6->addWidget(scoreLineEdit);


        verticalLayout->addLayout(horizontalLayout_6);


        horizontalLayout_8->addLayout(verticalLayout);

        addButton = new QPushButton(presenter);
        addButton->setObjectName(QString::fromUtf8("addButton"));

        horizontalLayout_8->addWidget(addButton);


        verticalLayout_2->addLayout(horizontalLayout_8);


        retranslateUi(presenter);

        QMetaObject::connectSlotsByName(presenter);
    } // setupUi

    void retranslateUi(QWidget *presenter)
    {
        presenter->setWindowTitle(QCoreApplication::translate("presenter", "presenter", nullptr));
        label_6->setText(QCoreApplication::translate("presenter", "Questions", nullptr));
        label_5->setText(QCoreApplication::translate("presenter", "Answer", nullptr));
        answerButton->setText(QCoreApplication::translate("presenter", "Answer question", nullptr));
        label->setText(QCoreApplication::translate("presenter", "Id", nullptr));
        label_2->setText(QCoreApplication::translate("presenter", "Text", nullptr));
        label_3->setText(QCoreApplication::translate("presenter", "Correct Answer", nullptr));
        label_4->setText(QCoreApplication::translate("presenter", "Score", nullptr));
        addButton->setText(QCoreApplication::translate("presenter", "Add question", nullptr));
    } // retranslateUi

};

namespace Ui {
    class presenter: public Ui_presenter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRESENTER_H
