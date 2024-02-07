#include "predictionsettings.h"

PredictionSettings::PredictionSettings()
    : m_nmm(0.0), m_from(QDateTime(QDate(QDate::currentDate()), QTime(0, 0))),
      m_to(QDateTime(QDate(QDate::currentDate()), QTime(23, 0))),
      m_interval(3600), m_method(NF_CTE) {}
