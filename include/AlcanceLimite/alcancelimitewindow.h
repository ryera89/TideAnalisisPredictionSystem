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

     double computeMeanAmpPhase(const HarmonicConstant &hc_A, const HarmonicConstant &hc_B); //calculo de los valores medios de amplitud y fase para la componente hc
     double computeCalcPeriod();
     void determineCalcPeriod();   

     //Calculations For Full Moon
     void determineH0S0P0_FullMoon();
     void determineN_FullMoon();
     void determineNodalFactor_FullMoon();
     void determineAstronomicalMagnitudes_FullMoon();
     void determineVoplusU_FullMoon();
     //Calculations For Mayor Moon Decl
     void determineH0S0P0_MayorMoonDec();
     void determineN_MayorMoonDec();
     void determineNodalFactor_MayorMoonDec();
     void determineAstronomicalMagnitudes_MayorMoonDec();
     void determineVoplusU_MayorMoonDec();
     //Data colection
     void getPostACoordinates();
     void getPostBCoordinates();

     void getPostAHarmonicConstants();
     void getPostBHarmonicConstants();

     void getNMMrefNMTA();
     void getNMMrefNMTB();

     void computeDistanceFromCoordinates();

};
#endif // ALCANCELIMITEWINDOW_H
