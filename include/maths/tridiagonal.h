#ifndef TRIDIAGONAL_H
#define TRIDIAGONAL_H

#include "matrix.h"

class Tridiagonal
{
private:
    size_t n;
    valarray<double> mdiag;
    valarray<double> udiag;
    valarray<double> ldiag;
public:
    Tridiagonal(const Matrix &a);
    //Tridiagonal(const valarray<double> &main_diagonal,const valarray<double> &upper_diagonal,const valarray<double> &lower_diagonal);

    void solve(const valarray<double> &vb, valarray<double> &vx);
    void solve(const NumericalVector &nvb, NumericalVector &nvx);

    ~Tridiagonal(){}
};

#endif // TRIDIAGONAL_H
