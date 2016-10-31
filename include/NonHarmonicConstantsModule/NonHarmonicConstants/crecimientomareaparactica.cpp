#include "crecimientomareaparactica.h"

#include "include/HarmonicConstantsModule/HarmonicConstantClass/harmonicconstant.h"
#include <QtMath>

CrecimientoMareaParactica::CrecimientoMareaParactica(const HarmonicConstant &M2, const HarmonicConstant &N2):
    m_M2(M2), m_N2(N2)
{
    calculate();
}

void CrecimientoMareaParactica::calculate()
{
    double deltaF = m_M2.phase() - m_N2.phase();
    double t = 0.0;
    if (deltaF < 180){
        t = 1.837*(deltaF)/24;
    }else{
        t = -1.837*(deltaF)/24;
    }


    m_days = qFloor(t);
    m_hours = qFloor((t-m_days)*24);
}
