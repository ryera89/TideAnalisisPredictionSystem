#include "alcancelimitewindow.h"
#include "ui_alcancelimitewindow.h"
#include <QtMath>

AlcanceLimiteWindow::AlcanceLimiteWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AlcanceLimiteWindow)
{
    ui->setupUi(this);
    ui->lunaLLenaDateEdit->setDate(QDate::currentDate());
    ui->mayorDeclinacionDateEdit->setDate(QDate::currentDate());

    connect(ui->readyAPushButton,SIGNAL(clicked(bool)),this,SLOT(getPostAData()));
    connect(ui->readyBPushButton,SIGNAL(clicked(bool)),this,SLOT(getPostBData()));

    connect(ui->distanciaComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(setDistanceCalcMethod(int))); //Calculo de distancias

    connect(ui->latitudAComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(setOtherFacilitiesDisabled()));
    connect(ui->longitudAComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(setOtherFacilitiesDisabled()));
    connect(ui->latitudASpinBox,SIGNAL(valueChanged(double)),this,SLOT(setOtherFacilitiesDisabled()));
    connect(ui->longitudASpinBox,SIGNAL(valueChanged(double)),this,SLOT(setOtherFacilitiesDisabled()));
    connect(ui->m2AmpASpinBox,SIGNAL(valueChanged(double)),this,SLOT(setOtherFacilitiesDisabled()));
    connect(ui->s2AmpASpinBox,SIGNAL(valueChanged(double)),this,SLOT(setOtherFacilitiesDisabled()));
    connect(ui->k1AmpASpinBox,SIGNAL(valueChanged(double)),this,SLOT(setOtherFacilitiesDisabled()));
    connect(ui->o1AmpASpinBox,SIGNAL(valueChanged(double)),this,SLOT(setOtherFacilitiesDisabled()));
    connect(ui->m2PhaseASpinBox,SIGNAL(valueChanged(double)),this,SLOT(setOtherFacilitiesDisabled()));
    connect(ui->s2PhaseASpinBox,SIGNAL(valueChanged(double)),this,SLOT(setOtherFacilitiesDisabled()));
    connect(ui->k1PhaseASpinBox,SIGNAL(valueChanged(double)),this,SLOT(setOtherFacilitiesDisabled()));
    connect(ui->o1PhaseASpinBox,SIGNAL(valueChanged(double)),this,SLOT(setOtherFacilitiesDisabled()));
    connect(ui->nmmASpinBox,SIGNAL(valueChanged(double)),this,SLOT(setOtherFacilitiesDisabled()));

    connect(ui->latitudBComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(setParameterDisabled()));
    connect(ui->longitudBComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(setParameterDisabled()));
    connect(ui->latitudBSpinBox,SIGNAL(valueChanged(double)),this,SLOT(setParameterDisabled()));
    connect(ui->longitudBSpinBox,SIGNAL(valueChanged(double)),this,SLOT(setParameterDisabled()));
    connect(ui->m2AmpBSpinBox,SIGNAL(valueChanged(double)),this,SLOT(setParameterDisabled()));
    connect(ui->s2AmpBSpinBox,SIGNAL(valueChanged(double)),this,SLOT(setParameterDisabled()));
    connect(ui->k1AmpBSpinBox,SIGNAL(valueChanged(double)),this,SLOT(setParameterDisabled()));
    connect(ui->o1AmpBSpinBox,SIGNAL(valueChanged(double)),this,SLOT(setParameterDisabled()));
    connect(ui->m2PhaseBSpinBox,SIGNAL(valueChanged(double)),this,SLOT(setParameterDisabled()));
    connect(ui->s2PhaseBSpinBox,SIGNAL(valueChanged(double)),this,SLOT(setParameterDisabled()));
    connect(ui->k1PhaseBSpinBox,SIGNAL(valueChanged(double)),this,SLOT(setParameterDisabled()));
    connect(ui->o1PhaseBSpinBox,SIGNAL(valueChanged(double)),this,SLOT(setParameterDisabled()));
    connect(ui->nmmBSpinBox,SIGNAL(valueChanged(double)),this,SLOT(setParameterDisabled()));

    connect(ui->latitudAComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(resetDistanceComboBoxIndex()));
    connect(ui->longitudAComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(resetDistanceComboBoxIndex()));
    connect(ui->latitudASpinBox,SIGNAL(valueChanged(double)),this,SLOT(resetDistanceComboBoxIndex()));
    connect(ui->longitudASpinBox,SIGNAL(valueChanged(double)),this,SLOT(resetDistanceComboBoxIndex()));

    connect(ui->latitudBComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(resetDistanceComboBoxIndex()));
    connect(ui->longitudBComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(resetDistanceComboBoxIndex()));
    connect(ui->latitudBSpinBox,SIGNAL(valueChanged(double)),this,SLOT(resetDistanceComboBoxIndex()));
    connect(ui->longitudBSpinBox,SIGNAL(valueChanged(double)),this,SLOT(resetDistanceComboBoxIndex()));


    this->setAttribute(Qt::WA_DeleteOnClose);
}

AlcanceLimiteWindow::~AlcanceLimiteWindow()
{
    delete ui;
}

void AlcanceLimiteWindow::getPostAData()
{
    getPostACoordinates();
    getNMMrefNMTA();
    getPostAHarmonicConstants();

    ui->puestoBGroupBox->setEnabled(true);
}

void AlcanceLimiteWindow::getPostBData()
{
    getPostBCoordinates();
    getNMMrefNMTB();
    getPostBHarmonicConstants();

    determineCalcPeriod();

    ui->otrosParametrosGroupBox->setEnabled(true);

}

void AlcanceLimiteWindow::setOtherFacilitiesDisabled()
{
    if (ui->puestoBGroupBox->isEnabled()) ui->puestoBGroupBox->setDisabled(true);

    if (ui->otrosParametrosGroupBox->isEnabled()) ui->otrosParametrosGroupBox->setDisabled(true);
}

void AlcanceLimiteWindow::setParameterDisabled()
{
    if (ui->otrosParametrosGroupBox->isEnabled()) ui->otrosParametrosGroupBox->setDisabled(true);
}

void AlcanceLimiteWindow::setDistanceCalcMethod(int index)
{
    switch (index) {
    case 0:
        ui->distanciaSpinBox->setValue(0.0);
        break;
    case 1:
        computeDistanceFromCoordinates();
    default:
        break;
    }
}

void AlcanceLimiteWindow::resetDistanceComboBoxIndex()
{
    switch (ui->distanciaComboBox->currentIndex()) {
    case 0:
        break;
    default:
        ui->distanciaComboBox->setCurrentIndex(0);
        break;
    }
}

void AlcanceLimiteWindow::computeDistanceFromCoordinates()
{
    double distance = m_puestoACoordinate.distanceTo(m_puestoBCoordinate);

    distance/=1000;

    ui->distanciaSpinBox->setValue(distance);
}

double AlcanceLimiteWindow::computeMeanAmpPhase(const HarmonicConstant &hc_A, const HarmonicConstant &hc_B)
{
   double HiA_square = pow(hc_A.amplitud(),2);
   double HiB_square = pow(hc_B.amplitud(),2);

   double rem = 2*hc_A.amplitud()*hc_B.amplitud()*(hc_B.phase() - hc_A.phase());

   double val = qAbs(HiA_square + HiB_square - rem);

   return qSqrt(val);
}

double AlcanceLimiteWindow::computeCalcPeriod()
{
   double Mean_M2 = computeMeanAmpPhase(m_M2_A,m_M2_B);
   double Mean_K1 = computeMeanAmpPhase(m_K1_A,m_K1_B);
   double Mean_O1 = computeMeanAmpPhase(m_O1_A,m_O1_B);

   return (Mean_K1 + Mean_O1)/Mean_M2;
}

void AlcanceLimiteWindow::determineCalcPeriod()
{
    double value = computeCalcPeriod();

    if (value <= 0.5){
        ui->periodoCalculoLineEdit->setText(tr("Sicigias"));
        ui->lunaLLenaDateEdit->setEnabled(true);
        ui->mayorDeclinacionDateEdit->setEnabled(false);
        return;
    }
    if (value >= 2.0){
        ui->periodoCalculoLineEdit->setText(tr("Mayor Declinación Lunar"));
        ui->lunaLLenaDateEdit->setEnabled(false);
        ui->mayorDeclinacionDateEdit->setEnabled(true);
        return;
    }
    if (value > 0.5 && value < 2.0){
        ui->periodoCalculoLineEdit->setText(tr("Sicigias y Mayor Declinación Lunar"));
        ui->lunaLLenaDateEdit->setEnabled(true);
        ui->mayorDeclinacionDateEdit->setEnabled(true);
        return;
    }
}
void AlcanceLimiteWindow::determineH0S0P0_FullMoon()
{
    int P = ui->lunaLLenaDateEdit->date().year() - 1900;

    int P1 = P*360;

    int  P2 = qFloor((P - 1)/4);

    double Dh = P1 + P2 + 0.5;

    m_h0_FullMoon = 279.696678 + 0.9856473354*Dh;
    m_s0_FullMoon = 270.434164 + 13.1763965268*Dh;
    m_p0_FullMoon = 334.329556 + 0.1114040803*Dh;

    //H0
    if (m_h0_FullMoon > 360.0){
        m_h0_FullMoon -= qFloor(m_h0_FullMoon/360.0)*360.0;
    }
    if (m_h0_FullMoon < 0.0){
        m_h0_FullMoon += qFloor(qAbs(m_h0_FullMoon/360.0))*360.0;
    }

    //S0
    if (m_s0_FullMoon > 360.0){
        m_s0_FullMoon -= qFloor(m_s0_FullMoon/360.0)*360.0;
    }
    if (m_s0_FullMoon < 0.0){
        m_s0_FullMoon += qFloor(qAbs(m_s0_FullMoon/360.0))*360.0;
    }

    //P0
    if (m_p0_FullMoon > 360.0){
        m_p0_FullMoon -= qFloor(m_p0_FullMoon/360.0)*360.0;
    }
    if (m_p0_FullMoon < 0.0){
        m_p0_FullMoon += qFloor(qAbs(m_p0_FullMoon/360.0))*360.0;
    }
}

void AlcanceLimiteWindow::determineN_FullMoon()
{
    QDate epoch_date(1,1,1900);
    QDate fullMoonDate(ui->lunaLLenaDateEdit->date());

    quint64 julianDaysNumber = fullMoonDate.toJulianDay() - epoch_date.toJulianDay();

    m_N_FullMoon = 259.183275 - 0.0529539222*julianDaysNumber;

    if (m_N_FullMoon > 360.0){
        m_N_FullMoon -= qFloor(m_N_FullMoon/360.0)*360.0;
    }
    if (m_N_FullMoon < 0.0){
        m_N_FullMoon += qFloor(qAbs(m_N_FullMoon/360.0))*360.0;
    }

}

void AlcanceLimiteWindow::determineNodalFactor_FullMoon()
{
    m_fM2_FullMoon = 1.00035 - 0.03733*qCos(qDegreesToRadians(m_N_FullMoon))
            + 0.00017*qCos(2*qDegreesToRadians(m_N_FullMoon)) + 0.00001*qCos(3*qDegreesToRadians(m_N_FullMoon));

    m_fS2_FullMoon = 1.0;

    m_fK1_FullMoon = 1.0060 - 0.1160*qCos(qDegreesToRadians(m_N_FullMoon))
            + 0.0088*qCos(2*qDegreesToRadians(m_N_FullMoon)) + 0.0006*qCos(3*qDegreesToRadians(m_N_FullMoon));

    m_fO1_FullMoon = 1.0089 - 0.1871*qCos(qDegreesToRadians(m_N_FullMoon))
            + 0.0147*qCos(2*qDegreesToRadians(m_N_FullMoon)) + 0.0014*qCos(3*qDegreesToRadians(m_N_FullMoon));


}

void AlcanceLimiteWindow::determineAstronomicalMagnitudes_FullMoon()
{
    m_v_FullMoon = 12.94*qSin(qDegreesToRadians(m_N_FullMoon)) - 1.34*qSin(2*qDegreesToRadians(m_N_FullMoon))
            + 0.19*qSin(3*qDegreesToRadians(m_N_FullMoon));

    m_ep_FullMoon = 11.87*qSin(qDegreesToRadians(m_N_FullMoon)) - 1.34*qSin(2*qDegreesToRadians(m_N_FullMoon))
            + 0.19*qSin(3*qDegreesToRadians(m_N_FullMoon));

    m_vPrima_FullMoon = 8.86*qSin(qDegreesToRadians(m_N_FullMoon)) - 0.68*qSin(2*qDegreesToRadians(m_N_FullMoon))
            + 0.07*qSin(3*qDegreesToRadians(m_N_FullMoon));

    m_vPrima2_FullMoon = 17.74*qSin(qDegreesToRadians(m_N_FullMoon)) - 0.68*qSin(2*qDegreesToRadians(m_N_FullMoon))
            + 0.04*qSin(3*qDegreesToRadians(m_N_FullMoon));
}

void AlcanceLimiteWindow::determineVoplusU_FullMoon()
{
    m_V0_plus_u_M2_FullMoon = 2*m_h0_FullMoon - 2*m_s0_FullMoon + 2*m_ep_FullMoon - 2*m_v_FullMoon;

    m_V0_plus_u_S2_FullMoon = 0.0;

    m_V0_plus_u_K1_FullMoon = m_h0_FullMoon + 90.0 - m_vPrima_FullMoon;

    m_V0_plus_u_O1_FullMoon = m_h0_FullMoon - 2*m_s0_FullMoon + 2*m_ep_FullMoon - m_v_FullMoon + 270.0;

    if (m_V0_plus_u_M2_FullMoon > 360.0){
        m_V0_plus_u_M2_FullMoon -= qFloor(m_V0_plus_u_M2_FullMoon/360.0)*360.0;
    }
    if (m_V0_plus_u_M2_FullMoon < 0.0){
        m_V0_plus_u_M2_FullMoon += qFloor(qAbs(m_V0_plus_u_M2_FullMoon/360.0))*360.0;
    }

    if (m_V0_plus_u_K1_FullMoon > 360.0){
        m_V0_plus_u_K1_FullMoon -= qFloor(m_V0_plus_u_K1_FullMoon/360.0)*360.0;
    }
    if (m_V0_plus_u_K1_FullMoon < 0.0){
        m_V0_plus_u_K1_FullMoon += qFloor(qAbs(m_V0_plus_u_K1_FullMoon/360.0))*360.0;
    }

    if (m_V0_plus_u_O1_FullMoon > 360.0){
        m_V0_plus_u_O1_FullMoon -= qFloor(m_V0_plus_u_O1_FullMoon/360.0)*360.0;
    }
    if (m_V0_plus_u_O1_FullMoon < 0.0){
        m_V0_plus_u_O1_FullMoon += qFloor(qAbs(m_V0_plus_u_O1_FullMoon/360.0))*360.0;
    }
}

void AlcanceLimiteWindow::determineH0S0P0_MayorMoonDec()
{
    int P = ui->mayorDeclinacionDateEdit->date().year() - 1900;

    int P1 = P*360;

    int  P2 = qFloor((P - 1)/4);

    double Dh = P1 + P2 + 0.5;

    m_h0_MayorMoonDec = 279.696678 + 0.9856473354*Dh;
    m_s0_MayorMoonDec = 270.434164 + 13.1763965268*Dh;
    m_p0_MayorMoonDec = 334.329556 + 0.1114040803*Dh;

    //H0
    if (m_h0_MayorMoonDec > 360.0){
        m_h0_MayorMoonDec -= qFloor(m_h0_MayorMoonDec/360.0)*360.0;
    }
    if (m_h0_MayorMoonDec < 0.0){
        m_h0_MayorMoonDec += qFloor(qAbs(m_h0_MayorMoonDec/360.0))*360.0;
    }

    //S0
    if (m_s0_MayorMoonDec > 360.0){
        m_s0_MayorMoonDec -= qFloor(m_s0_MayorMoonDec/360.0)*360.0;
    }
    if (m_s0_MayorMoonDec < 0.0){
        m_s0_MayorMoonDec += qFloor(qAbs(m_s0_MayorMoonDec/360.0))*360.0;
    }

    //P0
    if (m_p0_MayorMoonDec > 360.0){
        m_p0_MayorMoonDec -= qFloor(m_p0_MayorMoonDec/360.0)*360.0;
    }
    if (m_p0_MayorMoonDec < 0.0){
        m_p0_MayorMoonDec += qFloor(qAbs(m_p0_MayorMoonDec/360.0))*360.0;
    }
}

void AlcanceLimiteWindow::determineN_MayorMoonDec()
{
    QDate epoch_date(1,1,1900);
    QDate MayorMoonDecDate(ui->mayorDeclinacionDateEdit->date());

    quint64 julianDaysNumber = MayorMoonDecDate.toJulianDay() - epoch_date.toJulianDay();

    m_N_MayorMoonDec = 259.183275 - 0.0529539222*julianDaysNumber;

    if (m_N_MayorMoonDec > 360.0){
        m_N_MayorMoonDec -= qFloor(m_N_MayorMoonDec/360.0)*360.0;
    }
    if (m_N_MayorMoonDec < 0.0){
        m_N_MayorMoonDec += qFloor(qAbs(m_N_MayorMoonDec/360.0))*360.0;
    }
}

void AlcanceLimiteWindow::determineNodalFactor_MayorMoonDec()
{
    m_fM2_MayorMoonDec = 1.00035 - 0.03733*qCos(qDegreesToRadians(m_N_MayorMoonDec))
            + 0.00017*qCos(2*qDegreesToRadians(m_N_MayorMoonDec)) + 0.00001*qCos(3*qDegreesToRadians(m_N_MayorMoonDec));

    m_fS2_MayorMoonDec = 1.0;

    m_fK1_MayorMoonDec = 1.0060 - 0.1160*qCos(qDegreesToRadians(m_N_MayorMoonDec))
            + 0.0088*qCos(2*qDegreesToRadians(m_N_MayorMoonDec)) + 0.0006*qCos(3*qDegreesToRadians(m_N_MayorMoonDec));

    m_fO1_MayorMoonDec = 1.0089 - 0.1871*qCos(qDegreesToRadians(m_N_MayorMoonDec))
            + 0.0147*qCos(2*qDegreesToRadians(m_N_MayorMoonDec)) + 0.0014*qCos(3*qDegreesToRadians(m_N_MayorMoonDec));
}

void AlcanceLimiteWindow::determineAstronomicalMagnitudes_MayorMoonDec()
{
    m_v_MayorMoonDec = 12.94*qSin(qDegreesToRadians(m_N_MayorMoonDec)) - 1.34*qSin(2*qDegreesToRadians(m_N_MayorMoonDec))
            + 0.19*qSin(3*qDegreesToRadians(m_N_MayorMoonDec));

    m_ep_MayorMoonDec = 11.87*qSin(qDegreesToRadians(m_N_MayorMoonDec)) - 1.34*qSin(2*qDegreesToRadians(m_N_MayorMoonDec))
            + 0.19*qSin(3*qDegreesToRadians(m_N_MayorMoonDec));

    m_vPrima_MayorMoonDec = 8.86*qSin(qDegreesToRadians(m_N_MayorMoonDec)) - 0.68*qSin(2*qDegreesToRadians(m_N_MayorMoonDec))
            + 0.07*qSin(3*qDegreesToRadians(m_N_MayorMoonDec));

    m_vPrima2_MayorMoonDec = 17.74*qSin(qDegreesToRadians(m_N_MayorMoonDec)) - 0.68*qSin(2*qDegreesToRadians(m_N_MayorMoonDec))
            + 0.04*qSin(3*qDegreesToRadians(m_N_MayorMoonDec));
}

void AlcanceLimiteWindow::determineVoplusU_MayorMoonDec()
{
    m_V0_plus_u_M2_MayorMoonDec = 2*m_h0_MayorMoonDec - 2*m_s0_MayorMoonDec + 2*m_ep_MayorMoonDec - 2*m_v_MayorMoonDec;

    m_V0_plus_u_S2_MayorMoonDec = 0.0;

    m_V0_plus_u_K1_MayorMoonDec = m_h0_MayorMoonDec + 90.0 - m_vPrima_MayorMoonDec;

    m_V0_plus_u_O1_MayorMoonDec = m_h0_MayorMoonDec - 2*m_s0_MayorMoonDec + 2*m_ep_MayorMoonDec - m_v_MayorMoonDec + 270.0;

    if (m_V0_plus_u_M2_MayorMoonDec > 360.0){
        m_V0_plus_u_M2_MayorMoonDec -= qFloor(m_V0_plus_u_M2_MayorMoonDec/360.0)*360.0;
    }
    if (m_V0_plus_u_M2_MayorMoonDec < 0.0){
        m_V0_plus_u_M2_MayorMoonDec += qFloor(qAbs(m_V0_plus_u_M2_MayorMoonDec/360.0))*360.0;
    }

    if (m_V0_plus_u_K1_MayorMoonDec > 360.0){
        m_V0_plus_u_K1_MayorMoonDec -= qFloor(m_V0_plus_u_K1_MayorMoonDec/360.0)*360.0;
    }
    if (m_V0_plus_u_K1_MayorMoonDec < 0.0){
        m_V0_plus_u_K1_MayorMoonDec += qFloor(qAbs(m_V0_plus_u_K1_MayorMoonDec/360.0))*360.0;
    }

    if (m_V0_plus_u_O1_MayorMoonDec > 360.0){
        m_V0_plus_u_O1_MayorMoonDec -= qFloor(m_V0_plus_u_O1_MayorMoonDec/360.0)*360.0;
    }
    if (m_V0_plus_u_O1_MayorMoonDec < 0.0){
        m_V0_plus_u_O1_MayorMoonDec += qFloor(qAbs(m_V0_plus_u_O1_MayorMoonDec/360.0))*360.0;
    }
}

void AlcanceLimiteWindow::getPostACoordinates()
{
    double latitud = ui->latitudASpinBox->value();
    double longitud = ui->longitudASpinBox->value();

    int latIndex = ui->latitudAComboBox->currentIndex();
    int longIndex =ui->longitudAComboBox->currentIndex();

    switch (latIndex) {
    case 1:
        latitud *= -1.0;
        break;
    default:
        break;
    }
    switch (longIndex) {
    case 1:
        longitud *= -1.0;
        break;
    default:
        break;
    }

    m_puestoACoordinate.setLatitude(latitud);
    m_puestoACoordinate.setLongitude(longitud);
}

void AlcanceLimiteWindow::getPostBCoordinates()
{
    double latitud = ui->latitudBSpinBox->value();
    double longitud = ui->longitudBSpinBox->value();

    int latIndex = ui->latitudBComboBox->currentIndex();
    int longIndex =ui->longitudBComboBox->currentIndex();

    switch (latIndex) {
    case 1:
        latitud *= -1.0;
        break;
    default:
        break;
    }
    switch (longIndex) {
    case 1:
        longitud *= -1.0;
        break;
    default:
        break;
    }
    m_puestoBCoordinate.setLatitude(latitud);
    m_puestoBCoordinate.setLongitude(longitud);
}

void AlcanceLimiteWindow::getPostAHarmonicConstants()
{
    double M2_amp = ui->m2AmpASpinBox->value();
    double S2_amp = ui->s2AmpASpinBox->value();
    double K1_amp = ui->k1AmpASpinBox->value();
    double O1_amp = ui->o1AmpASpinBox->value();

    double M2_pha = ui->m2PhaseASpinBox->value();
    double S2_pha = ui->s2PhaseASpinBox->value();
    double K1_pha = ui->k1PhaseASpinBox->value();
    double O1_pha = ui->o1PhaseASpinBox->value();

    m_M2_A.setAmplitud(M2_amp);
    m_S2_A.setAmplitud(S2_amp);
    m_K1_A.setAmplitud(K1_amp);
    m_O1_A.setAmplitud(O1_amp);

    m_M2_A.setPhase(M2_pha);
    m_S2_A.setPhase(S2_pha);
    m_K1_A.setPhase(K1_pha);
    m_O1_A.setPhase(O1_pha);
}

void AlcanceLimiteWindow::getPostBHarmonicConstants()
{
    double M2_amp = ui->m2AmpBSpinBox->value();
    double S2_amp = ui->s2AmpBSpinBox->value();
    double K1_amp = ui->k1AmpBSpinBox->value();
    double O1_amp = ui->o1AmpBSpinBox->value();

    double M2_pha = ui->m2PhaseBSpinBox->value();
    double S2_pha = ui->s2PhaseBSpinBox->value();
    double K1_pha = ui->k1PhaseBSpinBox->value();
    double O1_pha = ui->o1PhaseBSpinBox->value();

    m_M2_B.setAmplitud(M2_amp);
    m_S2_B.setAmplitud(S2_amp);
    m_K1_B.setAmplitud(K1_amp);
    m_O1_B.setAmplitud(O1_amp);

    m_M2_B.setPhase(M2_pha);
    m_S2_B.setPhase(S2_pha);
    m_K1_B.setPhase(K1_pha);
    m_O1_B.setPhase(O1_pha);
}

void AlcanceLimiteWindow::getNMMrefNMTA()
{
    m_nmm_A = ui->nmmASpinBox->value();
}

void AlcanceLimiteWindow::getNMMrefNMTB()
{
    m_nmm_B = ui->nmmBSpinBox->value();
}

