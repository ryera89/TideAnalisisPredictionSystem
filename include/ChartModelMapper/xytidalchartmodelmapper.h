#ifndef XYTIDALCHARTMODELMAPPER_H
#define XYTIDALCHARTMODELMAPPER_H

#include "../model_view/tablemodel.h"
#include <QObject>
#include <QtCharts>
class ReadOnlyTableModel;
// TODO: impementar el update cuando se agregan filas

class XYTidalChartModelMapper : public QObject {
  Q_OBJECT

public:
  explicit XYTidalChartModelMapper(QAbstractTableModel *model,
                                   QXYSeries *series, QObject *parent = 0);

  void setSeries(QXYSeries *series);

private slots:
  void updateSeriesData(const QModelIndex &topLeft,
                        const QModelIndex &bottomRight,
                        const QVector<int> &roles = QVector<int>());

private:
  QAbstractTableModel *m_model;
  QXYSeries *m_series;
};

#endif // XYTIDALCHARTMODELMAPPER_H
