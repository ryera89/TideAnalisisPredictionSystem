#ifndef CRECIMIENTOMAREAPARACTICA_H
#define CRECIMIENTOMAREAPARACTICA_H

/*Esta clase es la constante no armonica
Crecimiento de la marea paralactica, depende de las constantes armonicas
M2, N2*/

#include <QString>
class HarmonicConstant;

class CrecimientoMareaParactica
{
public:
    explicit CrecimientoMareaParactica(const HarmonicConstant &M2, const HarmonicConstant &N2);

    int days() const{return m_days;}
    int hours() const{return m_hours;}

private:
    static const QString m_name = "Crecimiento de la Marea Paralactica";
    static const QString m_description = "Intervalo de tiempo desde el momento de perigeo de"
                                         " la luna hasta el momento de cuando las fases
                                         " de las ondas M2 y N2 coinciden.";

    HarmonicConstant m_M2;
    HarmonicConstant m_N2;

    int m_days;
    int m_hours;

    void calculate();
};

#endif // CRECIMIENTOMAREAPARACTICA_H
