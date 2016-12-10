#ifndef SAMPLINGDIALOG_H
#define SAMPLINGDIALOG_H

#include <QDialog>
#include "include/measurement/measurement.h"


class QDateEdit;
class QTimeEdit;
class QLabel;
class QProgressBar;
class QPushButton;

class SamplingDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SamplingDialog(const QVector<TidesMeasurement> &inputMeasurements, QWidget *parent = 0);

private slots:
    void sampleData();

private:
    QVector<TidesMeasurement> m_allData;
    QVector<TidesMeasurement> m_reducedData;

    quint64 m_potentialPoints;

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

    void updateStatusText(quint64 datosEntrada,quint64 datosSalidaPotenciales, quint64 currentAddedPoints);
};

#endif // SAMPLINGDIALOG_H
