//
// Created by Dragos on 7/5/2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_gui.h" resolved

#include "gui.h"
#include "ui_gui.h"

gui::gui(Service& srv, Programmer pr, QWidget *parent) :
        QWidget(parent), ui(new Ui::gui), srv(srv), pr(pr) {
    ui->setupUi(this);
    srv.addObserver(this);
    connect();
    update();
    this->setWindowTitle(QString::fromStdString(pr.getName()));
    ui->buttonStart->setDisabled(true);
    ui->buttonDone->setDisabled(true);
}

gui::~gui() {
    delete ui;
}

void gui::connect() {
    QObject::connect(ui->buttonAdd, &QPushButton::clicked, this, &gui::add);
    QObject::connect(ui->buttonRemove, &QPushButton::clicked, this, &gui::remove);
    QObject::connect(ui->listWidget, &QListWidget::itemClicked, this, &gui::check_clicked);
}

void gui::update() {
    ui->listWidget->clear();
    for(auto task:srv.sorted_by_status()){
        string text = task.getDescription() + "," + task.getStatus() + "," + to_string(task.getId());
        ui->listWidget->addItem(QString::fromStdString(text));
    }
}

void gui::add() {
    string description = ui->lineDescription->text().toStdString();
    string status = "open";
    srv.add(description, status, pr.getId());
}

void gui::remove() {
    string description = ui->lineDescriptionRemove->text().toStdString();
    srv.remove(description);
}

void gui::start() {

}

void gui::done() {

}

void gui::check_clicked() {
    auto item = ui->listWidget->selectedItems()[0];
    auto line = item->text().toStdString();


    vector<string> separated_words;
    stringstream l(line);
    string token;
    while (getline(l, token, ','))
        separated_words.push_back(token);
    if(separated_words[1] == "in progress" || pr.getId() == stoi(separated_words[2])){
        ui->buttonDone->setDisabled(false);
        ui->buttonStart->setDisabled(true);
    }
    if(separated_words[1] == "open"){
        ui->buttonDone->setDisabled(true);
        ui->buttonStart->setDisabled(false);
    }
    if(separated_words[1] == "closed"){
        ui->buttonDone->setDisabled(true);
        ui->buttonStart->setDisabled(true);
    }
}

