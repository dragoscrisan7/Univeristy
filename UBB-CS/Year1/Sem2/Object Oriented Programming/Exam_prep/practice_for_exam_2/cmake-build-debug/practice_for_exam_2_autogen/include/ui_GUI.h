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

class Ui_GUI
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTableView *tableView;
    QPushButton *developButton;
    QPushButton *savePlotButton;
    QPushButton *acceptIdeaButton;
    QPushButton *addIdeaButton;
    QGridLayout *gridLayout;
    QLineEdit *actEdit;
    QLabel *label_3;
    QLineEdit *descriptionEdit;
    QLabel *label_2;

    void setupUi(QWidget *GUI)
    {
        if (GUI->objectName().isEmpty())
            GUI->setObjectName(QString::fromUtf8("GUI"));
        GUI->resize(670, 552);
        verticalLayout = new QVBoxLayout(GUI);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(GUI);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        tableView = new QTableView(GUI);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        verticalLayout->addWidget(tableView);

        developButton = new QPushButton(GUI);
        developButton->setObjectName(QString::fromUtf8("developButton"));

        verticalLayout->addWidget(developButton);

        savePlotButton = new QPushButton(GUI);
        savePlotButton->setObjectName(QString::fromUtf8("savePlotButton"));

        verticalLayout->addWidget(savePlotButton);

        acceptIdeaButton = new QPushButton(GUI);
        acceptIdeaButton->setObjectName(QString::fromUtf8("acceptIdeaButton"));

        verticalLayout->addWidget(acceptIdeaButton);

        addIdeaButton = new QPushButton(GUI);
        addIdeaButton->setObjectName(QString::fromUtf8("addIdeaButton"));

        verticalLayout->addWidget(addIdeaButton);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        actEdit = new QLineEdit(GUI);
        actEdit->setObjectName(QString::fromUtf8("actEdit"));

        gridLayout->addWidget(actEdit, 2, 1, 1, 1);

        label_3 = new QLabel(GUI);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        descriptionEdit = new QLineEdit(GUI);
        descriptionEdit->setObjectName(QString::fromUtf8("descriptionEdit"));

        gridLayout->addWidget(descriptionEdit, 1, 1, 1, 1);

        label_2 = new QLabel(GUI);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(GUI);

        QMetaObject::connectSlotsByName(GUI);
    } // setupUi

    void retranslateUi(QWidget *GUI)
    {
        GUI->setWindowTitle(QCoreApplication::translate("GUI", "GUI", nullptr));
        label->setText(QCoreApplication::translate("GUI", "Ideas:", nullptr));
        developButton->setText(QCoreApplication::translate("GUI", "Develop", nullptr));
        savePlotButton->setText(QCoreApplication::translate("GUI", "Save Plot", nullptr));
        acceptIdeaButton->setText(QCoreApplication::translate("GUI", "Accept idea", nullptr));
        addIdeaButton->setText(QCoreApplication::translate("GUI", "Add idea", nullptr));
        label_3->setText(QCoreApplication::translate("GUI", "Act", nullptr));
        label_2->setText(QCoreApplication::translate("GUI", "Description", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GUI: public Ui_GUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
