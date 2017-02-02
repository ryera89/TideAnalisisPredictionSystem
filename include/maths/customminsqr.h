#ifndef CUSTOMMINSQR_H
#define CUSTOMMINSQR_H

#include <QVector>
#include <vector>
#include "gauss_jordan.h"
#include "ludcmp.h"
#include <QDateTime>

class CustomMinSqr
{
public:
    CustomMinSqr(valarray<double> &x, valarray<double> &y, valarray<double> &sig, const QVector<QDateTime> &datetimeVector , QVector<double> funks(const double&, const QDateTime&, const QDateTime&));

    void hold(const int i, const double &val){ia[i] = false; a[i] = val;}  //fija el parametro de a[i]
    void free(const int i){ia[i] = true;}  //Libera el parametro de a[i]

    void fitGJ();
    void fitLU();
    //void fitLikeTheBook();

    valarray<double> parametros() const{return a;}
    Matrix matrizCovariante() const{return m_covar;}
    double chiSquare() const{return m_chisq;}

private:
    int m_nData;
    int m_nParam;
    valarray<double> &m_x;
    valarray<double> &m_y;
    valarray<double> &m_sig;          //varianza de cada medicion, si no se conoce debe ser pasada como uno para todas
    QVector<QDateTime> m_dateTimeVector;
    QVector<double> (*funcs)(const double&, const QDateTime&, const QDateTime&);
    vector<bool> ia;

    /*Parametros de salida*/
    valarray<double> a;             //parametros a ajustar
    Matrix m_covar;                 //Matriz Covariante
    double m_chisq;                   //Chi cuadrado del ajuste

};

#endif // CUSTOMMINSQR_H
