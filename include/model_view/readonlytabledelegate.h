#ifndef READONLYTABLEDELEGATE_H
#define READONLYTABLEDELEGATE_H

#include <QStyledItemDelegate>
class QPainter;

class ReadOnlyTableDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    ReadOnlyTableDelegate(QObject *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    enum field{dateColumn, timeColumn, levelColumn}; //Seccion de la tabla.
};

#endif // READONLYTABLEDELEGATE_H
