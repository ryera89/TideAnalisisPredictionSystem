#ifndef SELECTIONRANGELABEL_H
#define SELECTIONRANGELABEL_H

#include <QDateTime>
#include <QLabel>

class SelectionRangeLabel : public QLabel {
public:
  SelectionRangeLabel(const QString &labelText, QWidget *parent = 0);

public slots:
  void setInternalData(const QDateTime &iniDateTime, qreal iniValue,
                       const QDateTime &endDateTime, qreal endValue);
  void setLabel(const QString &label);
  void setIniRangeValues(const QDateTime &iniDateTime, qreal iniValue);
  void setEndRangeValues(const QDateTime &endDateTime, qreal endValue);

private:
  QString m_label;

  QDateTime m_iniRangeDateTime;
  QDateTime m_endRangeDateTime;

  qreal m_iniRangeValue;
  qreal m_endRangeValue;

  void updateDisplayedData();
};

#endif // SELECTIONRANGELABEL_H
