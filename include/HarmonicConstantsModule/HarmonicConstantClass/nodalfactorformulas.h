#ifndef NODALFACTORFORMULAS_H
#define NODALFACTORFORMULAS_H

#include <QtMath>
#include "doodsonnumbers.h"
#include "astronomicalmeanlongitudes.h"
#include "harmonicconstant.h"

//Calculo de V0 de las componentes armonicas
//Parametros  T   s   h   p   N   Ps   90
//Doodson No  d1  d2  d3  d4  d5  d6   dext
//Formula     d1*T + d2*s + d3*h + d4*p + d5*N + d6*Ps + dext*90
double V0(const DoodsonNumbers &doodsonN, const AstronomicalMeanLongitudes &astroLong){
    double aux1 = doodsonN.D1()*astroLong.solarHourAngle();
    double aux2 = doodsonN.D2()*astroLong.moonLongitude();
    double aux3 = doodsonN.D3()*astroLong.sunLongitude();
    double aux4 = doodsonN.D4()*astroLong.lunarPerigeeLongitude();
    double aux5 = doodsonN.D5()*astroLong.lunarAscendingNodeLongitude();
    double aux6 = doodsonN.D6()*astroLong.perihlionLongitude();
    double aux7 = doodsonN.Extended()*90.0;

    return aux1+aux2+aux3+aux4+aux5+aux6+aux7;
}
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
//u = -2ξ
double NodalAngleFactor_Mf(const double &e){
    return -2.0*e;
}

//Formula para el calculo del factor nodal de las componentes lunares diurnas O1,Q1,2Q1,RHO1,SIGMA1,SO3
//f = sin(I)*pow(cos(I/2),2)/0.3800
double NodalAmplitudeFactor_O1_Q1_2Q1_RHO1_SIGMA1_SO3(const double &I){

    double Irad = qDegreesToRadians(I);

    double aux1 = qSin(Irad);
    double aux2 = qPow(qCos(Irad/2.0),2);

    return aux1*aux2/0.3800;
}
//u = 2ξ-ν
double NodalAngleFactor_O1_Q1_2Q1_RHO1_SIGMA1_SO3(const double &e, const double &v){
    return 2.0*e-v;
}
//Formula para el calculo del factor nodal de las componentes lunares diurnas J1,CHI1,THETA1,MP1,SO1
//f = sin(2I)/0.7214
double NodalAmplitudeFactor_J1_CHI1_THETA1_MP1_SO1(const double &I){
    double Irad = qDegreesToRadians(I);

    return qSin(2.0*Irad)/0.7214;
}
//u = -ν
double NodalAngleFactor_J1_CHI1_THETA1_MP1_SO1(const double &v){
    return -v;
}
//Formula para el calculo del factor nodal de las componentes lunares diurnas OO1, KQ1
//f = sin(I)*pow(sin(I/2),2)/0.0164
double NodalAmplitudeFactor_OO1_KQ1(const double &I){
    double Irad = qDegreesToRadians(I);

    double aux1 = qSin(Irad);
    double aux2 = qPow(qSin(Irad/2.0),2);

    return aux1*aux2/0.0164;
}
//u = -2ξ-ν
double NodalAngleFactor_OO1_KQ1(const double &e,const double &v){
    return -2.0*e-v;
}
//Formula para el calculo del factor nodal de la componente diurna M1
//f = sin(I)*pow(cos(I/2),2)/(0.3800*Qa) = f(O1)/Qa
double NodalAmplitudeFactor_M1(const double &I, const double &Qa){
    return NodalAmplitudeFactor_O1_Q1_2Q1_RHO1_SIGMA1(I)/Qa;
}
//u = ξ-ν+Q
double NodalAngleFactor_M1(const double &e, const double &v, const double &Q){
    return e-v+Q;
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
//u = - ν’
double NodalAngleFactor_K1_SK3(const double &vprima){
    return -vprima;
}

//Formula para el calculo del factor nodal de las componentes lunares semidiurnas M2,N2,2N2,NU2,LAMDA2,MU2,2SM2,MS4,2SM6
//f = pow(cos(I/2),4)/0.9154
double NodalAmplitudeFactor_M2_N2_2N2_NU2_LAMDA2_MU2_2SM2_MS4_2SM6(const double &I){
    double Irad = qDegreesToRadians(I);

    double aux = qPow(qCos(Irad/2.0),4);

    return aux/0.9154;
}
// u = 2ξ-2ν
double NodalAngleFactor_M2_N2_2N2_NU2_LAMDA2_MU2_MS4_2SM6(const double &ep,const double &v){
    return 2.0*ep - 2.0*v;
}
// u = -u(M2)
double NodalAngleFactor_2SM2(const double &ep,const double &v){
    return -2.0*ep + 2.0*v;
}
//Formula para el calculo del factor nodal de la componente lunar semidiurna KJ2
//f = pow(sin(I),2)/0.1565
double NodalAmplitudeFactor_KJ2(const double &I){
    double Irad = qDegreesToRadians(I);

    double aux = qPow(qSin(Irad),2);

    return aux/0.1565;

}
// u = -2ν
double NodalAngleFactor_KJ2(const double &v){
    return -2.0*v;
}
//Formula para el calculo del factor nodal de la componente semidiurna L2
//f = pow(cos(I/2),4)/(0.9154*Ra) =  f(M2)/Ra
double NodalAmplitudeFactor_L2(const double &I, const double &Ra){
    double aux = NodalAmplitudeFactor_M2_N2_2N2_NU2_LAMDA2_MU2(I);

    return aux/Ra;
}
// u = 2ξ-2ν-R
double NodalAngleFactor_L2(const double &ep, const double &v, const double &R){
    return 2.0*ep-2.0*v-R;
}
//Formula para el calculo del factor nodal de la componente semidiurna K2
//f = sqrt(19.0444*pow(sin(I)),4)+2.7702*pow(sin(I),2)*cos(2ν) + 0.0981)
double NodalAmplitudeFactor_K2(const double &I, const double &v){
    double Irad = qDegreesToRadians(I);
    double vrad = qDegreesToRadians(v);

    double aux1 = qPow(qSin(Irad),4);
    double aux2 = qPow(qSin(Irad),2)*qCos(2.0*vrad);

    return qSqrt(19.044*aux1 + 2.7702*aux2 + 0.0981);
}
// u = -2ν''
double NodalAngleFactor_K2(const double &v2prima2){
    return -v2prima2;
}
//Formula para el calculo del factor nodal de la componente lunar terdiurna M3
//f = pow(cos(I/2),6)/0.8758
double NodalAmplitudeFactor_M3(const double &I){
    double Irad = qDegreesToRadians(I);

    double aux = qPow(qCos(Irad/2.0),6);

    return aux/0.8758;
}
//u = 3ξ-3ν
double NodalAngleFactor_M3(const double &e, const double &v){
    return 3.0*e - 3.0*v;
}
//Formula para el calculo del factor nodal de las componentes MNS2,M4,MN4,2MS6,MSN6,2(MS)8
// f = pow(f(M2),2)
double NodalAmplitudeFactor_MNS2_M4_MN4_2MS6_MSN6_2MS8(const double &I){
    return qPow(NodalAmplitudeFactor_M2_N2_2N2_NU2_LAMDA2_MU2_2SM2_MS4_2SM6(I),2);
}
// u = 4ξ-4ν = 2*u(M2)
double NodalAngleFactor_MNS2_M4_MN4_2MS6_MSN6_2MS8(const double &e, const double &v){
    return 4.0*e - 4.0*v;
}
//Formula para el calculo del factor nodal de las componentes MK3
// f = f(M2)*f(K1)
double NodalAmplitudeFactor_MK3(const double &I, const double &v){
    double aux1 = NodalAmplitudeFactor_M2_N2_2N2_NU2_LAMDA2_MU2_2SM2_MS4_2SM6(I);
    double aux2 = NodalAmplitudeFactor_K1_SK3(I,v);

    return aux1*aux2;
}
// u = 2ξ-2ν-ν’
double NodalAngleFactor_MK3(const double &e, const double &v, const double &vprima){
    return 2.0*e - 2.0*v - vprima;
}
//Formula para el calculo del factor nodal de las componentes 2MK3
// f = pow(f(M2),2)*f(K1)
double NodalAmplitudeFactor_2MK3(const double &I, const double &v){
    double aux1 = qPow(NodalAmplitudeFactor_M2_N2_2N2_NU2_LAMDA2_MU2_2SM2_MS4_2SM6(I),2.0);
    double aux2 = NodalAmplitudeFactor_K1_SK3(I,v);

    return aux1*aux2;
}
// u = 4ξ-4ν+ν’
double NodalAngleFactor_2MK3(const double &e, const double &v, const double &vprima){
    return 4.0*e - 4.0*v + vprima;
}
//Formula para el calculo del factor nodal de las componentes MK4
// f = pow(f(M2),2)*f(K2)
double NodalAmplitudeFactor_MK4(const double &I, const double &v){
    double aux1 = NodalAmplitudeFactor_M2_N2_2N2_NU2_LAMDA2_MU2_2SM2_MS4_2SM6(I);
    double aux2 = NodalAmplitudeFactor_K2(I,v);

    return aux1*aux2;
}
// u = 2ξ-2ν-2ν’’
double NodalAngleFactor_MK4(const double &e, const double &v, const double &v2prima2){
    return 2.0*e - 2.0*v - v2prima2;
}
//Formula para el calculo del factor nodal de las componentes M6,2MN6,3MS8,2MSN8
// f = pow(f(M2),3)
double NodalAmplitudeFactor_M6_2MN6_3MS8_2MSN8(const double &I){
    return qPow(NodalAmplitudeFactor_M2_N2_2N2_NU2_LAMDA2_MU2_2SM2_MS4_2SM6(I),3.0);
}
// u = 6ξ-6ν = 3*u(M2)
double NodalAngleFactor_M6_2MN6_3MS8_2MSN8(const double &e, const double &v){
    return 6.0*e - 6.0*v;
}
//Formula para el calculo del factor nodal de las componentes M8
// f = pow(f(M2),4)
double NodalAmplitudeFactor_M8(const double &I){
    return qPow(NodalAmplitudeFactor_M2_N2_2N2_NU2_LAMDA2_MU2_2SM2_MS4_2SM6(I),4.0);
}
// u = 8ξ-8ν = 4*u(M2)
double NodalAngleFactor_M8(const double &e, const double &v){
    return 8.0*e - 8.0*v;
}
//SOLAR componentes de origen solar f = 1.0, u = 0
//LUNAR_LONGPERIOD_1  componentes Mm, Msf u = 0, f = [2/3-pow(sin(I),2)]/0.5021
//LUNAR_LONGPERIOD_2  componente Mf u = -2ξ, f = pow(sin(I),2)/0.1578
//LUNAR_DIURNAL_1 componentes lunares diurnas O1,Q1,2Q1,RHO1,SIGMA1,SO3 u = 2ξ-ν, f = sin(I)*pow(cos(I/2),2)/0.3800
//LUNAR_DIURNAL_2 componentes lunares diurnas J1,CHI1,THETA1,MP1,SO1 u = -ν, f = sin(2I)/0.7214
//LUNAR_DIURNAL_3 lunares diurnas OO1, KQ1 f = sin(I)*pow(sin(I/2),2)/0.0164, u = -2ξ-ν
//COMBINATION_DIURNAL_1 componente M1 f = sin(I)*pow(cos(I/2),2)/(0.3800*Qa) = f(O1)/Qa, u = ξ-ν+Q
//COMBINATION_DIURNAL_2 componentes K1, SK3, f = sqrt(0.8965*pow(sin(2I),2)+0.6001*sin(2I)cos(ν) + 0.1006),u = - ν’
//LUNAR_SEMIDIURNAL_1 componentes lunares semidiurnas M2,N2,2N2,NU2,LAMDA2,MU2,2SM2,MS4,2SM6 f = pow(cos(I/2),4)/0.9154, u = 2ξ-2ν
//LUNAR_SEMIDIURNAL_1_2 componente 2SM2 f = f = pow(cos(I/2),4)/0.9154, u = -2ξ+2ν
//LUNAR_SEMIDIURNAL_2 componente lunar semidiurna KJ2 f = pow(sin(I),2)/0.1565, u = -2ν
//COMBINATION_SEMIDIURNAL_1 componente semidiurna L2 f(M2)/Ra, u = 2ξ-2ν-R
//COMBINATION_SEMIDIURNAL_2 componente semidiurna K2 f = sqrt(19.0444*pow(sin(I)),4)+2.7702*pow(sin(I),2)*cos(2ν) + 0.0981), u = -2ν''
//LUNAR_TERDIURNAL componente M3 f = pow(cos(I/2),6)/0.8758, u = 3ξ-3ν
//SHALLOW_1 las componentes MNS2,M4,MN4,2MS6,MSN6,2(MS)8 f = pow(f(M2),2), u = 4ξ-4ν = 2*u(M2)
//SHALLOW_2 componentes M6,2MN6,3MS8,2MSN8 f = pow(f(M2),3), u = 6ξ-6ν = 3*u(M2)
//SHALLOW_3 componentes M8 f = pow(f(M2),4), u = 8ξ-8ν = 4*u(M2)
//SHALLOW_COMB_1 componentes MK3 f = f(M2)*f(K1), u = 2ξ-2ν-ν’
//SHALLOW_COMB_2 componentes 2MK3 f = pow(f(M2),2)*f(K1), u = 4ξ-4ν+ν’
//SHALLOW_COMB_3 componentes MK4 // f = pow(f(M2),2)*f(K2), u = 2ξ-2ν-2ν’’
double NodalAmplitudeFactor(const HarmonicConstant &hc, const AstronomicalMeanLongitudes &astrolong){
    switch (hc.origin()) {
    case HarmonicConstant::SOLAR:    //SOLAR componentes de origen solar f = 1.0 u = 0.0
        return 1.0;
        break;
    case HarmonicConstant::LUNAR_LONGPERIOD_1:    //LUNAR_LONGPERIOD_1  componentes Mm, Msf u = 0, f = [2/3-pow(sin(I),2)]/0.5021
        return NodalAmplitudeFactor_Mm_Msf(astrolong.I());
        break;
    case HarmonicConstant::LUNAR_LONGPERIOD_2:     //LUNAR_LONGPERIOD_2  componente Mf u = -2ξ, f = pow(sin(I),2)/0.1578
        return NodalAmplitudeFactor_Mf(astrolong.I());
        break;
    case HarmonicConstant::LUNAR_DIURNAL_1:   //LUNAR_DIURNAL_1 componentes lunares diurnas O1,Q1,2Q1,RHO1,SIGMA1,SO3 u = 2ξ-ν, f = sin(I)*pow(cos(I/2),2)/0.3800
        return NodalAmplitudeFactor_O1_Q1_2Q1_RHO1_SIGMA1_SO3(astrolong.I());
        break;
    case HarmonicConstant::LUNAR_DIURNAL_2:      //LUNAR_DIURNAL_2 componentes lunares diurnas J1,CHI1,THETA1,MP1,SO1 u = -ν, f = sin(2I)/0.7214
        return NodalAmplitudeFactor_J1_CHI1_THETA1_MP1_SO1(astrolong.I());
        break;
    case HarmonicConstant::LUNAR_DIURNAL_3:      //LUNAR_DIURNAL_3 lunares diurnas OO1, KQ1 f = sin(I)*pow(sin(I/2),2)/0.0164, u = -2ξ-ν
        return NodalAmplitudeFactor_OO1_KQ1(astrolong.I());
        break;
    case HarmonicConstant::COMBINATION_DIURNAL_1:   //COMBINATION_DIURNAL_1 componente M1 f = sin(I)*pow(cos(I/2),2)/(0.3800*Qa) = f(O1)/Qa, u = ξ-ν+Q
        return NodalAmplitudeFactor_M1(astrolong.I(),astrolong.Qa());
        break;
    case HarmonicConstant::COMBINATION_DIURNAL_2:   //COMBINATION_DIURNAL_2 componentes K1, SK3, f = sqrt(0.8965*pow(sin(2I),2)+0.6001*sin(2I)cos(ν) + 0.1006),u = - ν’
        return NodalAmplitudeFactor_K1_SK3(astrolong.I(),astrolong.v());
        break;
    case HarmonicConstant::LUNAR_SEMIDIURNAL_1:  //LUNAR_SEMIDIURNAL_1 componentes lunares semidiurnas M2,N2,2N2,NU2,LAMDA2,MU2,2SM2,MS4,2SM6
        return NodalAmplitudeFactor_M2_N2_2N2_NU2_LAMDA2_MU2_2SM2_MS4_2SM6(astrolong.I());
        break;
    case HarmonicConstant::LUNAR_SEMIDIURNAL_1_2:   //LUNAR_SEMIDIURNAL_1_2 componente 2SM2
        return NodalAmplitudeFactor_M2_N2_2N2_NU2_LAMDA2_MU2_2SM2_MS4_2SM6(astrolong.I());
        break;
    case HarmonicConstant::LUNAR_SEMIDIURNAL_2:  //LUNAR_SEMIDIURNAL_2 componente lunar semidiurna KJ2
        return NodalAmplitudeFactor_KJ2(astrolong.I());
        break;
    case HarmonicConstant::COMBINATION_SEMIDIURNAL_1:  //COMBINATION_SEMIDIURNAL_1 componente semidiurna L2
        return NodalAmplitudeFactor_L2(astrolong.I(),astrolong.Ra());
        break;
    case HarmonicConstant::COMBINATION_SEMIDIURNAL_2:  //COMBINATION_SEMIDIURNAL_2 componente semidiurna K2
        return NodalAmplitudeFactor_K2(astrolong.I(),astrolong.v());
        break;
    case HarmonicConstant::LUNAR_TERDIURNAL:   //LUNAR_TERDIURNAL componente M3
        return NodalAmplitudeFactor_M3(astrolong.I());
        break;
    case HarmonicConstant::SHALLOW_1:    //SHALLOW_1 las componentes MNS2,M4,MN4,2MS6,MSN6,2(MS)8
        return NodalAmplitudeFactor_MNS2_M4_MN4_2MS6_MSN6_2MS8(astrolong.I());
        break;
    case HarmonicConstant::SHALLOW_2:    //SHALLOW_2 componentes M6,2MN6,3MS8,2MSN8
        return NodalAmplitudeFactor_M6_2MN6_3MS8_2MSN8(astrolong.I());
        break;
    case HarmonicConstant::SHALLOW_3:    //SHALLOW_3 componentes M8
        return NodalAmplitudeFactor_M8(astrolong.I());
        break;
    case HarmonicConstant::SHALLOW_COMB_1:    //SHALLOW_COMB_1 componentes MK3
        return NodalAmplitudeFactor_MK3(astrolong.I(),astrolong.v());
        break;
    case HarmonicConstant::SHALLOW_COMB_2:    //SHALLOW_COMB_2 componentes 2MK3
        return NodalAmplitudeFactor_2MK3(astrolong.I(),astrolong.v());
        break;
    case HarmonicConstant::SHALLOW_COMB_3:    //SHALLOW_COMB_3 componentes MK4
        return NodalAmplitudeFactor_MK4(astrolong.I(),astrolong.v());
        break;
    default:
        break;
    }
}
double NodalAngleFactor(const HarmonicConstant &hc, const AstronomicalMeanLongitudes &astrolong){
    switch (hc.origin()) {
    case HarmonicConstant::SOLAR:    //SOLAR componentes de origen solar f = 1.0 u = 0.0
        return 0.0;
        break;
    case HarmonicConstant::LUNAR_LONGPERIOD_1:    //LUNAR_LONGPERIOD_1  componentes Mm, Msf u = 0, f = [2/3-pow(sin(I),2)]/0.5021
        return 0.0;
        break;
    case HarmonicConstant::LUNAR_LONGPERIOD_2:     //LUNAR_LONGPERIOD_2  componente Mf u = -2ξ, f = pow(sin(I),2)/0.1578
        return NodalAngleFactor_Mf(astrolong.ep());
        break;
    case HarmonicConstant::LUNAR_DIURNAL_1:   //LUNAR_DIURNAL_1 componentes lunares diurnas O1,Q1,2Q1,RHO1,SIGMA1,SO3 u = 2ξ-ν, f = sin(I)*pow(cos(I/2),2)/0.3800
        return NodalAngleFactor_O1_Q1_2Q1_RHO1_SIGMA1_SO3(astrolong.ep,astrolong.v());
        break;
    case HarmonicConstant::LUNAR_DIURNAL_2:      //LUNAR_DIURNAL_2 componentes lunares diurnas J1,CHI1,THETA1,MP1,SO1 u = -ν, f = sin(2I)/0.7214
        return NodalAngleFactor_J1_CHI1_THETA1_MP1_SO1(astrolong.v());
        break;
    case HarmonicConstant::LUNAR_DIURNAL_3:      //LUNAR_DIURNAL_3 lunares diurnas OO1, KQ1 f = sin(I)*pow(sin(I/2),2)/0.0164, u = -2ξ-ν
        return NodalAngleFactor_OO1_KQ1(astrolong.ep(),astrolong.v());
        break;
    case HarmonicConstant::COMBINATION_DIURNAL_1:   //COMBINATION_DIURNAL_1 componente M1 f = sin(I)*pow(cos(I/2),2)/(0.3800*Qa) = f(O1)/Qa, u = ξ-ν+Q
        return NodalAngleFactor_M1(astrolong.ep,astrolong.v,astrolong.Q());
        break;
    case HarmonicConstant::COMBINATION_DIURNAL_2:   //COMBINATION_DIURNAL_2 componentes K1, SK3, f = sqrt(0.8965*pow(sin(2I),2)+0.6001*sin(2I)cos(ν) + 0.1006),u = - ν’
        return NodalAngleFactor_K1_SK3(astrolong.vPrima());
        break;
    case HarmonicConstant::LUNAR_SEMIDIURNAL_1:  //LUNAR_SEMIDIURNAL_1 componentes lunares semidiurnas M2,N2,2N2,NU2,LAMDA2,MU2,2SM2,MS4,2SM6
        return NodalAngleFactor_M2_N2_2N2_NU2_LAMDA2_MU2_MS4_2SM6(astrolong.ep,astrolong.v());
        break;
    case HarmonicConstant::LUNAR_SEMIDIURNAL_1_2:  //LUNAR_SEMIDIURNAL_1_2 componente 2SM2
        return NodalAngleFactor_2SM2(astrolong.ep,astrolong.v());
        break;
    case HarmonicConstant::LUNAR_SEMIDIURNAL_2:  //LUNAR_SEMIDIURNAL_2 componente lunar semidiurna KJ2
        return NodalAngleFactor_KJ2(astrolong.v());
        break;
    case HarmonicConstant::COMBINATION_SEMIDIURNAL_1:  //COMBINATION_SEMIDIURNAL_1 componente semidiurna L2
        return NodalAngleFactor_L2(astrolong.ep,astrolong.v(),astrolong.R());
        break;
    case HarmonicConstant::COMBINATION_SEMIDIURNAL_2:  //COMBINATION_SEMIDIURNAL_2 componente semidiurna K2
        return NodalAngleFactor_K2(astrolong.v2Prima());
        break;
    case HarmonicConstant::LUNAR_TERDIURNAL:   //LUNAR_TERDIURNAL componente M3
        return NodalAngleFactor_M3(astrolong.ep(),astrolong.v());
        break;
    case HarmonicConstant::SHALLOW_1:    //SHALLOW_1 las componentes MNS2,M4,MN4,2MS6,MSN6,2(MS)8
        return NodalAngleFactor_MNS2_M4_MN4_2MS6_MSN6_2MS8(astrolong.ep(),astrolong.v());
        break;
    case HarmonicConstant::SHALLOW_2:    //SHALLOW_2 componentes M6,2MN6,3MS8,2MSN8
        return NodalAngleFactor_M6_2MN6_3MS8_2MSN8(astrolong.ep(),astrolong.v());
        break;
    case HarmonicConstant::SHALLOW_3:    //SHALLOW_3 componentes M8
        return NodalAngleFactor_M8(astrolong.ep(),astrolong.v());
        break;
    case HarmonicConstant::SHALLOW_COMB_1:    //SHALLOW_COMB_1 componentes MK3
        return NodalAngleFactor_MK3(astrolong.ep,astrolong.v(),astrolong.vPrima());
        break;
    case HarmonicConstant::SHALLOW_COMB_2:    //SHALLOW_COMB_2 componentes 2MK3
        return NodalAngleFactor_2MK3(astrolong.ep,astrolong.v(),astrolong.vPrima());
        break;
    case HarmonicConstant::SHALLOW_COMB_3:    //SHALLOW_COMB_3 componentes MK4
        return NodalAngleFactor_MK4(astrolong.ep,astrolong.v(),astrolong.v2Prima());
        break;
    default:
        break;
    }
}
double V0_u(const HarmonicConstant &hc, const AstronomicalMeanLongitudes &V0aml, const AstronomicalMeanLongitudes &uaml){
    return V0(hc.doodsonNumbers(),V0aml) + NodalAngleFactor(hc,uaml);
}

#endif // NODALFACTORFORMULAS_H
