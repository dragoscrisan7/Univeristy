#pragma once
#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class presenter; }
QT_END_NAMESPACE

class presenter : public QWidget {
Q_OBJECT

public:
    explicit presenter(QWidget *parent = nullptr);

    ~presenter() override;

private:
    Ui::presenter *ui;
};