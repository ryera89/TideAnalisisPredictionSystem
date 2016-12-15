#include "alturapromediomarea.h"
#include <QtMath>

AlturaPromedioMarea::AlturaPromedioMarea(const HarmonicConstant &M2, const HarmonicConstant &S2,
                                                             const HarmonicConstant &N2, const HarmonicConstant &K2,
                                                             const HarmonicConstant &K1, const HarmonicConstant &O1,
                                                             const HarmonicConstant &P1, const HarmonicConstant &Q1,
                                                             const HarmonicConstant &M4, const HarmonicConstant &M6):
   m_M2(M2), m_S2(S2), m_N2(N2), m_K2(K2), m_K1(K1), m_O1(O1), m_P1(P1), m_Q1(Q1), m_M4(M4), m_M6(M6)
{
    calculate();
}

double AlturaPromedioMarea::A()
{
    double resp = 1.006*m_M2.amplitud() + 0.27*qPow(m_S2.amplitud(),2)/m_M2.amplitud() - m_K2.amplitud();
    return resp;

}

double AlturaPromedioMarea::B()
{
   double resp = 1.021*(m_K1.amplitud() + m_O1.amplitud());
   return resp;
}

double AlturaPromedioMarea::V()
{
   double relationFlag = (m_K1.amplitud() + m_O1.amplitud())/m_M2.amplitud();

   double a = A();
   double b = B();

   double num1 = 2*a*qSin(qDegreesToRadians(m_K1.phase() + m_O1.phase() - m_M2.phase()));
   double den1 = 4*a*qSin(qDegreesToRadians(m_K1.phase() + m_O1.phase() - m_M2.phase())) + b;

   double v1 = qRadiansToDegrees(qAtan(num1/den1));


   if (relationFlag <= 7.7){
       double num2 = 2*a*qSin(qDegreesToRadians(m_K1.phase() + m_O1.phase() - m_M2.phase() - 2*v1));

       double val = num2/b;

       double v2;

       if (val >= -1 && val <= 1) v2 = qRadiansToDegrees(qAsin(val));
       else return v1;

       double v = 0.5*(v1 + v2);

       return v;
   }

   return v1;
}

double AlturaPromedioMarea::W()
{
    double relationFlag = (m_K1.amplitud() + m_O1.amplitud())/m_M2.amplitud();

    double a = A();
    double b = B();

    double num1 = 2*a*qSin(qDegreesToRadians(m_K1.phase() + m_O1.phase() - m_M2.phase()));
    double den1 = 4*a*qSin(qDegreesToRadians(m_K1.phase() + m_O1.phase() - m_M2.phase())) - b;

    double w1 = qRadiansToDegrees(qAtan(num1/den1));


    if (relationFlag <= 7.7){
        double num2 = 2*a*qSin(qDegreesToRadians(m_K1.phase() + m_O1.phase() - m_M2.phase() - 2*w1));

        double val = -num2/b;

        double w2;
        if (val >= -1 && val <= 1) w2 = qRadiansToDegrees(qAsin(val));
        else return w1;



        double w = 0.5*(w1 + w2);

        return w;
    }

    return w1;
}

double AlturaPromedioMarea::Mn()
{
    double sumando1 = 2*m_M2.amplitud();

    double sumando2 = 1.071*qPow(m_S2.amplitud(),2) + 0.963*qPow(m_N2.amplitud(),2) + 1.077*qPow(m_K2.amplitud(),2)
                       + 0.269*qPow(m_K1.amplitud(),2) + 0.231*qPow(m_O1.amplitud(),2) + 0.266*qPow(m_P1.amplitud(),2)
                       + 0.214*qPow(m_Q1.amplitud(),2);

    sumando2/=2*m_M2.amplitud();

    double mn = sumando1 + sumando2;
    return mn;
}

void AlturaPromedioMarea::calculate()
{
    //****************Altura Promedio de Marea Semidiurna****************
    double mn = Mn();

    double v = V();
    double w = W();

    double aux1Semi = m_M2.amplitud()*(qCos(qDegreesToRadians(v)) + qCos(qDegreesToRadians(w)) - 2);
    double aux2Semi = 0.035*(v - w)*m_M4.amplitud()*qSin(qDegreesToRadians(2*m_M2.phase() - m_M4.phase()));
    double aux3Semi = 2*m_M6.amplitud()*qCos(qDegreesToRadians(3*m_M2.phase() - m_M6.phase()));

    double APS = mn + aux1Semi + aux2Semi + aux3Semi;

    m_APS = APS;

   //*****************Altura Promedio de Marea en Sicigias***************
    double aux1Sic = APS - qPow(m_S2.amplitud(),2)/2*m_M2.amplitud();

    double aux2Sic = qPow((m_K1.amplitud() + m_O1.amplitud())/m_M2.amplitud(),2);

    double aux3Sic = (1.96 - 0.08*aux2Sic)*m_S2.amplitud();

    m_APSS = aux1Sic + aux3Sic;

    //*****************Altura Promedio de la Marea en Cuadratura**************
    m_APC  = aux1Sic - aux3Sic;

    //****************Altura Promedio de la Marea Tropical****************************
    double aux1Trop = 0.042*(m_K1.amplitud() + m_O1.amplitud());
    double aux2Trop = (m_K1.amplitud() + m_O1.amplitud())*(qCos(qDegreesToRadians(v)) + qCos(qDegreesToRadians(w)));
    double aux3Trop = 0.035*m_M2.amplitud()*(v - w)*qSin(qDegreesToRadians(m_M2.phase() - m_K1.phase() - m_O1.phase()));

    m_APT = aux1Trop + aux2Trop - aux3Trop;
}
