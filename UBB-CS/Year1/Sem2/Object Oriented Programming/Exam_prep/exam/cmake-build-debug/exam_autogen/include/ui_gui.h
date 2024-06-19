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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gui
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTableView *tableView;
    QGridLayout *gridLayout;
    QLineEdit *actEdit;
    QLabel *label_3;
    QLineEdit *descriptionEdit;
    QLabel *label_2;
    QPushButton *developButton;
    QPushButton *savePlotButton;
    QPushButton *acceptIdeaButton;
    QPushButton *addIdeaButton;

    void setupUi(QWidget *gui)
    {
        if (gui->objectName().isEmpty())
            gui->setObjectName(QString::fromUtf8("gui"));
        gui->resize(476, 422);
        verticalLayout = new QVBoxLayout(gui);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(gui);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        tableView = new QTableView(gui);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        verticalLayout->addWidget(tableView);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        actEdit = new QLineEdit(gui);
        actEdit->setObjectName(QString::fromUtf8("actEdit"));

        gridLayout->addWidget(actEdit, 2, 1, 1, 1);

        label_3 = new QLabel(gui);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        descriptionEdit = new QLineEdit(gui);
        descriptionEdit->setObjectName(QString::fromUtf8("descriptionEdit"));

        gridLayout->addWidget(descriptionEdit, 1, 1, 1, 1);

        label_2 = new QLabel(gui);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        developButton = new QPushButton(gui);
        developButton->setObjectName(QString::fromUtf8("developButton"));

        verticalLayout->addWidget(developButton);

        savePlotButton = new QPushButton(gui);
        savePlotButton->setObjectName(QString::fromUtf8("savePlotButton"));

        verticalLayout->addWidget(savePlotButton);

        acceptIdeaButton = new QPushButton(gui);
        acceptIdeaButton->setObjectName(QString::fromUtf8("acceptIdeaButton"));

        verticalLayout->addWidget(acceptIdeaButton);

        addIdeaButton = new QPushButton(gui);
        addIdeaButton->setObjectName(QString::fromUtf8("addIdeaButton"));

        verticalLayout->addWidget(addIdeaButton);


        retranslateUi(gui);

        QMetaObject::connectSlotsByName(gui);
    } // setupUi

    void retranslateUi(QWidget *gui)
    {
        gui->setWindowTitle(QCoreApplication::translate("gui", "gui", nullptr));
        label->setText(QCoreApplication::translate("gui", "Ideas:", nullptr));
        label_3->setText(QCoreApplication::translate("gui", "Act", nullptr));
        label_2->setText(QCoreApplication::translate("gui", "Description", nullptr));
        developButton->setText(QCoreApplication::translate("gui", "Develop", nullptr));
        savePlotButton->setText(QCoreApplication::translate("gui", "Save Plot", nullptr));
        acceptIdeaButton->setText(QCoreApplication::translate("gui", "Accept idea", nullptr));
        addIdeaButton->setText(QCoreApplication::translate("gui", "Add idea", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gui: public Ui_gui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
