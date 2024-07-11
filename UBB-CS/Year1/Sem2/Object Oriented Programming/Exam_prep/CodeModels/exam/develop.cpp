//
// Created by Dragos on 6/11/2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_develop.h" resolved
#include <QFileDialog>
#include "develop.h"
#include "ui_develop.h"
#include <fstream>

develop::develop(Idea& idea, QWidget *parent) :
        QWidget(parent), ui(new Ui::develop), idea{idea} {
    ui->setupUi(this);
    connectSignalsAndSlots();
    this->ui->textEdit->setText(QString::fromStdString(idea.getDescription()));
}

develop::~develop() {
    delete ui;
}

void develop::connectSignalsAndSlots() {
    QObject::connect(this->ui->pushButton, &QPushButton::clicked, this, &develop::save);

}

void develop::save() {
    std::string path = QFileDialog::getSaveFileName().toStdString();
    std::ofstream f(path);
    f<<this->ui->textEdit->toPlainText().toStdString();
}

