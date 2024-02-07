#ifndef PREDICTIONSETTINGS_H
#define PREDICTIONSETTINGS_H

#include <QDateTime>
#include <QtCore>

class PredictionSettings {
public:
  enum PredMethod { NF_CTE, NF_VAR };
  PredictionSettings();

  double nmm() const { return m_nmm; }
  QDateTime from() const { return m_from; }
  QDateTime to() const { return m_to; }
  quint64 interval() const { return m_interval; }
  PredMethod method() const { return m_method; }

  void setNMM(const double &nmm1) { m_nmm = nmm1; }
  void setBegingDate(const QDateTime &from1) { m_from = from1; }
  void setEndDate(const QDateTime &to1) { m_to = to1; }
  void setInterval(const quint64 &interval1) { m_interval = interval1; }
  void setMethod(PredMethod method1) { m_method = method1; }

private:
  double m_nmm;
  QDateTime m_from;
  QDateTime m_to;
  quint64 m_interval;

  PredMethod m_method;
};

#endif // PREDICTIONSETTINGS_H
