#include "matrix.h"
#include "svd.h"
#include <QDateTime>
#include <QVector>

struct Customfitsvd {
  int ndat, ma;
  valarray<double> *x;
  Matrix *xmd;
  valarray<double> &y, &sig;
  valarray<double> a;
  Matrix covar;
  double chisq;
  QVector<QDateTime> m_dateTime;
  QVector<double> (*funcs)(const double &, const QDateTime &,
                           const QDateTime &);
  QVector<double> (*funcsmd)(const valarray<double> &);
  double tol;

  Customfitsvd(valarray<double> &xx, valarray<double> &yy,
               valarray<double> &ssig, const QVector<QDateTime> &dateTime,
               QVector<double> funks(const double &, const QDateTime &,
                                     const QDateTime &),
               const double TOL = 1.e-12)
      : ndat(yy.size()), x(&xx), xmd(NULL), y(yy), sig(ssig),
        m_dateTime(dateTime), funcs(funks), tol(TOL) {}

  void fit() {
    int i, j, k;
    double tmp, thresh, sum;
    if (x)
      ma = funcs((*x)[0], m_dateTime.at(0), m_dateTime.at(0)).size();
    else
      ma = funcsmd(row(*xmd, 0)).size();
    a.resize(ma);
    covar.resize(ma, ma);
    Matrix aa(ndat, ma);
    QVector<double> afunc(ma);
    valarray<double> b(ndat);
    for (i = 0; i < ndat; i++) {
      if (x)
        afunc = funcs((*x)[i], m_dateTime.at(i), m_dateTime.at(0));
      else
        afunc = funcsmd(row(*xmd, i));
      tmp = 1.0 / sig[i];
      for (j = 0; j < ma; j++)
        aa[i][j] = afunc[j] * tmp;
      b[i] = y[i] * tmp;
    }
    SVD svd(aa);
    thresh = (tol > 0. ? tol * svd.w[0] : -1.);
    svd.solve(b, a, thresh);
    chisq = 0.0;
    for (i = 0; i < ndat; i++) {
      sum = 0.;
      for (j = 0; j < ma; j++)
        sum += aa[i][j] * a[j];
      chisq += pow(sum - b[i], 2);
    }
    for (i = 0; i < ma; i++) {
      for (j = 0; j < i + 1; j++) {
        sum = 0.0;
        for (k = 0; k < ma; k++)
          if (svd.w[k] > svd.tsh)
            sum += svd.v[i][k] * svd.v[j][k] / pow(svd.w[k], 2);
        covar[j][i] = covar[i][j] = sum;
      }
    }
  }

  Customfitsvd(Matrix &xx, valarray<double> &yy, valarray<double> &ssig,
               QVector<double> funks(const valarray<double> &),
               const double TOL = 1.e-12)
      : ndat(yy.size()), x(NULL), xmd(&xx), y(yy), sig(ssig), funcsmd(funks),
        tol(TOL) {}

  valarray<double> row(Matrix &a, const int i) {
    int j, n = a.dim2();
    valarray<double> ans(n);
    for (j = 0; j < n; j++)
      ans[j] = a[i][j];
    return ans;
  }
};
