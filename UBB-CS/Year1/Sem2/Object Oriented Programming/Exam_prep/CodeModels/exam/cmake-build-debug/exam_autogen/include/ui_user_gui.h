/********************************************************************************
** Form generated from reading UI file 'user_gui.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USER_GUI_H
#define UI_USER_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_user_gui
{
public:

    void setupUi(QWidget *user_gui)
    {
        if (user_gui->objectName().isEmpty())
            user_gui->setObjectName(QString::fromUtf8("user_gui"));
        user_gui->resize(400, 300);

        retranslateUi(user_gui);

        QMetaObject::connectSlotsByName(user_gui);
    } // setupUi

    void retranslateUi(QWidget *user_gui)
    {
        user_gui->setWindowTitle(QCoreApplication::translate("user_gui", "user_gui", nullptr));
    } // retranslateUi

};

namespace Ui {
    class user_gui: public Ui_user_gui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USER_GUI_H
