#include "presenter.h"
#include "ui_Presenter.h"
#include <QMessageBox>
#include <sstream>

Presenter::Presenter(Service& s, Participant& p, QWidget *parent) :
        QWidget(parent), ui(new Ui::Presenter), srv(s), p(p){
    ui->setupUi(this);

    this->srv.addObserver(this);
    this->update();
    this->setWindowTitle("Presented");
    if(this->p.getName() != "presenter"){
        this->setWindowTitle(QString::fromStdString(p.getName()));
        this->ui->idLabel->hide();
        this->ui->textLabel->hide();
        this->ui->correctAnsweLabel->hide();
        this->ui->scoreLabel->hide();
        this->ui->idLine->hide();
        this->ui->textLine->hide();
        this->ui->scoreLine->hide();
        this->ui->correctAnswerLine->hide();
        this->ui->questionButton->hide();
    }
    else{
        this->ui->answerButton->hide();
        this->ui->answerlabel->hide();
        this->ui->answerLine->hide();
    }
}

void Presenter::update(){
    this->ui->listWidget->clear();
    if(p.getName() == "presenter"){
        for(auto item:this->srv.sorted_by_id()){
            string txt;
            txt = "id: "+std::to_string(item.getId()) + ", question: " + item.getText() + ", answer "+ item.getCorrectAnswer() + ", score: " + std::to_string(item.getScore());
            this->ui->listWidget->addItem(QString::fromStdString(txt));
        }
    }
    else{
        for(auto item:this->srv.sorted_by_score()){
            string txt;
            txt = "id: "+std::to_string(item.getId()) + ", question: " + item.getText() + ", answer "+ item.getCorrectAnswer() + ", score: " + std::to_string(item.getScore());
            this->ui->listWidget->addItem(QString::fromStdString(txt));
        }
    }
}

Presenter::~Presenter() {
    delete ui;
}

void Presenter::add_question() {
    int id = this->ui->idLine->text().toInt();
    int score = this->ui->scoreLine->text().toInt();
    string text = this->ui->textLine->text().toStdString();
    string c_a = this->ui->correctAnswerLine->text().toStdString();
    try{
        this->srv.add_question(id, text, c_a, score);
        this->ui->idLine->clear();
        this->ui->scoreLine->clear();
        this->ui->textLine->clear();
        this->ui->correctAnswerLine->clear();
    }
    catch(string e){
        QMessageBox box;
        box.setText(QString::fromStdString(e));
        box.exec();
    }

}

void Presenter::answer_question() {
    string text = this->ui->answerLine->text().toStdString();
    for(auto item:this->ui->listWidget->selectedItems()) {
        string text = item->text().toStdString();
        stringstream ss{text};
        string token;

        getline(ss, token, ':');
        getline(ss, token, ' ');

        stringstream ss2{token};
        getline(ss, token, ',');

        int id = std::stoi(token);
        try {
            if (this->srv.is_answer(id, text)) {
                this->answered.push_back(id);
                this->p.upScore(this->srv.get_question_score(id));
                this->ui->scoreLine->setText(QString::fromStdString(std::to_string(this->p.getScore())));
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

