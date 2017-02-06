#include "predictormainwindow.h"
#include "predictionfunctions.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextStream>

PredictorMainWindow::PredictorMainWindow(QWidget *parent) : QMainWindow(parent)
{
    m_predictionSettingsWidget = Q_NULLPTR;

    m_locationHCTree = new QTreeWidget;
    m_locationHCTree->setMinimumWidth(350);
    m_locationHCTree->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Preferred);

    m_tidesDataTableView = new QTableView;
    m_tidesDataTableView->setMinimumWidth(350);
    m_tidesDataTableView->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Preferred);

    m_tidesHighLowWaterTableView = new QTableView;
    m_tidesHighLowWaterTableView->setMinimumWidth(350);
    m_tidesHighLowWaterTableView->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Preferred);

    m_tidesDataModel = new ReadOnlyTableModel;
    m_tidesHighLowWaterDataModel = new ReadOnlyTableModel;

    m_tidesDataTableView->setModel(m_tidesDataModel);
    m_tidesHighLowWaterTableView->setModel(m_tidesHighLowWaterDataModel);

    m_tidesDataChart = new QChart;
    m_tidesDataChartView = new customChartView(m_tidesDataChart);

    m_levelAxis = new QValueAxis;
    m_timeAxis = new QDateTimeAxis;

    m_tidesDataSeries = new QSplineSeries;
    m_selectionSeries = new QScatterSeries;

    createActions();
    createMenus();
    interfazLayout();

    //this->setWindowModality(Qt::ApplicationModal);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

void PredictorMainWindow::setHarmonicConstants(const QVector<HarmonicConstant> &hcVector)
{
    m_harmonicConstantsSet = hcVector;
}

void PredictorMainWindow::createPredictionSettingsDialog()
{
    m_predictionSettingsWidget = new PredictonSettingsWidget(m_predictionSettings);

    connect(m_predictionSettingsWidget,&PredictonSettingsWidget::okButtonPressed,this,&PredictorMainWindow::getPredictionSettings);

    m_predictionSettingsWidget->show();
}

void PredictorMainWindow::getPredictionSettings()
{
    m_predictionSettings.setNMM(m_predictionSettingsWidget->nmm());
    m_predictionSettings.setBegingDate(m_predictionSettingsWidget->fromDateTime());
    m_predictionSettings.setEndDate(m_predictionSettingsWidget->endDateTime());
    m_predictionSettings.setInterval(m_predictionSettingsWidget->interval());
    m_predictionSettings.setMethod(m_predictionSettingsWidget->predictionMethod());

    m_predictionSettingsWidget->close();
}

void PredictorMainWindow::beginPredictionAtRegularIntervals()
{
    double nmm = m_predictionSettings.nmm();
    QDateTime from = m_predictionSettings.from();
    QDateTime to = m_predictionSettings.to();
    quint64 interval = m_predictionSettings.interval();

    QVector<TidesMeasurement> predData;

    switch (m_predictionSettings.method()) {
    case PredictionSettings::NF_CTE:
        predData = predictionWithNodalFactorCte(nmm,from,to,interval, m_harmonicConstantsSet);
        break;
    default:
        predData = predictionWithNodalFactorVar(nmm,from,to,interval, m_harmonicConstantsSet);
        break;
    }

    m_tidesDataModel->setMeasurements(predData);
}

void PredictorMainWindow::savePredicitionsToFile()
{
    QString filePath = QFileDialog::getSaveFileName(this,tr("Guardar Datos"),"","*.txt");
    QFileInfo fileInfo(filePath);
    if (fileInfo.suffix().isEmpty()) filePath.append(".txt");

    QFile file(filePath);

    if (file.open(QIODevice::WriteOnly)){
        QTextStream out(&file);

        QString fecha("FECHA");
        QString hora("HORA");
        QString nivel("NIVEL");

        out.setFieldWidth(8);
        out.setFieldAlignment(QTextStream::AlignCenter);
        out << fecha;

        out.setFieldWidth(0);
        out.setFieldAlignment(QTextStream::AlignCenter);
        out << "  ";

        out.setFieldWidth(8);
        out.setFieldAlignment(QTextStream::AlignCenter);
        out << hora;

        out.setFieldWidth(0);
        out.setFieldAlignment(QTextStream::AlignCenter);
        out << "  ";

        out.setFieldWidth(8);
        out.setFieldAlignment(QTextStream::AlignCenter);
        out << nivel;

        out.setFieldWidth(0);
        out.setFieldAlignment(QTextStream::AlignCenter);
        out << endl;

        foreach (TidesMeasurement tm, m_tidesDataModel->measurementData()) {
            out.setFieldWidth(10);
            out.setFieldAlignment(QTextStream::AlignCenter);
            out << tm.measurementDate().toString("dd/MM/yyyy");

            out.setFieldWidth(0);
            out << "  ";

            out.setFieldWidth(5);
            out << tm.measurementTime().toString("hh:mm");

            out.setFieldWidth(0);
            out << "  ";

            out.setFieldWidth(6);
            out.setRealNumberNotation(QTextStream::FixedNotation);
            out.setRealNumberPrecision(3);
            out << tm.seaLevel();

            out.setFieldWidth(0);
            out << endl;

        }
    }else{
        QMessageBox::warning(this,tr("Error al escribir archivo"),
                             tr("No se puede escribir el archivo %1:\n%2.")
                             .arg(file.fileName().arg(file.errorString())));
    }
    file.close();
}

void PredictorMainWindow::interfazLayout()
{
    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addWidget(m_locationHCTree);
    leftLayout->addWidget(m_tidesDataTableView);
    leftLayout->addWidget(m_tidesHighLowWaterTableView);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addWidget(m_tidesDataChartView);

    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(mainLayout);

    this->setCentralWidget(centralWidget);
}

void PredictorMainWindow::createActions()
{
    m_predictionSettingsAction = new QAction(QIcon(":images/configure2.png"),tr("Configuración"));
    connect(m_predictionSettingsAction,&QAction::triggered,this,&PredictorMainWindow::createPredictionSettingsDialog);

    m_predictionRegularIntervalAction = new QAction(QIcon(":images/arrow_right.png"),tr("Intervalos Regulares"));
    connect(m_predictionRegularIntervalAction,&QAction::triggered,this,&PredictorMainWindow::beginPredictionAtRegularIntervals);

    m_predictionHighLowWatersAction = new QAction(QIcon(":images/arrow_right.png"),tr("Máximos y Mínimos"));

    m_savePredictionsToFile = new QAction(tr("Guardar Prediciones"));
    connect(m_savePredictionsToFile,&QAction::triggered,this,&PredictorMainWindow::savePredicitionsToFile);
}

void PredictorMainWindow::createMenus()
{
    m_predictionMenu = menuBar()->addMenu(tr("Predicción"));
    m_predictionMenu->addAction(m_predictionSettingsAction);
    m_predictionMenu->addSeparator();
    m_predictionMenu->addAction(m_predictionRegularIntervalAction);
    m_predictionMenu->addAction(m_predictionHighLowWatersAction);

    m_dataMenu = menuBar()->addMenu(tr("Datos"));
    m_dataMenu->addAction(m_savePredictionsToFile);
}
