#include "harmonicconstantfrequencytabledelegate.h"

#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QPainter>
void HarmonicConstantFrequencyTableDelegate::paint(
    QPainter *painter, const QStyleOptionViewItem &option,
    const QModelIndex &index) const {
  if (index.column() == nameColumn) {
    QString name = index.model()->data(index, Qt::DisplayRole).toString();

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
    painter->drawText(myOption.rect.adjusted(0, 0, -3, 0), name,
                      QTextOption(Qt::AlignVCenter | Qt::AlignRight));
    painter->restore();
  } else {
    if (index.column() == freqColumn) {
      double frequency = index.model()->data(index, Qt::DisplayRole).toDouble();

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
                        QString::number(frequency),
                        QTextOption(Qt::AlignVCenter | Qt::AlignRight));
      painter->restore();

    } else {
      if (index.column() == descColumn) {
        QString description =
            index.model()->data(index, Qt::DisplayRole).toString();

        QStyleOptionViewItem myOption = option;
        myOption.displayAlignment = Qt::AlignLeft | Qt::AlignVCenter;

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
        painter->drawText(myOption.rect.adjusted(0, 0, -3, 0), description,
                          QTextOption(Qt::AlignVCenter | Qt::AlignLeft));
        painter->restore();
      } else {
        QStyledItemDelegate::paint(painter, option, index);
      }
    }
  }
}

QWidget *HarmonicConstantFrequencyTableDelegate::createEditor(
    QWidget *parent, const QStyleOptionViewItem &option,
    const QModelIndex &index) const {
  if (index.column() == nameColumn) {
    QLineEdit *nameEdit = new QLineEdit(parent);

    connect(nameEdit, SIGNAL(editingFinished()), this,
            SLOT(commitAndCloseNameEditor()));
    return nameEdit;
  }
  if (index.column() == freqColumn) {
    QDoubleSpinBox *freqEdit = new QDoubleSpinBox(parent);
    freqEdit->setDecimals(6);
    freqEdit->setRange(-1000000, 1000000);

    connect(freqEdit, SIGNAL(editingFinished()), this,
            SLOT(commitAndCloseFreqEditor()));
    return freqEdit;
  }
  if (index.column() == descColumn) {
    QLineEdit *descEdit = new QLineEdit(parent);

    connect(descEdit, SIGNAL(editingFinished()), this,
            SLOT(commitAndCloseDescEditor()));
    return descEdit;
  }

  return QStyledItemDelegate::createEditor(parent, option, index);
}

void HarmonicConstantFrequencyTableDelegate::setEditorData(
    QWidget *editor, const QModelIndex &index) const {
  if (index.column() == nameColumn) {
    QString name = index.model()->data(index).toString();
    QLineEdit *nameEditor = qobject_cast<QLineEdit *>(editor);
    // Q_ASSERT(dateEditor);
    nameEditor->setText(name);
  } else if (index.column() == freqColumn) {
    double frequency = index.model()->data(index).toDouble();
    QDoubleSpinBox *freqEditor = qobject_cast<QDoubleSpinBox *>(editor);
    freqEditor->setValue(frequency);
  } else if (index.column() == descColumn) {
    QString description = index.model()->data(index).toString();
    QLineEdit *descEditor = qobject_cast<QLineEdit *>(editor);

    descEditor->setText(description);
  } else {
    QStyledItemDelegate::setEditorData(editor, index);
  }
}

void HarmonicConstantFrequencyTableDelegate::setModelData(
    QWidget *editor, QAbstractItemModel *model,
    const QModelIndex &index) const {
  if (index.column() == nameColumn) {
    QLineEdit *nameEditor = qobject_cast<QLineEdit *>(editor);
    model->setData(index, nameEditor->text());
  } else if (index.column() == freqColumn) {
    QDoubleSpinBox *freqEditor = qobject_cast<QDoubleSpinBox *>(editor);
    model->setData(index, freqEditor->value());
  } else if (index.column() == descColumn) {
    QLineEdit *descEditor = qobject_cast<QLineEdit *>(editor);
    model->setData(index, descEditor->text());

  } else {
    QStyledItemDelegate::setModelData(editor, model, index);
  }
}

void HarmonicConstantFrequencyTableDelegate::commitAndCloseNameEditor() {
  QLineEdit *editor = qobject_cast<QLineEdit *>(sender());
  emit commitData(editor);
  emit closeEditor(editor);
}

void HarmonicConstantFrequencyTableDelegate::commitAndCloseFreqEditor() {
  QDoubleSpinBox *editor = qobject_cast<QDoubleSpinBox *>(sender());
  emit commitData(editor);
  emit closeEditor(editor);
}

void HarmonicConstantFrequencyTableDelegate::commitAndCloseDescEditor() {
  QLineEdit *editor = qobject_cast<QLineEdit *>(sender());
  emit commitData(editor);
  emit closeEditor(editor);
}
