#include "spmmainwindow.h"


#include <QHBoxLayout>

SPMmainWindow::SPMmainWindow(QWidget *parent) : QMainWindow(parent)
{
    m_central = new CentralWidget(this);
    m_loadDialog = 0;
    m_tablaHorariaWidget = 0;
    setCentralWidget(m_central);

    m_datosDeMarea = new TidalData(QVector<TidesMeasurement>(100));

    m_tidalTableModel = new ReadOnlyTableModel(m_datosDeMarea);

    m_central->tableView()->setModel(m_tidalTableModel);

    int width = 20 + m_central->tableView()->verticalHeader()->width();
    for (int i = 0; i < m_tidalTableModel->columnCount(QModelIndex()); ++i){
         width += m_central->tableView()->columnWidth(i);
    }
    m_central->tableView()->setFixedWidth(width);

    mapper = new XYTidalChartModelMapper(m_tidalTableModel,m_central->chartSerie());
    connect(mapper,SIGNAL(chartSeriesSeted()),m_central,SLOT(setSeriesData()));
    connect(mapper,SIGNAL(chartSeriesUpdated(int)),m_central,SLOT(updateSerieData(int)));

    //this->layout()->addWidget(m_dataTable);
    //this->layout()->addWidget(m_freqEditor);

    createActions();
    createMenus();

   // QHBoxLayout *mainLayout = new QHBoxLayout;

    //mainLayout->addWidget(m_dataTable);
   // mainLayout->addWidget(m_freqEditor);

    //this->layout()->addItem(mainLayout);

}

void SPMmainWindow::loadDataFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Cargar Archivo"));
    if (!fileName.isEmpty()){
        m_loadDialog = new LoadDialog(fileName,this);
        connect(m_loadDialog,SIGNAL(dataGeted(QVector<QStringList>,int,int,int, const QString&, const QString&)),
                    this,SLOT(recieveData(QVector<QStringList>,int,int,int, const QString&, const QString&)));

        //TODO: Las conexiones de los senales del dialogo para coger la localizacion Eq_Id, Lat, Long
        m_loadDialog->show();
    }

}

void SPMmainWindow::crearTablaHoraria()
{
    m_tablaHorariaWidget = new TablaHorariaWidget;
    m_tablaHorariaWidget->loadTableData(this->datosDeMarea());

    m_tablaHorariaWidget->show();

}

void SPMmainWindow::recieveData(const QVector<QStringList> &data, int dateField, int timeField, int heightField, const QString &dateFormat, const QString &timeFormat)
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

   /*m_tideChartView->chart()->removeSeries(m_series);
   m_tideChartView->chart()->removeAxis(m_timeAxis);

   m_timeAxis->setRange(QDateTime::fromMSecsSinceEpoch(m_series->at(0).x()),QDateTime::fromMSecsSinceEpoch(m_series->at(m_series->count() - 1).x()));

   m_tideChartView->chart()->addSeries(m_series);
   m_tideChartView->chart()->createDefaultAxes();

   m_tideChartView->chart()->setAxisX(m_timeAxis,m_series);*/
}

/*void SPMmainWindow::gettingData(const QVector<QStringList> &data, int dateField, int timeField, int heightField)
{
    m_central->recieveData(data,dateField,timeField,heightField);
    //m_loadDialog = 0;
}*/

void SPMmainWindow::createActions()
{
    m_newProjectAction = new QAction(tr("&Nuevo Proyecto"),this);
    //NOTE: icon
    m_newProjectAction->setShortcut(QKeySequence::New);
    m_newProjectAction->setToolTip(tr("Crea un nuevo proyecto"));
    //NOTE connect

    m_loadProjectAction = new QAction(tr("&Cargar Proyecto"),this);
    //NOTE: icon
    m_loadProjectAction->setShortcut(QKeySequence::Open);
    m_loadProjectAction->setToolTip(tr("Carga un proyecto"));
    //NOTE connect

    m_saveProjectAction = new QAction(tr("&Salvar Proyecto"),this);
    //NOTE: icon
    m_saveProjectAction->setShortcut(QKeySequence::Save);
    m_saveProjectAction->setToolTip(tr("Salva el proyecto"));
    //NOTE connect

    m_saveAsProjectAction = new QAction(tr("S&alvar Proyecto Como..."),this);
    //NOTE: icon
    m_saveAsProjectAction->setShortcut(QKeySequence::SaveAs);
    m_saveAsProjectAction->setToolTip(tr("Salva el proyecto"));
    //NOTE connect

    /*m_importFrom_CVS_Action =  new QAction(tr("Importar desde archivo cvs"),this);
    //NOTE: icon
    //m_importFrom_CVS_Action->setShortcut(QKeySequence::SaveAs);
    m_importFrom_CVS_Action->setToolTip(tr("Importar los datos desde un archivo .cvs"));
    //NOTE connect*/

    m_importFrom_ASCII_Action =  new QAction(tr("Importar"),this);
    //NOTE: icon
    //m_importFrom_CVS_Action->setShortcut(QKeySequence::SaveAs);
    m_importFrom_ASCII_Action->setToolTip(tr("Importar desde archivo ASCII"));
    //NOTE connect
    connect(m_importFrom_ASCII_Action,SIGNAL(triggered(bool)),this,SLOT(loadDataFile()));

    m_exitAction = new QAction(tr("Salir"),this);
    //NOTE: icon
    m_exitAction->setShortcut(QKeySequence::Quit);
    m_exitAction->setToolTip(tr("Salir de SPM"));
    connect(m_exitAction,SIGNAL(triggered(bool)),qApp,SLOT(quit()));


    //view Actions--------------------------------------------------
    m_tablaHorariadeMareaAction = new QAction(tr("Tabla Horaria"),this);
    //icon
    m_tablaHorariadeMareaAction->setToolTip(tr("Muestra la tabla horaria de marea"));
    connect(m_tablaHorariadeMareaAction,SIGNAL(triggered(bool)),this,SLOT(crearTablaHoraria()));
    //NOTE: Faltan muchas mas acciones

}

void SPMmainWindow::createMenus()
{
    m_fileMenu = menuBar()->addMenu(tr("Archivo"));
    m_fileMenu->addAction(m_newProjectAction);
    m_fileMenu->addAction(m_loadProjectAction);
    m_fileMenu->addAction(m_saveProjectAction);
    m_fileMenu->addAction(m_saveAsProjectAction);

    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_importFrom_ASCII_Action);

    //m_importSubMenu = m_fileMenu->addMenu(tr("&Importar"));
    //m_importSubMenu->addAction(m_importFrom_CVS_Action);
    //m_importSubMenu->addAction(m_importFrom_TXT_Action);

    m_fileMenu->addAction(m_exitAction);

    m_viewMenu = menuBar()->addMenu(tr("Ver"));
    m_viewMenu->addAction(m_tablaHorariadeMareaAction);
}
