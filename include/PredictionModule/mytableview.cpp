#include "mytableview.h"

MyTableView::MyTableView(QWidget *parent) : QTableView(parent) {}

void MyTableView::setRowSelection(const int &column0, const int &row0,
                                  const int &columnf, const int &rowf,
                                  QItemSelectionModel::SelectionFlag flag) {
  int y0 = rowViewportPosition(row0);
  int x0 = columnViewportPosition(column0);

  int yf = rowViewportPosition(rowf);
  int xf = columnViewportPosition(columnf);

  QRect rect(QPoint(x0, y0), QPoint(xf, yf));

  setSelection(rect, flag);

  QModelIndex index = indexAt(QPoint(x0, y0));
  scrollTo(index, QAbstractItemView::PositionAtTop);
}

void MyTableView::keyPressEvent(QKeyEvent *event) {
  QTableView::keyPressEvent(event);

  QModelIndexList indexList = selectedIndexes();

  if (!indexList.isEmpty()) {
    if (m_modelIndexesList.isEmpty()) {
      int row0 = indexList.first().row();
      int rowf = indexList.last().row();

      m_modelIndexesList = indexList;

      emit rowsSelected(row0, rowf);
    } else {
      if (m_modelIndexesList.first() != indexList.last() ||
          m_modelIndexesList.last() != indexList.last()) {
        int row0 = indexList.first().row();
        int rowf = indexList.last().row();

        m_modelIndexesList = indexList;

        emit rowsSelected(row0, rowf);
      }
    }
  } else {
    m_modelIndexesList = indexList;

    emit noRowsSelected();
  }

  if (event->key() == Qt::Key_Delete)
    emit deleteKeyPressed();
}

void MyTableView::mouseReleaseEvent(QMouseEvent *event) {
  QTableView::mouseReleaseEvent(event);

  QModelIndexList indexList = selectedIndexes();

  if (!indexList.isEmpty()) {
    if (m_modelIndexesList.isEmpty()) {
      int row0 = indexList.first().row();
      int rowf = indexList.last().row();

      m_modelIndexesList = indexList;

      emit rowsSelected(row0, rowf);
    } else {
      if (m_modelIndexesList.first() != indexList.last() ||
          m_modelIndexesList.last() != indexList.last()) {
        int row0 = indexList.first().row();
        int rowf = indexList.last().row();

        m_modelIndexesList = indexList;

        emit rowsSelected(row0, rowf);
      }
    }
  } else {
    m_modelIndexesList = indexList;

    emit noRowsSelected();
  }
}
