#include "selectionrangelabel.h"

#include <QDateTime>

SelectionRangeLabel::SelectionRangeLabel(const QString &labelText, QWidget *parent):QLabel(parent)
{
    m_label = labelText;
    updateDisplayedData();
}

void SelectionRangeLabel::setInternalData(const QDateTime &iniDateTime, qreal iniValue, const QDateTime &endDateTime, qreal endValue)
{
    m_iniRangeDateTime = iniDateTime;
    m_iniRangeValue = iniValue;
    m_endRangeDateTime = endDateTime;
    m_endRangeValue = endValue;

    updateDisplayedData();
}

void SelectionRangeLabel::setLabel(const QString &label)
{
    m_label = label;

    updateDisplayedData();
}

void SelectionRangeLabel::setIniRangeValues(const QDateTime &iniDateTime, qreal iniValue)
{
    m_iniRangeDateTime = iniDateTime;
    m_iniRangeValue = iniValue;

    updateDisplayedData();
}

void SelectionRangeLabel::setEndRangeValues(const QDateTime &endDateTime, qreal endValue)
{
    m_endRangeDateTime = endDateTime;
    m_endRangeValue = endValue;

    updateDisplayedData();
}

void SelectionRangeLabel::updateDisplayedData()
{
    this->setText("<b>"+m_label+ ": "+ "<font color = blue>" + m_iniRangeDateTime.toString("dd/MM/yyyy hh:mm")
                  + " " + QString::number(m_iniRangeValue,'g',4) + "m</font> | <font color = red>" + m_endRangeDateTime.toString("dd/MM/yyyy hh:mm")
                  + " " + QString::number(m_endRangeValue,'g',4) + "m</font></b>" );
}
