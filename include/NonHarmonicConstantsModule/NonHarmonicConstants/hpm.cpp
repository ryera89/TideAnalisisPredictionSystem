#include "hpm.h"
#include <QtMath>


HPM::HPM(const HarmonicConstant &M2, const HarmonicConstant &M4, const HarmonicConstant &M6):
    m_M2(M2), m_M4(M4), m_M6(M6)
{
    calculate();
}


double HPM::shallowWaterInfluence()
{
    double a = 2*m_M4.amplitud()*qSin(qDegreesToRadians(2*m_M2.phase() - m_M4.phase()));

    double b = 3*m_M6.amplitud()*qSin(qDegreesToRadians(3*m_M2.phase() - m_M6.phase()));

    double c = 4*m_M4.amplitud()*qCos(qDegreesToRadians(2*m_M2.phase() - m_M4.phase()));

    double d = m_M2.amplitud() + 9*m_M6.amplitud()*qCos(qDegreesToRadians(3*m_M2.phase() - m_M6.phase()));

    double temp = (a+b)/(c+d);
    double resp = qRadiansToDegrees(qAtan(temp));
    return resp;
}

void HPM::calculate()
{
    if (m_M2.frequency() == 0.0){
        return;
    }
    double v = shallowWaterInfluence();
    double hpm = (m_M2.phase() - v)/m_M2.frequency();

    int hours = qFloor(hpm);

    double min = (hpm - hours)*60;
    int minutes = qFloor(min);

    m_hours = hours;
    m_minutes = minutes;

}
