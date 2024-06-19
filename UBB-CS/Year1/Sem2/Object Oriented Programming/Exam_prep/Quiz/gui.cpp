//
// Created by Dragos on 6/27/2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_gui.h" resolved

#include "gui.h"
#include "ui_gui.h"


gui::gui(Participants& p, Service& srv, QWidget *parent) :
        QWidget(parent), ui(new Ui::gui), p(p), srv(srv){
    ui->setupUi(this);
    connect();
    this->srv.addObserver(this);
    this->update();
    this->setWindowTitle(QString::fromStdString(p.getName()));
    ui->buttonAnswer->setDisabled(p.getName() == "Presenter");
    ui->buttonAddQ->setDisabled(p.getName() != "Presenter");

}

gui::~gui() {
    delete ui;
}

void gui::add_question() {
    int id = ui->lineId->text().toInt();
    string text = ui->lineText->text().toStdString();
    string correct_answer = ui->lineCA->text().toStdString();
    int score = ui->lineScore->text().toInt();
    try{
        srv.add(id, text, correct_answer, score);
        ui->lineScore->clear();
        ui->lineCA->clear();
        ui->lineText->clear();
        ui->lineId->clear();
    }
    catch(string s){
        QMessageBox box;
        box.setText(QString::fromStdString(s));
        box.exec();
    }
}

void gui::update() {
    ui->listWidget->clear();
    if(p.getName() == "Presenter"){
        for(auto questions:srv.sorted_by_id()){
            string to_print = to_string(questions.getId()) + "," + questions.getText() + "," + questions.getCorrectAnswer() + "," + to_string(questions.getScore());
            ui->listWidget->addItem(QString::fromStdString(to_print));
        }
    }
    else{
        for(auto questions:srv.sorted_by_score()){
            string to_print = to_string(questions.getId()) + "," + questions.getText() + "," + to_string(questions.getScore());
            ui->listWidget->addItem(QString::fromStdString(to_print));
        }
    }
}

void gui::connect() {
    QObject::connect(this->ui->buttonAddQ,&QPushButton::clicked, this, &gui::add_question);
    QObject::connect(this->ui->buttonAnswer, &QPushButton::clicked, this, &gui::answer_question);
    QObject::connect(this->ui->listWidget, &QListWidget::itemClicked, this, &gui::to_answer);
}

void gui::answer_question() {
    string answer = ui->lineAnswer->text().toStdString();
    string line = ui->listWidget->selectedItems()[0]->text().toStdString();
    int id = stoi(line.substr(0,line.find(',')));
    int score = srv.answer(id, answer);
    if(score != 0){
        answ_id.push_back(id);
        p.raise_score(score);
        ui->listWidget->selectedItems()[0]->setBackground(Qt::green);
        this->ui->buttonAnswer->setDisabled(true);
    }
}

void gui::to_answer() {
    auto item = ui->listWidget->selectedItems()[0];
    string line = item->text().toStdString();
    int id = stoi(line.substr(0,line.find(',')));
    for(auto p:answ_id){
        if(p == id) {
            this->ui->buttonAnswer->setDisabled(true);
            return;
        }
    }
    this->ui->buttonAnswer->setDisabled(false);
}

