#ifndef MINSQR_H
#define MINSQR_H

/*********************************************************************
Esta es una libreria que implementa el metodo de minimos cuadrados
aqui se resolvera el problema apicando la solucion de sistema de ecuaciones
lineales por el metodo de LU, Gauss-Jordan, SVD y QR. El metodo fue implementado
en junio del 2016 y permite la eleccion de los parametros Ak que deben ser
ajustados los cual pueden ser escogidos por el usuario, ademas se obtine la
matriz covariante que nos brinda la varianza de los parametros ajustados. Esta
libreria esta implementada en C++ usando QVector de Qt
**********************************************************************/

#include "gauss_jordan.h"
#include "ludcmp.h"
#include <QVector>
#include <vector>

class MinSqr {
private:
  int m_nData;
  int m_nParam;
  valarray<double> &m_x;
  valarray<double> &m_y;
  valarray<double> &m_sig; // varianza de cada medicion, si no se conoce debe
                           // ser pasada como uno para todas
  QVector<double> (*funcs)(const double &);
  vector<bool> ia;

  /*Parametros de salida*/
  valarray<double> a; // parametros a ajustar
  Matrix m_covar;     // Matriz Covariante
  double m_chisq;     // Chi cuadrado del ajuste

public:
  MinSqr(valarray<double> &x, valarray<double> &y, valarray<double> &sig,
         QVector<double> funks(const double &));

  void hold(const int i, const double &val) {
    ia[i] = false;
    a[i] = val;
  }                                        // fija el parametro de a[i]
  void free(const int i) { ia[i] = true; } // Libera el parametro de a[i]

  void fitGJ();
  void fitLU();
  void fitLikeTheBook();

  valarray<double> parametros() const { return a; }
  Matrix matrizCovariante() const { return m_covar; }
  double chiSquare() const { return m_chisq; }
};

/*Matrix function(const Matrix);

class MinSqr
{
private:
    int m_nData;                //cantidad de mediciones
    int m_nHarmonicConstants;    //numero de constantes Armonicas a Calcular
    valarray<double> &m_measurement;   //vector donde se encuentran los valores
de las mediciones Matrix &m_w;               //Matriz nx1 n numero de constantes
armmonicas a calcular
    // m_m_t;               //Matriz 1xN N numero de mediciones
    valarray<double> m_x;            //vector para guardar los valores de las A
    valarray<double> m_y;            //vector para guardar los valores de las B
    Matrix (*func)(const Matrix);  //Puntero a una Funcion que devulve una
matriz sen y cos
    //Matrix m_Der;             //Matriz donde se guarda los senos y los cosenos
de wt valarray<double> m_solution;   //Vector donde se van a gurdar las
soluciones valarray<double> m_b;          //Vector donde se va a guardar el lado
derecho de las ecuaciones

public:
    MinSqr(valarray<double> &measurement, Matrix &w,Matrix funk(const Matrix));
};*/

#endif // MINSQR_H
