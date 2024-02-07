#ifndef LUDCMP_H
#define LUDCMP_H

#include "matrix.h"

class LUdcmp {
private:
  Matrix lu; // Store the decomposition
  size_t n;
  valarray<int> indx; // stores the permutations.
  double d;           // used by det().

  Matrix &aref; // just used by mprove
public:
  LUdcmp(Matrix &a);
  void solve(valarray<double> &b,
             valarray<double> &x); // solve for a single right side
  void solve(NumericalVector &b, NumericalVector &x);
  void solve(Matrix &b, Matrix &x); // solve for multiple right side

  Matrix inverse(); // a inverse.
  double det();     // return determinant of a

  void mprove(valarray<double> &b, valarray<double> &x); //
  void mprove(NumericalVector &b, NumericalVector &x);

  Matrix getMatrixLU() const { return lu; }

  ~LUdcmp() {}
};

#endif // LUDCMP_H
