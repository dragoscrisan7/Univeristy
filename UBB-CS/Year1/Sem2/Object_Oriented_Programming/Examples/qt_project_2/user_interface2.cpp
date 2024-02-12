#include "user_interface2.h"
#include "ui_user_interface2.h"


user_interface2::user_interface2(Repo& r, QWidget *parent) :
        QWidget(parent), ui(new Ui::user_interface2), repo(r) {
    ui->setupUi(this);
    repo.read_from_file();
    this->Populate();
    this->connectSignalsAndSlots();
}

user_interface2::~user_interface2() {
    delete ui;
}

void user_interface2::Populate() {
    this->ui->listWidget->clear();

    repo.Sort();
    for(auto& item: repo.items){
        new QListWidgetItem(QString::fromStdString(item.To_string()), this->ui->listWidget);
    }
}

void user_interface2::connectSignalsAndSlots() {
    QObject::connect(ui->Button1,&QPushButton::clicked, this, &user_interface2::Press_Button);
    QObject::connect(ui->Button2, &QPushButton::clicked, this, &user_interface2::Press_Button2);
}

bool compare2(Item i1, Item i2){
    if(i1.get_quantity() > i2.get_quantity())
        return false;
    else
        return true;
}

void user_interface2::Press_Button() {
    this->ui->list2->clear();
    string c = ui->input_cateory->text().toStdString();
    vector<Item> cat_items;
    for(auto& item:repo.items){
        if(item.get_category() == c){
            cat_items.push_back(item);
        }
    }
    sort(cat_items.begin(), cat_items.end(), compare2);

    for(auto& item: cat_items){
        new QListWidgetItem(QString::fromStdString(item.To_string()),ui->list2);
    }
    std::destroy(cat_items.begin(), cat_items.end());
}

void user_interface2::Press_Button2() {
    this->ui->listWidget->clear();
    string c = ui->input_categry2->text().toStdString();
    string n = ui->input_name->text().toStdString();
    for(auto& item:repo.items){
        if(item.get_name().find(n) && item.get_category().find(c)) {
            new QListWidgetItem(QString::fromStdString(item.To_string()), ui->listWidget);
        }
    }
}

