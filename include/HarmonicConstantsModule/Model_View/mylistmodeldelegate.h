#ifndef MYLISTMODELDELEGATE_H
#define MYLISTMODELDELEGATE_H

#include <QStyledItemDelegate>
class QPainter;

class MyListModelDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    MyListModelDelegate(QObject *parent = 0):QStyledItemDelegate(parent){}

    //void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

signals:
    void schemeNameChanged(const QString &oldName, const QString &newName) const;

private slots:
    void commitAndCloseEditor();
};

#endif // MYLISTMODELDELEGATE_H
