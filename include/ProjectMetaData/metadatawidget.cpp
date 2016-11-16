#include "metadatawidget.h"
#include <QLineEdit>
#include <QLabel>
#include <QFormLayout>
#include <QHBoxLayout>

metaDataWidget::metaDataWidget(QWidget *parent) : QWidget(parent)
{
    createComponents();
    interfazLayout();
}

QString metaDataWidget::projectName() const
{
    return m_projectNameLineEdit->text();
}

QString metaDataWidget::stationName() const
{
    return m_stationNameLineEdit->text();
}

QString metaDataWidget::localizationName() const
{
    return m_localizationNameLineEdit->text();
}

double metaDataWidget::ceroPuesto() const
{
    return m_ceroPuestoEdit->value();
}

double metaDataWidget::nivelReferencia() const
{
    return m_nivelReferenciaEdit->value();
}

MeasurementUnitEditWidget::Units metaDataWidget::ceroUnit() const
{
    return m_ceroPuestoEdit->unit();
}

MeasurementUnitEditWidget::Units metaDataWidget::referenciaUnit() const
{
    return m_nivelReferenciaEdit->unit();
}

double metaDataWidget::latitud() const
{
    return m_latitudEdit->coordinate();
}

double metaDataWidget::longitud() const
{
    return m_longitudEdit->coordinate();
}

QString metaDataWidget::equipmentID() const
{
    return m_equipmentIdLineEdit->text();
}

void metaDataWidget::setProjectName(const QString &str)
{
    m_projectNameLineEdit->setText(str);
}

void metaDataWidget::setStationName(const QString &str)
{
    m_stationNameLineEdit->setText(str);
}

void metaDataWidget::setLocalizationName(const QString &str)
{
    m_localizationNameLineEdit->setText(str);
}

void metaDataWidget::setCeroPuestoValueAndUnit(MeasurementUnitEditWidget::Units unit, double value)
{
    m_ceroPuestoEdit->setSpinAndComboBoxesValues(unit,value);
}

void metaDataWidget::setNivelReferenciaValueAndUnit(MeasurementUnitEditWidget::Units unit, double value)
{
    m_nivelReferenciaEdit->setSpinAndComboBoxesValues(unit,value);
}


void metaDataWidget::setLatitud(double latitud)
{
    m_latitudEdit->setEditorAndComboValue(latitud);
}

void metaDataWidget::setLongitud(double longitud)
{
    m_longitudEdit->setEditorAndComboValue(longitud);
}

void metaDataWidget::setEquipmentID(const QString &str)
{
    m_equipmentIdLineEdit->setText(str);
}

void metaDataWidget::createComponents()
{
    m_projectNameLabel = new QLabel(tr("Proyecto:"),this);
    m_projectNameLineEdit = new QLineEdit(this);

    m_stationNameLabel = new QLabel(tr("Puesto:"),this);
    m_stationNameLineEdit = new QLineEdit(this);

    m_localizationNameLabel = new QLabel(tr("Localización:"),this);
    m_localizationNameLineEdit = new QLineEdit(this);

    m_ceroPuestoLabel = new QLabel(tr("Cero del Puesto:"),this);
    m_ceroPuestoEdit = new MeasurementUnitEditWidget(this);

    m_nivelReferenciaLabel = new QLabel(tr("Nivel de Referencia:"),this);
    m_nivelReferenciaEdit = new MeasurementUnitEditWidget(this);

    m_latitudLabel = new QLabel(tr("Latitud:"),this);
    m_latitudEdit = new MyCoordinatesEditorWidget(this);

    m_longitudLabel = new QLabel(tr("Longitud:"),this);
    m_longitudEdit = new MyCoordinatesEditorWidget(this);
    m_longitudEdit->setHType(MyCoordinatesEditorWidget::longitud);

    m_equipmentIdLabel = new QLabel(tr("Equipo ID:"),this);
    m_equipmentIdLineEdit = new QLineEdit(this);
}

void metaDataWidget::interfazLayout()
{
    /*QHBoxLayout *lat_longLayout = new QHBoxLayout;
    lat_longLayout->addWidget(m_latitudLabel);
    lat_longLayout->addWidget(m_latitudEdit);
    lat_longLayout->addStretch();
    lat_longLayout->addWidget(m_longitudLabel);
    lat_longLayout->addWidget(m_longitudEdit);*/

    /*QHBoxLayout *levelsLayout = new QHBoxLayout;
    levelsLayout->addWidget(m_ceroPuestoLabel);
    levelsLayout->addWidget(m_ceroPuestoEdit);
    levelsLayout->addStretch();
    levelsLayout->addWidget(m_nivelReferenciaLabel);
    levelsLayout->addWidget(m_nivelReferenciaEdit);*/

    QFormLayout *mainLayout = new QFormLayout;
    mainLayout->addRow(m_projectNameLabel,m_projectNameLineEdit);
    mainLayout->addRow(m_stationNameLabel,m_stationNameLineEdit);
    mainLayout->addRow(m_localizationNameLabel,m_localizationNameLineEdit);
    mainLayout->addRow(m_equipmentIdLabel,m_equipmentIdLineEdit);
    mainLayout->addRow(m_ceroPuestoLabel,m_ceroPuestoEdit);
    mainLayout->addRow(m_nivelReferenciaLabel,m_nivelReferenciaEdit);
    mainLayout->addRow(m_latitudLabel,m_latitudEdit);
    mainLayout->addRow(m_longitudLabel,m_longitudEdit);

    this->setLayout(mainLayout);
}
