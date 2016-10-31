#ifndef READONLYTABLEMODEL_H
#define READONLYTABLEMODEL_H

#include <QAbstractTableModel>
#include <include/measurement/tidaldata.h>

class ReadOnlyTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    ReadOnlyTableModel(QObject *parent = 0): QAbstractTableModel(parent){
        headers << "Fecha" << "Hora" << "Nivel del Mar";
        m_data = QVector<TidesMeasurement>(100);
    }

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    void setMeasurements(const QVector<TidesMeasurement> &measurement);

    QVector<TidesMeasurement> measurementData() const{return m_data;}

private:
    QVector<TidesMeasurement> m_data;
    QStringList headers;
};

#endif // READONLYTABLEMODEL_H
