#ifndef DISPLAYEDDATALABELS_H
#define DISPLAYEDDATALABELS_H

#include <QLabel>

#include <QDate>
#include <QTime>

class DisplayedDataLabels : public QLabel
{
    Q_OBJECT
public:
    DisplayedDataLabels(QWidget *parent = 0);
    DisplayedDataLabels(const QString &label,const QDate &date, const QTime &time, const double &value, QWidget *parent = 0);
    DisplayedDataLabels(const QString &label,const QDateTime &date_time, const double &value, QWidget *parent = 0);

public slots:
    void setInternalData(const QString &label, const QDate &date, const QTime &time, const double &value);
    void setInternalData(const QString &label, const QDateTime &date_time, const double &value);
    void setInternalData(const QDate &date, const QTime &time, const double &value);
    void setInternalData(const QDateTime &date_time, const double &value);
    void setInternalData(const QDateTime &date_time);

    void setLabel(const QString &label);
    void setDate(const QDate &date);
    void setTime(const QTime &time);
    void setValue(const double &value);


private:
    QString m_label;
    QDate m_date;
    QTime m_time;
    double m_value;

    void updateDisplayedData();
};

#endif // DISPLAYEDDATALABELS_H
