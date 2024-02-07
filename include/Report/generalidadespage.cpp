#include "generalidadespage.h"

#include <QGroupBox>
#include <QPlainTextEdit>
#include <QVBoxLayout>
GeneralidadesPage::GeneralidadesPage(QWidget *parent) : QWizardPage(parent) {
  setTitle(tr("Establecimiento del puesto"));

  m_descrCostaGroupBox = new QGroupBox(tr("Descripción de la costa"));
  m_descrMareografoGroupBox = new QGroupBox(tr("Datos del mareógrafo"));
  m_descrMarInstGroupBox =
      new QGroupBox(tr("Descripción de la instalación del mareógrafo"));
  m_descrAveriasGroupBox =
      new QGroupBox(tr("Datos sobre averías en los dispositivos de nivel"));

  m_descrCostaTextEdit = new QPlainTextEdit;
  m_descrCostaTextEdit->setPlaceholderText(
      tr("estabilidad, relieve de fondo, distribución de las profundidades, "
         "etc."));
  m_descrMareografoTextEdit = new QPlainTextEdit;
  m_descrMareografoTextEdit->setPlaceholderText(
      tr("número, tipo, período de función, etc."));
  m_descrMarInstTextEdit = new QPlainTextEdit;
  m_descrMarInstTextEdit->setPlaceholderText(
      tr("distancia de la costa, profundidad, método de instalación, etc."));
  m_descrAveriasTextEdit = new QPlainTextEdit;
  m_descrAveriasTextEdit->setPlaceholderText(
      tr("número de la regla, mareógrafo, carácter de la avería, medidas "
         "tomadas, nivelaciones de control, etc."));

  QVBoxLayout *layout1 = new QVBoxLayout;
  layout1->addWidget(m_descrCostaTextEdit);

  QVBoxLayout *layout2 = new QVBoxLayout;
  layout2->addWidget(m_descrMareografoTextEdit);

  QVBoxLayout *layout3 = new QVBoxLayout;
  layout3->addWidget(m_descrMarInstTextEdit);

  QVBoxLayout *layout4 = new QVBoxLayout;
  layout4->addWidget(m_descrAveriasTextEdit);

  m_descrCostaGroupBox->setLayout(layout1);
  m_descrMareografoGroupBox->setLayout(layout2);
  m_descrMarInstGroupBox->setLayout(layout3);
  m_descrAveriasGroupBox->setLayout(layout4);

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(m_descrCostaGroupBox);
  layout->addWidget(m_descrMareografoGroupBox);
  layout->addWidget(m_descrMarInstGroupBox);
  layout->addWidget(m_descrAveriasGroupBox);

  setLayout(layout);
}

QString GeneralidadesPage::descripcionCosta() const {
  return m_descrCostaTextEdit->toPlainText();
}

QString GeneralidadesPage::descripcionMareografo() const {
  return m_descrMareografoTextEdit->toPlainText();
}

QString GeneralidadesPage::descripcionInstalacionMareografo() const {
  return m_descrMarInstTextEdit->toPlainText();
}

QString GeneralidadesPage::descripcionAverias() const {
  return m_descrAveriasTextEdit->toPlainText();
}
