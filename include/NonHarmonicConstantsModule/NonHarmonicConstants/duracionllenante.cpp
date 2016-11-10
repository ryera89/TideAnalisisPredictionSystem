#include "duracionllenante.h"
#include <QtMath>



DuracionLLenante::DuracionLLenante(const HarmonicConstant &M2, const HarmonicConstant &M4, const HarmonicConstant &M6):
    m_M2(M2), m_M4(M4), m_M6(M6)
{
    calculate();
}
double DuracionLLenante::shallowWaterInfluence1()
{
    double a = 2*m_M4.amplitud()*qSin(qDegreesToRadians(2*m_M2.phase() - m_M4.phase()));

    double b = 3*m_M6.amplitud()*qSin(qDegreesToRadians(3*m_M2.phase() - m_M6.phase()));

    double c = 4*m_M4.amplitud()*qCos(qDegreesToRadians(2*m_M2.phase() - m_M4.phase()));

    double d = m_M2.amplitud() + 9*m_M6.amplitud()*qCos(qDegreesToRadians(3*m_M2.phase() - m_M6.phase()));

    double temp = (a+b)/(c+d);
    double resp = qRadiansToDegrees(qAtan(temp));
    return resp;
}

double DuracionLLenante::shallowWaterInfluence2()
{
    double a = 2*m_M4.amplitud()*qSin(qDegreesToRadians(2*m_M2.phase() - m_M4.phase()));

    double b = 3*m_M6.amplitud()*qSin(qDegreesToRadians(3*m_M2.phase() - m_M6.phase()));

    double c = 4*m_M4.amplitud()*qCos(qDegreesToRadians(2*m_M2.phase() - m_M4.phase()));

    double d = m_M2.amplitud() + 9*m_M6.amplitud()*qCos(qDegreesToRadians(3*m_M2.phase() - m_M6.phase()));

    double temp = (a-b)/(c-d);
    double resp = qRadiansToDegrees(qAtan(temp));
    return resp;
}

void DuracionLLenante::calculate()
{
    if (m_M2.frequency() == 0.0){
        return;
    }

    double v = shallowWaterInfluence1();
    double w = shallowWaterInfluence2();

    double Tv = (180 - (v - w))/m_M2.frequency();

    int hours = qFloor(Tv);

    double min = (Tv - hours)*60;
    int minutes = qFloor(min);

    m_hours = hours;
    m_minutes = minutes;
}
