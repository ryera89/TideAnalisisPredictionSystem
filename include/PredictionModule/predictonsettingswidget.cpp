#include "predictonsettingswidget.h"
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

PredictonSettingsWidget::PredictonSettingsWidget(
    const PredictionSettings &predSetting, QWidget *parent)
    : QWidget(parent) {
  m_methodLabel = new QLabel("Método:");
  m_nmmLabel = new QLabel("Datum:");
  m_fromLabel = new QLabel("Inicio:");
  m_toLabel = new QLabel("Fin:");
  m_intervalLabel = new QLabel("Intervalo:");

  m_methodComboBox = new QComboBox;
  m_methodComboBox->addItem("Factores Nodales Constantes");
  m_methodComboBox->addItem("Factores Nodales Variables");

  switch (predSetting.method()) {
  case PredictionSettings::NF_CTE:
    m_methodComboBox->setCurrentIndex(0);
    break;
  default:
    m_methodComboBox->setCurrentIndex(1);
    break;
  }

  m_nmmSpinBox = new QDoubleSpinBox;
  m_nmmSpinBox->setDecimals(3);
  m_nmmSpinBox->setSuffix("m");
  m_nmmSpinBox->setRange(-1000.0, 1000.0);
  m_nmmSpinBox->setValue(predSetting.nmm());

  m_fromDateEdit = new QDateTimeEdit(predSetting.from());
  m_fromDateEdit->setCalendarPopup(true);
  m_toDateEdit = new QDateTimeEdit(predSetting.to());
  m_toDateEdit->setCalendarPopup(true);

  m_intervalSpinBox = new QSpinBox;
  m_intervalSpinBox->setSuffix("min");
  m_intervalSpinBox->setMaximum(3600);
  m_intervalSpinBox->setValue(predSetting.interval() /
                              60); // Llevando de segundos a minnutos

  m_okPushButton = new QPushButton("Aceptar");
  connect(m_okPushButton, &QAbstractButton::clicked, this,
          &PredictonSettingsWidget::okButtonPressed);

  m_cancelPushButton = new QPushButton("Cancelar");
  connect(m_cancelPushButton, &QAbstractButton::clicked, this, &QWidget::close);

  interfazLayout();

  this->setWindowTitle(tr("Configuración"));
  this->setWindowIcon(QIcon(":images/configure2.png"));
  this->setWindowModality(Qt::ApplicationModal);
  this->setAttribute(Qt::WA_DeleteOnClose);
}

PredictionSettings::PredMethod
PredictonSettingsWidget::predictionMethod() const {
  switch (m_methodComboBox->currentIndex()) {
  case 0:
    return PredictionSettings::NF_CTE;
    break;
  default:
    return PredictionSettings::NF_VAR;
    break;
  }
}

double PredictonSettingsWidget::nmm() const { return m_nmmSpinBox->value(); }

QDateTime PredictonSettingsWidget::fromDateTime() const {
  return m_fromDateEdit->dateTime();
}

QDateTime PredictonSettingsWidget::endDateTime() const {
  return m_toDateEdit->dateTime();
}

quint64 PredictonSettingsWidget::interval() const {
  return m_intervalSpinBox->value() *
         60; // El intervalo es en segundos y el usuario lo entra en minutos
}

void PredictonSettingsWidget::interfazLayout() {
  QFormLayout *formLayout = new QFormLayout;
  formLayout->addRow(m_methodLabel, m_methodComboBox);
  formLayout->addRow(m_nmmLabel, m_nmmSpinBox);
  formLayout->addRow(m_fromLabel, m_fromDateEdit);
  formLayout->addRow(m_toLabel, m_toDateEdit);
  formLayout->addRow(m_intervalLabel, m_intervalSpinBox);

  QHBoxLayout *buttonLayout = new QHBoxLayout;
  buttonLayout->addWidget(m_okPushButton);
  buttonLayout->addWidget(m_cancelPushButton);

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addLayout(formLayout);
  mainLayout->addLayout(buttonLayout);
  mainLayout->setAlignment(buttonLayout, Qt::AlignRight);

  this->setLayout(mainLayout);
}
