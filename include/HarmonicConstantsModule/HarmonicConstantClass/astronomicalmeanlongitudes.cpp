#include "astronomicalmeanlongitudes.h"
#include <QtMath>
#include <iostream>

AstronomicalMeanLongitudes::AstronomicalMeanLongitudes(const QDateTime &datetime):m_datetime(datetime){
    determineLongitudesBySchureman();
    determineSolarAngle();

}

void AstronomicalMeanLongitudes::setDateTimeForCalc(const QDateTime &datetime)
{
    m_datetime = datetime;

    determineLongitudesBySchureman();
    determineSolarAngle();
}

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


    determineValues_I_v_ep_vprima_2v2prima();
    determineRa();
    determineR();
    determineQa();
    determineQ();

}

void AstronomicalMeanLongitudes::determineLongitudesByTASK2000()
{
    int IY = m_datetime.date().year() - 1900;

    int IL = qFloor((IY - 1.0)/4.0);

    QDate aux_Date(m_datetime.date().year(),1,1);

    qint64 IDAY = aux_Date.daysTo(m_datetime.date());

    double DL = IL + IDAY  + (m_datetime.time().hour() + m_datetime.time().minute()/60.0)/24.0;

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


    determineValues_I_v_ep_vprima_2v2prima();
    determineRa();
    determineR();
    determineQa();
    determineQ();
}

void AstronomicalMeanLongitudes::determineLongitudesBySchureman()
{
    //int Y = 0;
    //QDate aux_Date(m_datetime.date().year(),1,1);

    //qint64 D = aux_Date.daysTo(m_datetime.date());

    //int I = 0;

    //if (m_datetime.date().year() > 2000){
        //I = qFloor(0.25*(m_datetime.date().year() - 1901));
        //Y = m_datetime.date().year() - 1900;
    //}else{
        //I = qFloor(0.25*(m_datetime.date().year() - 2001));
        //Y = m_datetime.date().year() - 2000;
    //}
    QDate epochBegin(1900,1,1);
    //double T = (365.0*Y + D-1 + I)/36526.0;

    double fraction = (m_datetime.time().hour() + m_datetime.time().minute()/60.0)/24.0;

    double T = (epochBegin.daysTo(m_datetime.date()) + 0.5 + fraction)/36525.0;
    double T_square = qPow(T,2.0);
    double T_cubic = qPow(T,3.0);

    m_s = 270.0 + 26.0/60.0 + 14.72/3600.0 + (1336.0*360.0 + 1108411.20/3600.0)*T
            + 9.09/3600.0*T_square + 0.0068/3600.0*T_cubic;

    m_h = 279.0 + 41.0/60.0 + 48.04/3600.0 + 129602768.13/3600.0*T + 1.089/3600.0*T_square;

    m_p = 334.0 + 19.0/60.0 + 40.87/3600.0 + (11.0*360.0 + 392515.94/3600.0)*T - 37.24/3600.0*T_square
            - 0.045/3600.0*T_cubic;

    m_N = 259.0 + 10.0/60.0 + 57.12/3600.0 - (5.0*360.0 + 482912.63/3600.0)*T + 7.58/3600.0*T_square
            + 0.008/3600.0*T_cubic;

    m_Ps = 281.0 + 13.0/60.0 + 15.0/3600.0 + 6189.03/3600.0*T + 1.63/3600.0*T_square + 0.012/3600.0*T_cubic;

    determineAngleModulus(m_s);
    determineAngleModulus(m_h);
    determineAngleModulus(m_p);
    determineAngleModulus(m_N);
    determineAngleModulus(m_Ps);


    determineValues_I_v_ep_vprima_2v2prima();
    determineRa();
    determineR();
    determineQa();
    determineQ();
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

    determineValues_I_v_ep_vprima_2v2prima();
    determineRa();
    determineR();
    determineQa();
    determineQ();

}

void AstronomicalMeanLongitudes::printAstronomicalLongitudesToConsole()
{
    std::cout << "-----Astronomical Longitudes------" << std::endl;
    std::cout << "Date: " << m_datetime.toString("dd/MM/yyyy hh:mm:ss").toStdString() << std::endl;
    std::cout << "Mean Moon Longitude     [s]: " << m_s << std::endl;
    std::cout << "Mean Sun Longitude      [h]: " << m_h << std::endl;
    std::cout << "Lunar Perigee Longitude [p]: " << m_p << std::endl;
    std::cout << "Lunar Ascending Node    [N]: " << m_N << std::endl;
    std::cout << "Perihelion Longitude   [Ps]: " << m_Ps << std::endl;

    std::cout << "        [I]: " << m_I << std::endl;
    std::cout << "        [v]: " << m_v << std::endl;
    std::cout << "       [ep]: " << m_ep << std::endl;
    std::cout << "  [v_prima]: " << m_v_prima << std::endl;
    std::cout << "[2v_2prima]: " << m_2v_2prima << std::endl;

    std::cout << "[Ra]: " << m_Ra << std::endl;
    std::cout << " [R]: " << m_R << std::endl;
    std::cout << "[Qa]: " << m_Qa << std::endl;
    std::cout << " [Q]: " << m_Q << std::endl;

}

void AstronomicalMeanLongitudes::determineValues_I_v_ep_vprima_2v2prima()
{
    determineValues_I();
    determineValues_v_ep();
    determineValues_vprima();
    determineValues_2v2prima();

}

void AstronomicalMeanLongitudes::determineValues_I()
{
    m_I = qRadiansToDegrees(qAcos(0.91370 - 0.03569*qCos(qDegreesToRadians(m_N))));
    //determineAngleModulus(m_I);
}

void AstronomicalMeanLongitudes::determineValues_v_ep()
{
    double num2 = qSin(qDegreesToRadians((w - i)/2.0));
    double den2 = qSin(qDegreesToRadians((w + i)/2.0));

    double num1 = qCos(qDegreesToRadians((w - i)/2.0));
    double den1 = qCos(qDegreesToRadians((w + i)/2.0));
    //double aux1 = num1/den1;
    //double aux2 = num2/den2;
    double factor = qTan(qDegreesToRadians(m_N/2.0));

    double A = qRadiansToDegrees(qAtan((num1/den1)*factor));
    double B = qRadiansToDegrees(qAtan((num2/den2)*factor));

    m_v = A - B;

    //determineAngleModulus(m_v);

    m_ep = m_N - A - B;

    //WARNING: This may be wrong
    if (m_N > 180.0){
        m_ep-=360.0;
    }

    //determineAngleModulus(m_ep);
}

void AstronomicalMeanLongitudes::determineValues_vprima()
{
    double num = qSin(qDegreesToRadians(m_v))*qSin(qDegreesToRadians(2.0*m_I));
    double den = qCos(qDegreesToRadians(m_v))*qSin(qDegreesToRadians(2.0*m_I)) + 0.3347;

    m_v_prima = qRadiansToDegrees(qAtan(num/den));

    //determineAngleModulus(m_v_prima);
}

void AstronomicalMeanLongitudes::determineValues_2v2prima()
{
    double num = qSin(qDegreesToRadians(2*m_v))*qPow(qSin(qDegreesToRadians(m_I)),2.0);
    double den = qCos(qDegreesToRadians(2*m_v))*qPow(qSin(qDegreesToRadians(m_I)),2.0) + 0.0727;

    m_2v_2prima = qRadiansToDegrees(qAtan(num/den));

    //determineAngleModulus(m_2v_2prima);
}

void AstronomicalMeanLongitudes::determineRa()
{
    double P = m_p - m_ep;
    double term1 = 12.0*qPow(qTan(qDegreesToRadians(m_I/2.0)),2.0)*qCos(qDegreesToRadians(2.0*P));
    double term2 = 36.0*qPow(qTan(qDegreesToRadians(m_I/2.0)),4.0);

    double den = 1.0 - term1 + term2;

    m_Ra = 1.0/qSqrt(den);
}

void AstronomicalMeanLongitudes::determineR()
{
    double P = m_p - m_ep;

    double num = 6.0*qSin(qDegreesToRadians(2.0*P));

    double aux = 1.0/qTan(qDegreesToRadians(m_I/2.0));

    double den = qPow(aux,2.0) - 6.0*qCos(qDegreesToRadians(2.0*P));

    m_R = qRadiansToDegrees(qAtan(num/den));

    //determineAngleModulus(m_R);
}

void AstronomicalMeanLongitudes::determineQa()
{
    double term1 = (9.0/2.0)*qPow(qTan(qDegreesToRadians(m_I/2.0)),2.0);
    double term2 = (9.0/4.0)*qPow(qTan(qDegreesToRadians(m_I/2.0)),4.0);
    double term3 = (3.0/2.0)*(1 - qPow(qTan(qDegreesToRadians(m_I/2.0)),2.0))*qCos(qDegreesToRadians(2.0*(m_p - m_ep)));

    double den = (5.0/2.0) - term1 + term2 + term3;

    m_Qa = 1.0/qSqrt(den);

    //double P = m_p - m_ep;

    //double num = qSin(qDegreesToRadians(2*P));

    //double term1 = 3.0*qCos(qDegreesToRadians(m_I))/qPow(qCos(qDegreesToRadians(m_I/2.0)),2);
    //double term2 = qCos(qDegreesToRadians(2*P));
    //double den = term1 + term2;

    //m_Qa = qRadiansToDegrees(qAtan(num/den));
}

void AstronomicalMeanLongitudes::determineQ()
{
    //double num = 2.0 - 3.0*qPow(qTan(qDegreesToRadians(m_I/2.0)),2.0);
    //double den = 4.0 - 3.0*qPow(qTan(qDegreesToRadians(m_I/2.0)),2.0);

    double P = m_p - m_ep;

    double num = 5.0*qCos(qDegreesToRadians(m_I)) - 1;
    double den = 7.0*qCos(qDegreesToRadians(m_I)) + 1;


    double factor = qTan(qDegreesToRadians(P));

    m_Q = qRadiansToDegrees(qAtan((num/den)*factor));

    determineAngleModulus(m_Q);

    if ((m_Q > 270.0 && m_Q < 360.0) && (P > 90.0 && P < 180.0)){
        m_Q -= 180.0;
    }
    if ((m_Q > 0.0 && m_Q < 90.0) && (P > 180.0 && P < 270.0)){
        m_Q += 180.0;
    }
}

void AstronomicalMeanLongitudes::determineSolarAngle()
{
    int hour = m_datetime.time().hour();
    int minutes = m_datetime.time().minute();

    m_solarAngle = (hour*60.0 + minutes - 720.0)/4.0;
    if (hour == 0 && minutes == 0) m_solarAngle = 180.0;
}

void AstronomicalMeanLongitudes::determineAngleModulus(double &angle)
{
    if (angle >= 0.0 && angle <=360.0){ return;
    }else{
        if (angle > 360.0){
            angle -= qFloor(angle/360.0)*360.0;
            return;
        }
        if (angle < 0.0){
            angle += qCeil(qAbs(angle/360.0))*360.0;
            return;
        }
    }
}
