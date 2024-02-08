#include "hctabledelegate.h"

#include <QPainter>

HCTableDelegate::HCTableDelegate(QObject *parent)
    : QStyledItemDelegate(parent) {}

void HCTableDelegate::paint(QPainter *painter,
                            const QStyleOptionViewItem &option,
                            const QModelIndex &index) const {
  switch (index.column()) {
  case 0: {
    QString hcName = index.model()->data(index, Qt::DisplayRole).toString();

    QStyleOptionViewItem myOption = option;
    myOption.displayAlignment = Qt::AlignRight | Qt::AlignVCenter;

    initStyleOption(&myOption, index);
    painter->save();
    painter->setRenderHints(QPainter::Antialiasing |
                            QPainter::TextAntialiasing);

    if (myOption.state & QStyle::State_Selected) {
      painter->fillRect(myOption.rect, myOption.palette.highlight());
      painter->setPen(myOption.palette.highlightedText().color());
    } else {
      painter->setPen(myOption.palette.windowText().color());
    }

    painter->drawText(myOption.rect.adjusted(0, 0, -3, 0), hcName,
                      QTextOption(Qt::AlignVCenter | Qt::AlignRight));
    painter->restore();
    break;
  }
  case 1: {
    double val = index.model()->data(index, Qt::DisplayRole).toDouble();

    QStyleOptionViewItem myOption = option;
    myOption.displayAlignment = Qt::AlignRight | Qt::AlignVCenter;

    initStyleOption(&myOption, index);
    painter->save();
    painter->setRenderHints(QPainter::Antialiasing |
                            QPainter::TextAntialiasing);

    if (myOption.state & QStyle::State_Selected) {
      painter->fillRect(myOption.rect, myOption.palette.highlight());
      painter->setPen(myOption.palette.highlightedText().color());
    } else {
      painter->setPen(myOption.palette.windowText().color());
    }

    painter->drawText(myOption.rect.adjusted(0, 0, -3, 0),
                      QString::number(val, 'f', 6),
                      QTextOption(Qt::AlignVCenter | Qt::AlignRight));
    painter->restore();
    break;
  }
  case 2: {
    double val = index.model()->data(index, Qt::DisplayRole).toDouble();

    QStyleOptionViewItem myOption = option;
    myOption.displayAlignment = Qt::AlignRight | Qt::AlignVCenter;

    initStyleOption(&myOption, index);
    painter->save();
    painter->setRenderHints(QPainter::Antialiasing |
                            QPainter::TextAntialiasing);

    if (myOption.state & QStyle::State_Selected) {
      painter->fillRect(myOption.rect, myOption.palette.highlight());
      painter->setPen(myOption.palette.highlightedText().color());
    } else {
      painter->setPen(myOption.palette.windowText().color());
    }

    painter->drawText(myOption.rect.adjusted(0, 0, -3, 0),
                      QString::number(val, 'f', 6),
                      QTextOption(Qt::AlignVCenter | Qt::AlignRight));
    painter->restore();
    break;
  }
  case 3: {
    double val = index.model()->data(index, Qt::DisplayRole).toDouble();

    QStyleOptionViewItem myOption = option;
    myOption.displayAlignment = Qt::AlignRight | Qt::AlignVCenter;

    initStyleOption(&myOption, index);
    painter->save();
    painter->setRenderHints(QPainter::Antialiasing |
                            QPainter::TextAntialiasing);

    if (myOption.state & QStyle::State_Selected) {
      painter->fillRect(myOption.rect, myOption.palette.highlight());
      painter->setPen(myOption.palette.highlightedText().color());
    } else {
      painter->setPen(myOption.palette.windowText().color());
    }

    painter->drawText(myOption.rect.adjusted(0, 0, -3, 0),
                      QString::number(val, 'f', 6),
                      QTextOption(Qt::AlignVCenter | Qt::AlignRight));
    painter->restore();
    break;
  }
  case 4: {
    double val = index.model()->data(index, Qt::DisplayRole).toDouble();

    QStyleOptionViewItem myOption = option;
    myOption.displayAlignment = Qt::AlignRight | Qt::AlignVCenter;

    initStyleOption(&myOption, index);
    painter->save();
    painter->setRenderHints(QPainter::Antialiasing |
                            QPainter::TextAntialiasing);

    if (myOption.state & QStyle::State_Selected) {
      painter->fillRect(myOption.rect, myOption.palette.highlight());
      painter->setPen(myOption.palette.highlightedText().color());
    } else {
      painter->setPen(myOption.palette.windowText().color());
    }

    painter->drawText(myOption.rect.adjusted(0, 0, -3, 0),
                      QString::number(val, 'f', 6),
                      QTextOption(Qt::AlignVCenter | Qt::AlignRight));
    painter->restore();
    break;
  }
  case 5: {
    double val = index.model()->data(index, Qt::DisplayRole).toDouble();

    QStyleOptionViewItem myOption = option;
    myOption.displayAlignment = Qt::AlignRight | Qt::AlignVCenter;

    initStyleOption(&myOption, index);
    painter->save();
    painter->setRenderHints(QPainter::Antialiasing |
                            QPainter::TextAntialiasing);

    if (myOption.state & QStyle::State_Selected) {
      painter->fillRect(myOption.rect, myOption.palette.highlight());
      painter->setPen(myOption.palette.highlightedText().color());
    } else {
      painter->setPen(myOption.palette.windowText().color());
    }

    painter->drawText(myOption.rect.adjusted(0, 0, -3, 0),
                      QString::number(val, 'f', 3),
                      QTextOption(Qt::AlignVCenter | Qt::AlignRight));
    painter->restore();
    break;
  }
  case 6: {
    double val = index.model()->data(index, Qt::DisplayRole).toDouble();

    QStyleOptionViewItem myOption = option;
    myOption.displayAlignment = Qt::AlignRight | Qt::AlignVCenter;

    initStyleOption(&myOption, index);
    painter->save();
    painter->setRenderHints(QPainter::Antialiasing |
                            QPainter::TextAntialiasing);

    if (myOption.state & QStyle::State_Selected) {
      painter->fillRect(myOption.rect, myOption.palette.highlight());
      painter->setPen(myOption.palette.highlightedText().color());
    } else {
      painter->setPen(myOption.palette.windowText().color());
    }

    painter->drawText(myOption.rect.adjusted(0, 0, -3, 0),
                      QString::number(val, 'f', 3),
                      QTextOption(Qt::AlignVCenter | Qt::AlignRight));
    painter->restore();
    break;
  }
  default:
    QStyledItemDelegate::paint(painter, option, index);
    break;
  }
  /*if (index.column() == 0){ //Constituente
      QString hcName = index.model()->data(index,Qt::DisplayRole).toString();

      QStyleOptionViewItem myOption = option;
      myOption.displayAlignment = Qt::AlignRight | Qt::AlignVCenter;

      initStyleOption(&myOption,index);
      painter->save();
      painter->setRenderHints(QPainter::Antialiasing |
  QPainter::TextAntialiasing);

      if (myOption.state & QStyle::State_Selected){
          painter->fillRect(myOption.rect,myOption.palette.highlight());
          painter->setPen(myOption.palette.highlightedText().color());
      }else{
          painter->setPen(myOption.palette.windowText().color());
      }

      painter->drawText(myOption.rect.adjusted(0,0,-3,0),hcName,
                        QTextOption(Qt::AlignVCenter | Qt::AlignRight));
      painter->restore();

  }
  if (index.column() == 1){ //Frecuencia
      double val = index.model()->data(index,Qt::DisplayRole).toDouble();

      QStyleOptionViewItem myOption = option;
      myOption.displayAlignment = Qt::AlignRight | Qt::AlignVCenter;

      initStyleOption(&myOption,index);
      painter->save();
      painter->setRenderHints(QPainter::Antialiasing |
  QPainter::TextAntialiasing);

      if (myOption.state & QStyle::State_Selected){
          painter->fillRect(myOption.rect,myOption.palette.highlight());
          painter->setPen(myOption.palette.highlightedText().color());
      }else{
          painter->setPen(myOption.palette.windowText().color());
      }

      painter->drawText(myOption.rect.adjusted(0,0,-3,0),QString::number(val,'f',6),
                        QTextOption(Qt::AlignVCenter | Qt::AlignRight));
      painter->restore();
  }
  if (index.column() == 2){ //C
      double val = index.model()->data(index,Qt::DisplayRole).toDouble();

      QStyleOptionViewItem myOption = option;
      myOption.displayAlignment = Qt::AlignRight | Qt::AlignVCenter;

      initStyleOption(&myOption,index);
      painter->save();
      painter->setRenderHints(QPainter::Antialiasing |
  QPainter::TextAntialiasing);

      if (myOption.state & QStyle::State_Selected){
          painter->fillRect(myOption.rect,myOption.palette.highlight());
          painter->setPen(myOption.palette.highlightedText().color());
      }else{
          painter->setPen(myOption.palette.windowText().color());
      }

      painter->drawText(myOption.rect.adjusted(0,0,-3,0),QString::number(val,'f',6),
                        QTextOption(Qt::AlignVCenter | Qt::AlignRight));
      painter->restore();
  }
  if (index.column() == 3){ //S
      double val = index.model()->data(index,Qt::DisplayRole).toDouble();

      QStyleOptionViewItem myOption = option;
      myOption.displayAlignment = Qt::AlignRight | Qt::AlignVCenter;

      initStyleOption(&myOption,index);
      painter->save();
      painter->setRenderHints(QPainter::Antialiasing |
  QPainter::TextAntialiasing);

      if (myOption.state & QStyle::State_Selected){
          painter->fillRect(myOption.rect,myOption.palette.highlight());
          painter->setPen(myOption.palette.highlightedText().color());
      }else{
          painter->setPen(myOption.palette.windowText().color());
      }

      painter->drawText(myOption.rect.adjusted(0,0,-3,0),QString::number(val,'f',6),
                        QTextOption(Qt::AlignVCenter | Qt::AlignRight));
      painter->restore();
  }
  if (index.column() == 4){ //Amplitud
      double val = index.model()->data(index,Qt::DisplayRole).toDouble();

      QStyleOptionViewItem myOption = option;
      myOption.displayAlignment = Qt::AlignRight | Qt::AlignVCenter;

      initStyleOption(&myOption,index);
      painter->save();
      painter->setRenderHints(QPainter::Antialiasing |
  QPainter::TextAntialiasing);

      if (myOption.state & QStyle::State_Selected){
          painter->fillRect(myOption.rect,myOption.palette.highlight());
          painter->setPen(myOption.palette.highlightedText().color());
      }else{
          painter->setPen(myOption.palette.windowText().color());
      }

      painter->drawText(myOption.rect.adjusted(0,0,-3,0),QString::number(val,'f',6),
                        QTextOption(Qt::AlignVCenter | Qt::AlignRight));
      painter->restore();
  }
  if (index.column() == 5){ //Fase
      double val = index.model()->data(index,Qt::DisplayRole).toDouble();

      QStyleOptionViewItem myOption = option;
      myOption.displayAlignment = Qt::AlignRight | Qt::AlignVCenter;

      initStyleOption(&myOption,index);
      painter->save();
      painter->setRenderHints(QPainter::Antialiasing |
  QPainter::TextAntialiasing);

      if (myOption.state & QStyle::State_Selected){
          painter->fillRect(myOption.rect,myOption.palette.highlight());
          painter->setPen(myOption.palette.highlightedText().color());
      }else{
          painter->setPen(myOption.palette.windowText().color());
      }

      painter->drawText(myOption.rect.adjusted(0,0,-3,0),QString::number(val,'f',3),
                        QTextOption(Qt::AlignVCenter | Qt::AlignRight));
      painter->restore();
  }
  if (index.column() == 6){ //Fase Corregida
      double val = index.model()->data(index,Qt::DisplayRole).toDouble();

      QStyleOptionViewItem myOption = option;
      myOption.displayAlignment = Qt::AlignRight | Qt::AlignVCenter;

      initStyleOption(&myOption,index);
      painter->save();
      painter->setRenderHints(QPainter::Antialiasing |
  QPainter::TextAntialiasing);

      if (myOption.state & QStyle::State_Selected){
          painter->fillRect(myOption.rect,myOption.palette.highlight());
          painter->setPen(myOption.palette.highlightedText().color());
      }else{
          painter->setPen(myOption.palette.windowText().color());
      }

      painter->drawText(myOption.rect.adjusted(0,0,-3,0),QString::number(val,'f',3),
                        QTextOption(Qt::AlignVCenter | Qt::AlignRight));
      painter->restore();
  }*/
}
