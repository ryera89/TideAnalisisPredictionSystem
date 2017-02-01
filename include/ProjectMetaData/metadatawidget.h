#ifndef METADATAWIDGET_H
#define METADATAWIDGET_H

/*Facilities for project metadata introduction and edition*/

#include <QWidget>
#include "include/CoordinatesEditionWidget/mycoordinateseditorwidget.h"
#include "include/MeasurementUnitEditWidget/measurementuniteditwidget.h"
#include "timezoneselection.h"

class QLineEdit;
class QLabel;

class metaDataWidget : public QWidget
{
    Q_OBJECT
public:
    explicit metaDataWidget(QWidget *parent = 0);

    QString projectName() const;
    QString stationName() const;
    QString localizationName() const;
    double ceroPuesto() const;
    double nivelReferencia() const;
    MeasurementUnitEditWidget::Units ceroUnit() const;
    MeasurementUnitEditWidget::Units referenciaUnit() const;
    double latitud() const;
    double longitud() const;
    QString equipmentID() const;
    int timeZoneOffset() const;
    bool isDaylightTimeSaving() const;

    void setProjectName(const QString &str);
    void setStationName(const QString &str);
    void setLocalizationName(const QString &str);
    void setCeroPuestoValueAndUnit(MeasurementUnitEditWidget::Units unit,double value);
    void setNivelReferenciaValueAndUnit(MeasurementUnitEditWidget::Units unit, double value);
    void setLatitud(double);
    void setLongitud(double);
    void setEquipmentID(const QString &str);

    void setTimeZoneOffset(int timeOffset);
    void setDaylightTimeSaving(bool daylightTimeSaving);

signals:

public slots:

private:
    QLabel *m_projectNameLabel;
    QLabel *m_stationNameLabel;
    QLabel *m_localizationNameLabel;
    QLabel *m_latitudLabel;
    QLabel *m_longitudLabel;
    QLabel *m_equipmentIdLabel;
    QLabel *m_ceroPuestoLabel;
    QLabel *m_nivelReferenciaLabel;

    QLabel *m_timeZoneLabel;


    QLineEdit *m_projectNameLineEdit;
    QLineEdit *m_stationNameLineEdit;
    QLineEdit *m_localizationNameLineEdit;
    MeasurementUnitEditWidget *m_ceroPuestoEdit;
    MeasurementUnitEditWidget *m_nivelReferenciaEdit;
    MyCoordinatesEditorWidget *m_latitudEdit;
    MyCoordinatesEditorWidget *m_longitudEdit;
    QLineEdit *m_equipmentIdLineEdit;

    MeasurementUnitEditWidget::Units ceroDisplayUnits;
    MeasurementUnitEditWidget::Units referenciaDisplayUnits;

    TimeZoneSelection *m_timeZone;

    void createComponents();
    void interfazLayout();


};

#endif // METADATAWIDGET_H
