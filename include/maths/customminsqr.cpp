#include "customminsqr.h"

CustomMinSqr::CustomMinSqr(
    valarray<double> &x, valarray<double> &y, valarray<double> &sig,
    const QVector<QDateTime> &datetimeVector,
    QVector<double> funks(const double &, const QDateTime &, const QDateTime &))
    : m_nData(x.size()), m_x(x), m_y(y), m_sig(sig),
      m_dateTimeVector(datetimeVector), funcs(funks) {
  m_nParam =
      funcs(m_x[0], m_dateTimeVector.at(0), m_dateTimeVector.at(0)).size();
  a.resize(m_nParam);
  m_covar.resize(m_nParam, m_nParam); // Resize the covariant matrix to m_nParam
  ia.resize(m_nParam);
  for (int i = 0; i < m_nParam; ++i)
    ia[i] = true; // Por defecto no hay parametros fijos
}

void CustomMinSqr::fitGJ() {
  int mfit = 0; // contador de los parametros libres
  QVector<double> afunc(
      m_nParam); // Qvector en el cual se guardan las filas de la matriz diseno
  double ym;

  for (int j = 0; j < m_nParam; ++j)
    if (ia[j])
      mfit++;

  if (mfit == 0)
    throw("MinSqr::fitGJ: No hay parametros para der ajustados.");

  Matrix temp(m_nData, mfit); // Matrix Diseno
  Matrix beta(m_nData, 1);    // right hand matrix

  for (int i = 0; i < m_nData; ++i) {
    afunc = funcs(m_x[i], m_dateTimeVector.at(i), m_dateTimeVector.at(0));
    ym = m_y[i];
    if (mfit < m_nParam) {
      for (int j = 0; j < m_nParam; ++j) {
        if (!ia[j]) {
          ym -= a[j] * afunc[j]; // Restando de la medicion el parametro fijo
          afunc.removeAt(j);     // Quita el parametro fijo del vector
        }
      }
    }
    for (int j = 0; j < mfit; ++j)
      afunc[j] /= m_sig[i]; // dividiendo entre la varianza de la medicion i

    ym /= m_sig[i];
    beta[i][0] = ym;

    for (int j = 0; j < mfit; ++j) {
      temp[i][j] = afunc[j]; // Creando la matriz diseno
    }
  }
  beta = transpose(temp) * beta; // (transpuesta de A)* b
  temp = transpose(temp) * temp; //(transpuesta de A)*A

  gauss_jordan(temp, beta);

  int j = 0;
  for (int l = 0; l < m_nParam; ++l) {
    if (ia[l]) {
      a[l] = beta[j++][0]; // Poniendo la solucion en la posicion correcta.
    }
  }

  m_chisq = 0.0;
  for (int i = 0; i < m_nData; ++i) { // Hayando chi cuadrado
    afunc = funcs(m_x[i], m_dateTimeVector.at(i), m_dateTimeVector.at(0));
    double sum = 0.0;
    for (int j = 0; j < m_nParam; ++j) {
      sum += a[j] * afunc[j];
    }
    m_chisq += pow((m_y[i] - sum) / m_sig[i], 2);
  }

  for (int i = 0; i < mfit; ++i) { // Poniendo la matris covariante
    for (int j = 0; j < mfit; ++j) {
      m_covar[i][j] = temp[i][j];
    }
  }

  if (mfit < m_nParam) { // Si existen parametros fijos
    int k = mfit - 1;

    for (int j = m_nParam - 1; j >= 0; --j) { // Reordenando la matriz
                                              // covariante
      if (ia[j]) {
        for (int i = 0; i < m_nParam; ++i)
          std::swap(m_covar[i][k], m_covar[i][j]);
        for (int i = 0; i < m_nParam; ++i)
          std::swap(m_covar[k][i], m_covar[j][i]);

        --k;
      }
    }
  }
}

void CustomMinSqr::fitLU() {
  int mfit = 0; // contador de los parametros libres
  QVector<double> afunc(
      m_nParam); // Qvector en el cual se guardan las filas de la matriz diseno
  double ym;

  for (int j = 0; j < m_nParam; ++j)
    if (ia[j])
      mfit++;

  if (mfit == 0)
    throw("MinSqr::fitGJ: No hay parametros para der ajustados.");

  Matrix temp(m_nData, mfit); // Matrix Diseno
  Matrix beta(m_nData, 1);    // right hand matrix

  for (int i = 0; i < m_nData; ++i) {
    afunc = funcs(m_x[i], m_dateTimeVector.at(i), m_dateTimeVector.at(0));
    ym = m_y[i];
    if (mfit < m_nParam) {
      for (int j = 0; j < m_nParam; ++j) {
        if (!ia[j]) {
          ym -= a[j] * afunc[j]; // Restando de la medicion el parametro fijo
          afunc.removeAt(j);     // Quita el parametro fijo del vector
        }
      }
    }
    for (int j = 0; j < mfit; ++j)
      afunc[j] /= m_sig[i]; // dividiendo entre la varianza de la medicion i

    ym /= m_sig[i];
    beta[i][0] = ym;

    for (int j = 0; j < mfit; ++j) {
      temp[i][j] = afunc[j]; // Creando la matriz diseno
    }
  }
  beta = transpose(temp) * beta; // (transpuesta de A)* b
  temp = transpose(temp) * temp; //(transpuesta de A)*A

  LUdcmp LU(temp);

  LU.solve(beta, beta);

  int j = 0;
  for (int l = 0; l < m_nParam; ++l) {
    if (ia[l]) {
      a[l] = beta[j++][0]; // Poniendo la solucion en la posicion correcta.
    }
  }

  m_chisq = 0.0;
  for (int i = 0; i < m_nData; ++i) { // Hayando chi cuadrado
    afunc = funcs(m_x[i], m_dateTimeVector.at(i), m_dateTimeVector.at(0));
    double sum = 0.0;
    for (int j = 0; j < m_nParam; ++j) {
      sum += a[j] * afunc[j];
    }
    m_chisq += pow((m_y[i] - sum) / m_sig[i], 2);
  }

  /*for (int i = 0; i < mfit; ++i){      //Poniendo la matris covariante
      for (int j = 0; j < mfit; ++j){
          m_covar[i][j] = temp[i][j];
      }
  }

  if (mfit < m_nParam){    //Si existen parametros fijos
      int k = mfit - 1;

      for (int j = m_nParam - 1;j >= 0; --j){   //Reordenando la matriz
  covariante if (ia[j]){ for (int i = 0; i < m_nParam; ++i)
  std::swap(m_covar[i][k],m_covar[i][j]); for (int i = 0; i < m_nParam; ++i)
  std::swap(m_covar[k][i],m_covar[j][i]);

            --k;
        }
      }
  }*/
}
