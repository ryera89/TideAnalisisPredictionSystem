#include "displayeddatalabels.h"
#include <QDateTime>

DisplayedDataLabels::DisplayedDataLabels(QWidget *parent):QLabel(parent)
{
    m_label = QString();
    m_date = QDate();
    m_time = QTime();
    m_value = 0.0;
}

DisplayedDataLabels::DisplayedDataLabels(const QString &label, const QDate &date, const QTime &time, const double &value, QWidget *parent):
    QLabel(parent),m_label(label),m_date(date),m_time(time),m_value(value)
{
    updateDisplayedData();
}

DisplayedDataLabels::DisplayedDataLabels(const QString &label, const QDateTime &date_time, const double &value, QWidget *parent):
     QLabel(parent),m_label(label),m_date(date_time.date()),m_time(date_time.time()),m_value(value)
{
    updateDisplayedData();
}

void DisplayedDataLabels::setInternalData(const QString &label, const QDate &date, const QTime &time, const double &value)
{
    m_label = label;
    m_date = date;
    m_time = time;
    m_value = value;

    updateDisplayedData();
}

void DisplayedDataLabels::setInternalData(const QString &label, const QDateTime &date_time, const double &value)
{
    m_label = label;
    m_date = date_time.date();
    m_time = date_time.time();
    m_value = value;

    updateDisplayedData();
}

void DisplayedDataLabels::setInternalData(const QDate &date, const QTime &time, const double &value)
{
    m_date = date;
    m_time = time;
    m_value = value;

    updateDisplayedData();
}

void DisplayedDataLabels::setInternalData(const QDateTime &date_time, const double &value)
{
    m_date = date_time.date();
    m_time = date_time.time();
    m_value = value;

    updateDisplayedData();
}

void DisplayedDataLabels::setInternalData(const QDateTime &date_time)
{
    m_date = date_time.date();
    m_time = date_time.time();

    updateDisplayedData();
}

void DisplayedDataLabels::setLabel(const QString &label)
{
    m_label = label;

    updateDisplayedData();
}

void DisplayedDataLabels::setDate(const QDate &date)
{
    m_date = date;

    updateDisplayedData();
}

void DisplayedDataLabels::setTime(const QTime &time)
{
    m_time = time;

    updateDisplayedData();
}

void DisplayedDataLabels::setValue(const double &value)
{
    m_value = value;

    updateDisplayedData();
}

void DisplayedDataLabels::updateDisplayedData()
{
    if (m_date.isValid() && m_time.isValid()){
        this->setText(m_label + ": " + m_date.toString("dd/MM/yyyy") + " " + m_time.toString("hh:mm") + " " + QString::number(m_value,'g',4));
    }else{
        this->setText(m_label + ": ");
    }

}
