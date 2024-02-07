#ifndef HARMONICCONSTANTFREQUENCYTABLEMODEL_H
#define HARMONICCONSTANTFREQUENCYTABLEMODEL_H

#include <QAbstractTableModel>

#include "include/HarmonicConstantsModule/HarmonicConstantClass/harmonicconstant.h"

class HarmonicConstantFrequencyTableModel : public QAbstractTableModel {
  Q_OBJECT
public:
  HarmonicConstantFrequencyTableModel(QObject *parent = 0);
  HarmonicConstantFrequencyTableModel(QVector<HarmonicConstant> &datos,
                                      QObject *parent = 0);

  int rowCount(const QModelIndex &parent) const;
  int columnCount(const QModelIndex &parent) const;
  QVariant data(const QModelIndex &index, int role) const;

  QVariant headerData(int section, Qt::Orientation orientation, int role) const;

  // Para habilitar edicion
  bool setData(const QModelIndex &index, const QVariant &value, int role);
  bool setHeaderData(int section, Qt::Orientation orientation,
                     const QVariant &value, int role);
  Qt::ItemFlags
  flags(const QModelIndex &index) const; // debe retornar Qt::ItemIsEditable

  // Deben estar conectados a la vista
  bool insertRows(int row, int count,
                  const QModelIndex &parent = QModelIndex());
  bool insertRow(int row, const QModelIndex &parent);
  // bool insertColumns(int column, int count, const QModelIndex &parent);
  bool removeRows(int row, int count,
                  const QModelIndex &parent = QModelIndex());
  bool removeRow(int row, const QModelIndex &parent);
  // bool removeColumns(int column, int count, const QModelIndex &parent);

  QVector<HarmonicConstant> allData() const;
  void setAllData(const QVector<HarmonicConstant> &datos);

private:
  QVector<HarmonicConstant> m_data;
  QStringList m_headers;
};

#endif // HARMONICCONSTANTFREQUENCYTABLEMODEL_H
