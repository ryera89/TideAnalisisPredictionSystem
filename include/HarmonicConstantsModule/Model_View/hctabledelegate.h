#ifndef HCTABLEDELEGATE_H
#define HCTABLEDELEGATE_H

#include <QStyledItemDelegate>
class QPainter;

class HCTableDelegate : public QStyledItemDelegate
{
public:
    HCTableDelegate(QObject *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // HCTABLEDELEGATE_H
