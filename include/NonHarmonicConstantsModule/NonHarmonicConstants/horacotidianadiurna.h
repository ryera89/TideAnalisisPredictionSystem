#ifndef HORACOTIDIANADIURNA_H
#define HORACOTIDIANADIURNA_H

#include "include/HarmonicConstantsModule/HarmonicConstantClass/harmonicconstant.h"
#include <QString>

class HoraCotidianaDiurna {
public:
  HoraCotidianaDiurna(const HarmonicConstant &K1, const HarmonicConstant &O1,
                      const double &longitud);

  double HCD() const { return m_value; }

private:
  const QString m_name = "Hora Cotidiana de la Marea Diurna";

  HarmonicConstant m_K1;
  HarmonicConstant m_O1;
  double m_longitud;

  double m_value;

  void calculate();
};

#endif // HORACOTIDIANADIURNA_H
