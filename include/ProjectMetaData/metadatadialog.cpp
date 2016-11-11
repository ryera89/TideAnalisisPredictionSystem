#include "metadatadialog.h"
#include "metadatawidget.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include "include/ProjectMetaData/projectmetadata.h"

MetaDataDialog::MetaDataDialog(const ProjectMetaData &data,QWidget *parent, Qt::WindowFlags f):QDialog(parent,f)
{
    this->setWindowTitle(tr("Información del Proyecto"));
    createComponets();
    interfazLayout();

    m_metadata->setProjectName(data.projectName());
    m_metadata->setStationName(data.stationName());
    m_metadata->setLocalizationName(data.localizationName());
    m_metadata->setLatitud(data.latitud());
    m_metadata->setLongitud(data.longitud());
    m_metadata->setEquipmentID(data.equipmentID());

    this->setWindowIcon(QIcon(":images/project-info.png"));
    this->setAttribute(Qt::WA_DeleteOnClose);
}

QString MetaDataDialog::projectName() const
{
    return m_metadata->projectName();
}

QString MetaDataDialog::stationName() const
{
    return m_metadata->stationName();
}

QString MetaDataDialog::localizationName() const
{
    return m_metadata->localizationName();
}

double MetaDataDialog::latitud() const
{
    return m_metadata->latitud();
}

double MetaDataDialog::longitud() const
{
    return m_metadata->longitud();
}

QString MetaDataDialog::equipmentId() const
{
    return m_metadata->equipmentID();
}

void MetaDataDialog::createComponets()
{
    m_metadata = new metaDataWidget(this);

    m_okButton = new QPushButton(QIcon(":images/Ok.png"),tr("Aceptar"),this);
    connect(m_okButton,SIGNAL(clicked(bool)),this,SIGNAL(okButtonClicked(bool)));

    m_cancelButton = new QPushButton(QIcon(":images/No.png"),tr("Cancelar"),this);
    connect(m_cancelButton,SIGNAL(clicked(bool)),this,SLOT(close()));

    m_groupBox = new QGroupBox(this);
}

void MetaDataDialog::interfazLayout()
{
    m_groupBox->setLayout(m_metadata->layout());

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch();
    buttonLayout->addWidget(m_okButton);
    buttonLayout->addWidget(m_cancelButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_groupBox);
    mainLayout->addLayout(buttonLayout);

    this->setLayout(mainLayout);
}
