#ifndef TIDALDATA_H
#define TIDALDATA_H

#include <QObject>
#include "measurement.h"


#include <QVector>
#include <QHash>
#include <QPointF>
//#include <QMap>

class TidalData
{
public:
    explicit TidalData(){}
    TidalData(const QVector<TidesMeasurement> &measurements);

    QVector<TidesMeasurement> m_measurements;
    QVector<QDate> m_measurementDates;

    QHash<QDate,double> m_dateSums;
    QHash<QDate,double> m_meanSeaLevel;
    QHash<QDate,QPointF> m_extremes;
    QHash<QDate,double> m_differences;

    TidesMeasurement m_minimo; //Variable que guarda la minima medicion
    TidesMeasurement m_maximo; //VAriable que guarda la maxima medicion

    QHash<QDate,int> m_measurementNumberPerDay;
    int maxMeasurementNumberPerDay;

    void setDataSource(const QVector<TidesMeasurement> &measurement);
    //QVector<TidesMeasurement> data() const {return m_measurements;}


private:
    void findMeasurementDates();
    void settingUpData();

    //void findTimeMean();

    //void findMaxMeasurement();
    //void findMinMeasurement();


    //QVector<QTime> m_measurementTimes;



    //QVector<QHash<QTime,double>> m_timeSums;
    //QVector<QHash<QTime,double>> m_timeMean;


};

#endif // TIDALDATA_H
