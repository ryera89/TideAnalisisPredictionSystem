#ifndef FFT_H
#define FFT_H

#include <QVector>
#include <cmath>
#include <complex>
#include <vector>

using namespace std;

void four1(double *data, const int n, const int isign);

struct WrapVecDoub { // Vector
  vector<double> vvec;
  vector<double> &v;
  int n;
  int mask;

  WrapVecDoub(const int nn) : vvec(nn), v(vvec), n(nn / 2), mask(n - 1) {
    validate();
  }

  void validate() {
    if (n & (n - 1))
      throw("vec size must be power of 2.");
  }

  inline complex<double> &operator[](int i) {
    return (complex<double> &)v[(i & mask) << 1];
  }

  inline double &real(int i) { return v[(i & mask) << 1]; }

  inline double &imag(int i) { return v[((i & mask) << 1) + 1]; }

  operator vector<double> &() { return v; }
};

struct WrapQVecDoub { // QVector
  QVector<double> vvec;
  QVector<double> &v;
  int n;
  int mask;

  WrapQVecDoub(const int nn) : vvec(nn), v(vvec), n(nn / 2), mask(n - 1) {
    validate();
  }

  void validate() {
    if (n & (n - 1))
      throw("vec size must be power of 2.");
  }

  inline complex<double> &operator[](int i) {
    return (complex<double> &)v[(i & mask) << 1];
  }

  inline double &real(int i) { return v[(i & mask) << 1]; }

  inline double &imag(int i) { return v[((i & mask) << 1) + 1]; }

  operator QVector<double> &() { return v; }
};
#endif // FFT_H
