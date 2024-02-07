#include "chapaspage.h"

#include <QGroupBox>
#include <QPlainTextEdit>
#include <QVBoxLayout>
ChapasPage::ChapasPage(QWidget *parent) : QWizardPage(parent) {
  setTitle(tr("Datos de las referencias"));

  m_descrChapaPartidaGroupBox =
      new QGroupBox(tr("Datos de la chapa de partida"));
  m_descrChapaPrincipalGroupBox =
      new QGroupBox(tr("Datos de la chapa principal"));
  m_descrChapaTrabajoGroupBox =
      new QGroupBox(tr("Datos de la chapa de trabajo"));

  m_descrChapaPartidaTextEdit = new QPlainTextEdit;
  m_descrChapaPartidaTextEdit->setPlaceholderText(
      tr("número, año de establecimiento, nombre del organismo, quién colocó "
         "la chapa, "
         "situación de la chapa, etc."));

  m_descrChapaPrincipalTextEdit = new QPlainTextEdit;
  m_descrChapaPrincipalTextEdit->setPlaceholderText(
      tr("número, año de establecimiento, nombre del organismo, quién colocó "
         "la chapa, "
         "situación de la chapa, etc."));

  m_descrChapaTrabajoTextEdit = new QPlainTextEdit;
  m_descrChapaTrabajoTextEdit->setPlaceholderText(
      tr("número, año de establecimiento, nombre del organismo, quién colocó "
         "la chapa, "
         "situación de la chapa, etc."));

  QVBoxLayout *layout1 = new QVBoxLayout;
  layout1->addWidget(m_descrChapaPartidaTextEdit);

  QVBoxLayout *layout2 = new QVBoxLayout;
  layout2->addWidget(m_descrChapaPrincipalTextEdit);

  QVBoxLayout *layout3 = new QVBoxLayout;
  layout3->addWidget(m_descrChapaTrabajoTextEdit);

  m_descrChapaPartidaGroupBox->setLayout(layout1);

  m_descrChapaPrincipalGroupBox->setLayout(layout2);

  m_descrChapaTrabajoGroupBox->setLayout(layout3);

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(m_descrChapaPartidaGroupBox);
  layout->addWidget(m_descrChapaPrincipalGroupBox);
  layout->addWidget(m_descrChapaTrabajoGroupBox);

  setLayout(layout);
}

QString ChapasPage::descripcionChapaPartida() const {
  return m_descrChapaPartidaTextEdit->toPlainText();
}

QString ChapasPage::descripcionChapaPrincipal() const {
  return m_descrChapaPrincipalTextEdit->toPlainText();
}

QString ChapasPage::descripcionChapaTrabajo() const {
  return m_descrChapaTrabajoTextEdit->toPlainText();
}
