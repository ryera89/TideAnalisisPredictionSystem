#ifndef HORAPUESTO_H
#define HORAPUESTO_H

/*Constante no armonica <Hora del Puesto> depende de M2 y S2
asi como que se toma E = HPM en la primera aproximacion*/

#include <QString>

class HarmonicConstant;
class HPM;
class HoraPuesto
{
public:
    HoraPuesto(const HarmonicConstant &M2, const HarmonicConstant &S2, const HPM &hpm);


    int hours() const{return m_hours;}
    int minutes() const{return m_minutes;}


private:
    static const QString m_name = "Hora del Puesto";
    static const QString m_description = "Valor del intervalo Lunar, cuando la Luna pasa a través del "
                                         "meridiano del lugar simultáneamente con el Sol, con la condición que la Luna"
                                         " y el sol se encuentran en el ecuador , a distancias medias de la tierra. "
                                         "Tomando en cuenta que la luna culmina al mediodía o a medianoche, entonces "
                                         "la hora del puesto es la hora verdadera de ocurrencia de la pleamar.";


    HarmonicConstant m_M2;
    HarmonicConstant m_S2;

    int m_hours;
    int m_minutes;

    void calculate(const HPM &hpm);
};

#endif // HORAPUESTO_H
