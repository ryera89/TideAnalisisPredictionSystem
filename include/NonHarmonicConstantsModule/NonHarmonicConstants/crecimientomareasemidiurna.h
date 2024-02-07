#ifndef CRECIMIENTOMAREASEMIDIURNA_H
#define CRECIMIENTOMAREASEMIDIURNA_H

/*Esta clase es la constante no armonica
Crecimiento de la marea semidiurna, depende de las constantes armonicas
M2, S2*/

#include "include/HarmonicConstantsModule/HarmonicConstantClass/harmonicconstant.h"
#include <QString>

class CrecimientoMareaSemidiurna {
public:
  explicit CrecimientoMareaSemidiurna(const HarmonicConstant &M2,
                                      const HarmonicConstant &S2);

  double CMS() const { return m_value; }

private:
  const QString m_name = "Crecimiento de la Marea Semidiurna";
  const QString m_description =
      "Intervalo de tiempo desde el momento de ocurrencia"
      " de luna nueva o llena hasta el momento de ocurrencia de la"
      " mayor amplitud de la marea , las llamadas mareas de sicigias"
      " en las cual la fase de las ondas M2 y S2 coinciden.";

  HarmonicConstant m_M2;
  HarmonicConstant m_S2;

  double m_value;

  void calculate();
};

#endif // CRECIMIENTOMAREASEMIDIURNA_H
