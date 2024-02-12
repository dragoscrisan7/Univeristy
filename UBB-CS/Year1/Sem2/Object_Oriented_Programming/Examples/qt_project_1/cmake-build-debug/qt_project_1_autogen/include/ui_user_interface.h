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
    QVBoxLayout *verticalLayout;
    QListWidget *list_tasks;
    QLineEdit *msgBox;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *input;
    QPushButton *button;

    void setupUi(QWidget *user_interface)
    {
        if (user_interface->objectName().isEmpty())
            user_interface->setObjectName(QString::fromUtf8("user_interface"));
        user_interface->resize(352, 294);
        verticalLayout = new QVBoxLayout(user_interface);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        list_tasks = new QListWidget(user_interface);
        list_tasks->setObjectName(QString::fromUtf8("list_tasks"));

        verticalLayout->addWidget(list_tasks);

        msgBox = new QLineEdit(user_interface);
        msgBox->setObjectName(QString::fromUtf8("msgBox"));

        verticalLayout->addWidget(msgBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(user_interface);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        input = new QLineEdit(user_interface);
        input->setObjectName(QString::fromUtf8("input"));

        horizontalLayout->addWidget(input);

        button = new QPushButton(user_interface);
        button->setObjectName(QString::fromUtf8("button"));

        horizontalLayout->addWidget(button);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(user_interface);

        QMetaObject::connectSlotsByName(user_interface);
    } // setupUi

    void retranslateUi(QWidget *user_interface)
    {
        user_interface->setWindowTitle(QCoreApplication::translate("user_interface", "user_interface", nullptr));
        label->setText(QCoreApplication::translate("user_interface", "Input prioirty:", nullptr));
        button->setText(QCoreApplication::translate("user_interface", "Show tasks", nullptr));
    } // retranslateUi

};

namespace Ui {
    class user_interface: public Ui_user_interface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USER_INTERFACE_H
