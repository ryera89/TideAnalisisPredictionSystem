#ifndef SPMCHART_H
#define SPMCHART_H

#include <QtCharts>

using namespace QtCharts;

class SPMChart : public QChart
{
    Q_OBJECT
public:
    SPMChart(QGraphicsItem *parent = 0);

public slots:
    //void updateSeriesData();

};

#endif // SPMCHART_H
