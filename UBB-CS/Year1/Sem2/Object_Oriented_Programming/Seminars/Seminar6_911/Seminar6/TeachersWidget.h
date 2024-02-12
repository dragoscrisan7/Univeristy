#pragma once

#include <QWidget>
#include "ui_TeachersWidget.h"
#include <QAbstractItemModel>

class TeachersWidget : public QWidget
{
	Q_OBJECT

public:
	TeachersWidget(QAbstractItemModel* model, QWidget *parent = Q_NULLPTR);
	~TeachersWidget();

private:
	Ui::TeachersWidget ui;
};
