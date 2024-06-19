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
    QHBoxLayout *horizontalLayout_4;
    QListWidget *listWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *Revised;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLabel *MustRevise;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QLineEdit *lineName;
    QPushButton *buttonAddSourceFile;
    QPushButton *buttonRevise;

    void setupUi(QWidget *gui)
    {
        if (gui->objectName().isEmpty())
            gui->setObjectName(QString::fromUtf8("gui"));
        gui->resize(400, 300);
        verticalLayout_2 = new QVBoxLayout(gui);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        listWidget = new QListWidget(gui);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        horizontalLayout_4->addWidget(listWidget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(gui);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        Revised = new QLabel(gui);
        Revised->setObjectName(QString::fromUtf8("Revised"));

        horizontalLayout_2->addWidget(Revised);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(gui);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        MustRevise = new QLabel(gui);
        MustRevise->setObjectName(QString::fromUtf8("MustRevise"));

        horizontalLayout_3->addWidget(MustRevise);


        verticalLayout->addLayout(horizontalLayout_3);


        horizontalLayout_4->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_3 = new QLabel(gui);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        lineName = new QLineEdit(gui);
        lineName->setObjectName(QString::fromUtf8("lineName"));

        horizontalLayout->addWidget(lineName);

        buttonAddSourceFile = new QPushButton(gui);
        buttonAddSourceFile->setObjectName(QString::fromUtf8("buttonAddSourceFile"));

        horizontalLayout->addWidget(buttonAddSourceFile);


        verticalLayout_2->addLayout(horizontalLayout);

        buttonRevise = new QPushButton(gui);
        buttonRevise->setObjectName(QString::fromUtf8("buttonRevise"));

        verticalLayout_2->addWidget(buttonRevise);


        retranslateUi(gui);

        QMetaObject::connectSlotsByName(gui);
    } // setupUi

    void retranslateUi(QWidget *gui)
    {
        gui->setWindowTitle(QCoreApplication::translate("gui", "gui", nullptr));
        label->setText(QCoreApplication::translate("gui", "Revised:", nullptr));
        Revised->setText(QCoreApplication::translate("gui", "TextLabel", nullptr));
        label_2->setText(QCoreApplication::translate("gui", "To revise:", nullptr));
        MustRevise->setText(QCoreApplication::translate("gui", "TextLabel", nullptr));
        label_3->setText(QCoreApplication::translate("gui", "Name:", nullptr));
        buttonAddSourceFile->setText(QCoreApplication::translate("gui", "Add Source File", nullptr));
        buttonRevise->setText(QCoreApplication::translate("gui", "Revise", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gui: public Ui_gui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
