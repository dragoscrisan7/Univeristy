//
// Created by Oana on 6/6/2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Presenter.h" resolved

#include <sstream>
#include <QMessageBox>
#include "presenter.h"
#include "ui_Presenter.h"


Presenter::Presenter(Service &service, Participant& p, QWidget *parent) :
        QWidget(parent), ui(new Ui::Presenter), service(service) , participant(p){
    ui->setupUi(this);
    connect_sluts_and_signals();
    this->service.addObserver(this);
    this->update();
    this->setWindowTitle("Presenter");
    if (this->participant.getName() != "presenter") {
        this->setWindowTitle(QString::fromStdString(this->participant.getName()));
        this->ui->label_correct_answer->hide();
        this->ui->label_id->hide();
        this->ui->label_score->hide();
        this->ui->label_text->hide();
        this->ui->addButton->hide();
        this->ui->scoreLineEdit->hide();
        this->ui->textLineEdit->hide();
        this->ui->idLineEdit->hide();
        this->ui->correctAnswerLineEdit->hide();
    }
    else{
        this->ui->label_answer->hide();
        this->ui->answerButton->hide();
        this->ui->answerLineEdit->hide();
    }
}

Presenter::~Presenter() {
    delete ui;
}

void Presenter::connect_sluts_and_signals() {
    QObject::connect(this->ui->addButton, &QPushButton::clicked, this, &Presenter::add_question);
    QObject::connect(this->ui->answerButton, &QPushButton::clicked, this, &Presenter::answer_question);
    QObject::connect(this->ui->listWidget, &QListWidget::itemClicked, this, &Presenter::check_question);
}

void Presenter::add_question() {
    int id = this->ui->idLineEdit->text().toInt();
    int score = this->ui->scoreLineEdit->text().toInt();
    std::string text = this->ui->textLineEdit->text().toStdString();
    std::string answer = this->ui->correctAnswerLineEdit->text().toStdString();
    try{
        this->service.add_question(id, text, answer, score);
        this->ui->idLineEdit->clear();
        this->ui->textLineEdit->clear();
        this->ui->correctAnswerLineEdit->clear();
        this->ui->scoreLineEdit->clear();

    }
    catch(std::string e){
        QMessageBox box;
        box.setText(QString::fromStdString(e));
        box.exec();
    }


}

void Presenter::check_question() {
    int id = -1;
    for( auto item: this->ui->listWidget->selectedItems()){
        std::string line = item->text().toStdString();
        std::stringstream ss{ line };
        std::string token;

        std::getline(ss, token, ':');
        std::getline(ss, token, ' ');

        std::stringstream ss2{ token };
        std::getline(ss, token, ',');

        id = std::stoi(token);
    }
    for( int i=0; i<this->answered.size();i++){
        if(answered[i] == id) {
            this->ui->answerButton->setDisabled(true);
            return;
        }
    }
    this->ui->answerButton->setDisabled(false);

}

void Presenter::update() {
    this->ui->listWidget->clear();
    if (participant.getName()=="presenter"){
        for(auto item : this->service.sorted_by_id()){
            std::string txt;
            txt = "id: "+std::to_string(item.getId()) + ", question: " + item.getText() + ", answer "+ item.getCorrectAnswer() + ", score: " + std::to_string(item.getScore());
            this->ui->listWidget->addItem(QString::fromStdString(txt));
        }
    }
    else{
        for(auto item : this->service.sorted_by_score()){
            std::string txt;
            txt = "id: "+std::to_string(item.getId()) + ", question: " + item.getText() + ", score: " + std::to_string(item.getScore());
            this->ui->listWidget->addItem(QString::fromStdString(txt));
        }
    }

}

void Presenter::answer_question() {
    std::string answer = this->ui->answerLineEdit->text().toStdString();
    for (auto item : this->ui->listWidget->selectedItems()){
        std::string line = item->text().toStdString();
        std::stringstream ss{ line };
        std::string token;

        std::getline(ss, token, ':');
        std::getline(ss, token, ' ');

        std::stringstream ss2{ token };
        std::getline(ss, token, ',');

        int id = std::stoi(token);
        try {
            if (this->service.is_answer(id, answer)) {
                this->answered.push_back(id);
                this->participant.upScore(this->service.get_question_score(id));
                this->ui->scoreLineEdit->setText(QString::fromStdString(std::to_string(this->participant.getScore())));
                item->setBackground(Qt::green);
                this->ui->answerButton->setDisabled(true);
            }
            else {
                QMessageBox box;
                box.setText("Wrong answer!");
                box.exec();
            }
        }
        catch (std::exception& e) {
            QMessageBox box;
            box.setText(e.what());
            box.exec();
        }
    }

}
