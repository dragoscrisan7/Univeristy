#include "user_interface.h"
#include "ui_user_interface.h"


user_interface::user_interface(Repo& r, QWidget *parent) :
        QWidget(parent), ui(new Ui::user_interface), repo(r) {
    ui->setupUi(this);
    repo.loadData();
    this->populateList();
    this->connectSignalsAndSlots();
}

user_interface::~user_interface() {
    delete ui;
}

void user_interface::populateList() {
    this->ui->listWidget->clear();

    repo.sortVector();

    for (auto Weather: repo.weathers){
        new QListWidgetItem(QString::fromStdString(Weather.To_string()),this->ui->listWidget);
    }
}

void user_interface::press_button() {
    ui->listWidget->clear();
    int p = ui->input_prec->text().toInt();
    for(auto& weather:repo.weathers){
        if(weather.get_prec() < p)
            new QListWidgetItem(QString::fromStdString(weather.To_string()),this->ui->listWidget);
    }
}

void user_interface::press_button2() {
    this->ui->listWidget_2->clear();
    int start = ui->input_start->text().toInt();
    string desc = ui->input_desc->text().toStdString();

    int total_nr_of_hours = 0;
    for(auto& weather:repo.weathers){
        if(weather.get_desc() == desc && weather.get_start() > start){
            int nr_hours = weather.get_end() - weather.get_start();
            total_nr_of_hours += nr_hours;
        }
        else if(weather.get_desc() == desc && weather.get_end() < start){
            int nr_hours = weather.get_end() - start;
            total_nr_of_hours += nr_hours;
        }
    }
    string result;
    if(total_nr_of_hours == 0)
        result = "no match";
    else
        result = to_string(total_nr_of_hours);
    new QListWidgetItem(QString::fromStdString(result), this->ui->listWidget_2);
}

void user_interface::connectSignalsAndSlots() {
    QObject::connect(this->ui->pushButton, &QPushButton::clicked, this, &user_interface::press_button);
    QObject::connect(this->ui->result_button, &QPushButton::clicked, this, &user_interface::press_button2);
}


