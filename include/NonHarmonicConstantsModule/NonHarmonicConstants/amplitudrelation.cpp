#include "amplitudrelation.h"
#include "include/HarmonicConstantsModule/HarmonicConstantClass/harmonicconstant.h"


AmplitudRelation::AmplitudRelation(const HarmonicConstant &M2, const HarmonicConstant &K1, const HarmonicConstant &O1):
    m_M2(M2), m_K1(K1), m_O1(O1)
{
    calculate();
}

void AmplitudRelation::calculate()
{
    m_Relation = (m_K1.amplitud() + m_O1.amplitud())/m_M2.amplitud();
}
