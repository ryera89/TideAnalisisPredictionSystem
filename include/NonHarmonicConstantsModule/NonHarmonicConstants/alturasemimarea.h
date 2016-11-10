#ifndef ALTURASEMIMAREA_H
#define ALTURASEMIMAREA_H


/*Esta clase es la constante no arminica
Altura de Semimarea, depende de las constantes armonicas
M2, K1, O1, M4 y de L (que es Altura del NMM sobre el cero de profundidad que se toma para dicha carta.
(altura del NMM con respecto al NMT o NMB ).*/

#include <QString>
#include "include/HarmonicConstantsModule/HarmonicConstantClass/harmonicconstant.h"
class HarmonicConstant;

class AlturaSemimarea
{
public:
    explicit AlturaSemimarea(const HarmonicConstant &M2, const HarmonicConstant &K1,
                             const HarmonicConstant &O1, const HarmonicConstant &M4, const double &L);


    double AlturaDeSemimarea() const{return m_HTL;}

private:

    const QString m_name = "Altura de la Semimarea";
    const QString m_description = "Altura media calculada utilizando solamente"
                                         " las alturas de las pleamares y bajamares.";

    HarmonicConstant m_M2;
    HarmonicConstant m_K1;
    HarmonicConstant m_O1;
    HarmonicConstant m_M4;
    double m_L;

    double m_HTL;

    void calculate();
};

#endif // ALTURASEMIMAREA_H
