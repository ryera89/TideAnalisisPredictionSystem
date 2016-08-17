#ifndef MEASUREMENT_H
#define MEASUREMENT_H
#include <QCoreApplication>

#include <QDate>
#include <QTime>

class TidalTimeLevel{
private:
    double m_seaLevel;
    QTime m_time;

public:
    TidalTimeLevel(const QTime &time, const double seaLevel):m_time(time),m_seaLevel(seaLevel){}

    void setTime(const QTime &time);
    void setSeaLevel(const double &level);

    QTime time() const {return m_time;}
    double seaLevel() const {return m_seaLevel;}
};

class TidesMeasurement{
private:
    qreal m_seaLevel;    //nivel del mar
    QDate m_date;
    QTime m_time;
public:
    TidesMeasurement(){}
    TidesMeasurement(const qreal &seaLevel,const QDate &measurementDate,
                             const QTime &measurementTime);

    //Write Functions
    void setSeaLevel(const qreal &value);
    void setMeasurementDate(const QDate &date);
    void setMeasurementTime(const QTime &time);

    //Read Functions
    qreal seaLevel() const {return m_seaLevel;}
    QDate measurementDate() const {return m_date;}
    QTime measurementTime() const {return m_time;}

    TidalTimeLevel dateMeasurement() const;
};


inline bool operator ==(const TidesMeasurement &om1, const TidesMeasurement &om2){
    return om1.seaLevel() == om2.seaLevel() && om1.measurementDate() == om2.measurementDate()
            && om1.measurementTime() == om2.measurementTime() ;
}
inline bool operator !=(const TidesMeasurement &om1, const TidesMeasurement &om2){
    return !(om1==om2);
}

#endif // MEASUREMENT_H
