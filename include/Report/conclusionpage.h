#ifndef CONCLUSIONPAGE_H
#define CONCLUSIONPAGE_H

#include <QWizardPage>

class QLabel;

class ConclusionPage : public QWizardPage {
  Q_OBJECT
public:
  ConclusionPage(QWidget *parent = 0);

private:
  QLabel *m_conclusionLabel;
};

#endif // CONCLUSIONPAGE_H
