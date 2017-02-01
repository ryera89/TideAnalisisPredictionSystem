#ifndef TIMEZONESELECTION_H
#define TIMEZONESELECTION_H

#include <QFrame>
#include <QComboBox>
#include <QCheckBox>


class TimeZoneSelection : public QFrame
{
    Q_OBJECT
public:
    TimeZoneSelection(QWidget *parent = 0);
    ~TimeZoneSelection(){}


    int hourOffset() const {return m_hourOffset;}
    bool isDaylightTimeSaving() const {return m_DTS;}

private slots:
    void setTimeZoneOffSet(int index);
    void setDaylightTimeSaving(bool status);

private:
    QComboBox *m_timeZoneComboBox;
    QCheckBox *m_DTSCheckBox;

    int m_hourOffset;
    bool m_DTS;
};

#endif // TIMEZONESELECTION_H
