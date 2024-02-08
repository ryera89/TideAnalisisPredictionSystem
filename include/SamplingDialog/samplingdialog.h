#ifndef SAMPLINGDIALOG_H
#define SAMPLINGDIALOG_H

#include "../measurement/measurement.h"
#include <QDate>
#include <QDialog>
#include <QMap>

class QDateEdit;
class QTimeEdit;
class QLabel;
class QProgressBar;
class QPushButton;

class SamplingDialog : public QDialog {
  Q_OBJECT
public:
  explicit SamplingDialog(const QVector<TidesMeasurement> &inputMeasurements,
                          QWidget *parent = 0);

  QVector<TidesMeasurement> dataSampled() const { return m_reducedData; }

private slots:
  void sampleData();

  void updateFinalDateEditRange(const QDate &iniDate);
  void updatePotentialPoints();

private:
  QVector<TidesMeasurement> m_allData;
  QVector<TidesMeasurement> m_reducedData;

  quint64 m_potentialPoints;

  QMap<QDate, int> m_mapForFirstDatePos;
  QMap<QDate, int> m_mapForEndDatePos;

  QLabel *m_fechaInicialLabel;
  QLabel *m_fechaFinalLabel;
  QLabel *m_intervaloLabel;
  QLabel *m_infoLabel;

  QDateEdit *m_fechaInicialEdit;
  QDateEdit *m_fechaFinalEdit;
  QTimeEdit *m_intervaloEdit;

  QPushButton *m_cancelButton;
  QPushButton *m_sampleButton;
  QPushButton *m_okButton;

  QProgressBar *m_progressBar;
  QLabel *m_statusLabel;

  void updateStatusText(quint64 datosEntrada, quint64 datosSalidaPotenciales,
                        quint64 currentAddedPoints);
};

#endif // SAMPLINGDIALOG_H
