#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>

#include "../EditionComponents/editiontable.h"
#include "../PredictionModule/mytableview.h"
#include "../SelectionRangeLabel/selectionrangelabel.h"
#include "../model_view/readonlytablemodel.h"
#include "../model_view/tablemodel.h"
#include "../model_view/tidaltabledelegate.h"
#include "customchartview.h"
#include "spmchart.h"
#include <QHBoxLayout>
#include <QPlainTextEdit>
#include <iostream>

class DisplayedDataLabels;
class QSpinBox;
class QSlider;
class XYTidalChartModelMapper;

class CentralWidget : public QWidget {
  Q_OBJECT
public:
  explicit CentralWidget(QWidget *parent = 0);

  // MySeries* chartSerie() const{return m_series;}
  QSplineSeries *chartSerie() const { return m_series; } // CAmbiar esto
  QTableView *tableView() const { return m_tidalTableView; }
  QChartView *chartView() const { return m_tideChartView; }
  TableModel *tableModel() const { return m_tidalTableModel; }

signals:

public slots:
  // void loadData(const QString &filePath);
  // void loadDataInTable(const QVector<TidesMeasurement> &measurements);
  // void loadDataChart(); //Funcion para actualizar la grafica.
  // void updateDataInChartWhenRowIsEliminated(int i, int cont); //Slot para
  // modificar la tabla cuando se elimina una fila void
  // checkDateTimeStringFormat(const QString &dateFormat, const QString
  // &timeFormat);
  void updateSerieData(int row);
  void setSeriesData();

private slots:
  void zoomXAxis(int level);
  void getAndDisplayCursorPosInSeries(QPointF point);
  void getAndDisplayClickedPosInSeries(QPointF point);
  void setPointSelectedRange(QPointF pPoint, QPointF rPoint);
  void deleteSelectedPointOnGraph();

  void updateSelectionSeriesData(const QModelIndex &topLeft,
                                 const QModelIndex &bottomRight,
                                 const QVector<int> &roles);
  void updateSeriesData(const QModelIndex &topLeft,
                        const QModelIndex &bottomRight,
                        const QVector<int> &roles = QVector<int>());

  void
  updateSeriesDataAtRowRemove(const QModelIndex &parent, int in,
                              int last); // Update series in data elimination

  void zoomYAxis(int zoomLevel);

  void updateOnRealTimeSelectionRange(QPointF iniPos, QPointF currentPos);

  void selectDataInChart(int row0, int rowf);
  void deselectDataInChart();

private:
  // Table Facilities
  MyTableView *m_tidalTableView;

  // Chart Facilities
  SPMChart *m_tideChart;
  customChartView *m_tideChartView;

  QDateTimeAxis *m_timeAxis;
  QValueAxis *m_yAxis;
  // QValueAxis *m_yAxis;
  QSplineSeries *m_series;

  qreal m_maxSerieYValue;
  qreal m_minSerieYValue;

  QScatterSeries *m_selectionSeries;
  // QScatterSeries *m_scatterSerie;
  // MySeries *m_series;
  // Display Facilities
  QSlider *m_rangeSlider;
  QSpinBox *m_rangeSpinBox;

  QSlider *m_zoomYSlider;
  QSpinBox *m_zoomYSpinBox;

  double m_yMin;
  double m_yMax;
  // DisplayedDataLabels *m_rangeIniDDLabel;
  // DisplayedDataLabels *m_rangeEndDDLabel;
  // DisplayedDataLabels *m_selectionIniDDLabel;
  // DisplayedDataLabels *m_selectionEndDDLabel;
  DisplayedDataLabels *m_cursorPosDDLabel;
  SelectionRangeLabel *m_selectionPointRange;

  // Storage and sync facilities
  TableModel *m_tidalTableModel;
  // XYTidalChartModelMapper *m_mapper;

  int m_currentXZoomLevel;
  QMap<int, int> m_mapForValuesInMainAndSelectionSeries;

  void createComponents();
  void setInterfazLayout();
  void settingUpTable();
  void settingZoomPosibleValues();

  void deletePoints();
  void updateDisplayRangeLabel();

  QPointF seekMaxAndMinViewYSerieValue(const QDateTime &beg,
                                       const QDateTime &end);
};

#endif // CENTRALWIDGET_H
