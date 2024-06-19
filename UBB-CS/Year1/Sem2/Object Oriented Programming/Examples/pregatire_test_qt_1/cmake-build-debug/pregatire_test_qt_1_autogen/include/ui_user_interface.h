/********************************************************************************
** Form generated from reading UI file 'user_interface.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USER_INTERFACE_H
#define UI_USER_INTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_user_interface
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget;
    QGridLayout *gridLayout;
    QLineEdit *priorityLineEdit;
    QPushButton *durationButton;
    QLabel *durationLabel;

    void setupUi(QWidget *user_interface)
    {
        if (user_interface->objectName().isEmpty())
            user_interface->setObjectName(QString::fromUtf8("user_interface"));
        user_interface->resize(510, 367);
        horizontalLayout = new QHBoxLayout(user_interface);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        listWidget = new QListWidget(user_interface);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        verticalLayout->addWidget(listWidget);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        priorityLineEdit = new QLineEdit(user_interface);
        priorityLineEdit->setObjectName(QString::fromUtf8("priorityLineEdit"));

        gridLayout->addWidget(priorityLineEdit, 0, 0, 1, 1);

        durationButton = new QPushButton(user_interface);
        durationButton->setObjectName(QString::fromUtf8("durationButton"));

        gridLayout->addWidget(durationButton, 0, 1, 1, 1);

        durationLabel = new QLabel(user_interface);
        durationLabel->setObjectName(QString::fromUtf8("durationLabel"));

        gridLayout->addWidget(durationLabel, 1, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(user_interface);

        QMetaObject::connectSlotsByName(user_interface);
    } // setupUi

    void retranslateUi(QWidget *user_interface)
    {
        user_interface->setWindowTitle(QCoreApplication::translate("user_interface", "user_interface", nullptr));
        durationButton->setText(QCoreApplication::translate("user_interface", "Show Duration", nullptr));
        durationLabel->setText(QCoreApplication::translate("user_interface", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class user_interface: public Ui_user_interface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USER_INTERFACE_H
