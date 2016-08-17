#ifndef XYTIDALCHARTMODELMAPPER_H
#define XYTIDALCHARTMODELMAPPER_H

#include <QObject>
#include "include/model_view/tablemodel.h"
#include <QtCharts>

//TODO: impementar el update cuando se agregan filas
using namespace QtCharts;

class XYTidalChartModelMapper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QXYSeries* series READ series WRITE setSeries NOTIFY seriesChanged)
    Q_PROPERTY(QAbstractTableModel* model READ model WRITE setModel NOTIFY modelChanged)

public:
    explicit XYTidalChartModelMapper(QAbstractTableModel *model, QXYSeries *series, QObject *parent = 0);

QXYSeries* series() const
{
    return m_series;
}

QAbstractTableModel* model() const
{
    return m_model;
}

signals:

void seriesChanged(QXYSeries* series);

void modelChanged(QAbstractTableModel* model);

void chartSeriesUpdated(int);
void chartSeriesSeted();

public slots:
void setSeries(QXYSeries* series)
{
    if (m_series == series)
        return;

    m_series = series;
    emit seriesChanged(series);
}
void setModel(QAbstractTableModel* model)
{
    if (m_model == model)
        return;

    m_model = model;
    emit modelChanged(model);
}


private slots:
void updateSeriesData(const QModelIndex &topLeft, const QModelIndex &bottomRight,
                      const QVector<int> &roles = QVector<int> ());
void setSeriesData();

private:
QXYSeries* m_series;
QAbstractTableModel* m_model;




};

#endif // XYTIDALCHARTMODELMAPPER_H
