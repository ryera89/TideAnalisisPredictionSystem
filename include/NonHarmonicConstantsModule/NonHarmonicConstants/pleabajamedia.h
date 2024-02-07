#ifndef PLEABAJAMEDIA_H
#define PLEABAJAMEDIA_H

/*Esta clase representa las constantes no armonicas PMS, PMC
PMT, BMS, BMC y  BMT dependen de las constantes no armonicas
APSS, APC, APT y HTL.*/

#include "include/HarmonicConstantsModule/HarmonicConstantClass/harmonicconstant.h"
#include <QString>
class AlturaPromedioMarea;
class AlturaSemimarea;

class PleaBajaMedia {
public:
  explicit PleaBajaMedia(const AlturaPromedioMarea &apm,
                         const AlturaSemimarea &as);

  double PleamarMediaSicigias() const { return m_PMS; }
  double PleamarMediaCuadratura() const { return m_PMC; }
  double PleamarMediaTropical() const { return m_PMT; }
  double BajamarMediaSicigias() const { return m_BMS; }
  double BajamarMediaCuadratura() const { return m_BMC; }
  double BajamarMediaTropical() const { return m_BMT; }

private:
  // Pleas
  const QString m_namePMS = "Pleamar Media de Sicigias.";
  const QString m_namePMC = "Pleamar Media de Cuadratura.";
  const QString m_namePMT = "Pleamar Media Tropical.";
  // Bajas
  const QString m_nameBMS = "Bajamar Media de Sicigias.";
  const QString m_nameBMC = "Bajamar Media de Cuadraturas.";
  const QString m_nameBMT = "Bajamar Media Tropical.";

  // Pleamares
  double m_PMS;
  double m_PMC;
  double m_PMT;
  // Bajamares
  double m_BMS;
  double m_BMC;
  double m_BMT;

  void calculate(const AlturaPromedioMarea &apm, const AlturaSemimarea &as);
};

#endif // PLEABAJAMEDIA_H
