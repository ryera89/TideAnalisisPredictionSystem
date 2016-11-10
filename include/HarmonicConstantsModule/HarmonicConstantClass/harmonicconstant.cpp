#include "harmonicconstant.h"
#include <QtMath>


HarmonicConstant::HarmonicConstant():m_name(QString()),m_frequency(0.0),m_description(QString()),m_C(0.0),m_S(0.0),m_amplitud(0.0),m_phase(0.0){}

HarmonicConstant::HarmonicConstant(const QString &name, const double &frequency, const QString &description):m_name(name),m_frequency(frequency),
    m_description(description), m_C(0.0),m_S(0.0),m_amplitud(0.0), m_phase(0.0){}

HarmonicConstant::HarmonicConstant(const QString &name, const double &frequency, const QString &description, const double &C, const double &S):
    m_name(name),m_frequency(frequency),m_description(description), m_C(C), m_S(S)

{
    m_amplitud = qSqrt(qPow(C,2) + qPow(S,2));

    if (C != 0.0){
        m_phase = qRadiansToDegrees((qAtan(S/C)));

        if (S > 0.0 && C < 0.0) m_phase+=180;
        if (S < 0.0 && C < 0.0) m_phase+=180;
        if (S < 0.0 && C > 0.0) m_phase+=360;
    }else m_phase = 90.0;

}

void HarmonicConstant::setComponentValues(const double &C, const double &S)
{
    m_C = C;
    m_S = S;

    m_amplitud = qSqrt(qPow(C,2) + qPow(S,2));

    if (C != 0.0){
        m_phase = qRadiansToDegrees((qAtan(S/C)));

        if (S > 0.0 && C < 0.0) m_phase+=180;
        if (S < 0.0 && C < 0.0) m_phase+=180;
        if (S < 0.0 && C > 0.0) m_phase+=360;

    }else m_phase = 90.0;
}



