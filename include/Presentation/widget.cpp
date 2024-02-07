#include "widget.h"
#include "ui_widget.h"
#include <QGraphicsOpacityEffect>
#include <QPicture>
Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);

  // QGraphicsOpacityEffect *opacity = new QGraphicsOpacityEffect();
  // QGraphicsOpacityEffect *opacityLabel = new QGraphicsOpacityEffect();

  // ui->frame->setAttribute(Qt::WA_TranslucentBackground);
  // ui->frame->setWindowOpacity(0.7);

  // opacity->setOpacity(0.5);
  // opacityLabel->setOpacity(1.0);

  // ui->frame->setGraphicsEffect(opacity);
  // ui->label->setGraphicsEffect(opacityLabel);
}

Widget::~Widget() { delete ui; }
