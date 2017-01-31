#include "tidaldata.h"
//#include <QHash>
//#include <QVector>
//#include <QPointF>

TidalData::TidalData(const QVector<TidesMeasurement> &measurements)
{
    m_measurements = measurements;

    findMeasurementDates();
    settingUpData();
}

void TidalData::setDataSource(const QVector<TidesMeasurement> &measurement)
{
    m_measurements = measurement;

    m_measurementDates.clear();

    m_dateSums.clear();
    m_meanSeaLevel.clear();
    m_extremes.clear();
    m_differences.clear();
    m_measurementNumberPerDay.clear();

    findMeasurementDates();
    settingUpData();
}

void TidalData::findMeasurementDates()
{
    QDate date = m_measurements.at(0).measurementDate();
    m_measurementDates.push_back(date);
    for (int i = 1; i < m_measurements.size(); ++i){
        QDate aux = m_measurements.at(i).measurementDate();
        if (aux != date){
            date = aux;
            m_measurementDates.push_back(date);
        }
    }
}

//Para data ordenada cronologicamnete
//WARNING: puede exitir un Bug en el break;
void TidalData::settingUpData()
{
    int aux = 0;

    maxMeasurementNumberPerDay = 0;


    m_minimo = m_measurements[0];
    m_maximo = m_measurements[0];

    for (int k = 0; k < m_measurementDates.size(); ++k){
        double suma = 0.0;
        int measurementNumber = 0;
        double max = m_measurements.at(aux).seaLevel();
        double min = m_measurements.at(aux).seaLevel();

        //m_minimo.setSeaLevel(min);
        //m_maximo.setSeaLevel(max);

        for (int i = aux; i < m_measurements.size(); ++i){

            double maximo = m_measurements.at(i).seaLevel();
            double minimo = m_measurements.at(i).seaLevel();

            if (maximo > m_maximo.seaLevel()){
                m_maximo.setSeaLevel(maximo);
                m_maximo.setMeasurementDate(m_measurements.at(i).measurementDate());
                m_maximo.setMeasurementTime(m_measurements.at(i).measurementTime());
            }
            if (minimo < m_minimo.seaLevel()){
                m_minimo.setSeaLevel(minimo);
                m_minimo.setMeasurementDate(m_measurements.at(i).measurementDate());
                m_minimo.setMeasurementTime(m_measurements.at(i).measurementTime());
            }


            if (m_measurementDates.at(k) == m_measurements.at(i).measurementDate()){
                double comp = m_measurements.at(i).seaLevel();
                suma += m_measurements.at(i).seaLevel();
                if (comp < min) min = comp;
                if (comp > max) max = comp;

                ++aux;
                ++measurementNumber;

                if (measurementNumber > maxMeasurementNumberPerDay) maxMeasurementNumberPerDay = measurementNumber;
            }else break;
        }
        QDate date1 = m_measurementDates.at(k);

        //QHash<QDate,QPointF> extreme;
        //extreme[date1] = QPointF(max,min);
        m_extremes[date1] = QPointF(max,min);

        //QHash<QDate,double> hash;
        //hash[date1] = max - min;
        m_differences[date1] = max - min;

        //hash[date1] = suma;
        m_dateSums[date1] = suma;

        //hash[date1] = suma/(aux + 1);
        m_meanSeaLevel[date1] = suma/measurementNumber;

        //QHash<QDate,int> hash1;
        //hash1[date1] = measurementNumber;
        m_measurementNumberPerDay[date1] = measurementNumber;
    }
}

