#include "TableModel.h"

TableModel::TableModel(Service& service, QObject *parent) : QAbstractTableModel{parent}, service{service} {

}

int TableModel::rowCount(const QModelIndex &parent) const {
    return service.allIdeas().size();
}

int TableModel::columnCount(const QModelIndex &parent) const {
    return 4;
}

QVariant TableModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    int column = index.column();
    Idea idea = this->service.allIdeas()[row];
    if (role == Qt::DisplayRole)
    {
        switch (column)
        {
            case 0:
                return QString::fromStdString(idea.getDescription());
            case 1:
                return QString::fromStdString(idea.getStatus());
            case 2:
                return QString::fromStdString(idea.getCreator());
            case 3:
                return QString::number(idea.getAct());
            default: break;
        }
    }
    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
                case 0:
                    return QString{ "Description" };
                case 1:
                    return QString{ "Status" };
                case 2:
                    return QString{ "Creator" };
                case 3:
                    return QString{ "Act" };
                default:
                    break;
            }
        }
    }
    return QVariant{};

}

void TableModel::addIdea(const Idea &idea) {
    int n = this->service.allIdeas().size();
    this->beginInsertRows(QModelIndex{}, n, n);
    this->service.addIdea(idea.getDescription(), idea.getCreator(), idea.getAct());
    this->endInsertRows();
}

void TableModel::acceptIdea(std::string description, int act) {
    this->beginResetModel();
    this->service.acceptIdea(description, act);
    this->endResetModel();
}
