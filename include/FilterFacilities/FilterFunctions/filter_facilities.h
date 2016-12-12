#ifndef FILTER_FACILITIES_H
#define FILTER_FACILITIES_H
#include <QtCore>
#include "include/measurement/measurement.h"
#include <QObject>
//Glitch Filter
class Filters : public QObject{
    Q_OBJECT
public:
    Filters(QObject *parent = Q_NULLPTR):QObject(parent){}

    enum ByValue{LESS, EQUAL, GREATER, LESS_EQUAL, GREATER_EQUAL}; //Enum para el filtro valueFilter

    QVector<int> glitchFilter(qreal glitchValue, const QVector<TidesMeasurement> &data); //Retorna un vector con las posiciones de los datos encontrados
    QVector<int> blocksFilter(int flag, const QVector<TidesMeasurement> &data); //Retorna un vector con la posicion de los bloques
    QVector<int> valueFilter(qreal value, const QVector<TidesMeasurement> &data, Filters::ByValue criteria);
signals:
    void matchesFound(int matches);
    void filterProgress(int progress);

};





#endif // FILTER_FACILITIES_H
