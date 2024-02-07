#include "pleabajamedia.h"

#include "alturapromediomarea.h"
#include "alturasemimarea.h"

PleaBajaMedia::PleaBajaMedia(const AlturaPromedioMarea &apm,
                             const AlturaSemimarea &as) {
  calculate(apm, as);
}

void PleaBajaMedia::calculate(const AlturaPromedioMarea &apm,
                              const AlturaSemimarea &as) {
  m_PMS = as.AlturaDeSemimarea() +
          apm.AlturaPromedioSicigias() / 2; // Pleamar Media de Sicigias

  m_PMC = as.AlturaDeSemimarea() +
          apm.AlturaPromedioCuadratura() / 2; // Pleamar Media de Cuadratura

  m_PMT = as.AlturaDeSemimarea() +
          apm.AlturaPromedioTropical() / 2; // Pleamar Media Tropical

  m_BMS = as.AlturaDeSemimarea() -
          apm.AlturaPromedioSicigias() / 2; // Bajamar Media de Sicigias

  m_BMC = as.AlturaDeSemimarea() -
          apm.AlturaPromedioCuadratura() / 2; // Bajamar Media de Cuadratura

  m_BMT = as.AlturaDeSemimarea() -
          apm.AlturaPromedioTropical() / 2; // Bajamar Media Tropical
}
