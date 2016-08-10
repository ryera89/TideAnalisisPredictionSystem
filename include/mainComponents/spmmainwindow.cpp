#include "spmmainwindow.h"


#include <QHBoxLayout>

SPMmainWindow::SPMmainWindow(QWidget *parent) : QMainWindow(parent)
{
    m_central = new CentralWidget(this);
    m_loadDialog = 0;
    setCentralWidget(m_central);

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
                    m_central,SLOT(recieveData(QVector<QStringList>,int,int,int, const QString&, const QString&)));

        //TODO: Las conexiones de los senales del dialogo para coger la localizacion Eq_Id, Lat, Long
        m_loadDialog->show();
    }

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
}
