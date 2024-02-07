#include "timezoneselection.h"
#include <QHBoxLayout>
#include <QtMath>

#include <iostream>
TimeZoneSelection::TimeZoneSelection(QWidget *parent) : QFrame(parent) {
  m_timeZoneComboBox = new QComboBox;
  m_DTSCheckBox = new QCheckBox(tr("Horario de Verano"));

  m_DTS = false;

  connect(m_timeZoneComboBox, SIGNAL(currentIndexChanged(int)), this,
          SLOT(setTimeZoneOffSet(int)));

  connect(m_DTSCheckBox, SIGNAL(stateChanged(int)), this,
          SLOT(setDaylightTimeSaving(int)));

  QStringList strList;
  for (int i = -12; i <= 12; ++i) {
    QString str("UTC");

    if (i < 0)
      str += "-";
    if (i == 0)
      str += " ";
    if (i > 0)
      str += "+";

    if ((i > -10 && i < 0) || (i > 0 && i < 10))
      str += "0";

    str += QString::number(qAbs(i));

    str += ":00";

    strList.append(str);
  }

  m_timeZoneComboBox->addItems(strList);

  QHBoxLayout *lay = new QHBoxLayout;

  lay->addWidget(m_timeZoneComboBox);
  lay->addWidget(m_DTSCheckBox);

  this->setLayout(lay);
  this->layout()->setMargin(0);
}

void TimeZoneSelection::setTimeZone(int index) {
  m_timeZoneComboBox->setCurrentIndex(index);
}

void TimeZoneSelection::setTimeLightSaving(bool timeLightSaving) {
  m_DTSCheckBox->setChecked(timeLightSaving);
}

void TimeZoneSelection::setTimeZoneOffSet(int index) {
  switch (index) {
  case 0:
    m_hourOffset = -12;
    break;
  case 1:
    m_hourOffset = -11;
    break;
  case 2:
    m_hourOffset = -10;
    break;
  case 3:
    m_hourOffset = -9;
    break;
  case 4:
    m_hourOffset = -8;
    break;
  case 5:
    m_hourOffset = -7;
    break;
  case 6:
    m_hourOffset = -6;
    break;
  case 7:
    m_hourOffset = -5;
    break;
  case 8:
    m_hourOffset = -4;
    break;
  case 9:
    m_hourOffset = -3;
    break;
  case 10:
    m_hourOffset = -2;
    break;
  case 11:
    m_hourOffset = -1;
    break;
  case 12:
    m_hourOffset = 0;
    break;
  case 13:
    m_hourOffset = 1;
    break;
  case 14:
    m_hourOffset = 2;
    break;
  case 15:
    m_hourOffset = 3;
    break;
  case 16:
    m_hourOffset = 4;
    break;
  case 17:
    m_hourOffset = 5;
    break;
  case 18:
    m_hourOffset = 6;
    break;
  case 19:
    m_hourOffset = 7;
    break;
  case 20:
    m_hourOffset = 8;
    break;
  case 21:
    m_hourOffset = 9;
    break;
  case 22:
    m_hourOffset = 10;
    break;
  case 23:
    m_hourOffset = 11;
    break;
  case 24:
    m_hourOffset = 12;
    break;
  default:
    break;
  }

  // std::cout << "Offset " << m_hourOffset << std::endl;
}

void TimeZoneSelection::setDaylightTimeSaving(int status) {
  m_DTS = status;

  // std::cout << status << std::endl;
  // std::cout << m_DTS << std::endl;
}
