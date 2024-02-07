#ifndef GENERALIDADESPAGE_H
#define GENERALIDADESPAGE_H

#include <QWizardPage>

class QGroupBox;
class QPlainTextEdit;

class GeneralidadesPage : public QWizardPage {
  Q_OBJECT
public:
  GeneralidadesPage(QWidget *parent = 0);

  QString descripcionCosta() const;
  QString descripcionMareografo() const;
  QString descripcionInstalacionMareografo() const;
  QString descripcionAverias() const;

private:
  QGroupBox *m_descrCostaGroupBox;
  QGroupBox *m_descrMareografoGroupBox;
  QGroupBox *m_descrMarInstGroupBox;
  QGroupBox *m_descrAveriasGroupBox;

  QPlainTextEdit *m_descrCostaTextEdit;
  QPlainTextEdit *m_descrMareografoTextEdit;
  QPlainTextEdit *m_descrMarInstTextEdit;
  QPlainTextEdit *m_descrAveriasTextEdit;
};

#endif // GENERALIDADESPAGE_H
