#include "xytidalchartmodelmapper.h"
#include "include/model_view/readonlytablemodel.h"
#include <iostream>

XYTidalChartModelMapper::XYTidalChartModelMapper(QAbstractTableModel *model,
                                                 QXYSeries *series,
                                                 QObject *parent)
    : QObject(parent), m_model(model), m_series(series) {

  // connect(m_model,SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
  // this,SLOT(updateSeriesData(QModelIndex,QModelIndex,QVector<int>)));
  // connect(m_model,SIGNAL(modelReset()),this,SLOT(setSeriesData()));

  // connect(this,SIGNAL(modelChanged(TableModel*)),this,SIGNAL(chartSeriesUpdated()));
  // connect(this,SIGNAL(seriesChanged(QXYSeries*)),this,SIGNAL(chartSeriesUpdated()));
}

void XYTidalChartModelMapper::setSeries(QXYSeries *series) {
  if (series)
    m_series = series;
}

void XYTidalChartModelMapper::updateSeriesData(const QModelIndex &topLeft,
                                               const QModelIndex &bottomRight,
                                               const QVector<int> &roles) {
  Q_UNUSED(roles)

  int topRow = topLeft.row();
  int bottomRow = bottomRight.row();

  // int firstColumn = topLeft.column();
  // int lastColumn = bottomRight.column();

  for (int i = topRow; i <= bottomRow; ++i) {
    double y_value;
    QDateTime x_value;

    x_value.setDate(
        m_model->data(m_model->index(i, 0), Qt::DisplayRole).toDate());

    x_value.setTime(
        m_model->data(m_model->index(i, 1), Qt::DisplayRole).toTime());

    y_value = m_model->data(m_model->index(i, 2), Qt::DisplayRole).toDouble();

    if (i < m_series->count()) {
      m_series->replace(i, x_value.toMSecsSinceEpoch(), y_value);
    } else {
      if (i == m_series->count()) {
        m_series->append(x_value.toMSecsSinceEpoch(), y_value);
      } else {
        int k = m_series->count();
        while (k < i) {
          m_series->append(0, 0);
          ++k;
        }
        m_series->append(x_value.toMSecsSinceEpoch(), y_value);
      }
    }
  }
}
