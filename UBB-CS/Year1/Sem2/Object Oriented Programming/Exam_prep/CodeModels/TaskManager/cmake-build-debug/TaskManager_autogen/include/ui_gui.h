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
    QHBoxLayout *horizontalLayout_3;
    QListWidget *listWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *buttonStart;
    QPushButton *buttonDone;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineDescription;
    QPushButton *buttonAdd;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineDescriptionRemove;
    QPushButton *buttonRemove;

    void setupUi(QWidget *gui)
    {
        if (gui->objectName().isEmpty())
            gui->setObjectName(QString::fromUtf8("gui"));
        gui->resize(605, 434);
        verticalLayout_2 = new QVBoxLayout(gui);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        listWidget = new QListWidget(gui);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        horizontalLayout_3->addWidget(listWidget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        buttonStart = new QPushButton(gui);
        buttonStart->setObjectName(QString::fromUtf8("buttonStart"));

        verticalLayout->addWidget(buttonStart);

        buttonDone = new QPushButton(gui);
        buttonDone->setObjectName(QString::fromUtf8("buttonDone"));

        verticalLayout->addWidget(buttonDone);


        horizontalLayout_3->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(gui);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineDescription = new QLineEdit(gui);
        lineDescription->setObjectName(QString::fromUtf8("lineDescription"));

        horizontalLayout->addWidget(lineDescription);

        buttonAdd = new QPushButton(gui);
        buttonAdd->setObjectName(QString::fromUtf8("buttonAdd"));

        horizontalLayout->addWidget(buttonAdd);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(gui);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        lineDescriptionRemove = new QLineEdit(gui);
        lineDescriptionRemove->setObjectName(QString::fromUtf8("lineDescriptionRemove"));

        horizontalLayout_2->addWidget(lineDescriptionRemove);

        buttonRemove = new QPushButton(gui);
        buttonRemove->setObjectName(QString::fromUtf8("buttonRemove"));

        horizontalLayout_2->addWidget(buttonRemove);


        verticalLayout_2->addLayout(horizontalLayout_2);


        retranslateUi(gui);

        QMetaObject::connectSlotsByName(gui);
    } // setupUi

    void retranslateUi(QWidget *gui)
    {
        gui->setWindowTitle(QCoreApplication::translate("gui", "gui", nullptr));
        buttonStart->setText(QCoreApplication::translate("gui", "Start", nullptr));
        buttonDone->setText(QCoreApplication::translate("gui", "Done", nullptr));
        label->setText(QCoreApplication::translate("gui", "Description", nullptr));
        buttonAdd->setText(QCoreApplication::translate("gui", "Add", nullptr));
        label_2->setText(QCoreApplication::translate("gui", "Description", nullptr));
        buttonRemove->setText(QCoreApplication::translate("gui", "Remove", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gui: public Ui_gui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
