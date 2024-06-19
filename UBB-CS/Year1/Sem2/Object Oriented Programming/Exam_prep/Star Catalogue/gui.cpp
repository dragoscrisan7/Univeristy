//
// Created by Dragos on 7/5/2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_gui.h" resolved

#include "gui.h"
#include "ui_gui.h"
#include <QMessageBox>


gui::gui(Service& srv, Astronomers& a, QWidget *parent) :
        QWidget(parent), ui(new Ui::gui), srv(srv), ast(a) {
    ui->setupUi(this);
    srv.addObserver(this);
    model = new MyTable(srv.getAllStars());
    ui->tableView->setModel(model);
    update();
    connect();
    this->setWindowTitle(QString::fromStdString(ast.getName()));
}

gui::~gui() {
    delete ui;
}

void gui::add_star() {
    string name = ui->lineName->text().toStdString();
    int RA = ui->lineRA->text().toInt();
    int Dec = ui->lineDec->text().toInt();
    int diam = ui->lineDiam->text().toInt();
    string constellation = ast.getConstellation();
    if(diam<=0 || name == "" || srv.search(name)){
        QMessageBox box;
        box.setText("Error adding");
        box.exec();
    }
    else{
        srv.add(name, constellation, RA, Dec, diam);
    }
}

void gui::update() {
    if(ui->checkBox->isChecked()){
        auto v = srv.getAllWithConst(ast.getConstellation());
        model->update(v);
    }
    else{
        model->update(srv.getAllStars());
    }
}

void gui::connect() {
    QObject::connect(ui->buttonAdd, &QPushButton::clicked, this, &gui::add_star);
    QObject::connect(ui->checkBox, &QCheckBox::stateChanged, this, &gui::update);
    QObject::connect(ui->tableView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &gui::view);
}

void gui::view() {
    auto rows = ui->tableView->selectionModel()->selectedIndexes();
    if(rows.empty()){
        QMessageBox box;
        box.setText("error with view");
        box.exec();
    }
    auto name = rows[0].data(Qt::DisplayRole).toString().toStdString();
}

