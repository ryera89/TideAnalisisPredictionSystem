#include "tablemodel.h"

TableModel::TableModel(QObject *parent): QAbstractTableModel(parent)
{
    headers << "Fecha" << "Hora" << "Nivel del Mar";


}

int TableModel::rowCount(const QModelIndex /*&parent*/) const
{
    return measurements.size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();

    if (role == Qt::TextAlignmentRole){
        return int(Qt::AlignVCenter | Qt::AlignRight);
    }else{
        if (role == Qt::DisplayRole){
            switch (index.column()) {
            case 0:
                return measurements[index.row()].measurementDate();
            case 1:
                return measurements[index.row()].measurementTime();
            case 2:
                return measurements[index.row()].seaLevel();
            default:
                return QVariant();
            }

        }
    }
    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole){
        if (orientation == Qt::Horizontal){
           return headers[section];
        }
        if (orientation == Qt::Vertical){
            return section;
        }
    }
    return QVariant();
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole){
        switch (index.column()) {
        case 0:
            //TODO: Quizas inicializar comprovaciones de fechas
            measurements[index.row()].setMeasurementDate(value.toDate());
            emit dataChanged(index,index);
            return true;
        case 1:
            //TODO: Quizas inicializar comprobaciones de tiempo
            measurements[index.row()].setMeasurementTime(value.toTime());
            emit dataChanged(index,index);
            return true;
        case 2:
            measurements[index.row()].setSeaLevel(value.toDouble());
            emit dataChanged(index,index);
            return true;
        default:
            return false;
        }
    }
    return false;
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    flags |= Qt::ItemIsEditable;
    return flags;
}

bool TableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent,row,row+count-1);
    for (int i = 0; i < count; ++i ){
        measurements.insert(row,TidesMeasurement());
        ++row;
    }
    endInsertRows();
    return true;
}

bool TableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row+count-1);
    for (int i = 0; i < count; ++i ){
        measurements.remove(row);
        ++row;
    }
    endRemoveRows();
    return true;
}

void TableModel::setMeasurements(const QVector<TidesMeasurement> &measurement)
{
    beginResetModel();
    measurements = measurement;
    endResetModel();
}

