#ifndef PREDICTONSETTINGSWIDGET_H
#define PREDICTONSETTINGSWIDGET_H

#include "predictionsettings.h"
#include <QComboBox>
#include <QDateTimeEdit>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QWidget>

class PredictonSettingsWidget : public QWidget {
  Q_OBJECT
public:
  explicit PredictonSettingsWidget(const PredictionSettings &predSetting,
                                   QWidget *parent = 0);

  PredictionSettings::PredMethod predictionMethod() const;
  double nmm() const;
  QDateTime fromDateTime() const;
  QDateTime endDateTime() const;
  quint64 interval() const;

signals:
  void okButtonPressed();

private:
  QLabel *m_methodLabel;
  QLabel *m_nmmLabel;
  QLabel *m_fromLabel;
  QLabel *m_toLabel;
  QLabel *m_intervalLabel;

  QComboBox *m_methodComboBox;
  QDoubleSpinBox *m_nmmSpinBox;
  QDateTimeEdit *m_fromDateEdit;
  QDateTimeEdit *m_toDateEdit;
  QSpinBox *m_intervalSpinBox;

  QPushButton *m_okPushButton;
  QPushButton *m_cancelPushButton;

  void interfazLayout();
};

#endif // PREDICTONSETTINGSWIDGET_H
