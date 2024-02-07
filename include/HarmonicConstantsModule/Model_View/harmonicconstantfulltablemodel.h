#ifndef HARMONICCONSTANTFULLTABLEMODEL_H
#define HARMONICCONSTANTFULLTABLEMODEL_H

#include "include/HarmonicConstantsModule/HarmonicConstantClass/harmonicconstant.h"
#include <QAbstractTableModel>

class HarmonicConstantFullTableModel : public QAbstractTableModel {
public:
  HarmonicConstantFullTableModel(QObject *parent = 0);
  HarmonicConstantFullTableModel(const QVector<HarmonicConstant> &datos,
                                 QObject *parent = 0);

  int rowCount(const QModelIndex &parent) const;
  int columnCount(const QModelIndex &parent) const;
  QVariant data(const QModelIndex &index, int role) const;

  QVariant headerData(int section, Qt::Orientation orientation, int role) const;

  QVector<HarmonicConstant> allData() const;
  void setAllData(const QVector<HarmonicConstant> &datos);

private:
  QVector<HarmonicConstant> m_data;
  QStringList m_headers;
};

#endif // HARMONICCONSTANTFULLTABLEMODEL_H
