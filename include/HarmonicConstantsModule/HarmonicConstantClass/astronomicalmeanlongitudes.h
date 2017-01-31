#ifndef ASTRONOMICALMEANLONGITUDES_H
#define ASTRONOMICALMEANLONGITUDES_H

#include <QDateTime>

class AstronomicalMeanLongitudes
{
public:
    explicit AstronomicalMeanLongitudes(const QDateTime &datetime);

    void setDateTimeForCalc(const QDateTime &datetime);
    QDateTime dateTimeOfCalc() const {return m_datetime;}

    double moonLongitude() const{return m_s;}
    double sunLongitude() const{return m_h;}
    double lunarPerigeeLongitude() const{return m_p;}
    double lunarAscendingNodeLongitude() const{return m_N;}
    double perihlionLongitude() const{return m_Ps;}

    double I() const{return m_I;}
    double v() const{return m_v;}
    double ep() const{return m_ep;}
    double vPrima() const{return m_v_prima;}
    double v2Prima() const{return m_2v_2prima;}

    double Ra() const {return m_Ra;}
    double R() const {return m_R;}
    double Qa() const {return m_Qa;}
    double Q() const {return m_Q;}

    double solarHourAngle() const{return m_solarAngle;}

    void determineLongitudesByCartwright();
    void determineLongitudesByTASK2000();
    void determineLongitudesBySchureman();
    void determineLongitudesByPugh();

    void printAstronomicalLongitudesToConsole();

private:
    static constexpr double w = 23.4525481844151;
    static constexpr double i = 5.145601054748851;

    QDateTime m_datetime; //Date for the calculus of the astronimical mean longitudes

    double m_s; //Mean Moon Longitude
    double m_h; //Mean Sun Longitude
    double m_p; //Lunar Perigee Longitude
    double m_N; //Lunar Ascending Node Longitude
    double m_Ps; //Perihelion Longitude

    //Parametros para determinar los factores nodales de correccion de las constantes armonicas
    double m_I;
    double m_v;
    double m_ep;
    double m_v_prima;
    double m_2v_2prima;

    //Valores de R, Ra Q y Qa para los componentes L2 y M1
    double m_R;
    double m_Ra;
    double m_Q;
    double m_Qa;

    //solar angle
    double m_solarAngle;

    void determineValues_I_v_ep_vprima_2v2prima();

    void determineValues_I();
    void determineValues_v_ep();
    void determineValues_vprima();
    void determineValues_2v2prima();

    void determineRa();
    void determineR();
    void determineQa();
    void determineQ();

    void determineSolarAngle();

    void determineAngleModulus(double &angle);
};

#endif // ASTRONOMICALMEANLONGITUDES_H
