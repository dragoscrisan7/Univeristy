#include "user_interface.h"
#include "ui_user_interface.h"
#include "QMessageBox"

user_interface::user_interface(Programmer& p, Repository &repo, QWidget *parent) :
        QWidget(parent), ui(new Ui::user_interface), repo(repo), p(p) {
    ui->setupUi(this);
    repo.add(this);
    populate();
    connect_sluts_and_buttons();
}

user_interface::~user_interface() {
    delete ui;
}

void user_interface::populate() {
    this->ui->listWidget->clear();
    for(auto elem: this->repo.sortedFiles()){
        string txt = elem.getName() + "," + elem.getCreator() + "," + elem.getReviewer() + ',' + elem.getStatus() + "\n";
        auto *item = new QListWidgetItem();
        QFont font;
        font.setBold(true);
        item->setText(QString::fromStdString(txt));
        if(elem.isNotRevised())
            item->setFont(font);
        this->ui->listWidget->addItem(item);
    }
    this->ui->revisedLabel->setText(QString::fromStdString(to_string(p.getRevised())));
    this->ui->mustReviseLabel->setText(QString::fromStdString(to_string(p.getMustRevise())));
}

void user_interface::add_file() {
    string name = this->ui->lineAddFile->text().toStdString();
    if(name == ""){
        QMessageBox box;
        box.setText(QString::fromStdString("empty name\n"));
        box.exec();
    }
    else{
        int ok = 0;
        for(auto file: repo.getFiles()){
            if(file.getName() == name){
                ok = 1;
            }
        }
        if(ok == 1){
            QMessageBox box;
            box.setText(QString::fromStdString("empty name\n"));
            box.exec();
        }
        else{
            SourceFile sf{name, this->p.getName(), "not_revised", " "};
            this->repo.add_file(sf);
            populate();
        }
    }
}

void user_interface::connect_sluts_and_buttons() {
    QObject::connect(this->ui->addButton, &QPushButton::clicked, this, &user_interface::add_file);
    QObject::connect(this->ui->reviseButton, &QListWidget::itemSelectionChanged, this, &user_interface::revise);
}

void user_interface::revise() {

}




