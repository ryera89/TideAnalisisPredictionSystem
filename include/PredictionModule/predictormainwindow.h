#ifndef PREDICTORMAINWINDOW_H
#define PREDICTORMAINWINDOW_H

#include "include/HarmonicConstantsModule/HarmonicConstantClass/harmonicconstant.h"
#include "include/TablaHorariaDeMarea/tablahorariawidget.h"
#include "include/mainComponents/customchartview.h"
#include "include/model_view/readonlytabledelegate.h"
#include "include/model_view/readonlytablemodel.h"
#include "mytableview.h"
#include "predictonsettingswidget.h"
#include <QHash>
#include <QMainWindow>
#include <QSlider>
#include <QSpinBox>

class QTreeWidget;
class QTableView;
class QPointF;

class PredictorMainWindow : public QMainWindow {
  Q_OBJECT
public:
  explicit PredictorMainWindow(const QString &hcDataBaseDir,
                               QWidget *parent = 0);
  void setHarmonicConstants(const QVector<HarmonicConstant> &hcVector);

  void scanHCDataBase(const QString &hcDataBaseDir);
signals:

public slots:
  void createPredictionSettingsDialog();
  void createTidesTable();
  void getPredictionSettings();
  void beginPredictionAtRegularIntervals();
  void beginFindHighLowWaters();
  void beginDetermineNMT();
  void savePredicitionsToFile();
  void saveHighLowWatersToFile();
  void setChartSeriesData();

  void setChartTheme(QChart::ChartTheme theme);
  void setAnimationOptions(QChart::AnimationOptions animation);
  void setRenderHints(QPainter::RenderHints hint);

  void selectPoints(QPointF pPoint, QPointF rPoint);
  void selectPoint(QPointF pPoint);

  void zoomXAxis(int zoomLevel);
  void zoomYAxis(int zoomLevel);

  void selectDataInChart(int row0, int rowf);
  void deselectDataInChart();

  void loadHCFromDataBase(QTreeWidgetItem *current, QTreeWidgetItem *prev);

private:
  TablaHorariaWidget *m_tablaMarea;
  PredictonSettingsWidget *m_predictionSettingsWidget;

  QTreeWidget *m_locationHCTree;

  MyTableView *m_tidesDataTableView;
  QTableView *m_tidesHighLowWaterTableView;
  ReadOnlyTableModel *m_tidesDataModel;
  ReadOnlyTableModel *m_tidesHighLowWaterDataModel;

  QChart *m_tidesDataChart;
  customChartView *m_tidesDataChartView;

  QValueAxis *m_levelAxis;
  QDateTimeAxis *m_timeAxis;

  QSplineSeries *m_tidesDataSeries;
  QScatterSeries *m_selectionSeries;

  QAction *m_predictionSettingsAction;
  QAction *m_predictionRegularIntervalAction;
  QAction *m_predictionHighLowWatersAction;
  QAction *m_detNMTAction;

  QAction *m_tidesTableAction;
  QAction *m_savePredictionsToFile;
  QAction *m_saveHighAndLowWatersToFile;

  QMenu *m_predictionMenu;
  QMenu *m_dataMenu;

  PredictionSettings m_predictionSettings;

  QVector<HarmonicConstant> m_harmonicConstantsSet;

  QSlider *m_zoomXSlider;
  QSpinBox *m_zoomXSpinBox;

  int m_currentXZoomLevel;

  QSlider *m_zoomYSlider;
  QSpinBox *m_zoomYSpinBox;

  double m_yMax;
  double m_yMin;

  QWidget *m_centralWidget;

  QWidget *m_chartWidget;

  QString m_provincia;
  QString m_localidad;
  QString m_localizationName;
  double m_latitud;
  double m_longitud;

  QTextEdit *m_hcDescriptionPlainTextEdit;

  QHash<QTreeWidgetItem *, QString> m_hashForHCFiles;
  QString m_currentFile;

  QLabel *m_loadingLabel;
  QMovie *m_loadingMovie;

  QLabel *m_NMTLabel;
  QLineEdit *m_NMTLineEdit;

  QLabel *m_regIntervalLabel;
  QLabel *m_extremesLabel;

  void interfazLayout();
  void createActions();
  void createMenus();

  void settingUpXZoomValues();

  bool loadHCFromDataBaseFile(const QString &filePath);

  void displayHCDescriptions();
  void readHCInfoFromFile(const QString &infoFilePath);

  void hideNMTFac();
};
QPointF findMinAndMax(const QVector<TidesMeasurement> &measurements);

#endif // PREDICTORMAINWINDOW_H
