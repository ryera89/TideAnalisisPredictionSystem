#include "astronomicalmeanlongitudes.h"
#include <QtMath>
#include <iostream>

void AstronomicalMeanLongitudes::determineLongitudesByCartwright()
{
    QDate epochBegin(1899,12,31);

    qint64 daysNumber = epochBegin.daysTo(m_datetime.date());

    double fraction = (m_datetime.time().hour() + m_datetime.time().minute()/60.0)/24.0 - 0.5;

    double d = daysNumber + fraction;

    double T = d/36525.0;

    double T_square = qPow(T,2);

    m_s = 0.751206 + 1336.855231*T - 0.000003*T_square;
    m_h = 0.776935 + 100.002136*T + 0.000001*T_square;
    m_p = 0.928693 + 11.302872*T - 0.000029*T_square;
    m_N = 0.719954 - 5.372617*T + 0.000006*T_square;
    m_Ps = 0.781169 + 0.004775*T + 0.000001*T_square;

    m_s*=360.0;
    m_h*=360.0;
    m_p*=360.0;
    m_N*=360.0;
    m_Ps*=360.0;

    determineAngleModulus(m_s);
    determineAngleModulus(m_h);
    determineAngleModulus(m_p);
    determineAngleModulus(m_N);
    determineAngleModulus(m_Ps);

}

void AstronomicalMeanLongitudes::determineLongitudesByTASK2000()
{
    int IY = m_datetime.date().year() - 1900;

    int IL = qFloor((IY - 1.0)/4.0);

    QDate aux_Date(m_datetime.date().year(),1,1);

    qint64 IDAY = aux_Date.daysTo(m_datetime.date());

    double DL = IL + IDAY - 1.0 + (m_datetime.time().hour() + m_datetime.time().minute()/60.0)/24.0;

    m_s = 277.0247 + 129.38481*IY + 13.17639*DL;
    m_h = 280.1895 - 0.23872*IY + 0.98565*DL;
    m_p = 334.3853 + 40.66249*IY + 0.11140*DL;
    m_N = 259.1568 - 19.32818*IY - 0.05295*DL;
    m_Ps = 281.2209 + 0.017192*IY;

    determineAngleModulus(m_s);
    determineAngleModulus(m_h);
    determineAngleModulus(m_p);
    determineAngleModulus(m_N);
    determineAngleModulus(m_Ps);

    //No esta Implementado para fechas menores de 1900

}

void AstronomicalMeanLongitudes::determineLongitudesBySchureman()
{
    int Y = 0;
    QDate aux_Date(m_datetime.date().year(),1,1);

    qint64 D = aux_Date.daysTo(m_datetime.date());

    int I = 0;

    if (m_datetime.date().year() < 2000){
        I = qFloor(0.25*(m_datetime.date().year() - 1901));
        Y = m_datetime.date().year() - 1900;
    }else{
        I = qFloor(0.25*(m_datetime.date().year() - 2001));
        Y = m_datetime.date().year() - 2000;
    }
    double T = (365.0*Y + D-1 + I)/36526.0;
    double T_square = qPow(T,2);

    m_s = 277.0248 + 481267.8906*T + 0.0011*T_square;
    m_h = 280.1895 + 36000.7689*T + 0.000303*T_square;
    m_p = 334.3853 + 4069.0340*T - 0.0103*T_square;
    m_N = 259.1568 - 1934.142*T - 0.0021*T_square;
    m_Ps = 281.2209 + 1.7192*T + 0.00045*T_square;

    determineAngleModulus(m_s);
    determineAngleModulus(m_h);
    determineAngleModulus(m_p);
    determineAngleModulus(m_N);
    determineAngleModulus(m_Ps);
}

void AstronomicalMeanLongitudes::determineLongitudesByPugh()
{
    QDate epochBegin(2000,1,1);
    qint64 days = epochBegin.daysTo(m_datetime.date());

    double fraction = (m_datetime.time().hour() + m_datetime.time().minute()/60.0)/24.0;

    double T = (days + fraction - 0.5)/36525.0;

    m_s = 218.32 + 481267.88*T;
    m_h = 280.47 + 36000.77*T;
    m_p = 83.35 + 4069.01*T;
    m_N = 125.04 - 1934.14*T;
    m_Ps = 282.94 + 1.72*T;

    determineAngleModulus(m_s);
    determineAngleModulus(m_h);
    determineAngleModulus(m_p);
    determineAngleModulus(m_N);
    determineAngleModulus(m_Ps);

}

void AstronomicalMeanLongitudes::printAstronomicalLongitudesToConsole()
{
    std::cout << "-----Astronomical Longitudes------" << std::endl;
    std::cout << "Mean Moon Longitude [s]: " << m_s << std::endl;
    std::cout << "Mean Sun Longitude [h]: " << m_h << std::endl;
    std::cout << "Lunar Perigee Longitude [p]: " << m_p << std::endl;
    std::cout << "Lunar Ascending Node [N]: " << m_N << std::endl;
    std::cout << "Perihelion Longitude [Ps]: " << m_Ps << std::endl;
}

void AstronomicalMeanLongitudes::determineAngleModulus(double &angle)
{
    if (angle > 360.0){
        angle -= qFloor(angle/360.0)*360.0;
    }
    if (angle < 0.0){
        angle += qCeil(qAbs(angle/360.0))*360.0;
    }
}
