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

QString metaDataWidget::latitud() const
{
    return m_latitudLineEdit->text();
}

QString metaDataWidget::longitud() const
{
    return m_longitudLineEdit->text();
}

QString metaDataWidget::equipmentID() const
{
    return m_equipmentIdLabel->text();
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

void metaDataWidget::setLatitud(const QString &str)
{
    m_latitudLineEdit->setText(str);
}

void metaDataWidget::setLongitud(const QString &str)
{
    m_longitudLineEdit->setText(str);
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

    m_localizationNameLabel = new QLabel(tr("Localización"),this);
    m_localizationNameLineEdit = new QLineEdit(this);

    m_latitudLabel = new QLabel(tr("Latitud:"),this);
    m_latitudLineEdit = new QLineEdit(this);

    m_longitudLabel = new QLabel(tr("Longitud:"),this);
    m_longitudLineEdit = new QLineEdit(this);

    m_equipmentIdLabel = new QLabel(tr("Equipo ID:"),this);
    m_equipmentIdLineEdit = new QLineEdit(this);
}

void metaDataWidget::interfazLayout()
{
    QHBoxLayout *lat_longLayout = new QHBoxLayout;
    lat_longLayout->addWidget(m_latitudLabel);
    lat_longLayout->addWidget(m_latitudLineEdit);
    lat_longLayout->addStretch();
    lat_longLayout->addWidget(m_longitudLabel);
    lat_longLayout->addWidget(m_longitudLineEdit);

    QFormLayout *mainLayout = new QFormLayout;
    mainLayout->addRow(m_projectNameLabel,m_projectNameLineEdit);
    mainLayout->addRow(m_stationNameLabel,m_stationNameLineEdit);
    mainLayout->addRow(m_localizationNameLabel,m_localizationNameLineEdit);
    mainLayout->addRow(lat_longLayout);
    mainLayout->addRow(m_equipmentIdLabel,m_equipmentIdLineEdit);

    this->setLayout(mainLayout);
}
