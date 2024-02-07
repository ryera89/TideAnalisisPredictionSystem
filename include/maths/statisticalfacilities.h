#ifndef STATISTICALFACILITIES_H
#define STATISTICALFACILITIES_H

#include <QVector>
#include <cmath>
#include <valarray>

using namespace std;

double
mean(const QVector<double> &measurements); // Valor medio de la distribucion
double mean(const valarray<double> &measurements);
double varianza(const QVector<double> &measurements); // varianza
double varianza(const valarray<double> &measurements);
double desvstd(const QVector<double> &measurements); // Desviacion estandar
double desvstd(const valarray<double> &measurements);
double absMeanDesv(const QVector<double> &measurement);
double absMeanDesv(const valarray<double> &measurement);
double
skewnees(const QVector<double> &
             measurements); // Skewnees: degree of assymetry of the distribution
double skewnees(const valarray<double> &measurements);
double
kurtosis(const QVector<double> &measurements); // Kurtosis: relative peakedness
                                               // or flatness of a distribution
double kurtosis(const valarray<double> &measurements);

#endif // STATISTICALFACILITIES_H
