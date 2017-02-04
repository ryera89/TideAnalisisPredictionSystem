#include "tidaltabledelegate.h"
#include <QDate>
#include <QTime>
#include <QDateEdit>
#include <QTimeEdit>
#include <QLineEdit>
#include <QPainter>

TidalTableDelegate::TidalTableDelegate(QObject *parent): QStyledItemDelegate(parent){}
void TidalTableDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
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
        painter->drawText(myOption.rect.adjusted(0,0,-3,0),date.toString("yyyy/MM/dd"),
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
                painter->drawText(myOption.rect.adjusted(0,0,-3,0),QString::number(level),
                                  QTextOption(Qt::AlignVCenter | Qt::AlignRight));
                painter->restore();
            }else{
                QStyledItemDelegate::paint(painter,option,index);
            }
        }
    }

}

QWidget *TidalTableDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == dateColumn){
        QDateEdit *dateEdit = new QDateEdit(parent);
        dateEdit->setDisplayFormat("yyyy/MM/dd");

        connect(dateEdit,SIGNAL(editingFinished()),this,SLOT(commitAndCloseDateEditor()));
        return dateEdit;
    }
    if (index.column() == timeColumn){
        QTimeEdit *timeEdit = new QTimeEdit(parent);
        timeEdit->setDisplayFormat("hh:mm:ss");

        connect(timeEdit,SIGNAL(editingFinished()),this,SLOT(commitAndCloseTimeEditor()));
        return timeEdit;
    }
    if (index.column() == levelColumn){
        QLineEdit *levelEdit = new QLineEdit(parent);
        QDoubleValidator *validator = new QDoubleValidator;
        levelEdit->setValidator(validator);

        connect(levelEdit,SIGNAL(editingFinished()),this,SLOT(commitAndCloseLevelEditor()));
        return levelEdit;
    }

    return QStyledItemDelegate::createEditor(parent,option,index);
}

void TidalTableDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (index.column() == dateColumn){
        QDate date = index.model()->data(index).toDate();
        QDateEdit *dateEditor = qobject_cast<QDateEdit*>(editor);
        //Q_ASSERT(dateEditor);
        dateEditor->setDate(date);
    }else if (index.column() == timeColumn){
        QTime time = index.model()->data(index).toTime();
        QTimeEdit *timeEditor = qobject_cast<QTimeEdit*>(editor);
        timeEditor->setTime(time);
    }else if (index.column() == levelColumn){
        double value = index.model()->data(index).toDouble();
        QLineEdit *levelEditor = qobject_cast<QLineEdit*>(editor);

        levelEditor->setText(QString::number(value));
    }else{
        QStyledItemDelegate::setEditorData(editor,index);
    }

}

void TidalTableDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (index.column() == dateColumn){
        QDateEdit *dateEditor = qobject_cast<QDateEdit*>(editor);
        dateEditor->interpretText();
        model->setData(index,dateEditor->date());
    }else if (index.column() == timeColumn){
        QTimeEdit *timeEditor = qobject_cast<QTimeEdit*>(editor);
        timeEditor->interpretText();
        model->setData(index,timeEditor->time());
    }else if (index.column() == levelColumn){
       QLineEdit *levelEditor = qobject_cast<QLineEdit*>(editor);
       model->setData(index,levelEditor->text().toDouble());

    }else{
         QStyledItemDelegate::setModelData(editor,model,index);
    }

}

void TidalTableDelegate::commitAndCloseDateEditor()
{
    QDateEdit *editor = qobject_cast<QDateEdit *>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}

void TidalTableDelegate::commitAndCloseTimeEditor()
{
    QTimeEdit *editor = qobject_cast<QTimeEdit *>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}

void TidalTableDelegate::commitAndCloseLevelEditor()
{
    QLineEdit *editor = qobject_cast<QLineEdit*>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}
