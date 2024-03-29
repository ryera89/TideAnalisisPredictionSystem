#include "metadatadialog.h"
#include "metadatawidget.h"
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>

MetaDataDialog::MetaDataDialog(const ProjectMetaData &data, QWidget *parent,
                               Qt::WindowFlags f)
    : QDialog(parent, f) {
  this->setWindowTitle(tr("Información del Proyecto"));
  createComponets();
  interfazLayout();

  m_metadata->setProjectName(data.projectName());
  m_metadata->setStationName(data.stationName());
  m_metadata->setLocalizationName(data.localizationName());
  m_metadata->setCeroPuestoValueAndUnit(data.ceroUnit(), data.ceroPuesto());
  m_metadata->setNivelReferenciaValueAndUnit(data.referenciaUnit(),
                                             data.nivelReferencia());
  m_metadata->setLatitud(data.latitud());
  m_metadata->setLongitud(data.longitud());
  m_metadata->setEquipmentID(data.equipmentID());

  m_metadata->setTimeZoneOffset(data.timeZoneOffset());
  m_metadata->setDaylightTimeSaving(data.isDaylightTimeSaving());

  this->setModal(true);
  this->setWindowIcon(QIcon(":images/project-info.png"));
  this->setAttribute(Qt::WA_DeleteOnClose);
}

QString MetaDataDialog::projectName() const {
  return m_metadata->projectName();
}

QString MetaDataDialog::stationName() const {
  return m_metadata->stationName();
}

QString MetaDataDialog::localizationName() const {
  return m_metadata->localizationName();
}

double MetaDataDialog::ceroPuesto() const { return m_metadata->ceroPuesto(); }

double MetaDataDialog::nivelReferencia() const {
  return m_metadata->nivelReferencia();
}

double MetaDataDialog::latitud() const { return m_metadata->latitud(); }

double MetaDataDialog::longitud() const { return m_metadata->longitud(); }

MeasurementUnitEditWidget::Units MetaDataDialog::ceroPuestoUnit() const {
  return m_metadata->ceroUnit();
}

MeasurementUnitEditWidget::Units MetaDataDialog::nivelReferenciaUnit() const {
  return m_metadata->referenciaUnit();
}

QString MetaDataDialog::equipmentId() const {
  return m_metadata->equipmentID();
}

int MetaDataDialog::timeZoneOffset() const {
  return m_metadata->timeZoneOffset();
}

bool MetaDataDialog::isDaylightTimeSaving() const {
  return m_metadata->isDaylightTimeSaving();
}

void MetaDataDialog::createComponets() {
  m_metadata = new metaDataWidget(this);

  m_okButton = new QPushButton(QIcon(":images/Ok.png"), tr("Aceptar"), this);
  connect(m_okButton, SIGNAL(clicked(bool)), this,
          SIGNAL(okButtonClicked(bool)));

  m_cancelButton =
      new QPushButton(QIcon(":images/No.png"), tr("Cancelar"), this);
  connect(m_cancelButton, SIGNAL(clicked(bool)), this, SLOT(close()));

  m_groupBox = new QGroupBox(this);
}

void MetaDataDialog::interfazLayout() {
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
