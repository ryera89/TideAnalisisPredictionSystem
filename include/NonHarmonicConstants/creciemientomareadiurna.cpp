#include "creciemientomareadiurna.h"
#include <QtMath>

CreciemientoMareaDiurna::CreciemientoMareaDiurna(const HarmonicConstant &K1,
                                                 const HarmonicConstant &O1)
    : m_K1(K1), m_O1(O1) {
  calculate();
}

void CreciemientoMareaDiurna::calculate() {
  double deltaF = m_K1.phase() - m_O1.phase();
  double t = 0.0;
  if (deltaF <= 180) {
    t = 0.911 * (deltaF) / 24;
  } else {
    t = -0.911 * (deltaF) / 24;
  }

  m_value = t;
}
