#include "manualharmonicconstantsdelegate.h"

#include <QDoubleSpinBox>
#include <QPainter>

ManualHarmonicConstantsDelegate::ManualHarmonicConstantsDelegate(QObject *parent):QStyledItemDelegate(parent){}


void ManualHarmonicConstantsDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    switch (index.column()) {
    case 0:{
        QString hcName = index.model()->data(index,Qt::DisplayRole).toString();

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

        painter->drawText(myOption.rect.adjusted(0,0,-3,0),hcName,
                          QTextOption(Qt::AlignVCenter | Qt::AlignRight));
        painter->restore();
        break;
    }
    case 1:{
        double val = index.model()->data(index,Qt::DisplayRole).toDouble();

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

        painter->drawText(myOption.rect.adjusted(0,0,-3,0),QString::number(val,'f',6),
                          QTextOption(Qt::AlignVCenter | Qt::AlignRight));
        painter->restore();
        break;
    }
    case 2:{
        double val = index.model()->data(index,Qt::DisplayRole).toDouble();

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

        painter->drawText(myOption.rect.adjusted(0,0,-3,0),QString::number(val,'f',6),
                          QTextOption(Qt::AlignVCenter | Qt::AlignRight));
        painter->restore();
        break;
    }
    case 3:{
        double val = index.model()->data(index,Qt::DisplayRole).toDouble();

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

        painter->drawText(myOption.rect.adjusted(0,0,-3,0),QString::number(val,'f',3),
                          QTextOption(Qt::AlignVCenter | Qt::AlignRight));
        painter->restore();
        break;
    }
    default:
        QStyledItemDelegate::paint(painter,option,index);
        break;
    }
}

QWidget *ManualHarmonicConstantsDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == 2){
        QDoubleSpinBox *ampEditor =  new QDoubleSpinBox(parent);
        ampEditor->setDecimals(6);
        connect(ampEditor,SIGNAL(editingFinished()),this,SLOT(commitAndCloseAmpEditor()));
        return ampEditor;
    }
    if (index.column() == 3){
        QDoubleSpinBox *phaseEditor =  new QDoubleSpinBox(parent);
        phaseEditor->setDecimals(3);
        connect(phaseEditor,SIGNAL(editingFinished()),this,SLOT(commitAndClosePhaseEditor()));
        return phaseEditor;
    }

    return QStyledItemDelegate::createEditor(parent,option,index);
}

void ManualHarmonicConstantsDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (index.column() == 2){
        double amp = index.model()->data(index).toDouble();

        QDoubleSpinBox *ampEditor = qobject_cast<QDoubleSpinBox*>(editor);
        ampEditor->setValue(amp);
    }else if (index.column() == 3){
        double phase = index.model()->data(index).toDouble();

        QDoubleSpinBox *phaseEditor = qobject_cast<QDoubleSpinBox*>(editor);
        phaseEditor->setValue(phase);
    }else{
        QStyledItemDelegate::setEditorData(editor,index);
    }
}

void ManualHarmonicConstantsDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (index.column() == 2){
        QDoubleSpinBox *ampEditor = qobject_cast<QDoubleSpinBox*>(editor);
        ampEditor->interpretText();
        model->setData(index,ampEditor->value());
    }else if (index.column() == 3){
        QDoubleSpinBox *phaseEditor = qobject_cast<QDoubleSpinBox*>(editor);
        phaseEditor->interpretText();
        model->setData(index,phaseEditor->value());
    }else{
        QStyledItemDelegate::setModelData(editor,model,index);
    }
}

void ManualHarmonicConstantsDelegate::commitAndCloseAmpEditor()
{
    QDoubleSpinBox *editor = qobject_cast<QDoubleSpinBox*>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}

void ManualHarmonicConstantsDelegate::commitAndClosePhaseEditor()
{
    QDoubleSpinBox *editor = qobject_cast<QDoubleSpinBox*>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}
