#include "nivelacion_acuatica_calculo.h"

qreal calcularNivelacionAcuatica1PuestoPermanete(const QVector<TidesMeasurement> &mp, const QVector<TidesMeasurement> &m0, qreal nmm0)
{
  if (mp.size() != m0.size()) return 0.0; //Retorna 0 si el el set de mediciones no coincide en size

  qreal diffSum = 0.0;
  for (int i = 0; i < mp.size(); ++i){
      diffSum += mp.at(i).seaLevel() - m0.at(i).seaLevel(); //Compute the sum of the level diferences
  }

  diffSum/=mp.size();  //media de las diferencias

  return nmm0 + diffSum;

}


qreal calcularNivelacionAcuatica1PuestoPermanete(const QVector<TidesMeasurement> &diff, qreal nmm0)
{
    qreal diffSum = 0.0;

    foreach (TidesMeasurement measurement, diff) {
        diffSum += measurement.seaLevel(); //Compute the sum of the level diferences
    }

    diffSum/=diff.size(); //media de las diferencias

    return nmm0 + diffSum;
}

qreal calcularNivelacionAcuatica2PuestoPermanete(const QVector<TidesMeasurement> &mp, const QVector<TidesMeasurement> &m01, const QVector<TidesMeasurement> &m02, qreal nmm01, qreal nmm02, const QGeoCoordinate &coordinateP, const QGeoCoordinate &coordinate01, const QGeoCoordinate &coordinate02)
{
    qreal nmm1 = calcularNivelacionAcuatica1PuestoPermanete(mp,m01,nmm01);
    qreal nmm2 = calcularNivelacionAcuatica1PuestoPermanete(mp,m02,nmm02);

    qreal S1 = coordinateP.distanceTo(coordinate01);
    qreal S2 = coordinateP.distanceTo(coordinate02);

    return (nmm1*S2 + nmm2+S1)/(S2+S1);
}

qreal calcularNivelacionAcuatica2PuestoPermanete(const QVector<TidesMeasurement> &diff1, const QVector<TidesMeasurement> &diff2, qreal nmm01, qreal nmm02, const QGeoCoordinate &coordinateP, const QGeoCoordinate &coordinate01, const QGeoCoordinate &coordinate02)
{
    qreal nmm1 = calcularNivelacionAcuatica1PuestoPermanete(diff1,nmm01);
    qreal nmm2 = calcularNivelacionAcuatica1PuestoPermanete(diff2,nmm02);

    qreal S1 = coordinateP.distanceTo(coordinate01);
    qreal S2 = coordinateP.distanceTo(coordinate02);

    return (nmm1*S2 + nmm2+S1)/(S2+S1);

}
