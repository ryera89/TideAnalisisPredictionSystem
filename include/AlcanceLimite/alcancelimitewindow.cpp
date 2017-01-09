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

    this->setAttribute(Qt::WA_DeleteOnClose);
}

AlcanceLimiteWindow::~AlcanceLimiteWindow()
{
    delete ui;
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

