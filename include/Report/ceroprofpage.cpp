#include "ceroprofpage.h"

#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>

#include <QFormLayout>
#include <QVBoxLayout>
CeroProfPage::CeroProfPage(QWidget *parent) : QWizardPage(parent) {
  setTitle("Datos sobre el cero de profundidad");

  m_ceroProfundidadLabel = new QLabel(tr("Cero de Profundidad:"));
  m_metodoCeroProfundidadLabel = new QLabel(tr("Método de determinación:"));
  m_periodoCeroProfundidadLabel = new QLabel(tr("Período de observaciones:"));
  m_sitCeroProfundidadCeroPuestoLabel = new QLabel(tr("Cero del puesto:"));
  m_sitCeroProfundidadNMMLabel = new QLabel(tr("Nivel medio del mar:"));
  m_sitCeroProfundidadChapaPrincipalLabel = new QLabel(tr("Chapa principal:"));
  m_nivelMinimoLabel = new QLabel(tr("Nivel mínimo observado:"));
  m_nivelMaximoLabel = new QLabel(tr("Nivel máximo observado:"));

  m_sitCeroProfGroupBox =
      new QGroupBox(tr("Situación del cero de profundidad respecto a"));
  m_oscNivelCeroProfGroupBox = new QGroupBox(
      tr("Oscilaciones del nivel del mar respecto al cero de profundidad"));

  m_ceroProfundidadEdit = new QLineEdit;
  m_metodoCeroProfundidadEdit = new QLineEdit;
  m_metodoCeroProfundidadEdit->setPlaceholderText(
      tr("método de cálculo del cero de profundidad"));
  m_periodoCeroProfundidadEdit = new QLineEdit;
  m_periodoCeroProfundidadEdit->setPlaceholderText(
      tr("tiempo determinado para calcular el cero de profundidad"));
  m_sitCeroProfundidadCeroPuestoEdit = new QLineEdit;
  m_sitCeroProfundidadNMMEdit = new QLineEdit;
  m_sitCeroProfundidadChapaPrincipalEdit = new QLineEdit;
  m_nivelMinimoEdit = new QLineEdit;
  m_nivelMaximoEdit = new QLineEdit;

  QFormLayout *layout1 = new QFormLayout;
  layout1->addRow(m_ceroProfundidadLabel, m_ceroProfundidadEdit);
  layout1->addRow(m_metodoCeroProfundidadLabel, m_metodoCeroProfundidadEdit);
  layout1->addRow(m_periodoCeroProfundidadLabel, m_periodoCeroProfundidadEdit);

  QFormLayout *layout2 = new QFormLayout;
  layout2->addRow(m_sitCeroProfundidadCeroPuestoLabel,
                  m_sitCeroProfundidadCeroPuestoEdit);
  layout2->addRow(m_sitCeroProfundidadNMMLabel, m_sitCeroProfundidadNMMEdit);
  layout2->addRow(m_sitCeroProfundidadChapaPrincipalLabel,
                  m_sitCeroProfundidadChapaPrincipalEdit);

  QFormLayout *layout3 = new QFormLayout;
  layout3->addRow(m_nivelMinimoLabel, m_nivelMinimoEdit);
  layout3->addRow(m_nivelMaximoLabel, m_nivelMaximoEdit);

  m_sitCeroProfGroupBox->setLayout(layout2);
  m_oscNivelCeroProfGroupBox->setLayout(layout3);

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addLayout(layout1);
  layout->addWidget(m_sitCeroProfGroupBox);
  layout->addWidget(m_oscNivelCeroProfGroupBox);

  setLayout(layout);
}

QString CeroProfPage::ceroDeProfundidad() const {
  return m_ceroProfundidadEdit->text();
}

QString CeroProfPage::metodoCeroDeProfundidad() const {
  return m_metodoCeroProfundidadEdit->text();
}

QString CeroProfPage::periodoObsCeroDeProfundidad() const {
  return m_periodoCeroProfundidadEdit->text();
}

QString CeroProfPage::situacionCeroProfundidad() const {
  return m_sitCeroProfGroupBox->title() + ":";
}

QString CeroProfPage::situacionCeroProfCeroPuesto() const {
  return m_sitCeroProfundidadCeroPuestoEdit->text();
}

QString CeroProfPage::situacionCeroProfNMM() const {
  return m_sitCeroProfundidadNMMEdit->text();
}

QString CeroProfPage::situacionCeroProfChapaPrincipal() const {
  return m_sitCeroProfundidadChapaPrincipalEdit->text();
}

QString CeroProfPage::oscilacionesRespectoACeroProfundidad() const {
  return m_oscNivelCeroProfGroupBox->title() + ":";
}

QString CeroProfPage::nivelMinimo() const { return m_nivelMinimoEdit->text(); }

QString CeroProfPage::nivelMaximo() const { return m_nivelMaximoEdit->text(); }
