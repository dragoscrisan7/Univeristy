//
// Created by Oana on 6/7/2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_GUI.h" resolved

#include <QMessageBox>
#include "gui.h"
#include "ui_GUI.h"
#include "develop.h"


GUI::GUI(Service& service, Writer& writer, TableModel* tableModel, QWidget *parent) :
        QWidget(parent), ui(new Ui::GUI), service{service}, writer{writer}, model{tableModel} {
    ui->setupUi(this);
    this->ui->tableView->setModel(model);
    this->ui->tableView->show();
    std::string name = this->writer.getName();
    connectSignalsAndSlots();
    this->setWindowTitle(QString::fromStdString(name));
    if (this->writer.getExpertise()!="Senior")
        this->ui->acceptIdeaButton->hide();

}

GUI::~GUI() {
    delete ui;
}

void GUI::connectSignalsAndSlots() {
    QObject::connect(this->ui->addIdeaButton, &QPushButton::clicked, this,&GUI::addIdea);
    QObject::connect(this->ui->acceptIdeaButton, &QPushButton::clicked, this, &GUI::acceptIdea);
    QObject::connect(this->ui->savePlotButton, &QPushButton::clicked, this, &GUI::savePlot);
    QObject::connect(this->ui->developButton, &QPushButton::clicked, this, &GUI::developIdea);
}

void GUI::addIdea() {
    std::string description = this->ui->descriptionEdit->text().toStdString();
    int act = this->ui->actEdit->text().toInt();
    try {
        //this->service.addIdea(description, this->writer.getName(), act);
        Idea* idea = new Idea{description, "proposed", this->writer.getName(), act};
        this->model->addIdea(*idea);
        this->ui->tableView->resizeColumnsToContents();
    }catch(char const* e){
        QMessageBox box;
        box.setText(QString::fromStdString(e));
        box.exec();
    }
}

void GUI::acceptIdea() {
    int act = this->ui->actEdit->text().toInt();
    std::string description=this->ui->descriptionEdit->text().toStdString();
    try{
        this->model->acceptIdea(description, act);
        this->ui->tableView->resizeColumnsToContents();

    }catch(char const* e){
        QMessageBox box;
        box.setText(QString::fromStdString(e));
        box.exec();
    }
}

void GUI::savePlot() {
    this->service.saveToFileAcceptedIdeas();
    QMessageBox box;
    box.setText("Ideas are added.");
    box.exec();
}

void GUI::developIdea() {
    auto accepted = this->service.allAcceptedIdeas();
    std::vector<Idea> acceptedByWriter ;
    for (auto item: accepted)
        if(item.getCreator()==writer.getName())
            acceptedByWriter.push_back(item);
    if(acceptedByWriter.size()==0){
        QMessageBox box;
        box.setText("This button is unavailable for you");
        box.exec();
        return;
    }
    for(int i=0;i<acceptedByWriter.size();i++){
        Develop* dv = new Develop{acceptedByWriter[i]};
        dv->show();
    }

}
