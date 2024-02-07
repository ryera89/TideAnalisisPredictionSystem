#include "predictionfunctions.h"

#include <iostream>

// Interval en seconds 1h = 3600sec
QVector<TidesMeasurement>
predictionsWithNodalFactorCte(const double &datum, const QDateTime &from,
                              const QDateTime &to, const quint64 &interval,
                              const QVector<HarmonicConstant> &hcVector) {
  QDateTime aux(from.date(), from.time(), Qt::UTC);
  QDateTime auxEnd(to.date(), to.time(), Qt::UTC);

  AstronomicalMeanLongitudes aml_V0(from);

  QDateTime middPoint = determineDataSerieMidPoint(aux, auxEnd);

  AstronomicalMeanLongitudes aml_u(middPoint);

  QVector<TidesMeasurement> resp;
  double t = 0.0;
  while (aux <= auxEnd) {

    resp.push_back(
        predictionWithNodalFactorCte(datum, t, aml_V0, aml_u, aux, hcVector));

    t += interval / 3600.0;
    aux = aux.addSecs(interval);
  }

  return resp;
}

QVector<TidesMeasurement>
predictionsWithNodalFactorVar(const double &datum, const QDateTime &from,
                              const QDateTime &to, const quint64 &interval,
                              const QVector<HarmonicConstant> &hcVector) {
  AstronomicalMeanLongitudes aml_V0(from);

  QDateTime aux(from.date(), from.time(), Qt::UTC);
  QDateTime auxEnd(to.date(), to.time(), Qt::UTC);
  double t = 0.0;
  QVector<TidesMeasurement> resp;
  while (aux <= auxEnd) {
    resp.push_back(
        predictionWithNodalFactorVar(datum, t, aux, aml_V0, hcVector));
    t += interval / 3600.0;
    aux = aux.addSecs(interval);
  }

  return resp;
}

QVector<TidesMeasurement>
findHighLowWatersWithNodalFactorVar(const double &datum, const QDateTime &from,
                                    const QDateTime &to,
                                    const QVector<HarmonicConstant> &hcVector) {
  AstronomicalMeanLongitudes beginV0(from);

  QDateTime aux(from.date(), from.time(), Qt::UTC);
  QDateTime auxEnd(to.date(), to.time(), Qt::UTC);

  double t = 0.0;
  double ta = 0.0;
  double tb = 0.0;

  // double min = 0.0;
  // double max = 0.0;

  QVector<TidesMeasurement> resp;

  while (aux <= auxEnd) {
    double h = datum;
    double ha = datum;
    double hb = datum;

    tb = t + 60.0 / 3600.0;
    ta = t - 60.0 / 3600.0;

    AstronomicalMeanLongitudes astlong(aux);
    for (int i = 0; i < hcVector.size(); ++i) {

      double f = NodalAmplitudeFactor(hcVector.at(i), astlong);
      double V0_plus_u = V0_u(hcVector.at(i), beginV0, astlong);

      double aux1 = hcVector.at(i).frequency() * t;
      double aux2 = V0_plus_u;
      double aux3 = hcVector.at(i).correctedPhase();

      double rAmp = f * hcVector.at(i).amplitud();
      h += rAmp * qCos(qDegreesToRadians(aux1 + aux2 - aux3));

      double wta = hcVector.at(i).frequency() * ta;
      double wtb = hcVector.at(i).frequency() * tb;

      ha += rAmp * qCos(qDegreesToRadians(wta + aux2 - aux3));
      hb += rAmp * qCos(qDegreesToRadians(wtb + aux2 - aux3));
    }
    if (ha < h && hb < h) {
      TidesMeasurement predMeas(h, aux);
      resp.push_back(predMeas);
    }
    if (ha > h && hb > h) {
      TidesMeasurement predMeas(h, aux);
      resp.push_back(predMeas);
    }

    // std::cout << t << std::endl;
    // std::cout << aux.toString("dd/MM/yyyy hh:mm").toStdString() << std::endl;
    t += 60.0 / 3600.0;
    aux = aux.addSecs(60);
  }

  return resp;
}

QVector<TidesMeasurement>
findHighLowWatersWithNodalFactorCte(const double &datum, const QDateTime &from,
                                    const QDateTime &to,
                                    const QVector<HarmonicConstant> &hcVector) {
  AstronomicalMeanLongitudes beginV0(from);

  QDateTime middPoint = determineDataSerieMidPoint(from, to);

  AstronomicalMeanLongitudes midd_u_And_f(middPoint);

  QVector<double> hcF;
  QVector<double> hcV_u;
  for (int i = 0; i < hcVector.size(); ++i) {
    double f = NodalAmplitudeFactor(hcVector.at(i), midd_u_And_f);
    double V0_plus_u = V0_u(hcVector.at(i), beginV0, midd_u_And_f);
    hcF.push_back(f);
    hcV_u.push_back(V0_plus_u);

    // std::cout << hcVector.at(i).name().toStdString() << " " << f << " " <<
    // V0_plus_u << std::endl;
  }

  QDateTime aux(from.date(), from.time(), Qt::UTC);
  QDateTime auxEnd(to.date(), to.time(), Qt::UTC);
  QVector<TidesMeasurement> resp;
  double t = 0.0;
  double ta = 0.0;
  double tb = 0.0;
  while (aux <= auxEnd) {
    double h = datum;
    double ha = datum;
    double hb = datum;

    tb = t + 60.0 / 3600.0;
    ta = t - 60.0 / 3600.0;

    for (int i = 0; i < hcVector.size(); ++i) {
      double aux1 = hcVector.at(i).frequency() * t;
      double aux2 = hcV_u.at(i);
      double aux3 = hcVector.at(i).correctedPhase();

      double rAmp = hcF.at(i) * hcVector.at(i).amplitud();
      h += rAmp * qCos(qDegreesToRadians(aux1 + aux2 - aux3));

      double wta = hcVector.at(i).frequency() * ta;
      double wtb = hcVector.at(i).frequency() * tb;

      ha += rAmp * qCos(qDegreesToRadians(wta + aux2 - aux3));
      hb += rAmp * qCos(qDegreesToRadians(wtb + aux2 - aux3));
    }
    if (ha < h && hb < h) {
      TidesMeasurement predMeas(h, aux);
      resp.push_back(predMeas);
    }
    if (ha > h && hb > h) {
      TidesMeasurement predMeas(h, aux);
      resp.push_back(predMeas);
    }

    // std::cout << t << std::endl;
    t += 60.0 / 3600.0;
    aux = aux.addSecs(60);
  }

  return resp;
}

TidesMeasurement
predictionWithNodalFactorVar(const double &datum, const double &t,
                             const QDateTime &current,
                             const AstronomicalMeanLongitudes &aml_V0,
                             const QVector<HarmonicConstant> &hcVector) {
  double h = datum;

  AstronomicalMeanLongitudes aml_u(current);

  for (int i = 0; i < hcVector.size(); ++i) {
    double f = NodalAmplitudeFactor(hcVector.at(i), aml_u); // Nodal Factor

    double astrCorr = V0_u(hcVector.at(i), aml_V0, aml_u); // V0 + u

    double wt = hcVector.at(i).frequency() * t;

    double phaseC =
        hcVector.at(i).correctedPhase(); // Fase Corregida de la constante

    double ampR = f * hcVector.at(i).amplitud(); // Amplitud Reducida

    h += ampR * qCos(qDegreesToRadians(wt + astrCorr - phaseC));
  }
  TidesMeasurement predMeas(h, current);

  return predMeas;
}

TidesMeasurement
predictionWithNodalFactorCte(const double &datum, const double &t,
                             const AstronomicalMeanLongitudes &aml_V0,
                             const AstronomicalMeanLongitudes &aml_u,
                             const QDateTime &current,
                             const QVector<HarmonicConstant> &hcVector) {
  double h = datum;

  for (int i = 0; i < hcVector.size(); ++i) {
    double f = NodalAmplitudeFactor(hcVector.at(i), aml_u); // Nodal Factor

    double astrCorr = V0_u(hcVector.at(i), aml_V0, aml_u); // V0 + u

    double wt = hcVector.at(i).frequency() * t;

    double phaseC =
        hcVector.at(i).correctedPhase(); // Fase Corregida de la constante

    double ampR = f * hcVector.at(i).amplitud(); // Amplitud Reducida

    h += ampR * qCos(qDegreesToRadians(wt + astrCorr - phaseC));
  }

  TidesMeasurement predMeas(h, current);

  return predMeas;
}

QVector<TidesMeasurement>
findExtremesWithNodalFactorsVar(const double &datum, const QDateTime &from,
                                const QDateTime &to,
                                const QVector<HarmonicConstant> &hcVector) {
  QDateTime aux(from.date(), from.time(), Qt::UTC);
  QDateTime auxEnd(to.date(), to.time(), Qt::UTC);

  QDateTime datetime_a(aux);
  QDateTime datetime_b(aux);
  QDateTime datetime_c(aux);

  AstronomicalMeanLongitudes aml_V0(aux);

  double ta = 0.0;
  double tb = 0.0;
  double tc = 0.0;

  QVector<TidesMeasurement> resp;

  while (aux <= auxEnd) {
    ta = tb - 1.0;
    tc = tb + 1.0;

    datetime_a = datetime_b.addSecs(-3600);
    datetime_c = datetime_b.addSecs(3600);

    double ha =
        predictionWithNodalFactorVar(datum, ta, datetime_a, aml_V0, hcVector)
            .seaLevel();
    double hb =
        predictionWithNodalFactorVar(datum, tb, datetime_b, aml_V0, hcVector)
            .seaLevel();
    double hc =
        predictionWithNodalFactorVar(datum, tc, datetime_c, aml_V0, hcVector)
            .seaLevel();

    if (ha < hb && hc < hb) { // Maximo
      tb = ta + 60.0 / 3600.0;
      datetime_b = datetime_a.addSecs(60);
      hb = predictionWithNodalFactorVar(datum, tb, datetime_b, aml_V0, hcVector)
               .seaLevel();
      while (hb > ha) {
        ha = hb;
        ta = tb;
        tb = ta + 60.0 / 3600.0;
        datetime_a = datetime_b;
        datetime_b = datetime_a.addSecs(60);
        hb = predictionWithNodalFactorVar(datum, tb, datetime_b, aml_V0,
                                          hcVector)
                 .seaLevel();
      }
      TidesMeasurement predMeas(ha, datetime_a);
      resp.push_back(predMeas);
    }
    if (ha > hb && hc > hb) { // Minimo
      tb = ta + 60.0 / 3600.0;
      datetime_b = datetime_a.addSecs(60);
      hb = predictionWithNodalFactorVar(datum, tb, datetime_b, aml_V0, hcVector)
               .seaLevel();
      while (hb < ha) {
        ha = hb;
        ta = tb;
        tb = ta + 60.0 / 3600.0;
        datetime_a = datetime_b;
        datetime_b = datetime_a.addSecs(60);
        hb = predictionWithNodalFactorVar(datum, tb, datetime_b, aml_V0,
                                          hcVector)
                 .seaLevel();
      }
      TidesMeasurement predMeas(ha, datetime_a);
      resp.push_back(predMeas);
    }
    tb = tc;
    aux = aux.addSecs(3600);
    datetime_b = aux;
  }
  return resp;
}

QVector<TidesMeasurement>
findExtremesWithNodalFactorsCte(const double &datum, const QDateTime &from,
                                const QDateTime &to,
                                const QVector<HarmonicConstant> &hcVector) {
  QDateTime aux(from.date(), from.time(), Qt::UTC);
  QDateTime auxEnd(to.date(), to.time(), Qt::UTC);

  QDateTime datetime_a(aux);
  QDateTime datetime_b(aux);
  QDateTime datetime_c(aux);

  AstronomicalMeanLongitudes aml_V0(aux);

  QDateTime midd = determineDataSerieMidPoint(aux, auxEnd);

  AstronomicalMeanLongitudes aml_u(midd);

  double ta = 0.0;
  double tb = 0.0;
  double tc = 0.0;

  QVector<TidesMeasurement> resp;

  while (aux <= auxEnd) {
    ta = tb - 1.0;
    tc = tb + 1.0;

    datetime_a = datetime_b.addSecs(-3600);
    datetime_c = datetime_b.addSecs(3600);

    double ha = predictionWithNodalFactorCte(datum, ta, aml_V0, aml_u,
                                             datetime_a, hcVector)
                    .seaLevel();
    double hb = predictionWithNodalFactorCte(datum, tb, aml_V0, aml_u,
                                             datetime_b, hcVector)
                    .seaLevel();
    double hc = predictionWithNodalFactorCte(datum, tc, aml_V0, aml_u,
                                             datetime_c, hcVector)
                    .seaLevel();

    if (ha < hb && hc < hb) { // Maximo
      tb = ta + 60.0 / 3600.0;
      datetime_b = datetime_a.addSecs(60);
      hb = predictionWithNodalFactorCte(datum, tb, aml_V0, aml_u, datetime_b,
                                        hcVector)
               .seaLevel();
      while (hb > ha) {
        ha = hb;
        ta = tb;
        tb = ta + 60.0 / 3600.0;
        datetime_a = datetime_b;
        datetime_b = datetime_a.addSecs(60);
        hb = predictionWithNodalFactorCte(datum, tb, aml_V0, aml_u, datetime_b,
                                          hcVector)
                 .seaLevel();
      }
      TidesMeasurement predMeas(ha, datetime_a);
      resp.push_back(predMeas);
    }
    if (ha > hb && hc > hb) { // Minimo
      tb = ta + 60.0 / 3600.0;
      datetime_b = datetime_a.addSecs(60);
      hb = predictionWithNodalFactorCte(datum, tb, aml_V0, aml_u, datetime_b,
                                        hcVector)
               .seaLevel();
      while (hb < ha) {
        ha = hb;
        ta = tb;
        tb = ta + 60.0 / 3600.0;
        datetime_a = datetime_b;
        datetime_b = datetime_a.addSecs(60);
        hb = predictionWithNodalFactorCte(datum, tb, aml_V0, aml_u, datetime_b,
                                          hcVector)
                 .seaLevel();
      }
      TidesMeasurement predMeas(ha, datetime_a);
      resp.push_back(predMeas);
    }
    tb = tc;
    aux = aux.addSecs(3600);
    datetime_b = aux;
  }
  return resp;
}

TidesMeasurement findLAT(const QVector<TidesMeasurement> &extremes) {
  if (extremes.isEmpty())
    return TidesMeasurement();

  TidesMeasurement nmm = extremes.first();

  foreach (const TidesMeasurement &tmExt, extremes) {
    if (nmm.seaLevel() > tmExt.seaLevel())
      nmm = tmExt;
  }

  return nmm;
}

TidesMeasurement determineLAT(const double &datum, const QDateTime &begin,
                              const QVector<HarmonicConstant> &hcVector) {
  QDateTime to = begin.addYears(19);

  return findLAT(findExtremesWithNodalFactorsVar(datum, begin, to, hcVector));
}
