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

     double computeMeanAmpPhase(const HarmonicConstant &hc_A, const HarmonicConstant &hc_B); //calculo de los valores medios de amplitud y fase para la componente hc
     double computeCalcPeriod();

};
#endif // ALCANCELIMITEWINDOW_H
