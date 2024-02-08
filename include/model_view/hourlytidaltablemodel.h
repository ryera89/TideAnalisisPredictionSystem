#ifndef HOURLYTIDALTABLEMODEL_H
#define HOURLYTIDALTABLEMODEL_H

#include "../measurement/tidaldata.h"
#include <QAbstractTableModel>

class HourlyTidalTableModel : public QAbstractTableModel {
public:
  HourlyTidalTableModel(QObject *parent);

  int rowCount(const QModelIndex &parent) const;
  int columnCount(const QModelIndex &parent) const;
  // QVariant data(const QModelIndex &index, int role) const;

private:
  TidalData *m_data;
};

#endif // HOURLYTIDALTABLEMODEL_H
