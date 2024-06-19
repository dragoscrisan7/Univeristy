#include "TeachersWidget.h"

TeachersWidget::TeachersWidget(QAbstractItemModel* model, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	ui.studentsTableView->setModel(model);
}

TeachersWidget::~TeachersWidget()
{
}
