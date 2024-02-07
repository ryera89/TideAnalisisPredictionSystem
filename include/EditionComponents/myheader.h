#ifndef MYHEADER_H
#define MYHEADER_H

#include <QHeaderView>
class QMenu;
class QAction;
class QContextMenuEvent;

class MyHeader : public QHeaderView {
  Q_OBJECT
public:
  MyHeader(Qt::Orientation orientation, QWidget *parent = 0);

signals:
  void removeRowActionTriggered(bool);
  void insertRowActionTriggered(bool);

protected:
  void contextMenuEvent(QContextMenuEvent *event);
  void mousePressEvent(QMouseEvent *event);

private:
  QMenu *m_contextMenu;

  QAction *m_removeRowAction;
  QAction *m_insertRowAction;

  void createContextMenu();
};

#endif // MYHEADER_H
