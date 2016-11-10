#ifndef DURACIONLLENANTE_H
#define DURACIONLLENANTE_H

/*Esta clase es la constante no armonica
Duracion del Llenante, depende de las constantes armonicas
M2, M4, M6*/

#include <QString>
#include "include/HarmonicConstantsModule/HarmonicConstantClass/harmonicconstant.h"

class DuracionLLenante
{
public:
    explicit DuracionLLenante(const HarmonicConstant &M2, const HarmonicConstant &M4, const HarmonicConstant &M6);

    int hours() const{return m_hours;}
    int minutes() const{return m_minutes;}


private:
    const QString m_name = "Duracion del Llenante";
    const QString m_description = "Valor medio del intervalo desde el momento de ocurrencia de la bajamar"
                                         " hasta el momento de ocurrencia de la pleamar siguiente.";

    //Constantes armonicas que determinan esta constante no armonica
    HarmonicConstant m_M2;
    HarmonicConstant m_M4;
    HarmonicConstant m_M6;

    int m_hours;    //Esta constante se expresa en unidades de tiempo (ie horas y minutos (+-1minuto))
    int m_minutes;

    double shallowWaterInfluence1();   //devuelven la influencia de la aguas poco profundas en esta constante
    double shallowWaterInfluence2();

    void calculate();   //Calcula la constante no armonica
};

#endif // DURACIONLLENANTE_H
