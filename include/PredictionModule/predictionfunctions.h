#ifndef PREDICTIONFUNCTIONS_H
#define PREDICTIONFUNCTIONS_H

#include <QtCore>
#include "include/HarmonicConstantsModule/HarmonicConstantClass/harmonicconstant.h"
#include "include/measurement/measurement.h"
#include <QVector>


QVector<TidesMeasurement> predictionWithNodalFactorCte(const double &datum, const QDateTime &from, const QDateTime &to, const quint64 &interval,const QVector<HarmonicConstant> &hcVector);
QVector<TidesMeasurement> predictionWithNodalFactorVar(const double &datum, const QDateTime &from, const QDateTime &to, const quint64 &interval,const QVector<HarmonicConstant> &hcVector);

#endif // PREDICTIONFUNCTIONS_H
