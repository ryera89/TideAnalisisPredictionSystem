#ifndef CUSTOMCHARTVIEW_H
#define CUSTOMCHARTVIEW_H

#include <QWidget>
#include <QtCharts/QChartView>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QToolButton>


using namespace QtCharts;

class customChartView : public QChartView
{
    Q_OBJECT
public:
    customChartView(QChart *chart, QWidget *parent = 0);

signals:
    void seriesPoint(QPointF point);
protected:
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

public slots:

private:
    QPointF m_currentMousePos;
    //QToolButton *leftButton;
    //QToolButton *rightButton;

};

#endif // CUSTOMCHARTVIEW_H
