//
// Created by Dragos on 7/6/2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_gui.h" resolved

#include "gui.h"
#include "ui_gui.h"


gui::gui(Service& srv, Users u, QWidget *parent) :
        QWidget(parent), ui(new Ui::gui), srv(srv), user(u) {
    ui->setupUi(this);
    this->setWindowTitle(QString::fromStdString(user.getName()));
    connect();
    srv.addObserver(this);
    update();

}

gui::~gui() {
    delete ui;
}

void gui::update() {
    ui->listPosts->clear();
    string name = user.getName();
    for(auto post:srv.getAllPosts(name)){
        string text = to_string(post.getId()) + "," + post.getText() + "," + to_string(post.getDay()) + "," + to_string(post.getMonth()) + "," + to_string(post.getYear()) + "," + post.getUser();
        ui->listPosts->addItem(QString::fromStdString(text));
    }
    ui->listSubscriptions->clear();
    for(auto topics: srv.getForUser(name)){
        string text = topics.getText();
        ui->listSubscriptions->addItem(QString::fromStdString(text));
    }
}

void gui::connect() {
    QObject::connect(ui->buttonAddPost, &QPushButton::clicked, this, &gui::add_post);
    QObject::connect(ui->buttonUpdatePost, &QPushButton::clicked, this, &gui::);
}

void gui::add_subscription() {

}


void gui::add_post() {
    string post = ui->lineAddPost->text().toStdString();
    /*vector<Topics> topics;
    for(int i=0;i<tokens.size();i++){

    }
    */
    int id = srv.getpostsize();
    string text = post;
    int d = 6;
    int m = 7;
    int y = 2022;
    string u = user.getName();
    srv.add(id,text,d,m,y,u);
}

void gui::update_post() {

}

