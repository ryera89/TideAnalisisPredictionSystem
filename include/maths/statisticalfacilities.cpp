#include "statisticalfacilities.h"



double mean(const QVector<double> &measurements)      //calcula el valor medio de una muestra
{
    double ave = 0.0;
    for (int i = 0; i < measurements.size(); ++i){
        ave += measurements[i];
    }
    ave/=measurements.size();
    return ave;
}

double mean(const valarray<double> &measurements)      //calcula el valor medio de una muestra
{
    double ave = 0.0;

    for (int i = 0; i < measurements.size(); ++i){
        ave += measurements[i];
    }
    ave/=measurements.size();
    return ave;
}

double varianza(const QVector<double> &measurements){
    double var = 0.0;
    double ave = mean(measurements);

    uint N = measurements.size();

    double temp1 = 0.0;
    double temp2 = 0.0;

    for (int j = 0; j < N; ++j){
        temp1+=(pow((measurements[j]-ave),2.0));
        temp2+=(measurements[j] - ave);
    }
    temp2 = pow(temp2,2.0)/N;
    var = (temp1 - temp2)/(N-1);

    return var;
}
double varianza(const valarray<double> &measurements){
    double var = 0.0;
    double ave = mean(measurements);

    uint N = measurements.size();

    double temp1 = 0.0;
    double temp2 = 0.0;

    for (int j = 0; j < N; ++j){
        temp1+=(pow((measurements[j]-ave),2.0));
        temp2+=(measurements[j] - ave);
    }
    temp2 = pow(temp2,2.0)/N;
    var = (temp1 - temp2)/(N-1);

    return var;
}

double desvstd(const QVector<double> &measurements){
    return sqrt(varianza(measurements));
}
double desvstd(const valarray<double> &measurements){
    return sqrt(varianza(measurements));
}


double absMeanDesv(const QVector<double> &measurement)
{
    double amdesv = 0.0;

    double ave = mean(measurement);

    int N = measurement.size();

    for (int j = 0; j < N; ++j){
        amdesv += abs(measurement[j] - ave);
    }

    return amdesv/N;
}
double absMeanDesv(const valarray<double> &measurement)
{
    double amdesv = 0.0;

    double ave = mean(measurement);

    int N = measurement.size();

    for (int j = 0; j < N; ++j){
        amdesv += abs(measurement[j] - ave);
    }

    return amdesv/N;
}
double skewnees(const QVector<double> &measurements)
{
    double skew = 0.0;
    double desv = desvstd(measurements);
    double ave = mean(measurements);

    int N = measurements.size();

    double temp = 0.0;
    for (int j = 0; j < N; ++j){
        temp+= pow((measurements[j] - ave),3.0);
    }
    temp/=pow(desv,3.0);

    skew = temp/N;

    return skew;
}
double skewnees(const valarray<double> &measurements)
{
    double skew = 0.0;
    double desv = desvstd(measurements);
    double ave = mean(measurements);

    int N = measurements.size();

    double temp = 0.0;
    for (int j = 0; j < N; ++j){
        temp+= pow((measurements[j] - ave),3.0);
    }
    temp/=pow(desv,3.0);

    skew = temp/N;

    return skew;
}
double kurtosis(const valarray<double> &measurements)
{
    double kurt = 0.0;
    double desv = desvstd(measurements);
    double ave = mean(measurements);

    int N = measurements.size();

    double temp = 0.0;
    for (int j = 0; j < N; ++j){
        temp+= pow((measurements[j] - ave),4.0);
    }
    temp/=pow(desv,4.0);

    kurt = temp/N - 3.0;

    return kurt;
}

double kurtosis(const QVector<double> &measurements)
{
    double kurt = 0.0;
    double desv = desvstd(measurements);
    double ave = mean(measurements);

    int N = measurements.size();

    double temp = 0.0;
    for (int j = 0; j < N; ++j){
        temp+= pow((measurements[j] - ave),4.0);
    }
    temp/=pow(desv,4.0);

    kurt = temp/N - 3.0;

    return kurt;
}
