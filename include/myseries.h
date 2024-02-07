#ifndef MYSERIES_H
#define MYSERIES_H

#include <QtCharts/QScatterSeries>
#include <QtCharts/QSplineSeries>

using namespace QtCharts;

class MySeries : public QSplineSeries, QScatterSeries {

  Q_OBJECT
public:
  MySeries(QObject *parent = 0) : QSplineSeries(parent) {}
};

#endif // MYSERIES_H
