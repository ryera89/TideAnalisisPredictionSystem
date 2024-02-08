#ifndef NONHARMONINCCALCDIALOG_H
#define NONHARMONINCCALCDIALOG_H

#include "displayresultwidget.h"
#include "../HarmonicConstantClass/harmonicconstant.h"
#include "../MeasurementUnitEditWidget/measurementuniteditwidget.h"
#include "../ProjectMetaData/projectmetadata.h"
#include <QDialog>
#include <QSignalMapper>
class QLabel;
class QDoubleSpinBox;
class MyCoordinatesEditorWidget;

class NonHarmonicCalcDialog : public QDialog {
  Q_OBJECT

public:
  NonHarmonicCalcDialog(qreal longitud, QWidget *parent = 0);
  void
  loadHarmonicConstants(const QVector<HarmonicConstant> &harmonicConstants);
  ~NonHarmonicCalcDialog() {}

  void setMetaData(const ProjectMetaData &metadata);

  QString relacionDeAmplitud() const;
  QString horaDelPuestoMedia() const;
  QString horaDelPuesto() const;
  QString duracionDelVaciante() const;
  QString duracionDelLenante() const;
  QString crecimientoDeLaMareaSemidiurna() const;
  QString crecimientoDeLaMareaParalactica() const;
  QString crecimientoDeLaMareaDiurna() const;
  QString horaCotidianaMareaSemidiurna() const;
  QString horaCotidianaMareaDiurna() const;
  QString alturaPromedioDeLaMareaSemidiurna() const;
  QString alturaPromedioDeLaMareaSicigias() const;
  QString alturaPromedioDeLaMareaCuadratura() const;
  QString alturaPromedioDeLaMareaTropical() const;

private slots:
  void calculate(int index);

  void saveToFile();

  void calculateAll();

signals:
  void closed();

protected:
  void closeEvent(QCloseEvent *event);

private:
  QVector<displayResultWidget *> m_displayResultWidgetVector;

  QFrame *m_inputFrame;
  QFrame *m_relationFrame;

  QFrame *m_column1Frame;
  QFrame *m_column2Frame;
  QFrame *m_column3Frame;

  QLabel *m_NMMLabel;
  QLabel *m_longitudLabel;
  QLabel *m_ampRelationLabel;
  QLabel *m_semidiurnalRelationLabel;
  QLabel *m_tipoMareaLabel;

  MeasurementUnitEditWidget *m_NMMSpinBox;
  MyCoordinatesEditorWidget *m_longitudEditor;
  QLineEdit *m_ampRelationLineEdit;
  QLineEdit *m_semidiurnalRelationLineEdit;
  QLineEdit *m_tipoMareaLineEdit;

  QPushButton *m_calcAllPushButton;
  QPushButton *m_savePushButton;
  QPushButton *m_closePushButton;

  QSignalMapper *m_mapper;

  HarmonicConstant m_M2; // Semidiurnal
  HarmonicConstant m_S2;
  HarmonicConstant m_N2;
  HarmonicConstant m_K2;

  HarmonicConstant m_K1; // Diurnal
  HarmonicConstant m_O1;
  HarmonicConstant m_P1;
  HarmonicConstant m_Q1;

  HarmonicConstant m_M4; // Bajo Fondo
  HarmonicConstant m_M6;

  ProjectMetaData m_metaData;

  // qreal m_longitud;
  // qreal m_nivelMedio;

  void createComponents();
  void createDisplaysResultWidgets();
  void setInterfaceLayout();

  double calculateAmplitudRelation();
  double calculateSemidiurnalRelation();
  QString tipoDeMarea(double ampRelation);
  void enableNonHarmonicConstantCalc(double ampRelation);

  double calculateHPM();
  double calculateHP();
  double calculateDV();
  double calculateDLL();
  double calculateCMS();
  double calculateCMP();
  double calculateCMD();
  double calculateHCMS();
  double calculateHCMD();
  double calculateAPMS();
  double calculateAPMSS();
  double calculateAPMC();
  double calculateAPMT();
  double calculateAS();
  double calculatePMS();
  double calculatePMC();
  double calculatePMMT();
  double calculateBMSS();
  double calculateBMC();
  double calculateBMMT();

  QString fromDoubleToDaysAndHours(double value);
  QString fromDoubleToHoursAndMinutes(double value);

  void saveNonHarmonicConstants(const QString &filePath);
};

#endif // NONHARMONINCCALCDIALOG_H
