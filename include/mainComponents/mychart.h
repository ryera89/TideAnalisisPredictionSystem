#ifndef MYCHART_H
#define MYCHART_H

#include <QtCharts>

class MyChart : public QChart {
  Q_OBJECT

public:
  MyChart(QGraphicsItem *parent = Q_NULLPTR,
          Qt::WindowFlags wFlags = Qt::WindowFlags())
      : QChart(parent, wFlags) {}

protected:
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget);
};

#endif // MYCHART_H
