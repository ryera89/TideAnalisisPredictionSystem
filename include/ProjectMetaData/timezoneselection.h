#ifndef TIMEZONESELECTION_H
#define TIMEZONESELECTION_H

#include <QCheckBox>
#include <QComboBox>
#include <QFrame>

class TimeZoneSelection : public QFrame {
  Q_OBJECT
public:
  TimeZoneSelection(QWidget *parent = 0);
  ~TimeZoneSelection() {}

  int timeZoneOffset() const { return m_hourOffset; }
  bool isDaylightTimeSaving() const { return m_DTS; }

  void setTimeZone(int index);
  void setTimeLightSaving(bool timeLightSaving);

private slots:
  void setTimeZoneOffSet(int index);
  void setDaylightTimeSaving(int status);

private:
  QComboBox *m_timeZoneComboBox;
  QCheckBox *m_DTSCheckBox;

  int m_hourOffset;
  bool m_DTS;
};

#endif // TIMEZONESELECTION_H
