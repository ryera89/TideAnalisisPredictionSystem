#ifndef MYTABLEVIEW_H
#define MYTABLEVIEW_H

#include <QKeyEvent>
#include <QMouseEvent>
#include <QTableView>
class MyTableView : public QTableView {
  Q_OBJECT
public:
  MyTableView(QWidget *parent = 0);

  void setRowSelection(const int &column0, const int &row0, const int &columnf,
                       const int &rowf,
                       QItemSelectionModel::SelectionFlag flag);

signals:
  void rowsSelected(int row0, int rowf);
  void noRowsSelected();
  void deleteKeyPressed();

protected:
  void keyPressEvent(QKeyEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);

private:
  QModelIndexList m_modelIndexesList;
};

#endif // MYTABLEVIEW_H
