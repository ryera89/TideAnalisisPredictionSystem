#include "gauss_jordan.h"

inline void
seekPivot(const Matrix &a, const valarray<int> &pIndReg, size_t &prInd,
          size_t &pcInd) { // funcion para buscar el pivot y guarda los indexes.
  double big = 0.0;
  for (size_t j = 0; j < a.dim1(); ++j)
    if (pIndReg[j] != 1)
      for (size_t k = 0; k < a.dim1(); ++k) {
        if (pIndReg[k] == 0) {
          if (abs(a[j][k]) >= big) {
            big = abs(a[j][k]);
            prInd = j;
            pcInd = k;
          }
        }
      }
}
inline void mulRowbyScalar(Matrix &a, const double &pivinv, size_t x_row) {
  for (size_t j = 0; j < a.dim2(); ++j) {
    a.row(x_row)[j] *= pivinv;
  }
}

inline void reduceRows(Matrix &a, Matrix &b,
                       size_t prInd) { // Reduce las filas excepto la del pivote
  for (size_t j = 0; j < a.dim1(); ++j) {
    if (j != prInd) {
      double dum = a[j][prInd];
      a[j][prInd] = 0.0;
      for (size_t l = 0; l < a.dim2(); ++l)
        a[j][l] -= a[prInd][l] * dum;
      for (size_t l = 0; l < b.dim2(); ++l)
        b[j][l] -= b[prInd][l] * dum;
    }
  }
}

void gauss_jordan(Matrix &a,
                  Matrix &b) { // Gauss-Jordan with full pivoting strategy
  size_t i, pcInd, prInd, n = a.dim1();
  int j;
  double pivinv;
  valarray<int> pcIndReg(0, n), prIndReg(0, n), pIndReg(0, n);

  for (i = 0; i < n; ++i) {
    seekPivot(a, pIndReg, prInd, pcInd);
    ++(pIndReg[pcInd]);
    if (prInd != pcInd) {
      a.swapRows(prInd, pcInd);
      b.swapRows(prInd, pcInd);
    }
    prIndReg[i] = prInd;
    pcIndReg[i] = pcInd;
    if (a[pcInd][pcInd] == 0)
      throw Error("gauss_jordan: Singular Matrix.");
    pivinv = 1.0 / a[pcInd][pcInd];
    a[pcInd][pcInd] = 1.0;

    mulRowbyScalar(a, pivinv, pcInd);
    mulRowbyScalar(b, pivinv, pcInd);

    reduceRows(a, b, pcInd);
  }
  for (j = n - 1; j >= 0; --j) {
    if (prIndReg[j] != pcIndReg[j])
      a.swapColumns(prIndReg[j], pcIndReg[j]);
  }
}
void gauss_jordan(Matrix &a) {
  Matrix b(a.dim1(), 0);
  gauss_jordan(a, b);
}

/*void gauss(Matrix a, Matrix &b){
    size_t i,pcInd,prInd, n = a.dim1();
    int j;
    double pivinv;
    valarray<int> pcIndReg(0,n), prIndReg(0,n), pIndReg(0,n);

    for (i = 0; i < n; ++i){
        seekPivot(a,pIndReg,prInd,pcInd);
        ++(pIndReg[pcInd]);
        if (prInd != pcInd){
            a.swapRows(prInd,pcInd);
            b.swapRows(prInd,pcInd);
        }
        prIndReg[i] = prInd;
        pcIndReg[i] = pcInd;
        if (a[pcInd][pcInd] == 0) throw Error("gauss_jordan: Singular Matrix.");
        pivinv = 1.0/a[pcInd][pcInd];
        a[pcInd][pcInd] = 1.0;

        mulRowbyScalar(a,pivinv,pcInd);
        mulRowbyScalar(b,pivinv,pcInd);

        reduceRows(a,b,pcInd);
    }
    for (j = n-1;j>=0;--j){
        if (prIndReg[j] != pcIndReg[j])
           a.swapColumns(prIndReg[j],pcIndReg[j]);
    }
}*/
