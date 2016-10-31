#ifndef SEMIDIURNALRELATION_H
#define SEMIDIURNALRELATION_H

/*Constante no armonica Relacion de las amplitudes medias semnidiurna solar y
semidiurna lunar, depende de las constantes armonicas M2, S2*/

#include <QString>

class HarmonicConstant;

class SemidiurnalRelation
{
public:
    SemidiurnalRelation(const HarmonicConstant &M2, const HarmonicConstant &S2);

    double relationS2M2() const{return m_Relation;}

private:
    static const QString m_name = "Relacion Semidiurna";
    static const QString m_description = "Relación entre las amplitudes medias de las ondas principal"
                                 " semidiurna solar y principal semidiurna lunar.";

    HarmonicConstant m_M2;
    HarmonicConstant m_S2;

    double m_Relation;

    void calculate();
};

#endif // SEMIDIURNALRELATION_H
