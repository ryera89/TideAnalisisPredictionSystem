#ifndef ALCANCELIMITEWINDOW_H
#define ALCANCELIMITEWINDOW_H

#include <QMainWindow>
#include <QtPositioning/QGeoCoordinate>
#include "include/HarmonicConstantsModule/HarmonicConstantClass/harmonicconstant.h"

namespace Ui {
class AlcanceLimiteWindow;
}

class AlcanceLimiteWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AlcanceLimiteWindow(QWidget *parent = 0);
    ~AlcanceLimiteWindow();

private slots:
    void getPostAData();
    void getPostBData();
    void setOtherFacilitiesDisabled();
    void setParameterDisabled();
    void setDistanceCalcMethod(int index);
    void resetDistanceComboBoxIndex();
    void determinarAlcance();

private:
     Ui::AlcanceLimiteWindow *ui;

     //Puesto A
     HarmonicConstant m_M2_A;
     HarmonicConstant m_S2_A;
     HarmonicConstant m_K1_A;
     HarmonicConstant m_O1_A;

     //Puesto B
     HarmonicConstant m_M2_B;
     HarmonicConstant m_S2_B;
     HarmonicConstant m_K1_B;
     HarmonicConstant m_O1_B;

     QGeoCoordinate m_puestoACoordinate;
     QGeoCoordinate m_puestoBCoordinate;

     double m_nmm_A;
     double m_nmm_B;

     double m_calc_period;

     double m_prof_prec; //Presicion en la medicion de las profundidades
     double m_distance_AB; //distancia desde puesto A hasta puesto B

     double m_h0_FullMoon; // Argumento astronomico
     double m_s0_FullMoon; // Argumento astronomico
     double m_p0_FullMoon; // Argumento astronomico

     double m_h0_MayorMoonDec; // Argumento astronomico
     double m_s0_MayorMoonDec; // Argumento astronomico
     double m_p0_MayorMoonDec; // Argumento astronomico

     double m_N_FullMoon; //Nudo ascensional de la orbita lunar
     double m_N_MayorMoonDec; //Nudo ascensional de la orbita lunar

     double m_fM2_FullMoon;
     double m_fS2_FullMoon;
     double m_fK1_FullMoon;
     double m_fO1_FullMoon;

     double m_fM2_MayorMoonDec;
     double m_fS2_MayorMoonDec;
     double m_fK1_MayorMoonDec;
     double m_fO1_MayorMoonDec;

     double m_v_FullMoon;
     double m_ep_FullMoon;
     double m_vPrima_FullMoon;
     double m_vPrima2_FullMoon;

     double m_v_MayorMoonDec;
     double m_ep_MayorMoonDec;
     double m_vPrima_MayorMoonDec;
     double m_vPrima2_MayorMoonDec;

     double m_V0_plus_u_M2_FullMoon;
     double m_V0_plus_u_S2_FullMoon;
     double m_V0_plus_u_K1_FullMoon;
     double m_V0_plus_u_O1_FullMoon;

     double m_V0_plus_u_M2_MayorMoonDec;
     double m_V0_plus_u_S2_MayorMoonDec;
     double m_V0_plus_u_K1_MayorMoonDec;
     double m_V0_plus_u_O1_MayorMoonDec;

     double m_LM2_AB_FullMoon;
     double m_LS2_AB_FullMoon;
     double m_LK1_AB_FullMoon;
     double m_LO1_AB_FullMoon;

     double m_LM2_AB_MayorMoonDec;
     double m_LS2_AB_MayorMoonDec;
     double m_LK1_AB_MayorMoonDec;
     double m_LO1_AB_MayorMoonDec;

     double m_LM2_BA_FullMoon;
     double m_LS2_BA_FullMoon;
     double m_LK1_BA_FullMoon;
     double m_LO1_BA_FullMoon;

     double m_LM2_BA_MayorMoonDec;
     double m_LS2_BA_MayorMoonDec;
     double m_LK1_BA_MayorMoonDec;
     double m_LO1_BA_MayorMoonDec;

     //Ni Values
     double m_nM2_AB;
     double m_nS2_AB;
     double m_nK1_AB;
     double m_nO1_AB;

     double m_nM2_BA;
     double m_nS2_BA;
     double m_nK1_BA;
     double m_nO1_BA;

     //Puesto A
     double m_hmin_AB_FullMoon;
     double m_hmax_AB_FullMoon;
     //Puesto B
     double m_hmin_BA_FullMoon;
     double m_hmax_BA_FullMoon;
     //Puesto A
     double m_hmin_AB_MayorMoonDec;
     double m_hmax_AB_MayorMoonDec;
     //Puesto B
     double m_hmin_BA_MayorMoonDec;
     double m_hmax_BA_MayorMoonDec;

     //Puesto A FullMoon
     double m_alcance_A_FullMoon;
     //Puesto B FullMoon
     double m_alcance_B_FullMoon;
     //Puesto A Mayor Moon Declination
     double m_alcance_A_MayorMoonDec;
     //Puesto B Mayor Moon Declination
     double m_alcance_B_MayorMoonDec;

     double computeMeanAmpPhase(const HarmonicConstant &hc_A, const HarmonicConstant &hc_B); //calculo de los valores medios de amplitud y fase para la componente hc
     double computeCalcPeriod();
     void determineCalcPeriod();
     double computeTnValue(const HarmonicConstant &hc_1, const HarmonicConstant &hc_2);

     void determineNValues_AB();
     void determineNValues_BA();

     //Calculations For Full Moon
     void determineH0S0P0_FullMoon();
     void determineN_FullMoon();
     void determineNodalFactor_FullMoon();
     void determineAstronomicalMagnitudes_FullMoon();
     void determineVoplusU_FullMoon();
     void determineLValues_AB_FullMoon(); //Alcance Puesto A
     void determineLValues_BA_FullMoon(); //Alcance Puesto B
     void determineHmaxAndHmin_AB_FullMoon();
     void determineHmaxAndHmin_BA_FullMoon();
     void calcularAlcance_A_FullMoon();
     void calcularAlcance_B_FullMoon();

     //Calculations For Mayor Moon Decl
     void determineH0S0P0_MayorMoonDec();
     void determineN_MayorMoonDec();
     void determineNodalFactor_MayorMoonDec();
     void determineAstronomicalMagnitudes_MayorMoonDec();
     void determineVoplusU_MayorMoonDec();
     void determineLValues_AB_MayorMoonDec(); //Alcance Puesto A
     void determineLValues_BA_MayorMoonDec(); //Alcance Puesto B
     void determineHmaxAndHmin_AB_MayorMoonDec();
     void determineHmaxAndHmin_BA_MayorMoonDec();
     void calcularAlcance_A_MayorMoonDec();
     void calcularAlcance_B_MayorMoonDec();

     //Data colection
     void getPostACoordinates();
     void getPostBCoordinates();

     void getPostAHarmonicConstants();
     void getPostBHarmonicConstants();

     void getNMMrefNMTA();
     void getNMMrefNMTB();

     void computeDistanceFromCoordinates();

     void findAngle(double &angle);

};
#endif // ALCANCELIMITEWINDOW_H
