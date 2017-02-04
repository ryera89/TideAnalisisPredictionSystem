#include "nivelacionacuaticatablemodel.h"
#include <QPointF>

NivelacionAcuaticaTableModel::NivelacionAcuaticaTableModel(QObject *parent):QAbstractTableModel(parent)
{
    m_headers << "Fecha" << "Hora" << "Nivel[m]\nP.Prov" << "Nivel[m]\nP.Perm" << "DIFF[m]\nP.Prov - P.Perm"
              << "DIFF[m]\nP.Prov - P.Perm1" << "DIFF[m]\nP.Prov - P.Perm2";

    m_colCount = 5;
    m_rowCount = m_puestoProvisionalDataSeries.size();

    setMetododeNivelacion(UnPuestoPermanente);
}

int NivelacionAcuaticaTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_rowCount;
}

int NivelacionAcuaticaTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_colCount;
}

QVariant NivelacionAcuaticaTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();

    if (role == Qt::TextAlignmentRole){
        return int(Qt::AlignVCenter | Qt::AlignRight);
    }else{
        if (role == Qt::DisplayRole){
            int row = index.row();
            switch (index.column()) {
            case 0:
                return m_puestoProvisionalDataSeries.at(row).measurementDate();
                break;
            case 1:
                return m_puestoProvisionalDataSeries.at(row).measurementTime();
                break;
            case 2:
                return m_puestoProvisionalDataSeries.at(row).seaLevel();
                break;
            case 3:
                return m_puestoPermanente1DataSeries.at(row).seaLevel();
                break;
            case 4:{
                if (m_metodo == UnPuestoPermanente) return m_diffConPuestoPermanente1DataSeries.at(row).seaLevel();
                else return m_puestoPermanente2DataSeries.at(row).seaLevel();
                break;
            }
            case 5:
                return m_diffConPuestoPermanente1DataSeries.at(row).seaLevel();
                break;
            case 6:
                return m_diffConPuestoPermanente2DataSeries.at(row).seaLevel();
                break;
            default:
                return QVariant();
                break;
            }
        }
    }
    return QVariant();
}

QVariant NivelacionAcuaticaTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole){
        if (orientation == Qt::Horizontal) return m_headers[section];
        if (orientation == Qt::Vertical) return section + 1;
    }
    return QVariant();
}

void NivelacionAcuaticaTableModel::setPuestoProvisionalDataSet(const QVector<TidesMeasurement> &puestoProvicionalData)
{
    beginResetModel();
    m_rowCount = puestoProvicionalData.size();
    m_puestoProvisionalDataSeries = puestoProvicionalData;
    m_puestoPermanente1DataSeries.resize(m_puestoProvisionalDataSeries.size());
    m_puestoPermanente2DataSeries.resize(m_puestoProvisionalDataSeries.size());
    m_diffConPuestoPermanente1DataSeries.resize(m_puestoProvisionalDataSeries.size());
    m_diffConPuestoPermanente2DataSeries.resize(m_puestoProvisionalDataSeries.size());
    for (int i = 0; i < m_puestoProvisionalDataSeries.size(); ++i){
        m_diffConPuestoPermanente1DataSeries[i] = m_puestoProvisionalDataSeries.at(i) - m_puestoPermanente1DataSeries.at(i);
        m_diffConPuestoPermanente2DataSeries[i] = m_puestoProvisionalDataSeries.at(i) - m_puestoPermanente2DataSeries.at(i);
    }
    endResetModel();

}

void NivelacionAcuaticaTableModel::setPuestoPermanente1DataSet(const QVector<TidesMeasurement> &puestoPermanente1Data)
{
    beginResetModel();
    m_rowCount = puestoPermanente1Data.size();
    m_puestoPermanente1DataSeries = puestoPermanente1Data;
    m_puestoProvisionalDataSeries.resize(m_puestoPermanente1DataSeries.size());
    m_puestoPermanente2DataSeries.resize(m_puestoPermanente1DataSeries.size());
    m_diffConPuestoPermanente1DataSeries.resize(m_puestoProvisionalDataSeries.size());
    m_diffConPuestoPermanente2DataSeries.resize(m_puestoProvisionalDataSeries.size());
    for (int i = 0; i < m_puestoProvisionalDataSeries.size(); ++i){
        m_diffConPuestoPermanente1DataSeries[i] = m_puestoProvisionalDataSeries.at(i) - m_puestoPermanente1DataSeries.at(i);
        //m_diffConPuestoPermanente2DataSeries[i] = m_puestoProvisionalDataSeries.at(i) - m_puestoPermanente2DataSeries.at(i);
    }
    endResetModel();
}

void NivelacionAcuaticaTableModel::setPuestoPermanente2DataSet(const QVector<TidesMeasurement> &puestoPermanente2Data)
{
    beginResetModel();
    m_rowCount = puestoPermanente2Data.size();
    m_puestoPermanente2DataSeries = puestoPermanente2Data;
    m_puestoProvisionalDataSeries.resize(m_puestoPermanente2DataSeries.size());
    m_puestoPermanente1DataSeries.resize(m_puestoPermanente2DataSeries.size());
    m_diffConPuestoPermanente1DataSeries.resize(m_puestoProvisionalDataSeries.size());
    m_diffConPuestoPermanente2DataSeries.resize(m_puestoProvisionalDataSeries.size());
    for (int i = 0; i < m_puestoProvisionalDataSeries.size(); ++i){
        //m_diffConPuestoPermanente1DataSeries[i] = m_puestoProvisionalDataSeries.at(i) - m_puestoPermanente1DataSeries.at(i);
        m_diffConPuestoPermanente2DataSeries[i] = m_puestoProvisionalDataSeries.at(i) - m_puestoPermanente2DataSeries.at(i);
    }
    endResetModel();
}

QVector<QPointF> NivelacionAcuaticaTableModel::puestoProvDataForGraph() const
{
    QVector<QPointF> data;

    foreach (const TidesMeasurement &measurement, m_puestoProvisionalDataSeries) {
        QDateTime dateTime = measurement.measurementDateTime();
        qreal y = measurement.seaLevel();
        qreal x = dateTime.toMSecsSinceEpoch();

        data.append(QPointF(x,y));
    }
    return data;
}

QVector<QPointF> NivelacionAcuaticaTableModel::puestoPerm1DataForGraph() const
{
    QVector<QPointF> data;

    foreach (const TidesMeasurement &measurement, m_puestoPermanente1DataSeries) {
        QDateTime dateTime = measurement.measurementDateTime();
        qreal y = measurement.seaLevel();
        qreal x = dateTime.toMSecsSinceEpoch();

        data.append(QPointF(x,y));
    }
    return data;
}

QVector<QPointF> NivelacionAcuaticaTableModel::puestoPerm2DataForGraph() const
{
    QVector<QPointF> data;

    foreach (const TidesMeasurement &measurement, m_puestoPermanente2DataSeries) {
        QDateTime dateTime = measurement.measurementDateTime();
        qreal y = measurement.seaLevel();
        qreal x = dateTime.toMSecsSinceEpoch();

        data.append(QPointF(x,y));
    }
    return data;
}


void NivelacionAcuaticaTableModel::setMetododeNivelacion(int index)
{
    switch (index) {
    case 0:
        setMetodoDeNivelacion(UnPuestoPermanente);
        break;
    case 1:
        setMetodoDeNivelacion(DosPuestosPermantes);
        break;
    default:
        setMetodoDeNivelacion(UnPuestoPermanente);
        break;
    }
}

void NivelacionAcuaticaTableModel::setMetodoDeNivelacion(NivelacionAcuaticaTableModel::MetodoDeNivelacion metodo)
{
    if (m_metodo != metodo){
        m_metodo = metodo;

        if (m_metodo == UnPuestoPermanente){
            m_colCount = 5;
            m_headers[3] = "Nivel [m]\n"
                           "P.Perm";
            m_headers[4] = "DIFF [m]\n"
                           "P.Prov - P.Perm";
            beginRemoveColumns(QModelIndex(),5,6);
            endRemoveColumns();
        }
        if (m_metodo == DosPuestosPermantes){
            m_colCount = 7;
            m_headers[3] = "Nivel[m]\n"
                           "P.Perm1";
            m_headers[4] = "Nivel[m]\n"
                           "P.Perm2";
            beginInsertColumns(QModelIndex(),5,6);
            endInsertColumns();
        }
    }
}
