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
    QWidget *widget;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QLineEdit *input_prec;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *input_desc;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *input_start;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *result_button;
    QListWidget *listWidget_2;

    void setupUi(QWidget *user_interface)
    {
        if (user_interface->objectName().isEmpty())
            user_interface->setObjectName(QString::fromUtf8("user_interface"));
        user_interface->resize(614, 429);
        widget = new QWidget(user_interface);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(9, 9, 591, 496));
        verticalLayout_4 = new QVBoxLayout(widget);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        listWidget = new QListWidget(widget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        verticalLayout_2->addWidget(listWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        input_prec = new QLineEdit(widget);
        input_prec->setObjectName(QString::fromUtf8("input_prec"));

        horizontalLayout->addWidget(input_prec);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout_4->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        input_desc = new QLineEdit(widget);
        input_desc->setObjectName(QString::fromUtf8("input_desc"));

        horizontalLayout_3->addWidget(input_desc);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        input_start = new QLineEdit(widget);
        input_start->setObjectName(QString::fromUtf8("input_start"));

        horizontalLayout_2->addWidget(input_start);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_3->addLayout(verticalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        result_button = new QPushButton(widget);
        result_button->setObjectName(QString::fromUtf8("result_button"));

        horizontalLayout_4->addWidget(result_button);

        listWidget_2 = new QListWidget(widget);
        listWidget_2->setObjectName(QString::fromUtf8("listWidget_2"));

        horizontalLayout_4->addWidget(listWidget_2);


        verticalLayout_3->addLayout(horizontalLayout_4);


        verticalLayout_4->addLayout(verticalLayout_3);


        retranslateUi(user_interface);

        QMetaObject::connectSlotsByName(user_interface);
    } // setupUi

    void retranslateUi(QWidget *user_interface)
    {
        user_interface->setWindowTitle(QCoreApplication::translate("user_interface", "user_interface", nullptr));
        pushButton->setText(QCoreApplication::translate("user_interface", "Filter for less than:", nullptr));
        label_2->setText(QCoreApplication::translate("user_interface", "Description", nullptr));
        label->setText(QCoreApplication::translate("user_interface", "Type start time:", nullptr));
        result_button->setText(QCoreApplication::translate("user_interface", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class user_interface: public Ui_user_interface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USER_INTERFACE_H
