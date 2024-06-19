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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gui
{
public:
    QVBoxLayout *verticalLayout_2;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineName;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineRA;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QLineEdit *lineDec;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLineEdit *lineDiam;
    QPushButton *buttonAdd;
    QCheckBox *checkBox;

    void setupUi(QWidget *gui)
    {
        if (gui->objectName().isEmpty())
            gui->setObjectName(QString::fromUtf8("gui"));
        gui->resize(642, 450);
        verticalLayout_2 = new QVBoxLayout(gui);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tableView = new QTableView(gui);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

        verticalLayout_2->addWidget(tableView);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(gui);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineName = new QLineEdit(gui);
        lineName->setObjectName(QString::fromUtf8("lineName"));

        horizontalLayout->addWidget(lineName);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(gui);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        lineRA = new QLineEdit(gui);
        lineRA->setObjectName(QString::fromUtf8("lineRA"));

        horizontalLayout_2->addWidget(lineRA);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_4 = new QLabel(gui);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_3->addWidget(label_4);

        lineDec = new QLineEdit(gui);
        lineDec->setObjectName(QString::fromUtf8("lineDec"));

        horizontalLayout_3->addWidget(lineDec);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_3 = new QLabel(gui);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_4->addWidget(label_3);

        lineDiam = new QLineEdit(gui);
        lineDiam->setObjectName(QString::fromUtf8("lineDiam"));

        horizontalLayout_4->addWidget(lineDiam);


        verticalLayout->addLayout(horizontalLayout_4);


        horizontalLayout_5->addLayout(verticalLayout);

        buttonAdd = new QPushButton(gui);
        buttonAdd->setObjectName(QString::fromUtf8("buttonAdd"));

        horizontalLayout_5->addWidget(buttonAdd);


        horizontalLayout_6->addLayout(horizontalLayout_5);

        checkBox = new QCheckBox(gui);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        horizontalLayout_6->addWidget(checkBox);


        verticalLayout_2->addLayout(horizontalLayout_6);


        retranslateUi(gui);

        QMetaObject::connectSlotsByName(gui);
    } // setupUi

    void retranslateUi(QWidget *gui)
    {
        gui->setWindowTitle(QCoreApplication::translate("gui", "gui", nullptr));
        label->setText(QCoreApplication::translate("gui", "Name", nullptr));
        label_2->setText(QCoreApplication::translate("gui", "RA", nullptr));
        label_4->setText(QCoreApplication::translate("gui", "Dec", nullptr));
        label_3->setText(QCoreApplication::translate("gui", "Diameter", nullptr));
        buttonAdd->setText(QCoreApplication::translate("gui", "Add", nullptr));
        checkBox->setText(QCoreApplication::translate("gui", "CheckBox", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gui: public Ui_gui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
