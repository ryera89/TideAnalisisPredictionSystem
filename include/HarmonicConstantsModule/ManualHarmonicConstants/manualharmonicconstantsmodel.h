#ifndef MANUALHARMONICCONSTANTSMODEL_H
#define MANUALHARMONICCONSTANTSMODEL_H

#include <QAbstractTableModel>
#include "include/HarmonicConstantsModule/HarmonicConstantClass/harmonicconstant.h"
class ManualHarmonicConstantsModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    ManualHarmonicConstantsModel(QObject *parent = 0);
    ManualHarmonicConstantsModel(const QVector<HarmonicConstant> &datos, QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;  //debe retornar Qt::ItemIsEditable

    QVector<HarmonicConstant> allData() const;
    void setAllData(const QVector<HarmonicConstant> &datos);

private:
    QVector<HarmonicConstant> m_data;
    QStringList m_headers;

};

#endif // MANUALHARMONICCONSTANTSMODEL_H
