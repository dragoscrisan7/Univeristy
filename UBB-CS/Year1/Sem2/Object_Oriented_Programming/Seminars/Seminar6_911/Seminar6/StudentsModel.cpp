#include "StudentsModel.h"
#include <qbrush.h>
#include <qcolor.h>

StudentsModel::StudentsModel(Repository& repo): repo{repo}
{
}

int StudentsModel::rowCount(const QModelIndex& parent) const
{
	return this->repo.getSize();
}

int StudentsModel::columnCount(const QModelIndex& parent) const
{
	return 4;
}

QVariant StudentsModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	int column = index.column();
	Student x= repo.getStudents()[row];
	if (role == Qt::DisplayRole) {
		switch (column)
		{
		case 0:
			return QString::fromStdString(x.getName());
		case 1:
			return QString::fromStdString(x.getGroup());
		case 2:
			return QString::number(x.getSeminarGrade());
		case 3:
			return QString::number(x.getLabGrade());
		default:
			break;
		}
	}
	if (role == Qt::BackgroundRole) {
		if (row % 2) {
			QBrush b(QColor(250,220,220));
			return b;
		}

	}
	
	

	return QVariant();
}

QVariant StudentsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal) {
		if (role == Qt::DisplayRole) {
			switch (section)
			{
			case 0:
				return "Name";
			case 1:
				return "Group";
			case 2:
				return "Seminar Grade";
			case 3:
				return "Lab Grade";
			default:
				break;
			}
		}
	}
	return QVariant();
}

Qt::ItemFlags StudentsModel::flags(const QModelIndex& index) const
{
	int row = index.row();
	int col = index.column();

	if (col >= 2)
		return Qt::ItemIsEditable | Qt::ItemIsEnabled;

	return Qt::ItemFlags();
}

bool StudentsModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	int row = index.row();
	int column = index.column();

	Student& student = this->repo.getStudents()[row];

	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		switch (column)
		{
		case 2:
			student.setSeminarGrade(value.toDouble());
		case 3:
			student.setLabGrade(value.toDouble());
		default:
			break;
		}
	}

	emit dataChanged(index, index);

	return false;
}
