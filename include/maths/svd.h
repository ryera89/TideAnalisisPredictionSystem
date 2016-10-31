#ifndef SVD_H
#define SVD_H

#include "matrix.h"


struct SVD{
    int m,n;
    Matrix u,v;
    valarray<double> w;
    double eps, tsh;
    SVD(Matrix &a);

    void solve(valarray<double> &b, valarray<double> &x, double thresh);
    void solve(Matrix &b,Matrix &x, double thresh);

    int rank(double thresh);
    int nullity(double thresh);

    Matrix range(double thresh);
    Matrix nullspace(double thresh);

    double inv_condition();

    void decompose();
    void reorder();
    double pythag(const double a, const double b);

};

#endif // SVD_H
