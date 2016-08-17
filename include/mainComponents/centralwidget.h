#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>

class QTableView;
#include <QHBoxLayout>
#include "spmchart.h"
#include <QPlainTextEdit>
#include "include/model_view/tablemodel.h"
#include "include/model_view/tidaltabledelegate.h"
#include "include/model_view/readonlytablemodel.h"
#include "customchartview.h"
#include <iostream>


class CentralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CentralWidget(QWidget *parent = 0);

signals:

public slots:
    //void loadData(const QString &filePath);
    //void loadDataInTable(const QVector<TidesMeasurement> &measurements);
    //void loadDataChart(); //Funcion para actualizar la grafica.
    //void updateDataInChartWhenRowIsEliminated(int i, int cont); //Slot para modificar la tabla cuando se elimina una fila
    //void  checkDateTimeStringFormat(const QString &dateFormat, const QString &timeFormat);

    QSplineSeries* chartSerie() const{return m_series;}
    void updateSerieData(int row);
    void setSeriesData();

    QTableView* tableView() const{return m_tidalTableView;}


private:
    //Table Facilities
    QTableView *m_tidalTableView;



    //Chart Facilities

    SPMChart *m_tideChart;
    customChartView *m_tideChartView;

    QDateTimeAxis *m_timeAxis;
    //QValueAxis *m_yAxis;

    QSplineSeries *m_series;

    void settingUpTable();

};

#endif // CENTRALWIDGET_H
