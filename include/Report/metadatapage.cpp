#include "metadatapage.h"
#include <QLabel>
#include <QDateEdit>
#include <QLineEdit>
#include <QFormLayout>
#include <QGroupBox>
#include <QVBoxLayout>

MetadataPage::MetadataPage(QWidget *parent):QWizardPage(parent)
{
    setTitle(tr("Datos Generales del Puesto"));

    m_nombrePuestoLabel = new QLabel(tr("Puesto:"));
    m_establecimientoLabel = new QLabel(tr("Establecimiento:"));
    m_ceroPuestoLabel = new QLabel(tr("Cero del puesto:"));
    m_nivelReferenciaLabel = new QLabel(tr("Nivel de referencia:"));
    m_latitudLabel = new QLabel(tr("Latitud:"));
    m_longitudLabel = new QLabel(tr("Longitud:"));
    m_fechaInicioLabel = new QLabel(tr("Inicio de observaciones:"));
    m_fechaFinalLabel = new QLabel(tr("Fin de observaciones:"));
    m_duracionLabel = new QLabel(tr("Duración de obseravaciones:"));
    m_usoHorarioLabel = new QLabel(tr("Huso Horario:"));
    m_apellidosResponsableLabel = new QLabel(tr("Apellidos:"));
    m_nombreResponsableLabel = new QLabel(tr("Nombre:"));
    m_dptoLabel = new QLabel(tr("Departamento:"));

    m_nombrePuestoEdit = new QLineEdit;
    m_nombrePuestoEdit->setPlaceholderText(tr("Nombre del puesto"));
    m_establecimientoEdit = new QLineEdit;
    m_establecimientoEdit->setPlaceholderText(tr("(Mar, Bahía, Cabo, Población)"));
    m_ceroPuestoEdit = new QLineEdit;
    m_nivelReferenciaEdit = new QLineEdit;
    m_latitudEdit = new QLineEdit;
    m_longitudEdit = new QLineEdit;
    m_fechaInicioDateEdit = new QDateEdit;
    m_fechaInicioDateEdit->setDisplayFormat("dd/MM/yyyy");
    m_fechaInicioDateEdit->setCalendarPopup(true);
    m_fechaFinalDateEdit = new QDateEdit;
    m_fechaFinalDateEdit->setDisplayFormat("dd/MM/yyyy");
    m_fechaFinalDateEdit->setCalendarPopup(true);
    m_duracionEdit = new QLineEdit;
    m_usoHorarioEdit = new QLineEdit;
    m_apellidosResponsableEdit = new QLineEdit;
    m_apellidosResponsableEdit->setPlaceholderText(tr("Apellidos"));
    m_nombreResponsableEdit = new QLineEdit;
    m_nombreResponsableEdit->setPlaceholderText(tr("Nombre"));
    m_dptoEdit = new QLineEdit;
    m_dptoEdit->setPlaceholderText(tr("Dpto"));

    m_responsabeGroupBox = new QGroupBox(tr("Resposable de las observaciones"));

    QFormLayout *layout1 = new QFormLayout;
    layout1->addRow(m_nombrePuestoLabel,m_nombrePuestoEdit);
    layout1->addRow(m_establecimientoLabel,m_establecimientoEdit);
    layout1->addRow(m_ceroPuestoLabel,m_ceroPuestoEdit);
    layout1->addRow(m_nivelReferenciaLabel,m_nivelReferenciaEdit);
    layout1->addRow(m_latitudLabel,m_latitudEdit);
    layout1->addRow(m_longitudLabel,m_longitudEdit);
    layout1->addRow(m_fechaInicioLabel,m_fechaInicioDateEdit);
    layout1->addRow(m_fechaFinalLabel,m_fechaFinalDateEdit);
    layout1->addRow(m_duracionLabel,m_duracionEdit);
    layout1->addRow(m_usoHorarioLabel,m_usoHorarioEdit);

    QFormLayout *layout2 = new QFormLayout;
    layout2->addRow(m_apellidosResponsableLabel,m_apellidosResponsableEdit);
    layout2->addRow(m_nombreResponsableLabel,m_nombreResponsableEdit);
    layout2->addRow(m_dptoLabel,m_dptoEdit);

    m_responsabeGroupBox->setLayout(layout2);


    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(layout1);
    layout->addWidget(m_responsabeGroupBox);

    setLayout(layout);
}

QString MetadataPage::nombrePuesto() const
{
    return m_nombrePuestoEdit->text();
}

QString MetadataPage::establecimiento() const
{
    return m_establecimientoEdit->text();
}

QString MetadataPage::ceroPuesto() const
{
    return m_ceroPuestoEdit->text();
}

QString MetadataPage::nivelReferencia() const
{
    return m_nivelReferenciaEdit->text();
}

QString MetadataPage::latitud() const
{
    return m_latitudEdit->text();
}

QString MetadataPage::longitud() const
{
    return m_longitudEdit->text();
}

QString MetadataPage::fechaInicio() const
{
    return m_fechaInicioDateEdit->date().toString("dd/MM/yyyy");
}

QString MetadataPage::fechaFinal() const
{
    return m_fechaFinalDateEdit->date().toString("dd/MM/yyyy");
}

QString MetadataPage::duracion() const
{
    return m_duracionEdit->text();
}

QString MetadataPage::usoHorario() const
{
    return m_usoHorarioEdit->text();
}

QString MetadataPage::responsableHeader() const
{
    return m_responsabeGroupBox->title() + ":";
}

QString MetadataPage::responsable() const
{
    return m_nombreResponsableEdit->text() + " " + m_apellidosResponsableEdit->text();
}

QString MetadataPage::responsabeDpto() const
{
    return m_dptoEdit->text();
}

void MetadataPage::setMetaData(const ProjectMetaData &metadata)
{
    QString puesto(metadata.stationName());
    m_nombrePuestoEdit->setText(puesto);

    int timeOffset = metadata.timeZoneOffset();

    QString timeZone("UTC+00:00");

    if (timeOffset > 0){
        if (timeOffset < 10){
            timeZone = "UTC+0" + QString::number(timeOffset) + ":00";
        }else{
            timeZone = "UTC+" + QString::number(timeOffset) + ":00";
        }

    }
    if (timeOffset < 0){
        if (timeOffset > -10){
            timeZone = "UTC-0" + QString::number(qAbs(timeOffset)) + ":00";
        }else{
            timeZone = "UTC-" + QString::number(qAbs(timeOffset)) + ":00";
        }
    }
    m_usoHorarioEdit->setText(timeZone);

    QString cerodelpuesto = QString::number(metadata.ceroPuesto(),'f',3) + "m";
    m_ceroPuestoEdit->setText(cerodelpuesto);

    QString niveldereferencia = QString::number(metadata.nivelReferencia(),'f',3) + "m";
    m_nivelReferenciaEdit->setText(niveldereferencia);

    double latitud = metadata.latitud();
    QString latitudStr("0.000");
    if (latitud > 0.0){
        latitudStr = QString::number(latitud,'f',3) + "⁰ N";
    }
    if (latitud < 0.0){
        latitudStr = QString::number(qAbs(latitud),'f',3) + "⁰ S";
    }
    m_latitudEdit->setText(latitudStr);

    double longitud = metadata.longitud();
    QString longitudStr("0.000");
    if (longitud > 0.0){
        longitudStr = QString::number(longitud,'f',3) + "⁰ E";
    }
    if (longitud < 0.0){
        longitudStr = QString::number(qAbs(longitud),'f',3) + "⁰ W";
    }
    m_longitudEdit->setText(longitudStr);
}

void MetadataPage::setMeasurementsPeriod(const QDate &begin, const QDate &end)
{
    m_fechaInicioDateEdit->setDate(begin);
    m_fechaFinalDateEdit->setDate(end);

    qint64 period = begin.daysTo(end);

    m_duracionEdit->setText(QString::number(period + 1) + " días");
}
