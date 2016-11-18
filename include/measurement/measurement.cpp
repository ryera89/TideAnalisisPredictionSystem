#include "measurement.h"



TidesMeasurement::TidesMeasurement(const qreal &seaLevel, const QDate &measurementDate,
                                   const QTime &measurementTime):  m_seaLevel(seaLevel), m_date(measurementDate), m_time(measurementTime){
}

bool TidesMeasurement::isValid() const
{
    return (m_date.isValid() && m_time.isValid());
}


void TidesMeasurement::setSeaLevel(const qreal &value)
{
    if (m_seaLevel == value) return;

    m_seaLevel = value;
}

void TidesMeasurement::setMeasurementDate(const QDate &date)
{
    if (m_date == date) return;

    m_date = date;
}

void TidesMeasurement::setMeasurementTime(const QTime &time)
{
    if (m_time == time) return;

    m_time = time;
}

TidalTimeLevel TidesMeasurement::dateMeasurement() const
{
    return TidalTimeLevel(m_time,m_seaLevel);
}

/*void TidesMeasurement::setLabelDate(const QString &newLabel)
{
    if (m_labelDate == newLabel) return;

    m_labelDate = newLabel;
}

void TidesMeasurement::setLabelTime(const QString &newLabel)
{
    if (m_labelTime == newLabel) return;

    m_labelTime = newLabel;
}

void TidesMeasurement::setLabelSeaLevel(const QString &newLabel)
{
    if (m_labelSeaLevel == newLabel) return;

    m_labelSeaLevel = newLabel;
}

QString TidesMeasurement::labelDate() {return m_labelDate;}
QString TidesMeasurement::labelTime() {return m_labelTime;}
QString TidesMeasurement::labelSeaLevel() {return m_labelSeaLevel;}
uint TidesMeasurement::fieldNumber() {return m_fieldNumber;}

//STATIC MEMBERS DEFINITIONS
uint TidesMeasurement :: m_fieldNumber = 3;
QString TidesMeasurement :: m_labelDate = "Fecha";
QString TidesMeasurement :: m_labelTime = "Hora";
QString TidesMeasurement :: m_labelSeaLevel = "Nivel del Mar";*/



void TidalTimeLevel::setTime(const QTime &time)
{
    if (m_time != time) m_time = time;
}

void TidalTimeLevel::setSeaLevel(const double &level)
{
    m_seaLevel = level;
}
