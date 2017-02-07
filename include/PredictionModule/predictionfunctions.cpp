#include "predictionfunctions.h"
#include "include/HarmonicConstantsModule/HarmonicConstantClass/nodalfactorformulas.h"

#include <iostream>

//Interval en seconds 1h = 3600sec
QVector<TidesMeasurement> predictionWithNodalFactorCte(const double &datum, const QDateTime &from, const QDateTime &to, const quint64 &interval, const QVector<HarmonicConstant> &hcVector)
{
    AstronomicalMeanLongitudes beginV0(from);

    QDateTime middPoint = determineDataSerieMidPoint(from,to);

    AstronomicalMeanLongitudes midd_u_And_f(middPoint);

    QVector<double> hcF;
    QVector<double> hcV_u;
    for (int i = 0 ; i < hcVector.size(); ++i){
        double f = NodalAmplitudeFactor(hcVector.at(i),midd_u_And_f);
        double V0_plus_u = V0_u(hcVector.at(i),beginV0,midd_u_And_f);
        hcF.push_back(f);
        hcV_u.push_back(V0_plus_u);

        //std::cout << hcVector.at(i).name().toStdString() << " " << f << " " << V0_plus_u << std::endl;
    }

    QDateTime aux(from.date(),from.time(),Qt::UTC);
    QDateTime auxEnd(to.date(),to.time(),Qt::UTC);
    QVector<TidesMeasurement> resp;
    double t = 0.0;
    while (aux <= auxEnd){
        double h = datum;
        for (int i = 0; i < hcVector.size(); ++i){
            double aux1 = hcVector.at(i).frequency()*t;
            double aux2 = hcV_u.at(i);
            double aux3 = hcVector.at(i).correctedPhase();

            double rAmp =  hcF.at(i)*hcVector.at(i).amplitud();
            h += rAmp*qCos(qDegreesToRadians(aux1+aux2-aux3));
        }
        TidesMeasurement predMeas(h,aux);
        resp.push_back(predMeas);

        //std::cout << t << std::endl;
        t += interval/3600.0;
        aux = aux.addSecs(interval);
    }

  return resp;
}


QVector<TidesMeasurement> predictionWithNodalFactorVar(const double &datum, const QDateTime &from, const QDateTime &to, const quint64 &interval, const QVector<HarmonicConstant> &hcVector)
{
    AstronomicalMeanLongitudes beginV0(from);

    //QDateTime middPoint = determineDataSerieMidPoint(from,to);

    //AstronomicalMeanLongitudes midd_u_And_f(middPoint);

    //QVector<double> hcF;
    //QVector<double> hcV_u;
    /*for (int i = 0 ; i < hcVector.size(); ++i){
        AstronomicalMeanLongitudes astlong(aux);
        double f = NodalAmplitudeFactor(hcVector.at(i),astlong);
        double V0_plus_u = V0_u(hcVector.at(i),beginV0,astlong);
        hcF.push_back(f);
        hcV_u.push_back(V0_plus_u);
    }*/

    QDateTime aux(from.date(),from.time(),Qt::UTC);
    QDateTime auxEnd(to.date(),to.time(),Qt::UTC);
    double t = 0.0;
    QVector<TidesMeasurement> resp;
    while (aux <= auxEnd){
        double h = datum;
        AstronomicalMeanLongitudes astlong(aux);
        for (int i = 0; i < hcVector.size(); ++i){

            double f = NodalAmplitudeFactor(hcVector.at(i),astlong);
            double V0_plus_u = V0_u(hcVector.at(i),beginV0,astlong);

            double aux1 = hcVector.at(i).frequency()*t;
            double aux2 = V0_plus_u;
            double aux3 = hcVector.at(i).correctedPhase();

            double rAmp =  f*hcVector.at(i).amplitud();
            h += rAmp*qCos(qDegreesToRadians(aux1+aux2-aux3));
        }
        TidesMeasurement predMeas(h,aux);
        resp.push_back(predMeas);

        //std::cout << t << std::endl;
        //std::cout << aux.toString("dd/MM/yyyy hh:mm").toStdString() << std::endl;
        t += interval/3600.0;
        aux = aux.addSecs(interval);
    }

  return resp;
}
