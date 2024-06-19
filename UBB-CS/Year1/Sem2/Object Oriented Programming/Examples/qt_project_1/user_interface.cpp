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
    this->ui->list_tasks->clear();

    repo.sortVector();

    for (auto Task: repo.tasks){
        QListWidgetItem* q = new QListWidgetItem(QString::fromStdString(Task.To_string()),this->ui->list_tasks);
        QFont f;
        f.setBold(true);
        if(Task.get_priority() == 1){
            q->setFont(f);
        }
    }
}

void user_interface::press_button() {
    int p = ui->input->text().toInt();
    int total = 0;
    int ok = 0;
    for(auto& task:repo.tasks){
        if(task.get_priority() == p)
            total += task.get_duration();
    }
    if(total == 0){
        this->ui->msgBox->setText("There are no tasks with the given priority");
    }
    else
        this->ui->msgBox->setText(QString::fromStdString(std::to_string(total)));

}

void user_interface::connectSignalsAndSlots() {
    QObject::connect(this->ui->button, &QPushButton::clicked, this, &user_interface::press_button);
}

