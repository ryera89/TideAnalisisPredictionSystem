#include "semidiurnalrelation.h"
#include "include/HarmonicConstantsModule/HarmonicConstantClass/harmonicconstant.h"


SemidiurnalRelation::SemidiurnalRelation(const HarmonicConstant &M2, const HarmonicConstant &S2):
    m_M2(M2), m_S2(S2)
{
    calculate();
}

void SemidiurnalRelation::calculate()
{
    m_Relation = m_S2.amplitud()/m_M2.amplitud();
}
