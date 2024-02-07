#ifndef MATRIX_H
#define MATRIX_H

// #include "numericalvector.h"
#include "numericalvector.h"
#include "slice_iter.h"

class Matrix {
private:
  valarray<double> *v;
  size_t d1, d2;

public:
  Matrix();
  Matrix(size_t x, size_t y, double value = 0.0);
  Matrix(const Matrix &M1);
  Matrix &operator=(const Matrix &M1);
  ~Matrix() {}

  size_t size() const { return d1 * d2; }
  size_t dim1() const { return d1; }
  size_t dim2() const { return d2; }

  void resize(int x, int y, double val = 0.0);

  Slice_iter<double> row(size_t i);
  CSlice_iter<double> row(size_t i) const;

  Slice_iter<double> column(size_t i);
  CSlice_iter<double> column(size_t i) const;

  double &operator()(size_t x, size_t y); // FORTRAN STYLE SUBSCRIPTING
  double operator()(size_t x, size_t y) const;

  Slice_iter<double> operator()(size_t i) { return row(i); }
  CSlice_iter<double> operator()(size_t i) const { return row(i); }

  Slice_iter<double> operator[](size_t i) {
    return row(i);
  } // C style subscripting
  CSlice_iter<double> operator[](size_t i) const { return row(i); }

  Matrix &operator*=(double);
  Matrix &operator+=(const Matrix &m);
  Matrix &operator-=(const Matrix &m);

  valarray<double> &array() { return *v; }
  valarray<double> &array() const { return *v; }

  void ampMatrix(const valarray<double> &v);
  void ampMatrix(const NumericalVector &nv);
  void ampMatrix(const Matrix &m);

  Matrix &transpose();

  void swapRows(size_t x, size_t y);
  void swapColumns(size_t x, size_t y);

  bool isSymetric() const;
  bool isTridiagonal() const;
  bool isSquare() const { return dim1() == dim2(); }
};

// Function definitions---------------------------------

inline Slice_iter<double> Matrix::row(size_t i) {
  return Slice_iter<double>(v, slice(i, d2, d1));
}

inline CSlice_iter<double> Matrix::row(size_t i) const {
  return CSlice_iter<double>(v, slice(i, d2, d1));
}

inline Slice_iter<double> Matrix::column(size_t i) {
  return Slice_iter<double>(v, slice(i * d1, d1, 1));
}

inline CSlice_iter<double> Matrix::column(size_t i) const {
  return CSlice_iter<double>(v, slice(i * d1, d1, 1));
}

inline Matrix &Matrix::operator*=(double d) {
  (*v) *= d;
  return *this;
}
inline Matrix &Matrix::operator+=(const Matrix &m) {
  if (this->dim1() == m.dim1() && this->dim2() == m.dim2()) {
    this->array() += m.array();
    return *this;
  } else
    throw Error("Bad size in matrix sum.");
}
inline Matrix &Matrix::operator-=(const Matrix &m) {
  if (this->dim1() == m.dim1() && this->dim2() == m.dim2()) {
    this->array() -= m.array();
    return *this;
  } else
    throw Error("Bad size in matrix rest.");
}
//-----------------------------------------------------------------------

// Multiplication
// functions-------------------------------------------------------------

inline double mul(const valarray<double> &v1, const valarray<double> &v2) {
  if (v1.size() == v2.size()) {
    double r = 0;
    for (size_t i = 0; i < v1.size(); ++i)
      r += v1[i] * v2[i];
    return r;
  } else
    throw Error("Bad valarray size valarray-valarray multiplication.");
}

inline valarray<double> mul(const Matrix &m, const CSlice_iter<double> &sI) {
  if (m.dim2() == sI.s.size()) {
    valarray<double> r(m.dim1());
    for (size_t i = 0; i < m.dim2(); ++i) {
      r += (sI.ref(i) * m.column(i));
    }
    return r;
  } else
    throw Error("Bad size in Matrix-CSlice_iter multiplication");
}

inline valarray<double> mul(const Matrix &m, const valarray<double> &v) {
  if (m.dim2() == v.size()) {
    valarray<double> r(m.dim1());
    for (size_t i = 0; i < m.dim2(); ++i)
      r += (v[i] * m.column(i));

    return r;
  } else
    throw Error("Bad size in Matrix-valarray multiplication.");
}

inline NumericalVector mul(const Matrix &m, const NumericalVector &nv) {
  return NumericalVector(mul(m, nv.getValarray()));
}

inline Matrix mul(const Matrix &m1, const Matrix &m2) {
  if (m1.dim2() == m2.dim1()) {
    Matrix P(m1.dim1(), m2.dim2());
    for (size_t i = 0; i < P.dim2(); ++i) {
      for (size_t j = 0; j < P.dim1(); ++j) {
        P.column(i)[j] = mul(m1, m2.column(i))[j];
      }
    }
    return P;
  } else
    throw Error("Bad size in Matrix-Matrix multiplication.");
}

//-------------------------------------------------------------------------------

// Operators overload for
// multiplication------------------------------------------

inline Matrix operator*(double d, const Matrix &m) {
  Matrix R(m);
  R *= d;
  return R;
}

inline valarray<double> operator*(const Matrix &m, const valarray<double> v) {
  return mul(m, v);
}

inline NumericalVector operator*(const Matrix &m, const NumericalVector nv) {
  return mul(m, nv);
}

inline Matrix operator*(const Matrix &m1, const Matrix &m2) {
  return mul(m1, m2);
}

// Operator overload for sum and rest of
// matrices----------------------------------

inline Matrix operator+(const Matrix &m1, const Matrix &m2) {
  Matrix S(m1);
  S += m2;

  return S;
}
inline Matrix operator-(const Matrix &m1, const Matrix &m2) {
  Matrix S(m1);
  S -= m2;

  return S;
}

//-------------------------------------------------------------------------------

// Other
// Functions----------------------------------------------------------------
Matrix createIdentityMatrix(size_t n); // return a identity Matrix

Matrix ampMatrix(const Matrix &m, const valarray<double> &v);
Matrix ampMatrix(const Matrix &m, const NumericalVector &nv);
Matrix
ampMatrix(const Matrix &m1,
          const Matrix &m2); // return a amp matrix with m1 and m2 elements

Matrix transpose(const Matrix &m);

bool operator==(const Matrix &a, const Matrix &b);
bool operator!=(const Matrix &a, const Matrix &b);

#endif // MATRIX_H
