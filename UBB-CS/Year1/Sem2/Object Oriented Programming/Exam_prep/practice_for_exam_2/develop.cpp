//
// Created by Oana on 6/7/2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Develop.h" resolved

#include <QFileDialog>
#include "develop.h"
#include "ui_Develop.h"
#include <fstream>


Develop::Develop(Idea& idea, QWidget *parent) :
        QWidget(parent), ui(new Ui::Develop), idea{idea} {
    ui->setupUi(this);
    connectSignalsAndSlots();
    this->ui->textEdit->setText(QString::fromStdString(idea.getDescription()));
}

Develop::~Develop() {
    delete ui;
}

void Develop::connectSignalsAndSlots() {
    QObject::connect(this->ui->saveButton, &QPushButton::clicked, this, &Develop::save);

}

void Develop::save() {
    std::string path = QFileDialog::getSaveFileName().toStdString();
    std::ofstream f(path);
    f<<this->ui->textEdit->toPlainText().toStdString();
}
