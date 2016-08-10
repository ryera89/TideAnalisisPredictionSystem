#include "ludcmp.h"

inline void saveScalingFactor(Matrix &a, valarray<double> &scalingReg){
    double big, temp;
    for (size_t i = 0; i < a.dim1(); ++i){
        big = 0.0;
        for (size_t j = 0; j < a.dim1(); ++j)
            if ((temp = abs(a.column(i)[j])) > big) big = temp;
        if (big == 0) throw Error("Singular Matrix in LU decomposition.");
        scalingReg[i] = 1.0/big;                                               //save the scaling
    }
}

LUdcmp::LUdcmp(Matrix &a):lu(a), n(a.dim1()), indx(n), aref(a){
    //const double tiny = 1.0e-40;       //a small number
    size_t i, imax, j, k;

    double big, temp;
    //valarray<double> vv(n);
    d = 1.0;

   // saveScalingFactor(lu,vv);                        //for scaling factor.

    for (k = 0; k < n; ++k){
        big = 0.0;
        for (i = k; i < n; ++i){                       //seek pivot
            temp = abs(lu.column(k)[i]);               //if we implement pivot with scaling factor temp = vv[i]*abs(lu.column(k)[i])
            if (temp > big){
                big = temp;
                imax = i;                              //save pivot index
            }
        }
        if (k != imax){                       //If we need interchange rows
            lu.swapRows(imax,k);              //Yes then do it
            d = -d;                           //Change parity
            //swap(vv[imax],vv[k]);             //interchange scaling factor
        }
        indx[k] = imax;

        //Change 0.0 mby tiny for some singular matrix ops

        for (i = k + 1; i < n; ++i){
            temp = lu.column(k)[i]/=lu[k][k];
            for (j = k+1; j < n; ++j)
                lu[i][j]-=temp*lu[k][j];
        }

    }
}
void LUdcmp::solve(valarray<double> &vb, valarray<double> &vx){

    int i, ii = 0, ip, j;
    double sum;

    if (vb.size() != n) throw Error("ludcmp::solve: Bad sizes.");
    vx = vb;

    for (i = 0; i < n; ++i){
        ip = indx[i];              //REordering equations because row interchanges in LUdcmp
        sum = vx[ip];
        vx[ip] = vx[i];

        if (ii!=0)
            for (j = ii-1; j < i; ++j) sum -= lu[i][j]*vx[j];
        else if (sum != 0.0)        //A nonzero element was found so we must do the sum.
            ii=i+1;

        vx[i] = sum;

    }
    for (i = n-1; i >=0; --i){    //Backsubstitution
        sum = vx[i];
        for (j = i+1; j < n; ++j) sum -= lu[i][j]*vx[j];

        vx[i] = sum/lu[i][i];
    }

}
void LUdcmp::solve(NumericalVector &nvb, NumericalVector &nvx){
    valarray<double> vb(nvb.getValarray());
    valarray<double> vx(nvx.getValarray());
    solve(vb,vx);
    nvx = vx;
}
void LUdcmp::solve(Matrix &b, Matrix &x){
    size_t m = b.dim1();
    size_t n = b.dim2();
    x = b;
    valarray<double> xx(m);

    for (size_t j = 0; j < n; ++j ){
        for (size_t i = 0; i < m; ++i){
            xx[i] = b.column(j)[i];
        }
        solve(xx,xx);
        for (size_t i = 0; i < m; ++i) x.column(j)[i] = xx[i];

    }
}

Matrix LUdcmp::inverse(){
    Matrix I = createIdentityMatrix(lu.dim1());
    solve(I,I);
    return I;
}
double LUdcmp::det(){
    double dd = d;
    for (size_t i = 0; i < n; ++i) dd*=lu[i][i];

    return dd;
}
void LUdcmp::mprove(valarray<double> &b, valarray<double> &x){
    size_t i, j;
    valarray<double> r(n);

    for (i = 0; i < n; ++i){
        long double sdp = -b[i];
        for (j = 0; j < n; ++j) sdp+=(long double)aref[i][j]*(long double)x[j];

        r[i] = sdp;
    }

    solve(r,r);

    x-=r;
}
void LUdcmp::mprove(NumericalVector &b, NumericalVector &x){
    valarray<double> vb = b.getValarray();
    valarray<double> vx = x.getValarray();

    mprove(vb,vx);

    x = vx;
}
