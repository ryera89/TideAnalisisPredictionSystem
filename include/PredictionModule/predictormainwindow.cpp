#include "predictormainwindow.h"
#include "predictionfunctions.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextStream>
#include <QFont>
#include <QTextCursor>
#include <iostream>
#include <QtConcurrent>

#include "include/mainComponents/spmmainwindow.h"

PredictorMainWindow::PredictorMainWindow(const QString &hcDataBaseDir, QWidget *parent) : QMainWindow(parent)
{
    m_predictionSettingsWidget = Q_NULLPTR;
    m_tablaMarea = Q_NULLPTR;

    m_locationHCTree = new QTreeWidget;
    m_locationHCTree->setMinimumWidth(340);
    m_locationHCTree->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Preferred);
    m_locationHCTree->setColumnCount(3);
    QStringList headersList;
    headersList << "Localización" << "Fecha Inicio" << "Fecha Fin";
    m_locationHCTree->setHeaderLabels(headersList);

    connect(m_locationHCTree,SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),
            this,SLOT(loadHCFromDataBase(QTreeWidgetItem*,QTreeWidgetItem*)));

    scanHCDataBase(hcDataBaseDir);

    m_tidesDataTableView = new MyTableView;
    m_tidesDataTableView->hide();
    m_tidesDataTableView->verticalHeader()->hide();
    m_tidesDataTableView->setSelectionMode(QAbstractItemView::ContiguousSelection);
    m_tidesDataTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tidesDataTableView->setMinimumWidth(340);
    m_tidesDataTableView->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Preferred);
    connect(m_tidesDataTableView,SIGNAL(rowsSelected(int,int)),this,SLOT(selectDataInChart(int,int)));
    connect(m_tidesDataTableView,SIGNAL(noRowsSelected()),this,SLOT(deselectDataInChart()));

    m_tidesHighLowWaterTableView = new QTableView;
    m_tidesHighLowWaterTableView->hide();
    m_tidesHighLowWaterTableView->verticalHeader()->hide();
    m_tidesHighLowWaterTableView->setSelectionMode(QAbstractItemView::ContiguousSelection);
    m_tidesHighLowWaterTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tidesHighLowWaterTableView->setMinimumWidth(340);
    m_tidesHighLowWaterTableView->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Preferred);

    m_tidesDataModel = new ReadOnlyTableModel;
    connect(m_tidesDataModel,&ReadOnlyTableModel::modelReset,this,&PredictorMainWindow::setChartSeriesData);
    m_tidesHighLowWaterDataModel = new ReadOnlyTableModel;

    m_tidesDataTableView->setModel(m_tidesDataModel);
    m_tidesDataTableView->setItemDelegate(new ReadOnlyTableDelegate);
    m_tidesHighLowWaterTableView->setModel(m_tidesHighLowWaterDataModel);
    m_tidesHighLowWaterTableView->setItemDelegate(new ReadOnlyTableDelegate);
    m_tidesDataTableView->resizeRowsToContents();
    m_tidesHighLowWaterTableView->resizeRowsToContents();

    //Chart--------------------------------------------------
    m_tidesDataChart = new QChart;
    m_tidesDataChartView = new customChartView(m_tidesDataChart);
    m_tidesDataChartView->setMinimumWidth(800);

    m_levelAxis = new QValueAxis;
    m_levelAxis->setTitleText(tr("Nivel [m]"));
    m_timeAxis = new QDateTimeAxis;
    m_timeAxis->setFormat("d/M/yy h:mm");
    m_timeAxis->setTitleText(tr("Fecha & Hora"));

    m_tidesDataSeries = new QSplineSeries;
    m_tidesDataSeries->setPointsVisible();
    m_selectionSeries = new QScatterSeries;
    m_selectionSeries->setMarkerSize(7);

    m_tidesDataChart->addSeries(m_tidesDataSeries);
    m_tidesDataChart->addSeries(m_selectionSeries);
    m_tidesDataChart->legend()->hide();

    m_tidesDataChart->setAxisX(m_timeAxis,m_tidesDataSeries);
    m_tidesDataChart->setAxisX(m_timeAxis,m_selectionSeries);

    m_tidesDataChart->setAxisY(m_levelAxis,m_tidesDataSeries);
    m_tidesDataChart->setAxisY(m_levelAxis,m_selectionSeries);

    connect(m_tidesDataChartView,&customChartView::seriesPointsPressedAndRealesed,this,&PredictorMainWindow::selectPoints);
    connect(m_tidesDataChartView,&customChartView::seriesPointPressed,this,&PredictorMainWindow::selectPoint);
    //---------------------------------------------------------------
    m_zoomXSlider = new QSlider(Qt::Horizontal);
    m_zoomXSlider->setFixedWidth(100);
    m_zoomXSlider->setTickInterval(1);
    m_zoomXSlider->setMinimum(1);

    m_zoomXSpinBox = new QSpinBox;
    m_zoomXSpinBox->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    m_zoomXSpinBox->setMinimum(1);

    m_currentXZoomLevel = 1;

    connect(m_zoomXSlider,&QAbstractSlider::valueChanged,m_zoomXSpinBox,&QSpinBox::setValue);
    connect(m_zoomXSpinBox,SIGNAL(valueChanged(int)),m_zoomXSlider,SLOT(setValue(int)));
    connect(m_zoomXSpinBox,SIGNAL(valueChanged(int)),this,SLOT(zoomXAxis(int)));

    m_zoomYSlider = new QSlider(Qt::Horizontal);
    m_zoomYSlider->setFixedWidth(100);
    m_zoomYSlider->setTickInterval(1);
    m_zoomYSlider->setRange(1,10);
    m_zoomYSlider->setValue(10);

    m_zoomYSpinBox = new QSpinBox;
    m_zoomYSpinBox->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    m_zoomYSpinBox->setRange(1,10);
    m_zoomYSpinBox->setValue(10);

    //m_currentYZoomLevel = 10;

    connect(m_zoomYSlider,&QAbstractSlider::valueChanged,m_zoomYSpinBox,&QSpinBox::setValue);
    connect(m_zoomYSpinBox,SIGNAL(valueChanged(int)),m_zoomYSlider,SLOT(setValue(int)));
    connect(m_zoomYSpinBox,SIGNAL(valueChanged(int)),this,SLOT(zoomYAxis(int)));

    m_centralWidget = new QWidget;

    m_chartWidget = new QWidget;
    //m_chartWidget->hide();

    m_hcDescriptionPlainTextEdit = new QTextEdit;
    m_hcDescriptionPlainTextEdit->setReadOnly(true);
    m_hcDescriptionPlainTextEdit->setMaximumHeight(200);
    QTextCharFormat charFormat;
    QFont f("Courier New",11);
    charFormat.setFont(f);
    m_hcDescriptionPlainTextEdit->setCurrentCharFormat(charFormat);
    m_hcDescriptionPlainTextEdit->setTextColor(Qt::darkGreen);
    m_hcDescriptionPlainTextEdit->setBackgroundRole(QPalette::Shadow);

    m_loadingLabel = new QLabel;
    m_loadingMovie = new QMovie(":images/carga7.gif");
    m_loadingLabel->setMovie(m_loadingMovie);
    m_loadingLabel->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    m_loadingLabel->hide();

    m_NMTLabel = new QLabel(tr("Nivel Mínimo Teórico"));
    m_NMTLabel->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    m_NMTLineEdit = new QLineEdit;
    m_NMTLineEdit->setReadOnly(true);
    m_NMTLineEdit->setAlignment(Qt::AlignRight);
    m_NMTLineEdit->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);

    m_regIntervalLabel = new QLabel;
    m_regIntervalLabel->setAlignment(Qt::AlignHCenter);
    m_regIntervalLabel->setStyleSheet("background-color: blue");
    m_regIntervalLabel->setText("<h3>Intervalos Regulares</h3>");
    m_regIntervalLabel->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    m_regIntervalLabel->hide();

    m_extremesLabel = new QLabel;
    m_extremesLabel->setAlignment(Qt::AlignHCenter);
    m_extremesLabel->setStyleSheet("background-color: red");
    m_extremesLabel->setText("<h3>Extremos</h3>");
    m_extremesLabel->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    m_extremesLabel->hide();

    createActions();
    createMenus();
    interfazLayout();

    this->setWindowTitle(tr("Predicción & Mínimo Teórico"));
    this->setWindowIcon(QIcon(":images/prediction.png"));
    this->setWindowState(Qt::WindowMaximized);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

void PredictorMainWindow::setHarmonicConstants(const QVector<HarmonicConstant> &hcVector)
{
    m_harmonicConstantsSet = hcVector;

    displayHCDescriptions();
}

void PredictorMainWindow::scanHCDataBase(const QString &hcDataBaseDir)
{
    QDir hcDir(hcDataBaseDir);

    if (!hcDir.exists()){
        QMessageBox::information(this,tr("Directorio no encontrado"),tr("El directorio %1 no existe").arg(hcDataBaseDir));

        return;
    }else{
        QStringList listNameFilters("*.hcr");
        hcDir.setNameFilters(listNameFilters);
        hcDir.setSorting(QDir::Name | QDir::IgnoreCase);

        QFileInfoList fileInfoList = hcDir.entryInfoList();

        QStringList nameList;
        foreach (QFileInfo fileInfo, fileInfoList) {
            nameList.push_back(fileInfo.baseName().toUpper());
        }

        QVector<QStringList> stripedFileNamesVector;

        foreach (QString fileName, nameList) {
            QStringList stripedFileName = fileName.split("_");
            stripedFileNamesVector.push_back(stripedFileName);
        }

        QStringList provinciaList;
        QStringList localidadList;
        QStringList fechaInicioList;
        QStringList fechaFinList;
        foreach (QStringList strList, stripedFileNamesVector){
            /*foreach(QString str, strList){
                std::cout << str.toStdString() << std::endl;
            }*/
            provinciaList.push_back(strList.at(0));
            localidadList.push_back(strList.at(1));
            fechaInicioList.push_back(strList.at(2));
            fechaFinList.push_back(strList.at(3));
        }

        if (provinciaList.isEmpty()) return; //Si no hay archivos de HC no se hace nada.

        QString provAux = provinciaList.at(0);
        QTreeWidgetItem *item = new QTreeWidgetItem;
        item->setText(0,provAux);
        m_locationHCTree->addTopLevelItem(item);
        int i = 0;
        foreach (QString strProv, provinciaList) {
            if (strProv == provAux){
                QTreeWidgetItem *itemChild = new QTreeWidgetItem(item);
                itemChild->setText(0,localidadList.at(i));
                itemChild->setText(1,fechaInicioList.at(i));
                itemChild->setText(2,fechaFinList.at(i));
                m_hashForHCFiles[itemChild] = fileInfoList.at(i).filePath();
            }else{
                provAux = strProv;
                item = new QTreeWidgetItem;
                item->setText(0,provAux);
                m_locationHCTree->addTopLevelItem(item);
                QTreeWidgetItem *itemChild = new QTreeWidgetItem(item);
                itemChild->setText(0,localidadList.at(i));
                itemChild->setText(1,fechaInicioList.at(i));
                itemChild->setText(2,fechaFinList.at(i));
                m_hashForHCFiles[itemChild] = fileInfoList.at(i).filePath();
            }

            ++i;
        }


    }
}

void PredictorMainWindow::createPredictionSettingsDialog()
{
    m_predictionSettingsWidget = new PredictonSettingsWidget(m_predictionSettings);

    connect(m_predictionSettingsWidget,&PredictonSettingsWidget::okButtonPressed,this,&PredictorMainWindow::getPredictionSettings);

    m_predictionSettingsWidget->show();
}

void PredictorMainWindow::createTidesTable()
{
    if (m_tidesDataModel->measurementData().isEmpty()){
        QMessageBox::information(this,tr("Error"),tr("No existen datos validos que mostrar"));
    }else{
    TidalData data(m_tidesDataModel->measurementData());
    m_tablaMarea = new TablaHorariaWidget;
    m_tablaMarea->loadTableData(data);

    m_tablaMarea->show();

    }
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
    m_tidesDataTableView->hide();
    m_regIntervalLabel->hide();

    m_loadingLabel->show();
    m_loadingMovie->start();

    double nmm = m_predictionSettings.nmm();
    QDateTime from = m_predictionSettings.from();
    QDateTime to = m_predictionSettings.to();
    quint64 interval = m_predictionSettings.interval();

    //QVector<TidesMeasurement> predData;

    QFuture<QVector<TidesMeasurement>> future;

    //future = QtConcurrent::run(predictionWithNodalFactorCte,nmm,from,to,interval,m_harmonicConstantsSet);

    //future = QtConcurrent::run(predictionWithNodalFactorVar,nmm,from,to,interval,m_harmonicConstantsSet);



    switch (m_predictionSettings.method()) {
    case PredictionSettings::NF_CTE:
        future = QtConcurrent::run(predictionsWithNodalFactorCte,nmm,from,to,interval,m_harmonicConstantsSet);
        break;
    default:
        future = QtConcurrent::run(predictionsWithNodalFactorVar,nmm,from,to,interval,m_harmonicConstantsSet);
        break;
    }

    while(future.isRunning()){
        qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    }

    m_tidesDataModel->setMeasurements(future.result());

    m_loadingMovie->stop();
    m_loadingLabel->hide();

    m_regIntervalLabel->show();
    m_tidesDataTableView->show();
}

void PredictorMainWindow::beginFindHighLowWaters()
{
    m_extremesLabel->hide();
    m_tidesHighLowWaterTableView->hide();

    m_loadingLabel->show();
    m_loadingMovie->start();

    double nmm = m_predictionSettings.nmm();
    QDateTime from = m_predictionSettings.from();
    QDateTime to = m_predictionSettings.to();

    //QVector<TidesMeasurement> predData;

    QFuture<QVector<TidesMeasurement>> future;

    switch (m_predictionSettings.method()) {
    case PredictionSettings::NF_CTE:
        future = QtConcurrent::run(findExtremesWithNodalFactorsCte,nmm,from,to,m_harmonicConstantsSet);
        break;
    default:
        future = QtConcurrent::run(findExtremesWithNodalFactorsVar,nmm,from,to,m_harmonicConstantsSet);
        break;
    }

    while(future.isRunning()){
        qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    }

    m_tidesHighLowWaterDataModel->setMeasurements(future.result());

    m_loadingMovie->stop();
    m_loadingLabel->hide();

    m_extremesLabel->show();
    m_tidesHighLowWaterTableView->show();
}

void PredictorMainWindow::beginDetermineNMT()
{
    hideNMTFac();
    m_loadingLabel->show();
    m_loadingMovie->start();

    double nmm = m_predictionSettings.nmm();

    QDateTime from = m_predictionSettings.from();

    QFuture<TidesMeasurement> future;

    future = QtConcurrent::run(determineLAT,nmm,from,m_harmonicConstantsSet);

    while(future.isRunning()){
        qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    }

    m_loadingMovie->stop();
    m_loadingLabel->hide();

    m_NMTLabel->show();
    m_NMTLineEdit->show();

    m_NMTLineEdit->setText(QString::number(future.result().seaLevel(),'f',3) + "m");
}

void PredictorMainWindow::savePredicitionsToFile()
{
    QString filePath = QFileDialog::getSaveFileName(this,tr("Guardar Datos"),"","*.txt");
    QFileInfo fileInfo(filePath);
    if (fileInfo.suffix().isEmpty()) filePath.append(".txt");

    QFile file(filePath);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream out(&file);


        out.setRealNumberNotation(QTextStream::FixedNotation);
        out.setRealNumberPrecision(3);

        out << "PRONÓSTICO DE MAREA A INTERVALOS REGULARES DE TIEMPO" << endl;

        out << "PROVINCIA: " << m_provincia << endl;
        out << "LOCALIDAD: " << m_localidad << endl;
        out << "LATITUD:   " << m_latitud << endl;
        out << "LONGITUD:  " << m_longitud << endl;

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
            out << " ";

            out.setFieldWidth(5);
            out << tm.measurementTime().toString("hh:mm");

            out.setFieldWidth(0);
            out << " ";

            out.setFieldWidth(6);
            //out.setRealNumberPrecision(3);
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

void PredictorMainWindow::saveHighLowWatersToFile()
{
    QString filePath = QFileDialog::getSaveFileName(this,tr("Guardar Datos"),"","*.txt");
    QFileInfo fileInfo(filePath);
    if (fileInfo.suffix().isEmpty()) filePath.append(".txt");

    QFile file(filePath);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream out(&file);


        out.setRealNumberNotation(QTextStream::FixedNotation);
        out.setRealNumberPrecision(3);

        out << "PRONÓSTICO BAJAMARES Y PLEAMARES" << endl;

        out << "PROVINCIA: " << m_provincia << endl;
        out << "LOCALIDAD: " << m_localidad << endl;
        out << "LATITUD:   " << m_latitud << endl;
        out << "LONGITUD:  " << m_longitud << endl;

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

        foreach (TidesMeasurement tm, m_tidesHighLowWaterDataModel->measurementData()) {
            out.setFieldWidth(10);
            out.setFieldAlignment(QTextStream::AlignCenter);
            out << tm.measurementDate().toString("dd/MM/yyyy");

            out.setFieldWidth(0);
            out << " ";

            out.setFieldWidth(5);
            out << tm.measurementTime().toString("hh:mm");

            out.setFieldWidth(0);
            out << " ";

            out.setFieldWidth(6);
            //out.setRealNumberPrecision(3);
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

void PredictorMainWindow::setChartSeriesData()
{
    settingUpXZoomValues();

    m_zoomYSpinBox->setValue(10);

    m_chartWidget->show();

    m_selectionSeries->clear();

    QPointF MinMax = findMinAndMax(m_tidesDataModel->measurementData());
    m_yMin = MinMax.x();
    m_yMax = MinMax.y();
    m_levelAxis->setRange(m_yMin,m_yMax);

    QDateTime datetime0;
    QDateTime datetimef;

    if (!m_tidesDataModel->measurementData().isEmpty()){
        datetime0 = m_tidesDataModel->measurementData().first().measurementDateTime();
        datetimef = m_tidesDataModel->measurementData().last().measurementDateTime();
    }

    m_timeAxis->setRange(datetime0,datetime0.addSecs(24*3600));

    m_tidesDataSeries->replace(m_tidesDataModel->measurementDataRealPoints());

}

void PredictorMainWindow::setChartTheme(QChart::ChartTheme theme)
{
    m_tidesDataChart->setTheme(theme);
}

void PredictorMainWindow::setAnimationOptions(QChart::AnimationOptions animation)
{
    m_tidesDataChart->setAnimationOptions(animation);
}

void PredictorMainWindow::setRenderHints(QPainter::RenderHints hint)
{
    m_tidesDataChartView->setRenderHints(hint);
}

void PredictorMainWindow::selectPoints(QPointF pPoint, QPointF rPoint)
{
    QPointF pSeriesPoint = m_tidesDataChart->mapToValue(pPoint,m_tidesDataSeries);
    QPointF rSeriesPoint = m_tidesDataChart->mapToValue(rPoint,m_tidesDataSeries);

    m_tidesDataTableView->clearSelection();

    QVector<QPointF> selectedPoints;
    QVector<int> rowIndexes;

    int selRow = 0;
    foreach (QPointF point, m_tidesDataSeries->pointsVector()) {
        if (pSeriesPoint.x() <= rSeriesPoint.x()){
            if (point.x() >= pSeriesPoint.x() && point.x() <= rSeriesPoint.x()){
                selectedPoints.append(point);
                rowIndexes.append(selRow);
                //m_mapForValuesInMainAndSelectionSeries[posInMain] = posInSelection;
                //++posInSelection;
            }
            if (point.x() > rSeriesPoint.x()) break;
        }else{
            if (point.x() >= rSeriesPoint.x() && point.x() <= pSeriesPoint.x()){
                selectedPoints.append(point);
                rowIndexes.append(selRow);
                //m_mapForValuesInMainAndSelectionSeries[posInMain] = posInSelection;
                //++posInSelection;
            }
            if (point.x() > pSeriesPoint.x()) break;
        }
        ++selRow;
    }

    m_selectionSeries->replace(selectedPoints);

    if (!rowIndexes.isEmpty()){
        m_tidesDataTableView->setRowSelection(0,rowIndexes.first(),2,rowIndexes.last(),QItemSelectionModel::Select);
    }

}

void PredictorMainWindow::selectPoint(QPointF point)
{
    m_selectionSeries->clear();
    m_tidesDataTableView->clearSelection();

    QVector<QPointF> selectedPoints;

    QVector<QPointF> seriesPointsVector;
    int cont = 0;
    int selRow = 0;
    foreach (QPointF p, m_tidesDataSeries->pointsVector()) {
        seriesPointsVector.append(m_tidesDataChart->mapToPosition(p,m_tidesDataSeries));
    }
    qreal distance = INT64_MAX; //distancia al punto
    QPointF closest(INT64_MAX, INT64_MAX); //punto mas cercano

    foreach (QPointF po, seriesPointsVector) {
        qreal currentDist = qSqrt(qPow((po.y() - point.y()),2) + qPow((po.x() - point.x()),2));

        if (currentDist < distance){
            distance = currentDist;
            closest = po;
            //posInMainSeries = cont;
            selRow = cont;
        }
        ++cont;
    }
    if (distance <= 5){
        QPointF selectedPoint = m_tidesDataChart->mapToValue(closest,m_tidesDataSeries);
        selectedPoints.append(selectedPoint);
        m_tidesDataTableView->selectRow(selRow);
        //m_mapForValuesInMainAndSelectionSeries[posInMainSeries] = 0;


        m_selectionSeries->replace(selectedPoints);

    }
}

void PredictorMainWindow::zoomXAxis(int zoomLevel)
{
    if (m_tidesDataSeries){
        if (m_tidesDataSeries->pointsVector().isEmpty()) return;

        quint64 xMin = m_tidesDataSeries->pointsVector().first().x();
        quint64 xMax = m_tidesDataSeries->pointsVector().last().x();

        quint64 showXMin = m_timeAxis->min().toMSecsSinceEpoch();
        quint64 showXMax = m_timeAxis->max().toMSecsSinceEpoch();

        quint64 interval = 24*3600*1000*qAbs(zoomLevel-m_currentXZoomLevel);

        if (m_currentXZoomLevel < zoomLevel){
            showXMin-=interval/2;
            showXMax+=interval/2;

            if (showXMin < xMin){
                quint64 dif = xMin - showXMin;
                showXMin = xMin;

                showXMax+=dif;
                if (showXMax > xMax){
                    showXMax = xMax;
                }
            }

            if (showXMax > xMax){
                quint64 dif = showXMax - xMax;
                showXMax = xMax;

                showXMin-=dif;
                if (showXMin < xMin){
                    showXMin = xMin;
                }
            }
        }else{
            showXMax-=interval/2;
            showXMin+=interval/2;

            quint64 dif = showXMax - showXMin;
            quint64 diflimit = 24*3600*1000;
            if (dif < diflimit){
                quint64 lim = diflimit - dif;
                showXMin-=lim/2;
                showXMax+=lim/2;

                if (showXMin < xMin){
                    quint64 dif = xMin - showXMin;
                    showXMin = xMin;

                    showXMax+=dif;
                    if (showXMax > xMax){
                        showXMax = xMax;
                    }
                }

                if (showXMax > xMax){
                    quint64 dif = showXMax - xMax;
                    showXMax = xMax;

                    showXMin-=dif;
                    if (showXMin < xMin){
                        showXMin = xMin;
                    }
                }

            }
        }
        m_currentXZoomLevel = zoomLevel;
        m_timeAxis->setRange(QDateTime::fromMSecsSinceEpoch(showXMin),QDateTime::fromMSecsSinceEpoch(showXMax));
    }
}

void PredictorMainWindow::zoomYAxis(int zoomLevel)
{
    double scale = 0.0;

    switch (zoomLevel) {
    case 1:
        scale = 0.9;
        break;
    case 2:
        scale = 0.8;
        break;
    case 3:
        scale = 0.7;
        break;
    case 4:
        scale = 0.6;
        break;
    case 5:
        scale = 0.5;
        break;
    case 6:
        scale = 0.4;
        break;
    case 7:
        scale = 0.3;
        break;
    case 8:
        scale = 0.2;
        break;
    case 9:
        scale = 0.1;
        break;
    default:
        scale = 0.0;
        break;
    }

    if (m_tidesDataSeries){
        double minYAxis = m_yMin - scale*(m_yMax - m_yMin);
        double maxYAxis = m_yMax + scale*(m_yMax - m_yMin);

        m_levelAxis->setRange(minYAxis,maxYAxis);
    }
}

void PredictorMainWindow::selectDataInChart(int row0, int rowf)
{
    m_selectionSeries->clear();

    if (m_tidesDataSeries->pointsVector().isEmpty()) return;

    for (int i = row0; i <= rowf; ++i){
        m_selectionSeries->append(m_tidesDataSeries->at(i));
    }
}

void PredictorMainWindow::deselectDataInChart()
{
    m_selectionSeries->clear();
}

void PredictorMainWindow::loadHCFromDataBase(QTreeWidgetItem *current, QTreeWidgetItem *prev)
{
    Q_UNUSED(prev);

    if (m_hashForHCFiles.contains(current) && m_currentFile != m_hashForHCFiles.value(current)){
        m_currentFile = m_hashForHCFiles.value(current);
        loadHCFromDataBaseFile(m_currentFile);
        m_predictionRegularIntervalAction->setEnabled(true);
        m_predictionHighLowWatersAction->setEnabled(true);
        m_detNMTAction->setEnabled(true);
        QString currentInfoFile = m_currentFile;
        currentInfoFile.replace(".hcr",".txt");
        readHCInfoFromFile(currentInfoFile);
    }
}

void PredictorMainWindow::interfazLayout()
{
    QHBoxLayout *nmtLayout = new QHBoxLayout;
    nmtLayout->addWidget(m_NMTLabel);
    nmtLayout->addWidget(m_NMTLineEdit);
    hideNMTFac();

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addWidget(m_locationHCTree);
    leftLayout->addWidget(m_regIntervalLabel);
    leftLayout->addWidget(m_tidesDataTableView);
    leftLayout->addWidget(m_extremesLabel);
    leftLayout->addWidget(m_tidesHighLowWaterTableView);
    leftLayout->addLayout(nmtLayout);
    leftLayout->addWidget(m_loadingLabel);
    leftLayout->setAlignment(nmtLayout,Qt::AlignHCenter);
    leftLayout->setAlignment(m_loadingLabel,Qt::AlignHCenter);

    QHBoxLayout *zoomXLayout = new QHBoxLayout;
    zoomXLayout->addWidget(m_zoomXSlider);
    zoomXLayout->addWidget(m_zoomXSpinBox);
    zoomXLayout->setSpacing(0);

    QHBoxLayout *zoomYLayout = new QHBoxLayout;
    zoomYLayout->addWidget(m_zoomYSlider);
    zoomYLayout->addWidget(m_zoomYSpinBox);
    zoomYLayout->setSpacing(0);

    QHBoxLayout *zoomLayout = new QHBoxLayout;
    zoomLayout->addLayout(zoomYLayout);
    zoomLayout->addLayout(zoomXLayout);

    QVBoxLayout *rigthLayout = new QVBoxLayout;
    rigthLayout->addWidget(m_tidesDataChartView);
    rigthLayout->addLayout(zoomLayout);
    rigthLayout->setAlignment(zoomLayout,Qt::AlignRight);
    rigthLayout->addWidget(m_hcDescriptionPlainTextEdit);

    m_chartWidget->setLayout(rigthLayout);
    m_chartWidget->layout()->setMargin(0);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addWidget(m_chartWidget);


    m_centralWidget->setLayout(mainLayout);

    this->setCentralWidget(m_centralWidget);
}

void PredictorMainWindow::createActions()
{
    m_predictionSettingsAction = new QAction(QIcon(":images/configure2.png"),tr("Configuración"));
    connect(m_predictionSettingsAction,&QAction::triggered,this,&PredictorMainWindow::createPredictionSettingsDialog);

    m_predictionRegularIntervalAction = new QAction(QIcon(":images/arrow_right.png"),tr("Intervalos Regulares"));
    m_predictionRegularIntervalAction->setEnabled(false);
    connect(m_predictionRegularIntervalAction,&QAction::triggered,this,&PredictorMainWindow::beginPredictionAtRegularIntervals);

    m_predictionHighLowWatersAction = new QAction(QIcon(":images/arrow_right.png"),tr("Máximos y Mínimos"));
    m_predictionHighLowWatersAction->setEnabled(false);
    connect(m_predictionHighLowWatersAction,&QAction::triggered,this,&PredictorMainWindow::beginFindHighLowWaters);

    m_detNMTAction = new QAction(QIcon(":images/arrow_right.png"),tr("Nivel Mínimo Teórico"));
    m_detNMTAction->setEnabled(false);
    connect(m_detNMTAction,&QAction::triggered,this,&PredictorMainWindow::beginDetermineNMT);

    m_tidesTableAction = new QAction(QIcon(":images/timetable.png"),tr("Tabla de Marea"));
    connect(m_tidesTableAction,&QAction::triggered,this,&PredictorMainWindow::createTidesTable);


    m_savePredictionsToFile = new QAction(QIcon(":images/writeToFile1.png"),tr("Guardar Prediciones"));
    connect(m_savePredictionsToFile,&QAction::triggered,this,&PredictorMainWindow::savePredicitionsToFile);

    m_saveHighAndLowWatersToFile = new QAction(QIcon(":images/writeToFile1.png"),tr("Guardar Niveles Extremos"));
    connect(m_saveHighAndLowWatersToFile,&QAction::triggered,this,&PredictorMainWindow::saveHighLowWatersToFile);
}

void PredictorMainWindow::createMenus()
{
    m_predictionMenu = menuBar()->addMenu(tr("Predicción"));
    m_predictionMenu->addAction(m_predictionSettingsAction);
    m_predictionMenu->addSeparator();
    m_predictionMenu->addAction(m_predictionRegularIntervalAction);
    m_predictionMenu->addAction(m_predictionHighLowWatersAction);
    m_predictionMenu->addAction(m_detNMTAction);

    m_dataMenu = menuBar()->addMenu(tr("Datos"));
    m_dataMenu->addAction(m_tidesTableAction);
    m_dataMenu->addSeparator();
    m_dataMenu->addAction(m_savePredictionsToFile);
    m_dataMenu->addAction(m_saveHighAndLowWatersToFile);
}

void PredictorMainWindow::settingUpXZoomValues()
{
    m_zoomXSpinBox->setValue(1);

    if (!m_tidesDataModel->measurementData().isEmpty()){
        QDateTime ini = m_tidesDataModel->measurementData().first().measurementDateTime();
        QDateTime end = m_tidesDataModel->measurementData().last().measurementDateTime();

        quint64 days= ini.daysTo(end);

        m_zoomXSpinBox->setMaximum(days + 1);
        m_zoomXSlider->setMaximum(days + 1);
    }else{
        m_zoomXSlider->setMaximum(1);
        m_zoomXSpinBox->setMaximum(1);
    }
}

bool PredictorMainWindow::loadHCFromDataBaseFile(const QString &filePath)
{

    m_harmonicConstantsSet.clear(); //Limpiando el set anterior para cargar el set nuevo

    QFile file(filePath);

    if (file.open(QIODevice::ReadOnly)){
        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_5_7);

        qint32 hcmagic;

        in >> hcmagic;

        if (hcmagic != SPMmainWindow::HCMagicNumber){ //Chequeo al tipo de archivo abierto
            QMessageBox::information(this,tr("Error Leyendo Archivo"),tr("El archivo %1 no es del tipo de .hcr").arg(file.fileName()));
            file.close();
            return false;
        }

        QApplication::setOverrideCursor(Qt::WaitCursor);

        QString provincia;
        QString localidad;
        QString localizationName;
        double latitud;
        double longitud;

        in >> provincia >> localidad >> localizationName >> latitud >> longitud;

        m_provincia = provincia;
        m_localidad = localidad;
        m_localizationName = localizationName;
        m_latitud = latitud;
        m_longitud = longitud;

        quint32 dataNumber;

        in >> dataNumber;

        QString hcName;
        double hcFrequency;
        double hcAmplitud;
        double hcPhase;
        double hcCorrectedPhase;
        int origin;
        int D1;
        int D2;
        int D3;
        int D4;
        int D5;
        int D6;
        int Dext;

        HarmonicConstant::Origin hcOrigin;

        for (quint32 i = 0; i < dataNumber; ++i){

            in >> hcName >> hcFrequency >> hcAmplitud >> hcPhase >> hcCorrectedPhase >> origin
                    >> D1 >> D2 >> D3 >> D4 >> D5 >> D6 >> Dext;

            switch (origin) {
            case 0:    //SOLAR componentes de origen solar f = 1.0 u = 0.0
                hcOrigin = HarmonicConstant::SOLAR;
                break;
            case 1:    //LUNAR_LONGPERIOD_1  componentes Mm, Msf u = 0, f = [2/3-pow(sin(I),2)]/0.5021
                hcOrigin = HarmonicConstant::LUNAR_LONGPERIOD_1;
                break;
            case 2:     //LUNAR_LONGPERIOD_2  componente Mf u = -2ξ, f = pow(sin(I),2)/0.1578
                hcOrigin = HarmonicConstant::LUNAR_LONGPERIOD_2;
                break;
            case 3:   //LUNAR_DIURNAL_1 componentes lunares diurnas O1,Q1,2Q1,RHO1,SIGMA1,SO3 u = 2ξ-ν, f = sin(I)*pow(cos(I/2),2)/0.3800
                hcOrigin = HarmonicConstant::LUNAR_DIURNAL_1;
                break;
            case 4:      //LUNAR_DIURNAL_2 componentes lunares diurnas J1,CHI1,THETA1,MP1,SO1 u = -ν, f = sin(2I)/0.7214
                hcOrigin = HarmonicConstant::LUNAR_DIURNAL_2;
                break;
            case 5:      //LUNAR_DIURNAL_3 lunares diurnas OO1, KQ1 f = sin(I)*pow(sin(I/2),2)/0.0164, u = -2ξ-ν
                hcOrigin = HarmonicConstant::LUNAR_DIURNAL_3;
                break;
            case 6:   //COMBINATION_DIURNAL_1 componente M1 f = sin(I)*pow(cos(I/2),2)/(0.3800*Qa) = f(O1)/Qa, u = ξ-ν+Q
                hcOrigin = HarmonicConstant::COMBINATION_DIURNAL_1;
                break;
            case 7:   //COMBINATION_DIURNAL_2 componentes K1, SK3, f = sqrt(0.8965*pow(sin(2I),2)+0.6001*sin(2I)cos(ν) + 0.1006),u = - ν’
                hcOrigin = HarmonicConstant::COMBINATION_DIURNAL_2;
                break;
            case 8:  //LUNAR_SEMIDIURNAL_1 componentes lunares semidiurnas M2,N2,2N2,NU2,LAMDA2,MU2,2SM2,MS4,2SM6
                hcOrigin = HarmonicConstant::LUNAR_SEMIDIURNAL_1;
                break;
            case 9:  //LUNAR_SEMIDIURNAL_1_2 componente 2SM2
                hcOrigin = HarmonicConstant::LUNAR_SEMIDIURNAL_1_2;
                break;
            case 10:  //LUNAR_SEMIDIURNAL_2 componente lunar semidiurna KJ2
                hcOrigin = HarmonicConstant::LUNAR_SEMIDIURNAL_2;
                break;
            case 11:  //COMBINATION_SEMIDIURNAL_1 componente semidiurna L2
                hcOrigin = HarmonicConstant::COMBINATION_SEMIDIURNAL_1;
                break;
            case 12:  //COMBINATION_SEMIDIURNAL_2 componente semidiurna K2
                hcOrigin = HarmonicConstant::COMBINATION_SEMIDIURNAL_2;
                break;
            case 13:   //LUNAR_TERDIURNAL componente M3
                hcOrigin = HarmonicConstant::LUNAR_TERDIURNAL;
                break;
            case 14:    //SHALLOW_1 las componentes MNS2,M4,MN4,2MS6,MSN6,2(MS)8
                hcOrigin = HarmonicConstant::SHALLOW_1;
                break;
            case 15:    //SHALLOW_2 componentes M6,2MN6,3MS8,2MSN8
                hcOrigin = HarmonicConstant::SHALLOW_2;
                break;
            case 16:    //SHALLOW_3 componentes M8
                hcOrigin = HarmonicConstant::SHALLOW_3;
                break;
            case 17:    //SHALLOW_COMB_1 componentes MK3
                hcOrigin = HarmonicConstant::SHALLOW_COMB_1;
                break;
            case 18:    //SHALLOW_COMB_2 componentes 2MK3
                 hcOrigin = HarmonicConstant::SHALLOW_COMB_2;
                break;
            case 19:    //SHALLOW_COMB_3 componentes MK4
                 hcOrigin = HarmonicConstant::SHALLOW_COMB_3;
                break;
            default:
                break;
            }
           DoodsonNumbers dodsonNum(D1,D2,D3,D4,D5,D6,Dext);

           HarmonicConstant hc(hcName,hcFrequency,dodsonNum,hcOrigin);
           //hc.setName(hcName);
           //hc.setFrequency(hcFrequency);
           hc.setAmplitud(hcAmplitud);
           hc.setPhase(hcPhase);
           hc.setCorrectedPhase(hcCorrectedPhase);
           //hc.setOrigin(hcOrigin);

           m_harmonicConstantsSet.push_back(hc);
        }
        file.close();
        //displayHCDescriptions();
        QApplication::restoreOverrideCursor();
        return true;
    }
    QMessageBox::information(this,tr("Error Leyendo Archivo"),tr("El archivo %1 no se pudo leer").arg(file.fileName()));
    return false;
}

void PredictorMainWindow::readHCInfoFromFile(const QString &infoFilePath)
{
    m_hcDescriptionPlainTextEdit->clear();

    QFile file(infoFilePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&file);
        while(!in.atEnd()){
            m_hcDescriptionPlainTextEdit->append(in.readLine());
        }
        //m_hcDescriptionPlainTextEdit->setPlainText(in.readAll());
        //return in.readAll();
    }else{
        //return tr("No existe ningún registro de información sobre este set de constantes armónicas.").toUpper();
        m_hcDescriptionPlainTextEdit->append(tr("No existe ningún registro de información sobre este set de constantes armónicas.").toUpper());
    }
}

void PredictorMainWindow::hideNMTFac()
{
    m_NMTLabel->hide();
    m_NMTLineEdit->hide();
}

void PredictorMainWindow::displayHCDescriptions()
{
    m_hcDescriptionPlainTextEdit->document()->clear();

    QTextCursor cur(m_hcDescriptionPlainTextEdit->document());

    cur.movePosition(QTextCursor::Start);

    QTextCharFormat textFormat;
    textFormat.setFontWeight(QFont::Normal);
    textFormat.setFontPointSize(11);

    cur.insertText("Provincia: " + m_provincia,textFormat);
    cur.insertBlock();
    cur.insertText("Localidad: " + m_localidad,textFormat);
    cur.insertBlock();
    cur.insertText("Latitud: " + QString::number(m_latitud,'f',3),textFormat);
    cur.insertBlock();
    cur.insertText("Longitud: " + QString::number(m_longitud,'f',3),textFormat);

    cur.insertBlock();
    cur.insertBlock();

    int tableRowCount = m_harmonicConstantsSet.size() + 1;
    int tableColCount = 7;

    //QTextTableFormat tableFormat;

    QTextTable *table = cur.insertTable(tableRowCount,tableColCount);

    QTextBlockFormat cellFormat;
    cellFormat.setAlignment(Qt::AlignCenter);

    textFormat.setFontPointSize(9);

    cur = table->cellAt(0,0).firstCursorPosition();
    cur.setBlockFormat(cellFormat);
    cur.insertText("Componente",textFormat);

    cur = table->cellAt(0,1).firstCursorPosition();
    cur.setBlockFormat(cellFormat);
    cur.insertText("Frecuencia",textFormat);

    cur = table->cellAt(0,2).firstCursorPosition();
    cur.setBlockFormat(cellFormat);
    cur.insertText("Amplitud",textFormat);

    cur = table->cellAt(0,3).firstCursorPosition();
    cur.setBlockFormat(cellFormat);
    cur.insertText("Fase",textFormat);

    cur = table->cellAt(0,4).firstCursorPosition();
    cur.setBlockFormat(cellFormat);
    cur.insertText("Fase_Corr",textFormat);

    cur = table->cellAt(0,5).firstCursorPosition();
    cur.setBlockFormat(cellFormat);
    cur.insertText("Origen",textFormat);

    cur = table->cellAt(0,6).firstCursorPosition();
    cur.setBlockFormat(cellFormat);
    cur.insertText("Número Doodson",textFormat);

    int i = 1;
    foreach (const HarmonicConstant &hc, m_harmonicConstantsSet) {
        cur = table->cellAt(i,0).firstCursorPosition();
        cur.setBlockFormat(cellFormat);
        cur.insertText(hc.name());

        cur = table->cellAt(i,1).firstCursorPosition();
        cur.setBlockFormat(cellFormat);
        cur.insertText(QString::number(hc.frequency(),'f',6),textFormat);

        cur = table->cellAt(i,2).firstCursorPosition();
        cur.setBlockFormat(cellFormat);
        cur.insertText(QString::number(hc.amplitud(),'f',3),textFormat);

        cur = table->cellAt(i,3).firstCursorPosition();
        cur.setBlockFormat(cellFormat);
        cur.insertText(QString::number(hc.phase(),'f',3),textFormat);

        cur = table->cellAt(i,4).firstCursorPosition();
        cur.setBlockFormat(cellFormat);
        cur.insertText(QString::number(hc.correctedPhase(),'f',3),textFormat);

        cur = table->cellAt(i,5).firstCursorPosition();
        cur.setBlockFormat(cellFormat);
        cur.insertText(QString::number(hc.origin()),textFormat);

        cur = table->cellAt(i,6).firstCursorPosition();
        cur.setBlockFormat(cellFormat);
        cur.insertText("(" + QString::number(hc.doodsonNumbers().D1()) + ", " + QString::number(hc.doodsonNumbers().D2())
                       + ", " + QString::number(hc.doodsonNumbers().D3()) + ", " + QString::number(hc.doodsonNumbers().D4())
                       + ", " + QString::number(hc.doodsonNumbers().D5()) + ", " + QString::number(hc.doodsonNumbers().D6())
                       + ", " + QString::number(hc.doodsonNumbers().Extended()) + ")",textFormat);



       ++i;

    }

}

QPointF findMinAndMax(const QVector<TidesMeasurement> &measurements)
{
    double min = 0.0;
    double max = 1.0;

    if (measurements.size()){
        min = measurements.first().seaLevel();
        max = min;
    }

    foreach (const TidesMeasurement &tm, measurements) {
        if (min > tm.seaLevel()) min = tm.seaLevel();
        if (max < tm.seaLevel()) max = tm.seaLevel();
    }

    return QPointF(min,max);
}
