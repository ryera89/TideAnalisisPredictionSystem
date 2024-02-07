#ifndef CEROPROFPAGE_H
#define CEROPROFPAGE_H

#include <QWizardPage>

class QLabel;
class QLineEdit;
class QGroupBox;

class CeroProfPage : public QWizardPage {
  Q_OBJECT
public:
  CeroProfPage(QWidget *parent = 0);

  QString ceroDeProfundidad() const;
  QString metodoCeroDeProfundidad() const;
  QString periodoObsCeroDeProfundidad() const;

  QString situacionCeroProfundidad() const;

  QString situacionCeroProfCeroPuesto() const;
  QString situacionCeroProfNMM() const;
  QString situacionCeroProfChapaPrincipal() const;

  QString oscilacionesRespectoACeroProfundidad() const;

  QString nivelMinimo() const;
  QString nivelMaximo() const;

private:
  QLabel *m_ceroProfundidadLabel;
  QLabel *m_metodoCeroProfundidadLabel;
  QLabel *m_periodoCeroProfundidadLabel;
  QLabel *m_sitCeroProfundidadCeroPuestoLabel;
  QLabel *m_sitCeroProfundidadNMMLabel;
  QLabel *m_sitCeroProfundidadChapaPrincipalLabel;
  QLabel *m_nivelMinimoLabel;
  QLabel *m_nivelMaximoLabel;

  QGroupBox *m_sitCeroProfGroupBox;
  QGroupBox *m_oscNivelCeroProfGroupBox;

  QLineEdit *m_ceroProfundidadEdit;
  QLineEdit *m_metodoCeroProfundidadEdit;
  QLineEdit *m_periodoCeroProfundidadEdit;
  QLineEdit *m_sitCeroProfundidadCeroPuestoEdit;
  QLineEdit *m_sitCeroProfundidadNMMEdit;
  QLineEdit *m_sitCeroProfundidadChapaPrincipalEdit;
  QLineEdit *m_nivelMinimoEdit;
  QLineEdit *m_nivelMaximoEdit;
};

#endif // CEROPROFPAGE_H
