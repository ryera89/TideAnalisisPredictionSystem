#ifndef AMPLITUDRELATION_H
#define AMPLITUDRELATION_H

/*Constante no armonica, Relacion de Ampitudes,
Depende de las constantes armonicas M2, K1, O1*/

#include <QString>

class HarmonicConstant;

class AmplitudRelation
{
public:
    explicit AmplitudRelation(const HarmonicConstant &M2, const HarmonicConstant &K1, const HarmonicConstant &O1);

    double amplRelation() const {return m_Relation;}
private:
    static const QString m_name = "Relacion de Amplitudes";

    HarmonicConstant m_M2;
    HarmonicConstant m_K1;
    HarmonicConstant m_O1;

    double m_Relation;

    void calculate();
};

#endif // AMPLITUDRELATION_H
