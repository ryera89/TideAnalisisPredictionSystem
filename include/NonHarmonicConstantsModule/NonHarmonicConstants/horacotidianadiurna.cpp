#include "horacotidianadiurna.h"
#include <QtMath>


HoraCotidianaDiurna::HoraCotidianaDiurna(const HarmonicConstant &K1, const HarmonicConstant &O1,
                                         const double &longitud):
    m_K1(K1), m_O1(O1), m_longitud(longitud)
{
    calculate();
}

void HoraCotidianaDiurna::calculate()
{
    double hcd = (m_K1.phase() + m_O1.phase() + 2*m_longitud)/30.0;

    if (qFabs(m_K1.phase() - m_O1.phase()) > 180.0){
        if ((m_K1.phase() + m_O1.phase() + 2*m_longitud) >= 360.0){
            hcd-=12;
        }else{
            hcd+=12;
        }
    }

    if(hcd > 24.0) hcd-=24;
    if(hcd < 0) hcd+=24;

    m_value = hcd;
}
