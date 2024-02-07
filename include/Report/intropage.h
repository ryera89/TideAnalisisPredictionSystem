#ifndef INTROPAGE_H
#define INTROPAGE_H

#include <QWizardPage>
class QLabel;

class IntroPage : public QWizardPage {
  Q_OBJECT
public:
  IntroPage(QWidget *parent = 0);

private:
  QLabel *m_label;
};

#endif // INTROPAGE_H
