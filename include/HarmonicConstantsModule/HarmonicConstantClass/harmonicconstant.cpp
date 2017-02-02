#include "harmonicconstant.h"
#include <QtMath>


HarmonicConstant::HarmonicConstant():m_name(QString()),m_frequency(0.0),m_C(0.0),m_S(0.0),m_amplitud(0.0),m_phase(0.0),m_correctedPhase(0.0),m_origin(SOLAR){}

HarmonicConstant::HarmonicConstant(const QString &name, const double &frequency, const DoodsonNumbers &doodsonNumber,Origin orig):m_name(name),m_frequency(frequency)
  , m_doodsonNumber(doodsonNumber), m_origin(orig), m_C(0.0),m_S(0.0),m_amplitud(0.0), m_phase(0.0),m_correctedPhase(0.0) {}

HarmonicConstant::HarmonicConstant(const QString &name, const double &frequency, const double &C, const double &S, const DoodsonNumbers &doodsonNumber,Origin orig):
    m_name(name),m_frequency(frequency), m_C(C), m_S(S), m_doodsonNumber(doodsonNumber),m_origin(orig)

{
    m_amplitud = qSqrt(qPow(C,2) + qPow(S,2));

    if (C != 0.0){
        m_correctedPhase = qRadiansToDegrees((qAtan(S/C)));

        //NOTE: Ver como afecta esto al resultado de las fases
        if (S > 0.0 && C < 0.0) m_correctedPhase+=180;
        if (S < 0.0 && C < 0.0) m_correctedPhase+=180;
        if (S < 0.0 && C > 0.0) m_correctedPhase+=360;
    }else m_correctedPhase = 90.0;

}

void HarmonicConstant::setComponentValues(const double &C, const double &S)
{
    m_C = C;
    m_S = S;

    m_amplitud = qSqrt(qPow(C,2) + qPow(S,2));

    if (C != 0.0){
        m_correctedPhase = qRadiansToDegrees((qAtan(S/C)));

        //NOTE: Ver como afecta esto al resultado de las fases
        if (S > 0.0 && C < 0.0) m_correctedPhase+=180;
        if (S < 0.0 && C < 0.0) m_correctedPhase+=180;
        if (S < 0.0 && C > 0.0) m_correctedPhase+=360;

    }else m_correctedPhase = 90.0;
}



