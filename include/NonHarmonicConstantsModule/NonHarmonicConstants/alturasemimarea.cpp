#include "alturasemimarea.h"

#include <QtMath>

AlturaSemimarea::AlturaSemimarea(const HarmonicConstant &M2,
                                 const HarmonicConstant &K1,
                                 const HarmonicConstant &O1,
                                 const HarmonicConstant &M4, const double &L)
    : m_M2(M2), m_K1(K1), m_O1(O1), m_M4(M4), m_L(L) {
  calculate();
}

void AlturaSemimarea::calculate() {
  double aux1 = m_M4.amplitud() *
                qCos(qDegreesToRadians(2 * m_M2.phase() - m_M4.phase()));

  double aux2 = qPow((m_K1.amplitud() + m_O1.amplitud()), 2) / m_M2.amplitud();
  double aux3 =
      0.04 * aux2 *
      qCos(qDegreesToRadians(m_M2.phase() - m_K1.phase() - m_O1.phase()));

  m_HTL = m_L + aux1 - aux3;
}
