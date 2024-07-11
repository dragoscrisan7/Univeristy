// You may need to build the project (run Qt uic code generator) to get "ui_gui.h" resolved

#include "gui.h"
#include "ui_gui.h"
#include <QMessageBox>

vector<string> tokenize4(std::string str, char delimiter)
{
    std::vector <std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (getline(ss, token, delimiter))
        result.push_back(token);

    return result;
}


gui::gui(Service& srv, User& u, QWidget *parent) :
        QWidget(parent), ui(new Ui::gui), srv(srv), u(u){
    ui->setupUi(this);
    this->setWindowTitle(QString::fromStdString(u.getName()));
    this->srv.add_observer(this);
    update();
    connect_signals_and_sluts();
    ui->buttonAddAnswer->setDisabled(true);
    ui->spinBox->setDisabled(true);
}

gui::~gui() {
    delete ui;
}

void gui::update() {
    if(!ui->listWidget->selectedItems().empty()){
        show_answers();
    }
    ui->listWidget->clear();
    for(auto q: srv.sort_questions()){
        string text = to_string(q.getId()) + "," + q.getText() + "," + q.getUserName();
        ui->listWidget->addItem(QString::fromStdString(text));
    }
}

void gui::connect_signals_and_sluts() {
    QObject::connect(this->ui->buttonAddQuestion, &QPushButton::clicked, this, &gui::add_question);
    QObject::connect(this->ui->listWidget, &QListWidget::itemClicked, this, &gui::show_answers);
    QObject::connect(this->ui->buttonAddAnswer, &QPushButton::clicked, this, &gui::add_answer);
    QObject::connect(this->ui->listWidget_2, &QListWidget::itemClicked, this, &gui::upvote);
    QObject::connect(this->ui->spinBox, &QSpinBox::valueChanged, this, &gui::change_votes);
}

void gui::add_question() {
    string text = ui->lineTextQuestion->text().toStdString();
    this->srv.add_question(text, u.getName());
}

void gui::show_answers() {

    ui->listWidget_2->clear();
    auto item = ui->listWidget->selectedItems()[0];
    string line = item->text().toStdString();
    int qid = stoi(line.substr(0, line.find(',')));
    for(const auto& a:srv.answers_to_q(qid)){
        string text = to_string(a.getId()) + "," + to_string(a.getQid()) + "," + a.getText() + "," + a.getUserName() + "," + to_string(a.getVotes());
        ui->listWidget_2->addItem(QString::fromStdString(text));
        if(a.getUserName() == u.getName()){
            this->ui->listWidget_2->item(ui->listWidget_2->count()-1)->setBackground(Qt::yellow);
        }
    }
    ui->buttonAddAnswer->setDisabled(false);
}

void gui::add_answer() {
    string answer = ui->lineAnswer->text().toStdString();
    auto item = ui->listWidget->selectedItems()[0];
    string line = item->text().toStdString();
    int qid = stoi(line.substr(0, line.find(',')));
    srv.add_answer(qid, answer, u.getName());
}

void gui::upvote() {
    ui->spinBox->setDisabled(false);
    auto item = ui->listWidget_2->selectedItems()[0];
    string line = item->text().toStdString();
    vector<string> tokens = tokenize4(line, ',');
    string name = tokens[3];
    int votes = stoi(tokens[4]);
    ui->spinBox->setValue(votes);
    if(u.getName() == name){
        ui->spinBox->setDisabled(true);
    }
}

void gui::change_votes() {
    int votes = ui->spinBox->value();
    auto item = ui->listWidget_2->selectedItems()[0];
    string line = item->text().toStdString();
    int aid = stoi(line.substr(0, line.find(',')));
    srv.change_votes(aid, votes);
}