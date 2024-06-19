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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gui
{
public:
    QVBoxLayout *verticalLayout_2;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineId;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineText;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *lineCA;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLineEdit *lineScore;
    QPushButton *buttonAddQ;
    QHBoxLayout *horizontalLayout_7;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    QLineEdit *lineAnswer;
    QPushButton *buttonAnswer;

    void setupUi(QWidget *gui)
    {
        if (gui->objectName().isEmpty())
            gui->setObjectName(QString::fromUtf8("gui"));
        gui->resize(576, 424);
        verticalLayout_2 = new QVBoxLayout(gui);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        listWidget = new QListWidget(gui);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        verticalLayout_2->addWidget(listWidget);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(gui);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineId = new QLineEdit(gui);
        lineId->setObjectName(QString::fromUtf8("lineId"));

        horizontalLayout->addWidget(lineId);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(gui);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        lineText = new QLineEdit(gui);
        lineText->setObjectName(QString::fromUtf8("lineText"));

        horizontalLayout_2->addWidget(lineText);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(gui);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        lineCA = new QLineEdit(gui);
        lineCA->setObjectName(QString::fromUtf8("lineCA"));

        horizontalLayout_3->addWidget(lineCA);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(gui);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        lineScore = new QLineEdit(gui);
        lineScore->setObjectName(QString::fromUtf8("lineScore"));

        horizontalLayout_4->addWidget(lineScore);


        verticalLayout->addLayout(horizontalLayout_4);


        horizontalLayout_5->addLayout(verticalLayout);

        buttonAddQ = new QPushButton(gui);
        buttonAddQ->setObjectName(QString::fromUtf8("buttonAddQ"));

        horizontalLayout_5->addWidget(buttonAddQ);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_5 = new QLabel(gui);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_6->addWidget(label_5);

        lineAnswer = new QLineEdit(gui);
        lineAnswer->setObjectName(QString::fromUtf8("lineAnswer"));

        horizontalLayout_6->addWidget(lineAnswer);


        horizontalLayout_7->addLayout(horizontalLayout_6);

        buttonAnswer = new QPushButton(gui);
        buttonAnswer->setObjectName(QString::fromUtf8("buttonAnswer"));

        horizontalLayout_7->addWidget(buttonAnswer);


        verticalLayout_2->addLayout(horizontalLayout_7);


        retranslateUi(gui);

        QMetaObject::connectSlotsByName(gui);
    } // setupUi

    void retranslateUi(QWidget *gui)
    {
        gui->setWindowTitle(QCoreApplication::translate("gui", "gui", nullptr));
        label->setText(QCoreApplication::translate("gui", "Id", nullptr));
        label_2->setText(QCoreApplication::translate("gui", "Text", nullptr));
        label_3->setText(QCoreApplication::translate("gui", "Correct Answer", nullptr));
        label_4->setText(QCoreApplication::translate("gui", "Score", nullptr));
        buttonAddQ->setText(QCoreApplication::translate("gui", "Add Question", nullptr));
        label_5->setText(QCoreApplication::translate("gui", "Answer", nullptr));
        buttonAnswer->setText(QCoreApplication::translate("gui", "Answer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gui: public Ui_gui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
