#ifndef TIDALTABLEDELEGATE_H
#define TIDALTABLEDELEGATE_H

#include <QStyledItemDelegate>
class QPainter;


class TidalTableDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    TidalTableDelegate(QObject *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

private slots:
    void commitAndCloseDateEditor();
    void commitAndCloseTimeEditor();
    void commitAndCloseLevelEditor();
private:
    enum field{dateColumn, timeColumn, levelColumn}; //Seccion de la tabla.



};

#endif // TIDALTABLEDELEGATE_H
