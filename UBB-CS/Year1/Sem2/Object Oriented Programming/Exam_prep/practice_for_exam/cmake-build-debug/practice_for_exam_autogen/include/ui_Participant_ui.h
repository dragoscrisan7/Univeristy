/********************************************************************************
** Form generated from reading UI file 'participant_ui.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARTICIPANT_UI_H
#define UI_PARTICIPANT_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Participant_ui
{
public:

    void setupUi(QWidget *Participant_ui)
    {
        if (Participant_ui->objectName().isEmpty())
            Participant_ui->setObjectName(QString::fromUtf8("Participant_ui"));
        Participant_ui->resize(400, 300);

        retranslateUi(Participant_ui);

        QMetaObject::connectSlotsByName(Participant_ui);
    } // setupUi

    void retranslateUi(QWidget *Participant_ui)
    {
        Participant_ui->setWindowTitle(QCoreApplication::translate("Participant_ui", "Participant_ui", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Participant_ui: public Ui_Participant_ui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARTICIPANT_UI_H
