#ifndef AVERAGEDIALOG_H
#define AVERAGEDIALOG_H

#include "include/measurement/measurement.h"
#include <QDialog>

namespace Ui {
class AverageDialog;
}

class AverageDialog : public QDialog {
  Q_OBJECT

public:
  explicit AverageDialog(const QVector<TidesMeasurement> &data,
                         QWidget *parent = 0);
  ~AverageDialog();

  QVector<TidesMeasurement> averagedData() const { return m_averagedData; }

private slots:
  void averageData();

private:
  Ui::AverageDialog *ui;

  QVector<TidesMeasurement> m_data;
  QVector<TidesMeasurement> m_averagedData;

  void updateStatusLabel(int dataNumber);
};

#endif // AVERAGEDIALOG_H
