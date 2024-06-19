/********************************************************************************
** Form generated from reading UI file 'develop.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEVELOP_H
#define UI_DEVELOP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_develop
{
public:
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit;
    QPushButton *pushButton;

    void setupUi(QWidget *develop)
    {
        if (develop->objectName().isEmpty())
            develop->setObjectName(QString::fromUtf8("develop"));
        develop->resize(400, 300);
        verticalLayout = new QVBoxLayout(develop);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        textEdit = new QTextEdit(develop);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        verticalLayout->addWidget(textEdit);

        pushButton = new QPushButton(develop);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);


        retranslateUi(develop);

        QMetaObject::connectSlotsByName(develop);
    } // setupUi

    void retranslateUi(QWidget *develop)
    {
        develop->setWindowTitle(QCoreApplication::translate("develop", "develop", nullptr));
        pushButton->setText(QCoreApplication::translate("develop", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class develop: public Ui_develop {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVELOP_H
