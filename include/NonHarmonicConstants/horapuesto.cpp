#include "horapuesto.h"
#include "hpm.h"
#include <QtMath>
HoraPuesto::HoraPuesto(const HarmonicConstant &M2, const HarmonicConstant &S2,
                       const HPM &hpm)
    : m_M2(M2), m_S2(S2) {
  calculate(hpm);
}

void HoraPuesto::calculate(const HPM &hpm) {
  double E1 = hpm.HoraPuestoMedia();

  double E;
  int cont = 0;
  do {
    E = E1;

    double omega = 0.508 * E1;

    double aux1 = m_M2.phase() / 2;
    double aux2 = m_S2.phase() / 2;

    double num = -qSin(qDegreesToRadians(2 * (omega + aux1 - aux2)));
    double den = m_M2.amplitud() / m_S2.amplitud() +
                 qCos(qDegreesToRadians(2 * (omega + aux1 - aux2)));

    double tanX = num / den;

    double X = qRadiansToDegrees(qAtan(tanX)) / 2;

    E1 = (X + omega + m_M2.amplitud() / 2) / 15;

    ++cont;
  } while (qFabs(E1 - E) > 0.001 && cont < 1000000);

  m_value = E1;
}
