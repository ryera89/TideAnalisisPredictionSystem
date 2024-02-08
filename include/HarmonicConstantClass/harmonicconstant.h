#ifndef HARMONICCONSTANT_H
#define HARMONICCONSTANT_H

#include "doodsonnumbers.h"
#include <QString>

class HarmonicConstant {
public:
  enum Origin {
    SOLAR,
    LUNAR_LONGPERIOD_1,
    LUNAR_LONGPERIOD_2,
    LUNAR_DIURNAL_1,
    LUNAR_DIURNAL_2,
    LUNAR_DIURNAL_3,
    COMBINATION_DIURNAL_1,
    COMBINATION_DIURNAL_2,
    LUNAR_SEMIDIURNAL_1,
    LUNAR_SEMIDIURNAL_1_2,
    LUNAR_SEMIDIURNAL_2,
    COMBINATION_SEMIDIURNAL_1,
    COMBINATION_SEMIDIURNAL_2,
    LUNAR_TERDIURNAL,
    SHALLOW_1,
    SHALLOW_2,
    SHALLOW_3,
    SHALLOW_COMB_1,
    SHALLOW_COMB_2,
    SHALLOW_COMB_3
  };
  // SOLAR componentes de origen solar f = 1.0, u = 0
  // LUNAR_LONGPERIOD_1  componentes Mm, Msf u = 0, f =
  // [2/3-pow(sin(I),2)]/0.5021 LUNAR_LONGPERIOD_2  componente Mf u = -2ξ, f =
  // pow(sin(I),2)/0.1578 LUNAR_DIURNAL_1 componentes lunares diurnas
  // O1,Q1,2Q1,RHO1,SIGMA1,SO3 u = 2ξ-ν, f = sin(I)*pow(cos(I/2),2)/0.3800
  // LUNAR_DIURNAL_2 componentes lunares diurnas J1,CHI1,THETA1,MP1,SO1 u = -ν,
  // f = sin(2I)/0.7214 LUNAR_DIURNAL_3 lunares diurnas OO1, KQ1 f =
  // sin(I)*pow(sin(I/2),2)/0.0164, u = -2ξ-ν COMBINATION_DIURNAL_1 componente
  // M1 f = sin(I)*pow(cos(I/2),2)/(0.3800*Qa) = f(O1)/Qa, u = ξ-ν+Q
  // COMBINATION_DIURNAL_2 componentes K1, SK3, f =
  // sqrt(0.8965*pow(sin(2I),2)+0.6001*sin(2I)cos(ν) + 0.1006),u = - ν’
  // LUNAR_SEMIDIURNAL_1 componentes lunares semidiurnas
  // M2,N2,2N2,NU2,LAMDA2,MU2,2SM2,MS4,2SM6 f = pow(cos(I/2),4)/0.9154, u =
  // 2ξ-2ν LUNAR_SEMIDIURNAL_1_2 componente 2SM2 f = f = pow(cos(I/2),4)/0.9154,
  // u = -2ξ+2ν LUNAR_SEMIDIURNAL_2 componente lunar semidiurna KJ2 f =
  // pow(sin(I),2)/0.1565, u = -2ν COMBINATION_SEMIDIURNAL_1 componente
  // semidiurna L2 f(M2)/Ra, u = 2ξ-2ν-R COMBINATION_SEMIDIURNAL_2 componente
  // semidiurna K2 f = sqrt(19.0444*pow(sin(I)),4)+2.7702*pow(sin(I),2)*cos(2ν)
  // + 0.0981), u = -2ν'' LUNAR_TERDIURNAL componente M3 f =
  // pow(cos(I/2),6)/0.8758, u = 3ξ-3ν SHALLOW_1 las componentes
  // MNS2,M4,MN4,2MS6,MSN6,2(MS)8 f = pow(f(M2),2), u = 4ξ-4ν = 2*u(M2)
  // SHALLOW_2 componentes M6,2MN6,3MS8,2MSN8 f = pow(f(M2),3), u = 6ξ-6ν =
  // 3*u(M2) SHALLOW_3 componentes M8 f = pow(f(M2),4), u = 8ξ-8ν = 4*u(M2)
  // SHALLOW_COMB_1 componentes MK3 f = f(M2)*f(K1), u = 2ξ-2ν-ν’
  // SHALLOW_COMB_2 componentes 2MK3 f = pow(f(M2),2)*f(K1), u = 4ξ-4ν+ν’
  // SHALLOW_COMB_3 componentes MK4 // f = pow(f(M2),2)*f(K2), u = 2ξ-2ν-2ν’’

  HarmonicConstant();
  HarmonicConstant(const QString &name, const double &frequency,
                   const DoodsonNumbers &doodsonNumber, Origin orig);
  HarmonicConstant(const QString &name, const double &frequency,
                   const double &C, const double &S,
                   const DoodsonNumbers &doodsonNumber, Origin orig);

  // void setDescription(const QString &description){m_description =
  //  description;}
  void setName(const QString &name) { m_name = name; }
  void setFrequency(const double &frequency) { m_frequency = frequency; }
  void setComponentValues(const double &C, const double &S);
  void setAmplitud(const double &amp) { m_amplitud = amp; }
  void setPhase(const double &fase) { m_phase = fase; }
  void setCorrectedPhase(const double &cphase) { m_correctedPhase = cphase; }
  void setOrigin(Origin orig) { m_origin = orig; }

  // QString description()const {return m_description;}
  QString name() const { return m_name; }
  double frequency() const { return m_frequency; }
  double cosComponent() const { return m_C; }
  double senComponent() const { return m_S; }
  double amplitud() const { return m_amplitud; }
  double phase() const { return m_phase; }
  double correctedPhase() const { return m_correctedPhase; }

  Origin origin() const { return m_origin; }

  DoodsonNumbers doodsonNumbers() const { return m_doodsonNumber; }

private:
  QString m_name;
  double m_frequency;
  // QString m_description;

  double m_C; // componente que se multiplica con los cosenos
  double m_S; // componente que se multiplica con los senos

  double m_amplitud;
  double m_phase;
  double m_correctedPhase;

  DoodsonNumbers m_doodsonNumber;
  Origin m_origin;
};

#endif // HARMONICCONSTANT_H
