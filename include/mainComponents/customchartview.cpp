#include "customchartview.h"

#include <QObject>
#include <QHBoxLayout>
#include <QVBoxLayout>


customChartView::customChartView(QChart *chart, QWidget *parent): QChartView(chart,parent)
{
    /*leftButton = new QToolButton(this);
    leftButton->setFixedWidth(50);
    leftButton->setFixedHeight(50);
    leftButton->setIcon(QIcon(":images/arrow_left.png"));


    rightButton = new QToolButton(this);
    rightButton->setFixedWidth(50);
    rightButton->setFixedHeight(50);
    rightButton->setIcon(QIcon(":images/arrow_right.png"));*/

    //QHBoxLayout *buttonLayout = new QHBoxLayout;
    //buttonLayout->addWidget(leftButton);
    //buttonLayout->addWidget(rightButton);
    //buttonLayout->setAlignment(Qt::AlignCenter);

    //buttonLayout->setGeometry(QRect(0,this->height() - 40,this->width(),40));
    //buttonLayout->setParent(this->layout());

    //buttonLayout->setAlignment()

    //QVBoxLayout *mainLayout = new QVBoxLayout;
    //mainLayout->
    //mainLayout->addLayout(buttonLayout);

    //setLayout(mainLayout);
}

void customChartView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        chart()->zoomIn();
        break;
    case Qt::Key_Minus:
        chart()->zoomOut();
        break;
    case Qt::Key_Left:
        chart()->scroll(-10,0);
        break;
    case Qt::Key_Right:
        chart()->scroll(10,0);
        break;
    case Qt::Key_Up:
        chart()->scroll(0,10);
        break;
    case Qt::Key_Down:
        chart()->scroll(0,-10);
        break;
    default:
        QGraphicsView::keyPressEvent(event);
        break;
    }
}

void customChartView::wheelEvent(QWheelEvent *event)
{
  if (event->angleDelta().y() > 0) chart()->zoomIn();
  if (event->angleDelta().y() < 0) chart()->zoomOut();
}
