#ifndef PREDICTIONFUNCTIONS_H
#define PREDICTIONFUNCTIONS_H

#include "include/HarmonicConstantsModule/HarmonicConstantClass/harmonicconstant.h"
#include "include/HarmonicConstantsModule/HarmonicConstantClass/nodalfactorformulas.h"
#include "include/measurement/measurement.h"
#include <QVector>
#include <QtCore>

TidesMeasurement
predictionWithNodalFactorCte(const double &datum, const double &t,
                             const AstronomicalMeanLongitudes &aml_V0,
                             const AstronomicalMeanLongitudes &aml_u,
                             const QDateTime &current,
                             const QVector<HarmonicConstant> &hcVector);
TidesMeasurement
predictionWithNodalFactorVar(const double &datum, const double &t,
                             const QDateTime &current,
                             const AstronomicalMeanLongitudes &aml_V0,
                             const QVector<HarmonicConstant> &hcVector);

QVector<TidesMeasurement>
findExtremesWithNodalFactorsVar(const double &datum, const QDateTime &from,
                                const QDateTime &to,
                                const QVector<HarmonicConstant> &hcVector);
QVector<TidesMeasurement>
findExtremesWithNodalFactorsCte(const double &datum, const QDateTime &from,
                                const QDateTime &to,
                                const QVector<HarmonicConstant> &hcVector);

QVector<TidesMeasurement>
predictionsWithNodalFactorCte(const double &datum, const QDateTime &from,
                              const QDateTime &to, const quint64 &interval,
                              const QVector<HarmonicConstant> &hcVector);
QVector<TidesMeasurement>
predictionsWithNodalFactorVar(const double &datum, const QDateTime &from,
                              const QDateTime &to, const quint64 &interval,
                              const QVector<HarmonicConstant> &hcVector);
QVector<TidesMeasurement>
findHighLowWatersWithNodalFactorCte(const double &datum, const QDateTime &from,
                                    const QDateTime &to,
                                    const QVector<HarmonicConstant> &hcVector);
QVector<TidesMeasurement>
findHighLowWatersWithNodalFactorVar(const double &datum, const QDateTime &from,
                                    const QDateTime &to,
                                    const QVector<HarmonicConstant> &hcVector);

TidesMeasurement determineLAT(const double &datum, const QDateTime &begin,
                              const QVector<HarmonicConstant> &hcVector);
TidesMeasurement findLAT(const QVector<TidesMeasurement> &extremes);

#endif // PREDICTIONFUNCTIONS_H
