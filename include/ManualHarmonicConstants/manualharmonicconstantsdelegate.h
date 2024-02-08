#ifndef MANUALHARMONICCONSTANTSDELEGATE_H
#define MANUALHARMONICCONSTANTSDELEGATE_H

#include <QStyledItemDelegate>

class ManualHarmonicConstantsDelegate : public QStyledItemDelegate {
  Q_OBJECT
public:
  ManualHarmonicConstantsDelegate(QObject *parent = 0);

  void paint(QPainter *painter, const QStyleOptionViewItem &option,
             const QModelIndex &index) const;
  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                        const QModelIndex &index) const;

  void setEditorData(QWidget *editor, const QModelIndex &index) const;
  void setModelData(QWidget *editor, QAbstractItemModel *model,
                    const QModelIndex &index) const;

private slots:
  void commitAndCloseAmpEditor();
  void commitAndClosePhaseEditor();
};

#endif // MANUALHARMONICCONSTANTSDELEGATE_H
