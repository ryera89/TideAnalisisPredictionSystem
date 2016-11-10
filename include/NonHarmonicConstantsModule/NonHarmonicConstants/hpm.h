#ifndef HPM_H
#define HPM_H

/*Esta clase es la constante no armonica
Hora del puesto media o HPM tambien conocida como
Intervalo Lunar, depende de las constantes armonicas
M2, M4, M6*/

#include <QString>
#include "include/HarmonicConstantsModule/HarmonicConstantClass/harmonicconstant.h"

class HPM
{
public:
    explicit HPM(const HarmonicConstant &M2, const HarmonicConstant &M4, const HarmonicConstant &M6);

    int hours() const{return m_hours;}
    int minutes() const{return m_minutes;}

private:
    const QString m_name = "Hora del Puesto Media";
    const QString m_description = "Intervalo de tiempo desde el momento de "
                                         "culminación de la luna hasta el momento de ocurrencia de la pleamar.";

    //Constantes armonicas que determinan esta constante no armonica
    HarmonicConstant m_M2;
    HarmonicConstant m_M4;
    HarmonicConstant m_M6;

    int m_hours;    //Esta constante se expresa en unidades de tiempo (ie horas y minutos (+-1minuto))
    int m_minutes;

    double shallowWaterInfluence();   //devuelve la influencia de la aguas poco profundas en esta constante
    void calculate();   //Calcula la constante no armonica
};

#endif // HPM_H
