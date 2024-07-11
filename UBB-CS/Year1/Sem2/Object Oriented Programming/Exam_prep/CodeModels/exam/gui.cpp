//
// Created by Dragos on 6/11/2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_gui.h" resolved

#include "gui.h"
#include "ui_gui.h"
#include <QMessageBox>
#include "develop.h"


gui::gui(Service& service, Writer& writer, TableModel* tableModel, QWidget *parent) :
        QWidget(parent), ui(new Ui::gui), service{service}, writer{writer}, model{tableModel} {
    ui->setupUi(this);
    this->ui->tableView->setModel(model);
    this->ui->tableView->show();
    std::string name = this->writer.getName();
    connectSignalsAndSlots();
    this->setWindowTitle(QString::fromStdString(name));
    if (this->writer.getExpertise()!="Senior")
        this->ui->acceptIdeaButton->hide();
}

gui::~gui() {
    delete ui;
}

void gui::connectSignalsAndSlots() {
    QObject::connect(this->ui->addIdeaButton, &QPushButton::clicked, this,&gui::addIdea);
    QObject::connect(this->ui->acceptIdeaButton, &QPushButton::clicked, this, &gui::acceptIdea);
    QObject::connect(this->ui->savePlotButton, &QPushButton::clicked, this, &gui::savePlot);
    QObject::connect(this->ui->developButton, &QPushButton::clicked, this, &gui::developIdea);
}

void gui::addIdea() {
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

void gui::acceptIdea() {
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

void gui::savePlot() {
    this->service.saveToFileAcceptedIdeas();
    QMessageBox box;
    box.setText("Ideas are added.");
    box.exec();
}

void gui::developIdea() {
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
        develop* dv = new develop{acceptedByWriter[i]};
        dv->show();
    }
}

