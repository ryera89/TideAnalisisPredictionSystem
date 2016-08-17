#include "xytidalchartmodelmapper.h"
#include <iostream>


XYTidalChartModelMapper::XYTidalChartModelMapper(QAbstractTableModel *model, QXYSeries *series, QObject *parent)
    : m_model(model), m_series(series), QObject(parent)
{

    connect(m_model,SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
            this,SLOT(updateSeriesData(QModelIndex,QModelIndex,QVector<int>)));
    connect(m_model,SIGNAL(modelReset()),this,SLOT(setSeriesData()));
    connect(this,SIGNAL(modelChanged(QAbstractTableModel*)),this,SLOT(setSeriesData()));
    connect(this,SIGNAL(seriesChanged(QXYSeries*)),this,SLOT(setSeriesData()));

    //connect(this,SIGNAL(modelChanged(TableModel*)),this,SIGNAL(chartSeriesUpdated()));
    //connect(this,SIGNAL(seriesChanged(QXYSeries*)),this,SIGNAL(chartSeriesUpdated()));
}

//WARNING: Ver si hay problemas en la conversion.
void XYTidalChartModelMapper::updateSeriesData(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    int topRow = topLeft.row();
    int bottomRow = bottomRight.row();

    int firstColumn = topLeft.column();
    int lastColumn = bottomRight.column();

    for (topRow; topRow <= bottomRow; ++topRow){
        double y_value;
        QDateTime x_value;
        for (firstColumn; firstColumn <= lastColumn; ++firstColumn){
             x_value.setDate(m_model->data(m_model->index(topRow,0),
                                              Qt::DisplayRole).toDate());

             x_value.setTime(m_model->data(m_model->index(topRow,1),
                                              Qt::DisplayRole).toTime());

             y_value = m_model->data(model()->index(topRow,2),
                                        Qt::DisplayRole).toDouble();

        }
        if (topRow < m_series->count()){
            m_series->replace(topRow,x_value.toMSecsSinceEpoch(),y_value);
        }else{
            if (topRow == m_series->count()){
                m_series->append(x_value.toMSecsSinceEpoch(),y_value);
            }else{
                int i = m_series->count();
                while (i < topRow){
                    m_series->append(0,0);
                    ++i;
                }
                m_series->append(x_value.toMSecsSinceEpoch(),y_value);
            }
        }
        emit chartSeriesUpdated(topRow);
    }

}

void XYTidalChartModelMapper::setSeriesData()
{
    m_series->clear();
    int rowNumber = m_model->rowCount(QModelIndex());
    int columnNumber = m_model->columnCount(QModelIndex());

    for (int i = 0; i < rowNumber; ++i){
        double y_value;
        QDateTime x_value;
        for (int j = 0; j < columnNumber; ++j){
            x_value.setDate(m_model->data(m_model->index(i,0),
                                              Qt::DisplayRole).toDate());
            x_value.setTime(m_model->data(m_model->index(i,1),
                                              Qt::DisplayRole).toTime());
            y_value = m_model->data(model()->index(i,2),
                                        Qt::DisplayRole).toDouble();

        }
        m_series->append(x_value.toMSecsSinceEpoch(),y_value);
    }
    emit chartSeriesSeted();
}
