#ifndef NODALFACTORFORMULAS_H
#define NODALFACTORFORMULAS_H
#include <QtMath>

//Formula para el calculo del factor nodal de las componentes lunares de largo periodo Mm y Msf
//f = [2/3-pow(sin(I),2)]/0.5021
double NodalAmplitudeFactor_Mm_Msf(const double &I)
{
    double aux = qSin(qDegreesToRadians(I));

    return (2.0/3.0 - qPow(aux,2))/0.5021;
}
//Formula para el calculo del factor nodal de la componente lunar de largo periodo Mf
//f = pow(sin(I),2)/0.1578
double NodalAmplitudeFactor_Mf(const double &I){

    double aux = qSin(qDegreesToRadians(I));

    return qPow(aux,2)/0.1578;
}
//Formula para el calculo del factor nodal de las componentes lunares diurnas O1,Q1,2Q1,RHO1,SIGMA1,SO3
//f = sin(I)*pow(cos(I/2),2)/0.3800
double NodalAmplitudeFactor_O1_Q1_2Q1_RHO1_SIGMA1_SO3(const double &I){

    double Irad = qDegreesToRadians(I);

    double aux1 = qSin(Irad);
    double aux2 = qPow(qCos(Irad/2),2);

    return aux1*aux2/0.3800;
}
//Formula para el calculo del factor nodal de las componentes lunares diurnas J1,CHI1,THETA1,MP1,SO1
//f = sin(2I)/0.7214
double NodalAmplitudeFactor_J1_CHI1_THETA1_MP1_SO1(const double &I){
    double Irad = qDegreesToRadians(I);

    return qSin(2*Irad)/0.7214;
}
//Formula para el calculo del factor nodal de las componentes lunares diurnas OO1, KQ1
//f = sin(I)*pow(sin(I/2),2)/0.0164
double NodalAmplitudeFactor_OO1_KQ1(const double &I){
    double Irad = qDegreesToRadians(I);

    double aux1 = qSin(Irad);
    double aux2 = qPow(qSin(Irad/2),2);

    return aux1*aux2/0.0164;
}
//Formula para el calculo del factor nodal de la componente diurna M1
//f = sin(I)*pow(cos(I/2),2)/(0.3800*Qa) = f(O1)/Qa
double NodalAmplitudeFactor_M1(const double &I, const double &Qa){
    return NodalAmplitudeFactor_O1_Q1_2Q1_RHO1_SIGMA1(I)/Qa;
}
//Formula para el calculo del factor nodal de la componente diurna K1,SK3
//f = sqrt(0.8965*pow(sin(2I),2)+0.6001*sin(2I)cos(ν) + 0.1006)
double NodalAmplitudeFactor_K1_SK3(const double &I, const double &v){
    double Irad = qDegreesToRadians(I);
    double vrad = qDegreesToRadians(v);

    double aux1 = qPow(qSin(2.0*Irad),2);
    double aux2 = qSin(2.0*Irad)*qCos(vrad);

    return qSqrt(0.8965*aux1 + 0.6001*aux2 + 0.1006);
}
//Formula para el calculo del factor nodal de las componentes lunares semidiurnas M2,N2,2N2,NU2,LAMDA2,MU2,2SM2,MS4,2SM6
//f = pow(cos(I/2),4)/0.9154
double NodalAmplitudeFactor_M2_N2_2N2_NU2_LAMDA2_MU2_2SM2_MS4_2SM6(const double &I){
    double Irad = qDegreesToRadians(I);

    double aux = qPow(qCos(Irad/2.0),4);

    return aux/0.9154;
}
//Formula para el calculo del factor nodal de la componente lunar semidiurna KJ2
//f = pow(sin(I),2)/0.1565
double NodalAmplitudeFactor_KJ2(const double &I){
    double Irad = qDegreesToRadians(I);

    double aux = qPow(qSin(Irad),2);

    return aux/0.1565;

}
//Formula para el calculo del factor nodal de la componente semidiurna L2
//f = pow(cos(I/2),4)/(0.9154*Ra) =  f(M2)/Ra
double NodalAmplitudeFactor_L2(const double &I, const double &Ra){
    double aux = NodalAmplitudeFactor_M2_N2_2N2_NU2_LAMDA2_MU2(I);

    return aux/Ra;
}
//Formula para el calculo del factor nodal de la componente semidiurna K2
//f = sqrt(19.0444*pow(sin(I)),4)+2.7702*pow(sin(I),2)*cos(2ν) + 0.0981)
double NodalAmplitudeFactor_K2(const double &I, const double &v){
    double Irad = qDegreesToRadians(I);
    double vrad = qDegreesToRadians(v);

    double aux1 = qPow(qSin(Irad),4);
    double aux2 = qPow(qSin(Irad),2)*qCos(2*vrad);

    return qSqrt(19.044*aux1 + 2.7702*aux2 + 0.0981);
}
//Formula para el calculo del factor nodal de la componente lunar terdiurna M3
//f = pow(cos(I/2),6)/0.8758
double NodalAmplitudeFactor_M3(const double &I){
    double Irad = qDegreesToRadians(I);

    double aux = qPow(qCos(Irad/2.0),6);

    return aux/0.8758;
}
//Formula para el calculo del factor nodal de las componentes MNS2,M4,MN4,2MS6,MSN6,2(MS)8
// f = pow(f(M2),2)
double NodalAmplitudeFactor_MNS2_M4_MN4_2MS6_MSN6_2MS8(const double &I){
    return qPow(NodalAmplitudeFactor_M2_N2_2N2_NU2_LAMDA2_MU2_2SM2_MS4_2SM6(I),2);
}
//Formula para el calculo del factor nodal de las componentes MK3
// f = f(M2)*f(K1)
double NodalAmplitudeFactor_MK3(const double &I, const double &v){
    double aux1 = NodalAmplitudeFactor_M2_N2_2N2_NU2_LAMDA2_MU2_2SM2_MS4_2SM6(I);
    double aux2 = NodalAmplitudeFactor_K1_SK3(I,v);

    return aux1*aux2;
}
//Formula para el calculo del factor nodal de las componentes 2MK3
// f = pow(f(M2),2)*f(K1)
double NodalAmplitudeFactor_2MK3(const double &I, const double &v){
    double aux1 = qPow(NodalAmplitudeFactor_M2_N2_2N2_NU2_LAMDA2_MU2_2SM2_MS4_2SM6(I),2.0);
    double aux2 = NodalAmplitudeFactor_K1_SK3(I,v);

    return aux1*aux2;
}
//Formula para el calculo del factor nodal de las componentes MK4
// f = pow(f(M2),2)*f(K1)
double NodalAmplitudeFactor_MK4(const double &I, const double &v){
    double aux1 = NodalAmplitudeFactor_M2_N2_2N2_NU2_LAMDA2_MU2_2SM2_MS4_2SM6(I);
    double aux2 = NodalAmplitudeFactor_K2(I,v);

    return aux1*aux2;
}
//Formula para el calculo del factor nodal de las componentes M6,2MN6,3MS8,2MSN8
// f = pow(f(M2),3)
double NodalAmplitudeFactor_M6_2MN6_3MS8_2MSN8(const double &I){
    return qPow(NodalAmplitudeFactor_M2_N2_2N2_NU2_LAMDA2_MU2_2SM2_MS4_2SM6(I),3.0);
}
//Formula para el calculo del factor nodal de las componentes M8
// f = pow(f(M2),4)
double NodalAmplitudeFactor_M8(const double &I){
    return qPow(NodalAmplitudeFactor_M2_N2_2N2_NU2_LAMDA2_MU2_2SM2_MS4_2SM6(I),4.0);
}
#endif // NODALFACTORFORMULAS_H
