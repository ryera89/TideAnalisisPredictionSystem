#include "matrix.h"

// Member Functions DEf-----------------------------------------
Matrix::Matrix(){
    d1 =1;
    d2 =1;
    v = new valarray<double> (1);
}

Matrix::Matrix(size_t x, size_t y, double val){
    //check that x and y are sensible
    d1 = x;
    d2 = y;
    v = new valarray<double>(x*y);

    for (int i = 0; i < v->size(); ++i) v->operator [](i) = val;



}
Matrix::Matrix(const Matrix &M1){
    d1 = M1.d1;
    d2 = M1.d2;

    v = new valarray<double> (d1*d2);

    (*v) = (*(M1.v));
}

void Matrix::ampMatrix(const valarray<double> &v){
    size_t col = v.size()/this->dim1(); //numero de columnas nuevas

    if (!(v.size()%this->dim1())){      //si el tamano del array es un multiplo del numero de filas de la matriz
        valarray<double> aux(d1*(d2+col));
        for (size_t i = 0; i < this->size(); ++i){
            aux[i] = this->array()[i];
        }
        for (size_t i = this->size(); i < aux.size(); ++i){
            aux[i] = v[i-this->size()];
        }
        d2+=col;                                   //se agrega una nueva columna
        this->array() = aux;

    }else throw Error("Bad size in ampMatrix.");
}
void Matrix::ampMatrix(const NumericalVector &nv){
    this->ampMatrix(nv.getValarray());
}

void Matrix::ampMatrix(const Matrix &m){
    this->ampMatrix(m.array());
}

Matrix& Matrix::transpose(){
    Matrix T(d2,d1);

    for (size_t i = 0; i < d1; ++i)
        for (size_t j = 0; j < d2; ++j)
            T.column(i)[j] = this->row(i)[j];

    *this = T;
    return *this;
}

void Matrix::swapRows(size_t x, size_t y){
    if (x < d1 && y < d1){
        for (size_t i = 0; i < d2; ++i)
            swap(column(i)[x],column(i)[y]);
    }else throw Error("Bad size in Row interchange.");
}
void Matrix::swapColumns(size_t x, size_t y){
    if (x < d2 && y < d2){
        for (size_t i = 0; i < d1; ++i)
            swap(row(i)[x],row(i)[y]);
    }else throw Error("Bad size in Column interchange.");
}
bool Matrix::isSymetric() const {

    if (!(this->isSquare())) return false;

    size_t n = this->dim1();

    for (size_t i = 1; i < n; ++i){
        for (size_t j = 1; j < n; ++j){
            if (row(i)[j] != row(j)[i]) return false;
        }
    }
    return true;
}
bool Matrix::isTridiagonal() const{
    if (!(isSquare())) return false;
    size_t n = this->dim1();
    for (size_t i = 0; i < n-2; ++i){
        for (size_t j = i; j < n-2; ++j){
            if ( (column(i)[j+2]!= 0.0) || (column(j+2)[i]!=0.0) ) return false;
        }
    }
    return true;
}

Matrix& Matrix::operator =(const Matrix& M1){

    if (this == &M1) return *this;
        d1 = M1.d1;
        d2 = M1.d2;

        v->resize(d1*d2);

       (*v) = (*(M1.v));

        return *this;
}

void Matrix::resize(int x, int y, double val)
{
    d1 = x;
    d2 = y;

    v->resize(d1*d2);

    for (int i = 0; i < v->size(); ++i) v->operator [](i) = val;
}

double& Matrix::operator ()(size_t x, size_t y){
    return row(x)[y];
}
double Matrix::operator ()(size_t x, size_t y) const{
    return row(x)[y];
}
//-----------------------------------------------------------

//Other Functions definitions---------------------------------

Matrix createIdentityMatrix(size_t n){
    Matrix I(n,n);

    for (size_t i = 0; i < n; ++i){
        for (size_t j = 0; j < n; ++j){
            if (i==j) I.column(i)[j] = 1;
            else I.column(i)[j] = 0;
        }
    }
    return I;
}

Matrix ampMatrix(const Matrix &m, const valarray<double> &v){
    Matrix AM(m);
    AM.ampMatrix(v);
    return AM;
}

Matrix ampMatrix(const Matrix &m, const NumericalVector &nv){
    Matrix AM(m);
    AM.ampMatrix(nv);
    return AM;
}

Matrix ampMatrix(const Matrix &m1, const Matrix &m2){
    Matrix AM(m1);
    AM.ampMatrix(m2);
    return AM;
}

Matrix transpose(const Matrix &m){
    Matrix T(m);

    return T.transpose();
}

bool operator ==(const Matrix &a, const Matrix &b){
    if (a.dim1() != b.dim1() || a.dim2() != b.dim2()) return false;

    for (size_t i = 0; i < a.dim2(); ++i ){
        for (size_t j = 0; j < a.dim1(); ++j){
           if (a.column(i)[j] != b.column(i)[j]) return false;
        }
    }
    return true;
}
bool operator !=(const Matrix &a, const Matrix &b){
    return !(a==b);
}

//------------------------------------------------------------
