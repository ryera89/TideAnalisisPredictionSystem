#ifndef ASTRONOMICALMEANLONGITUDES_H
#define ASTRONOMICALMEANLONGITUDES_H

#include <QDateTime>

class AstronomicalMeanLongitudes
{
public:
    explicit AstronomicalMeanLongitudes(const QDateTime &datetime):m_datetime(datetime){determineLongitudesByTASK2000();}

    double moonLongitude() const{return m_s;}
    double sunLongitude() const{return m_h;}
    double lunarPerigeeLongitude() const{return m_p;}
    double lunarAscendingNodeLongitude() const{return m_N;}
    double perihlionLongitude() const{return m_Ps;}

    void determineLongitudesByCartwright();
    void determineLongitudesByTASK2000();
    void determineLongitudesBySchureman();
    void determineLongitudesByPugh();

    void printAstronomicalLongitudesToConsole();

private:
    QDateTime m_datetime; //Date for the calculus of the astronimical mean longitudes

    double m_s; //Mean Moon Longitude
    double m_h; //Mean Sun Longitude
    double m_p; //Lunar Perigee Longitude
    double m_N; //Lunar Ascending Node Longitude
    double m_Ps; //Perihelion Longitude

    void determineAngleModulus(double &angle);
};

#endif // ASTRONOMICALMEANLONGITUDES_H
