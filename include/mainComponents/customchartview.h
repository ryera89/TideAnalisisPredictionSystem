#ifndef CUSTOMCHARTVIEW_H
#define CUSTOMCHARTVIEW_H

#include <QKeyEvent>
#include <QToolButton>
#include <QWheelEvent>
#include <QWidget>
#include <QtCharts>

class customChartView : public QChartView {
  Q_OBJECT
public:
  customChartView(QChart *chart, QWidget *parent = 0);

signals:
  void seriesPoint(QPointF point);
  void seriesPointPressed(QPointF point);
  void seriesPointsPressedAndRealesed(QPointF pPoint, QPointF rPoint);
  void deleteSelectedPointsOnGraph();
  void selectionUpdated(QPointF initialPos, QPointF currentPos);

protected:
  void keyPressEvent(QKeyEvent *event);
  void wheelEvent(QWheelEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);

public slots:

private:
  QPointF m_currentMousePos;
  QPointF m_pressedMousePosition;
  QPointF m_releasedMousePosition;
  // QToolButton *leftButton;
  // QToolButton *rightButton;
};

#endif // CUSTOMCHARTVIEW_H
