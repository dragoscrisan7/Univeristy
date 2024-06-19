//
// Created by Dragos on 7/5/2022.
//

#ifndef STAR_CATALOGUE_GUI_H
#define STAR_CATALOGUE_GUI_H
#include "Service.h"
#include "ARepo.h"
#include "MyTable.h"
#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class gui; }
QT_END_NAMESPACE

class gui : public QWidget, public Observer {
Q_OBJECT

public:
    explicit gui(Service& srv, Astronomers& a ,QWidget *parent = nullptr);

    ~gui() override;


    void connect();
    void add_star();
    void update() override;
    void view();
private:
    Ui::gui *ui;
    Service& srv;
    Astronomers ast;
    MyTable* model;
};


#endif //STAR_CATALOGUE_GUI_H
