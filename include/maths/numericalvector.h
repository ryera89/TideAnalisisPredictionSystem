#ifndef NUMERICALVECTOR_H
#define NUMERICALVECTOR_H


#include <valarray>
#include <string>
#include <iostream>
#include <cmath>




typedef unsigned int uint;

using namespace std;

//typedef unsigned int uint;

class Error{
public:
  Error(const string &error){cout << error << endl;}
};

class NumericalVector
{

private:

  valarray<double>* v;

public:
  NumericalVector(size_t size);
  NumericalVector(const double &val, size_t size);
  NumericalVector(const valarray<double> &vv);

  NumericalVector(const NumericalVector& nv);
  NumericalVector& operator =(const NumericalVector& nv);
  NumericalVector& operator =(const valarray<double>& vv);

  size_t size() const {return v->size();}

  double Max(){return v->max();}
  double Min(){return v->min();}
  double Sum(){return v->sum();}

  valarray<double> getValarray() const {return *v;}

 void operator *=(const double &scalar){*v *= scalar;}
 void operator +=(const NumericalVector &nv);
 void operator -=(const NumericalVector &nv);

double Length() const;
double static Length(const NumericalVector &nv);

  double operator [](size_t i) const {return (*v)[i];}
  double& operator [](size_t i) {return (*v)[i];}

    ~NumericalVector();
};

NumericalVector operator +(const NumericalVector &nv1, const NumericalVector &nv2);
NumericalVector operator -(const NumericalVector &nv1, const NumericalVector &nv2);
NumericalVector operator *(const double &scalar, const NumericalVector &nv);
double operator *(const NumericalVector &nv1, const NumericalVector &nv2);

double angle_cos(const NumericalVector &nv1, const NumericalVector &nv2);
double angle(const NumericalVector&nv1, const NumericalVector &nv2);
#endif // NUMERICALVECTOR_H
