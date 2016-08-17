#ifndef READONLYTABLEMODEL_H
#define READONLYTABLEMODEL_H

#include <QAbstractTableModel>
#include <include/measurement/tidaldata.h>

class ReadOnlyTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    ReadOnlyTableModel(TidalData *data, QObject *parent = 0): QAbstractTableModel(parent){
        headers << "Fecha" << "Hora" << "Nivel del Mar";
        m_data = data;
        //setDataSource(data->m_measurements);
    }


    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    void setDataSource(const QVector<TidesMeasurement> &measurement);

private:
    TidalData *m_data;
    QStringList headers;
};

#endif // READONLYTABLEMODEL_H
