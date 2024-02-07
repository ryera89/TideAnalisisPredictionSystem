#include "measurementuniteditwidget.h"

#include <QComboBox>
#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <iostream>
MeasurementUnitEditWidget::MeasurementUnitEditWidget(QWidget *parent)
    : QFrame(parent) {
  m_value = 0.0;

  m_spinBox = new QDoubleSpinBox;
  m_spinBox->setDecimals(3);
  m_spinBox->setRange(INT64_MIN, INT64_MAX);

  m_comboBox = new QComboBox;
  m_comboBox->addItem("m");
  m_comboBox->addItem("dm");
  m_comboBox->addItem("cm");
  m_comboBox->addItem("mm");
  m_comboBox->setFixedWidth(43);

  QHBoxLayout *myLayout = new QHBoxLayout;
  myLayout->addWidget(m_spinBox);
  myLayout->addWidget(m_comboBox);
  myLayout->setSpacing(0);

  this->setLayout(myLayout);
  this->layout()->setMargin(0);

  connect(m_spinBox, SIGNAL(valueChanged(double)), this,
          SLOT(spinBoxValueChanged(double)));
  connect(m_comboBox, SIGNAL(currentIndexChanged(int)), this,
          SLOT(comboBoxIndexChanged(int)));
  connect(this, SIGNAL(value_type_Changed(int, double)), this,
          SLOT(setValue(int, double)));
}
double MeasurementUnitEditWidget::value() const { return m_value; }

MeasurementUnitEditWidget::Units MeasurementUnitEditWidget::unit() const {
  switch (m_comboBox->currentIndex()) {
  case 0:
    return Units::M;
    break;
  case 1:
    return Units::DM;
    break;
  case 2:
    return Units::CM;
    break;
  case 3:
    return Units::MM;
    break;
  default:
    break;
  }
  return Units::M;
}
void MeasurementUnitEditWidget::spinBoxValueChanged(double value) {
  emit value_type_Changed(m_comboBox->currentIndex(), value);
}

void MeasurementUnitEditWidget::comboBoxIndexChanged(int index) {
  emit value_type_Changed(index, m_spinBox->value());
}

void MeasurementUnitEditWidget::setValue(
    int index,
    double value) // El valor guardado siempre esta en SI de unidade m o kg
{
  switch (index) {
  case 1:
    m_value = value / 10;
    break;
  case 2:
    m_value = value / 100;
    break;
  case 3:
    m_value = value / 1000;
    break;
  default:
    m_value = value;
    break;
  }

  // std::cout << m_value << " " << index << std::endl;
}

void MeasurementUnitEditWidget::setSpinAndComboBoxesValues(Units u,
                                                           double value) {
  switch (u) {
  case Units::DM:
    value *= 10;
    break;
  case Units::CM:
    value *= 100;
    break;
  case Units::MM:
    value *= 1000;
    break;
  default:
    break;
  }
  m_comboBox->setCurrentIndex(u);
  m_spinBox->setValue(value);
}
