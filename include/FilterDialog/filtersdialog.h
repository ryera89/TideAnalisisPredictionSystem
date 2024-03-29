#ifndef FILTERSDIALOG_H
#define FILTERSDIALOG_H

#include "../FilterFunctions/filter_facilities.h"
#include "../measurement/measurement.h"
#include <QDialog>
#include <QSignalMapper>
class QPushButton;
class QComboBox;
class QCheckBox;
class QRadioButton;
class QFrame;
class QLabel;
class QDoubleSpinBox;
class QSpinBox;
class QGroupBox;
class QProgressBar;
class QVBoxLayout;
class QPlainTextEdit;

class FiltersDialog : public QDialog {
  Q_OBJECT
public:
  explicit FiltersDialog(const QVector<TidesMeasurement> &data,
                         QWidget *parent = Q_NULLPTR);

  QVector<TidesMeasurement> filteredData() const { return m_data; }

private slots:

  void applyFilter();
  void
  updateFoundDataForGlitchAndValueFilter(int matNumber, int pos,
                                         const TidesMeasurement &measurement);
  void updataFoundDataForBlockFilter(int matNumber,
                                     const QVector<int> &matches);
  void setCriteria(int index);
  // void setDataForElimination(int index);
  void deletePoints();

private:
  QVector<TidesMeasurement> m_data;
  QVector<int> m_matchedDataPos;
  Filters m_filter;

  Filters::ByValue m_criteria;

  // QVBoxLayout *m_checkBoxesLayout;

  // QVector<QCheckBox*> m_resultsCheckBoxes;
  // QMap<int,bool> m_resultsCheckBoxesStatusMap;
  // QSignalMapper *m_mapper;

  QPushButton *m_filterPushButton;
  QPushButton *m_deleteDataPushButton;
  QPushButton *m_okPushButton;
  QPushButton *m_cancelPushButton;

  QRadioButton *m_byValueRadioButton;
  QRadioButton *m_byGlitchRadioButton;
  QRadioButton *m_byBlockRadioButton;

  QGroupBox *m_filterGroupBox;

  QDoubleSpinBox *m_glithSpinBox;
  QDoubleSpinBox *m_valueSpinBox;
  QSpinBox *m_blockSpinBox;

  QComboBox *m_criteriaSelectionComboBox;

  QLabel *m_glitchInfoLabel;
  QLabel *m_blockInfoLabel;

  QPlainTextEdit *m_resultEdit;

  // QFrame *m_resultsFrame;

  // QCheckBox *m_selectAllCheckBox;

  QProgressBar *m_progressBar;

  QLabel *m_opInfoLabel;

  // void createChechBoxesResult();
  void displayResults(int pos, const TidesMeasurement &measurement);
  void updateInfoLabel(int matches);
  void updateInfoLabelOnDataElimination(int remainingDataNumber,
                                        int currentDataNumber);
};

#endif // FILTERSDIALOG_H
