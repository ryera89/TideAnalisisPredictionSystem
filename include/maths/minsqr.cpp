#include "minsqr.h"
#include "ludcmp.h"

/*Matrix function(const Matrix m){
    int row = 2*m.dim1();
    int column = m.dim2();
    Matrix Resp(row,column);

    for (int i = 0; i < m.dim1(); ++i){
        for (int j = 0; j < column; ++j){
            Resp[i][j] = cos(m[i][j]);
        }
    }
    for (int i = 0; i < m.dim1(); ++i){
        for (int j = 0; j < column; ++j){
            Resp[i+m.dim1()][j] = sin(m[i][j]);
        }
    }
    return Resp;
}

MinSqr::MinSqr(valarray<double> &measurement, Matrix &w, Matrix funk(const Matrix)):m_measurement(measurement), m_w(w), func(funk)
{
    m_nData = measurement.size();
    m_nHarmonicConstants = w.size();
    Matrix m_t(1,m_nData);
    for (int i = 0; i < m_nData; ++i) m_t[i][0] = i; //Asignamos los valores de t desde 0 - N-1

    Matrix m_Der = func(m_w*m_t);


    m_b = m_Der*m_measurement;  // M*Derivada es el vector de la derecha

    Matrix NormaEq = m_Der*transpose(m_Der);

    LUdcmp Lu(NormaEq);

    Lu.solve(m_b,m_solution);

    for (int i = 0; i < m_solution.size(); ++i){
        cout << m_solution[i] <<", ";
    }


}*/

MinSqr::MinSqr(valarray<double> &x, valarray<double> &y, valarray<double> &sig, QVector<double> funks(const double &)): m_nData(x.size()), m_x(x),
  m_y(y), m_sig(sig), funcs(funks)
{
    m_nParam = funcs(m_x[0]).size();
    a.resize(m_nParam);
    m_covar.resize(m_nParam,m_nParam);        //Resize the covariant matrix to m_nParam
    ia.resize(m_nParam);
    for (int i = 0; i < m_nParam; ++i) ia[i] = true;     //Por defecto no hay parametros fijos
}

void MinSqr::fitGJ()
{
    int mfit = 0;  //contador de los parametros libres
    QVector<double> afunc(m_nParam);    //Qvector en el cual se guardan las filas de la matriz diseno
    double ym;

    for (int j = 0; j < m_nParam; ++j)
        if (ia[j]) mfit++;

    if (mfit == 0) throw("MinSqr::fitGJ: No hay parametros para der ajustados.");

    Matrix  temp(m_nData,mfit); //Matrix Diseno
    Matrix beta(m_nData,1); //right hand matrix

    for (int i = 0; i < m_nData; ++i){
        afunc = funcs(m_x[i]);
        ym = m_y[i];
        if (mfit < m_nParam){
            for (int j = 0; j < m_nParam; ++j){
                if (!ia[j]){
                    ym -= a[j]*afunc[j];       //Restando de la medicion el parametro fijo
                    afunc.removeAt(j);         //Quita el parametro fijo del vector
                }
            }
        }
        for (int j = 0; j < mfit; ++j) afunc[j]/=m_sig[i];  //dividiendo entre la varianza de la medicion i

        ym/=m_sig[i];
        beta[i][0] = ym;

        for (int j = 0; j < mfit; ++j){
            temp[i][j] = afunc[j];                       //Creando la matriz diseno
        }
    }
    beta = transpose(temp)*beta;     // (transpuesta de A)* b
    temp = transpose(temp)*temp;     //(transpuesta de A)*A

    gauss_jordan(temp,beta);

    int j = 0;
    for (int l = 0; l < m_nParam; ++l){
        if (ia[l]){
            a[l] = beta[j++][0];  //Poniendo la solucion en la posicion correcta.
        }
    }

    m_chisq = 0.0;
    for (int i = 0; i < m_nData; ++i){    //Hayando chi cuadrado
        afunc = funcs(m_x[i]);
        double sum = 0.0;
        for (int j = 0; j < m_nParam; ++j){
            sum += a[j]*afunc[j];
        }
        m_chisq += pow((m_y[i]-sum)/m_sig[i],2);
    }

    for (int i = 0; i < mfit; ++i){      //Poniendo la matris covariante
        for (int j = 0; j < mfit; ++j){
            m_covar[i][j] = temp[i][j];
        }
    }

    if (mfit < m_nParam){    //Si existen parametros fijos
        int k = mfit - 1;

        for (int j = m_nParam - 1;j >= 0; --j){   //Reordenando la matriz covariante
           if (ia[j]){
              for (int i = 0; i < m_nParam; ++i) std::swap(m_covar[i][k],m_covar[i][j]);
              for (int i = 0; i < m_nParam; ++i) std::swap(m_covar[k][i],m_covar[j][i]);

              --k;
          }
        }
    }


}

void MinSqr::fitLU()
{
    int mfit = 0;  //contador de los parametros libres
    QVector<double> afunc(m_nParam);    //Qvector en el cual se guardan las filas de la matriz diseno
    double ym;

    for (int j = 0; j < m_nParam; ++j)
        if (ia[j]) mfit++;

    if (mfit == 0) throw("MinSqr::fitGJ: No hay parametros para der ajustados.");

    Matrix  temp(m_nData,mfit); //Matrix Diseno
    Matrix beta(m_nData,1); //right hand matrix

    for (int i = 0; i < m_nData; ++i){
        afunc = funcs(m_x[i]);
        ym = m_y[i];
        if (mfit < m_nParam){
            for (int j = 0; j < m_nParam; ++j){
                if (!ia[j]){
                    ym -= a[j]*afunc[j];       //Restando de la medicion el parametro fijo
                    afunc.removeAt(j);         //Quita el parametro fijo del vector
                }
            }
        }
        for (int j = 0; j < mfit; ++j) afunc[j]/=m_sig[i];  //dividiendo entre la varianza de la medicion i

        ym/=m_sig[i];
        beta[i][0] = ym;

        for (int j = 0; j < mfit; ++j){
            temp[i][j] = afunc[j];                       //Creando la matriz diseno
        }
    }
    beta = transpose(temp)*beta;     // (transpuesta de A)* b
    temp = transpose(temp)*temp;     //(transpuesta de A)*A

    LUdcmp LU(temp);

    LU.solve(beta,beta);

    int j = 0;
    for (int l = 0; l < m_nParam; ++l){
        if (ia[l]){
            a[l] = beta[j++][0];  //Poniendo la solucion en la posicion correcta.
        }
    }

    m_chisq = 0.0;
    for (int i = 0; i < m_nData; ++i){    //Hayando chi cuadrado
        afunc = funcs(m_x[i]);
        double sum = 0.0;
        for (int j = 0; j < m_nParam; ++j){
            sum += a[j]*afunc[j];
        }
        m_chisq += pow((m_y[i]-sum)/m_sig[i],2);
    }

    /*for (int i = 0; i < mfit; ++i){      //Poniendo la matris covariante
        for (int j = 0; j < mfit; ++j){
            m_covar[i][j] = temp[i][j];
        }
    }

    if (mfit < m_nParam){    //Si existen parametros fijos
        int k = mfit - 1;

        for (int j = m_nParam - 1;j >= 0; --j){   //Reordenando la matriz covariante
           if (ia[j]){
              for (int i = 0; i < m_nParam; ++i) std::swap(m_covar[i][k],m_covar[i][j]);
              for (int i = 0; i < m_nParam; ++i) std::swap(m_covar[k][i],m_covar[j][i]);

              --k;
          }
        }
    }*/
}

void MinSqr::fitLikeTheBook()
{
    int i,j,k,l,m,mfit = 0;
    double ym,wt,sum,sig2i;
    QVector<double> afunc(m_nParam);

    for (j = 0; j < m_nParam; j++) if (ia[j]) mfit++;

    if (mfit == 0) throw("MinSqr::fitGJ: No hay parametros para der ajustados.");

    Matrix temp(mfit,mfit);
    Matrix beta(mfit,1);

    for (i=0;i<m_nData;i++) {     //Loop over data to accumulate coefficients of the normal equations.
        afunc = funcs(m_x[i]);
        ym=m_y[i];
        if (mfit < m_nParam) {         //Subtract off dependences on known pieces of the fitting function.
            for (j=0;j<m_nParam;j++)
                if (!ia[j]) ym -= a[j]*afunc[j];
        }
        sig2i=1.0/pow(m_sig[i],2);
        for (j=0,l=0;l<m_nParam;l++) {   //Set up matrix and r.h.s. for matrix inversion.
            if (ia[l]) {
                wt=afunc[l]*sig2i;
                for (k=0,m=0;m<=l;m++)
                    if (ia[m]) temp[j][k++] += wt*afunc[m];
                beta[j++][0] += ym*wt;
            }
        }
    }
    for (j=1;j<mfit;j++) for (k=0;k<j;k++) temp[k][j]=temp[j][k];
    gauss_jordan(temp,beta);
                                                   //Matrix solution.
    for (j=0,l=0;l<m_nParam;l++) if (ia[l]) a[l]=beta[j++][0];

    m_chisq=0.0;
    for (i=0;i<m_nData;i++) {
        afunc = funcs(m_x[i]);
        sum=0.0;
        for (j=0;j<m_nParam;j++) sum += a[j]*afunc[j];
        m_chisq += pow(((m_y[i]-sum)/m_sig[i]),2);
    }
    for (j=0;j<mfit;j++) for (k=0;k<mfit;k++) m_covar[j][k]=temp[j][k];
    for (i=mfit;i<m_nParam;i++)                        //Rearrange covariance matrix into the correct  order.
        for (j=0;j<i+1;j++) m_covar[i][j]=m_covar[j][i]=0.0;

    k=mfit-1;
    for (j=m_nParam-1;j>=0;j--) {
        if (ia[j]) {
            for (i=0;i<m_nParam;i++) std::swap(m_covar[i][k],m_covar[i][j]);
            for (i=0;i<m_nParam;i++) std::swap(m_covar[k][i],m_covar[j][i]);
            k--;
        }

    }

}
