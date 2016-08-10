#include "tridiagonal.h"

Tridiagonal::Tridiagonal(const Matrix &a): n(a.dim1()), mdiag(n), udiag(n-1), ldiag(n-1){
    if (!(a.isTridiagonal())) throw Error("Tridiagonal: La matriz no es tridiagonal.");
    //n = a.dim1();

    //mdiag(n);
    //udiag(n-1);
    //ldiag(n-1);

    for (size_t i = 0; i < n; ++i){
        mdiag[i] = a[i][i];
        if (i < n-1) udiag[i] = a[i][i+1];
        if (i > 0) ldiag[i-1] = a[i][i-1];

        /*cout <<"( "<< mdiag[i] << ", ";
        if (i < n-1) cout << ldiag[i] <<", " << udiag[i] <<" )"<<endl;*/
    }

}
/*Tridiagonal::Tridiagonal(const valarray<double> &main_diagonal, const valarray<double> &upper_diagonal, const valarray<double> &lower_diagonal)
    : n(main_diagonal.size()), mdiag(main_diagonal), udiag(upper_diagonal), ldiag(lower_diagonal)
{
    //n = main_diagonal.size();
    if (upper_diagonal.size() != n-1 || lower_diagonal.size() != n-1) throw Error("Tridiagonal: Bad array size.");

    //mdiag(main_diagonal);
    //udiag(upper_diagonal);
    //ldiag(lower_diagonal);
}*/

void Tridiagonal::solve(const valarray<double> &vb, valarray<double> &vx){
    int i;

    if (vb.size()!=n) throw Error("Tridiagonal::solve : Bad size.");

    if (mdiag[0] == 0.0) throw Error("Tridiagonal::solve : First element of the main diagonal equal to 0.0.");

    vx = vb;

    ldiag[0] /= mdiag[0];

    for (i = 1; i < n; ++i){

        mdiag[i] -= udiag[i-1]*ldiag[i-1];
        if (i < n-1) ldiag[i] /= mdiag[i];

        if (mdiag[i] == 0.0) throw Error("Tridiagonal::solve: Diagonal element equal to 0.0.");

        vx[i] -= vx[i-1]*ldiag[i-1];

        //cout << mdiag[i-1] <<endl;
        //cout << udiag[i-1] <<endl;
        //cout << ldiag[i-1] <<endl;

    }

    vx[n-1] /= mdiag[n-1];

    for (i = n-2; i >= 0; --i){
        vx[i] = ( vx[i] - vx[i+1]*udiag[i])/mdiag[i];
    }


}

void Tridiagonal::solve(const NumericalVector &nvb, NumericalVector &nvx){
    valarray<double> vb(nvb.getValarray());
    valarray<double> vx(nvx.getValarray());

    solve(vb,vx);

    nvx = vx;
}


