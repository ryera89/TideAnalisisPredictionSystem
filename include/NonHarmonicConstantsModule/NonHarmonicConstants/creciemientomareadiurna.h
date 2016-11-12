#ifndef CRECIEMIENTOMAREADIURNA_H
#define CRECIEMIENTOMAREADIURNA_H

/*Esta clase es la constante no armonica
Crecimiento de la marea paralactica, depende de las constantes armonicas
O1, K1*/

#include <QString>
#include "include/HarmonicConstantsModule/HarmonicConstantClass/harmonicconstant.h"

class CreciemientoMareaDiurna
{
public:
    explicit CreciemientoMareaDiurna(const HarmonicConstant &K1, const HarmonicConstant &O1);

    double CMD() const{return m_value;}

private:
   const QString m_name = "Crecimiento de la Marea Diurna";
   const QString m_description = "Intervalo de tiempo desde el momento de"
                                         " momento de la mayor declinación Lunar,"
                                         " hasta el momento de coincidencia de las"
                                         " fases de las ondas K1 y O1.";


    HarmonicConstant m_K1;
    HarmonicConstant m_O1;

    double m_value;

    void calculate();
};

#endif // CRECIEMIENTOMAREADIURNA_H
