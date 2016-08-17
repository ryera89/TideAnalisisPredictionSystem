#include "readonlytablemodel.h"


int ReadOnlyTableModel::rowCount(const QModelIndex &parent) const
{
    return m_data->m_measurements.size();
}

int ReadOnlyTableModel::columnCount(const QModelIndex &parent) const
{
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
                return m_data->m_measurements[index.row()].measurementDate();
            case 1:
                return m_data->m_measurements[index.row()].measurementTime();
            case 2:
                return m_data->m_measurements[index.row()].seaLevel();
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

void ReadOnlyTableModel::setDataSource(const QVector<TidesMeasurement> &measurement)
{
    beginResetModel();
    m_data->setDataSource(measurement);
    endResetModel();
}



/*void ReadOnlyTableModel::setMeasurements(const QVector<TidesMeasurement> &measurement)
{
    beginResetModel();
    measurements = measurement;
    endResetModel();
}*/
