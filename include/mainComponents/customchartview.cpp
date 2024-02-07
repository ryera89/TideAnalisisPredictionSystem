#include "customchartview.h"

#include <QHBoxLayout>
#include <QMouseEvent>
#include <QObject>
#include <QStyleOptionGraphicsItem>
#include <QVBoxLayout>

customChartView::customChartView(QChart *chart, QWidget *parent)
    : QChartView(chart, parent) {

  /*leftButton = new QToolButton(this);
  leftButton->setFixedWidth(50);
  leftButton->setFixedHeight(50);
  leftButton->setIcon(QIcon(":images/arrow_left.png"));


  rightButton = new QToolButton(this);
  rightButton->setFixedWidth(50);
  rightButton->setFixedHeight(50);
  rightButton->setIcon(QIcon(":images/arrow_right.png"));*/

  // QHBoxLayout *buttonLayout = new QHBoxLayout;
  // buttonLayout->addWidget(leftButton);
  // buttonLayout->addWidget(rightButton);
  // buttonLayout->setAlignment(Qt::AlignCenter);

  // buttonLayout->setGeometry(QRect(0,this->height() - 40,this->width(),40));
  // buttonLayout->setParent(this->layout());

  // buttonLayout->setAlignment()

  // QVBoxLayout *mainLayout = new QVBoxLayout;
  // mainLayout->
  // mainLayout->addLayout(buttonLayout);

  // setLayout(mainLayout);
}

void customChartView::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
  case Qt::Key_Left:
    chart()->scroll(-10, 0);
    emit seriesPoint(m_currentMousePos);
    break;
  case Qt::Key_Right:
    chart()->scroll(10, 0);
    emit seriesPoint(m_currentMousePos);
    break;

  case Qt::Key_Up: {
    chart()->scroll(0, 10);
    emit seriesPoint(m_currentMousePos);
    break;
  case Qt::Key_Down: {
    chart()->scroll(0, -10);
    emit seriesPoint(m_currentMousePos);
  } break;
  }
  case Qt::Key_Delete:
    emit deleteSelectedPointsOnGraph();
    break;
  default:
    QChartView::keyPressEvent(event);
    break;
  }
}

void customChartView::wheelEvent(QWheelEvent *event) {
  this->chart()->scroll(event->angleDelta().y(), 0);
  // emit seriesPoint(event->pos());
}

void customChartView::mouseMoveEvent(QMouseEvent *event) {
  /* if (this->chart()->plotArea().contains(event->pos())){

       m_currentMousePos = event->pos();

       emit seriesPoint(m_currentMousePos);

       //if (rubberBand() != QChartView::NoRubberBand) emit
   selectionUpdated(m_pressedMousePosition,m_currentMousePos);

   }*/
  QChartView::mouseMoveEvent(event);
  if (this->chart()->plotArea().contains(event->pos())) {

    m_currentMousePos = event->pos();

    emit seriesPoint(m_currentMousePos);

    // if (rubberBand() != QChartView::NoRubberBand) emit
    // selectionUpdated(m_pressedMousePosition,m_currentMousePos);
  }
  if (rubberBand() != QChartView::NoRubberBand)
    emit selectionUpdated(m_pressedMousePosition, m_currentMousePos);
}

void customChartView::mousePressEvent(QMouseEvent *event) {
  /*if (chart()->series().first()){
      QPointF clickedPoint =
  chart()->mapToValue(event->pos(),chart()->series().first());

      emit seriesPointPressed(clickedPoint);
  }else{
      QChartView::mousePressEvent(event);
  }*/
  // emit seriesPointPressed(event->pos());
  if (this->chart()->plotArea().contains(event->pos())) {
    m_pressedMousePosition = event->pos();
    setRubberBand(QChartView::HorizontalRubberBand);
  }
  QChartView::mousePressEvent(event);
}

void customChartView::mouseReleaseEvent(QMouseEvent *event) {
  if (this->rubberBand() != QChartView::NoRubberBand) {
    if (this->chart()->plotArea().contains(
            QPoint(event->pos().x(), chart()->plotArea().y()))) {
      m_releasedMousePosition = event->pos();
    } else {
      if (event->pos().x() >
          chart()->plotArea().left() + chart()->plotArea().width())
        m_releasedMousePosition =
            QPointF(chart()->plotArea().left() + chart()->plotArea().width(),
                    event->pos().y());
      else
        m_releasedMousePosition =
            QPointF(this->chart()->plotArea().left(), event->pos().y());
    }
    // m_releasedMousePosition = QPointF(this->chart()->plotArea().left() +
    // this->chart()->plotArea().width(),event->pos().y());

    this->setRubberBand(QChartView::NoRubberBand);

    if (qAbs(m_pressedMousePosition.x() - m_releasedMousePosition.x()) <= 4) {
      emit seriesPointPressed(m_releasedMousePosition);
    } else
      emit seriesPointsPressedAndRealesed(m_pressedMousePosition,
                                          m_releasedMousePosition);
  }
}
