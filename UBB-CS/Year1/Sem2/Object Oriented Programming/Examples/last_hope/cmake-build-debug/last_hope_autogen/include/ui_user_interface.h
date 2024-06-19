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
    QHBoxLayout *horizontalLayout_5;
    QListWidget *listWidget;
    QPushButton *reviseButton;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *mustReviseLabel;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLabel *revisedLabel;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *lineAddFile;
    QPushButton *addButton;

    void setupUi(QWidget *user_interface)
    {
        if (user_interface->objectName().isEmpty())
            user_interface->setObjectName(QString::fromUtf8("user_interface"));
        user_interface->resize(400, 344);
        verticalLayout = new QVBoxLayout(user_interface);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        listWidget = new QListWidget(user_interface);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        horizontalLayout_5->addWidget(listWidget);

        reviseButton = new QPushButton(user_interface);
        reviseButton->setObjectName(QString::fromUtf8("reviseButton"));

        horizontalLayout_5->addWidget(reviseButton);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(user_interface);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        mustReviseLabel = new QLabel(user_interface);
        mustReviseLabel->setObjectName(QString::fromUtf8("mustReviseLabel"));

        horizontalLayout->addWidget(mustReviseLabel);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(user_interface);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        revisedLabel = new QLabel(user_interface);
        revisedLabel->setObjectName(QString::fromUtf8("revisedLabel"));

        horizontalLayout_2->addWidget(revisedLabel);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(user_interface);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        lineAddFile = new QLineEdit(user_interface);
        lineAddFile->setObjectName(QString::fromUtf8("lineAddFile"));

        horizontalLayout_3->addWidget(lineAddFile);


        horizontalLayout_4->addLayout(horizontalLayout_3);

        addButton = new QPushButton(user_interface);
        addButton->setObjectName(QString::fromUtf8("addButton"));

        horizontalLayout_4->addWidget(addButton);


        verticalLayout->addLayout(horizontalLayout_4);


        retranslateUi(user_interface);

        QMetaObject::connectSlotsByName(user_interface);
    } // setupUi

    void retranslateUi(QWidget *user_interface)
    {
        user_interface->setWindowTitle(QCoreApplication::translate("user_interface", "user_interface", nullptr));
        reviseButton->setText(QCoreApplication::translate("user_interface", "Revise", nullptr));
        label->setText(QCoreApplication::translate("user_interface", "Must Revise:", nullptr));
        mustReviseLabel->setText(QCoreApplication::translate("user_interface", "Must_Revise", nullptr));
        label_2->setText(QCoreApplication::translate("user_interface", "Revised:", nullptr));
        revisedLabel->setText(QCoreApplication::translate("user_interface", "Revised", nullptr));
        label_3->setText(QCoreApplication::translate("user_interface", "Add File", nullptr));
        addButton->setText(QCoreApplication::translate("user_interface", "Add", nullptr));
    } // retranslateUi

};

namespace Ui {
    class user_interface: public Ui_user_interface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USER_INTERFACE_H
