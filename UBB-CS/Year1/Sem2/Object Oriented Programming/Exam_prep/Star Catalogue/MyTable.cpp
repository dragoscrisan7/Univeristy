//
// Created by Dragos on 7/5/2022.
//

#include "MyTable.h"
#include <QBrush>

MyTable::MyTable(const vector<Stars> &arr) : arr(arr) {}

int MyTable::rowCount(const QModelIndex &parent) const {
    return arr.size();
}

int MyTable::columnCount(const QModelIndex &parent) const {
    return 4;
}

void MyTable::update(vector<Stars>& new_arr) {
    arr = new_arr;
    auto top = createIndex(0,0);
    auto bottom = createIndex(rowCount(), columnCount());

    emit dataChanged(top, bottom);
    emit layoutChanged();
}

QVariant MyTable::data(const QModelIndex& index, int role) const{
    if(role == Qt::DisplayRole){
        auto& item = arr[index.row()];
        auto col = index.column();
        if(col == 0){
            return QString::fromStdString(item.getName());
        }
        if(col == 1){
            return QString::number(item.getRa());
        }
        if(col == 2){
            return QString::number(item.getDec());
        }
        if(col == 3){
            return QString::number(item.getDiameter());
        }
    }
    if(role == Qt::BackgroundRole){
        auto& item = arr[index.row()];
        if(item.getDiameter()>10){
            QBrush bg(Qt::red);
            return bg;
        }
    }
    return QVariant{};
}

