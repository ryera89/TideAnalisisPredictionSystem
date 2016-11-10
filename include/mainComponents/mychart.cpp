#include "mychart.h"
#include <QPainter>

void MyChart::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();

    painter->setBrush(QBrush(Qt::red));

    QVector<QVector<QPointF>> seriesPoints;

    foreach (QAbstractSeries *serie, this->series()) {
        QVector<QPointF> pointOnGraph(0);
        QXYSeries *xySeries = qobject_cast<QXYSeries*>(serie);
        foreach (QPointF point, xySeries->pointsVector()) {
            pointOnGraph.append(mapToPosition(point,xySeries));
            painter->drawPoint(mapToPosition(point,xySeries));
        }
        seriesPoints.append(pointOnGraph);
    }

    painter->restore();

    QChart::paint(painter,option,widget);
    //QVector<QPointF> pointOnGraph(0);

    /*foreach (QPointF po, points) {
        pointOnGraph.append(chart()->mapToPosition(po,m_series));
    }*/

    /*foreach (var, container) {

    }
    painter.drawPoint(point);*/

    //QChartView::paintEvent(event);
}
