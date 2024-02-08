#include "mylistmodeldelegate.h"
#include <QLineEdit>
#include <QMessageBox>
#include <QPainter>

/*void MyListModelDelegate::paint(QPainter *painter, const QStyleOptionViewItem
&option, const QModelIndex &index) const
{
    QString str = index.model()->data(index,Qt::DisplayRole).toString();
    QStyleOptionViewItem myOption = option;
    myOption.displayAlignment = Qt::AlignLeft | Qt::AlignVCenter;

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

    painter->drawText(myOption.rect.adjusted(0,0,-3,0),str,
                      QTextOption(Qt::AlignVCenter | Qt::AlignLeft));

    painter->restore();

}*/

QWidget *MyListModelDelegate::createEditor(QWidget *parent,
                                           const QStyleOptionViewItem &option,
                                           const QModelIndex &index) const {
  Q_UNUSED(option);
  Q_UNUSED(index);
  QLineEdit *textEdit = new QLineEdit(parent);

  // connect(textEdit,SIGNAL(editingFinished()),this,SLOT(commitAndCloseEditor()));
  return textEdit;
}

void MyListModelDelegate::setEditorData(QWidget *editor,
                                        const QModelIndex &index) const {
  QString str = index.model()->data(index).toString();
  QLineEdit *textEditor = qobject_cast<QLineEdit *>(editor);

  textEditor->setText(str);
}

void MyListModelDelegate::setModelData(QWidget *editor,
                                       QAbstractItemModel *model,
                                       const QModelIndex &index) const {
  QLineEdit *textEditor = qobject_cast<QLineEdit *>(editor);
  QString newName = textEditor->text(); // VAraiable que guarda el text de
                                        // editor
  QString oldName =
      model->data(index).toString(); // VAriable que el nombre viejo

  QVector<QString> modelValues;
  for (int i = 0; i < model->rowCount(); ++i) {
    QModelIndex auxIndex = model->index(i, 0);
    if (index != auxIndex)
      modelValues.push_back(model->data(auxIndex).toString());
  }
  if (!modelValues.contains(textEditor->text())) {
    model->setData(index, textEditor->text());
    emit schemeNameChanged(oldName, newName);
  } else {
    QMessageBox::information(0, tr("Esquema Duplicado"),
                             tr("Ya existe un esquema con ese nombre."));
    textEditor->setText(oldName);
    model->setData(index, textEditor->text());
  }
}

void MyListModelDelegate::commitAndCloseEditor() {
  QLineEdit *editor = qobject_cast<QLineEdit *>(sender());
  emit commitData(editor);
  emit closeEditor(editor);
}
