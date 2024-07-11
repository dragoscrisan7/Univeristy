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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gui
{
public:
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QListWidget *listFeed;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QListWidget *listPosts;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QListWidget *listSubscriptions;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QLineEdit *lineSearc;
    QListWidget *listSearch;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QLineEdit *lineAddPost;
    QPushButton *buttonAddPost;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_6;
    QLineEdit *lineUpdatepost;
    QPushButton *buttonUpdatePost;

    void setupUi(QWidget *gui)
    {
        if (gui->objectName().isEmpty())
            gui->setObjectName(QString::fromUtf8("gui"));
        gui->resize(816, 525);
        verticalLayout_4 = new QVBoxLayout(gui);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(gui);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        listFeed = new QListWidget(gui);
        listFeed->setObjectName(QString::fromUtf8("listFeed"));

        verticalLayout->addWidget(listFeed);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_2 = new QLabel(gui);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        listPosts = new QListWidget(gui);
        listPosts->setObjectName(QString::fromUtf8("listPosts"));

        verticalLayout_2->addWidget(listPosts);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_3 = new QLabel(gui);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_3->addWidget(label_3);

        listSubscriptions = new QListWidget(gui);
        listSubscriptions->setObjectName(QString::fromUtf8("listSubscriptions"));

        verticalLayout_3->addWidget(listSubscriptions);


        horizontalLayout->addLayout(verticalLayout_3);


        verticalLayout_4->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_4 = new QLabel(gui);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        lineSearc = new QLineEdit(gui);
        lineSearc->setObjectName(QString::fromUtf8("lineSearc"));

        horizontalLayout_2->addWidget(lineSearc);

        listSearch = new QListWidget(gui);
        listSearch->setObjectName(QString::fromUtf8("listSearch"));

        horizontalLayout_2->addWidget(listSearch);


        verticalLayout_4->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_5 = new QLabel(gui);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_3->addWidget(label_5);

        lineAddPost = new QLineEdit(gui);
        lineAddPost->setObjectName(QString::fromUtf8("lineAddPost"));

        horizontalLayout_3->addWidget(lineAddPost);

        buttonAddPost = new QPushButton(gui);
        buttonAddPost->setObjectName(QString::fromUtf8("buttonAddPost"));

        horizontalLayout_3->addWidget(buttonAddPost);


        verticalLayout_4->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_6 = new QLabel(gui);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_4->addWidget(label_6);

        lineUpdatepost = new QLineEdit(gui);
        lineUpdatepost->setObjectName(QString::fromUtf8("lineUpdatepost"));

        horizontalLayout_4->addWidget(lineUpdatepost);

        buttonUpdatePost = new QPushButton(gui);
        buttonUpdatePost->setObjectName(QString::fromUtf8("buttonUpdatePost"));

        horizontalLayout_4->addWidget(buttonUpdatePost);


        verticalLayout_4->addLayout(horizontalLayout_4);


        retranslateUi(gui);

        QMetaObject::connectSlotsByName(gui);
    } // setupUi

    void retranslateUi(QWidget *gui)
    {
        gui->setWindowTitle(QCoreApplication::translate("gui", "gui", nullptr));
        label->setText(QCoreApplication::translate("gui", "Feed", nullptr));
        label_2->setText(QCoreApplication::translate("gui", "Posts", nullptr));
        label_3->setText(QCoreApplication::translate("gui", "Subscriptions", nullptr));
        label_4->setText(QCoreApplication::translate("gui", "Search:", nullptr));
        label_5->setText(QCoreApplication::translate("gui", "Add Post", nullptr));
        buttonAddPost->setText(QCoreApplication::translate("gui", "Add", nullptr));
        label_6->setText(QCoreApplication::translate("gui", "Update Post", nullptr));
        buttonUpdatePost->setText(QCoreApplication::translate("gui", "Update", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gui: public Ui_gui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
