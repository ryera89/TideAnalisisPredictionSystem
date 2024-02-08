#include "harmonicconstant.h"

#include <cmath>
#include <numbers>

namespace {

constexpr double radiansToDegrees(double radians) noexcept {
  constexpr double toDegrees = 180 / std::numbers::pi;
  return radians * toDegrees;
}

constexpr double getCorrectedPhase(double sinComponent, double cosComponent) {
  // TODO: evaluate how this affect the phases result. Can not we work in
  // radians directly
  double phase = radiansToDegrees((std::atan2(sinComponent, cosComponent)));
  return phase > 0.0 ? phase : 360 + phase;
}
} // namespace

HarmonicConstant::HarmonicConstant(const QString &name, double frequency,
                                   const std::array<int, 7> &doodsonNumber,
                                   Origin orig)
    : m_name(name), m_frequency(frequency), m_C(0.0), m_S(0.0), m_amplitud(0.0),
      m_phase(0.0), m_correctedPhase(0.0), m_doodsonNumbers{doodsonNumber},
      m_origin(orig) {}

HarmonicConstant::HarmonicConstant(const QString &name, double frequency,
                                   std::array<int, 7> &&doodsonNumber,
                                   Origin orig)
    : m_name(name), m_frequency(frequency), m_C(0.0), m_S(0.0), m_amplitud(0.0),
      m_phase(0.0), m_correctedPhase(0.0), m_doodsonNumbers{doodsonNumber},
      m_origin(orig) {}

void HarmonicConstant::setName(const QString &name) { m_name = name; }

void HarmonicConstant::setFrequency(double frequency) {
  m_frequency = frequency;
}

void HarmonicConstant::setComponentValues(double C, double S) {
  m_C = C;
  m_S = S;

  m_amplitud = std::sqrt(C * C + S * S);
  m_correctedPhase = getCorrectedPhase(S, C);
}

void HarmonicConstant::setAmplitud(double amp) { m_amplitud = amp; }

void HarmonicConstant::setPhase(double phase) { m_phase = phase; }

void HarmonicConstant::setCorrectedPhase(double cphase) {
  m_correctedPhase = cphase;
}

void HarmonicConstant::setOrigin(Origin orig) { m_origin = orig; }

QString HarmonicConstant::name() const { return m_name; }

double HarmonicConstant::frequency() const { return m_frequency; }

double HarmonicConstant::cosComponent() const { return m_C; }

double HarmonicConstant::senComponent() const { return m_S; }

double HarmonicConstant::amplitud() const { return m_amplitud; }

double HarmonicConstant::phase() const { return m_phase; }

double HarmonicConstant::correctedPhase() const { return m_correctedPhase; }

HarmonicConstant::Origin HarmonicConstant::origin() const { return m_origin; }

const std::array<int, 7> &HarmonicConstant::doodsonNumbers() const {
  return m_doodsonNumbers;
}
