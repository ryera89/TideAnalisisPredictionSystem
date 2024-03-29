#ifndef SPMMAINWINDOW_H
#define SPMMAINWINDOW_H

#include "../TablaHorariaDeMarea/tablahorariawidget.h"
#include "../loadDialog/loaddialog.h"
#include "centralwidget.h"
#include <QMainWindow>
#include <QMenuBar>
// #include "include/ChartModelMapper/xytidalchartmodelmapper.h"
#include "../AlcanceLimite/alcancelimitewindow.h"
#include "../AverageDialog/averagedialog.h"
#include "../EditionComponents/manualdataintroductionwidget.h"
#include "../FilterDialog/filtersdialog.h"
#include "../HarmonicConstantClass/harmonicconstant.h"
#include "../ManualHarmonicConstants/manualharmonicconstantintrodialog.h"
#include "../NivelacionAcuaticaWidget/nivelacionacuaticawidget.h"
#include "../PredictionModule/predictormainwindow.h"
#include "../Presentation/widget.h"
#include "../ProjectMetaData/projectmetadata.h"
#include "../Report/reportwizard.h"
#include "../SamplingDialog/samplingdialog.h"
#include "uploadhcdialog.h"
#include <QtConcurrent/QtConcurrent>

using namespace QtConcurrent;

class SchemeWidget;
class MetaDataDialog;
class FreqEditor;
class NonHarmonicCalcDialog;

// El analisis armonico se hace con la horas respecto al inicio del year

class SPMmainWindow : public QMainWindow {
  Q_OBJECT
public:
  explicit SPMmainWindow(QWidget *parent = 0);

  enum FILE_ID {
    SchemesMagicNumber = 18041989,
    MagicNumber = 19891804,
    HCMagicNumber = 20150926
  }; // Magic Numbers for config files recognition

  // TidalData datosDeMarea() const{return m_datosDeMarea;}
  // QAbstractTableModel* model()const{return m_tidalTableModel;}

  // Esta es la funcion que hay que pasarle al metodo de minsqr
  static QVector<double> funcion(const double &t);
  static QVector<double> funcionModificada(const double &t,
                                           const QDateTime &datetime,
                                           const QDateTime &beginDate);

  static QString hcDataBaseDir();

  QSize sizeHint() const;

public slots:
  void hidePresentation();
  void getNonHarmonicConstansForReport();
  void about();
signals:
  void harmonicAnalisisFinished();
private slots:
  void newProject();
  void openProject();
  void saveProject();
  void saveProjectAs();

  void loadDataFile();
  void createManualDataIntWidget();
  void crearTablaHoraria();
  void createMetaDataDialog();
  void createNonHarmonicDialog();
  void createNivelacionAcuaticaWidget();
  void updateMetaData(); // SLOT para connectar al dilogo de los meta datos para
                         // guardarlos

  /*void recieveData(const QVector<QStringList> &data, int dateField, int
     timeField, int heightField, const QString &dateFormat, const QString
     &timeFormat);*/

  // void beginDataRecieve(const QVector<TidesMeasurement> &datos);
  void createHarmonicAnalisisDialog();
  // void createFrequencyEditor();

  void createSamplingDilalog();
  void loadSampledData();

  void createFilterDialog();
  void loadFilteredData();

  void createAverageDialog();
  void loadAverageData();

  void
  createAlcanceLimiteWindow(); // Inrterfaz para el calculo del alcance limite
  void createPredictor();

  void createUpHcDialog();
  void createReportWizard();

  void createManualHCDialog();

  // bool saveFrequencyFile();
  void harmonicAnalisis();
  void harmonicAnalisisWithAllData();
  // void harmonicAnalisisWithCustomData();
  void saveHarmonicConstantToFile();

  void uploadHCToDataBase();

protected slots:
  void setChartLightTheme(bool);
  void setChartDarkTheme(bool);
  void setChartBrownSandTheme(bool);
  void setChartBlueCeruleanTheme(bool);
  void setChartBlueIcyTheme(bool);
  void setChartBlueNscTheme(bool);
  void setChartHighContrastTheme(bool);
  void setChartQtTheme(bool);

  void setChartNoAnimation(bool);
  void setChartGridAxisAnimation(bool);
  void setChartSeriesAnimation(bool);
  void setChartAllAnimation(bool);

  void setRenderedChartViewFlag(bool);

  void beginDataExtration();
  void appendManualDataToProject();

  void beginDataExtrationFromFile();
  void appendImportedData();

  // bool saveAnalisisData();

  // void gettingData(const QVector<QStringList> &data, int dateField, int
  // timeField, int heightField);

private:
  Widget *m_presentation;

  // Config files
  // filespath--------------------------------------------------------------------
  // const QString m_frequencyFilePath = "data/frequency.frq"; //fichero donde
  // se guardan la frecuencias de las constantes armonicas
  const QString m_schemesFilePath =
      "data/Schemes/schemes.sch"; // Fichero donde se guardan los esquemas

  static QString
      m_hcDirDataBase; // Directorio donde se almacenan las contantes armonicas

  QString m_projectFilePath; // Para cuando se abre un proyecto;

  QString
      m_provincia; // Para guardar las constantes armonicas a la base de datos
  QString m_localidad;

  bool m_firstOpen;

  /*********************************Visual
   * Widgets**********************************************/
  // Central Widget Main
  // Interface----------------------------------------------------------------------
  CentralWidget *m_central;
  // Dialogs------------------------------------------------------------------------------------------
  LoadDialog *m_loadDialog;
  TablaHorariaWidget *m_tablaHorariaWidget;
  ManualDataIntroductionWidget *m_manualDataIntroductionWidget;
  MetaDataDialog *m_projectMetaDataDialog;
  SchemeWidget *m_schemeWidget;
  NonHarmonicCalcDialog *m_nonHarmonicConstantDialog;
  // FreqEditor *m_frequencyEditor;
  NivelacionAcuaticaWidget *m_nivelacionAcuaticaWidget;
  SamplingDialog *m_samplingDialog;
  FiltersDialog *m_filterDialog;
  AverageDialog *m_averageDialog;
  AlcanceLimiteWindow *m_alcanceLimiteWindow;
  PredictorMainWindow *m_predictor;
  UploadHCDialog *m_upHcDialog;
  ReportWizard *m_reportWizard;
  ManualHarmonicConstantIntroDialog *m_manualHCIntroDialog;
  // QML component
  /*************************ACTIONS*************************************************/
  // File Menu
  // Actions----------------------------------------------------------------
  QAction *m_newProjectAction;
  QAction *m_loadProjectAction;
  QAction *m_saveProjectAction;
  QAction *m_saveAsProjectAction;
  QAction *m_projectMetaDataAction;
  QAction *m_exitAction;

  // ChartActions-----------------------------------------------------------------------
  QAction *m_themeLightAction;
  QAction *m_themeDarkAction;
  QAction *m_themeBlueCeruleanAction;
  QAction *m_themeBrownSandAction;
  QAction *m_themeBlueIcyAction;
  QAction *m_themeBlueNcsAction;
  QAction *m_themeHighcontrastAction;
  QAction *m_themeQtAction;

  QActionGroup *m_themeGroup; // exclusive actions

  QAction *m_animationNoAnimationAction;
  QAction *m_animationGridAxisAnimationAction;
  QAction *m_animationSeriesAnimationAction;
  QAction *m_animationAllAnimationAction;

  QAction *m_chartRenderHintAction;

  QActionGroup *m_animationGroup; // exclusive actions

  // Data
  // Actions-----------------------------------------------------------------------
  QAction *m_manualDataIntroductionAction;
  QAction *m_importFrom_ASCII_Action;

  // Edit Action
  QAction *m_samplingDialogAction;
  QAction *m_filterDialogAction;
  QAction *m_averageDialogAction;

  // Analisis
  // Actions-------------------------------------------------------------------
  QAction *m_tablaHorariadeMareaAction;
  QAction *m_harmonicAnalisisAction;
  QAction *m_nonHarmonicAnalisisAction;

  // Tools
  // Actions------------------------------------------------------------------------
  // QAction *m_freqEditorAction;
  QAction *m_nivelacionAcuaticaAction;
  QAction *m_alcanceLimiteAction;
  QAction *m_predictorAction;
  QAction *m_manualHCIntroAction;

  // Report Action
  QAction *m_reportAction;

  QAction *m_aboutAction;

  // View
  // Actions-----------------------------------------------------------------------

  /************************MENUS******************************************************/
  QMenu *m_fileMenu;

  QMenu *m_dataMenu;

  QMenu *m_editMenu;

  QMenu *m_analisisMenu;
  QMenu *m_toolMenu;

  QMenu *m_viewMenu;
  QMenu *m_chartMenu;
  // QMenu *m_importSubMenu;
  QMenu *m_animationSubMenu;
  QMenu *m_themeSubMenu;

  // Report Menu
  QMenu *m_reportMenu;

  QMenu *m_aboutMenu;

  /*************************ToolBars**********************************************************/
  QToolBar *m_projectToolBar;
  QToolBar *m_dataToolBar;
  QToolBar *m_analsisToolBar;
  QToolBar *m_toolToolBar;

  /*************************Private Functions For
   * Interface*************************************************/
  void createActions();
  void createMenus();
  void createToolBars();

  /**************************Internal Data
   * Storage**********************************************************/
  ProjectMetaData m_metadataStorage; // Meta datos del proyecto

  // TidalData m_datosDeMarea;
  // ReadOnlyTableModel *m_tidalTableModel;
  // XYTidalChartModelMapper *mapper;

  QVector<HarmonicConstant>
      m_harmonicConstantVector; // Donde se almacenan las constantes armonicas;
  static QVector<HarmonicConstant>
      m_selectedHarmonicConstantVector; // Constantes armonicas seleccionadas
                                        // para analisis

  // Non Harmonic Constants
  QString m_HoraDelPuestoMedia;
  QString m_HoraDelPuesto;
  QString m_DuracionDelVaciante;
  QString m_DuracionDelLlenate;
  QString m_CrecimientoDeLaMareaSemidiurna;
  QString m_CrecimientoDeLaMareaParalactica;
  QString m_CrecimientoDeLaMareaDiurna;
  QString m_HoraCotidianaDeLaMareaSemidiurna;
  QString m_HoraCotidianaDeLaMareaDiurna;
  QString m_AlturaPromedioDeLaMareaSemidiurna;
  QString m_AlturaPromedioDeLaMareaSicigias;
  QString m_AlturaPromedioDeLaMareaCuadratura;
  QString m_AlturaPromedioDeLaMareaTropical;
  QString m_RelacionDeAmplitud;

  static bool m_daylightTimeSaving;
  /******************************Private Functions For
   * Funcionality*******************************************/
  void syncData(const QVector<HarmonicConstant> &components);

  bool createHarmonicAnalisisDialogFromConfigFile();
  bool readFile(const QString &filePath);
  bool writeFile(const QString &filePath);
  bool saveHCToDataBase(const QString &filePath);
  bool saveHCInfoToDataBase(const QString &filePath);
  // static void setSelectectedHarmonicConstants();
  // bool saveAnalisisDataToFile(const QString &filePath);
  void saveHarmonicConstants(const QString &filePath);
  void harmonicConstantSet();

  void applyCorrectionsToHarmonicConstants();
  void determineHarmonicContantPhase();
  void findHarmonicConstantCorrectedPhase(QDateTime begin, QDateTime end,
                                          bool DaylightTimeSaving,
                                          HarmonicConstant &hc);
  void findHarmonicConstantPhase(int timeOffset, double longitud,
                                 HarmonicConstant &hc);
  void findHarmonicConstantAmplitud(QDateTime begin, QDateTime end,
                                    bool DaylightTimeSaving,
                                    HarmonicConstant &hc);
};

#endif // SPMMAINWINDOW_H
