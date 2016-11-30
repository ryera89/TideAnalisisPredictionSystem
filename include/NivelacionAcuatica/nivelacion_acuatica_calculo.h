#ifndef NIVELACION_ACUATICA_CALCULO_H
#define NIVELACION_ACUATICA_CALCULO_H

#include <QtCore>
#include <QtPositioning/QGeoCoordinate>
#include "include/measurement/measurement.h"

//retorna el nivel medio del mar del puesto provicional usando un puesto permanente
//mp: mediciones puesto provicional
//m0: mediciones puesto permanente
//nmm0: nivel medio del mar del puesto permanente
qreal calcularNivelacionAcuatica1PuestoPermanete(const QVector<TidesMeasurement> &mp, const QVector<TidesMeasurement> &m0, qreal nmm0);
//diff: diferencias de nivel con puesto permanente
qreal calcularNivelacionAcuatica1PuestoPermanete(const QVector<TidesMeasurement> &diff,qreal nmm0);

//retorna el nivel medio del mar del puesto provicional usando 2 puestos permanentes
//mp: mediciones puesto provicional
//m01: mediciones puesto permanente 1
//m02: mediciones puesto permanente 2
//nmm01: nivel medio del mar del puesto permanente 1
//nmm02: nivel medio del mar del puesto permanente 2
//coordinateP: coordenadas del puesto de nivel provicional
//coordinate01: coordenadas del puesto de nivel permanente 1
//coordinate02: coordenadas del puesto de nivel permanente 2
qreal calcularNivelacionAcuatica2PuestoPermanete(const QVector<TidesMeasurement> &mp, const QVector<TidesMeasurement> &m01,
                                                 const QVector<TidesMeasurement> &m02, qreal nmm01, qreal nmm02,const QGeoCoordinate &coordinateP,
                                                 const QGeoCoordinate &coordinate01, const QGeoCoordinate &coordinate02);
//diff1 diferencias de nivel con el puesto permanente 1
//diff2 diferencias de nivel con el puesto permanente 2
qreal calcularNivelacionAcuatica2PuestoPermanete(const QVector<TidesMeasurement> &diff1, const QVector<TidesMeasurement> &diff2, qreal nmm01,
                                                 qreal nmm02,const QGeoCoordinate &coordinateP, const QGeoCoordinate &coordinate01, const QGeoCoordinate &coordinate02);
#endif // NIVELACION_ACUATICA_CALCULO_H
