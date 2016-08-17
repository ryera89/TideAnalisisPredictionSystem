#include "hourlytidaltablemodel.h"

int HourlyTidalTableModel::rowCount(const QModelIndex &/*parent*/) const
{
    return m_data->m_measurementDates.size() + 4;
}

int HourlyTidalTableModel::columnCount(const QModelIndex &parent) const
{
    return m_data->maxMeasurementNumberPerDay + 6;
}

/*QVariant HourlyTidalTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();

    if (role == Qt::TextAlignmentRole){
        return int(Qt::AlignVCenter | Qt::AlignHCenter);
    }else{
        if (role == Qt::DisplayRole){
          if (index.column() == 0 && index.row() == 0) return "FECHA";
          if (index.column() == 0 && (index.row() > 1 &&
                  index.row() < m_data->m_measurementDates.size()+2)){
              return m_data->m_measurementDates[index.row() - 2];
          }
          //NOTE: Aqui va lo de las dos ultimas filas

          if (index.column() == 1 && index.row() == 0) return "HORA";
          if (index.row() == 1 && index.column() > 0 &&
                  index.column() <= m_data->maxMeasurementNumberPerDay){
              return QTime(index.column(),0);
          }
          if (index.column() > 0 && index.column() < m_data->maxMeasurementNumberPerDay
                  && index.row() > 1 && index.row() < m_data->m_measurementDates.size() + 2){
              return m_data->m_measurements[index.column()
                      + m_data->m_measurementNumberPerDay[index.row()]];
          }

        }
    }
    return QVariant();
}*/
