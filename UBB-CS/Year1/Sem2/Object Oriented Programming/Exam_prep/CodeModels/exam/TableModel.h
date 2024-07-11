#pragma once
#include "Service.h"
#include <QAbstractTableModel>

class TableModel : public QAbstractTableModel{
private:
    Service& service;
public:
    TableModel(Service& service,  QObject* parent = nullptr);
    int rowCount(const QModelIndex& parent = QModelIndex{}) const override;

    int columnCount(const QModelIndex &parent = QModelIndex{}) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void addIdea(const Idea& idea);

    void acceptIdea(std::string description, int act);

};
