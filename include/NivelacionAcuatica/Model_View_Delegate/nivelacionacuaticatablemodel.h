#ifndef NIVELACIONACUATICATABLEMODEL_H
#define NIVELACIONACUATICATABLEMODEL_H

#include <QAbstractTableModel>
#include "include/measurement/measurement.h"

class NivelacionAcuaticaTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum MetodoDeNivelacion{UnPuestoPermanente, DosPuestosPermantes};

    explicit NivelacionAcuaticaTableModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    //bool insertColumns(int column, int count, const QModelIndex &parent);
    //bool removeColumns(int column, int count, const QModelIndex &parent);

    void setPuestoProvisionalDataSet(const QVector<TidesMeasurement> &puestoProvicionalData);
    void setPuestoPermanente1DataSet(const QVector<TidesMeasurement> &puestoPermanente1Data);
    void setPuestoPermanente2DataSet(const QVector<TidesMeasurement> &puestoPermanente2Data);

    QVector<TidesMeasurement> puestoProvData() const{return m_puestoProvisionalDataSeries;}
    QVector<TidesMeasurement> puestoPerm1Data() const{return m_puestoPermanente1DataSeries;}
    QVector<TidesMeasurement> puestoPerm2Data() const{return m_puestoPermanente2DataSeries;}
    QVector<TidesMeasurement> diffPProvPuestoPerm1() const{return m_diffConPuestoPermanente1DataSeries;}
    QVector<TidesMeasurement> diffPProvPuestoPerm2() const{return m_diffConPuestoPermanente2DataSeries;}

    QVector<QPointF> puestoProvDataForGraph() const;
    QVector<QPointF> puestoPerm1DataForGraph() const;
    QVector<QPointF> puestoPerm2DataForGraph() const;

public slots:
    void setMetododeNivelacion(int index);

private:
    QVector<TidesMeasurement> m_puestoProvisionalDataSeries;
    QVector<TidesMeasurement> m_puestoPermanente1DataSeries;
    QVector<TidesMeasurement> m_puestoPermanente2DataSeries;
    QVector<TidesMeasurement> m_diffConPuestoPermanente1DataSeries;
    QVector<TidesMeasurement> m_diffConPuestoPermanente2DataSeries;

    int m_colCount;
    int m_rowCount;

    QStringList m_headers;

    MetodoDeNivelacion m_metodo;
    void setMetodoDeNivelacion(MetodoDeNivelacion metodo);
};

#endif // NIVELACIONACUATICATABLEMODEL_H
