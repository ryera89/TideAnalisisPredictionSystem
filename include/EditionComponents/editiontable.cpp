#include "editiontable.h"
#include "myheader.h"

#include <QAction>
#include <QContextMenuEvent>
#include <QKeyEvent>
#include <QMenu>

EditionTable::EditionTable(QWidget *parent) : QTableView(parent) {

  createContextMenu();
  MyHeader *verHeader = new MyHeader(Qt::Vertical, this);
  connect(verHeader, SIGNAL(removeRowActionTriggered(bool)), this,
          SLOT(removeRows()));
  connect(verHeader, SIGNAL(insertRowActionTriggered(bool)), this,
          SLOT(insertRow()));
  this->setVerticalHeader(verHeader);
  this->setSelectionMode(QAbstractItemView::ContiguousSelection);

  connect(m_removeRowAction, SIGNAL(triggered(bool)), this, SLOT(removeRows()));
  connect(m_insertRowAction, SIGNAL(triggered(bool)), this, SLOT(insertRow()));
}

bool EditionTable::removeRows() {
  QModelIndexList indexes = selectedIndexes();
  if (indexes.size() > 0) {
    int row = indexes.at(0).row();
    int cont = indexes.last().row() - row;
    // this->model()->removeRows(row,cont);

    emit rowsRemoved(row, cont);
    return true;
  }
  return false;
}

void EditionTable::insertRow() {
  QModelIndex index = currentIndex();

  if (index.isValid())
    this->model()->insertRow(index.row());
  else
    emit rowInserted();
}

void EditionTable::contextMenuEvent(QContextMenuEvent *event) {
  Q_UNUSED(event);
  m_contextMenu->exec(QCursor::pos());
}

void EditionTable::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
  case Qt::Key_Return: {
    QModelIndex index = currentIndex();
    if (index.isValid() && (index.row() + 1) < this->model()->rowCount()) {
      QModelIndex nextIndex =
          this->model()->index(index.row() + 1, index.column());
      this->setCurrentIndex(nextIndex);
    }
    break;
  }
  case Qt::Key_Enter: {
    QModelIndex index = currentIndex();
    if (index.isValid() && (index.row() + 1) < this->model()->rowCount()) {
      QModelIndex nextIndex =
          this->model()->index(index.row() + 1, index.column());
      this->setCurrentIndex(nextIndex);
    }
    break;
  }
  default:
    QTableView::keyPressEvent(event);
    break;
  }
}

void EditionTable::createContextMenu() {
  m_contextMenu = new QMenu;

  m_removeRowAction =
      new QAction(QIcon(":images/table_row_delete.png"), tr("Eliminar fila"));
  m_insertRowAction =
      new QAction(QIcon(":images/table_row_new.png"), tr("Insertar fila"));

  m_contextMenu->addAction(m_insertRowAction);
  m_contextMenu->addAction(m_removeRowAction);
}
