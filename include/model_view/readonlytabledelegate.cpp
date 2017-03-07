#include "readonlytabledelegate.h"
#include <QDate>
#include <QTime>
#include <QDateEdit>
#include <QTimeEdit>
#include <QLineEdit>
#include <QPainter>

ReadOnlyTableDelegate::ReadOnlyTableDelegate(QObject *parent):QStyledItemDelegate(parent){}

void ReadOnlyTableDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == dateColumn){
        QDate date = index.model()->data(index,Qt::DisplayRole).toDate();

        QStyleOptionViewItem myOption = option;
        myOption.displayAlignment = Qt::AlignRight | Qt::AlignVCenter;

        initStyleOption(&myOption,index);
        painter->save();
        painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

        if (myOption.state & QStyle::State_Selected){
            painter->fillRect(myOption.rect,myOption.palette.highlight());
            painter->setPen(myOption.palette.highlightedText().color());
        }else{
            painter->setPen(myOption.palette.windowText().color());
        }
        painter->drawText(myOption.rect.adjusted(0,0,-3,0),date.toString("dd/MM/yyyy"),
                          QTextOption(Qt::AlignVCenter | Qt::AlignRight));
        painter->restore();

    }else{
        if (index.column() == timeColumn){
            QTime time = index.model()->data(index,Qt::DisplayRole).toTime();

            QStyleOptionViewItem myOption = option;
            myOption.displayAlignment = Qt::AlignRight | Qt::AlignVCenter;

            initStyleOption(&myOption,index);
            painter->save();
            painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

            if (myOption.state & QStyle::State_Selected){
                painter->fillRect(myOption.rect,myOption.palette.highlight());
                painter->setPen(myOption.palette.highlightedText().color());
            }else{
                painter->setPen(myOption.palette.windowText().color());
            }
            painter->drawText(myOption.rect.adjusted(0,0,-3,0),time.toString("hh:mm:ss"),
                              QTextOption(Qt::AlignVCenter | Qt::AlignRight));
            painter->restore();
        }else{
            if (index.column() == levelColumn){
                double level = index.model()->data(index,Qt::DisplayRole).toDouble();

                QStyleOptionViewItem myOption = option;
                myOption.displayAlignment = Qt::AlignRight | Qt::AlignVCenter;

                initStyleOption(&myOption,index);
                painter->save();
                painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

                if (myOption.state & QStyle::State_Selected){
                    painter->fillRect(myOption.rect,myOption.palette.highlight());
                    painter->setPen(myOption.palette.highlightedText().color());
                }else{
                    painter->setPen(myOption.palette.windowText().color());
                }
                painter->drawText(myOption.rect.adjusted(0,0,-3,0),QString::number(level,'f',3),
                                  QTextOption(Qt::AlignVCenter | Qt::AlignRight));
                painter->restore();
            }else{
                QStyledItemDelegate::paint(painter,option,index);
            }
        }
    }

}



