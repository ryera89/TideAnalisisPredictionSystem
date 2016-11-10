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


protected:
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);

public slots:
    void zoomXAxis(quint32 level);

private:
    //QToolButton *leftButton;
    //QToolButton *rightButton;
    quint32 m_currentXZoomLevel;
};

#endif // CUSTOMCHARTVIEW_H
