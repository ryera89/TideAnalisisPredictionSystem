#ifndef TABLEMODEL_H
#define TABLEMODEL_H


#include <QAbstractTableModel>
#include "include/measurement/measurement.h"
#include <QVector>
#include <QModelIndex>


class TableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    TableModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;


    //Para habilitar edicion
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;  //debe retornar Qt::ItemIsEditable

    //Deben estar conectados a la vista
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool insertRow(int row, const QModelIndex &parent);
    //bool insertColumns(int column, int count, const QModelIndex &parent);
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool removeRow(int row, const QModelIndex &parent);
    //bool removeColumns(int column, int count, const QModelIndex &parent);

    //Para importar y salvar los datos
    bool importData();  //Proyecto Nuevo usando el dialogo de carga
    //bool loadData(const QString &fileName); //Proyecto ya creado y guardado
    //bool saveData(const QString &fileName); //Al momento de Salvar el proyecto


    void setMeasurements(const QVector<TidesMeasurement> &measurement);

    QVector<TidesMeasurement> measurementData() const{return measurements;}

private:
    QVector<TidesMeasurement> measurements;
    QStringList headers;
};

#endif // TABLEMODEL_H
