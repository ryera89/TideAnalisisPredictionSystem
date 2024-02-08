#ifndef PROJECTMETADATA_H
#define PROJECTMETADATA_H

#include "../MeasurementUnitEditWidget/measurementuniteditwidget.h"
#include <QString>

class ProjectMetaData {
public:
  ProjectMetaData();
  ProjectMetaData(const QString &projectName, const QString &stationName,
                  const QString &localizationName, const double &cero,
                  const double &referencia, const double &latitud,
                  const double &longitud, const QString &equipmentId,
                  const int &timeZoneOffSet, bool daylightTimeSaving,
                  MeasurementUnitEditWidget::Units ceroUnits,
                  MeasurementUnitEditWidget::Units referenciaUnits)
      : m_projectName(projectName), m_stationName(stationName),
        m_localizationName(localizationName), m_ceroPuesto(cero),
        m_nivelReferencia(referencia), m_latitud(latitud), m_longitud(longitud),
        m_equipmentId(equipmentId), m_timeZoneOffset(timeZoneOffSet),
        m_DaylightTimeSaving(daylightTimeSaving), displayZeroUnits(ceroUnits),
        displayReferenceUnits(referenciaUnits) {}

  QString projectName() const { return m_projectName; }
  QString stationName() const { return m_stationName; }
  QString localizationName() const { return m_localizationName; }
  double latitud() const { return m_latitud; }
  double longitud() const { return m_longitud; }
  double ceroPuesto() const { return m_ceroPuesto; }
  double nivelReferencia() const { return m_nivelReferencia; }
  QString equipmentID() const { return m_equipmentId; }
  MeasurementUnitEditWidget::Units ceroUnit() const { return displayZeroUnits; }
  MeasurementUnitEditWidget::Units referenciaUnit() const {
    return displayReferenceUnits;
  }
  int timeZoneOffset() const { return m_timeZoneOffset; }
  bool isDaylightTimeSaving() const { return m_DaylightTimeSaving; }

  void setProjectName(const QString &str) { m_projectName = str; }
  void setStationName(const QString &str) { m_stationName = str; }
  void setLocalizationName(const QString &str) { m_localizationName = str; }
  void setLatitud(double latitud) { m_latitud = latitud; }
  void setLongitud(double longitud) { m_longitud = longitud; }
  void setCeroPuesto(double cero) { m_ceroPuesto = cero; }
  void setNivelReferencia(double referencia) { m_nivelReferencia = referencia; }
  void setEquipmentID(const QString &str) { m_equipmentId = str; }
  void setCeroUnits(MeasurementUnitEditWidget::Units ceroUnits);
  void setReferenceUnits(MeasurementUnitEditWidget::Units referenceUnits);

  void setTimeZoneOffSet(int timeOffset) { m_timeZoneOffset = timeOffset; }
  void setDayLightTimeSaving(bool status) { m_DaylightTimeSaving = status; }

private:
  QString m_projectName;
  QString m_stationName;
  QString m_localizationName;
  double m_ceroPuesto;
  double m_nivelReferencia;
  double m_latitud;
  double m_longitud;
  QString m_equipmentId;

  int m_timeZoneOffset;      // Offset en horas desde UTC
  bool m_DaylightTimeSaving; // Si es horario de verano

  MeasurementUnitEditWidget::Units displayZeroUnits;
  MeasurementUnitEditWidget::Units displayReferenceUnits;
};

#endif // PROJECTMETADATA_H
