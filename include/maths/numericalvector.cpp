#include "numericalvector.h"


NumericalVector::NumericalVector(size_t size){
    v = new valarray<double>(size);
}

NumericalVector::NumericalVector(const double &val, size_t size){
    v = new valarray<double>(val,size);
}
NumericalVector::NumericalVector(const NumericalVector &nv){
    v = new valarray<double>(nv.size());

    *v = (*(nv.v));
}
NumericalVector::NumericalVector(const valarray<double> &vv){
    v = new valarray<double>(vv);
}

NumericalVector& NumericalVector::operator =(const NumericalVector& nv){

    if (this == &nv) return *this;

    delete v;

    v = new valarray<double>(nv.size());

    *v = (*(nv.v));
    return *this;
}
NumericalVector& NumericalVector::operator =(const valarray<double> &vv){
    *v = vv;
    return *this;
}

void NumericalVector::operator +=(const NumericalVector &nv){
    if (this->size() == nv.size()){
        *v+=nv.getValarray();
    }

}
void NumericalVector::operator -=(const NumericalVector &nv){
    if (this->size() == nv.size()){
        *v-=nv.getValarray();
    }
}

double  NumericalVector::Length() const{
    double r=0;
   for (uint i=0; i < this->size();++i){
       r+=pow((*v)[i],2);
   }
   return sqrt(r);
}

double NumericalVector::Length(const NumericalVector &nv)  {
   double r=0;
   for (uint i=0; i < nv.size();++i){
       r+=pow(nv[i],2);
   }
   return sqrt(r);
}


NumericalVector::~NumericalVector()
{

}
//--------------------------------------------------------------
NumericalVector operator +(const NumericalVector &nv1, const NumericalVector &nv2){

    if (nv1.size() == nv2.size()){
        NumericalVector r(nv1);
        r+=nv2;
        return r;
    }else throw Error("Bad size in vector sum");

}
NumericalVector operator -(const NumericalVector &nv1, const NumericalVector &nv2){
    if (nv1.size() == nv2.size()){
        NumericalVector r(nv1);
        r+=nv2;
        return r;
    }else throw Error("Bad size in vector rest");
}

NumericalVector operator *(const double &scalar, const NumericalVector &nv2){
    NumericalVector r(nv2);
    r*=scalar;
    return r;
}
double operator *(const NumericalVector &nv1, const NumericalVector &nv2){
    if (nv1.size() == nv2.size()){
        double r = 0;
        for (size_t i = 0; i < nv1.size(); ++i){
            r+=nv1[i]*nv2[i];
        }
        return r;
    }else throw Error("Incompatible arrays sizes.");
}
double angle_cos(const NumericalVector &nv1, const NumericalVector &nv2){
    return nv1*nv2/(nv1.Length()*nv2.Length());
}
double angle(const NumericalVector &nv1, const NumericalVector &nv2){
    return acos(angle_cos(nv1,nv2));
}
