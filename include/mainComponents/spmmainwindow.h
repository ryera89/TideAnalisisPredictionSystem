#ifndef SPMMAINWINDOW_H
#define SPMMAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include "centralwidget.h"
#include "include/loadDialog/loaddialog.h"
#include "include/TablaHorariaDeMarea/tablahorariawidget.h"
//#include "include/ChartModelMapper/xytidalchartmodelmapper.h"
#include "include/EditionComponents/manualdataintroductionwidget.h"
#include "include/ProjectMetaData/projectmetadata.h"
#include "include/HarmonicConstantsModule/HarmonicConstantClass/harmonicconstant.h"
class SchemeWidget;
class MetaDataDialog;
class FreqEditor;


//NOTE: el analisis armonico se hace con la horas respecto al inicio del year

class SPMmainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit SPMmainWindow(QWidget *parent = 0);

    //TidalData datosDeMarea() const{return m_datosDeMarea;}
    //QAbstractTableModel* model()const{return m_tidalTableModel;}

    //Esta es la funcion que hay que pasarle al metodo de minsqr
    static QVector<double> funcion(const double &t);

    QSize sizeHint() const;

signals:

private slots:
    void loadDataFile();
    void createManualDataIntWidget();
    void crearTablaHoraria();
    void createMetaDataDialog();

    void updateMetaData(); //SLOT para connectar al dilogo de los meta datos para guardarlos

    /*void recieveData(const QVector<QStringList> &data, int dateField, int timeField,
                     int heightField, const QString &dateFormat, const QString &timeFormat);*/

    //void beginDataRecieve(const QVector<TidesMeasurement> &datos);
    void createHarmonicAnalisisDialog();
    void createFrequencyEditor();


    bool saveFrequencyFile();
    void harmonicAnalisis();
    void harmonicAnalisisWithAllData();
    void harmonicAnalisisWithCustomData();



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
    void beginDataExtrationFromFile();

    bool writeFrequencyFile(const QString &filePath);
    bool saveAnalisisData();

    //void gettingData(const QVector<QStringList> &data, int dateField, int timeField, int heightField);

private:

    enum {SchemesMagicNumber = 18041989, ComponentsMagicNumber = 19891804};
    //Internal data storage files path
    const QString m_frequencyFilePath = "data/frequency.frq"; //fichero donde se guardan la frecuencias de las constantes armonicas
    const QString m_schemesFilePath = "data/schemes.sch"; //Fichero donde se guardan los esquemas

     CentralWidget *m_central;
     LoadDialog *m_loadDialog;
     TablaHorariaWidget *m_tablaHorariaWidget;
     ManualDataIntroductionWidget *m_manualDataIntroductionWidget;
     MetaDataDialog *m_projectMetaDataDialog;
     SchemeWidget *m_schemeWidget;
     FreqEditor *m_frequencyEditor;

     /*************************ACTIONS*************************************************/
     //File Menu Actions
     QAction *m_newProjectAction;
     QAction *m_loadProjectAction;
     QAction *m_saveProjectAction;
     QAction *m_saveAsProjectAction;
     QAction *m_projectMetaDataAction;
     QAction *m_exitAction;

     //ChartActions-----------------------------------------------------------------------
     QAction *m_themeLightAction;
     QAction *m_themeDarkAction;
     QAction *m_themeBlueCeruleanAction;
     QAction *m_themeBrownSandAction;
     QAction *m_themeBlueIcyAction;
     QAction *m_themeBlueNcsAction;
     QAction *m_themeHighcontrastAction;
     QAction *m_themeQtAction;

     QActionGroup *m_themeGroup;

     QAction *m_animationNoAnimationAction;
     QAction *m_animationGridAxisAnimationAction;
     QAction *m_animationSeriesAnimationAction;
     QAction *m_animationAllAnimationAction;

     QAction *m_chartRenderHintAction;

     QActionGroup *m_animationGroup;

     //View Actions-----------------------------------------------------------------------

     QAction *m_tablaHorariadeMareaAction;

     //Data Actions-----------------------------------------------------------------------
     QAction *m_manualDataIntroductionAction;
     QAction *m_importFrom_ASCII_Action;

     //Analisis Actions-------------------------------------------------------------------
     QAction *m_harmonicAnalisisAction;

     //Tools Actions------------------------------------------------------------------------
     QAction *m_freqEditorAction;



     /***********************************************************************************/


     /************************MENUS******************************************************/
     QMenu *m_fileMenu;

     QMenu *m_dataMenu;

     QMenu *m_analisisMenu;
     QMenu *m_toolMenu;

     QMenu *m_viewMenu;
     QMenu *m_chartMenu;
     //QMenu *m_importSubMenu;
     QMenu *m_animationSubMenu;
     QMenu *m_themeSubMenu;

     /***********************************************************************************/
    //NOTE: va el widget especial que contiene el chart

    //NOTE: van las acciones que se ejecutan en el programa.


     void createActions();
     void createMenus();

     //DOnde se almacenan los datos
     ProjectMetaData m_metadataStorage;

     //TidalData m_datosDeMarea;
     //ReadOnlyTableModel *m_tidalTableModel;
     //XYTidalChartModelMapper *mapper;

     QVector<HarmonicConstant> m_harmonicConstantVector; //Donde se almacenan las constantes armonicas;
     static QVector<HarmonicConstant> m_selectedHarmonicConstantVector; //Constantes armonicas seleccionadas para analisis

     void syncData(const QVector<HarmonicConstant> &components);
     bool createHarmonicAnalisisDialogFromConfigFile();
     bool loadHarmonicConstantsFromFile();
     //static void setSelectectedHarmonicConstants();

     bool saveAnalisisDataToFile(const QString &filePath);

};

#endif // SPMMAINWINDOW_H
