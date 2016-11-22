#include "horacotidianasemidiurna.h"
#include <QtMath>


HoraCotidianaSemidiurna::HoraCotidianaSemidiurna(const HarmonicConstant &M2, const HarmonicConstant &M4, const HarmonicConstant &M6,
                                                 const double &longitud):
    m_M2(M2), m_M4(M4), m_M6(M6), m_longitud(longitud)
{
    calculate();
}

double HoraCotidianaSemidiurna::shallowWaterInfluence1()
{
    double a = 2*m_M4.amplitud()*qSin(qDegreesToRadians(2*m_M2.phase() - m_M4.phase()));

    double b = 3*m_M6.amplitud()*qSin(qDegreesToRadians(3*m_M2.phase() - m_M6.phase()));

    double c = 4*m_M4.amplitud()*qCos(qDegreesToRadians(2*m_M2.phase() - m_M4.phase()));

    double d = m_M2.amplitud() + 9*m_M6.amplitud()*qCos(qDegreesToRadians(3*m_M2.phase() - m_M6.phase()));

    double temp = (a+b)/(c+d);
    double resp = qRadiansToDegrees(qAtan(temp));
    return resp;
}

double HoraCotidianaSemidiurna::shallowWaterInfluence2()
{
    double a = 2*m_M4.amplitud()*qSin(qDegreesToRadians(2*m_M2.phase() - m_M4.phase()));

    double b = 3*m_M6.amplitud()*qSin(qDegreesToRadians(3*m_M2.phase() - m_M6.phase()));

    double c = 4*m_M4.amplitud()*qCos(qDegreesToRadians(2*m_M2.phase() - m_M4.phase()));

    double d = m_M2.amplitud() + 9*m_M6.amplitud()*qCos(qDegreesToRadians(3*m_M2.phase() - m_M6.phase()));

    double temp = (a-b)/(c-d);
    double resp = qRadiansToDegrees(qAtan(temp));
    return resp;
}

void HoraCotidianaSemidiurna::calculate()
{
    double v = shallowWaterInfluence1();
    double w = shallowWaterInfluence2();

    double hcs = (m_M2.phase() - 2*m_longitud - (v+w)/2)/30;

    if (hcs > 12.0) hcs-=12.0;
    if (hcs < 0) hcs+=12.0;

    m_value = hcs;
}
