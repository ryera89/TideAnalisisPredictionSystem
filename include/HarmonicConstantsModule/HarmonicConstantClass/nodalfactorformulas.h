#ifndef NODALFACTORFORMULAS_H
#define NODALFACTORFORMULAS_H

#include <QtMath>
#include "doodsonnumbers.h"
#include "astronomicalmeanlongitudes.h"
#include "harmonicconstant.h"


QDateTime determineDataSerieMidPoint(const QDateTime &begin, const QDateTime &end);

//Calculo de V0 de las componentes armonicas
//Parametros  T   s   h   p   N   Ps   90
//Doodson No  d1  d2  d3  d4  d5  d6   dext
//Formula     d1*T + d2*s + d3*h + d4*p + d5*N + d6*Ps + dext*90
double V0(const DoodsonNumbers &doodsonN, const AstronomicalMeanLongitudes &astroLong);
//Formula para el calculo del factor nodal de las componentes lunares de largo periodo Mm y Msf
//f = [2/3-pow(sin(I),2)]/0.5021
double NodalAmplitudeFactor_Mm_Msf(const double &I);

//Formula para el calculo del factor nodal de la componente lunar de largo periodo Mf
//f = pow(sin(I),2)/0.1578
double NodalAmplitudeFactor_Mf(const double &I);
//u = -2ξ
double NodalAngleFactor_Mf(const double &e);

//Formula para el calculo del factor nodal de las componentes lunares diurnas O1,Q1,2Q1,RHO1,SIGMA1,SO3
//f = sin(I)*pow(cos(I/2),2)/0.3800
double NodalAmplitudeFactor_O1_Q1_2Q1_RHO1_SIGMA1_SO3(const double &I);
//u = 2ξ-ν
double NodalAngleFactor_O1_Q1_2Q1_RHO1_SIGMA1_SO3(const double &e, const double &v);
//Formula para el calculo del factor nodal de las componentes lunares diurnas J1,CHI1,THETA1,MP1,SO1
//f = sin(2I)/0.7214
double NodalAmplitudeFactor_J1_CHI1_THETA1_MP1_SO1(const double &I);
//u = -ν
double NodalAngleFactor_J1_CHI1_THETA1_MP1_SO1(const double &v);
//Formula para el calculo del factor nodal de las componentes lunares diurnas OO1, KQ1
//f = sin(I)*pow(sin(I/2),2)/0.0164
double NodalAmplitudeFactor_OO1_KQ1(const double &I);
//u = -2ξ-ν
double NodalAngleFactor_OO1_KQ1(const double &e,const double &v);
//Formula para el calculo del factor nodal de la componente diurna M1
//f = sin(I)*pow(cos(I/2),2)/(0.3800*Qa) = f(O1)/Qa
double NodalAmplitudeFactor_M1(const double &I, const double &Qa);
//u = ξ-ν+Q
double NodalAngleFactor_M1(const double &e, const double &v, const double &Q);

//Formula para el calculo del factor nodal de la componente diurna K1,SK3
//f = sqrt(0.8965*pow(sin(2I),2)+0.6001*sin(2I)cos(ν) + 0.1006)
double NodalAmplitudeFactor_K1_SK3(const double &I, const double &v);
//u = - ν’
double NodalAngleFactor_K1_SK3(const double &vprima);

//Formula para el calculo del factor nodal de las componentes lunares semidiurnas M2,N2,2N2,NU2,LAMDA2,MU2,2SM2,MS4,2SM6
//f = pow(cos(I/2),4)/0.9154
double NodalAmplitudeFactor_M2_N2_2N2_NU2_LAMDA2_MU2_2SM2_MS4_2SM6(const double &I);
// u = 2ξ-2ν
double NodalAngleFactor_M2_N2_2N2_NU2_LAMDA2_MU2_MS4_2SM6(const double &ep,const double &v);
// u = -u(M2)
double NodalAngleFactor_2SM2(const double &ep,const double &v);
//Formula para el calculo del factor nodal de la componente lunar semidiurna KJ2
//f = pow(sin(I),2)/0.1565
double NodalAmplitudeFactor_KJ2(const double &I);
// u = -2ν
double NodalAngleFactor_KJ2(const double &v);
//Formula para el calculo del factor nodal de la componente semidiurna L2
//f = pow(cos(I/2),4)/(0.9154*Ra) =  f(M2)/Ra
double NodalAmplitudeFactor_L2(const double &I, const double &Ra);
// u = 2ξ-2ν-R
double NodalAngleFactor_L2(const double &ep, const double &v, const double &R);
//Formula para el calculo del factor nodal de la componente semidiurna K2
//f = sqrt(19.0444*pow(sin(I)),4)+2.7702*pow(sin(I),2)*cos(2ν) + 0.0981)
double NodalAmplitudeFactor_K2(const double &I, const double &v);
// u = -2ν''
double NodalAngleFactor_K2(const double &v2prima2);
//Formula para el calculo del factor nodal de la componente lunar terdiurna M3
//f = pow(cos(I/2),6)/0.8758
double NodalAmplitudeFactor_M3(const double &I);
//u = 3ξ-3ν
double NodalAngleFactor_M3(const double &e, const double &v);
//Formula para el calculo del factor nodal de las componentes MNS2,M4,MN4,2MS6,MSN6,2(MS)8
// f = pow(f(M2),2)
double NodalAmplitudeFactor_MNS2_M4_MN4_2MS6_MSN6_2MS8(const double &I);
// u = 4ξ-4ν = 2*u(M2)
double NodalAngleFactor_MNS2_M4_MN4_2MS6_MSN6_2MS8(const double &e, const double &v);
//Formula para el calculo del factor nodal de las componentes MK3
// f = f(M2)*f(K1)
double NodalAmplitudeFactor_MK3(const double &I, const double &v);
// u = 2ξ-2ν-ν’
double NodalAngleFactor_MK3(const double &e, const double &v, const double &vprima);
//Formula para el calculo del factor nodal de las componentes 2MK3
// f = pow(f(M2),2)*f(K1)
double NodalAmplitudeFactor_2MK3(const double &I, const double &v);
// u = 4ξ-4ν+ν’
double NodalAngleFactor_2MK3(const double &e, const double &v, const double &vprima);
//Formula para el calculo del factor nodal de las componentes MK4
// f = pow(f(M2),2)*f(K2)
double NodalAmplitudeFactor_MK4(const double &I, const double &v);
// u = 2ξ-2ν-2ν’’
double NodalAngleFactor_MK4(const double &e, const double &v, const double &v2prima2);
//Formula para el calculo del factor nodal de las componentes M6,2MN6,3MS8,2MSN8
// f = pow(f(M2),3)
double NodalAmplitudeFactor_M6_2MN6_3MS8_2MSN8(const double &I);
// u = 6ξ-6ν = 3*u(M2)
double NodalAngleFactor_M6_2MN6_3MS8_2MSN8(const double &e, const double &v);
//Formula para el calculo del factor nodal de las componentes M8
// f = pow(f(M2),4)
double NodalAmplitudeFactor_M8(const double &I);
// u = 8ξ-8ν = 4*u(M2)
double NodalAngleFactor_M8(const double &e, const double &v);
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
double NodalAmplitudeFactor(const HarmonicConstant &hc, const AstronomicalMeanLongitudes &astrolong);
double NodalAngleFactor(const HarmonicConstant &hc, const AstronomicalMeanLongitudes &astrolong);
double V0_u(const HarmonicConstant &hc, const AstronomicalMeanLongitudes &V0aml, const AstronomicalMeanLongitudes &uaml);

#endif // NODALFACTORFORMULAS_H
