#include "spmmainwindow.h"

#include "include/ProjectMetaData/metadatadialog.h"
#include "include/HarmonicConstantsModule/schemewidget.h"
#include "include/HarmonicConstantsModule/FrequencyEditor/freqeditor.h"
#include <QHBoxLayout>
#include "include/maths/minsqr.h"
#include "include/maths/fitsvd.h"
#include "include/measurement/tidaldata.h"
#include "include/NonHarmonicConstantsModule/FrontEnd/nonharmoninccalcdialog.h"
#include "include/HarmonicConstantsModule/Model_View/harmonicconstantfrequencytablemodel.h"
#include <QtMath>
#include <iostream>

QVector<HarmonicConstant> SPMmainWindow::m_selectedHarmonicConstantVector = QVector<HarmonicConstant>();

SPMmainWindow::SPMmainWindow(QWidget *parent) : QMainWindow(parent)
{
    m_central = new CentralWidget(this);

    m_loadDialog = 0;
    m_tablaHorariaWidget = 0;
    m_manualDataIntroductionWidget = 0;
    m_projectMetaDataDialog = 0;
    m_schemeWidget = 0;
    m_nonHarmonicConstantDialog = 0;
    m_frequencyEditor = 0;
    m_nivelacionAcuaticaWidget = 0;
    setCentralWidget(m_central);



    //m_datosDeMarea = TidalData(QVector<TidesMeasurement>(100));

    //m_tidalTableModel = new ReadOnlyTableModel(m_datosDeMarea);

    //m_central->tableView()->setModel(m_tidalTableModel);

    /*int width = 20 + m_central->tableView()->verticalHeader()->width();
    for (int i = 0; i < m_tidalTableModel->columnCount(QModelIndex()); ++i){
         width += m_central->tableView()->columnWidth(i);
    }
    m_central->tableView()->setFixedWidth(width);*/

    //mapper = new XYTidalChartModelMapper(m_tidalTableModel,m_central->chartSerie());
    //connect(mapper,SIGNAL(chartSeriesSeted()),m_central,SLOT(setSeriesData()));
    //connect(mapper,SIGNAL(chartSeriesUpdated(int)),m_central,SLOT(updateSerieData(int)));

    //this->layout()->addWidget(m_dataTable);
    //this->layout()->addWidget(m_freqEditor);

    createActions();
    createMenus();
    createToolBars();

    m_themeDarkAction->setChecked(true);
    m_animationNoAnimationAction->setChecked(true);

    loadHarmonicConstantsFromFile();

   // QHBoxLayout *mainLayout = new QHBoxLayout;

    //mainLayout->addWidget(m_dataTable);
   // mainLayout->addWidget(m_freqEditor);

    //this->layout()->addItem(mainLayout);
    setWindowIcon(QIcon(":images/aquarius-48.png"));
}

QVector<double> SPMmainWindow::funcion(const double &t)
{
    QVector<double> resp(1,1.0);

    foreach (HarmonicConstant harmonic, SPMmainWindow::m_selectedHarmonicConstantVector) {
        double val = qCos(qDegreesToRadians(harmonic.frequency()*t));
        resp.append(val);
    }
    foreach (HarmonicConstant harmonic, m_selectedHarmonicConstantVector) {
        double val = qSin(qDegreesToRadians(harmonic.frequency()*t));
        resp.append(val);
    }
    return resp;
}

QSize SPMmainWindow::sizeHint() const
{
    return this->maximumSize();
}

void SPMmainWindow::loadDataFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Cargar Archivo"));
    if (!fileName.isEmpty()){
        m_loadDialog = new LoadDialog(fileName,this);
        m_loadDialog->setProjectMetaData(m_metadataStorage);
        //connect(m_loadDialog,SIGNAL(dataGeted(QVector<QStringList>,int,int,int, const QString&, const QString&)),
                    //this,SLOT(recieveData(QVector<QStringList>,int,int,int, const QString&, const QString&)));
        connect(m_loadDialog,SIGNAL(importButtonClicked()),this,SLOT(beginDataExtrationFromFile()));

        //TODO: Las conexiones de los senales del dialogo para coger la localizacion Eq_Id, Lat, Long
        m_loadDialog->show();
    }

}

void SPMmainWindow::createManualDataIntWidget()
{
    m_manualDataIntroductionWidget = new ManualDataIntroductionWidget(this);
    m_manualDataIntroductionWidget->setProjectMetaData(m_metadataStorage);
    connect(m_manualDataIntroductionWidget,SIGNAL(okButtonClicked()),
            this,SLOT(beginDataExtration()));
    m_manualDataIntroductionWidget->show();
}

void SPMmainWindow::crearTablaHoraria()
{
    if (m_central->tableModel()->measurementData().isEmpty()){
        QMessageBox::information(this,tr("Error"),tr("No existen datos validos que mostrar"));
    }else{
    TidalData data(m_central->tableModel()->measurementData());
    m_tablaHorariaWidget = new TablaHorariaWidget;
    m_tablaHorariaWidget->loadTableData(data);

    m_tablaHorariaWidget->show();

    }
}

void SPMmainWindow::createMetaDataDialog()
{
    m_projectMetaDataDialog = new MetaDataDialog(m_metadataStorage, this,Qt::WindowCloseButtonHint);
    m_projectMetaDataDialog->show();
    connect(m_projectMetaDataDialog,SIGNAL(okButtonClicked(bool)),this,SLOT(updateMetaData()));
}

void SPMmainWindow::createNonHarmonicDialog()
{
    m_nonHarmonicConstantDialog = new NonHarmonicCalcDialog(m_metadataStorage.longitud(),this);
    m_nonHarmonicConstantDialog->loadHarmonicConstants(SPMmainWindow::m_selectedHarmonicConstantVector);
    m_nonHarmonicConstantDialog->setMetaData(m_metadataStorage);
    m_nonHarmonicConstantDialog->show();
}

void SPMmainWindow::createNivelacionAcuaticaWidget()
{
    m_nivelacionAcuaticaWidget = new NivelacionAcuaticaWidget;
    m_nivelacionAcuaticaWidget->show();
}

void SPMmainWindow::updateMetaData()
{
    m_metadataStorage.setProjectName(m_projectMetaDataDialog->projectName());
    m_metadataStorage.setStationName(m_projectMetaDataDialog->stationName());
    m_metadataStorage.setLocalizationName(m_projectMetaDataDialog->localizationName());
    m_metadataStorage.setCeroPuesto(m_projectMetaDataDialog->ceroPuesto());
    m_metadataStorage.setNivelReferencia(m_projectMetaDataDialog->nivelReferencia());
    m_metadataStorage.setCeroUnits(m_projectMetaDataDialog->ceroPuestoUnit());
    m_metadataStorage.setReferenceUnits(m_projectMetaDataDialog->nivelReferenciaUnit());
    m_metadataStorage.setLatitud(m_projectMetaDataDialog->latitud());
    m_metadataStorage.setLongitud(m_projectMetaDataDialog->longitud());
    m_metadataStorage.setEquipmentID(m_projectMetaDataDialog->equipmentId());

    m_projectMetaDataDialog->close();
}

void SPMmainWindow::createHarmonicAnalisisDialog()
{
    if (!createHarmonicAnalisisDialogFromConfigFile()){
        QStringList schemes;
        schemes << "default";
        QStringList componets;
        componets << "M2" << "S2" << "N2" << "K2" << "K1" << "Q1" << "P1" << "O1" << "M4" << "MS4" << "M6";
        QMap<QString,QMap<QString,bool>> schemesComponents;
        QMap<QString,bool> componentStatus;
        foreach (QString str, componets) {
            componentStatus[str] = true;
        }
        schemesComponents[schemes.at(0)] = componentStatus;
        QMap<QString,QString> descriptionMap;
        descriptionMap[schemes.at(0)] = "Esquema por defecto";

        QDateTime iniDateTime;
        QDateTime endDateTime;

        if (!m_central->tableModel()->measurementData().isEmpty()){
            iniDateTime = QDateTime(m_central->tableModel()->measurementData().first().measurementDate(),m_central->tableModel()->measurementData().first().measurementTime(),Qt::UTC);
            endDateTime = QDateTime(m_central->tableModel()->measurementData().last().measurementDate(),m_central->tableModel()->measurementData().last().measurementTime(),Qt::UTC);
        }

        m_schemeWidget = new  SchemeWidget(iniDateTime, endDateTime, schemes,componets,schemesComponents,descriptionMap,this);
    }
    connect(m_schemeWidget,SIGNAL(analizeButtonClicked()),this,SLOT(harmonicAnalisis()));
    connect(m_schemeWidget,SIGNAL(saveDataButtonClicked()),this,SLOT(saveAnalisisData()));
    connect(m_schemeWidget,SIGNAL(saveHarmonicConstantsButtonClicked()),this,SLOT(saveHarmonicConstantToFile()));
    connect(this,SIGNAL(harmonicAnalisisFinished()),m_schemeWidget,SLOT(enableSaveHarmonicConstantButton()));
    m_schemeWidget->show();

}

void SPMmainWindow::createFrequencyEditor()
{
    m_frequencyEditor = new FreqEditor(m_frequencyFilePath,this);

    m_frequencyEditor->show();
    connect(m_frequencyEditor,SIGNAL(acceptButtonClicked()),this,SLOT(saveFrequencyFile()));

}

bool SPMmainWindow::saveFrequencyFile()
{
    if (this->writeFrequencyFile(m_frequencyFilePath)){
        m_harmonicConstantVector = m_frequencyEditor->harmonicConstantsModel()->allData();
        m_frequencyEditor->close();
        QApplication::setOverrideCursor(Qt::WaitCursor);
        //TODO think about an splash screen
        syncData(m_harmonicConstantVector);
        QApplication::restoreOverrideCursor();
        return true;
    }
    return false;

}

void SPMmainWindow::harmonicAnalisis()
{

    if (m_schemeWidget->currentSelectionComboBoxIndex()){
        harmonicAnalisisWithCustomData();
    }else{
        harmonicAnalisisWithAllData();
    }

    emit harmonicAnalisisFinished();
}

void SPMmainWindow::harmonicAnalisisWithAllData()
{

    QMap<QString,bool> harmonicComponentStatus = m_schemeWidget->selectedSchemeComponentStatus();
    SPMmainWindow::m_selectedHarmonicConstantVector.clear();
    foreach (HarmonicConstant harmonic, m_harmonicConstantVector) {
        if (harmonicComponentStatus.value(harmonic.name())){
           SPMmainWindow::m_selectedHarmonicConstantVector.append(harmonic);
        }
    }
    //SPMmainWindow::m_selectedHarmonicConstantVector = aux;

    //QVector<TidesMeasurement> datos = m_tidalTableModel->measurementData().m_measurements; //Datos de marea;

    //TODO pensar ne filtrado de datos
    if (m_central->tableModel()->measurementData().isEmpty()) return;
    int year = m_central->tableModel()->measurementData().first().measurementDate().year();
    QDateTime yearBegin(QDate(year,1,1),QTime(0,0),Qt::UTC);

    valarray<double> timeValarray(m_central->tableModel()->measurementData().size());
    valarray<double> levelValarray(m_central->tableModel()->measurementData().size());

    int i = 0;
    foreach (TidesMeasurement meas, m_central->tableModel()->measurementData()) {
        quint64 seconds = yearBegin.secsTo(QDateTime(meas.measurementDate(),meas.measurementTime(),Qt::UTC));
        double t = seconds/3600.0;

        timeValarray[i] = t;
        levelValarray[i] = meas.seaLevel();
        ++i;

        //VAriante 2
        //timeValarray[i] = i + 1;
        //levelValarray[i] = meas.seaLevel();
        //++i;
    }

    valarray<double> var(1.0,m_central->tableModel()->measurementData().size());

    if (m_schemeWidget->isLuDecompositionAnalisis()){
        MinSqr minimosCuadrados(timeValarray,levelValarray,var,SPMmainWindow::funcion);
        minimosCuadrados.fitLU();

        for (int k = 0; k < SPMmainWindow::m_selectedHarmonicConstantVector.size(); ++k){
            SPMmainWindow::m_selectedHarmonicConstantVector[k].setComponentValues(minimosCuadrados.parametros()[k+1],minimosCuadrados.parametros()[k+1+(SPMmainWindow::m_selectedHarmonicConstantVector.size())]);
        }

        /*for (uint k = 0; k < minimosCuadrados.parametros().size(); ++k){
            std::cout << minimosCuadrados.parametros()[k] << std::endl;
        }

        std::cout << "Chi cuadrado=" <<minimosCuadrados.chiSquare() << std::endl;
         std::cout << "Nivel Medio=" <<minimosCuadrados.parametros()[0] << std::endl;*/
    }else{

        Fitsvd test(timeValarray,levelValarray,var,SPMmainWindow::funcion);
        test.fit();

        for (int k = 0; k < SPMmainWindow::m_selectedHarmonicConstantVector.size(); ++k){
            SPMmainWindow::m_selectedHarmonicConstantVector[k].setComponentValues(test.a[k+1],test.a[k+1+(SPMmainWindow::m_selectedHarmonicConstantVector.size())]);
        }

        /*for (uint k = 0; k < test.a.size(); ++k){
            std::cout << test.a[k] << std::endl;
        }

        std::cout << "Chi cuadrado=" << test.chisq << std::endl;
        std::cout << "Nivel Medio=" << test.a[0] << std::endl;*/
    }


    m_schemeWidget->setHarmonicConstantModelData(SPMmainWindow::m_selectedHarmonicConstantVector);

    m_schemeWidget->showHarmonicConstantTable();

}

void SPMmainWindow::harmonicAnalisisWithCustomData()
{
    QDateTime initialDateTime = m_schemeWidget->initialDateTime();
    QDateTime endDateTime = m_schemeWidget->endDateTime();
    if (initialDateTime >= endDateTime){
        QMessageBox::information(this,tr("Error en analisis"),tr("La fecha final es menor que la fecha inicial."));
        return;
    }

    quint64 timeInterval = m_schemeWidget->timeInterval();

    QMap<QString,bool> harmonicComponentStatus = m_schemeWidget->selectedSchemeComponentStatus();
    SPMmainWindow::m_selectedHarmonicConstantVector.clear();
    foreach (HarmonicConstant harmonic, m_harmonicConstantVector) {
        if (harmonicComponentStatus.value(harmonic.name())){
           SPMmainWindow::m_selectedHarmonicConstantVector.append(harmonic);
        }
    }

    if (m_central->tableModel()->measurementData().isEmpty()) return;
    QDateTime yearBegin(QDate(initialDateTime.date().year(),1,1),QTime(0,0),Qt::UTC);

    QVector<double> timeVector;
    QVector<double> levelVector;

    QDateTime auxDateTime = initialDateTime;
    foreach (TidesMeasurement meas, m_central->tableModel()->measurementData()) {
        if (auxDateTime <= endDateTime){
            if (auxDateTime == meas.measurementDateTime()){
                quint64 seconds = yearBegin.secsTo(QDateTime(meas.measurementDate(),meas.measurementTime(),Qt::UTC));
                double t = seconds/3600.0;

                timeVector.push_back(t);
                levelVector.push_back(meas.seaLevel());
            }
            while (auxDateTime <= meas.measurementDateTime()){
                auxDateTime = auxDateTime.addSecs(timeInterval);
            }

        }

    }
    valarray<double> timeValarray(timeVector.size());
    valarray<double> levelValarray(levelVector.size());

    for (uint i = 0; i < timeValarray.size(); ++i){
        timeValarray[i] = timeVector[i];
        levelValarray[i] = levelVector[i];
    }


    valarray<double> var(1.0,timeValarray.size());

    if (m_schemeWidget->isLuDecompositionAnalisis()){
        MinSqr minimosCuadrados(timeValarray,levelValarray,var,SPMmainWindow::funcion);
        minimosCuadrados.fitLU();



        for (int k = 0; k < SPMmainWindow::m_selectedHarmonicConstantVector.size(); ++k){
            SPMmainWindow::m_selectedHarmonicConstantVector[k].setComponentValues(minimosCuadrados.parametros()[k+1],minimosCuadrados.parametros()[k+1+(SPMmainWindow::m_selectedHarmonicConstantVector.size())]);
        }

        for (uint k = 0; k < minimosCuadrados.parametros().size(); ++k){
            std::cout << minimosCuadrados.parametros()[k] << std::endl;
        }

        std::cout << "Chi cuadrado=" <<minimosCuadrados.chiSquare() << std::endl;
         std::cout << "Nivel Medio=" <<minimosCuadrados.parametros()[0] << std::endl;
    }else{

        Fitsvd test(timeValarray,levelValarray,var,SPMmainWindow::funcion);
        test.fit();

        for (int k = 0; k < SPMmainWindow::m_selectedHarmonicConstantVector.size(); ++k){
            SPMmainWindow::m_selectedHarmonicConstantVector[k].setComponentValues(test.a[k+1],test.a[k+1+(SPMmainWindow::m_selectedHarmonicConstantVector.size())]);
        }

        for (uint k = 0; k < test.a.size(); ++k){
            std::cout << test.a[k] << std::endl;
        }

        std::cout << "Chi cuadrado=" << test.chisq << std::endl;
        std::cout << "Nivel Medio=" << test.a[0] << std::endl;
    }


    m_schemeWidget->setHarmonicConstantModelData(SPMmainWindow::m_selectedHarmonicConstantVector);

    m_schemeWidget->showHarmonicConstantTable();

}

void SPMmainWindow::saveHarmonicConstantToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("Guardar Constantes No Armonicas"),QString(),"*.txt");
    if (!fileName.isEmpty()){
        if (QFileInfo(fileName).suffix().isEmpty()) fileName.append(".txt");

        saveHarmonicConstants(fileName);
    }
}

bool SPMmainWindow::writeFrequencyFile(const QString &filePath)
{
    QFile file(filePath);

    if (file.open(QIODevice::WriteOnly)){
       QDataStream out(&file);
       out.setVersion(QDataStream::Qt_5_7);

       QApplication::setOverrideCursor(Qt::WaitCursor);

       out << qint32(ComponentsMagicNumber);

       out << qint16(m_frequencyEditor->harmonicConstantsModel()->rowCount(QModelIndex()));

       foreach (HarmonicConstant harmonicConstant, m_frequencyEditor->harmonicConstantsModel()->allData()) {
           out << harmonicConstant.name() << (double)harmonicConstant.frequency() << harmonicConstant.description();
       }

       QApplication::restoreOverrideCursor();

    }else{
        QMessageBox::warning(this,tr("Error al escribir archivo"),
                             tr("No se puede escribir el archivo %1:\n%2.")
                             .arg(file.fileName().arg(file.errorString())));

        return false;
    }

    return true;
}

bool SPMmainWindow::saveAnalisisData()
{
    QString filePath = QFileDialog::getSaveFileName(this,tr("Guardar Datos"),"","*.txt");
    QFileInfo fileInfo(filePath);
    if (fileInfo.suffix().isEmpty()) filePath.append(".txt");

    return saveAnalisisDataToFile(filePath);
}

/*void SPMmainWindow::recieveData(const QVector<QStringList> &data, int dateField, int timeField, int heightField, const QString &dateFormat, const QString &timeFormat)
{
    QVector<TidesMeasurement> measurements;
    for (int i = 0; i < data.size(); ++i){
        if (dateField <= data[i].size() && timeField <= data[i].size() && heightField <= data[i].size()){ //Chequea que el campo exista
            //QVariant dateVariant = data[i].at(dateField - 1);
            //QVariant timeVariant = data[i].at(timeField - 1);

            QDate date = QDate::fromString(data[i].at(dateField - 1),dateFormat);
            QTime time = QTime::fromString(data[i].at(timeField - 1), timeFormat);

            //TODO: Crear un chequeo para comprobar si se estan cargando bien los datos.

            bool d_ok;
            QVariant heightVariant = data[i].at(heightField - 1);
            double height = heightVariant.toDouble(&d_ok);

            if (date.isValid() && time.isValid() && d_ok){
                measurements.push_back(TidesMeasurement(height,date,time));
            }

        }

    }
    //Esto  es lo que se cambiaria
   m_tidalTableModel->setDataSource(measurements);

   m_tideChartView->chart()->removeSeries(m_series);
   m_tideChartView->chart()->removeAxis(m_timeAxis);

   m_timeAxis->setRange(QDateTime::fromMSecsSinceEpoch(m_series->at(0).x()),QDateTime::fromMSecsSinceEpoch(m_series->at(m_series->count() - 1).x()));

   m_tideChartView->chart()->addSeries(m_series);
   m_tideChartView->chart()->createDefaultAxes();

   m_tideChartView->chart()->setAxisX(m_timeAxis,m_series);
}*/

/*void SPMmainWindow::beginDataRecieve(const QVector<TidesMeasurement> &datos)
{
    m_tidalTableModel->setDataSource(datos);
}*/

void SPMmainWindow::setChartLightTheme(bool checked)
{
    if (checked)
        this->m_central->chartView()->chart()->setTheme(QChart::ChartThemeLight);
}

void SPMmainWindow::setChartDarkTheme(bool checked)
{
    if (checked)
        this->m_central->chartView()->chart()->setTheme(QChart::ChartThemeDark);
}

void SPMmainWindow::setChartBrownSandTheme(bool checked)
{
    if (checked)
        this->m_central->chartView()->chart()->setTheme(QChart::ChartThemeBrownSand);
}

void SPMmainWindow::setChartBlueCeruleanTheme(bool checked)
{
    if (checked)
        this->m_central->chartView()->chart()->setTheme(QChart::ChartThemeBlueCerulean);
}

void SPMmainWindow::setChartBlueIcyTheme(bool checked)
{
    if (checked)
        this->m_central->chartView()->chart()->setTheme(QChart::ChartThemeBlueIcy);
}

void SPMmainWindow::setChartBlueNscTheme(bool checked)
{
    if (checked)
        this->m_central->chartView()->chart()->setTheme(QChart::ChartThemeBlueNcs);
}

void SPMmainWindow::setChartHighContrastTheme(bool checked)
{
    if (checked)
        this->m_central->chartView()->chart()->setTheme(QChart::ChartThemeHighContrast);
}

void SPMmainWindow::setChartQtTheme(bool checked)
{
    if (checked)
        this->m_central->chartView()->chart()->setTheme(QChart::ChartThemeQt);
}

void SPMmainWindow::setChartNoAnimation(bool checked)
{
    if (checked)
        this->m_central->chartView()->chart()->setAnimationOptions(QChart::NoAnimation);
}

void SPMmainWindow::setChartGridAxisAnimation(bool checked)
{
    if (checked)
        this->m_central->chartView()->chart()->setAnimationOptions(QChart::GridAxisAnimations);
}

void SPMmainWindow::setChartSeriesAnimation(bool checked)
{
    if (checked)
        this->m_central->chartView()->chart()->setAnimationOptions(QChart::SeriesAnimations);
}

void SPMmainWindow::setChartAllAnimation(bool checked)
{
    if (checked)
        this->m_central->chartView()->chart()->setAnimationOptions(QChart::AllAnimations);
}

void SPMmainWindow::setRenderedChartViewFlag(bool checked)
{
    this->m_central->chartView()->setRenderHint(QPainter::Antialiasing,checked);
}

void SPMmainWindow::beginDataExtration()
{
    QVector<TidesMeasurement> datos;

    int size = m_manualDataIntroductionWidget->model()->measurementData().size();

    qreal conversion = m_manualDataIntroductionWidget->conversionUnit();


    for (int i = 0; i < size ; ++i){
        if (m_manualDataIntroductionWidget->model()->measurementData().at(i).isValid()){

            datos.push_back(m_manualDataIntroductionWidget->model()->measurementData().at(i));

            if (conversion != 1.0){
                qreal value = m_manualDataIntroductionWidget->model()->measurementData().at(i).seaLevel()*conversion;
                datos[i].setSeaLevel(value);
            }
        }
    }

    m_metadataStorage.setProjectName(m_manualDataIntroductionWidget->projectName());
    m_metadataStorage.setStationName(m_manualDataIntroductionWidget->stationName());
    m_metadataStorage.setLocalizationName(m_manualDataIntroductionWidget->localizationName());
    m_metadataStorage.setCeroPuesto(m_manualDataIntroductionWidget->ceroPuesto());
    m_metadataStorage.setCeroUnits(m_manualDataIntroductionWidget->ceroUnit());
    m_metadataStorage.setNivelReferencia(m_manualDataIntroductionWidget->nivelReferencia());
    m_metadataStorage.setReferenceUnits(m_manualDataIntroductionWidget->referenceUnit());
    m_metadataStorage.setLatitud(m_manualDataIntroductionWidget->latitud());
    m_metadataStorage.setLongitud(m_manualDataIntroductionWidget->longitud());
    m_metadataStorage.setEquipmentID(m_manualDataIntroductionWidget->equipmentID());

    m_central->tableModel()->setMeasurements(datos);

    m_manualDataIntroductionWidget->close();
}

void SPMmainWindow::beginDataExtrationFromFile()
{
    m_metadataStorage.setProjectName(m_loadDialog->projectName());
    m_metadataStorage.setStationName(m_loadDialog->stationName());
    m_metadataStorage.setLocalizationName(m_loadDialog->localizationName());
    m_metadataStorage.setCeroPuesto(m_loadDialog->ceroPuesto());
    m_metadataStorage.setCeroUnits(m_loadDialog->ceroUnit());
    m_metadataStorage.setNivelReferencia(m_loadDialog->nivelReferencia());
    m_metadataStorage.setReferenceUnits(m_loadDialog->referenceUnit());
    m_metadataStorage.setLatitud(m_loadDialog->latitud());
    m_metadataStorage.setLongitud(m_loadDialog->longitud());
    m_metadataStorage.setEquipmentID(m_loadDialog->equipmentID());

    m_central->tableModel()->setMeasurements(m_loadDialog->measurementsData());

    m_loadDialog->close();
}


/*void SPMmainWindow::gettingData(const QVector<QStringList> &data, int dateField, int timeField, int heightField)
{
    m_central->recieveData(data,dateField,timeField,heightField);
    //m_loadDialog = 0;
}*/

void SPMmainWindow::createActions()
{
    m_newProjectAction = new QAction(QIcon(":/images/project-new.png"),tr("&Nuevo"),this);
    m_newProjectAction->setShortcut(QKeySequence::New);
    m_newProjectAction->setToolTip(tr("Crear nuevo proyecto"));
    //NOTE connect

    m_loadProjectAction = new QAction(QIcon(":/images/project-open.png"),tr("&Abrir"),this);
    m_loadProjectAction->setShortcut(QKeySequence::Open);
    m_loadProjectAction->setToolTip(tr("Cargar proyecto"));
    //NOTE connect

    m_saveProjectAction = new QAction(QIcon(":/images/save.png"),tr("&Guardar"),this);
    m_saveProjectAction->setShortcut(QKeySequence::Save);
    m_saveProjectAction->setToolTip(tr("Guardar proyecto"));
    //NOTE connect

    m_saveAsProjectAction = new QAction(QIcon(":/images/saveAs.png"),tr("Guardar &Como..."),this);
    m_saveAsProjectAction->setShortcut(QKeySequence::SaveAs);
    m_saveAsProjectAction->setToolTip(tr("Guardar proyecto como..."));
    //NOTE connect

    m_projectMetaDataAction = new QAction(QIcon(":/images/project-info.png"),tr("&Información"),this);
    m_projectMetaDataAction->setToolTip(tr("Información del Proyecto"));
    connect(m_projectMetaDataAction,SIGNAL(triggered(bool)),this,SLOT(createMetaDataDialog()));

    m_exitAction = new QAction(QIcon(":/images/project-close.png"),tr("Salir"),this);
    m_exitAction->setShortcut(QKeySequence::Quit);
    m_exitAction->setToolTip(tr("Cerrar aplicación"));
    connect(m_exitAction,SIGNAL(triggered(bool)),qApp,SLOT(quit()));

    //Analisis Actions*******************************************************************************
    m_tablaHorariadeMareaAction = new QAction(QIcon(":/images/timetable.png"),tr("Tabla Horaria"),this);
    m_tablaHorariadeMareaAction->setToolTip(tr("Tabla horaria de marea"));
    connect(m_tablaHorariadeMareaAction,SIGNAL(triggered(bool)),this,SLOT(crearTablaHoraria()));

    m_harmonicAnalisisAction = new QAction(QIcon(":images/harmonic-analisis.png"),tr("Análisis Armónico"),this);
    m_harmonicAnalisisAction->setToolTip(tr("Análisis Armónico"));
    connect(m_harmonicAnalisisAction,SIGNAL(triggered(bool)),this,SLOT(createHarmonicAnalisisDialog()));
    m_nonHarmonicAnalisisAction = new QAction(QIcon(":images/non_harmonic-analisis.png"),tr("Constantes No Armonicas"),this);
    m_nonHarmonicAnalisisAction->setToolTip(tr("Constantes No Armonicas"));
    connect(m_nonHarmonicAnalisisAction,SIGNAL(triggered(bool)),this,SLOT(createNonHarmonicDialog()));

    m_freqEditorAction = new QAction(tr("Editor de Componentes"),this);
    //TODO icon
    connect(m_freqEditorAction,SIGNAL(triggered(bool)),this,SLOT(createFrequencyEditor()));
    m_nivelacionAcuaticaAction = new QAction(QIcon(":images/nivelacion_acuatica.png"),tr("Nivelación Acuática"));
    connect(m_nivelacionAcuaticaAction,SIGNAL(triggered(bool)),this,SLOT(createNivelacionAcuaticaWidget()));


    //ChartActions--------------------------------------------------------------
    m_themeLightAction = new QAction(tr("Claro"),this);
    m_themeLightAction->setCheckable(true);
    connect(m_themeLightAction,SIGNAL(triggered(bool)),this,SLOT(setChartLightTheme(bool)));

    m_themeDarkAction = new QAction(tr("Oscuro"),this);
    m_themeDarkAction->setCheckable(true);
    connect(m_themeDarkAction,SIGNAL(triggered(bool)),this,SLOT(setChartDarkTheme(bool)));

    m_themeBlueCeruleanAction = new QAction(tr("Azul1"),this);
    m_themeBlueCeruleanAction->setCheckable(true);
    connect(m_themeBlueCeruleanAction,SIGNAL(triggered(bool)),this,SLOT(setChartBlueCeruleanTheme(bool)));

    m_themeBrownSandAction = new QAction(tr("Medio"),this);
    m_themeBrownSandAction->setCheckable(true);
    connect(m_themeBrownSandAction,SIGNAL(triggered(bool)),this,SLOT(setChartBrownSandTheme(bool)));

    m_themeBlueIcyAction = new QAction(tr("Azul2"),this);
    m_themeBlueIcyAction->setCheckable(true);
    connect(m_themeBlueIcyAction,SIGNAL(triggered(bool)),this,SLOT(setChartBlueIcyTheme(bool)));

    m_themeBlueNcsAction = new QAction(tr("Azul3"),this);
    m_themeBlueNcsAction->setCheckable(true);
    connect(m_themeBlueNcsAction,SIGNAL(triggered(bool)),this,SLOT(setChartBlueNscTheme(bool)));

    m_themeHighcontrastAction = new QAction(tr("Alto Contraste"),this);
    m_themeHighcontrastAction->setCheckable(true);
    connect(m_themeHighcontrastAction,SIGNAL(triggered(bool)),this,SLOT(setChartHighContrastTheme(bool)));

    m_themeQtAction = new QAction(tr("Qt"),this);
    m_themeQtAction->setCheckable(true);
    connect(m_themeQtAction,SIGNAL(triggered(bool)),this,SLOT(setChartQtTheme(bool)));

    m_themeGroup = new QActionGroup(this);
    m_themeGroup->addAction(m_themeLightAction);
    m_themeGroup->addAction(m_themeDarkAction);
    m_themeGroup->addAction(m_themeBrownSandAction);
    m_themeGroup->addAction(m_themeBlueCeruleanAction);
    m_themeGroup->addAction(m_themeBlueIcyAction);
    m_themeGroup->addAction(m_themeBlueNcsAction);
    m_themeGroup->addAction(m_themeHighcontrastAction);
    m_themeGroup->addAction(m_themeQtAction);

    m_animationNoAnimationAction = new QAction(tr("Ninguna"),this);
    m_animationNoAnimationAction->setCheckable(true);
    connect(m_animationNoAnimationAction,SIGNAL(triggered(bool)),this,SLOT(setChartNoAnimation(bool)));

    m_animationGridAxisAnimationAction = new QAction(tr("Ejes"),this);
    m_animationGridAxisAnimationAction->setCheckable(true);
    connect(m_animationGridAxisAnimationAction,SIGNAL(triggered(bool)),this,SLOT(setChartGridAxisAnimation(bool)));

    m_animationSeriesAnimationAction = new QAction(tr("Series"),this);
    m_animationSeriesAnimationAction->setCheckable(true);
    connect(m_animationSeriesAnimationAction,SIGNAL(triggered(bool)),this,SLOT(setChartSeriesAnimation(bool)));

    m_animationAllAnimationAction = new QAction(tr("Todas"),this);
    m_animationAllAnimationAction->setCheckable(true);
    connect(m_animationAllAnimationAction,SIGNAL(triggered(bool)),this,SLOT(setChartAllAnimation(bool)));

    m_animationGroup = new QActionGroup(this);
    m_animationGroup->addAction(m_animationNoAnimationAction);
    m_animationGroup->addAction(m_animationGridAxisAnimationAction);
    m_animationGroup->addAction(m_animationSeriesAnimationAction);
    m_animationGroup->addAction(m_animationAllAnimationAction);

    m_chartRenderHintAction = new QAction(tr("Antialiasing"),this);
    m_chartRenderHintAction->setCheckable(true);
    connect(m_chartRenderHintAction,SIGNAL(toggled(bool)),this,SLOT(setRenderedChartViewFlag(bool)));
    m_chartRenderHintAction->setChecked(true);
    //view Actions--------------------------------------------------

    //Data Actions---------------------------------------------------------------------
    m_manualDataIntroductionAction = new QAction(QIcon(":/images/table_pencil.png"),tr("Introducción Manual"),this);
    connect(m_manualDataIntroductionAction,SIGNAL(triggered(bool)),
            this,SLOT(createManualDataIntWidget()));

    m_importFrom_ASCII_Action =  new QAction(QIcon(":/images/import.png"),tr("Importar"),this);
    m_importFrom_ASCII_Action->setToolTip(tr("Importar datos desde archivo ASCII"));
    connect(m_importFrom_ASCII_Action,SIGNAL(triggered(bool)),this,SLOT(loadDataFile()));

}

void SPMmainWindow::createMenus()
{
    m_fileMenu = menuBar()->addMenu(tr("Proyecto"));
    m_fileMenu->addAction(m_newProjectAction);
    m_fileMenu->addAction(m_loadProjectAction);
    m_fileMenu->addAction(m_saveProjectAction);
    m_fileMenu->addAction(m_saveAsProjectAction);

    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_projectMetaDataAction);
    m_fileMenu->addSeparator();

    m_fileMenu->addAction(m_exitAction);

    m_dataMenu = menuBar()->addMenu(tr("Datos"));
    m_dataMenu->addAction(m_manualDataIntroductionAction);
    m_dataMenu->addAction(m_importFrom_ASCII_Action);

    m_analisisMenu = menuBar()->addMenu(tr("Análisis"));
    m_analisisMenu->addAction(m_tablaHorariadeMareaAction);
    m_analisisMenu->addSeparator();
    m_analisisMenu->addAction(m_harmonicAnalisisAction);
    m_analisisMenu->addSeparator();
    m_analisisMenu->addAction(m_nonHarmonicAnalisisAction);

    m_toolMenu = menuBar()->addMenu(tr("Herramientas"));
    m_toolMenu->addAction(m_nivelacionAcuaticaAction);
    m_toolMenu->addAction(m_freqEditorAction);

    m_chartMenu = menuBar()->addMenu(tr("Gráfico"));
    m_animationSubMenu = m_chartMenu->addMenu(tr("Animaciones"));
    m_animationSubMenu->addActions(m_animationGroup->actions());
    m_themeSubMenu = m_chartMenu->addMenu(tr("Temas"));
    m_themeSubMenu->addActions(m_themeGroup->actions());

    m_chartMenu->addAction(m_chartRenderHintAction);

    //m_viewMenu = menuBar()->addMenu(tr("Ver"));
    //m_viewMenu->addAction(m_tablaHorariadeMareaAction);
}

void SPMmainWindow::createToolBars()
{
    m_projectToolBar = addToolBar(tr("Project"));
    m_projectToolBar->addAction(m_newProjectAction);
    m_projectToolBar->addAction(m_loadProjectAction);
    m_projectToolBar->addAction(m_saveProjectAction);
    m_projectToolBar->addAction(m_saveAsProjectAction);
    m_projectToolBar->addAction(m_projectMetaDataAction);

    m_dataToolBar = addToolBar(tr("Data"));
    m_dataToolBar->addAction(m_manualDataIntroductionAction);
    m_dataToolBar->addAction(m_importFrom_ASCII_Action);

    m_analsisToolBar = addToolBar(tr("Analisis"));
    m_analsisToolBar->addAction(m_tablaHorariadeMareaAction);
    m_analsisToolBar->addAction(m_harmonicAnalisisAction);
    m_analsisToolBar->addAction(m_nonHarmonicAnalisisAction);

    m_toolToolBar = addToolBar(tr("Herramientas"));
    m_toolToolBar->addAction(m_nivelacionAcuaticaAction);
}

void SPMmainWindow::syncData(const QVector<HarmonicConstant> &components) //Para sync si hay un cambio en los componentes que se editan en otra facilidad
{
    QFile file(m_schemesFilePath);

    if (file.open(QIODevice::ReadOnly)){
        QDataStream in(&file);

        in.setVersion(QDataStream::Qt_5_7);

        quint32 magicNumber;
        in >> magicNumber;

        if (magicNumber != SchemesMagicNumber){
            QMessageBox::information(this,tr("Error leyendo archivo"),tr("Error leyendo el archivo de configuracion %1").arg(file.fileName()));
            return;
        }
        uint schemeNumber;
        uint componentsNumber;

        in >> schemeNumber >> componentsNumber;

        QStringList schemes;
        QMap<QString,QString> schemeDescription;
        QMap<QString,QMap<QString,bool>> scheme_componentSatus;
        QMap<QString,bool> componentStatus;

        foreach (HarmonicConstant harmonic, components) {
            componentStatus[harmonic.name()] = false;
        }

        for (uint i = 0; i < schemeNumber; ++i){
            QString sch;
            QString desc;
            in >> sch >> desc;
            schemes.push_back(sch);
            schemeDescription[sch] = desc;
            for (uint j = 0; j < componentsNumber; ++j){
                QString comp;
                bool status;
                in >> comp >> status;
                if (componentStatus.contains(comp)) componentStatus[comp] = status;
            }
            scheme_componentSatus[sch] = componentStatus;

        }
        file.close();  //Cerrando el archivo.

        //Ahora vamos a escribir en este archivo de componentes

        if (file.open(QIODevice::WriteOnly)){
           QDataStream out(&file);
           out.setVersion(QDataStream::Qt_5_7);

           out << (quint32)SchemesMagicNumber;

           out << (uint)schemeNumber << (uint)components.size();

           foreach (QString schemeName, schemes) {
               out << schemeName << schemeDescription.value(schemeName);
               foreach (HarmonicConstant harmonic, components) {
                   out << harmonic.name() << scheme_componentSatus.value(schemeName).value(harmonic.name());
               }
           }

        }else{
            QMessageBox::information(this,tr("Error escribiendo archivo"),tr("Error escribiendo el archivo de configuracion %1").arg(file.fileName()));
            return;
        }
    }else{
        QMessageBox::information(this,tr("Error leyendo archivo"),tr("Error leyendo el archivo de configuracion %1").arg(file.fileName()));
        return;
    }


}

bool SPMmainWindow::createHarmonicAnalisisDialogFromConfigFile()
{
    QFile file(m_schemesFilePath);

    if (file.open(QIODevice::ReadOnly)){
        QDataStream in(&file);

        in.setVersion(QDataStream::Qt_5_7);

        quint32 magicNumber;
        in >> magicNumber;

        if (magicNumber != SchemesMagicNumber){
            QMessageBox::information(this,tr("Error leyendo archivo"),tr("Error leyendo el archivo de configuracion %1").arg(file.fileName()));
            return false;
        }
        uint schemeNumber;
        uint componentsNumber;

        in >> schemeNumber >> componentsNumber;

        QStringList schemes;
        QStringList components;
        QMap<QString,QString> schemeDescription;
        QMap<QString,QMap<QString,bool>> scheme_componentSatus;
        QMap<QString,bool> componentStatus;

        for (uint i = 0; i < schemeNumber; ++i){
            QString sch;
            QString desc;
            in >> sch >> desc;
            schemes.push_back(sch);
            schemeDescription[sch] = desc;
            for (uint j = 0; j < componentsNumber; ++j){
                QString comp;
                bool status;
                in >> comp >> status;
                if (!components.contains(comp)) components.append(comp); //para que los componentes se agreguen una sola ves, los comp de todos los esqumeas deben ser iguales, solo cambia el status
                componentStatus[comp] = status;
            }
            scheme_componentSatus[sch] = componentStatus;
            //components.clear();
        }
        if (schemeNumber == 0){

        }

        QDateTime iniDateTime;
        QDateTime endDateTime;

        if (!m_central->tableModel()->measurementData().isEmpty()){
            iniDateTime = QDateTime(m_central->tableModel()->measurementData().first().measurementDate(),m_central->tableModel()->measurementData().first().measurementTime(),Qt::UTC);
            endDateTime = QDateTime(m_central->tableModel()->measurementData().last().measurementDate(),m_central->tableModel()->measurementData().last().measurementTime(),Qt::UTC);
        }

        m_schemeWidget  = new SchemeWidget(iniDateTime, endDateTime, schemes,components,scheme_componentSatus,schemeDescription,this);
        return true;
    }else{
        QMessageBox::information(this,tr("Error leyendo archivo"),tr("Error leyendo el archivo de configuracion %1").arg(file.fileName()));
        return false;
    }
}

bool SPMmainWindow::loadHarmonicConstantsFromFile()
{
    QFile file(m_frequencyFilePath);

    if (file.open(QIODevice::ReadOnly)){
        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_5_7);

        qint32 number;

        QApplication::setOverrideCursor(Qt::WaitCursor);

        in >> number;

        if (number != ComponentsMagicNumber){
            QMessageBox::information(this,tr("Error al leer archivo"),tr("El archivo %1 no tiene el formato requerido.").arg(file.fileName()));
            return false;
        }

        qint16 rowNumber;
        //qint16 columnNumber;

        in >> rowNumber;

        QVector<HarmonicConstant> datos;


        QString name;
        double frequency;
        QString description;

        for (int i = 0; i < rowNumber; ++i){
            in >> name >> frequency >> description;
            datos.push_back(HarmonicConstant(name,frequency,description));
        }

        m_harmonicConstantVector = datos;

        QApplication::restoreOverrideCursor();

        return true;
    }

    QMessageBox::information(this,tr("Error al leer archivo"),tr("No se puede leer el archivo %1:\n%2.")
                             .arg(file.fileName().arg(file.errorString())));

    return false;
}

bool SPMmainWindow::saveAnalisisDataToFile(const QString &filePath)
{
    QFile file(filePath);

    if (file.open(QIODevice::WriteOnly)){
        QTextStream out(&file);
        if (m_schemeWidget->currentSelectionComboBoxIndex()){
            QDateTime initialDateTime = m_schemeWidget->initialDateTime();
            QDateTime endDateTime = m_schemeWidget->endDateTime();
            if (initialDateTime >= endDateTime){
                QMessageBox::information(this,tr("Error en analisis"),tr("La fecha final es menor que la fecha inicial."));
                return false;
            }

            quint64 timeInterval = m_schemeWidget->timeInterval();

            if (m_central->tableModel()->measurementData().isEmpty()) return false;

            QDateTime auxDateTime = initialDateTime;
            foreach (TidesMeasurement meas, m_central->tableModel()->measurementData()) {
                if (auxDateTime <= endDateTime){
                    if (auxDateTime == meas.measurementDateTime()){
                       out << meas.measurementDate().toString("yyyy/MM/dd") << " " << meas.measurementTime().toString("hh:mm") << " " << meas.seaLevel() << endl;
                    }
                    while (auxDateTime <= meas.measurementDateTime()){
                        auxDateTime = auxDateTime.addSecs(timeInterval);
                    }

                }

            }

        }else{
            foreach (TidesMeasurement meas, m_central->tableModel()->measurementData()) {
                out << meas.measurementDate().toString("yyyy/MM/dd") << " " << meas.measurementTime().toString("hh:mm") << " " << meas.seaLevel() << endl;
            }
        }
    }else{
        QMessageBox::information(this,tr("Error Guardando Datos"),tr("El archivo %1 no se puede escribir").arg(file.fileName()));
        return false;
    }
    return true;
}

void SPMmainWindow::saveHarmonicConstants(const QString &filePath)
{
    QFile file(filePath);

    if (file.open(QIODevice::WriteOnly)){
        QTextStream out(&file);

        out << "CONSTANTES ARMONICAS" << endl;
        out << endl;



        qreal latitud = m_metadataStorage.latitud();
        qreal longitud = m_metadataStorage.longitud();

        out << "PROYECTO: "<< m_metadataStorage.projectName() << endl;
        out << "ESTACION: " << m_metadataStorage.stationName() << endl;
        out << "SITUACION: " << m_metadataStorage.localizationName() << endl;

        if (latitud < 0.0)  out << "LATITUD: " << qFabs(latitud) << "S" << endl;
        if (latitud > 0.0)  out << "LATITUD: " << latitud << "N" << endl;
        if (latitud == 0.0) out << "LATITUD: " << "0.000" << endl;

        if (longitud < 0.0)  out << "LONGITUD: " << qFabs(longitud) << "W" << endl;
        if (longitud > 0.0)  out << "LONGITUD: " << longitud << "E" << endl;
        if (longitud == 0.0) out << "LONGITUD: " << "0.000" << endl;

        out << endl;

        /*out << "TIPO DE MAREA: " << m_tipoMareaLineEdit->text() <<endl;
        out << "RELACION DE AMPLITUD: " << m_ampRelationLineEdit->text() << endl;
        out << "RELACION SEMIDIURNA: " << m_semidiurnalRelationLineEdit->text() << endl;*/

        QString constituente("CONSTITUENTE");
        QString v_ang("V. ANGULAR[grad/seg]");
        QString amp("AMPLITUD[m]");
        QString fase("FASE[grad]");


        out << constituente << "  " << v_ang << "  " << amp << "  " << fase << endl;
        out << "------------" << "  " << "--------------------" << "  " << "-----------" << "  " << "----------" << endl;

        foreach (HarmonicConstant hc, m_selectedHarmonicConstantVector) {
            out.setFieldWidth(constituente.length());
            out.setFieldAlignment(QTextStream::AlignCenter);
            out << hc.name();


            out.setFieldWidth(0);
            out.setFieldAlignment(QTextStream::AlignCenter);
            out << "  ";

            out.setFieldWidth(v_ang.length());
            out.setFieldAlignment(QTextStream::AlignCenter);
            out << hc.frequency();

            out.setFieldWidth(0);
            out.setFieldAlignment(QTextStream::AlignCenter);
            out << "  ";

            out.setFieldWidth(amp.length());
            out.setFieldAlignment(QTextStream::AlignCenter);
            out << hc.amplitud();

            out.setFieldWidth(0);
            out.setFieldAlignment(QTextStream::AlignCenter);
            out << "  ";

            out.setFieldWidth(fase.length());
            out.setFieldAlignment(QTextStream::AlignCenter);
            out << hc.phase();

            out.setFieldWidth(0);
            out.setFieldAlignment(QTextStream::AlignCenter);
            out << endl;
        }


    }else{
        QMessageBox::information(this,tr("Error Guardando Archivo"),tr("No se puede escribir el archivo"
                                                                       "%1").arg(file.fileName()));
    }
    file.close();
}


