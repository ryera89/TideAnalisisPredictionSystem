#include "crecimientomareasemidiurna.h"
#include <QtMath>
CrecimientoMareaSemidiurna::CrecimientoMareaSemidiurna(const HarmonicConstant &M2, const HarmonicConstant &S2):
    m_M2(M2), m_S2(S2)
{
    calculate();
}

void CrecimientoMareaSemidiurna::calculate()
{
    double deltaF = m_S2.phase() - m_M2.phase();
    double t = 0.0;
    if (deltaF <= 180){
        t = 0.984*(deltaF)/24;
    }else{
        t = -0.984*(deltaF)/24;
    }

    m_value = t;
}
