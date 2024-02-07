#ifndef FINALPAGE_H
#define FINALPAGE_H

#include <QWizardPage>

class QLabel;
class QLineEdit;
class QGroupBox;

class FinalPage : public QWizardPage {
  Q_OBJECT
public:
  FinalPage(QWidget *parent = 0);

  QString procesoNombre() const;
  QString procesoDpto() const;

  QString revisoNombre() const;
  QString revisoDpto() const;

  QString proceso() const;
  QString reviso() const;

private:
  QLabel *m_procesoApellidosLabel;
  QLabel *m_procesoNombreLabel;
  QLabel *m_procesoDptoLabel;
  QLabel *m_revisoApellidosLabel;
  QLabel *m_revisoNombreLabel;
  QLabel *m_revisoDptoLabel;

  QGroupBox *m_procesoGroupBox;
  QGroupBox *m_revisoGroupBox;

  QLineEdit *m_procesoApellidosEdit;
  QLineEdit *m_procesoNombreEdit;
  QLineEdit *m_procesoDptoEdit;
  QLineEdit *m_revisoApellidosEdit;
  QLineEdit *m_revisoNombreEdit;
  QLineEdit *m_revisoDptoEdit;
};

#endif // FINALPAGE_H
