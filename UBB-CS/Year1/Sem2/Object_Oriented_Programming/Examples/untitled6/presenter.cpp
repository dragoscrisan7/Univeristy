#include "presenter.h"
#include "ui_presenter.h"


presenter::presenter(QWidget *parent) :
        QWidget(parent), ui(new Ui::presenter) {
    ui->setupUi(this);
}

presenter::~presenter() {
    delete ui;
}
