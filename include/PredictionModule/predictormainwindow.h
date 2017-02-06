#ifndef PREDICTORMAINWINDOW_H
#define PREDICTORMAINWINDOW_H

#include <QMainWindow>
#include "include/mainComponents/customchartview.h"
#include "include/model_view/readonlytablemodel.h"
#include "predictonsettingswidget.h"
#include "include/HarmonicConstantsModule/HarmonicConstantClass/harmonicconstant.h"

class QTreeWidget;
class QTableView;


class PredictorMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit PredictorMainWindow(QWidget *parent = 0);
    void setHarmonicConstants(const QVector<HarmonicConstant> &hcVector);
signals:

public slots:
    void createPredictionSettingsDialog();
    void getPredictionSettings();
    void beginPredictionAtRegularIntervals();
    void savePredicitionsToFile();
private:
    PredictonSettingsWidget *m_predictionSettingsWidget;

    QTreeWidget *m_locationHCTree;

    QTableView *m_tidesDataTableView;
    QTableView *m_tidesHighLowWaterTableView;
    ReadOnlyTableModel *m_tidesDataModel;
    ReadOnlyTableModel *m_tidesHighLowWaterDataModel;

    QChart *m_tidesDataChart;
    customChartView *m_tidesDataChartView;


    QValueAxis *m_levelAxis;
    QDateTimeAxis *m_timeAxis;

    QSplineSeries *m_tidesDataSeries;
    QScatterSeries *m_selectionSeries;

    //QAction *m_nodalFactorsCtes;
    QAction *m_predictionSettingsAction;
    QAction *m_predictionRegularIntervalAction;
    QAction *m_predictionHighLowWatersAction;

    QAction *m_savePredictionsToFile;

    QMenu *m_predictionMenu;
    QMenu *m_dataMenu;

    PredictionSettings m_predictionSettings;

    QVector<HarmonicConstant> m_harmonicConstantsSet;

    void interfazLayout();
    void createActions();
    void createMenus();

};

#endif // PREDICTORMAINWINDOW_H
