#ifndef HORACOTIDIANASEMIDIURNA_H
#define HORACOTIDIANASEMIDIURNA_H

#include <QString>
#include "include/HarmonicConstantsModule/HarmonicConstantClass/harmonicconstant.h"


class HoraCotidianaSemidiurna
{
public:
    HoraCotidianaSemidiurna(const HarmonicConstant &M2, const HarmonicConstant &M4, const HarmonicConstant &M6, const double &longitud);

    double HCS() const{return m_value;}
private:
    const QString m_name = "Hora Cotidiana de la Marea Semidiurna";

    HarmonicConstant m_M2;
    HarmonicConstant m_M4;
    HarmonicConstant m_M6;
    double m_longitud;

    double m_value;

    double shallowWaterInfluence1();   //devuelven la influencia de la aguas poco profundas en esta constante
    double shallowWaterInfluence2();

    void calculate();
};

#endif // HORACOTIDIANASEMIDIURNA_H
