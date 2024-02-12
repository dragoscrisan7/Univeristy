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

class Ui_Develop
{
public:
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit;
    QPushButton *saveButton;

    void setupUi(QWidget *Develop)
    {
        if (Develop->objectName().isEmpty())
            Develop->setObjectName(QString::fromUtf8("Develop"));
        Develop->resize(400, 300);
        verticalLayout = new QVBoxLayout(Develop);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        textEdit = new QTextEdit(Develop);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        verticalLayout->addWidget(textEdit);

        saveButton = new QPushButton(Develop);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));

        verticalLayout->addWidget(saveButton);


        retranslateUi(Develop);

        QMetaObject::connectSlotsByName(Develop);
    } // setupUi

    void retranslateUi(QWidget *Develop)
    {
        Develop->setWindowTitle(QCoreApplication::translate("Develop", "Develop", nullptr));
        saveButton->setText(QCoreApplication::translate("Develop", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Develop: public Ui_Develop {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVELOP_H
