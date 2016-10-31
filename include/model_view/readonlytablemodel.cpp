#include "readonlytablemodel.h"


int ReadOnlyTableModel::rowCount(const QModelIndex &parent) const
{
    return m_data.size();
}

int ReadOnlyTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 3;
}

QVariant ReadOnlyTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();

    if (role == Qt::TextAlignmentRole){
        return int(Qt::AlignVCenter | Qt::AlignRight);
    }else{
        if (role == Qt::DisplayRole){
            switch (index.column()) {
            case 0:
                return m_data[index.row()].measurementDate();
            case 1:
                return m_data[index.row()].measurementTime();
            case 2:
                return m_data[index.row()].seaLevel();
            default:
                return QVariant();
            }

        }
    }
    return QVariant();
}

QVariant ReadOnlyTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole){
        if (orientation == Qt::Horizontal){
           return headers[section];
        }
        if (orientation == Qt::Vertical){
            return section + 1;
        }
    }

    return QVariant();
}

void ReadOnlyTableModel::setMeasurements(const QVector<TidesMeasurement> &measurement)
{
    beginResetModel();
    m_data = measurement;
    endResetModel();
}

/*void ReadOnlyTableModel::setMeasurements(const QVector<TidesMeasurement> &measurement)
{
    beginResetModel();
    measurements = measurement;
    endResetModel();
}*/
