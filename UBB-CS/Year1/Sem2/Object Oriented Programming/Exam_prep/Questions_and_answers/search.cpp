//
// Created by Dragos on 6/29/2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_search.h" resolved

#include "search.h"
#include "ui_search.h"


search::search(QWidget *parent) :
        QWidget(parent), ui(new Ui::search) {
    ui->setupUi(this);
}

search::~search() {
    delete ui;
}

