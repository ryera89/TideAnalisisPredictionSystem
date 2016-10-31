#ifndef HARMONICCONSTANTFREQUENCYTABLEDELEGATE_H
#define HARMONICCONSTANTFREQUENCYTABLEDELEGATE_H

#include <QStyledItemDelegate>

class HarmonicConstantFrequencyTableDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    HarmonicConstantFrequencyTableDelegate(QObject *parent = 0):QStyledItemDelegate(parent){}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

private slots:
    void commitAndCloseNameEditor();
    void commitAndCloseFreqEditor();
    void commitAndCloseDescEditor();

private:
    enum field{nameColumn, freqColumn, descColumn}; //Seccion de la tabla.
};

#endif // HARMONICCONSTANTFREQUENCYTABLEDELEGATE_H
