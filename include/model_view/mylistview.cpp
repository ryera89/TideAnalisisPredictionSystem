#include "mylistview.h"
#include <QAction>
#include <QContextMenuEvent>
#include <QKeyEvent>
#include <QMenu>

MyListView::MyListView(QWidget *parent) : QListView(parent) {
  createContextMenu();
}

void MyListView::contextMenuEvent(QContextMenuEvent *event) {
  // m_contextMenu->exec(QCursor::pos());

  if (this->indexAt(event->pos()).isValid()) {
    m_addAction->setDisabled(true);
    m_removeAction->setEnabled(true);
    m_renameAction->setEnabled(true);
    m_contextMenu->exec(QCursor::pos());
  } else {
    m_addAction->setEnabled(true);
    m_removeAction->setDisabled(true);
    m_renameAction->setDisabled(true);
    m_contextMenu->exec(QCursor::pos());
  }
}

void MyListView::currentChanged(const QModelIndex &current,
                                const QModelIndex &previous) {
  QListView::currentChanged(current, previous);

  emit currentIndexChanged(current, previous);
}

/*void MyListView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case value:

        break;
    default:
        break;
    }
}*/

void MyListView::insertNewItem() {
  int row = this->model()->rowCount();

  this->model()->insertRow(row);

  QString schemeName = tr("Nuevo Esquema");

  int cont = 0;

  for (int i = 0; i <= this->model()->rowCount() - 1; ++i) {
    QModelIndex auxIndex = this->model()->index(i, 0, QModelIndex());
    QString auxSchemeName =
        this->model()->data(auxIndex, Qt::DisplayRole).toString();
    if (schemeName == auxSchemeName) {
      ++cont;
      i = 0;
      schemeName = tr("Nuevo Esquema (%1)").arg(cont);
    }
  }

  QModelIndex index = this->model()->index(row, 0, QModelIndex());
  if (index.isValid()) {
    this->model()->setData(index, schemeName);
    this->setCurrentIndex(index);
    this->edit(index);
  }
}

void MyListView::removeItem() {
  QModelIndex index = currentIndex();

  if (index.isValid() && this->model()->rowCount(QModelIndex()) > 1) {
    QString schemeName = this->model()->data(index).toString();
    this->model()->removeRow(index.row());
    emit schemeDeleted(schemeName);
  }
}

void MyListView::editItemName() {
  QModelIndex index = currentIndex();
  if (index.isValid()) {
    this->edit(index);
  }
}

void MyListView::createContextMenu() {
  m_addAction = new QAction(QIcon(":images/add.png"), tr("Agregar"), this);
  connect(m_addAction, SIGNAL(triggered(bool)), this, SLOT(insertNewItem()));

  m_removeAction =
      new QAction(QIcon(":images/erase.png"), tr("Eliminar"), this);
  connect(m_removeAction, SIGNAL(triggered(bool)), this, SLOT(removeItem()));

  m_renameAction = new QAction(tr("Cambiar nombre"), this);
  connect(m_renameAction, SIGNAL(triggered(bool)), this, SLOT(editItemName()));

  m_contextMenu = new QMenu(this);

  m_contextMenu->addAction(m_addAction);
  m_contextMenu->addAction(m_removeAction);
  m_contextMenu->addAction(m_renameAction);
}
