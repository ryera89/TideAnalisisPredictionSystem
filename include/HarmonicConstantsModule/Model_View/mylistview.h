#ifndef MYLISTVIEW_H
#define MYLISTVIEW_H

#include <QListView>

class QMenu;
class QAction;

class MyListView : public QListView {
  Q_OBJECT
public:
  MyListView(QWidget *parent);

protected:
  void contextMenuEvent(QContextMenuEvent *event);
  void currentChanged(const QModelIndex &current, const QModelIndex &previous);
  // void keyPressEvent(QKeyEvent *event);

signals:
  void currentIndexChanged(
      const QModelIndex &current,
      const QModelIndex
          &previous); // signal to notify that the current index has changed
  void schemeDeleted(const QString &schemeName);

public slots:
  void editItemName();
  void insertNewItem();
  void removeItem();

private:
  QAction *m_addAction;
  QAction *m_removeAction;
  QAction *m_renameAction;

  QMenu *m_contextMenu;

  void createContextMenu();
};

#endif // MYLISTVIEW_H
