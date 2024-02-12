//
// Created by Dragos on 7/5/2022.
//

#pragma once

#include "Service.h"
#include <QAbstractTableModel>

class MyTable : public QAbstractTableModel{
private:
    vector<Stars> arr;
public:
    MyTable(const vector<Stars> &arr);
    int rowCount(const QModelIndex& parent = QModelIndex{}) const override;

    int columnCount(const QModelIndex &parent = QModelIndex{}) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    void update(vector<Stars>& new_arr);
};

