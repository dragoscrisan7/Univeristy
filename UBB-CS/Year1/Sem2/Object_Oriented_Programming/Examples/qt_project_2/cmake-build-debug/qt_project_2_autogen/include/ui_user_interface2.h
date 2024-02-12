/********************************************************************************
** Form generated from reading UI file 'user_interface2.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USER_INTERFACE2_H
#define UI_USER_INTERFACE2_H

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

class Ui_user_interface2
{
public:
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_3;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *input_name;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *input_categry2;
    QPushButton *Button2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *input_cateory;
    QPushButton *Button1;
    QListWidget *list2;

    void setupUi(QWidget *user_interface2)
    {
        if (user_interface2->objectName().isEmpty())
            user_interface2->setObjectName(QString::fromUtf8("user_interface2"));
        user_interface2->resize(651, 386);
        horizontalLayout_5 = new QHBoxLayout(user_interface2);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        listWidget = new QListWidget(user_interface2);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        verticalLayout_3->addWidget(listWidget);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(user_interface2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        input_name = new QLineEdit(user_interface2);
        input_name->setObjectName(QString::fromUtf8("input_name"));

        horizontalLayout_3->addWidget(input_name);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(user_interface2);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        input_categry2 = new QLineEdit(user_interface2);
        input_categry2->setObjectName(QString::fromUtf8("input_categry2"));

        horizontalLayout_2->addWidget(input_categry2);


        verticalLayout_2->addLayout(horizontalLayout_2);


        horizontalLayout_4->addLayout(verticalLayout_2);

        Button2 = new QPushButton(user_interface2);
        Button2->setObjectName(QString::fromUtf8("Button2"));

        horizontalLayout_4->addWidget(Button2);


        verticalLayout_3->addLayout(horizontalLayout_4);


        horizontalLayout_5->addLayout(verticalLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        input_cateory = new QLineEdit(user_interface2);
        input_cateory->setObjectName(QString::fromUtf8("input_cateory"));

        horizontalLayout->addWidget(input_cateory);

        Button1 = new QPushButton(user_interface2);
        Button1->setObjectName(QString::fromUtf8("Button1"));

        horizontalLayout->addWidget(Button1);


        verticalLayout->addLayout(horizontalLayout);

        list2 = new QListWidget(user_interface2);
        list2->setObjectName(QString::fromUtf8("list2"));

        verticalLayout->addWidget(list2);


        horizontalLayout_5->addLayout(verticalLayout);


        retranslateUi(user_interface2);

        QMetaObject::connectSlotsByName(user_interface2);
    } // setupUi

    void retranslateUi(QWidget *user_interface2)
    {
        user_interface2->setWindowTitle(QCoreApplication::translate("user_interface2", "user_interface2", nullptr));
        label_2->setText(QCoreApplication::translate("user_interface2", "Name", nullptr));
        label->setText(QCoreApplication::translate("user_interface2", "Category", nullptr));
        Button2->setText(QCoreApplication::translate("user_interface2", "Search", nullptr));
        Button1->setText(QCoreApplication::translate("user_interface2", "Category", nullptr));
    } // retranslateUi

};

namespace Ui {
    class user_interface2: public Ui_user_interface2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USER_INTERFACE2_H
