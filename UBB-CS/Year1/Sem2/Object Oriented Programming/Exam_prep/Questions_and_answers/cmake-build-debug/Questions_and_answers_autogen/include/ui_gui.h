/********************************************************************************
** Form generated from reading UI file 'gui.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_H
#define UI_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gui
{
public:
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineTextQuestion;
    QPushButton *buttonAddQuestion;
    QVBoxLayout *verticalLayout_2;
    QListWidget *listWidget_2;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QLineEdit *lineAnswer;
    QPushButton *buttonAddAnswer;
    QSpinBox *spinBox;

    void setupUi(QWidget *gui)
    {
        if (gui->objectName().isEmpty())
            gui->setObjectName(QString::fromUtf8("gui"));
        gui->resize(666, 334);
        horizontalLayout_6 = new QHBoxLayout(gui);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        listWidget = new QListWidget(gui);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        verticalLayout->addWidget(listWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(gui);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineTextQuestion = new QLineEdit(gui);
        lineTextQuestion->setObjectName(QString::fromUtf8("lineTextQuestion"));

        horizontalLayout->addWidget(lineTextQuestion);


        horizontalLayout_2->addLayout(horizontalLayout);

        buttonAddQuestion = new QPushButton(gui);
        buttonAddQuestion->setObjectName(QString::fromUtf8("buttonAddQuestion"));

        horizontalLayout_2->addWidget(buttonAddQuestion);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout_6->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        listWidget_2 = new QListWidget(gui);
        listWidget_2->setObjectName(QString::fromUtf8("listWidget_2"));

        verticalLayout_2->addWidget(listWidget_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_2 = new QLabel(gui);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_4->addWidget(label_2);

        lineAnswer = new QLineEdit(gui);
        lineAnswer->setObjectName(QString::fromUtf8("lineAnswer"));

        horizontalLayout_4->addWidget(lineAnswer);


        horizontalLayout_3->addLayout(horizontalLayout_4);

        buttonAddAnswer = new QPushButton(gui);
        buttonAddAnswer->setObjectName(QString::fromUtf8("buttonAddAnswer"));

        horizontalLayout_3->addWidget(buttonAddAnswer);


        horizontalLayout_5->addLayout(horizontalLayout_3);

        spinBox = new QSpinBox(gui);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));

        horizontalLayout_5->addWidget(spinBox);


        verticalLayout_2->addLayout(horizontalLayout_5);


        horizontalLayout_6->addLayout(verticalLayout_2);


        retranslateUi(gui);

        QMetaObject::connectSlotsByName(gui);
    } // setupUi

    void retranslateUi(QWidget *gui)
    {
        gui->setWindowTitle(QCoreApplication::translate("gui", "gui", nullptr));
        label->setText(QCoreApplication::translate("gui", "Question Text:", nullptr));
        buttonAddQuestion->setText(QCoreApplication::translate("gui", "Add question", nullptr));
        label_2->setText(QCoreApplication::translate("gui", "Answer Text:", nullptr));
        buttonAddAnswer->setText(QCoreApplication::translate("gui", "Add answer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gui: public Ui_gui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
