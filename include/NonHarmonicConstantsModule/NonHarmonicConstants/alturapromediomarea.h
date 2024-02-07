#ifndef ALTURAPROMEDIOMAREA_H
#define ALTURAPROMEDIOMAREA_H

/*Esta clase representa las constantes no armonicas APS, APSS
APC y APT, dependen de las constantes armonicas
M2, S2, N2, K2, K1, O1, P1, Q1, M4, M6.*/

#include "include/HarmonicConstantsModule/HarmonicConstantClass/harmonicconstant.h"
#include <QString>

class AlturaPromedioMarea {
public:
  explicit AlturaPromedioMarea(
      const HarmonicConstant &M2, const HarmonicConstant &S2,
      const HarmonicConstant &N2, const HarmonicConstant &K2,
      const HarmonicConstant &K1, const HarmonicConstant &O1,
      const HarmonicConstant &P1, const HarmonicConstant &Q1,
      const HarmonicConstant &M4, const HarmonicConstant &M6);

  double AlturaPromedioSemidiurna() const { return m_APS; }
  double AlturaPromedioSicigias() const { return m_APSS; }
  double AlturaPromedioCuadratura() const { return m_APC; }
  double AlturaPromedioTropical() const { return m_APT; }

private:
  const QString m_nameAPS = "Altura Promedio de la Marea Semidiurna";
  const QString m_nameAPSS = "Altura Promedio de la Marea en Sicigias";
  const QString m_nameAPC = "Altura Promedio de la Marea en Cuadratura";
  const QString m_nameAPT = "Altura Promedio de la Marea Tropical";

  HarmonicConstant m_M2;
  HarmonicConstant m_S2;
  HarmonicConstant m_N2;
  HarmonicConstant m_K2;
  HarmonicConstant m_K1;
  HarmonicConstant m_O1;
  HarmonicConstant m_P1;
  HarmonicConstant m_Q1;
  HarmonicConstant m_M4;
  HarmonicConstant m_M6;

  double m_APS;  // Altura promedio de marea semidiurna
  double m_APSS; // Altura promedio de marea en sicigias
  double m_APC;  // Altura promedio de marea de cuadratura
  double m_APT;  // Altura promedio de marea tropical

  double A();
  double B();

  double V(); // angulo v de la formula
  double W(); // angulo w de la formula

  double Mn(); // componente de la formula

  void calculate();
};

#endif // ALTURAPROMEDIOMAREA_H
