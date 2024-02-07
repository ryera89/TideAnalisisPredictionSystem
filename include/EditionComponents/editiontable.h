#ifndef EDITIONTABLE_H
#define EDITIONTABLE_H

#include <QTableView>

class QContextMenuEvent;
class QMenu;
class QAction;

class EditionTable : public QTableView {
  Q_OBJECT
public:
  EditionTable(QWidget *parent = 0);

signals:
  void rowsRemoved(int row, int cont);
  void rowInserted();

public slots:
  bool removeRows();
  void insertRow();

protected:
  void contextMenuEvent(QContextMenuEvent *event);
  void keyPressEvent(QKeyEvent *event);

private:
  QMenu *m_contextMenu;

  QAction *m_removeRowAction;
  QAction *m_insertRowAction;

  void createContextMenu();
};

#endif // EDITIONTABLE_H
