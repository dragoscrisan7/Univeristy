#include "user_interface.h"
#include "ui_user_interface.h"
#include <QDialog>
#include <QMessageBox>


user_interface::user_interface(QWidget *parent) :
        QWidget(parent), ui(new Ui::user_interface) {
    ui->setupUi(this);
    serv.read_from_file();
    connect_signals_and_slots();
    this->ui->durationLabel->clear();
    populate_list();
}

user_interface::~user_interface() {
    delete ui;
}

void user_interface::connect_signals_and_slots() {
    QObject::connect(this->ui->durationButton, &QPushButton::clicked, this, &user_interface::show_duration);

}

void user_interface::populate_list() {
    std::vector<Task> sorted_tasks = serv.sort_tasks();

    for (auto task: sorted_tasks){
        if (task.get_priority()==1){
            QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(task.to_string()));
            QFont font1;
            font1.setBold(true);
            item->setFont(font1);
            this->ui->listWidget->addItem(item);
        }
        else{
            QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(task.to_string()));
            this->ui->listWidget->addItem(item);
        }
    }
}

void user_interface::show_duration() {
    int priority_given = this->ui->priorityLineEdit->text().toInt();
    int total_duration = serv.total_duration_of_tasks_with_priority(priority_given);
    if (total_duration == -1){
        QMessageBox::warning(this, "Warning", "There are no tasks with the given priority.");

    }
    else{
        this->ui->durationLabel->setText(QString::fromStdString("Total duration: " + std::to_string(total_duration)));
    }

}

